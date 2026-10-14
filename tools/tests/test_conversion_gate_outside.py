"""Emit macros defined outside game/ and inputs/reference/shims/ (approved
2026-10-14, CR2B H1): an added #include of such a file is refused (Rule A3),
and a new use of such a macro in game/ is emit growth."""
import os
import subprocess
import sys
import tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "tests"))
sys.path.insert(0, str(ROOT / "tools"))
import conversion_gate as gate  # noqa
from test_conversion_gate_reshown_emit import _gate  # noqa

P = "game/G/a.cpp"
V = "inputs/vendor/v/e.h"
V2 = "inputs/vendor/v/wrap.h"
VE = {V: "#define OP(x) __asm _emit x\n"}
F = lambda body: "void f()\n{\n%s}\n" % body


def includes(before, after):
    """Rule A3 on a staged change (before/after: path -> text)."""
    with tempfile.TemporaryDirectory() as tmp:
        git = lambda *a: subprocess.run(["git", "-C", tmp, *a], check=True,
                                        capture_output=True, text=True)
        git("init", "-q")
        for files in (before, after):
            for path, text in files.items():
                full = Path(tmp) / path
                full.parent.mkdir(parents=True, exist_ok=True)
                full.write_text(text)
            git("add", "-A")
            if files is before:
                git("-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "b", "--allow-empty")
        here = os.getcwd()
        os.chdir(tmp)
        try:
            gate._LISTING.clear()
            gate._OUTSIDE.clear()
            return gate.added_outside_includes("HEAD", ":")
        finally:
            os.chdir(here)


def both(before, after):
    return _gate(before, after) + includes(before, after)


# --- Rule A3: added include ---
def test_added_include_of_vendor_emit_header_refused():
    assert includes(dict(VE, **{P: F("")}), dict(VE, **{P: '#include "v/e.h"\n' + F("")})) != []


def test_added_include_of_vendor_clean_header_passes():
    hdr = {V: "#define OP(x) (x)\n#define S \"__emit\"\n"}
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "v/e.h"\n' + F("")})) == []


def test_transitive_include_through_vendor_header_refused():
    hdr = dict(VE, **{V2: '#include "e.h"\n#define W 1\n'})
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "wrap.h"\n' + F("")})) != []


def test_transitive_include_of_clean_vendor_headers_passes():
    hdr = {V: "#define OP(x) (x)\n", V2: '#include "e.h"\n#define W 1\n'}
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "wrap.h"\n' + F("")})) == []


def test_moved_include_passes():
    b = dict(VE, **{P: '#include "v/e.h"\nint a;\n' + F("")})
    a = dict(VE, **{P: 'int a;\n#include "v/e.h"\n' + F("")})
    assert includes(b, a) == []


def test_shims_file_added_include_refused():
    s = "inputs/reference/shims/x/s.h"
    assert includes(dict(VE, **{s: "int a;\n"}), dict(VE, **{s: '#include "v/e.h"\nint a;\n'})) != []


def test_game_header_of_same_name_is_not_outside():
    hdr = {"game/G/e.h": "#define OP(x) __emit x\n"}
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "e.h"\n' + F("")})) == []


# --- new use of an outside emit macro ---
def test_cr2b_h1_repro_refused():
    b = dict(VE, **{P: F("\tint a = 1;\n")})
    a = dict(VE, **{P: '#include "v/e.h"\n' + F("\tint a = 1;\n\tOP(0xC3)\n")})
    assert both(b, a) != []


def test_new_use_via_existing_include_refused():
    b = dict(VE, **{P: '#include "v/e.h"\n' + F("\tint a = 1;\n")})
    a = dict(VE, **{P: '#include "v/e.h"\n' + F("\tint a = 1;\n\tOP(0xC3)\n")})
    assert _gate(b, a) != []


def test_new_use_via_outside_wrapper_macro_refused():
    hdr = dict(VE, **{V2: "#define W OP(0xC3)\n"})
    assert _gate(dict(hdr, **{P: F("\tint a = 1;\n")}),
                 dict(hdr, **{P: F("\tint a = 1;\n\tW\n")})) != []


def test_reshown_use_passes():
    b = dict(VE, **{P: "int y;\n" + F("\tOP(0xC3)\n")})
    a = dict(VE, **{P: F("\tOP(0xC3)\n")})
    assert _gate(b, a) == []


def test_use_of_vendor_non_emit_macro_passes():
    hdr = {V: "#define OP(x) (x)\n"}
    assert _gate(dict(hdr, **{P: "int g() { return 0; }\n"}),
                 dict(hdr, **{P: "int g() { return OP(1); }\n"})) == []


# --- grandfathered state on master ---
def test_allowlisted_include_passes():
    path, name = sorted(gate.OUTSIDE_INCLUDE_ALLOW)[0]
    o = "inputs/reference/ea/debug/" + name
    hdr = {o: "#define ts_lock _emit 0xF0\n"}
    assert includes(dict(hdr, **{path: "int a;\n"}),
                    dict(hdr, **{path: '#include "%s"\nint a;\n' % name})) == []


def test_same_include_in_other_file_refused():
    path, name = sorted(gate.OUTSIDE_INCLUDE_ALLOW)[0]
    hdr = {"inputs/reference/ea/debug/" + name: "#define ts_lock _emit 0xF0\n"}
    q = "game/G/other.h"
    assert includes(dict(hdr, **{q: "int a;\n"}),
                    dict(hdr, **{q: '#include "%s"\nint a;\n' % name})) != []


def test_existing_own_definition_use_passes():
    # wwmemlog.cpp / cpudetect.cpp define ts_lock / ASM_RDTSC themselves; the
    # EA copies outside do not change the verdict on re-shown uses.
    o = {"inputs/reference/ea/internal.h": "#define ts_lock _emit 0xF0\n"}
    body = "#define ts_lock _emit 0xF0\n" + F("\t__asm ts_lock\n")
    assert _gate(dict(o, **{P: "int y;\n" + body}), dict(o, **{P: body})) == []


def test_existing_own_definition_new_use_refused():
    o = {"inputs/reference/ea/internal.h": "#define ts_lock _emit 0xF0\n"}
    d = "#define ts_lock _emit 0xF0\n"
    assert _gate(dict(o, **{P: d + F("\tint a;\n")}), dict(o, **{P: d + F("\tint a;\n\t__asm ts_lock\n")})) != []


def test_allowlist_is_todays_three_pairs():
    assert len(gate.OUTSIDE_INCLUDE_ALLOW) == 3  # shrink-only


def test_sibling_quoted_include_is_not_outside():
    hdr = {"inputs/reference/ea/profile/internal.h": "#define ts_lock _emit 0xF0\n",
           "game/G/internal.h": "int z;\n"}
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "internal.h"\n' + F("")})) == []
