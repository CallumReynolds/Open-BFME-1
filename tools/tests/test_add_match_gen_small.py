"""add_match may repoint a game/gen_small/ claim to real C++, narrowly.

Approved by the project lead 2026-10-15: a gen-dtor placeholder
(game/gen_small/dtors_NNN.cpp / dtorsv_NNN.cpp) is retired by --replace-rva like a
gen-dump dump, and a hand-written claim in a game/gen_small/ U3*/W3* TU by
--replace-rva --correct-identity with token-exact identity evidence. The frozen
gen_small file is never edited: its remaining rows and every matched caller of the
retired name are re-verified in the same build, and the tool refuses when that
file also defines the new name.
"""
import csv
import io
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match

HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
RVA = "0x00707E60"
DTOR_OLD = "??_EGen_dtorv_00707e60@@UAEPAXI@Z"
DTOR_TU = "game/gen_small/dtorsv_000.cpp"
DTOR_ROW = f"{DTOR_OLD},,{RVA},84,{DTOR_TU},matched,gen-dtor;ghidra=gap"
SIBLING_ROW = (f"??_EGen_dtorv_00707f00@@UAEPAXI@Z,,0x00707F00,84,{DTOR_TU},matched,"
               "gen-dtor;ghidra=gap")
REAL = "??_ERoadType@@QAEPAXI@Z"
SOURCE_REL = "game/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp"

HAND_OLD = "?init@Rva0005DA80WideToAnsi@@QAEXPBGI@Z"
HAND_TU = "game/gen_small/W3AtlStringConversion.cpp"
HAND_RVA = "0x0005DA80"
HAND_ROW = (f"{HAND_OLD},,{HAND_RVA},107,{HAND_TU},matched,"
            "Open-BFME1 wide-to-ANSI conversion holder init; address-derived name")
HAND_NEW = "?Init@?$CW2AEX@$0IA@@ATL@@AAEXPBGI@Z"
PROOF = "targets/game/reverse/identity_evidence/0005da80-atl.md"
GOOD_PROOF = f"`{HAND_RVA}` ledgered as `{HAND_OLD}` is `{HAND_NEW}`.\n"


class Recorder:
    """subprocess.run double: records each build command, answers GATE."""

    def __init__(self, gate):
        self.gate = gate
        self.builds = []

    def __call__(self, command, **kwargs):
        if command and command[0] == "git":
            return SimpleNamespace(returncode=1, stdout=b"", stderr=b"")
        assert set(kwargs) == {"cwd", "env"}, kwargs
        self.builds.append(list(command))
        return SimpleNamespace(returncode=self.gate)


def arrange(tmp_path, monkeypatch, *, rows, name=REAL, rva=RVA, size="84",
            source=SOURCE_REL, replace_rva=RVA, extra=(), gate=0,
            callers=(), shadow=False, proof=None):
    reverse = tmp_path / "targets/game/reverse"
    reverse.mkdir(parents=True)
    src = tmp_path / source
    src.parent.mkdir(parents=True, exist_ok=True)
    src.write_bytes(b"void body() {}\r\n")
    functions = reverse / "functions.csv"
    functions.write_bytes((HEADER + "\r\n" + "".join(r + "\r\n" for r in rows)).encode())
    deleted = reverse / "deleted_rows.csv"
    deleted.write_bytes(b"name,target_rva,reason\n")
    if proof is not None:
        path = tmp_path / PROOF
        path.parent.mkdir(parents=True)
        path.write_text(proof)
    build_sh = tmp_path / "build.sh"
    build_sh.write_text("#!/bin/sh\nexit 0\n")
    build_sh.chmod(0o755)
    recorder = Recorder(gate)
    monkeypatch.setattr(add_match.subprocess, "run", recorder)
    seen = SimpleNamespace(callers=[], shadow=[])

    def fake_callers(root, replaced):
        seen.callers.append((replaced["name"], replaced["rva"]))
        return list(callers)

    def fake_defines(root, source_rel, symbol):
        seen.shadow.append((source_rel, symbol))
        return shadow

    monkeypatch.setattr(add_match, "orphaned_caller_selectors", fake_callers)
    monkeypatch.setattr(add_match, "frozen_tu_defines", fake_defines)
    monkeypatch.setattr(sys, "argv", [
        "add_match.py", name, rva, size, source, "--root", str(tmp_path),
        *(("--replace-rva", replace_rva) if replace_rva else ()), *extra])
    files = (functions, deleted, src)
    return files, recorder, seen


