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
  element is four-byte and trivially assignable, real type unproven, spelled `Rva003D3D50Elem*`.
  The resize 0x003D4210 that calls it is therefore `vector<Rva003D3D50Elem*>::resize`, not void*.
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
| row | `vector<Rva003D3D50Elem*>::_M_fill_insert` | - | 0x003D3D50 (Rva003D3D50VectorFillInsert.cpp) |
| row | `vector<void*>::resize(n, v)` -> `vector<Rva003D3D50Elem*>::resize` | 0x003D4210 | 0x003D4210 |
| row | `fill<void**,void*>` | - | 0x00066530 (ParticleSys.cpp) |
| retired rows | int/Drawable* `_M_fill_insert` at 0x00067740; int/Drawable*/ObjectID `fill` at 0x00066530 | | |
| pin moved | `fill<void**,void*>` | 0x0000A060 | 0x00018412 |
| pin added | `fill<Rva003D3D50Elem**,Rva003D3D50Elem*>` | - | 0x0000A060 |
| pin moved | `_M_insert_overflow<void*>` | 0x0001CBFC | 0x0001F4FB |
| pin added | `_M_insert_overflow<Rva003D3D50Elem*>` | - | 0x0001CBFC |

Each added pin covers the retail call the moved wrong pin used to cover.

## 0x0083EA80 (was also named fill<void**,void*>)

The ledger held `fill<void**,void*>` at 0x0083EA80 (WindowVideoManagerCtor.cpp, "byte-scan placement").
A rel32 scan finds no call or jmp to 0x0083EA80 and no ILT thunk for it, while 0x00066530 is called by the
proven vector<void*>::_M_fill_insert. With no folding, the void* name belongs to 0x00066530. 0x0083EA80
becomes `fill<Rva0083EA80Elem**,Rva0083EA80Elem*>` (Rva0083EA80PointerFill.cpp): same 30 bytes, element
type unproven, address-named.
