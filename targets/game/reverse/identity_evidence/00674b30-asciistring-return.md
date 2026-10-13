# 0x00674B30 returns a real AsciiString

`?bfmeDescribeZK@BfmeMessageZK@@QAE?AVAsciiStringZK@@XZ` returned a one-member
wrapper `AsciiStringZK { AsciiString m; }`, a per-file stand-in whose
destructor was pinned at ILT 0x0000D828.

- Retail unwind funclet 0x00C450A0 (state action of FuncInfo reached via the
  handler stub 0x00C450B9 the parent pushes) destroys the return object with
  `jmp 0x0000D828`.
- ILT 0x0000D828 is the thunk of the matched `??1AsciiString@@QAE@XZ`
  (functions.csv, AsciiStringNative.cpp), which jumps on to the releaseBuffer
  body 0x00887940. Retail was linked without ICF, so that ILT has one identity:
  the destroyed object's type is AsciiString.
- Layout: the wrapper held exactly one AsciiString at offset 0 and nothing
  else, so `AsciiString` itself has the same size (4), the same constructors
  (copy ctor, format) and the same destructor. Recompiling with `AsciiString`
  as the return type keeps both the parent (197 B) and the funclet (25 B)
  byte-exact, and the funclet now calls `??1AsciiString@@QAE@XZ` directly, so
  the stand-in pin `??1AsciiStringZK@@QAE@XZ` is dropped.
