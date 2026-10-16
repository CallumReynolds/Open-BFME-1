# 0x0014EC80 / 0x0014EF00: AIDock MoveToDock and MoveToExit onEnter were swapped

The ledger had `?onEnter@AIDockMoveToExitState` at 0x0014EC80 and
`?onEnter@AIDockMoveToDockState` at 0x0014EF00. Both are reversed.

Retail bytes (lotrbfme.exe):

| ctor | pushes literal | installs vtable | slot 4 (onEnter) | slot 5 | slot 6 (update) |
|------|----------------|-----------------|------------------|--------|-----------------|
| 0x0014F590 | 0x01095D90 `AIDockMoveToDockState` | 0x01095D38 | 0x0014EC80 | 0x0014EDC0 | 0x0014ED60 |
| 0x0014F690 | 0x01095E80 `AIDockMoveToExitState` | 0x01095E28 | 0x0014EF00 | 0x0014F010 | 0x0014EFC0 |

0x0014ED60 is the matched `AIDockMoveToDockState::update` (same table as
0x0014EC80).

Body shape agrees with Zero Hour: `AIDockMoveToDockState::onEnter` has the
`isDockOpen()` guard with `cancelDock`, and locks the machine; this is the
175-byte 0x0014EC80 body. `AIDockMoveToExitState::onEnter` has neither; this
is the 145-byte 0x0014EF00 body. `ea_evidence.csv` already records
0x0014EC80 = `AIDockMoveToDockState::onEnter` (chain+direct+wb1, strong).

The DockUpdateInterface header orders getEnterPosition +0x14, getDockPosition
+0x18, getExitPosition +0x1C (the matched MoveToDock::update calls +0x18
through it); 0x0014EC80 calls +0x18 and 0x0014EF00 calls +0x1C. AIDock.cpp's
local BFMERetailDockVTable view had +0x18/+0x1C swapped to fit the swapped
names; the source swap corrects it with unchanged bytes.

`tools/ilt_oracle.py check` reports CONFIRMED (exact) for both corrected
names at their addresses.

Fix: the two functions.csv rows exchange names, AIDock.cpp exchanges the two
bodies' classes and the two view slot names (bytes unchanged), and the two
ilt_contradicted_baseline.txt lines the old names caused are removed.
Approved by the project lead 2026-10-15.
