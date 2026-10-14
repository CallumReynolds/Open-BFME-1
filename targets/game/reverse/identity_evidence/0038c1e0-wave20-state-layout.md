# 0x0038C1E0 `?d_0038c1e0@@YAXXZ` — wave-20 state-object layout + callee inventory

Wave 20, agent F (host chalco.vps, branch agentloop6). Foundation job: the wave-19
identity (BFME port of Zero Hour `unitTimings()`, see
`0038c1e0-wave19-unittimings-identity.md` and `session9-38c1e0-truncated-dump.md`)
is kept; this file adds the **owning-object identity**, the **complete `[this+X]`
layout table**, and the **pinned callee inventory**. No bytes converted.

## 1. The ECX state object is the global at VA 0x012F08A0

The body opens `mov ebp, ecx` (retail +0x22) — the state arrives in ECX, not on
the stack. The sole caller pins which object that is:

* `GameLogic::update` (0x0038DA10) call site **+0x188**: `b9 a0 08 2f 01`
  `mov ecx, 0x12f08a0`; **+0x18D**: `call 0x407E32`.
* `0x407E32` is thunk RVA `0x7E32` `?j_00007e32@@YAXXZ`: a bare
  `jmp 0x78C1E0` — ECX is preserved, so `this == 0x012F08A0` in the body.
* Symbols pin at 0x012F08A0: `?g_aiTargetDispatchSuppressed@@3_NA` (byte 0).
  The AI-suppress flag is only byte +0x00 of this object; the rest is the
  unit-timing harness state (BFME packed ZH's function-local statics into one
  global). Aliased by `Rva00C6B240AiSuppressInit.cpp` — do **not** rename.
* Matched owner source already on master:
  `game/GameEngine/Source/GameLogic/System/GameLogic.cpp:6374`
  `struct Rva0038C1E0 { bool rva00; ... void rva0038C1E0(); };` and the call at
  line 6499: `if (g012F08A0.rva00 && first) g012F08A0.rva0038C1E0();`.
* Independent layout proof: the matched initializer
  `?@Rva00385FB0Initialize@4` (0x00385FB0,
  `game/GameEngine/Source/Common/Bfme/Rva00385FB0State.cpp`) zeroes exactly the
  offsets below (`0x00/04/08/0C/10/14/18/1C/20/24/28/30/34/38/3C/40/44/48/4C/50/58/60/68/70/78/80/88/8C/90/94`),
  which fixes the layout's size (>= 0x98) and the 8-byte alignment of the
  double/LARGE_INTEGER groups. Reached through ILT 0x12AD5.

## 2. Layout table (`[ebp+X]`, `ebp == ecx == 0x12F08A0`)

Disasm offsets refer to the wave-20 annotated retail dump
(`python3 tools/dis_retail.py 0x0038C1E0 2892`; +0x of the body).

