# 0x00067740 is vector<void*>::_M_fill_insert; 0x003D3D50 is not

Re-home approved by the project lead 2026-10-15 (re-home the vector<void*> rows to their retail-proven
addresses; same ruling as 00066eb0-vector-voidptr-fill-ctor.md).

Retail 1.03 unpacked, rel32 scan of every E8/E9 (tools/callers_of.py, tools/callees.py):

- STLport 4.6 `_hashtable.h:233-234`: the bucket vector is `vector<void*>`; `_M_initialize_buckets`
  (`_M_buckets.insert(_M_buckets.end(), __n_buckets, (void*)0)`) and `_M_copy_from`
  (`_M_buckets.insert(_M_buckets.end(), __ht._M_buckets.size(), (void*)0)`) call
  `vector<void*>::_M_fill_insert`.
- ILT 0x0002A059 (jmp 0x00067740) is called from 56 bodies, among them the ledgered hashtable bodies
  `_M_copy_from` 0x000D6800 and 0x00424380 and `_M_initialize_buckets` 0x0042D0E0 and 0x0048BDF0; the
  rest are gen-tgrid hashtable copies plus the /Od convert 0x0082FA70.
- 0x003D3D50 is reached only through ILT 0x0002570C, called only by the resize 0x003D4210, whose only
  callers are LargeGroupAudioKeyMap bfmeMerge 0x003D4580 and bfmeAddKey 0x003D46A0. No hashtable
  reaches it. Retail has no identical-COMDAT folding, so it is a different instantiation: its
  element type is `unsigned int` (see the section "0x003D3D50 is vector<unsigned int>" below).
  The resize 0x003D4210 that calls it is therefore `vector<unsigned int>::resize`, not void*.
- 0x00067740 calls fill ILT 0x00018412 (-> 0x00066530) twice and overflow ILT 0x0001F4FB
  (-> 0x000670F0) once; 0x003D3D50 calls fill ILT 0x0000A060 (-> 0x003D31A0) twice and overflow ILT
  0x0001CBFC (-> 0x000BBC80) once. So `fill<void**,void*>` is 0x00066530 and the void* overflow is
  reached through 0x0001F4FB.
- 0x00066530 has one caller, 0x00067740 (via 0x00018412). Its three ledger names
  (`fill<int*,int>`, `fill<Drawable**,Drawable*>`, `fill<ObjectID*,ObjectID>`) were already listed
  as one_identity surplus and ILT-contradicted; `fill<int*,int>` is pinned at 0x001DB670 and
  `fill<ObjectID*,ObjectID>` at 0x002CA830 elsewhere.
- The two names at 0x00067740 (`vector<int>` and `vector<Drawable*>::_M_fill_insert`) were
  one_identity surplus; `vector<int>::_M_fill_insert` is the ObjectTypes copy 0x001DBAB0 (pin
  0x000395CC, called by vector<int>::resize 0x001DC360).

## Rows and pins

| change | name | old | new |
|---|---|---|---|
| row | `vector<void*>::_M_fill_insert` | 0x003D3D50 | 0x00067740 (ParticleSys.cpp) |
| row | `vector<unsigned int>::_M_fill_insert` | - | 0x003D3D50 (Rva003D3D50VectorFillInsert.cpp) |
| row | `vector<void*>::resize(n, v)` -> `vector<unsigned int>::resize(n, v)` | 0x003D4210 | 0x003D4210 |
| row | `fill<void**,void*>` | - | 0x00066530 (ParticleSys.cpp) |
| retired rows | int/Drawable* `_M_fill_insert` at 0x00067740; int/Drawable*/ObjectID `fill` at 0x00066530 | | |
| pin moved | `fill<void**,void*>` | 0x0000A060 | 0x00018412 |
| pin added | `fill<unsigned int*,unsigned int>` | - | 0x0000A060 |
| pin moved | `_M_insert_overflow<void*>` | 0x0001CBFC | 0x0001F4FB |
| pin retired | `_M_insert_overflow<void*>` at 0x00004AED (replaced by `<Rva00418C50Elem*>`); `<int>` and `<Drawable*>` at 0x0001F4FB | | |

Each added pin covers the retail call the moved wrong pin used to cover.

## 0x0083EA80 (was also named fill<void**,void*>)

The ledger held `fill<void**,void*>` at 0x0083EA80 (WindowVideoManagerCtor.cpp, "byte-scan placement").
A rel32 scan finds no call or jmp to 0x0083EA80 and no ILT thunk for it, while 0x00066530 is called by the
proven vector<void*>::_M_fill_insert. With no folding, the void* name belongs to 0x00066530. 0x0083EA80
becomes `fill<Rva0083EA80Elem**,Rva0083EA80Elem*>` (Rva0083EA80PointerFill.cpp): same 30 bytes, element
type unproven, address-named.

