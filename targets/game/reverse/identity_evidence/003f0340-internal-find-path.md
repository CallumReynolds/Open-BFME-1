# internalFindPath at 0x003F0340

## Result and next experiment

This is a complete compiling partial, not a C++ recovery. The original assembly ledger row remains unchanged. The preserved source is `targets/game/reverse/attempts/0x003f0340.cpp`. Its compiler measurement is 2347 bytes against 2347 retail bytes, with 212 differing bytes and the first difference at +0x33. The repository's measured ranking score is 0.9097; it does not establish byte equality, identity or ABI. `build/internalfindpath-3f0340/measurements.json` is the measurement register, and `strict-comparison.json` gives every remaining byte offset from the relocation-resolved comparison.

Reopen with a specific hypothesis about local lifetimes or the native profile construction, rather than another unchanged register spelling. The first remaining difference is the radius address at +0x30: retail takes `[esp+0x20]` and this candidate takes `[esp+0x24]`. Other discrepancies include the query cell and adjusted destination slots, the coordinate-copy register schedule, the profile's layer reload and the widening/storage of the two zone returns. A proposed experiment is refuted if its complete probe and strict comparison do not improve the retained candidate at the established extent. Do not retry the variants listed below without new evidence.

## Tested state and retry hypothesis

The tested base is `989f0a6423a72cb463a4cddc401b5134dda9a66b`. The model was `gpt-6.1-sol`. The previous history had no usable reconstruction: the early partial's recorded bank is absent, and the later retry was recorded as truncated. A fresh complete body was therefore necessary.

The initial hypothesis was that the current landed free-list acquisition, field initializer, clipping, world-to-cell, radius and zone-profile bodies would repair the old BFME cell-info-layout and callee-ABI skeleton. This was supported by the actual source and decoded instructions, not only by the coordinator's digest. The hypothesis would have been refuted by a complete candidate no closer than the earlier saved measurements. The new complete measurements improve on the recorded previous attempts, but do not close the target.

The pertinent current sources are `game/GameEngine/Source/GameLogic/AI/PathfindCellInfoAcquire.cpp`, `PathfindCellInfoRecord.cpp`, `PathfindGetRadiusAndCenterE30.cpp`, `PathfinderRva003D84A0.cpp`, `pathfind_getcell.cpp`, `game/GameEngine/Source/Common/S3FieldInitialisers.cpp` and `game/GameEngine/Source/GameLogic/Pathfinder/PathfindZoneTerrain.cpp`. Donor comments disagree about some field meanings, so the reconstruction retains their descriptive labels without claiming that these labels are independently recovered identities.

## Identity, extent and target ABI

The Zero Hour twin is `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp`, beginning at line 6462. Its owning declaration is `GameEngine/Include/GameLogic/AIPathfind.h` in the same reference tree. The retail diagnostic strings explicitly name `Pathfinder::InternalFindPath()`. The decoded `findPath` caller at 0x003F2F60 calls ILT 0x000155EB at +0x3EA with the same receiver and four arguments, and that thunk jumps to this target. These are the identity anchors; a matching donor or pin alone was not used as proof.

The entire target decodes through +0x92B. Its returns are at +0xED, +0x11D, +0x49B, +0x8A4 and +0x928, all with `ret 0x10`. Every outgoing conditional or unconditional branch in this extent stays within it. There is no indirect call, external tail jump, hidden return buffer or exception-registration frame in the target. It is `__thiscall`, receives Object*, a LocomotorSet reference, a source Coord3D pointer and a destination Coord3D pointer, and returns a pointer in EAX. The caller passes the four slots in that order and preserves EAX through its epilogue. The target uses a 0x88-byte local frame. `retail.txt`, `control-flow.json`, `caller-dis.txt` and `caller-checked.txt` retain the decoded evidence.

`checked-target.log` records all 34 distinct direct-call targets. `inventory-complete.txt` records their decoded thunk routes, narrowly selected current ledger rows and pins, and the string bytes. Each routed callee has a complete `<rva>-dis.txt` and `<rva>-checked.txt` file in the scratch evidence folder. These files are evidence to inspect, not a claim that their existing names are correct. The controlling-player tail call was also followed to Team::getControllingPlayer at 0x000EC8F0; `team-player-dis.txt` shows both pointer-return paths.

## Layout and width evidence

The acquisition helper at 0x003D7DB0 reads the free-list head, the link slot at +0x30 and successor at +0x2C, updates both list directions, clears both links, writes the owner cell at +0x28, copies both 32-bit coordinate fields at +0x00 and +0x04, clears +0x08 and +0x0C, clears 16-bit costs at +0x10 and +0x12, clears each 32-bit field at +0x14, +0x18, +0x1C and +0x20, and masks the flags at +0x24. This complete helper, rather than the allocation size, establishes the record view. The allocation helper's stride corroborates that view. There is no STL value-type inference in this target.

