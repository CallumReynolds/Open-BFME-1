# 0x009D6220 is XferException::XferException(int, const char *, ...)

Retired name: `_bfmeFormatText` (descriptive placeholder, no evidence).
Identity: `??0XferException@@QAA@HPBDZZ` (already the symbols.csv pin).

Evidence (retail 1.03 unpacked):

- Every retail throw site pushes the arguments and the address of a stack
  object, calls 0x009D6220, pops 0xC (cdecl, `this` first), then pushes
  ThrowInfo VA 0x011DFE5C and the same stack object and calls
  `__CxxThrowException@8` (0x009F6D00). Example retail 0x00065B0A..0x00065B28:
  `push 0x1075524; lea edx,[esp+18h]; push 4; push edx; call 0xDD6220;
  add esp,0Ch; push 0x11DFE5C; lea eax,[esp+18h]; push eax; call 0xDF6D00`.
- ThrowInfo 0xDDFE5C -> CatchableTypeArray 0xDDFE54 -> CatchableType 0xDDFE34
  -> TypeDescriptor 0xEA704C `.?AVXferException@@`, size 8, copy ctor
  0x00065C50 (`??0XferException@@QAE@ABV0@@Z`), ThrowInfo unwind 0x00065C70
  (`??1XferException@@QAE@XZ`), both already matched.
- The object the call initialises is the thrown 8-byte XferException; the body
  writes `tag` at +4 and the formatted heap text at +0 and returns `this`.
  A `__cdecl` variadic member is exactly `QAA` with `this` pushed first.
- A natural `throw XferException(tag, fmt, ...)` compiled with the project
  flags reproduces the retail bytes of the callers (verified per TU by
  ./build.sh), and the compiler emits the `__TI1/__CTA1/__CT` records itself.
