# 0x00292FA0/84 is FlammableUpdate::calcSleepTime

The ledger split one retail body into two matched rows:

- `?bfmeCalcSleepTimeGate@FlammableUpdate@@QAE?AW4UpdateSleepTime@@XZ` at 0x00292FA0/13
- `?calcSleepTime@FlammableUpdate@@IAE?AW4UpdateSleepTime@@XZ` at 0x00292FAD/71

## One function, not two

`python3 tools/dis_retail.py 0x00292FA0 84`:

- +0x00 `mov al,[ecx+0x40]; test al,al; je +0x0d; mov eax,1; ret`: an early return.
- +0x0d `mov eax,[TheGameLogic]; push esi; mov esi,[eax+0x3c]; ...`: the Zero Hour
  `calcSleepTime` body. It reads the frame and walks the m_aflameEndFrame,
  m_burnedEndFrame and m_damageEndFrame minima at +0x28/+0x2c/+0x30.
- It ends with `ret` at +0x4c and +0x53, and Ghidra lists one function of 84 bytes.

## Callers name the start

- `python3 tools/callers_of.py 0x00292FA0` gives tryToIgnite (0x00293990, through ILT
  0x0003D81B) and update (0x00294410).
- `python3 tools/callers_of.py 0x00292FAD` gives "no named caller reaches it directly".
  The +0x0d entry is only the `je` target of the flag test.

In Zero Hour, FlammableUpdate::tryToIgnite and FlammableUpdate::update both call
calcSleepTime. So retail's calcSleepTime is the whole 84-byte body, with BFME's flag
test in front. The 71-byte row at +0x0d matched only because the Zero Hour body,
compiled against the Zero Hour header, equals that tail.

## Change

- The full body is defined once, as `FlammableUpdate::calcSleepTime` (protected, as the
  Zero Hour declaration is), in FlammableUpdateConstructorThunk.cpp. That file carries
  the BFME layout with the +0x40 byte.
- FlammableUpdate.cpp keeps the Zero Hour layout and no longer defines it.
- FlameStep00294410.cpp calls it by name.
