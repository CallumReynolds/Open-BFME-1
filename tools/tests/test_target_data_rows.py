"""Unexported data rows: witnessed by retail HIGHLOW operands, never by name alone."""
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import target_verify
from target_verify import TargetVerificationError

BASE = 0x400000
TEXT_RVA, DATA_RVA = 0x1000, 0x2000
DATUM = DATA_RVA + 0x99
HEADER = "name,target_rva,size,section,witnesses,evidence,model\n"


@dataclass
class Section:
    name: str
    rva: int
    virtual_size: int
    raw_size: int
    characteristics: int


@dataclass
class Reloc:
    rva: int
    type: int


class FakeTarget:
    """Code at 0x1000 that reads the byte at DATUM from offsets 2 and 0x10."""

    image_base = BASE
    exports = ()
    imports = ()

    def __init__(self, ledger):
        self.data_ledger_path = ledger
        self.sections = (Section(".text", TEXT_RVA, 0x100, 0x100, 0x60000020),
                         Section(".data", DATA_RVA, 0x200, 0x100, 0xC0000040))
        text = bytearray(b"\xcc" * 0x100)
        text[0:7] = b"\x80\x3d" + struct.pack("<I", BASE + DATUM) + b"\x00"
        text[0x0E:0x15] = b"\xc6\x05" + struct.pack("<I", BASE + DATUM) + b"\x01"
        text[0x20:0x26] = b"\x8b\x0d" + struct.pack("<I", BASE + DATA_RVA)
        self.text = bytes(text)
        self.relocations = (Reloc(TEXT_RVA + 2, 3), Reloc(TEXT_RVA + 0x10, 3), Reloc(TEXT_RVA + 0x22, 3))

    def section_for_rva(self, rva):
        return next(s for s in self.sections if s.rva <= rva < s.rva + s.virtual_size)

    def read_rva(self, rva, size):
        assert TEXT_RVA <= rva and rva + size <= TEXT_RVA + 0x100
        return self.text[rva - TEXT_RVA: rva - TEXT_RVA + size]


def ledger(tmp_path, row):
    path = tmp_path / "data.csv"
    path.write_bytes((HEADER + row + "\n").encode())
    return FakeTarget(path)


def row(witnesses="0x1002;0x1010", rva=None, section=".data"):
    rva = f"{DATUM:#x}" if rva is None else rva
    return f"?m_flag@Owner@@1_NA,{rva},1,{section},{witnesses},donor cites it,test"


def test_missing_ledger_is_empty(tmp_path):
    assert target_verify.read_data_rows(FakeTarget(tmp_path / "data.csv")) == {}


def test_witnessed_row_is_accepted(tmp_path):
    rows = target_verify.read_data_rows(ledger(tmp_path, row()))
    datum = rows["?m_flag@Owner@@1_NA"]
    assert datum["rva"] == DATUM and datum["witness_rvas"] == [0x1002, 0x1010]


@pytest.mark.parametrize("witnesses, message", [
    ("0x1003", "not a HIGHLOW"),
    ("0x1022", "addresses 0x2000"),
    ("0x1002;0x1002", "duplicate witness"),
])
def test_unwitnessed_address_is_rejected(tmp_path, witnesses, message):
    with pytest.raises(TargetVerificationError, match=message):
        target_verify.read_data_rows(ledger(tmp_path, row(witnesses)))


def test_section_must_match_and_hold_data(tmp_path):
    with pytest.raises(TargetVerificationError, match="lies in .data"):
        target_verify.read_data_rows(ledger(tmp_path, row(section=".bss")))
    with pytest.raises(TargetVerificationError, match="executable"):
        target_verify.read_data_rows(ledger(tmp_path, row("0x1002", rva="0x1080", section=".text")))


def test_crlf_ledger_is_rejected(tmp_path):
    path = tmp_path / "data.csv"
    path.write_bytes((HEADER + row() + "\n").replace("\n", "\r\n").encode())
    with pytest.raises(TargetVerificationError, match="LF"):
        target_verify.read_data_rows(FakeTarget(path))


def _relocate(target, symbol, rows):
    code = target.read_rva(TEXT_RVA, 7)
    code = code[:2] + b"\0\0\0\0" + code[6:]
    return target_verify._relocate(target, {"name": "f", "target_rva": TEXT_RVA}, None,
                                   code, [(2, 6, symbol)], {}, rows)


def test_relocation_uses_data_row(tmp_path):
    target = ledger(tmp_path, row())
    rows = target_verify.read_data_rows(target)
    linked, checks = _relocate(target, "?m_flag@Owner@@1_NA", rows)
    assert linked == target.read_rva(TEXT_RVA, 7)
    assert checks[0]["data"]["rva"] == DATUM


def test_relocation_without_row_still_needs_export(tmp_path):
    target = ledger(tmp_path, row())
    with pytest.raises(TargetVerificationError, match="no matching target export"):
        _relocate(target, "?m_other@Owner@@1_NA", target_verify.read_data_rows(target))


def test_relocation_to_another_address_is_rejected(tmp_path):
    target = ledger(tmp_path, row())
    rows = target_verify.read_data_rows(target)
    rows["?m_flag@Owner@@1_NA"] = {**rows["?m_flag@Owner@@1_NA"], "rva": DATUM + 1}
    with pytest.raises(TargetVerificationError, match="data row records"):
        _relocate(target, "?m_flag@Owner@@1_NA", rows)
