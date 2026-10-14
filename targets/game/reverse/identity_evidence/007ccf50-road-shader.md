# Road shader reconstruction at RVA 0x007CCF50

## Verified recovery, 2026-10-13

The 3931-byte body now passes the strict scoped build in
`game/GameEngineDevice/Source/W3DDevice/GameClient/RoadShaderPixelShader_init.cpp`.
The existing 179-byte initializer also remains exact. This recovery uses the
identity and complete boundary established below; it introduces no pins or
shared-header changes.

The new lever is the genuine, non-inlined `W3DShroud::getShroudTexture` definition
from its matched 29-byte TU: return the counted member handle at +0x1C. That
helper independently probes exact. Its visibility alone changes the shader to
3944 bytes with a larger frame. Combine it with a lexical block containing only
`blendVector` and its pixel-constant call, and all 3931 bytes match, including
all seven previously differing stack operands. The lexical block alone had
failed in earlier attempts. Adding the other texture handle's counting copy
constructor alone preserves the seven differences and is not needed.

Independent COFF/retail unwind-map inspection confirms all 18 states have the
same predecessor (-1) and cleanup receiver offset. In particular, state 17 now
cleans EBP-0x1F4, as retail does; it no longer cleans EBP-0x1E8. The handle and
string destructors retain the previously decoded release/Free_String behavior.

Raw receipts are `build/worker5-round3/base.log`, `getter.log`,
`getter-helper.log`, `counted.log`, `getter-scope.log`, `integrated.log`,
`init.log`, `eh-audit.log`, and `add-match.log`. The strict build reports 2/2
functions matched, 3 strings verified, 4 float constants verified, 237 DIR32
references checked, and no body-guard findings. The bank is removed by
`add_match.py --model gpt-6-astra`. The link census still reports LINKED 0 -> 0
for this TU: unresolved wrapper globals and string/helper names, existing
competing init/set definitions, the additionally visible shroud getter, and
COMDAT selections remain. The byte recovery therefore adds 3931 verified
source bytes but no demonstrated linked-byte credit. No pins or link baselines
were changed. The following sections preserve the earlier
partial's investigation and independent identity evidence.

## Earlier partial result

The complete candidate emits 3931 bytes against the 3931-byte retail extent, with 7 differing non-relocation bytes. It is a banked partial and adds no matched bytes. The scoped gate fails byte comparison. The preferred source is `targets/game/reverse/attempts/0x007ccf50.cpp`; every trial and raw output remains under `build/ccf50-retry/`. The tested base revision is `ebff4e78e2e6849857edb9f257640c7fe8c0a369`, and the model is `gpt-6.1-sol`.

The remaining body differences are temporary stack offsets. The shroud-presence check uses the wrong return-storage slot. The last alpha-operation diagnostic uses the wrong string-buffer slot. Its EH state 17 also cleans storage at `ebp-0x1E8`, while retail cleans `ebp-0x1F4`. That cleanup mismatch is an independent blocker to an exact recovery. See `build/ccf50-retry/audit-29.txt`, `probe-29-bank-ready.txt`, `gate-29.txt`, and `eh-29-comparison.txt`.

| Body offset | Retail byte | Candidate byte |
| --- | --- | --- |
| +0x05B1 | 1C | 14 |
| +0x05C7 | 1C | 14 |
| +0x0DEF | 18 | 24 |
| +0x0DF3 | 18 | 24 |
| +0x0E02 | 10 | 1C |
| +0x0E09 | 14 | 20 |
| +0x0E23 | 10 | 1C |

## Retry hypothesis and identity

The new hypothesis was that the previous flat-terrain identity was wrong, and that the now-landed road initializer and counted-handle/state-wrapper helpers could supply the missing class and ABI. It would be refuted by a different installing constructor, a different vtable initializer owner, incompatible road-shader handle offsets, or a complete compiler experiment that remained no closer than the retained bank.

The constructor at RVA `0x007CCE60` installs vtable VA `0x011288E4`. Slot zero reaches this target through ILT RVA `0x00036EC1`; slot two reaches the independently matched `RoadShaderPixelShader::init` at RVA `0x007CCE70` through ILT RVA `0x000030DF`. The complete initializer loads `shaders\roadnoise1.pso`, `roadnoise2.pso`, and `roadnoise3.pso` into owner offsets `+8`, `+0xC`, and `+0x10`. The target reads the same offsets and tests shader modes 8, 9, and 10, which the canonical enum names as the road base/noise combinations. Raw evidence is in `vtable-target.txt`, `vtable-owner.txt`, `helper-007cce60-decoded.txt`, and `helper-007cce70-decoded.txt` under the task scratch directory.

The method identity is `RoadShaderPixelShader::set(int)`, with private virtual decoration `?set@RoadShaderPixelShader@@EAEHH@Z` matching the landed initializer declaration. The previous alternatives merely include the whole shader-manager TU; they do not contain independent reconstructions. Recompiling the retained include now selects the separately landed `FlatTerrainShader2Stage::set` at RVA `0x007C5690`, which emits 7909 bytes against this target. Both immutable alternatives and the unedited preferred bank were inspected and preserved. See `audit-29.txt` and `probe-baseline-raw.txt`. No identity correction table or pin was edited.

## Boundary, calling convention, and types