def snapshot(files):
    return tuple(path.read_bytes() for path in files)


def refused(files):
    before = snapshot(files)
    with pytest.raises(SystemExit):
        add_match.main()
    assert snapshot(files) == before


# --- allowed -------------------------------------------------------------------------

def test_gen_dtor_repoint_lands_and_reverifies_frozen_tu_and_callers(tmp_path, monkeypatch):
    callers = ["row:0x00012345:20:?caller@@YAXXZ"]
    files, recorder, seen = arrange(tmp_path, monkeypatch, rows=[DTOR_ROW, SIBLING_ROW],
                                    callers=callers)
    add_match.main()
    ledger = files[0].read_text()
    assert DTOR_OLD not in ledger
    assert f"{REAL},,{RVA},84,{SOURCE_REL},matched," in ledger
    assert ledger.count(RVA) == 1
    (command,) = recorder.builds
    assert command[1:] == [SOURCE_REL, *callers, DTOR_TU]
    assert seen.callers == [(DTOR_OLD, 0x00707E60)]
    assert seen.shadow == [(DTOR_TU, REAL)]
    tombstone = list(csv.reader(io.StringIO(files[1].read_text())))[-1]
    assert tombstone[:2] == [DTOR_OLD, RVA]
    assert "gen-dtor scaffold placeholder" in tombstone[2]
    assert "Prior notes: gen-dtor;ghidra=gap" in tombstone[2]


@pytest.mark.parametrize("tu,old", [
    ("game/gen_small/dtors_004.cpp", "??_GGen_dtor_0070a000@@UAEPAXI@Z"),
    ("game/gen_small/dtorsv_000.cpp", "??_EGen_dtorv_0070a000@@UAEPAXI@Z"),
])
def test_both_gen_dtor_families_are_admitted(tmp_path, monkeypatch, tu, old):
    row = f"{old},,0x0070A000,30,{tu},matched,gen-dtor"
    files, recorder, _ = arrange(tmp_path, monkeypatch, rows=[row], rva="0x0070A000",
                                 size="30", replace_rva="0x0070A000",
                                 name="??_GThing@@UAEPAXI@Z")
    add_match.main()
    assert old not in files[0].read_text()
    # last row of its TU: nothing left there to re-verify or to shadow the new body
    assert recorder.builds[0][1:] == [SOURCE_REL]


def test_hand_written_gen_small_identity_correction_lands(tmp_path, monkeypatch):
    sibling = (f"?Rva0005B7A0GetConversionCodePage@@YGIXZ,,0x0005B7A0,90,{HAND_TU},"
               "matched,address-derived name")
    files, recorder, seen = arrange(
        tmp_path, monkeypatch, rows=[HAND_ROW, sibling], name=HAND_NEW, rva=HAND_RVA,
        size="107", replace_rva=HAND_RVA,
        source="game/GameEngine/Source/Common/T3AtlCImageCreateFromGdiplusBitmap.cpp",
        extra=("--correct-identity", HAND_OLD, "--identity-evidence", PROOF),
        proof=GOOD_PROOF)
    add_match.main()
    ledger = files[0].read_text()
    assert HAND_OLD + "," not in ledger
    assert "identity-correction=" + PROOF in ledger
    assert recorder.builds[0][-1] == HAND_TU
    assert seen.shadow == [(HAND_TU, HAND_NEW)]
    tombstone = list(csv.reader(io.StringIO(files[1].read_text())))[-1]
    assert tombstone[0] == HAND_OLD
    assert "Identity evidence: " + PROOF in tombstone[2]
    assert "Prior notes: Open-BFME1 wide-to-ANSI" in tombstone[2]


