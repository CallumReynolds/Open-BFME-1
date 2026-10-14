# 0x00675D40 returns a real AsciiString

`?bfmeDescribeZS@BfmeOrderZS@@QAE?AVAsciiStringZS@@XZ` returned a one-member
wrapper `AsciiStringZS { AsciiString m; }`, a per-file stand-in whose
destructor was pinned at ILT 0x0000D828. The same wrapper typed the two string
fields the description formats.

- Retail unwind funclet 0x00C45500 (state action of FuncInfo reached via the
  handler stub 0x00C45519 the parent pushes) destroys the return object with
  `jmp 0x0000D828`.
- ILT 0x0000D828 is the thunk of the matched `??1AsciiString@@QAE@XZ`
  (functions.csv, AsciiStringNative.cpp), which jumps on to the releaseBuffer
  body 0x00887940. Retail was linked without ICF, so that ILT has one identity:
  the destroyed object's type is AsciiString.
- Layout: the wrapper held exactly one AsciiString at offset 0 and nothing
  else (its text accessor forwarded to `AsciiString::str`), so `AsciiString`
  has the same size, constructors and destructor. Recompiling with
  `AsciiString` keeps the parent (219 B) and the funclet (25 B) byte-exact, so
  the stand-in pins `??1AsciiStringZS@@QAE@XZ`,
  `?format@StringBaseNarrowZS@@QAAXVAsciiStringZS@@ZZ`,
  `?bfmeNameZS@BfmeOrderZS@@QAE?AVAsciiStringZS@@XZ` and the
  `StringBaseNarrowZS` ctor/dtor pins (none referenced) are dropped.