The cell has an info pointer at +0x00, a 16-bit zone at +0x08, and the bit field at +0x0C. The obstacle helper independently compares info +0x20 with the ignored ID, and the layer is extracted from bits 6 through 11. startPathfind, the closed-list move, release/reset and first-bucket selection confirm the intrusive ownership operations and the 16-bit cost fields. The acquisition donor calls +0x08 `m_nextOpen`, while the startPathfind donor calls it `m_pathParent`; no semantic name correction is made here.

The actual query-record constructor at 0x003D54E0 writes all of its initialized fields: dwords at +0x00, +0x04, +0x08, +0x0C, +0x14, +0x18, +0x1C, +0x24, +0x28 and +0x30, and bytes at +0x10, +0x11, +0x20, +0x21, +0x2C, +0x2D and +0x2E. Only +0x24 receives -1. Padding stays unwritten. The footprint helper at 0x003E05B0 reads and writes this larger record through +0x30 and returns AL with `ret 8` on both exits. Its second argument is therefore the complete record view, not merely the ICoord2D pointer advertised by an older pin. The target initializes layer +0x08, radius +0x0C, centering +0x10, flags +0x14, ignored obstacle +0x18, coordinates +0x00/+0x04 and byte +0x11 before the call. The constructor has no EH states or owned subobjects in its decoded body, and no destructor or unwind registration appears in this target.

The zone helpers read profile dword +0x00, bytes +0x04 and +0x05, and dword +0x08. Both return a 16-bit value in AX and pop two stack slots. The complete getEffectiveZone body includes its switch table; bytes after +0xE0 are the eight-entry table, not additional instructions. The target fills the profile with the surfaces at LocomotorSet +0x10, the negation of the template byte getter, the computer-control getter's AL and the template integer getter minus one. Byte versus Bool source spelling was a compiler-shape experiment; only field widths and values are claimed.

The Object declaration comes from the current canonical `object.h`, and Coord3D comes from its canonical header. The receiver fields used by copied radius code, the AI pointer at Object +0x204, and the Object template at +0x04 were checked against decoded callees. Object +0x3A8 is kept as an opaque byte getter. The Pathfinder view uses decoded extent +0x14 through +0x20, closed-list head +0x838, tunneling byte +0x83C, ignored ID +0x844 and zone-manager receiver +0xC9C. The readiness test remains an anonymous byte read at +0x08 because the naming oracle's member label conflicts with that access.

The destination-query helper at 0x003DF580 receives eight stack slots and returns AL with `ret 0x20` on every return. Its argument order is Object*, x, y, layer, radius, centering byte, output blocker pointer and flags. The footprint helper receives Object* and the larger record. The zone-transition helper at 0x003ED070 receives four stack slots, uses both zone arguments as dwords, returns AL on both normal paths and pops 0x10. The neighbor helper at 0x003E6EE0 receives nine slots, reads both boolean arguments as bytes, uses the radius as an integer and returns an integer with `ret 0x24`. The layer-change helper pops two slots. No new pin was invented for any of these helpers; unknown methods retain their RVA names.

The existing closed-list pin uses `PAPAUPathfindCellInfo`, while the acquisition declaration uses the class-tag spelling. The retained source calls the existing ILT 0x00005E48 through a typed inline RVA wrapper. The complete callee shows an info record detached and linked through the supplied head slot, so its receiver and one pointer-to-pointer stack argument are independently supported. This resolves the spelling mismatch without changing a pin or claiming another owner identity.

## BFME differences and measured experiments

BFME replaces the Zero Hour single open-list search with indexed buckets and intrusive free-list operations. It adds the Object +0x3A8 fast path, the compact movement profile, a zone-transition helper, the larger footprint query, diagnostic checkpoints and the 15000-cell cutoff. The actual return-label literals are `VALID` and `NULL`.

All trial sources and unedited logs are under `build/internalfindpath-3f0340/`. The complete outcome table is `measurements.json`. The first complete reconstruction had a larger local frame. Exposing genuine radius, world-to-cell, clipping, query-constructor and acquisition definitions, then bounding the query and cell-info temporary scopes, recovered the retail frame. Each of those five helper copies separately probes exact over its complete retail extent with relocations masked; each helper result is one probe, not an independent strict-gate recovery claim. The raw files are `helper-radius-probe.log`, `helper-world-probe.log`, `helper-clip-probe.log`, `helper-record-probe.log` and `helper-acquire-probe.log`.

The principal improvement came from a byte-valued template-flag expression and byte profile storage, which emitted retail's `neg al; sbb al,al; inc al` sequence. Explicit Y-before-X destination copying and aligned byte locals made smaller improvements. The final bank input is trial 48, which has the same measured instruction result as trial 47 and resolves the closed-list call through an existing thunk.

