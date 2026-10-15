# 0x0082EF90 is vector<void*>::_M_fill_assign; its erase, swap and ~_Vector_base are void*'s

Re-home approved by the project lead 2026-10-15: re-home the vector<void*> rows to their retail-proven
addresses. This follows 00066eb0-vector-voidptr-fill-ctor.md and 00067740-vector-voidptr-fill-insert.md.

## Retail evidence

Retail 1.03 unpacked; rel32 scan of every E8/E9; tools/callees.py 0x82EF90 513.

0x0082EF90 is the /Od copy of STLport `vector<T>::_M_fill_assign(n, val)`:
`vector<T> __tmp(__n, __val, get_allocator()); __tmp.swap(*this);` plus the erase arm. It calls:

- `vector<void*>(n, v, a)` 0x00066EB0 through ILT 0x0002039C. This is the proven hashtable bucket ctor
  (00066eb0-vector-voidptr-fill-ctor.md).
- `get_allocator` 0x000665A0 through ILT 0x00009C28. This is already the matched
  `?get_allocator@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBE?AV?$allocator@PAX@2@XZ`, and every
  hashtable::resize calls it.
- erase 0x000CF750 through ILT 0x00002A3B.
- swap 0x00066F00 through ILT 0x000063E3. This is its only rel32 caller.
- ~_Vector_base 0x00066C30 through ILT 0x00031647. This is its only rel32 caller.

Retail was linked without identical-COMDAT folding, so one instantiation's members call that same
instantiation's members. Every callee above is therefore a vector<void*> member, and so is 0x0082EF90.

## Renames

- 0x0082EF90: `?_M_fill_assign@?$vector@PAVScienceInfo@@V?$allocator@PAVScienceInfo@@@_STL@@@_STL@@QAEXIABQAVScienceInfo@@@Z`
  becomes `?_M_fill_assign@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXIABQAX@Z`.
- 0x000CF750: `?erase@?$vector@PAVScienceInfo@@V?$allocator@PAVScienceInfo@@@_STL@@@_STL@@QAEPAPAVScienceInfo@@PAPAV3@0@Z`
  becomes `?erase@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEPAPAXPAPAX0@Z`.
- 0x00066F00: tg_00066f00 becomes `?swap@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXAAV12@@Z`.
- 0x00066C30: tg_00066c30 becomes `??1?$_Vector_base@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ`.

## 0x00069C80 is not vector<void*>::swap

The vendored zhstl row at 0x00069C80 held `?swap@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXAAV12@@Z`.
- Its only reference is its ILT jmp at 0x00042997, and nothing calls that ILT.
- With no folding, the void* name belongs to 0x00066F00, the swap the proven fill_assign calls.
- 0x00069C80 becomes `?swap@?$vector@PAURva00069C80Elem@@V?$allocator@PAURva00069C80Elem@@@_STL@@@_STL@@QAEXAAV12@@Z`.
  The element type is unproven, so it is an address-named opaque pointer (Rva00069C80PointerVectorSwap.cpp).

## Retired pins

These are the ScienceInfo "folded body" pins on void* bodies:
- `??0?$vector@PAVScienceInfo@@...@QAE@IABQAVScienceInfo@@ABV?$allocator@PAVScienceInfo@@@1@@Z` at 0x00066EB0.
- `??1?$_Vector_base@PAVScienceInfo@@...@QAE@XZ` at 0x00066C30.
- `?get_allocator@?$vector@PAVScienceInfo@@...` at 0x000665A0.
- `?swap@?$vector@PAVScienceInfo@@...` at 0x00066F00.

## dup_69ec0 (0x00069EC0) retired; swap<alloc_proxy<void**>> is 0x00066BC0

- vector<void*>::swap 0x00066F00 calls ILT 0x0001C7BF -> 0x00066BC0, which is now pinned as
  `??$swap@V?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@@_STL@@YAXAAV?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@0@0@Z`.
- The old pin of that name at 0x00069970 is retired. pin_consistency reports that the bodies at 0x00066BC0 and
  0x00069970 diverge at +0xB.
- The opaque swap at 0x00069C80 still calls 0x00069970, under its own opaque proxy-swap name.

## 0x00069C80 and 0x00069EC0 are interchangeable twins

- 0x00069C80 and 0x00069EC0 are byte-identical 45-byte swaps.
- Neither is called. Their only references are their ILT jmps, 0x00042997 and 0x0001C9A4.
- Both call the proxy swap 0x00069970 through ILT 0x00025176.
- Under no folding, at most one of them is `vector<Rva00069C80Elem*>::swap`, and nothing says which. The row name
  goes to 0x00069C80.
- The placeholder `dup_69ec0` keeps its row. It is now sourced from Rva00069C80PointerVectorSwap.cpp with
  dup-of= and object-symbol= set to the opaque swap name. Its old dup-of/object-symbol, vector<void*>::swap, was wrong.
- 0x00069970's ledger name, a `_List_node` alloc_proxy swap, is a gen placeholder. Three vector-shaped swaps call it:
  0x00069C80, 0x00069EC0 and 0x0006A060.

## swap<_STLP_alloc_proxy<int*>> pin at 0x00066BC0 retired

0x00066BC0's only caller is 0x00066F00, which is vector<void*>::swap. So the `<int*>` proxy-swap pin there is
wrong, and the `<void**>` pin takes its place.
