# Wave-19 a4: 0x0038C1E0 identity upgraded to BFME unitTimings harness

Status: BLOCKED, no source recovery. Boundary independently re-verified this
session on the baseline EXE: 7 RET sites, last RET at +0x0B4B, INT3 pad from
+0x0B4C. SEH prologue (push -1 / handler 0x101BE28 / and esp,-8) and ECX-passed
state (`mov ebp,ecx` at +0x22) confirmed.

## Identity: BFME port of ZH `static void unitTimings(void)`

Zero Hour twin: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/System/GameLogic.cpp:3074`
(called from `GameLogic::update` at line 3578). The BFME build moved the ZH
function-level `static` counters into an object passed in ECX and calls it
per-frame from `GameLogic::update` (sole caller, one ILT site; dependency map
row `GameLogic::popSleepyUpdate` at 0x0038C1E0 is the disputed old label).

Structural correspondence, retail offset -> ZH behavior:

| retail | instruction | ZH counterpart |
|---|---|---|
| +0x24 | `mov eax,[0x12ED524]; fild [eax+0x34]; fadd st,st` | frame-rate read (TheGameEngine) doubled |
| +0x2c | `test byte [ebp+0x14]; je exit` | enable/one-shot guard byte |
| +0x3d | `mov eax,[ebp+0x1c]; dec; store; jg exit` | `if (settleFrames>0){settleFrames--;...return;}` |
| +0x50 | `push &[ebp+0x30]; call [0x1358EB4]` | `QueryPerformanceCounter(&startTime64)` (ZH:3146) |
| +0x5a | `push &[ebp+0x40]; call [0x1358EB8]` | `QueryPerformanceFrequency(&freq64)` (ZH:3147) |
| +0x64 | `mov dword [ebp+0x20],2` | `timeFrames = TIME_FRAMES` (BFME constant 2) |
| +0x6b | `mov dword [ebp+0x48],0` | drawCallTotal reset |
| +0x85 | `mov eax,[ebp+0x20]; dec; store; jg exit` | `if (timeFrames>0){timeFrames--;...return;}` |
| +0x9c | vtable call `[eax+0x14c]` via TheDisplay | `TheDisplay->getLastFrameDrawCalls()` (ZH:3155) |
| +0xaa | `push &[ebp+0x38]; call [0x1358EB4]` | `QueryPerformanceCounter(&endTime64)` (ZH:3159) |
| +0xaf2..+0xafd | `mov byte [ebp+0xc],1` / `mov byte [ebp+0x14],0` / `call j_00009958` / `TheMessageStream->appendMessage(0x1d MSG_CLEAR_GAME_DATA)` | end-of-run reset; BFME addition not in the ZH revision vendored here |
| +0xb32 | `mov dword [ebp+0x4c],0` | additional state field |

Call inventory (tools/callees.py 0x0038C1E0 2892): 29 distinct REL32 targets,
including `destroyObject@GameLogic` x2 (0x38B0C0 via j_0001d0de), StringBase
copy ctor/set/ctor(PBD)/releaseBuffer x5, AsciiString::format, plus the IAT
pair KERNEL32 QueryPerformanceCounter x2 / QueryPerformanceFrequency x1. This
matches the ZH `AsciiString sides[16]` array + per-side game resets + unit
creation/destruction loop.

## Why still blocked

Native port needs (a) the owning class/layout of the ECX state object (fields
+0xc byte, +0x14 byte, +0x1c int, +0x20 int, +0x30/+0x38/+0x40 LARGE_INTEGERs,
+0x48 int, +0x4c int), (b) ~29 callee signatures, many still dumps, (c) the
exact BFME side-name strings and harness constants, and (d) the ~20-state EH
region around `AsciiString sides[16]`. No source draft exists in this
worktree; the wave-13 a6 prep is evidence only. Estimate: dedicated session.
