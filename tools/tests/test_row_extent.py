"""row_extent refuses new rows that start mid-body or swallow int3 padding.

Fixtures are the retail image and Ghidra inventory, as the two retired MASM
rows were in HEAD before fdd547e52f and d7c355102d.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import row_extent

ROOT = Path(__file__).resolve().parents[2]
GHIDRA = ROOT / "targets/game/reverse/ghidra_functions.csv"


@pytest.fixture(scope="module")
def env():
    import build
    try:
        build.read_target_bytes(0x1000, 1)
    except Exception as error:  # the retail image is a per-host input
        pytest.skip(f"retail image unavailable: {error}")
    image, sections = build.exe_image()
    index = row_extent.load_index(GHIDRA, image, sections, build.read_target_bytes,
                                  ROOT / "build/row_extent_index.pkl")
    return row_extent.load_ghidra(GHIDRA), build.read_target_bytes, index


def row(name, rva, size, notes="", status="matched"):
    return {"name": name, "rva": rva, "size": size, "notes": notes,
            "status": status, "source": "game/x.asm"}


def refusals(env, new):
    sizes, read, idx = env
    return row_extent.check([], [new], sizes, read, idx)


def test_handle_request_join_refused(env):
    found = refusals(env, row("?handleRequestJoin@LANAPI@@IAEXPAULANMessage@@I@Z",
                              0x005A565D, 1119))
    assert len(found) == 1
    assert "starts inside Ghidra function 0x005A5650/118" in found[0]


def test_generate_particle_info_refused(env):
    found = refusals(env, row("?generateParticleInfo@ParticleSystem@@IAEPBVParticleInfo@@HH@Z",
                              0x006008AF, 1257))
    assert len(found) == 1
    assert "starts inside Ghidra function 0x00600890/46" in found[0]


def test_span_over_padding_refused_even_at_a_real_start(env):
    # 0x005A5650 is a real start; 1119 B runs over padding into 0x005A56F0.
    found = refusals(env, row("?x@@YAXXZ", 0x005A5650, 0x5A56F0 - 0x5A5650 + 16))
    assert len(found) == 1 and "int3 padding" in found[0]
    assert "0x005A56F0" in found[0]


def test_boundary_aligned_rows_pass(env):
    for rva, size in [(0x005A5650, 118), (0x005A56F0, 481), (0x00600890, 46),
                      (0x006008D0, 178)]:
        assert refusals(env, row("?ok@@YAXXZ", rva, size)) == []


def test_start_inside_matched_row_refused(env):
    sizes, read, idx = env
    host = row("?host@@YAXXZ", 0x005A56F0, 481)
    found = row_extent.check([host], [host, row("?mid@@YAXXZ", 0x005A5700, 16)],
                             {}, read, idx)
    assert len(found) == 1 and "matched row ?host@@YAXXZ" in found[0]


def test_unverified_funclet_notes_do_not_exempt_thunk_does(env):
    assert len(refusals(env, row("?mid@@YAXXZ", 0x005A565D, 1119,
                                 notes="parent=?x@@YAXXZ"))) == 1
    assert len(refusals(env, row("?mid@@YAXXZ", 0x005A565D, 1119,
                                 notes="object-symbol=$L1"))) == 1
    assert refusals(env, row("?j_00001005@@YAXXZ", 0x1005, 5)) == []


def test_existing_rows_not_rejudged(env):
    sizes, read, idx = env
    bad = row("?handleRequestJoin@LANAPI@@IAEXPAULANMessage@@I@Z", 0x005A565D, 1119)
    assert row_extent.check([bad], [bad], sizes, read, idx) == []


def test_moved_row_is_judged(env):
    sizes, read, idx = env
    before = row("?x@@YAXXZ", 0x005A5650, 118)
    after = row("?x@@YAXXZ", 0x005A565D, 1119)
    assert len(row_extent.check([before], [after], sizes, read, idx)) == 1


# Adversarial review round 1 (RE-1..RE-6).

def test_re1_notes_substrings_do_not_exempt(env):
    for notes in ("see grandparent=none", "object-symbol=whatever",
                  "object-symbol=?probe@@YAXXZ"):
        assert len(refusals(env, row("?probe@@YAXXZ", 0x005A565D, 1119, notes=notes))) == 1


def test_re1_compiler_label_alone_does_not_exempt(env):
    assert len(refusals(env, row("?probe@@YAXXZ", 0x005A565D, 1119,
                                 notes="object-symbol=$L1234"))) == 1


def test_re2_only_real_ilt_thunks_exempt(env):
    assert len(refusals(env, row("?j_probe@@YAXXZ", 0x005A565D, 1119))) == 1
    assert len(refusals(env, row("?j_005A5650@@YAXXZ", 0x005A5650,
                                 0x5A56F0 - 0x5A5650 + 16))) == 1
    sizes, read, idx = env
    assert read(0x1005, 1) == b"\xe9"
    assert refusals(env, row("?j_00001005@@YAXXZ", 0x1005, 5)) == []


def test_re3_status_or_note_flip_is_rejudged(env):
    sizes, read, idx = env
    parked = row("?probe@@YAXXZ", 0x005A565D, 1119, notes="parent=?x@@YAXXZ",
                 status="unmatched")
    live = row("?probe@@YAXXZ", 0x005A565D, 1119)
    assert len(row_extent.check([parked], [live], sizes, read, idx)) == 1
    renamed = row("?probe@@YAXXZ", 0x005A565D, 1119, notes="parent=?y@@YAXXZ")
    assert len(row_extent.check([parked], [renamed], sizes, read, idx)) == 1


def test_re4_split_after_internal_ret_refused(env):
    # 0x0005B7F0 follows an internal ret inside Ghidra 0x0005B7A0/87.
    found = refusals(env, row("?tail@@YAXXZ", 0x0005B7F0, 7))
    assert len(found) == 1 and "0x0005B7A0" in found[0]
    # A C3 byte that is an operand (mov al, bl) is no boundary either.
    assert len(refusals(env, row("?mid@@YAXXZ", 0x00232265, 11))) == 1


def test_re5_catch_funclet_merged_by_ghidra_passes(env):
    # mov eax, <continuation in 0x00718B70>; ret
    assert refusals(env, row("?Rva00718D05CatchForward@@YAPAXXZ", 0x00718D05, 17)) == []


def test_re6_unmapped_rva_refused_not_crash(env):
    found = refusals(env, row("?probe@@YAXXZ", 0x02000000, 16))
    assert len(found) == 1 and "cannot read the retail image" in found[0]


def test_re6_missing_image_refused_not_crash():
    def read(rva, count):
        raise FileNotFoundError("no exe")
    found = row_extent.check([], [row("?probe@@YAXXZ", 0x005A5650, 118)], {}, read)
    assert len(found) == 1 and "no exe" in found[0]


def test_span_over_matched_row_refused(env):
    sizes, read, idx = env
    host = row("?next@@YAXXZ", 0x005A56F0, 481)
    found = row_extent.check([host], [host, row("?wide@@YAXXZ", 0x005A5650, 0xA4)],
                             {}, read, idx)
    assert len(found) == 1 and "0x005A56F0" in found[0]


# Adversarial review round 2: exemptions are verified, not trusted by value.

JOIN = 0x005A565D


@pytest.mark.parametrize("notes", ["parent=nonexistent", "masm;parent=a",
                                   "object-symbol=$LN9", "ghidra=Catch@0",
                                   "ghidra=Catch@009A565D"])
def test_r2_forged_exemptions_refused(env, notes):
    assert len(refusals(env, row("?x@@YAXXZ", JOIN, 1119, notes=notes))) == 1


def test_r2_real_parent_but_not_enclosing_refused(env):
    sizes, read, idx = env
    parent = row("?load@INI@@QAE_NVBFMERetailAsciiString@@00HH@Z", 0x00853B30, 250)
    bad = row("?x@@YAXXZ", JOIN, 1119, notes=f"parent={parent['name']}")
    assert len(row_extent.check([parent], [parent, bad], sizes, read, idx)) == 1


def test_r2_verified_funclet_inside_parent_passes(env):
    # Real row: $L414 cleanup Ghidra merged into ?load@INI, right after its ret 14h.
    sizes, read, idx = env
    parent = row("?load@INI@@QAE_NVBFMERetailAsciiString@@00HH@Z", 0x00853B30, 250)
    funclet = row("?dup_00853C2A@@YAXXZ", 0x00853C2A, 17,
                  notes=f"object-symbol=$L414;parent={parent['name']}")
    assert row_extent.check([parent], [parent, funclet], sizes, read, idx) == []
    plain = row("?dup_00853C2A@@YAXXZ", 0x00853C2A, 17, notes="object-symbol=$L414")
    assert len(row_extent.check([parent], [parent, plain], sizes, read, idx)) == 1


def test_catch_note_no_longer_self_certifies(env):
    # A rethrowing catch (no `mov eax, <va>; ret`) needs its parent= now.
    sizes, read, idx = env
    note = row("?d_0035d611@@YAXXZ", 0x0035D611, 21, notes="gen-dump;ghidra=Catch@0075d611")
    assert len(refusals(env, note)) == 1
    parent = row("?Rva0035D460@@YAXPAURva00359530Record@@PBU1@@Z", 0x0035D460, 433)
    child = {**note, "notes": f"ghidra=Catch@0075d611;parent={parent['name']}"}
    assert row_extent.check([parent], [parent, child], sizes, read, idx) == []


@pytest.mark.parametrize("rva,size", [(0x000BB313, 137), (0x001843A3, 281),
                                      (0x004889A3, 110)])
def test_r2_catch_shape_three_bytes_in_refused(env, rva, size):
    assert len(refusals(env, row("?x@@YAXXZ", rva, size))) == 1


# Synthetic image: each rule alone decides the case (mutation coverage).

def image(data, base=0x1000):
    def read(rva, count):
        if not base <= rva < base + len(data):
            raise ValueError(f"RVA 0x{rva:08X} is outside all PE sections")
        return data[rva - base:rva - base + count]
    return read


def judge(data, ghidra, new):
    return row_extent.check([], [new], ghidra, image(data))


def test_r2_branch_target_refused():
    # je 1005; ret; int3 int3 | 1005: nop; ret  -- padded, but a branch target
    data = bytes.fromhex("7403C3CCCC90C3")
    found = judge(data, {0x1000: 7}, row("?x@@YAXXZ", 0x1005, 2))
    assert len(found) == 1 and "branch target" in found[0]


def test_r2_three_int3_after_noreturn_call_passes():
    # call; int3 x3 | 1008: push ebp; ret
    data = bytes.fromhex("E800000000CCCCCC55C3")
    assert judge(data, {0x1000: 10}, row("?x@@YAXXZ", 0x1008, 2)) == []
    two = bytes.fromhex("E800000000CCCC55C3")
    assert len(judge(two, {0x1000: 9}, row("?x@@YAXXZ", 0x1007, 2))) == 1


def test_r2_split_after_ret_without_padding_refused():
    data = bytes.fromhex("90C355C3")
    found = judge(data, {0x1000: 4}, row("?x@@YAXXZ", 0x1002, 2))
    assert len(found) == 1 and "split body" in found[0]


def test_r2_catch_shape_target_must_be_in_parent():
    # jmp 1008; | 1002: mov eax, <va>; ret | 1008: ret
    inside = bytes.fromhex("EB06B808104000C3C3")
    outside = bytes.fromhex("EB06B808204000C3C3")
    new = row("?x@@YAXXZ", 0x1002, 6)
    assert judge(inside, {0x1000: 9}, new) == []
    assert len(judge(outside, {0x1000: 9}, new)) == 1


def test_r2_catch_shape_must_end_at_its_ret():
    # jmp 100A | 1002: ret; nop; mov eax, <va>; ret | 100A: ret -- earlier ret
    data = bytes.fromhex("EB08C390B80A104000C3C3")
    assert len(judge(data, {0x1000: 11}, row("?x@@YAXXZ", 0x1002, 8))) == 1


def test_r2_ilt_thunk_needs_e9():
    nops = bytes.fromhex("90" * 16)
    new = row("?j_00001004@@YAXXZ", 0x1004, 5)
    assert len(judge(nops, {0x1000: 16}, new)) == 1
    thunk = nops[:4] + bytes.fromhex("E900000000") + nops[9:]
    assert judge(thunk, {0x1000: 16}, new) == []


def test_r2_past_section_end_refused():
    found = judge(bytes(16), {}, row("?x@@YAXXZ", 0x1008, 16))
    assert len(found) == 1 and "past the end" in found[0]


def test_r2_parent_must_name_the_enclosing_row():
    # 1000: nop; ret | 1002: push ebp; ret -- a split unless a real parent waives it
    data = bytes.fromhex("90C355C3") + bytes.fromhex("90" * 0x100) + bytes.fromhex("C3")
    host = row("?h@@YAXXZ", 0x1000, 4)
    other = row("?p@@YAXXZ", 0x1104, 1)
    read = image(data)
    for notes, refused in (("parent=?h@@YAXXZ", 0), ("parent=?nope@@YAXXZ", 1),
                           ("parent=?p@@YAXXZ", 1)):
        new = row("?f@@YAXXZ", 0x1002, 2, notes=notes)
        found = row_extent.check([host, other], [host, other, new], {0x1000: 4}, read)
        assert len(found) == refused, notes


def test_r2_catch_shape_jmp_out_refused():
    # jmp 100B | 1002: jmp <inside|outside>; nop; mov eax, <va>; ret | 100B..: nops
    def body(dest):
        return (bytes.fromhex("EB09") + bytes([0xEB, dest - 0x1004])
                + bytes.fromhex("90B80B104000C3") + bytes.fromhex("90" * 0x20))
    new = row("?x@@YAXXZ", 0x1002, 9)
    assert judge(body(0x1004), {0x1000: 0x2B}, new) == []
    assert len(judge(body(0x1020), {0x1000: 0x2B}, new)) == 1


def test_r2_catch_shape_needs_plain_ret():
    # jmp 100A | 1002: mov eax, <va>; ret 4 | 100A: ret
    data = bytes.fromhex("EB08B80A104000C20400C3")
    assert len(judge(data, {0x1000: 11}, row("?x@@YAXXZ", 0x1002, 8))) == 1


# 2026-10-14 rule set (review rowcheck RC2A/RC2B).

def test_h2_labelled_row_is_a_known_body(env):
    sizes, read, idx = env
    host = row("?Rva00C6AFE0Init@@YAXXZ", 0x00C6AFE0, 36, notes="object-symbol=_$E1")
    forged = row("?x@@YAXXZ", 0x00C6AFF8, 12)
    found = row_extent.check([host], [host, forged], sizes, read, idx)
    assert len(found) == 1 and "matched row ?Rva00C6AFE0Init" in found[0]


def test_h2_run_over_labelled_rows_refused(env):
    sizes, read, idx = env
    rows = [row("uw_00c55cd5", 0x00C55CD5, 10, notes="object-symbol=__ehhandler$x")]
    forged = row("?x@@YAXXZ", 0x00C55CCA, 53)
    found = row_extent.check(rows, rows + [forged], sizes, read, idx)
    assert len(found) == 1 and "runs over" in found[0]


def test_h2_verified_child_inside_matched_row():
    # 1000: nop; ret | 1002: push ebp; ret  -- a row nested in a matched row
    read = image(bytes.fromhex("90C355C3"))
    host = row("?h@@YAXXZ", 0x1000, 4)
    for notes, refused in (("parent=?h@@YAXXZ", 0), ("object-symbol=$L1", 1),
                           ("ghidra=Catch@00401002", 1), ("parent=?other@@YAXXZ", 1)):
        child = row("?f@@YAXXZ", 0x1002, 2, notes=notes)
        assert len(row_extent.check([host], [host, child], {}, read)) == refused, notes
        # and the parent re-landed over its verified child
        moved = {**host, "size": 4, "notes": "x"}
        found = row_extent.check([child], [moved, child], {}, read)
        assert len(found) == refused, notes


def test_q1_aligned_padding_then_code_refused():
    # 1000: ret; int3 x15 | 1010: ret  -- the run ends at aligned 0x1010
    data = bytes.fromhex("C3" + "CC" * 15 + "C3")
    found = judge(data, {}, row("?x@@YAXXZ", 0x1000, 17))
    assert len(found) == 1 and "16-byte aligned" in found[0]
    # padding at the row's end, or an unaligned operand run, passes
    assert judge(data, {}, row("?x@@YAXXZ", 0x1000, 16)) == []
    operand = bytes.fromhex("B8CCCCCC00C3")  # mov eax, 0x00CCCCCC; ret
    assert judge(operand, {}, row("?x@@YAXXZ", 0x1000, 6)) == []


def test_q1_tryToRecruit_refused(env):
    assert len(refusals(env, row("?x@@YAXXZ", 0x0076E90A, 568))) == 1


def test_q2_unpadded_prologue_refused():
    # 1000: ret | 1001: push ebp; mov ebp, esp; ret; a known start at 1001
    data = bytes.fromhex("C3558BECC3")
    found = judge(data, {0x1001: 4}, row("?x@@YAXXZ", 0x1000, 5))
    assert len(found) == 1 and "prologue" in found[0]
    # not a known start, no prologue, or a branch target: passes
    assert judge(data, {}, row("?x@@YAXXZ", 0x1000, 5)) == []
    assert judge(bytes.fromhex("C3908BECC3"), {0x1001: 4}, row("?x@@YAXXZ", 0x1000, 5)) == []
    branched = bytes.fromhex("7401C3558BECC3")  # je 1003 | ret | 1003: push ebp...
    assert judge(branched, {0x1003: 4}, row("?x@@YAXXZ", 0x1000, 7)) == []


def test_q2_catch_continuation_passes():
    # 1000: ret | 1001: push ebp; mov ebp,esp; ret | 1005: mov eax, 0x401001; ret
    data = bytes.fromhex("C3558BECC3B801104000C3")
    assert judge(data, {0x1001: 4, 0x1005: 6}, row("?x@@YAXXZ", 0x1000, 5)) == []
    other = bytes.fromhex("C3558BECC3B802104000C3")
    assert len(judge(other, {0x1001: 4, 0x1005: 6}, row("?x@@YAXXZ", 0x1000, 5))) == 1


def test_q2_d3dx_refused(env):
    found = refusals(env, row("_D3DXVec4Transform@12", 0x009FAA48, 600))
    assert len(found) == 1 and "0x009FAAED" in found[0]


def test_q3_called_start_inside_ghidra_body_passes():
    # Ghidra merges 1000..1008; 1002 follows a ret with no padding but is called
    # from the body at 1010.  A jmp from another body does not count.
    called = bytes.fromhex("90C3558BEC5DC390" + "90" * 8 + "E8EDFFFFFFC3")
    assert judge(called, {0x1000: 8, 0x1010: 6}, row("?x@@YAXXZ", 0x1002, 5)) == []
    jumped = bytes.fromhex("90C3558BEC5DC390" + "90" * 8 + "E9EDFFFFFFC3")
    assert len(judge(jumped, {0x1000: 8, 0x1010: 6}, row("?x@@YAXXZ", 0x1002, 5))) == 1
    # a call from the enclosing body itself does not count either
    self_call = bytes.fromhex("90C3558BEC5DC3E8F6FFFFFF")
    assert len(judge(self_call, {0x1000: 12}, row("?x@@YAXXZ", 0x1002, 5))) == 1


def test_q3_ilt_target_passes_but_not_inside_matched_row():
    data = bytes.fromhex("90C3558BEC5DC390" + "90" * 8 + "E9EDFFFFFF")
    ghidra = {0x1000: 8, 0x1010: 5}
    assert judge(data, ghidra, row("?x@@YAXXZ", 0x1002, 5)) == []
    host = row("?h@@YAXXZ", 0x1000, 8)
    found = row_extent.check([host], [host, row("?x@@YAXXZ", 0x1002, 5)], ghidra, image(data))
    assert len(found) == 1


def test_q3_heapsort_passes(env):
    assert refusals(env, row("?x@@YAXXZ", 0x00A6C125, 53)) == []


def test_index_cache_keyed_on_inputs(tmp_path):
    ghidra = tmp_path / "g.csv"
    ghidra.write_text("rva,size\n0x1000,5\n")
    data = bytes.fromhex("E9FB0F0000")
    read = image(data)
    sections = []
    cache = tmp_path / "idx.pkl"
    first = row_extent.load_index(ghidra, data, sections, read, cache)
    assert first.ilt == {0x2000} and cache.exists()
    second = row_extent.load_index(ghidra, data, sections, read, cache)
    assert second.ilt == {0x2000}
    ghidra.write_text("rva,size\n")
    assert row_extent.load_index(ghidra, data, sections, read, cache).ilt == set()
