# Exact coordinate copy at RVA 0x003CCB70

## Result and reproduction

The complete 400-byte body at `[0x003CCB70, 0x003CCD00)` is reconstructed as `?updatePosition@Rva003CC890@@QAEXXZ` in `game/GameEngine/Source/GameLogic/LargeGroupAudio/Rva003CC890UpdatePosition.cpp`. The tested base is `62a114d84525e2c935cb8f4a26e1d0929c242f52`; the model is `gpt-6.1-sol`. The final-path probe is exact and the relocation-resolving scoped gate reports `Functions: OK 1/1 matched`. The owner keeps the bank's address-derived name. This recovery makes no native EA class-name claim.

The original bank is retained byte for byte in build/ccb70-finish/baseline.cpp. Its complete probe is build/ccb70-finish/probe-baseline.log, with a second raw reproduction in build/ccb70-finish/001-baseline-confirm-probe.log. It emits 400 bytes with six non-relocation differences. Sources and unedited probe output for every subsequent experiment remain in build/ccb70-finish/. The complete trial manifest is measurements.json there, and the running verdict is build/verdict.txt. These are local raw-evidence paths, not tracked artifacts.

Reproduce with `python tools/probe.py game/GameEngine/Source/GameLogic/LargeGroupAudio/Rva003CC890UpdatePosition.cpp "?updatePosition@Rva003CC890@@QAEXXZ" 0x003CCB70 --size 400 --all`. The retained independent driver build/ccb70-finish/gate.py calls `build.verify_functions` for that exact symbol, source and extent. The final source probe and candidate gate are retained as build/ccb70-finish/final-source-probe.log and build/ccb70-finish/final-source-gate.log.

## Retry hypotheses and the resolved residue

All eight pre-dispatch verdicts and both earlier evidence notes were read before iteration. The first new hypothesis was that the newly landed aggregate-return helper at 0x003CC940 changes the caller's value graph, unlike the earlier unpinned explicit-output declaration. Its actual source, return constructors and complete retail body were inspected. The named result view still produced the original six differences, and making the complete helper definition visible as inline and noinline did not change them. This refutes helper visibility alone as the allocation lever and resolves the earlier missing-pin dependency by reusing the existing matched symbol.

Every original wrong byte is accounted for: +0x40 and +0x44 exchange the target X/Z stack offsets in two loads; +0x50 and +0x58 exchange EDX/EDI in the fallback stores; +0xF7 and +0x101 exchange the same registers in the clamp stores. Retail loads Z into EDX from `[esp+0x40]` before X into EDI from `[esp+0x38]`. The bank does the opposite. The Y word stays in ECX. The target and bank otherwise have identical decoded instructions, field offsets, x87 arithmetic, branches and stack cleanup. These are complete decodes rather than raw opcode hits.

Trial 035 establishes a new allocation model: copying Y/Z as one eight-byte representation before X gives the retail register loads, but rotates the two copy blocks' stores to Y/Z/X. Trial 040 retains that eight-byte pair while copying X first. It emits the complete retail instruction stream exactly. Trial 047 expresses this as two standard `memcpy` operations in one static force-inline helper, copying the first coordinate word and then the remaining pair. Both copies must use this form: the fallback-only and clamp-only controls leave differences. The source contains no integer type-puns for these copies and emits no copy helper call. The helper's absent-from-retail annotation records that it folds into the caller.

The positional helper's returned `Rva003CC940Point` storage is read through the canonical three-float `Coord3D` layout view. Their complete fields agree at offsets 0, 4 and 8. This is a translation-unit storage view, not a claim that the opaque helper's historical result type was Coord3D. A full `memcpy` into a second canonical local and a visible position adapter both add instructions, so the final body retains the direct view. The bank's descriptive method and member declarations are preserved; its unused `position` declaration adds no symbol or pin.

The finite generator was restricted to register, copy and store families. It offered two arithmetic-store swaps. The four evaluated combinations remain under the directory named by build/ccb70-finish/family-location.txt, with unedited family probe logs and its result.json manifest. None improved the bank. Other rejected families included nontrivial coordinate copies, aggregate-return copies, result initialization, scope and aggregate grouping, arithmetic precision, squared-length grouping and explicit control-flow forms. The measured sources, rather than an inferred history of those shapes, are the evidence.

