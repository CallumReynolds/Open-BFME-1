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
PH = "game/G/a.h"  # a header: no `// cl:` line, so the suffix fallback
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
                if text is None:
                    full.unlink(missing_ok=True)
                    continue
                full.parent.mkdir(parents=True, exist_ok=True)
                full.write_text(text)
            git("add", "-A", "--", ".", ":(exclude)build")
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
    assert includes(dict(VE, **{PH: F("")}), dict(VE, **{PH: '#include "v/e.h"\n' + F("")})) != []


def test_added_include_of_vendor_clean_header_passes():
    hdr = {V: "#define OP(x) (x)\n#define S \"__emit\"\n"}
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include "v/e.h"\n' + F("")})) == []


def test_transitive_include_through_vendor_header_refused():
    hdr = dict(VE, **{V2: '#include "e.h"\n#define W 1\n'})
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include "wrap.h"\n' + F("")})) != []


def test_transitive_include_of_clean_vendor_headers_passes():
    hdr = {V: "#define OP(x) (x)\n", V2: '#include "e.h"\n#define W 1\n'}
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include "wrap.h"\n' + F("")})) == []


def test_moved_include_passes():
    b = dict(VE, **{PH: '#include "v/e.h"\nint a;\n' + F("")})
    a = dict(VE, **{PH: 'int a;\n#include "v/e.h"\n' + F("")})
    assert includes(b, a) == []


def test_shims_file_added_include_refused():
    s = "inputs/reference/shims/x/s.h"
    assert includes(dict(VE, **{s: "int a;\n"}), dict(VE, **{s: '#include "v/e.h"\nint a;\n'})) != []


def test_game_header_of_same_name_is_not_outside():
    hdr = {"game/G/e.h": "#define OP(x) __emit x\n"}
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include "e.h"\n' + F("")})) == []


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
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include "internal.h"\n' + F("")})) == []


# --- round 1 (VR1A, VR1B) ---
SW = "inputs/reference/shims/sweep/_pch.h"
CL = "// cl: /DNDEBUG /Iinputs/reference/shims/sweep /Iinputs/reference/ea/debug\n"
EAP = {"inputs/reference/ea/profile/_pch.h": '#include "internal.h"\n',
       "inputs/reference/ea/profile/internal.h": "#define ts_lock _emit 0xF0\n"}


CLV = "// cl: /Iinputs/vendor\n"


def test_a5_macro_flip_of_reached_file_refused():
    use = {P: CLV + '#include "v/e.h"\n' + F("\tint a = OP(1);\n")}
    assert includes(dict(use, **{V: "#define OP(x) (x)\n"}),
                    dict(use, **{V: "#define OP(x) __asm _emit x\n"}), gate.reach_growth) == [V]


def test_a5_unreachable_vendor_emit_import_passes():
    use = {P: CLV + '#include "v/c.h"\n' + F("")}
    assert includes(dict(use, **{"inputs/vendor/v/c.h": "int c;\n"}),
                    dict(use, **{"inputs/vendor/v/c.h": "int c;\n",
                                 "inputs/vendor/x/x.h": "#define EMITX __asm _emit 0x90\n"}),
                    gate.reach_growth) == []


def test_a5_raw_body_flip_refused():
    use = {P: CLV + '#include "v/b.h"\n' + F("\tbb();\n")}
    b = "inputs/vendor/v/b.h"
    assert includes(dict(use, **{b: "inline void bb(){}\n"}),
                    dict(use, **{b: "inline void bb(){ __asm _emit 0x90 }\n"}),
                    gate.reach_growth) == [b]


def test_a5_raw_body_edit_without_emit_passes():
    use = {P: CLV + '#include "v/b.h"\n' + F("\tbb();\n")}
    b = "inputs/vendor/v/b.h"
    assert includes(dict(use, **{b: "inline void bb(){}\n"}),
                    dict(use, **{b: "inline void bb(){ int z = 0; }\n"}),
                    gate.reach_growth) == []


def test_a5_reach_grows_behind_existing_include_refused():
    use = {P: CLV + '#include "v/w.h"\n' + F(""), "inputs/vendor/o/e.h": "inline void e(){ __asm _emit 0x90 }\n"}
    w = "inputs/vendor/v/w.h"
    assert includes(dict(use, **{w: "int w;\n"}), dict(use, **{w: '#include "../o/e.h"\nint w;\n'}),
                    gate.reach_growth) == ["inputs/vendor/o/e.h"]


