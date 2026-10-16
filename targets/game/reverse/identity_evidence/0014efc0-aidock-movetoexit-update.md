# 0x0014EFC0 is AIDockMoveToExitState::update

The 59-byte row at 0x0014EFC0 was `?bfmeGoCKF@BfmeThingCKF@@QAEHXZ`, an
anonymous conversion in BfmeConv618.cpp.

- The constructor at 0x0014F690 pushes the literal `AIDockMoveToExitState`
  (VA 0x01095E80) to its State base and installs vtable VA 0x01095E28
  (retail bytes read from lotrbfme.exe).
- Slots of 0x01095E28 (through their ILT jumps): 4 -> 0x0014EF00
  (`AIDockMoveToExitState::onEnter`, see
  `0014ec80-0014ef00-aidock-onenter-swap.md`), 5 -> 0x0014F010, 6 (+0x18,
  the State `update` slot) -> 0x0014EFC0 (via ILT 0x000152F8). The sibling
  tables use the same slot for `update`: 0x01095CC0 slot 6 -> 0x0014EBA0
  (`AIDockMoveToEntryState::update`) and 0x01095D38 slot 6 -> 0x0014ED60
  (matched `AIDockMoveToDockState::update`).
- The body is the Zero Hour `AIDockMoveToExitState::update` shape plus the
  BFME per-frame refresh its MoveToEntry/MoveToDock siblings carry: it reads
  the machine's goal object (`this+0x1C`), takes its dock interface, returns
  STATE_FAILURE (-2) when either is null, calls dock slot +0x1C
  (`getExitPosition` in DockUpdateInterface: +0x14 enter, +0x18 dock, +0x1C
  exit) with the machine owner (`machine+0x10`) and `&m_goalPosition`
  (+0x24), and tail-jumps to `AIInternalMoveToState::update`.
- `python3 tools/ilt_oracle.py check '?update@AIDockMoveToExitState@@UAE?AW4StateReturnType@@XZ' 0x0014EFC0`
  reports CONFIRMED (exact).

The ZH-shaped body AIDock.cpp carried as present-unmatched is replaced by the
retail body; byte gate EXACT at 59 bytes. Approved by the project lead
2026-10-15.
