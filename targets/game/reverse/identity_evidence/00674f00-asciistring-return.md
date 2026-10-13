# 0x00674F00 returns a real AsciiString

`?bfmeDescribeZM@BfmeOrderZM@@QAE?AVAsciiStringZM@@XZ` returned a one-member
wrapper `AsciiStringZM { AsciiString m; }`, a per-file stand-in whose
destructor was pinned at ILT 0x0000D828.

- Retail unwind funclet 0x00C451A0 (state action of FuncInfo reached via the
  handler stub 0x00C451B9 the parent pushes) destroys the return object with
  `jmp 0x0000D828`.
- ILT 0x0000D828 is the thunk of the matched `??1AsciiString@@QAE@XZ`
  (functions.csv, AsciiStringNative.cpp), which jumps on to the releaseBuffer
  body 0x00887940. Retail was linked without ICF, so that ILT has one identity:
  the destroyed object's type is AsciiString.
- Layout: the wrapper held exactly one AsciiString at offset 0 and nothing
  else, so `AsciiString` itself has the same size (4), the same constructors
  (copy ctor, format) and the same destructor. Recompiling with `AsciiString`
  as the return type keeps both the parent (182 B) and the funclet (25 B)
  byte-exact, and the funclet now calls `??1AsciiString@@QAE@XZ` directly, so
  the stand-in pin `??1AsciiStringZM@@QAE@XZ` is dropped.