The complete target decodes through its final `ret 4` at `+0xF58`, with no outgoing direct conditional branch or tail jump. The constructor and initializer were decoded at their complete ledger extents. The complete matched `W3DShaderManager::setShader` caller at RVA `0x00716980` loads the selected shader receiver into ECX, pushes one DWORD pass argument, invokes vtable slot zero, and returns the EAX result. The target preserves that receiver and returns the 32-bit value one. See `target-decoded.txt`, `checked-target.txt`, `caller-00716980-decoded.txt`, and `caller-00716980-checked.txt`.

The complete `bfmeGet` helper writes one pointer to hidden return storage and increments the object reference WORD at `+4`. The complete shroud getter copies its member handle at `+0x1C` into caller-owned hidden return storage, increments the same WORD, and returns with `ret 4`. The owning destructor reads the handle pointer, null-checks it, and tail-jumps to the completely decoded release helper. The release helper decrements the reference WORD, checks its low-word value and deletion flag, and may tail-jump through the object vtable. The candidate counted handles have one pointer and the same release semantics. Allocation size was not used as type evidence.

The complete `Peek_D3D_Base_Texture` helper receives the address of handle storage in ECX. It loads the object pointer from that storage, checks readiness through virtual slot `+0x28` using AL, may initialize through slot `+0x2C`, and returns the native pointer reached through object `+0x14` then `+8`. Thus passing the pointee as receiver would be wrong; the candidate preserves the handle receiver. The readiness and initialization virtual implementations were not identified in this run.

The complete `Get_String` and `Free_String` bodies establish the diagnostic wrapper as one buffer pointer, with allocation metadata at negative offsets from that pointer, pool ownership, and heap cleanup. The canonical StringClass declarations are included. The wrapper retains the witnessed null-byte load order. Its nominal wrapper identity is not claimed to be EA's original type. Relevant raw complete helper decodes and checked-callee outputs are indexed by `helpers-index.txt`.

All D3DX dispatch stubs, their initial routes, and the complete scalar multiply, inverse, scaling, and translation implementations were decoded and passed to checked_callees. They establish pointer arguments, float arguments and output fields, EAX pointer results, and stdcall cleanup of 12 or 16 bytes. The existing canonical prototypes are reused. The CPU-dependent selected runtime implementations were not exercised. See `matrices-index.txt` and its named raw files.

Direct-device calls use an explicit device receiver and the decoded retail vtable slots. The native header emits pixel constant slot `+0x1A8`, but this target and the complete separately matched setter at RVA `0x0071BF30` call `+0x1B4`. A local force-inlined helper preserves the canonical cache comparison/copy and calls that independently witnessed slot. This correction reduces the best body from eight differences to seven without changing its size. No new literal image address, global declaration pin, shared header, or tooling change was needed.

## EH and rejected experiments

The target has 18 unwind states, each with predecessor -1. Counted-handle states clean `ebp-0x1F0`; early diagnostic states clean `ebp-0x1EC`; later diagnostic states clean `ebp-0x1F4`. Retail handle cleanup reaches RVA `0x0005CC00`; string cleanup follows both decoded thunks to `Free_String` at RVA `0x009DB7A0`. The object comparison shows equivalent destructor semantics and matching storage adjustments for states zero through 16. State 17 has the wrong storage adjustment. The state count alone is not an EH pass.

Finite EH generation, throw specifications, `/EHsc`, exception suppression, and frame/register family choices did not close the body. Forcing the diagnostic constructor inline supplied the previously missing inlined state-cache expansions and produced the retail extent. Independent string storage, inherited string storage, alternate handle conversions, named shroud temporaries, handle inheritance, and boolean materialization did not improve the best result. Scoped blend-vector lifetimes fix the last diagnostic slot but move the saved receiver and projection local to wrong slots. Materializing the blend vector as a temporary gives the same worse shape. Full sources, edit specifications, compiler receipts, and unedited probes are retained. The two finite searches remain in `build/shape_search/1e31ce9db0f5466a88d7bd6943323247/` and `build/shape_search/42b0f72e346e453b9d5274881d801ab3/`.

Reopening is justified by evidence for a different temporary type or lexical lifetime that puts the shroud check and final diagnostic on their retail slots without moving the already-matching locals, or by an independently justified compiler lever that achieves that result. Repeating an unchanged spelling is not justified. EA comments from the corresponding road and flat pixel-shader statements are retained in the bank.

## Checks

`check-csv-final.txt`, `pin-check.txt`, and `class-banked.txt` pass. The saved bank reproduces the same measurement in `probe-banked.txt` and `audit-banked.txt`. The raw scoped gate `gate-banked.txt` fails byte comparison, so the candidate was not added to functions.csv and a full gate was not run. The name-regression CLI in this revision accepts Git revisions rather than two file paths; the requested file form fails with an invalid object-name message in `check-29-names.txt`. Calling its `regressions` routine directly on the unedited old bank and new source returns an empty list in `audit-banked.txt`. The declared-unmatched check against the bank reports the unclaimed target because it has not landed; the raw result is `find-unmatched-banked.txt`. No check failure was bypassed.

## Landing name, 2026-10-14

ilt_guard rejects `?set@RoadShaderPixelShader@@EAEHH@Z` (and the U/A/M/Q
decorations) as outside slot 44172's window 26494-26499. The matched init and
reset rows of this class are contradicted the same way and sit in
ilt_contradicted_baseline.txt, so the class spelling itself is in doubt. The
body lands as the address-derived `set007CCF50` (vtable slot 0) until the
spelling is proven.