# --- refused -------------------------------------------------------------------------

@pytest.mark.parametrize("row", [
    # generator output that is not a gen-dtor placeholder
    # (gen-thunk/gen-dump/gen-tgrid/gen-shim rows were replaceable before this change)
    f"?e_00707e60@@YAXXZ,,{RVA},84,game/gen_small/thunks_008.cpp,matched,gen-ehstub",
    f"?i_00707e60@@YAXXZ,,{RVA},84,game/gen_small/imports_000.cpp,matched,gen-import",
    f"$L1234,,{RVA},84,game/gen_small/uw_gen_001.cpp,matched,gen-funclet;parent=0x00707000",
    f"?x@@YAXXZ,,{RVA},84,game/gen_small/named_000.cpp,matched,gen-alias;object-symbol=?y@@YAXXZ",
    # gen-dtor note outside the dtors files, or a dtors file without the note
    f"{DTOR_OLD},,{RVA},84,game/gen_small/fam_001.cpp,matched,gen-dtor",
    f"{DTOR_OLD},,{RVA},84,{DTOR_TU},matched,authored",
    f"{DTOR_OLD},,{RVA},84,{DTOR_TU},unmatched,gen-dtorish",
    # a real-source row is not a scaffold
    f"?real@@YAXXZ,,{RVA},84,game/GameEngine/Real.cpp,matched,authored",
    # a hand-written gen_small row is a named claim: it needs --correct-identity
    f"{HAND_OLD},,{RVA},84,{HAND_TU},matched,address-derived name",
])
def test_non_admitted_rows_refused_without_identity_correction(tmp_path, monkeypatch, row):
    files, recorder, _ = arrange(tmp_path, monkeypatch, rows=[row])
    refused(files)
    assert recorder.builds == []


def test_wrong_bytes_restore_everything(tmp_path, monkeypatch):
    files, recorder, _ = arrange(tmp_path, monkeypatch, rows=[DTOR_ROW, SIBLING_ROW], gate=1)
    refused(files)
    assert len(recorder.builds) == 1


def test_red_caller_or_frozen_tu_restores_everything(tmp_path, monkeypatch):
    files, recorder, _ = arrange(tmp_path, monkeypatch, rows=[DTOR_ROW, SIBLING_ROW], gate=2,
                                 callers=["row:0x00012345:20:?caller@@YAXXZ"])
    refused(files)
    assert "row:0x00012345:20:?caller@@YAXXZ" in recorder.builds[0]


def test_frozen_tu_defining_the_new_name_is_refused(tmp_path, monkeypatch):
    files, recorder, seen = arrange(tmp_path, monkeypatch, rows=[DTOR_ROW, SIBLING_ROW],
                                    shadow=True)
    refused(files)
    assert seen.shadow == [(DTOR_TU, REAL)]


@pytest.mark.parametrize("rows,kwargs", [
    # two rows at the address
    ([DTOR_ROW, f"?other@@YAXXZ,,{RVA},84,game/GameEngine/Other.cpp,matched,authored"], {}),
    # the new name already claims another address
    ([DTOR_ROW, f"{REAL},,0x00700000,84,game/GameEngine/Other.cpp,matched,authored"], {}),
    # the new extent overlaps a matched neighbour
    ([DTOR_ROW, "?n@@YAXXZ,,0x00707E90,16,game/GameEngine/N.cpp,matched,authored"],
     {"size": "84"}),
])
def test_one_body_per_address(tmp_path, monkeypatch, rows, kwargs):
    files, recorder, _ = arrange(tmp_path, monkeypatch, rows=rows, **kwargs)
    refused(files)
    assert recorder.builds == []


