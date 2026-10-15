# 0x00066C70 is _Vector_base<void*>(const allocator<void*>&), not dup_66c70

Retired claim: `dup_66c70` at 0x00066C70 (37 bytes, vendored=cnc-zh, game/gen_small/zhstl_004.cpp,
verified through object-symbol `_Vector_base<AsciiString>(a)`, whose real body is 0x00065770).

Identity: `??0?$_Vector_base@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@ABV?$allocator@PAX@1@@Z`

Evidence (retail 1.03 unpacked, tools/dis_retail.py):

- 0x00066C70 zeroes _M_start/_M_finish and calls ILT 0x00036DE5 (`jmp 0x000668C0`) to build
  `_M_end_of_storage`. symbols.csv pins 0x00036DE5 as
  `_STLP_alloc_proxy<void**,void*,allocator<void*>>(a, void**)`, proven by the matched
  `_Vector_base<void*>(n, a)` at 0x00066A90 (call at +0x1E to the same ILT;
  identity_evidence/00066eb0-vector-voidptr-fill-ctor.md).
- The allocator-only `_Vector_base<AsciiString>(a)` is 0x00065770 (37 bytes, same shape); it calls
  ILT 0x00005114 -> 0x00065430, the AsciiString alloc_proxy. So 0x00066C70 is the void* instantiation
  of the same constructor.
- The (n, a) overload is already claimed at 0x00066A90; this is the (a) overload (no `I` size argument).
- Only reference: ILT 0x00026D82 (jmp). No rel32 call site in retail (unreferenced COMDAT kept by /INCREMENTAL).