| off  | size | type / name          | evidence |
|------|------|----------------------|----------|
| 0x00 | 1    | `bool enabled`       | caller test (da10+0x183); init byte=0 |
| 0x04 | 4    | AsciiString (StringBase<char>*) | `operator==` vs template+0x20 (+0x404); len via `[eax+4]` (+0x4A9) |
| 0x08 | 4    | AsciiString          | `isNotEmpty` (+0x49C, +0xB0E); `compareNoCase` vs template+0x28 (+0x411,+0x445) |
| 0x0C | 1    | `bool gotUnit`       | set 1 at +0x95A/+0xA87/+0xAC4; cleared +0x59C |
| 0x10 | 4    | `const ThingTemplate* curThing` | firstTemplate +0x6ED; next via `[+0x38C]` |
| 0x14 | 1    | `bool startTiming`   | test +0x2C/+0x5D9/+0x675; cleared +0xACC |
| 0x18 | 4    | `FILE* commaLog`     | `fputs`/`fflush` via `BfmeThingDYC::bfmeGoDYC` (0x382AD0); `fclose` via `release@Rva00382AA0` (0x382AA0) +0xA9D/+0xAD0 |
| 0x1C | 4    | `int settleFrames`   | dec +0x44; =2 at +0x119/+0x1ED/+0x24A/+0x31B; =4 then *100 +0xAEE/+0xB04 |
| 0x20 | 4    | `int timeFrames`     | =2 +0x64; dec +0x90 |
| 0x24 | 4    | `int unitTypes`      | inc/cmp 6 +0x6DB |
| 0x28 | 1    | `bool veryFirstTime` | test +0x37A/+0x46E/+0x6C0/+0xAE9; cleared +0x483 |
| 0x30 | 8    | `LARGE_INTEGER startTime64` | QPC +0x54 |
| 0x38 | 8    | `LARGE_INTEGER endTime64`   | QPC +0xB1 |
| 0x40 | 8    | `LARGE_INTEGER freq64`      | QPF +0x5E |
| 0x48 | 4    | `int drawCallTotal`  | fild x4; =0 +0x6B; += +0xAE |
| 0x4C | 4    | `int mode` (0..4 state machine) | +0x10A/+0x163/+0x23A/+0x2AF/+0x335; reset +0xB32 |
| 0x50 | 8    | `double timeAll`     | +0x16C |
| 0x58 | 8    | `double timeNoPart`  | +0x244 |
| 0x60 | 8    | `double` (cleared; unused in this body) | init only |
| 0x68 | 8    | `double timeNoSpawn` | +0x2B8 (fst) |
| 0x70 | 8    | `double timeLogic`   | +0x33F |
| 0x78 | 8    | `double timeToUpdate`| +0x10C |
| 0x80 | 8    | `double` (cleared; unused in this body) | init only |
| 0x88 | 4    | `float drawCallAll`  | +0x17D |
| 0x8C | 4    | `float drawCallNoPart` | +0x2CD |
| 0x90 | 4    | `float drawCallNoSpawn` | +0x34B |
| 0x94 | 4    | `float drawCallLogic`| +0x126 |

Object size >= 0x98 (init clears through `[eax+94h]`; +0x98..+0x9B pad implied
by the 8-byte alignment of the doubles). The 8-byte timing members hold
QPC/QPF output fed through `fild`/`fdiv` math: `(end-start) * 1e6 / freq` yields
microseconds; the `double 1e6` literal lives at 0x10EB500.

## 3. Callee inventory (29 distinct; `tools/callees.py 0x0038C1E0 2892`)

Thunk RVA -> real RVA, symbol (ledger name; thunks are `j_` ILT trampolines):