| Trial source stem | Emitted bytes | Non-relocation differences |
|---|---:|---:|
| 001-baseline-confirm | 400 | 6 |
| 002-canonical-helper-result-view | 400 | 6 |
| 004-visible-helper-noinline | 400 | 6 |
| 007-inline-byvalue-copy | 400 | 6 |
| 009-inline-aggregate-difference | 434 | 193 |
| 010-current-result-array | 402 | 120 |
| 012-frames-reversed-arms | 404 | 254 |
| 018-coordinate-base-copy | 400 | 6 |
| 024-native-nontrivial-point-locals | 400 | 6 |
| 028-result-initialized-current | 400 | 191 |
| 030-delta-target-initialization | 412 | 202 |
| 035-paired-yz-bitcopy | 400 | 12 |
| 040-x-then-yz-bitcopy | 400 | 0 |
| 044-paired-fallback-only | 400 | 6 |
| 045-paired-clamp-only | 400 | 9 |
| 047-inline-portable-copy | 400 | 0 |
| 048-retained-position-wrapper | 416 | 324 |
| 049-return-value-memcpy-view | 416 | 325 |
| 050-native-result-fields | 400 | 6 |

## Complete boundaries, owner and calling convention

The target has one plain `ret` at +0x18F, followed by INT3 padding. Its null-event edge reaches the shared ESI epilogue at +0x18B and skips the EDI save. All other conditional branches and direct jumps stay at decoded starts inside the extent. There is no tail jump, exception registration, container operation, constructor or cleanup state in this target. The byte extent is independently checked through its terminal return and outgoing flow, not merely an aligned endpoint.

The full 1465-byte caller at 0x003D1A60 ends in a plain return at +0x5B8. Its +0x590 instruction loads an element pointer into ECX, and +0x592 calls ILT 0x00026EBD, whose jump reaches this target. No stack argument, receiver adjustment or use of the call result occurs. The unadjusted thiscall declaration with an unused result agrees with those complete caller and callee paths. The final opaque owner retains `Rva003CC890` from the bank and the already matched release source. That source and the caller agree on the event at +0x0C, eight nullable links at +0x10 through +0x2C, flag at +0x34 and reference byte at +0x38. The target reads its configuration pointer at +0x08 and a float at configuration +0x10; it reads +0x34 as a signed dword and uses `fild` in the positive-frame path. The source's `m_step` and `m_flag` widths and signedness follow those accesses.

The direct target, position-helper and caller checked-callee reports are build/ccb70-finish/checked-target.log, checked-position.log and checked-caller.log. Their complete disassemblies are decode-target.log, decode-position.log and decode-caller.log in the same directory. cfg-audit.json records every decoded branch and return. thunks-tables.log retains each thunk and table entry used below.

## Complete position helper and result type

ILT 0x0004327F jumps to the already matched `?method@Rva003CC940@@QAE?AURva003CC940Point@@XZ` at 0x003CC940. Its complete 437-byte extent ends with `ret 4` at +0x1B2, followed by padding. All direct branch destinations are internal decoded starts. The incoming unadjusted ECX is the owner. The one stack slot points to result storage, and EAX returns that same storage address. Both complete callers supply this storage and consume its three words without reading EAX. The source reuses the landed aggregate-return declaration rather than creating the old `position` pin. The bytes alone do not distinguish hidden result storage from a same-shaped explicit output pointer; the existing matched declaration chooses the repository's contract.

The helper reads owner +0 and +4 as floats, configuration +0x0C as float, and every nonnull node's +0x30 as a signed dword with `fild`. It visits all eight node pointers. Its final stores write exactly three float components at result +0, +4 and +8. The existing Point default constructor does nothing; its complete copy constructor reads and writes all three corresponding float members, with no destructor or ownership action. No container key or payload inference is involved.

Its terrain dispatch at +0x198 pushes a null normal pointer, then Y and X float bits, and consumes ST(0). The complete TerrainLogic constructor at 0x006BE070 installs primary table VA 0x0111D090. Slot +0x18 routes through ILT 0x000445CB to the complete 59-byte forwarder at 0x006BE250. Its terminal zero path returns ST(0) with `ret 12`; its other path tail-jumps through the render object's slot +0x248 without changing stack arity. The complete render constructor at 0x006CFAE0 installs table VA 0x0111D8B8, whose +0x248 slot routes through ILT 0x0003065C to the 957-byte implementation at 0x006CBB50. That complete implementation reads both arguments as four-byte floats, writes all three normal components when nonnull and returns ST(0) with `ret 12` on every terminal path. The constructors were used for their table installations only; this conversion makes no constructor ownership or unwind reconstruction claim.

The extra complete decodes, checked-callee reports and branch audits are build/ccb70-finish/decode-terrain-constructor.log, decode-terrain-forwarder.log, decode-height.log, decode-height-constructor.log, their checked-* counterparts and extra-cfg-audit.json. The canonical coordinate header and the actual Zero Hour BaseType.h coordinate methods were read directly. No LargeGroupAudio source twin was ported or claimed.

