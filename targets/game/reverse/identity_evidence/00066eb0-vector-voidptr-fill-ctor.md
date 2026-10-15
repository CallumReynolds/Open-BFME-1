# 0x00066EB0 is vector<void*>(size_type, void* const&, const allocator&); 0x0036E870 is not

Re-home approved by the project lead 2026-10-15.

Retired claim: `??0?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@IABQAXABV?$allocator@PAX@1@@Z`
at 0x0036E870 (ParticleSys.cpp). That body becomes
`vector<Rva0036E870Elem*>(n, v, a)` (opaque pointee, address-derived).

Identity: the same name at 0x00066EB0 (was gen-tgrid `tg_00066eb0`,
object-symbol vector<int>).
Its base: `??0?$_Vector_base@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@IABV?$allocator@PAX@1@@Z`
is 0x00066A90 (ILT 0x00026085), not 0x001F9330 (ILT 0x000212D3).

Evidence (retail 1.03 unpacked, rel32 scan of every E8/E9 in executable sections):

- STLport 4.5.3 `_hashtable.h:234`: `typedef vector<void*, ...> _BucketVector;`
  and `_hashtable.c:341` `hashtable::resize` builds
  `_BucketVector __tmp(__n, (void*)(0), _M_buckets.get_allocator())`.
  So every `hashtable<...>::resize` calls vector<void*>(n, v, a).
- ILT 0x0002039C (jmp 0x00066EB0) is called by 56 sites, among them the
  matched/ledgered hashtable::resize bodies 0x67270, 0x8FB70, 0xB87C0, 0xD10F0,
  0xD12C0, 0xD38F0, 0xD3BE0, 0xF1E00, 0x135ED0, 0x1B0480, 0x37EDB0, 0x3898C0,
  0x389C00, 0x389E10, 0x4240F0 ... (tools/callers_of.py 0x66EB0). The
  symbols.csv pin of the ctor name was already this ILT (0x0002039C).
- 0x0036E870 calls ILT 0x000212D3 -> 0x001F9330; its own ILT 0x0002C430 has no
  caller anywhere in retail. Retail was linked without identical-COMDAT folding,
  so one name has one body: it cannot also be vector<void*>.
- 0x00066EB0 calls ILT 0x00026085 -> 0x00066A90. 0x00066A90 is also called
  (same ILT) by the matched vector<void*> copy ctor 0x0082EB30
  (`??0?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@ABV01@@Z`), so it is
  `_Vector_base<void*>(n, a)`.
- 0x000CC650 (gen-tgrid `tg_000cc650`, object-symbol `_Vector_base<void*>`) has
  one caller, the matched vector<AsciiString> copy ctor 0x000D2E70, through ILT
  0x0000D8B4 that symbols.csv already pins as `_Vector_base<AsciiString>(n, a)`;
  it is `_Vector_base<AsciiString>(n, a)`, not void*.
- The 102 game objects that define the vector<void*> ctor COMDAT are
  byte-identical (link index 2026-10-13) and differ from 0x0036E870 only in the
  base-ctor relocation; with the base pinned to 0x00026085 they are 0x00066EB0.

## Pins and aliases changed (retail rel32 evidence)

| change | name | old | new | retail evidence |
|---|---|---|---|---|
| moved | `_Vector_base<void*>(n,a)` | 0x000212D3 | 0x00026085 | 0x26085 `jmp 0x66A90`; called from 0x66EBE (inside vector<void*>(n,v,a) 0x66EB0) and 0x82EAB6/0x82EB80 (vector<void*> copy ctor 0x82EB30) |
| added | `_Vector_base<Rva0036E870Elem*>(n,a)` | - | 0x000212D3 | the call at 0x36E87E (inside 0x36E870) lands on ILT 0x212D3 -> 0x1F9330; opaque address-derived pointee; takes the role of the moved pin, net zero at 0x212D3 |
| moved | `_STLP_alloc_proxy<void**,void*>(a,p)` | 0x00065430 | 0x00036DE5 | 0x36DE5 `jmp 0x668C0`; called from 0x66AAE (inside 0x66A90 = _Vector_base<void*>) and 0x66C8A; 0x65430 is reached only through ILT 0x5114, called from 0x6578A (_Vector_base<AsciiString>(a) 0x65770) and 0xCC66E (0xCC650) |
| added | `_STLP_alloc_proxy<Gen_p4pod*>(a,p)` | - | 0x00005114 | 0x5114 `jmp 0x65430`; called from 0xCC66E; gen-tgrid placeholder payload, claims no real type |
| alias | `tg_000cc650` object-symbol | `_Vector_base<void*>(n,a)` | `_Vector_base<Gen_p4pod>(n,a)` | 0xCC650's only caller is vector<AsciiString> copy ctor 0xD2E70 (ILT 0xD8B4, pinned `_Vector_base<AsciiString>`); the real-name row needs the node-alloc config, which AsciiStringVectorCopyConstructor.cpp does not use, so the placeholder stays anonymous |
