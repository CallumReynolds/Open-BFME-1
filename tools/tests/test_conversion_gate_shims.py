"""Rule A follows emit macros and constants defined in inputs/reference/shims/
headers (approved 2026-10-14), but not in the vendored EA tree."""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "tests"))
sys.path.insert(0, str(ROOT / "tools"))
from test_conversion_gate_reshown_emit import _gate  # noqa

P = "game/GameEngine/Source/Common/Probe.cpp"
SHIM = "inputs/reference/shims/probe/ProbeEmit.h"
EA = "inputs/reference/ea/Code/GameEngine/Include/Common/ProbeEmit.h"
INC = '#include "ProbeEmit.h"\n'


def F(body):
    return "void g()\n{\n\t__asm {\n%s\t}\n}\n" % body


def run(b, a, files):
    before = {P: b}; after = {P: a}
    before.update(files); after.update(files)
    return _gate(before, after)


def test_shims_emit_macro_new_use_refused():
    assert run(INC + F(""), INC + F("\tRAWS\n"), {SHIM: "#define RAWS __emit 0xC3\n"}) != []


def test_shims_emit_macro_reshown_use_passes():
    hdr = {SHIM: "#define RAWS __emit 0xC3\n"}
    assert run("int y;\n" + INC + F("\tRAWS\n"), INC + F("\tRAWS\n"), hdr) == []


def test_vendored_ea_macro_not_followed():
    assert run(INC + F(""), INC + F("\tRAWS\n"), {EA: "#define RAWS __emit 0xC3\n"}) == []


def test_shims_constant_resolves():
    hdr = {SHIM: "#define OPS 0x90\n#define USES __emit OPS\n"}
    assert run(INC + F("\t__emit 0x90\n"), INC + F("\t__emit OPS\n"), hdr) == []


def test_vendored_ea_constant_not_resolved():
    hdr = {EA: "#define OPS 0x90\n#define USES __emit OPS\n"}
    assert run(INC + F("\t__emit 0x90\n"), INC + F("\t__emit OPS\n"), hdr) != []