## Audio calls, identity limits and declarations

The target's +0x2C call routes through ILT 0x00029AE1 to the complete resolver at 0x000B4020. Every one of its five return paths removes eight bytes. Its six table entries all reach decoded starts inside its 367-byte extent. The first stack argument points to three coordinate words; the second points to the one-byte found flag. The complete setter at 0x000B2210, reached through ILT 0x00001E88, accepts one coordinate pointer and removes four bytes. Its permitted owner-type paths copy exactly three words to receiver +0x34, +0x38 and +0x3C. Both target calls use the owned event pointer plus four as receiver. The owned object's handle load at +0x10 agrees with the existing release source and this embedded-event view.

The final indirect call is checked separately. Primary audio table VA 0x0111C0C0 slot +0xB4 contains ILT VA 0x00440039, which jumps to the complete 155-byte body at 0x006A2800. The target pushes the result pointer before the unsigned handle. That callee reads handle then coordinate pointer, forwards the second argument to the same setter and returns with `ret 8`. There is no primary-receiver adjustment and the target does not consume a result. The canonical global declaration remains `AudioManager *TheAudio`; the gate resolves its recorded DIR32 name. The source's 1.0f literal resolves to the independently read retail constant.

These complete decodes and checked inventories are retained as build/ccb70-finish/decode-resolve.log, decode-setter.log, decode-audio-slot.log and their checked-* reports. The loaded vtable entry, all resolver switch destinations and constant bytes are in thunks-tables.log. No method is pinned from a guessed call sequence.

Only the target's opaque row name is introduced. The EA evidence has a file row for this target, with no competing native name. Source-level `name_regression.regressions` reports no descriptive-name regression, and the ILT and EA guard functions accept the proposed row. build/ccb70-finish/identity-check.log retains the actual oracle results. The target and helper address-derived decorations are placeholders. The unchanged existing AudioEventRTS resolver and setter decorations are ILT-contradicted too; this conversion reuses them as existing repository binding names and does not assert them as newly recovered native identities. Their actual targets, receiver offsets, argument widths and cleanup are independently decoded above. No existing callee identity is renamed, no new real callee decoration is pinned and no baseline is changed.

## Verification and collection

The exact source and the split-copy cleanup both passed independent relocation-resolving scoped candidate gates. Class adoption and pin consistency pass in build/ccb70-finish/class-gate.log and pin-consistency.log. The source includes the canonical Coord3D header and adds no private definition of that class. All required final ledger and declaration checks, the verified add_match transaction and the normal scoped build are retained under build/ccb70-finish/ with their unedited output and exit receipts. The collection result is appended below after those commands finish. No shared header or shim is changed, so no full gate is required by this conversion. No Git write, synchronization or publication command is authorized or run.

The verified add_match transaction passes in build/ccb70-finish/add-match.log, replaces exactly one dump row, adds its tombstone and removes the bank. Its subprocess exit receipt is add-match-receipt.json. The logging wrapper subsequently encountered a console-encoding error while displaying the captured output; the command itself had completed with exit 0, and its unedited captured output and receipt were already saved. The normal scoped build through explicit Git Bash passes in build/ccb70-finish/normal-scoped-build.log, including source claims, complete bytes, the constant, the DIR32 reference and the body guard. A separate post-transaction byte gate passes in final-scoped-gate.log, and exact-final-probe.log is a fresh final-path exact probe.

The declaration checker passes in build/ccb70-finish/declared-final.log. Its three inline definitions are explicitly absent from retail. The class gate, member-name oracle and pin consistency pass in class-gate-final.log, name-oracle-final.log and pin-consistency-final.log. The documented name_regression file-path invocation is incompatible with this revision's Git-revision CLI; name-regression-cli.log preserves that failure. The actual bank/source texts pass the same checker's `regressions` API in final-identity-check.log, which also retains the proposed row's passing ILT and EA guard results.

The initial CSV check passed. The final required invocation is blocked in build/ccb70-finish/check-csv-final.log: its working-tree mode enumerates the still-indexed bank and tries to open the deleted targets/game/reverse/attempts/0x003ccb70.cpp. The source, ledger replacement, tombstone and bank deletion remain intact for the coordinator to stage together and recheck. The checker was not bypassed or weakened. final-tree-audit.json independently confirms one removed function row, one added replacement, one new tombstone, the preserved source terminators and unchanged symbols.csv. The saved original working-tree bank matches HEAD after normal checkout line-ending normalization. The default git whitespace check treats the required ledger CR as whitespace; diff-check-crlf.log passes when the check is told to recognize CR-at-EOL. No file terminators were rewritten to satisfy it.