def test_a5_existing_include_gains_clean_include_passes():
    use = {P: CLV + '#include "v/w.h"\n' + F(""), "inputs/vendor/o/c.h": "int c;\n"}
    w = "inputs/vendor/v/w.h"
    assert includes(dict(use, **{w: "int w;\n"}), dict(use, **{w: '#include "../o/c.h"\nint w;\n'}),
                    gate.reach_growth) == []


def test_a5_emit_file_moved_into_reach_refused():
    use = {P: CLV + '#include "v/w.h"\n' + F("")}
    e = "inline void e(){ __asm _emit 0x90 }\n"
    b = dict(use, **{"inputs/vendor/v/w.h": "int w;\n", "inputs/vendor/o/e.h": e})
    a = dict(use, **{"inputs/vendor/v/w.h": '#include "e2.h"\nint w;\n', "inputs/vendor/v/e2.h": e})
    a["inputs/vendor/o/e.h"] = None
    assert includes(b, a, gate.reach_growth) == ["inputs/vendor/v/e2.h"]


def test_a5_clean_file_moved_into_reach_passes():
    use = {P: CLV + '#include "v/w.h"\n' + F("")}
    b = dict(use, **{"inputs/vendor/v/w.h": "int w;\n", "inputs/vendor/o/c.h": "int c;\n"})
    a = dict(use, **{"inputs/vendor/v/w.h": '#include "c2.h"\nint w;\n', "inputs/vendor/v/c2.h": "int c;\n"})
    a["inputs/vendor/o/c.h"] = None
    assert includes(b, a, gate.reach_growth) == []


def test_h2_raw_emit_body_header_refused():
    hdr = {"inputs/vendor/v/b.h": "inline void bb(){ __asm _emit 0x90 }\n"}
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include "v/b.h"\n' + F("")})) != []


def test_h2_emit_only_in_string_or_comment_passes():
    hdr = {"inputs/vendor/v/b.h": "// __emit\nconst char *s = \"_emit\"; char c = '\"';\n"}
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include "v/b.h"\n' + F("")})) == []


def test_quoted_sibling_shadows_outside_header():
    hdr = dict(EAP, **{"game/G/_pch.h": "int z;\n"})
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include "_pch.h"\n' + F("")})) == []


def test_angle_include_does_not_see_sibling():
    hdr = dict(EAP, **{"game/G/_pch.h": "int z;\n"})
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include <_pch.h>\n' + F("")})) != []


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
    assert includes(dict(VE, **{PH: F("")}), dict(VE, **{PH: '#include "v/x/../e.h"\n' + F("")})) != []


def test_normpath_to_clean_file_passes():
    hdr = dict(VE, **{"inputs/vendor/v/c.h": "int c;\n"})
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include "v/x/../c.h"\n' + F("")})) == []


def test_case_insensitive_match_refused():
    assert includes(dict(VE, **{PH: F("")}), dict(VE, **{PH: '#include "V/E.H"\n' + F("")})) != []


def test_case_insensitive_clean_passes():
    hdr = {"inputs/vendor/v/c.h": "int c;\n"}
    assert includes(dict(hdr, **{PH: F("")}), dict(hdr, **{PH: '#include "V/C.H"\n' + F("")})) == []


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


# --- round 2 (VR2A, VR2B) ---
STL = {"inputs/vendor/stlport/evil.h": "inline void ev(){ __asm _emit 0x90 }\n",
       "inputs/vendor/stlport/list": "x\n"}


def test_stlport_include_dir_reaches_vendor_emit_refused():
    q = "game/G/s.cpp"
    head = "// cl: /DNDEBUG\n// stlport\n"
    assert includes(dict(STL, **{q: head + "int a;\n"}),
                    dict(STL, **{q: head + "#include <evil.h>\nint a;\n"})) != []


def test_non_stlport_tu_does_not_search_stlport_passes():
    q = "game/G/s.cpp"
    head = "// cl: /DNDEBUG\n"
    assert includes(dict(STL, **{q: head + "int a;\n"}),
                    dict(STL, **{q: head + "#include <evil.h>\nint a;\n"})) == []


def test_added_stlport_line_rejudges_includes_refused():
    q = "game/G/s.cpp"
    body = "#include <evil.h>\nint a;\n"
    assert includes(dict(STL, **{q: "// cl: /DNDEBUG\n" + body}),
                    dict(STL, **{q: "// cl: /DNDEBUG\n// stlport\n" + body})) != []


def test_cl_less_cpp_uses_default_dirs_not_suffix_passes():
    assert includes(dict(VE, **{P: F("")}), dict(VE, **{P: '#include "e.h"\n' + F("")})) == []