| thunk -> real | symbol | x | signature guess/status |
|---|---|---|---|
| 0x156e -> 0x1701a0 | `??0Rva001701A0Record@@QAE@XZ` | 1 | ctor, unresolved dump |
| 0x16a4 -> 0x0c4d40 | `?testStatus@BFMEActionObject@@QBE_NH@Z` | 1 | `bool(int)` |
| 0x2847 -> 0x4c0c80 | `?HideControlBar@@YAX_N@Z` | 1 | free `void(bool)` — matched |
| 0x32d8 -> 0x0a2cb0 | `?isKindOf@ThingTemplate@@QBE_NW4KindOfType@@@Z` | 17 | `bool(KindOfType)` — matched |
| 0x50c9 -> 0x1a7a90 | `?Rva001A7A90AddShrub@@YGXPBVThingTemplate@@PBUCoord3D@@MM@Z` | 1 | free `void(const ThingTemplate*, const Coord3D*, float, float)` |
| 0x84b8 -> 0x098e50 | `?getTemplate@Thing@@QBEPBVThingTemplate@@XZ` | 1 | matched |
| 0x9958 -> 0x382aa0 | `?release@Rva00382AA0@@QAEXXZ` | 2 | `fclose` wrapper (a: 0x382AA0) |
| 0xb81b -> 0x3d57f0 | `?addObjectToPathfindMap@Pathfinder@@QAEXPAVObject@@@Z` | 1 | matched shim |
| 0x1702b -> 0x061df0 | `?startsWith@?$StringBase@D@@QBE_NPBD@Z` | 1 | StringBase<char> |
| 0x1d0de -> 0x38b0c0 | `?destroyObject@GameLogic@@QAEXPAVObject@@@Z` | 2 | matched |
| 0x2194a -> 0x1c2b80 | `?clear@Rva001C2B80@@QAEXXZ` | 1 | unresolved dump |
| 0x220c5 -> 0x05feb0 | `?compare@?$StringBase@D@@QBEHABV1@@Z` | 1 | StringBase<char> |
| 0x259b9 -> 0x07fff0 | `??$?8D@@YA_NABV?$StringBase@D@@0@Z` | 2 | `operator==` (template, by-ref) |
| 0x27471 -> 0x090570 | `?compareNoCase@?$StringBase@D@@QBEHABV1@@Z` | 2 | StringBase<char> |
| 0x28bb9 -> 0x062040 | `??4AsciiString@@QAEAAV0@PBD@Z` | 3 | `AsciiString::operator=(const char*)` |
| 0x2d5c4 -> 0x05e510 | `?isNotEmpty@?$StringBase@D@@QBE_NXZ` | 2 | StringBase<char> |
| 0x364ad -> 0x1ad080 | `?d_001ad080@@YAXXZ` | 1 | unresolved dump (named stand-in) |
| 0x37f83 -> 0x1a34c0 | `?rva001A34C0@@YGXHHPAVMatrix3D@@H@Z` | 1 | free `void(int,int,Matrix3D*,int)` |
| 0x399a5 -> 0x132e40 | `?setOrientation@Thing@@QAEXM@Z` | 1 | `void(float)` |
| 0x3a1a7 -> 0x132ce0 | `?setPosition@Thing@@QAEXPBUCoord3D@@@Z` | 1 | `void(const Coord3D*)` |
| 0x421cc -> 0x382ad0 | `?bfmeGoDYC@BfmeThingDYC@@QAEXPAX@Z` | 1 | receives `[this+0x18]` (FILE*) — logging helper |
| 0x4494a -> 0x138520 | `?newObject@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@ABV?$BitFlags@$0FG@@@I@Z` | 1 | spawn |
| 0x44f30 -> 0x0df240 | `?getNthPlayer@PlayerList@@QAEPAVPlayer@@H@Z` | 1 | `Player*(int)` |
| 0x4b01a -> 0x0a2bb0 | `?compare@?$StringBase@D@@QBEHPBD@@Z`-family | 2 | StringBase<char> vs `const char*` |
| 0x887940 | `?releaseBuffer@?$StringBase@D@@AAEXXZ` | 5 | direct (object symbol, 8 ledger names share RVA) |
| 0x887b60 | `??0?$StringBase@D@@AAE@ABV0@@Z` | 1 | copy ctor |
| 0x887c90 | `?set@?$StringBase@D@@QAEXABV1@@Z` | 1 | |
| 0x888bc0 | `??0?$StringBase@D@@AAE@PBD@Z` | 1 | ctor from `const char*` |
| 0x888ff0 | `?format@AsciiString@@QAAXV1@ZZ` | 1 | CSV writer, varargs |

IAT: `[0x1358EB4]` `KERNEL32.dll!QueryPerformanceCounter` x2,
`[0x1358EB8]` `KERNEL32.dll!QueryPerformanceFrequency` x1.

## 4. Globals, strings, constants read by the body

* `0x12ED524` TheGameEngine +0x34 (int frame-rate; `fild`, then `fadd st,st`).
* `0x12F1270` TheDisplay, vtable slot +0x14C (returns draw-call count into [0x48]).
  Also +0x150 (mode-1 path) and +0x10.
* `0x12F1600` TheTacticalView, vt+0x54 lookAt/position (800,800,0 = 0x44480000 x2, 0 at +0xB0A..+0xB2F), vt+0x124/+0x128/+0x12C in the mode-0 path, +0x1C.
* `0x12F64BC` TheParticleSystemManager; `0x12ED5C8` TheWritableGlobalData (+0x24, +0x1E); `0x12F0898` GameLogic (+0xA8 object list); `0x12F0A94/98/9C` drawcall counters (÷100 trio); `0x12EF1D8` TheThingFactory (+8); `0x12ED748` ThePlayerList; `0x12EF214` TheAI (+0xC); `0x12ED5EC` TheMessageStream (vt+0x34 appendMessage).
* Tail message: `push 0x1D` `MSG_CLEAR_GAME_DATA` at +0xADD, then `[this+0xC]=1`,
  `[this+0x14]=0`, `[this+0x4C]=0`, `HideControlBar(true)`, and
  `[this+0x1C] = 4 * 100` when `[this+0x28]` (`veryFirstTime`).
