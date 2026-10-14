# 0x00261440 and 0x00261530 are the Rva00262120Entry copy, not ObjectCreationList's pair

The ledger named two SpecialPower-area bodies after `pair<const NameKeyType, ObjectCreationList>`:

- 0x00261440/90 as `??0?$pair@$$CBW4NameKeyType@@VObjectCreationList@@@_STL@@QAE@ABU01@@Z`
- 0x00261530/66 as `??$_Construct@U?$pair@$$CBW4NameKeyType@@VObjectCreationList@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBW4NameKeyType@@VObjectCreationList@@@0@ABU10@@Z`

and kept the real ObjectCreationList pair copy constructor at 0x001D7720/90 as `dup_1d7720`.

## The two 90-byte bodies call different instances

`python3 tools/callees.py`:

- 0x001D7720 calls ILT 0x00042E06 -> 0x001D6A60 (get_allocator) and ILT 0x0003F418 -> 0x001D6A70
  (`_Vector_base` constructor, `ret 8`). 0x001D6A60/0x001D6A70 are the pair the matched
  `vector<ObjectCreationNugget*>` copy constructor 0x001D7300 also calls (+0x10, +0x21).
- 0x00261440 calls ILT 0x00044166 -> 0x001D95A0 and ILT 0x0001D949 -> 0x001D95B0, the
  `Rva002622D0Subject *` vector base (identity_evidence/001d95b0-pointer-vector-base.md).

Retail was linked without identical-COMDAT folding, so one mangled name owns one body. The vector
inside 0x00261440 holds `Rva002622D0Subject *`, not `ObjectCreationNugget *`, so 0x00261440 is not the
ObjectCreationList pair. 0x001D7720 sits in ObjectCreationList's run, directly before the pair's
two-argument constructor 0x001D7810.

## Who calls them

- `python3 tools/callers_of.py 0x00261440`: only 0x00261530.
- `python3 tools/callers_of.py 0x00261530`: `vector<Rva00262120Entry>::_M_insert_overflow` 0x00262120,
  the 16-byte `push_back` 0x00262280 and the element walks 0x00261590/0x002615D0.

So 0x00261530 is `_Construct<Rva00262120Entry>` and 0x00261440 is the entry's copy constructor
(an Object pointer plus a `vector<Rva002622D0Subject *>`, 16 bytes). symbols.csv already pins both
names there (`??0Rva00262120Entry@@QAE@ABU0@@Z`, `??$_Construct@URva00262120Entry@@U1@@...`).

## Why the wrong rows matched

Until c654bb4cb8 renamed the 5-byte ILT row at 0x0003F418 to `?j_0003F418@@YAXXZ`, the name
`??0?$_Vector_base@PAVObjectCreationNugget@@...` had two candidate addresses: that row and a
"resweep callee back-solved" pin at 0x0001D949. The resolver keeps the first address that reproduces
retail, so 0x00261440 matched through 0x0001D949 and 0x001D7720 through 0x0003F418. With the row
renamed, only the false pin remained and four ObjectCreationList.cpp functions failed.

## Change

- The `_Vector_base<ObjectCreationNugget*>` constructor pin moves from 0x0001D949 to its body
  0x001D6A70 (the build adds the body's ILT 0x0003F418).
- 0x00261440 and 0x00261530 take the Rva00262120Entry names, built from
  game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva00261530EntryConstruct.cpp.
- 0x001D7720 takes the pair copy constructor's name, built from ObjectCreationList.cpp.