@pytest.mark.parametrize("source", [
    "game/gen_small/RoadType.cpp",
    "game/gen_asm/d_00707e60.asm",
    "game/masm_dumps/RoadType.asm",
    "inputs/reference/RoadType.cpp",
    "game/GameEngine/RoadType.h",
])
def test_successor_must_be_real_compiled_cpp(tmp_path, monkeypatch, source):
    files, recorder, _ = arrange(tmp_path, monkeypatch, rows=[DTOR_ROW], source=source)
    refused(files)
    assert recorder.builds == []


@pytest.mark.parametrize("extra,size", [
    (("--no-verify",), "84"),
    (("--boundary-evidence", "ret at +0x50"), "88"),
])
def test_no_unverified_or_reshaped_gen_small_repoint(tmp_path, monkeypatch, extra, size):
    files, recorder, _ = arrange(tmp_path, monkeypatch, rows=[DTOR_ROW], extra=extra, size=size)
    refused(files)
    assert recorder.builds == []


def test_gen_dtor_is_not_an_identity_correction(tmp_path, monkeypatch):
    files, _, _ = arrange(tmp_path, monkeypatch, rows=[DTOR_ROW],
                          extra=("--correct-identity", DTOR_OLD, "--identity-evidence", PROOF),
                          proof=f"{RVA} {DTOR_OLD} {REAL}\n")
    refused(files)


def hand(tmp_path, monkeypatch, *, proof, row=HAND_ROW, old=HAND_OLD):
    return arrange(tmp_path, monkeypatch, rows=[row], name=HAND_NEW, rva=HAND_RVA,
                   size="107", replace_rva=HAND_RVA,
                   extra=("--correct-identity", old, "--identity-evidence", PROOF),
                   proof=proof)


@pytest.mark.parametrize("text", [
    f"{HAND_OLD} is {HAND_NEW}.\n",                       # no RVA
    f"0x0005DA90 {HAND_OLD} is {HAND_NEW}.\n",            # wrong RVA
    f"{HAND_RVA} is {HAND_NEW}.\n",                       # no old name
    f"{HAND_RVA} is not {HAND_OLD}.\n",                   # no new name
    f"{HAND_RVA} {HAND_OLD} is x{HAND_NEW}.\n",           # new name only inside a token
])
def test_hand_written_correction_needs_token_exact_evidence(tmp_path, monkeypatch, text):
    files, recorder, _ = hand(tmp_path, monkeypatch, proof=text)
    refused(files)
    assert recorder.builds == []


def test_hand_written_correction_needs_the_exact_old_name(tmp_path, monkeypatch):
    files, _, _ = hand(tmp_path, monkeypatch, proof=GOOD_PROOF + "?wrong@@YAXXZ\n",
                       old="?wrong@@YAXXZ")
    refused(files)


@pytest.mark.parametrize("row", [
    # generator-numbered file names and generator/alias notes are not hand-written
    HAND_ROW.replace(HAND_TU, "game/gen_small/zhstl_001.cpp"),
    HAND_ROW.replace(HAND_TU, "game/gen_small/fam_001.cpp"),
    HAND_ROW.replace("Open-BFME1 wide-to-ANSI", "gen-shim;family=f1"),
    HAND_ROW.replace("Open-BFME1 wide-to-ANSI", "zh-landmulti;object-symbol=?y@@YAXXZ"),
    HAND_ROW.replace(",matched,", ",unmatched,"),
])
def test_only_hand_written_matched_gen_small_rows_are_correctable(tmp_path, monkeypatch, row):
    files, _, _ = hand(tmp_path, monkeypatch, proof=GOOD_PROOF, row=row)
    refused(files)


def test_live_state_helpers_refuse_a_test_root(tmp_path):
    row = {"name": DTOR_OLD, "rva": 0x00707E60}
    with pytest.raises(SystemExit):
        add_match.orphaned_caller_selectors(tmp_path, row)
    with pytest.raises(SystemExit):
        add_match.frozen_tu_defines(tmp_path, DTOR_TU, REAL)