* KindOf enum ids seen: 0x5E (0x94=Infantry? or Structure), 0x64, plus the whole
  `isKindOf` chain (17 calls) matching ZH's `sides[16]` unit-type classification.
* Strings: `'Other'` 0x10EB4B8, `'Cavalry'` 0x10EB4C0, `'Monster'` 0x10EB4CC,
  `'Machine'` 0x10EB4D8, `'Infantry'` 0x10EB4E4, `'No Object'` 0x10EB4F0,
  `'Structure'` 0x1095960, `'**NO MODEL**'` 0x10EB4A8, `'CINE'` 0x10EB454,
  `'GLAInfantryAngryMobNexus'` 0x10EB434, `'FlockOfBirds'` 0x10EB424;
  CSV format `'%.1f,%d/%d/%d,%.1f,%.1f,%.1f,%.1f,%s,%s,%s,%s,%.1f,%.1f,%.1f\n'`
  at 0x10EB45C (matches ZH unitTimings CSV columns).
* Float/double literals: `1e6` 0x10EB500, `100.0f` 0x107FAC4, `0.01f`
  0x1076C24, `300.0f` 0x1096088; immediates `400/300` (mode-0 lookAt),
  `700.0 / 2.2` (mode-4), `800/800` (tail).

## 5. Open items (unchanged blockers, refined)

1. ~24 of 29 callees still need typed declarations; the `?d_`/`Rva00...` dumps
   (0x1701A0 ctor, 0x1C2B80::clear, 0x1AD080, 0x1A34C0 4-arg free) are the
   hardest. `bfmeGoDYC`'s argument semantics (FILE* + format params) unknown.
2. KindOf enum values + `sides[16]` mapping need the ZH reference extraction
   (`unitTimings` at ZH GameLogic.cpp:3074; the BFME disasm's isKindOf chain is
   the ground truth for the 17 ids actually tested).
3. ~20-state SEH region (handler 0x101BE28) around the AsciiString temps: the
   draft must reproduce the string temp destruction order to converge.
4. Mode state machine 0..4 semantics: mode 0 = settle/warm-up (300/400 lookAt),
   mode 4 = final frame (700.0, 2.2). Needs the ZH `#ifdef DO_UNIT_TIMINGS`
   copy in-tree (GameLogic.cpp:4270) mapped onto the BFME deltas.

## 6. Draft + probe (wave 20)

`targets/game/reverse/attempts/0x0038c1e0.cpp` (banked via `re_log --stash`,
measured score 0.1419; `re_attempts.log` row `?d_0038c1e0@@YAXXZ 0x0038C1E0
2892 partial`). Probe `--size 2892 --shape`: ours=775 B vs retail=2892 B,
665 non-reloc diffs, 44 structural differences, 0.228 of instructions match
after register/constant normalization. Implemented in the draft: ECX capture,
`fild [TheGameEngine+0x34]` x2 frame-rate math, settleFrames/timeFrames
countdowns, QPC/QPF pair into `[this+0x30]/[this+0x40]/[this+0x38]`,
TheDisplay vt+0x14C draw counter assignment, the mode 0..4 machine (LOGIC ->
ALL -> NO_PARTICLES -> NO_SPAWN -> report), tail `MSG_CLEAR_GAME_DATA` 0x1D
post, `HideControlBar(true)`, `lookAt(800,800,0)`, and the state resets.
**Not** implemented (the remaining ~2100 B): the side/unit classification
chain (17x `ThingTemplate::isKindOf`, `sides[]` AsciiString list), the object
teardown/spawn loops (`destroyObject`/`newObject`), the 0x10EB45C CSV `format`
path, and the ~20-state SEH string-temp region. One measured negative: spelling
the QPC/QPF slots as direct per-site address casts (instead of hoisted
pointers) is worse (ours=774, diffs=671, shape=0.217).
