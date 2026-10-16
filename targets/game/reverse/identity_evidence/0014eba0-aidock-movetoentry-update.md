# 0x0014EBA0 is AIDockMoveToEntryState::update

The 59-byte row at 0x0014EBA0 was `?bfmeGoCKE@BfmeThingCKE@@QAEHXZ`, an
anonymous conversion in BfmeConv617.cpp.

- The constructor at 0x0014F510 pushes the literal `AIDockMoveToEntryState`
  (VA 0x01095D18) to its State base and installs vtable VA 0x01095CC0.
- Slot 4 of 0x01095CC0 reaches 0x0014EAE0, the matched
  `AIDockMoveToEntryState::onEnter`; slot 5 reaches 0x0014EBF0, the matched
  `AIDockMoveToEntryState::onExit`; slot 6 (+0x18), the State `update` slot
  (the same slot `AIDockMoveToDockState::update` 0x0014ED60 holds in its own
  table 0x01095D38), holds VA 0x004187CD, the ILT entry 0x000187CD whose
  `jmp` reaches 0x0014EBA0.
- The body is the Zero Hour `AIDockMoveToEntryState::update` shape plus a
  BFME refresh: it reads the machine's goal object, takes its dock interface,
  fails with STATE_FAILURE when either is null, calls dock slot +0x14
  (`getEnterPosition`, the same slot the matched onEnter uses) with the
  machine owner and `&m_goalPosition` (+0x24), and tail-jumps to
  `AIInternalMoveToState::update`.
- `python3 tools/ilt_oracle.py check '?update@AIDockMoveToEntryState@@UAE?AW4StateReturnType@@XZ' 0x0014EBA0`
  reports CONFIRMED (exact).

The ZH-shaped body AIDock.cpp carried as present-unmatched is replaced by
the retail body; byte gate EXACT at 59 bytes.