Rejected experiments include the two-element radius-frame generator choice, both earlier profile-constructor store orders, the direct four-argument profile constructor, boolean/byte/volatile centering variants, an integer computer-control temporary, ushort zone locals, explicit integer/flag getter owners, a reference parameter for allocateInfo, native zone-helper visibility, moving the blocker to the outer scope, and the unification/restoration of the getCell wrapper's temporary. The outer cell-scope trial was a compile failure and provides no byte evidence. Do not repeat it as a measured mismatch. The frame-family generator was fed to shape_search, and its manifest and unedited trial probes remain under `build/shape_search/4204681838824b39bc865ac44984ed49`.

## Checks and limits

`candidate-gate-47.log` contains the strict function comparison. Its only failed check is byte equality; all call relocations resolve. The independent string, float-constant and DIR32 address checks pass. `strict-comparison.json` derives its offset list directly from that raw output. The result is therefore a partial, not an exact claim and not a missing-pin blocker.

`csv-check.log`, `pin-check.log` and `class-check.log` pass on the tested checkout. `decl-check.log` refuses the scratch trial because it owns zero ledger rows, as expected for an unlanded candidate. No whitelist or policy change was made. `baseline-buildpy-gate.log` passes the unchanged assembly row's scoped gate, including body guard. `baseline-scoped-gate.log` records that build.cmd's py launcher could not locate Python in this sandbox; invoking the same tools/build.py through the available Python interpreter completed the check. No shared header or ledger source was changed, so no full gate is claimed or required for this bank.

Remaining identity limits are the inherited cell-info field labels, the opaque getter and helper meanings, and the exact source spelling of the profile bytes. The old footprint pin's ICoord2D-only declaration is not validated by this work. The bank uses a complete address-derived query-record declaration. These limits must be reviewed before any eventual exact landing, even if a later compiler shape closes the byte differences.

## Wave 20 (2026-10-15, agent D): definitive retail slot table (delta-index method)

Method: index-align our 733-instr /FAs stream vs retail at RVA 0x003F0340 (both 733
instrs), annotate our instructions with symbol+slot from build/exp0340/bank.asm,
retail slot = ours slot + (retail [esp+X] - ours [esp+X]) for rows reading the same
variable. Votes = number of agreeing rows.

| symbol | ours | retail | votes | symbol | ours | retail | votes |
|---|---|---|---|---|---|---|---|
| centerInCell | -136 | -136 | 7 ok | layer | -100 | -112 | 1 |
| isComputer | -132 | -132 | ok | cells/vars at -128 | -128 | -128 | ok |
| zone1 | -128 | -128 | 4 ok | blocker | -120 | -112 | 1 |
| cellCount | -128 | -128 | 3 ok | cell | -100 | -112 | 6 |
| templateLayer | -128 | -128 | 1 ok | radius | -116 | -120 | 5 |
| pos2d | -128 | -128 | 4 ok | zone2 | -120 | -116 | 2 |
| profile | -92 | -92 | 7 ok | adjustTo | -112 | -104 | 13 |
| isHuman | -80 | -80 | 3 ok | clipFrom | -76 | -76 | 7 |
| destinationLayer | -64 | -64 | 1 ok | startCellNdx | -60 | -60 | 2 |
| info | -52 | -52 | 9 ok | | | | |

Disputed window [-120..-92] (28 B):
- ours:   zone2+blocker(4) @-120, radius(4) @-116, adjustTo(12) @-112, cell/layer(8) @-100
- retail: radius(4) @-120, zone2(4) @-116, cell/blocker/layer(8) @-112, adjustTo(12) @-104

Same six objects, same 28 bytes; only the pack order differs (retail sizes run
4,4,8,12 vs ours 4,4,12,8). Everything outside the window matches.

Wave-20 experiments (46 new variants, fast frame oracle build/exp0340/frame_table.py):
- declaration order permutations (incl. radius-first, zone2-first, cell-before-adj):
  inert. Scope moves (cell/blocker posY7/Y9/V17/V19): inert. Init-splits for zone1,
  zone2, layer, destinationLayer, cellCount, templateLayer, isHuman, centerInCell:
  inert. adjustTo single struct copy: inert. Int/unsigned/typedef spellings: inert.
- Only sensitivities found: (1) `int radius;` without initializer -> radius -104,
  adjustTo -116 (V25); (2) __declspec(align(8/16)) on radius -> radius -120 but the
  deep region shifts (isComputer -140/-144, zone1 -132/-136, zone2 -124/-128);
  (3) blocker/cell at function scope -> whole frame +4 (blocker -64/-68, everything
  else -4); (4) profile-early -> cell/layer -88; zone-early -> centerInCell/isComputer
  swap. No variant exceeded 9/14 target slots.
- Consequence: the window assignment is not reachable by source-level spellings tried;
  it is driven by the allocator's IR-level pack order (first-definition timing /
  hidden temp). Next wave should perturb def timing or look for a missing local, not
  declaration order.
