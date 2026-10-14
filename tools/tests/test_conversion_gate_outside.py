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


def includes(before, after, fn=None):
    """Rule A3 (or fn(old, new)) on a staged change (before/after: path -> text)."""
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
            return (fn or gate.added_outside_includes)("HEAD", ":")
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
def test_ea_pch_sibling_internal_is_not_a_reach():
    # The EA debug/_pch.h includes "internal.h": its clean sibling, not the
    # profile/internal.h that defines ts_lock.
    hdr = {"inputs/reference/ea/debug/_pch.h": '#include "internal.h"\n',
           "inputs/reference/ea/debug/internal.h": "int q;\n",
           "inputs/reference/ea/profile/internal.h": "#define ts_lock _emit 0xF0\n"}
    q = "game/G/other.h"
    assert includes(dict(hdr, **{q: "int a;\n"}),
                    dict(hdr, **{q: '#include "_pch.h"\nint a;\n'})) == []


def test_ea_pch_reaching_profile_internal_refused():
    hdr = {"inputs/reference/ea/profile/_pch.h": '#include "internal.h"\n',
           "inputs/reference/ea/profile/internal.h": "#define ts_lock _emit 0xF0\n"}
    q = "game/G/other.h"
    assert includes(dict(hdr, **{q: "int a;\n"}),
                    dict(hdr, **{q: '#include "_pch.h"\nint a;\n'})) != []


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


def test_allowlist_is_empty():
    assert len(gate.OUTSIDE_INCLUDE_ALLOW) == 0  # shrink-only


def test_sibling_quoted_include_is_not_outside():
    hdr = {"inputs/reference/ea/profile/internal.h": "#define ts_lock _emit 0xF0\n",
           "game/G/internal.h": "int z;\n"}
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "internal.h"\n' + F("")})) == []


# --- round 1 (VR1A, VR1B) ---
SW = "inputs/reference/shims/sweep/_pch.h"
CL = "// cl: /DNDEBUG /Iinputs/reference/shims/sweep /Iinputs/reference/ea/debug\n"
EAP = {"inputs/reference/ea/profile/_pch.h": '#include "internal.h"\n',
       "inputs/reference/ea/profile/internal.h": "#define ts_lock _emit 0xF0\n"}


def test_h1_outside_flip_to_emit_refused():
    b = {V: "#define OP(x) (x)\n", P: F("\tint a = OP(1);\n")}
    a = {V: "#define OP(x) __asm _emit x\n", P: F("\tint a = OP(1);\n")}
    assert includes(b, a, gate.new_outside_emit_names) == ["OP"]


def test_h1_outside_existing_emit_macro_edit_passes():
    b = {V: "#define OP(x) __asm _emit x\n"}
    a = {V: "#define OP(x) __asm _emit x\n#define Q 1\n"}
    assert includes(b, a, gate.new_outside_emit_names) == []


def test_h2_raw_emit_body_header_refused():
    hdr = {"inputs/vendor/v/b.h": "inline void bb(){ __asm _emit 0x90 }\n"}
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "v/b.h"\n' + F("")})) != []


def test_h2_emit_only_in_string_or_comment_passes():
    hdr = {"inputs/vendor/v/b.h": "// __emit\nconst char *s = \"_emit\"; char c = '\"';\n"}
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "v/b.h"\n' + F("")})) == []


def test_quoted_sibling_shadows_outside_header():
    hdr = dict(EAP, **{"game/G/_pch.h": "int z;\n"})
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "_pch.h"\n' + F("")})) == []


def test_angle_include_does_not_see_sibling():
    hdr = dict(EAP, **{"game/G/_pch.h": "int z;\n"})
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include <_pch.h>\n' + F("")})) != []


def test_cl_include_dir_resolution_new_debug_tu_passes():
    hdr = dict(EAP, **{SW: "int z;\n"})
    q = "game/Libraries/Source/debug/new_tu.cpp"
    assert includes(dict(hdr, **{q: CL + "int a;\n"}),
                    dict(hdr, **{q: CL + '#include "_pch.h"\nint a;\n'})) == []


def test_cl_include_dir_into_emit_dir_refused():
    cl = "// cl: /Iinputs/reference/ea/profile\n"
    q = "game/Libraries/Source/debug/new_tu.cpp"
    assert includes(dict(EAP, **{q: cl + "int a;\n"}),
                    dict(EAP, **{q: cl + '#include "_pch.h"\nint a;\n'})) != []


