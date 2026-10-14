# 0x00674D20 returns a real AsciiString

`?bfmeDescribeZI@BfmeOrderZI@@QAE?AVAsciiStringZI@@XZ` returned a per-file
stand-in `AsciiStringZI : StringBaseNarrowZI { char *m; }` whose destructor was
pinned at ILT 0x0000D828 and whose format call was already cast to the real
`AsciiString::format` (0x00888FF0).

- Retail unwind funclet 0x00C45120 (state action of FuncInfo reached via the
  handler stub 0x00C45139 the parent pushes) destroys the return object with
  `jmp 0x0000D828`.
- ILT 0x0000D828 is the thunk of the matched `??1AsciiString@@QAE@XZ`
  (functions.csv, AsciiStringNative.cpp), which jumps on to the releaseBuffer
  body 0x00887940. Retail was linked without ICF, so that ILT has one identity:
  the destroyed object's type is AsciiString.
- Layout: the stand-in held exactly one 4-byte buffer pointer and nothing else,
  the same layout as `AsciiString`. Its name call through ILT 0x0002D204 is
  the matched `NetCommandMsg::getContentsAsAsciiString` (0x006747C0), spelled
  as in the sibling ZH/ZM/ZN sources.
- Recompiling with `AsciiString` keeps the parent (191 B) and the funclet
  (25 B) byte-exact, so the stand-in pins `??1AsciiStringZI@@QAE@XZ`,
  `?format@StringBaseNarrowZI@@QAAXVAsciiStringZI@@ZZ` and
  `?bfmeNameZI@BfmeOrderZI@@QAE?AVAsciiStringZI@@XZ` are dropped.