## 0x0082EA80 is vector<void*>::vector(size_type)

`?dup_0082ea80@@YAXXZ` (object-symbol vector<int>(n)) calls ILT 0x00026085 -> 0x00066A90, proven
`_Vector_base<void*>(n, a)` (00066eb0-vector-voidptr-fill-ctor.md). No folding, so the counted ctor that
builds that base is vector<void*>'s. No rel32 caller reaches 0x0082EA80.

## 0x000670F0 is vector<void*>::_M_insert_overflow (true_type)

ILT 0x0001F4FB (jmp 0x000670F0) is the overflow call of the proven vector<void*>::_M_fill_insert 0x00067740
(its only other callers are the /Od placeholders 0x0082F580 and 0x0082F610). The gen-shim row
`Gen_f265_b7a8aa_000670f0` (object-symbol on a gen placeholder type) takes the real name, sourced from
ParticleSys.cpp, which emits the void* overflow next to its _M_fill_insert (probe EXACT, 265 bytes).
The five gen-shim rows whose object-symbol also spells the void* overflow (0x000BBFC0, 0x00201270,
0x002013C0, 0x003A0960, 0x003CF220) are other instantiations; their aliases are left for a follow-up.

## 0x003D3D50 is vector<unsigned int> (round-1 review correction)

The first version spelled the element as an opaque pointer, which was unsupported. 0x003D3D50's overflow
call goes through ILT 0x0001CBFC to 0x000BBC80. 0x000BBC80 is also called by 7 int-like vectors:
`XferBlockPositionStack::pushPosition` 0x000BC760, `addAudioHandle` 0x006145C0, WindowManager 0x0046B340
and 0x0046C5F0, `parseSpecialPowerIDVector` 0x000BCE80, and the set bodies 0x009EC5B0 and 0x009EC770.
With no folding, they all share one element type. It is `unsigned int`:
- `addAudioHandle` grows a vector of AudioHandle (ZH GameAudio.h:74 `typedef UnsignedInt AudioHandle`).
  symbols.csv already pinned `_M_insert_overflow<unsigned int>` at 0x0001CBFC for that call.
- The LargeGroupAudioKeyMap copy constructor 0x003D3BB0 calls `_Vector_base(n, a)` 0x003D3540 and
  `get_allocator` 0x003D32D0. Both were already pinned, ilt_oracle CONFIRMED, as vector<unsigned int>'s.
- bfmeMerge and bfmeAddKey pass the resize fill value as `push 0`, a scalar. A wrapped struct
  (Gen_t_000bbc80_m4pod) builds a stack temporary instead and does not match.
- It is not int: vector<int>::_M_fill_insert 0x001DBAB0 (called by vector<int>::resize 0x001DC360) calls
  its overflow through ILT 0x0003B075 -> 0x000BBE70. So the int overflow is 0x000BBE70, which leaves
  0x000BBC80 for unsigned int. The name `pushPosition(const int&)` is a reconstruction, not evidence.

Consequences:
- The four LargeGroupAudioKeyMap TUs (Merge, AddKey, CopyConstructor, Rva003D47A0Load) derive from
  vector<unsigned int>.
- The copy constructor no longer `#define`s `_Vector_base` and `get_allocator` to the address-scoped
  stand-ins. Their pins (`Rva003D3540VectorBase<void*>` at 0x0000799B, `bfmeGetAllocator003D32D0<void*>`
  at 0x0002CE4E) are retired.
- No new overflow name is pinned at 0x0001CBFC: the existing unsigned int pin serves it.

Retired pins proven wrong by this change:
- `_M_insert_overflow<void*>` at 0x00004AED (-> 0x00418C50): Drawable::xfer (DrawableXfer.cpp) now
  spells its m_298 element as the opaque `Rva00418C50Elem*`, pinned at 0x00004AED in its place.
  The void* overflow is 0x000670F0. NOT retired (banked): the void* pin at 0x0003B075 (-> 0x000BBE70,
  int's); BfmeConv1896.cpp bfmeAddAK 0x001DB430 spells that vector as void*, and retyping it to int
  changes codegen (309 vs 301 bytes), so the pin stays until that body is reshaped.
- `_M_insert_overflow<int>` and `<Drawable*>` at 0x0001F4FB (-> 0x000670F0, void*'s).