def test_cl_line_change_rejudges_existing_includes():
    q = "game/Libraries/Source/debug/new_tu.cpp"
    body = '#include "_pch.h"\nint a;\n'
    hdr = dict(EAP, **{SW: "int z;\n"})
    assert includes(dict(hdr, **{q: CL + body}),
                    dict(hdr, **{q: "// cl: /Iinputs/reference/ea/profile\n" + body})) != []


def test_cl_line_change_to_clean_dirs_passes():
    q = "game/Libraries/Source/debug/new_tu.cpp"
    body = '#include "_pch.h"\nint a;\n'
    hdr = dict(EAP, **{SW: "int z;\n"})
    assert includes(dict(hdr, **{q: CL + body}),
                    dict(hdr, **{q: CL.replace("/DNDEBUG", "/DFOO") + body})) == []


def test_normpath_middle_dotdot_refused():
    assert includes(dict(VE, **{P: F("")}), dict(VE, **{P: '#include "v/x/../e.h"\n' + F("")})) != []


def test_normpath_to_clean_file_passes():
    hdr = dict(VE, **{"inputs/vendor/v/c.h": "int c;\n"})
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "v/x/../c.h"\n' + F("")})) == []


def test_case_insensitive_match_refused():
    assert includes(dict(VE, **{P: F("")}), dict(VE, **{P: '#include "V/E.H"\n' + F("")})) != []


def test_case_insensitive_clean_passes():
    hdr = {"inputs/vendor/v/c.h": "int c;\n"}
    assert includes(dict(hdr, **{P: F("")}), dict(hdr, **{P: '#include "V/C.H"\n' + F("")})) == []


def _cache_files(tmp):
    d = Path(tmp) / "build" / "conversion_gate_outside"
    return sorted(d.glob("*.json")) if d.exists() else []


def test_cache_cold_then_warm_same_answer():
    with tempfile.TemporaryDirectory() as tmp:
        git = lambda *a: subprocess.run(["git", "-C", tmp, *a], check=True,
                                        capture_output=True, text=True)
        git("init", "-q")
        (Path(tmp) / "inputs/vendor/v").mkdir(parents=True)
        (Path(tmp) / "inputs/vendor/v/e.h").write_text("#define OP(x) __asm _emit x\n")
        git("add", "-A")
        git("-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "b")
        here = os.getcwd()
        os.chdir(tmp)
        try:
            gate._OUTSIDE.clear()
            cold = gate.outside_state("HEAD")
            assert len(_cache_files(tmp)) == 1
            gate._OUTSIDE.clear()
            calls = []
            real = gate._outside_scan
            gate._outside_scan = lambda rev: calls.append(rev) or real(rev)
            try:
                warm = gate.outside_state("HEAD")
                staged = gate.outside_state(":")  # same outside trees: same key
            finally:
                gate._outside_scan = real
            assert warm == cold == staged and calls == []
            assert warm["names"] == ["OP"]
        finally:
            os.chdir(here)


def test_cache_key_changes_with_outside_tree():
    with tempfile.TemporaryDirectory() as tmp:
        git = lambda *a: subprocess.run(["git", "-C", tmp, *a], check=True,
                                        capture_output=True, text=True)
        git("init", "-q")
        (Path(tmp) / "inputs/vendor/v").mkdir(parents=True)
        (Path(tmp) / "inputs/vendor/v/e.h").write_text("#define OP(x) (x)\n")
        (Path(tmp) / "inputs/reference/shims").mkdir(parents=True)
        (Path(tmp) / "inputs/reference/shims/s.h").write_text("int s;\n")
        git("add", "-A")
        git("-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "b")
        here = os.getcwd()
        os.chdir(tmp)
        try:
            k1 = gate._outside_key("HEAD")
            (Path(tmp) / "inputs/reference/shims/s.h").write_text("int t;\n")
            git("add", "-A")
            assert gate._outside_key(":") == k1  # shims are not outside
            (Path(tmp) / "inputs/vendor/v/e.h").write_text("#define OP(x) __asm _emit x\n")
            git("add", "-A")
            gate._OUTSIDE.clear()
            assert gate._outside_key(":") != k1
            assert gate.outside_state(":")["names"] == ["OP"]
        finally:
            os.chdir(here)