def test_cl_less_header_keeps_suffix_fallback_refused():
    assert includes(dict(VE, **{PH: F("")}), dict(VE, **{PH: '#include "e.h"\n' + F("")})) != []


def test_forced_include_of_emit_file_refused():
    q = "game/G/f.cpp"
    assert includes(dict(VE, **{q: "// cl: /DNDEBUG\nint a;\n"}),
                    dict(VE, **{q: "// cl: /DNDEBUG /FIinputs/vendor/v/e.h\nint a;\n"})) != []


def test_forced_include_of_clean_file_passes():
    hdr = {"inputs/vendor/v/c.h": "int c;\n"}
    q = "game/G/f.cpp"
    assert includes(dict(hdr, **{q: "// cl: /DNDEBUG\nint a;\n"}),
                    dict(hdr, **{q: "// cl: /DNDEBUG /FI inputs/vendor/v/c.h\nint a;\n"})) == []


def test_cl_edit_does_not_blame_reach_that_existed_before():
    q = "game/G/f.cpp"
    body = '#include "v/e.h"\nint a;\n'
    assert includes(dict(VE, **{q: "// cl: /Iinputs/vendor\n" + body}),
                    dict(VE, **{q: "// cl: /Iinputs/vendor /Oy-\n" + body})) == []


def _cache_repo(tmp):
    git = lambda *a: subprocess.run(["git", "-C", tmp, *a], check=True,
                                    capture_output=True, text=True)
    git("init", "-q")
    (Path(tmp) / "inputs/vendor/v").mkdir(parents=True)
    (Path(tmp) / "inputs/vendor/v/e.h").write_text("#define OP(x) __asm _emit x\n")
    git("add", "-A")
    git("-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "b")


import pytest  # noqa: E402


@pytest.mark.parametrize("poison", ["{}", "[]", "null", "garbage{",
                                    '{"defs": "", "names": [], "seeds": [], "reach": {}}',
                                    '{"defs": 1, "names": "OP", "seeds": ["x"], "reach": []}'])
def test_corrupt_or_wrong_shape_cache_is_recomputed(poison):
    with tempfile.TemporaryDirectory() as tmp:
        _cache_repo(tmp)
        here = os.getcwd()
        os.chdir(tmp)
        try:
            gate._OUTSIDE.clear()
            key = gate._outside_key("HEAD")
            d = Path("build/conversion_gate_outside")
            d.mkdir(parents=True)
            (d / (key + ".json")).write_text(poison)
            state = gate.outside_state("HEAD")
            assert state["names"] == ["OP"] and state["seeds"] == ["inputs/vendor/v/e.h"]
        finally:
            os.chdir(here)


def test_stale_code_hash_changes_the_key():
    with tempfile.TemporaryDirectory() as tmp:
        _cache_repo(tmp)
        here = os.getcwd()
        os.chdir(tmp)
        real = gate._GATE_HASH
        try:
            k1 = gate._outside_key("HEAD")
            gate._GATE_HASH = "0" * 40
            assert gate._outside_key("HEAD") != k1
        finally:
            gate._GATE_HASH = real
            os.chdir(here)


def _work(before, after):
    return includes(before, after,
                    lambda o, n: gate.outside_work(o, n, gate.collect_diff_lines(o, n)))


def test_skip_path_plain_game_edit_runs_nothing():
    assert _work(dict(VE, **{P: F("")}), dict(VE, **{P: F("\tint a;\n")})) == (False, False)


def test_skip_path_include_edit_runs_a3():
    assert _work(dict(VE, **{P: F("")}), dict(VE, **{P: '#include "x.h"\n' + F("")}))[0] is True


def test_skip_path_vendor_edit_runs_a5():
    assert _work(dict(VE, **{P: F("")}), {V: "#define OP(x) (x)\n", P: F("")}) == (False, True)


def test_skip_path_game_delete_runs_a5():
    b = dict(VE, **{P: F(""), "game/G/b.h": "int b;\n"})
    a = dict(VE, **{P: F(""), "game/G/b.h": None})
    assert _work(b, a) == (False, True)


def test_a5_deleted_sibling_sends_include_outside_refused():
    q = "game/G/f.cpp"
    use = dict(EAP, **{q: "// cl: /Iinputs/reference/ea/profile\n#include \"_pch.h\"\nint a;\n"})
    b = dict(use, **{"game/G/_pch.h": "int z;\n"})
    a = dict(use, **{"game/G/_pch.h": None})
    assert includes(b, a, gate.reach_growth) == ["inputs/reference/ea/profile/internal.h"]
