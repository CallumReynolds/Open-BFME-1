??1UpdateModule@@MAE@XZ = 0x001B2B10 (protected; ilt_oracle CONFIRMED, UAE contradicted) (25 B).
Retail: stores UpdateModuleInterface vtbl 0x0109CBAC at +0x10, then the inlined ~BehaviorModule stores
(0x0109CB5C at +0, 0x0109CA98 at +0xC) and tail-jumps ILT 0x00047C53 (~ObjectModule). ~BehaviorModule itself
is 0x001B2AA0 (same two stores + same tail jump, reached via ILT 0x0000F82B). The eight other rows that alias
the object symbol ??1UpdateModule (0x1FAD80 0x201AE0 0x256C60 0x27FAF0 0x28A240 0x292550 0x2A16F0 0x2AAEF0) are
byte-identical dtors of derived classes that add no destructible members; they keep their ?dup_ names.
UpdateModule primary vtable 0x0109CD94 (O11 re-verification). Approved by the project lead 2026-10-15.
