# BFME-2 evidence applied to ten BFME-1 tasks — 2026-10-15

Donor checkout: `../Open-BFME-2`, revision `5fbd298178ffdb518b9a40a6b5fcc32f489772e4` (read only).
Model: gpt-6.1-sol. Starting BFME-1 checkout: `17c5dd5508`.

Ten selected queue tasks were investigated sequentially. Eight caller repairs
landed in eight commits; two attempts were restored and recorded blocked.

| # | Task / retail RVA | Outcome | Commit |
| --- | --- | --- | --- |
| 1 | DirtySock serial transport / 00819630 | Blocked: worker reference matches bytes but DIR32 ownership retains the generated worker name. Source restored. | Evidence in 94f453a51f |
| 2 | Vector erase / 0082C6E0 | Use existing STLport `__copy_trivial`; LINKS 90 B. | 94f453a51f |
| 3 | Character search / 0082F7C0 | Use existing `bfmeGoOV` with the independently proven pointer-returning ABI; LINKS 120 B. | 63e68aaa56 |
| 4 | Flash-region record copy / 003A6360 | Reference the existing `Rva003B7190Record` vtable provider; LINKS 33 B. | dc84449ae0 |
| 5 | Singleton teardown / 007EB310 | Reference the existing `Rva007EB2C0Object` vtable provider; target LINKS 100 B when existing providers are refreshed. | 3964019549 |
| 6 | BSTR constructor / 00958990 | Blocked: BFME-2 COMDAT change matches 129 B and removes duplicate, but the wrong SDK copy in WebBrowser.obj still wins. Source restored. | Evidence in b4db1bfad3 |
| 7 | Timer update / 00168270 | Call existing `AIPlayer::queueUnits`; LINKS 91 B. | b4db1bfad3 |
| 8 | Timer variant / 00168850 | Same callee repair; retain clamp 15 and reload 10; LINKS 103 B. | 6f9d889887 |
| 9 | Conditional DTK dispatch / 00168610 | Correct 22 B caller; DTL remained the file's sole blocker at this intermediate commit. | f80290a64e |
| 10 | Conditional DTL dispatch / 00168810 | Correct separate 22 B sibling; combined file LINKS 44 B. | This report's commit |

## Evidence and validation

The BFME-2 files `Rva0082C6E0VectorErase.cpp`, `BfmeConv1155.cpp`,
`Bfme/Rva003A6360CopyCtor.cpp`, `Rva007EB310Destroy.cpp`,
`Bstr_t_ctor.cpp`, `BfmeConv780.cpp` and `Rva004EF4C1Pace.cpp` supplied
implementation or provider leads. BFME-1 retail calls, tail branches,
recorded vtable addresses, existing provider sources and exact scoped
builds independently confirmed each landed change.

All eight repaired retail functions pass scoped byte verification. Normal
commit and push hooks ran for every landed commit. Each commit records its
claim lease and the linking check's before/after result; outcome records are
in `targets/game/reverse/re_attempts.log`. All repairs use existing owners and pins.

The seven changed caller TUs account for **581 existing matched bytes** that
now pass linking previews. This is linking progress, with zero new matched
function bytes. The aggregate progress card remains census-derived until
its next refresh. The singleton preview refreshed `createServiceHubImpl.cpp`
and `Rva007EB2C0ObjectDestructor.cpp`; the flag provider retains unrelated
unresolved calls, so only the target's 100 B is credited here.

## Remaining blockers and workspace

- DirtySock: repair the recorded DIR32 ownership through its designated writer;
  no alias workaround was added.
- BSTR: repair the earlier wrong SDK constructor emitter; backporting the
  BFME-2 COMDAT change alone is insufficient.

The terrain recursion and text cursor candidates were inspected and their
claims released during selection; they are outside the ten-task count.
The unrelated scratch directory, pyproject.toml and uv.lock were preserved.
Untracked Ghidra/JDK installations were temporarily parked under build/ so
the publication hook could inspect a clean input tree; they are restored to
their original locations after the final push. No gate was bypassed.
