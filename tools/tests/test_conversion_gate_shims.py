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


def test_vendored_ea_macro_new_use_refused():
    # Since 2026-10-14 (CR2B H1) a new use of an outside emit macro is growth.
    assert run(INC + F(""), INC + F("\tRAWS\n"), {EA: "#define RAWS __emit 0xC3\n"}) != []


def test_shims_constant_resolves():
    hdr = {SHIM: "#define OPS 0x90\n#define USES __emit OPS\n"}
    assert run(INC + F("\t__emit 0x90\n"), INC + F("\t__emit OPS\n"), hdr) == []


def test_vendored_ea_constant_not_resolved():
    hdr = {EA: "#define OPS 0x90\n#define USES __emit OPS\n"}
    assert run(INC + F("\t__emit 0x90\n"), INC + F("\t__emit OPS\n"), hdr) != []


# --- Round-1 review (2026-10-14): shims diffs are judged, any-emit wins ---
GH = "game/GameEngine/Include/Common/ProbeEmit.h"
INC_ = "inputs/reference/shims/probe/ProbeEmit.inc"


def two(b, a):
    return _gate(b, a)


def test_shims_two_step_macro_flip_refused():
    use = {P: INC + F("\tRAWS\n")}
    assert two(dict(use, **{SHIM: "#define RAWS __asm nop\n"}),
               dict(use, **{SHIM: "#define RAWS __emit 0xC3\n"})) != []


def test_shims_macro_non_emit_edit_passes():
    use = {P: INC + F("\tRAWS\n")}
    assert two(dict(use, **{SHIM: "#define RAWS __asm nop\n"}),
               dict(use, **{SHIM: "#define RAWS __asm int 3\n"})) == []


def test_shims_constant_flip_refused():
    use = {P: INC + F("\t__emit OPS\n")}
    assert two(dict(use, **{SHIM: "#define OPS 0x90\n"}),
               dict(use, **{SHIM: "#define OPS 0xC3\n"})) != []


def test_shims_constant_change_unused_by_emit_passes():
    use = {P: INC + F("\t__emit 0x90\n") + "int k = OPS;\n"}
    assert two(dict(use, **{SHIM: "#define OPS 0x90\n"}),
               dict(use, **{SHIM: "#define OPS 0xC3\n"})) == []


def test_shims_header_only_emit_added_refused():
    assert two({SHIM: "#define A 1\n"}, {SHIM: "#define A 1\n#define RAWS __emit 0xC3\n"}) != []


def test_shims_header_only_clean_edit_passes():
    assert two({SHIM: "#define A 1\n"}, {SHIM: "#define A 2\n"}) == []


def test_shims_non_h_file_macro_refused():
    assert run(INC + F(""), INC + F("\tRAWS\n"), {INC_: "#define RAWS __emit 0xC3\n"}) != []


def test_shims_non_h_file_macro_reshown_passes():
    hdr = {INC_: "#define RAWS __emit 0xC3\n"}
    assert run("int y;\n" + INC + F("\tRAWS\n"), INC + F("\tRAWS\n"), hdr) == []


def test_p1_shim_cannot_shadow_game_emit_macro():
    hdr = {GH: "#define EB(x) __emit x\n", SHIM: "#ifndef X\n#define EB(x) x\n#endif\n"}
    assert run(INC + F(""), INC + F("\tEB(0xC3)\n"), hdr) != []


def test_p1_shadowed_macro_reshown_passes():
    hdr = {GH: "#define EB(x) __emit x\n", SHIM: "#ifndef X\n#define EB(x) x\n#endif\n"}
    assert run("int y;\n" + INC + F("\tEB(0xC3)\n"), INC + F("\tEB(0xC3)\n"), hdr) == []


def test_r1_identical_duplicate_constant_resolves():
    hdr = {GH: "#define OPN 0x90\n#define USEG __emit OPN\n",
           SHIM: "#define OPN 0x90\n#define USEN __emit OPN\n"}
    assert run(INC + F("\t__emit 0x90\n"), INC + F("\t__emit OPN\n"), hdr) == []


def test_r1_differing_duplicate_constant_unresolved():
    hdr = {GH: "#define OPN 0x90\n", SHIM: "#define OPN 0xC3\n#define USEN __emit OPN\n"}
    assert run(INC + F("\t__emit 0x90\n"), INC + F("\t__emit OPN\n"), hdr) != []


def test_r2_mixed_ifdef_definition_fails_closed():
    hdr = {SHIM: "#ifdef ASMOK\n#define SZ(x) __emit x\n#else\n#define SZ(x) (x)\n#endif\n"}
    assert run(INC + "int h() { return 0; }\n", INC + "int h() { return SZ(1); }\n", hdr) != []


def test_r2_non_emit_only_definition_passes():
    hdr = {SHIM: "#ifndef ASMOK\n#define SZ(x) (x)\n#else\n#define SZ(x) ((x) + 1)\n#endif\n"}
    assert run(INC + "int h() { return 0; }\n", INC + "int h() { return SZ(1); }\n", hdr) == []


def test_r3_emit_in_string_literal_is_not_an_emit_macro():
    hdr = {SHIM: '#define NOTE "uses __emit"\n'}
    assert run(INC + "const char *h() { return 0; }\n",
               INC + "const char *h() { return NOTE; }\n", hdr) == []


def test_r3_emit_outside_string_is_an_emit_macro():
    hdr = {SHIM: '#define NOTE "uses" __emit 0x90\n'}
    assert run(INC + "const char *h() { return 0; }\n",
               INC + "const char *h() { return NOTE; }\n", hdr) != []


# --- Round-2 review: a char literal '"' cannot open a fake string ---
def test_char_literal_quote_in_header_macro_refused():
    hdr = {SHIM: "#define RAWS __asm mov al,'\"' __emit 0xC3 __asm mov al,'\"'\n"}
    assert run(INC + F(""), INC + F("\tRAWS\n"), hdr) != []


def test_char_literal_quote_in_game_body_refused():
    b = {"game/G/a.cpp": "void f()\n{\n  int a=1;\n}\n"}
    a = {"game/G/a.cpp": "void f()\n{\n  int a=1;\n"
                         "  char c='\"'; __asm _emit 0xC3 __asm _emit 0x90 char d='\"';\n}\n"}
    assert _gate(b, a) != []


def test_real_string_with_emit_still_not_an_emit_macro():
    hdr = {SHIM: "#define NOTE \"it's __emit\"\n"}
    assert run(INC + "const char *h() { return 0; }\n",
               INC + "const char *h() { return NOTE; }\n", hdr) == []
