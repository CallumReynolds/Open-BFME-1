"""owner_queue row 119: DIR32 unowned-name red already on origin/master does not
fail a commit; a new name, or a known name at a new address, still does."""
import io
import sys
import tempfile
from contextlib import redirect_stdout
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import gate_baseline as gb  # noqa: E402

ROW = {"name": "?f@@YAXXZ", "source": "game/f.cpp"}
# Not SubsystemDeleter<AI>: retail 0x01075E20 reaches its matched ??_G, which
# now proves that vtable (dir32_record_guard.function_owner_problem).
OLD = "??_7?$SubsystemDeleter@VNoLedgerOwner@@@@6B@"


def _full_gate(refs, known_text):
    """Run verify_dir32_consistency over refs with known_text as the baseline file;
    return (exit raised, stdout, report text or None)."""
    saved = {k: getattr(build, k) for k in ("ROOT", "DIR32_WHITELIST", "DIR32_UNOWNED_KNOWN",
                                            "dir32_references", "read_dir32_addresses",
                                            "retail_va_span", "dir32_identities",
                                            "load_symbol_map")}
    with tempfile.TemporaryDirectory() as d:
        tmp = Path(d)
        (tmp / "wl.txt").write_text("")
        (tmp / "known.txt").write_text(known_text)
        build.ROOT = tmp
        build.DIR32_WHITELIST = tmp / "wl.txt"
        build.DIR32_UNOWNED_KNOWN = tmp / "known.txt"
        build.dir32_references = lambda rows: iter(refs)
        build.read_dir32_addresses = lambda: {}
        build.retail_va_span = lambda: (0x400000, 0x1416000)
        build.dir32_identities = lambda recorded: ({}, {})
        build.load_symbol_map = lambda: {}
        out, raised = io.StringIO(), False
        try:
            with redirect_stdout(out):
                build.verify_dir32_consistency([ROW], propose=False)
        except SystemExit:
            raised = True
        finally:
            for k, v in saved.items():
                setattr(build, k, v)
        report = tmp / "build" / "dir32_unowned.txt"
        return raised, out.getvalue(), report.read_text() if report.exists() else None


def test_a_known_unowned_reference_passes():
    raised, out, _ = _full_gate([(ROW, 0x10, OLD, 0x01075E20)], gb.UNOWNED_HEADER + f"0x01075E20\t{OLD}\n")
    assert not raised, out


def test_a_new_unowned_name_still_fails_and_is_reported_with_its_base():
    raised, out, report = _full_gate([(ROW, 0x10, OLD, 0x01075E20), (ROW, 0x20, "?g_new@@3HA", 0x01300000)],
                                     f"0x01075E20\t{OLD}\n")
    assert raised and "FAIL 1 unrecorded" in out
    assert report.startswith("0x01300000\t?g_new@@3HA: ")


def test_a_known_name_at_a_different_address_still_fails():
    raised, _, report = _full_gate([(ROW, 0x10, OLD, 0x01075E24)], f"0x01075E20\t{OLD}\n")
    assert raised and report.startswith(f"0x01075E24\t{OLD}")


def test_no_baseline_file_tolerates_nothing():
    raised, _, _ = _full_gate([(ROW, 0x10, OLD, 0x01075E20)], "")
    assert raised


def test_record_text_round_trips_through_the_reader():
    report = f"0x01075E20\t{OLD}: nothing in the ledger owns 0x01075E20. Give\n"
    transcript = ("Functions: OK 5/5\nDIR32 consistency: FAIL 1 unrecorded name(s) no ledger identity backs\n"
                  "FULL GATE: FAIL — 1 red: dir32 consistency\n")
    text = gb.unowned_record_text(transcript, report)
    assert text is not None
    with tempfile.TemporaryDirectory() as d:
        path = Path(d) / "known.txt"
        path.write_text(text)
        assert build.read_dir32_unowned_known(path) == {("0x01075E20", OLD)}


def test_record_refuses_an_unfinished_or_reportless_gate():
    fail = "DIR32 consistency: FAIL 1 unrecorded name(s) no ledger identity backs\n"
    assert gb.unowned_record_text("Functions: OK 5/5\n" + fail, "x") is None          # no verdict
    assert gb.unowned_record_text(fail + "FULL GATE: FAIL — 1 red: dir32 consistency\n", None) is None
    # The other DIR32 failure stops before the unowned half: nothing is proven.
    assert gb.unowned_record_text("DIR32 consistency: FAIL 2 NEW inconsistent symbol(s)\n"
                                  "FULL GATE: FAIL — 1 red: dir32 consistency\n", "") is None
    assert gb.unowned_record_text("DIR32 consistency: OK (5 symbols)\nFULL GATE: OK — every check green\n",
                                  None) == gb.UNOWNED_HEADER
