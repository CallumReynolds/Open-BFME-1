# 0x0075BE60: Rva001C86B0Object is a callee ABI view, not a rename of Object

The 143-byte body at `0x0075BE60` (RET 8 at +0x8C, INT3 at +0x8F) landed in
`W3DModelDraw.cpp` under address names (`Rva0075BE60::rva0075BE60`); its owner
and method identity are unproven.

The bank `targets/game/reverse/attempts/0x0075be60.cpp` declared a TU-local
`class Object` carrying `getControllingPlayer()` and an aggregate-return
`Rva0075BE60Position bfmeGetPosition421AE(Coord3D *)`. In the landed source:

- the real `Object` (from `GameLogic/Object.h`, already included by
  `W3DModelDraw.cpp`) is kept for `draw->object` and
  `object->getControllingPlayer()`; `Object` is not renamed;
- the position call goes through `Rva001C86B0Object::position(Coord3D *)`, an
  address-named ABI view of ILT `0x000421AE` -> `0x001C86B0`. The ledger owns
  that body as `?bfmeGetPosition421AE@Object@@QAEPBUCoord3D@@PAU2@0@Z`
  (pointer return, two pointer arguments); this caller needs the
  aggregate-return spelling (hidden return slot = its outgoing argument slot,
  null second pointer), which the real `Object` declaration cannot carry
  without redeclaring the class. `pin_consistency.py --symbol` reports the pin
  consistent (0x000421AE -> 0x001C86B0, matched).

name_regression pairs the bank with the new source and reads the bank's local
`Object` as renamed to `Rva001C86B0Object`. That pairing is false: the name
`Object` is still used for the same object in the landed body.
Correction approved by the project lead 2026-10-15.
