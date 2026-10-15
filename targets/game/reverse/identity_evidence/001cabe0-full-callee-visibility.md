# 001CABE0 full-callee visibility and lifetime experiments

The preferred bank remains a partial and is unchanged. No new source recovery, identity correction, pin or ledger conversion is claimed. The tested revision is 0e5229fcf0270d88c23fc876d989391260ec80e1. The actual model is gpt-6.1-sol, confirmed by BFME_MODEL. The bank is targets/game/reverse/attempts/0x001cabe0.cpp; its SHA-256 is b673c6818baed640e39b69e7faca37b17105fd76fa63cef20b5889bad5eff2fb.

The initial hypothesis was that complete called members defined inside their classes would change the compiler's side-effect and register-preservation summaries enough to consume the module register for the disguise index while preserving the owner and controller registers. The refutation condition was an unchanged residue, new differing operands, structural drift or a helper that did not independently reproduce retail. Every successful target probe failed to improve the preferred bank. This does not prove that assembly is necessary or exhaust every possible C++ representation.

## Boundary, ABI and identity

Complete decoding confirms the half-open target extent [0x001CABE0, 0x001CAD58). All three returns restore the saved registers and exception registration; the final RET is at 0x001CAD57 and INT3 padding follows it. Every conditional branch stays inside the extent. The complete Object::attemptDamage caller at 0x001D0490 calls ILT 0x0002CA61 with its unadjusted Object pointer in ECX, no stack arguments or hidden return storage, then forwards the full EAX result. The target's direct callees and their ILT instructions were decoded in full. Raw evidence is build/cabe0-worker10/decoded-evidence.log.

The initial scratch inventory of the wrapper at 0x00232570 used an incomplete 14-byte extent and correctly flagged its outgoing conditional branch. The corrected 22-byte extent includes the non-null call to ILT 0x0002CA61 and the second RET 4. Only that complete wrapper is ABI evidence. Its corrected decode, the controlling-player accessor tail jump, the frame-handler import thunk, retail exception data and contain vtable bytes are in build/cabe0-worker10/extra-decoded-evidence.log.

BfmeSubBIC::bfmeAskBIC is the inherited bank spelling, not a newly established EA method or class name. The EA evidence row names Object.cpp without a method identity. All bank names are retained. The canonical Object header supplies module lookup and independently agrees with the owner field offsets; scratch inheritance and wrapper-object variants establish no additional type identity.

The complete StealthUpdate constructor and serializer independently witness the signed four-byte disguise index at +0x34 and template pointer at +0x38. The target reads the mask word at ThingTemplate+0xD0. PlayerList's complete lookup accepts one signed four-byte index, checks 0 through 31 and returns a Player pointer with RET 4. The active query returns a boolean consumed through AL. Team, override, name-key, module-lookup and relationship receiver and stack contracts agree with every target call. Their full decoded bodies are retained in build/cabe0-worker10/decoded-evidence.log.

The indirect contain query is checked separately. Vtable VA 0x010AB598 slot +0x3C routes through ILT 0x000085CB to the complete 88-byte query at 0x0021E340. The target supplies the interface pointer directly in ECX and one local-player pointer on the stack. Both callee returns use RET 4 and return a Player pointer. The vtable inventory is build/cabe0-worker10/vtable.log.

## Exact remaining bytes

| Offset | Retail | Preferred bank |
|---|---|---|
| +0xD8 | 76 (MOV ESI,[ESI+0x34]) | 56 (MOV EDX,[ESI+0x34]) |
| +0xE0 | 56 (PUSH ESI) | 52 (PUSH EDX) |
| +0xFD | 11 (MOV EDX,[ECX]) | 01 (MOV EAX,[ECX]) |
| +0x100 | 52 (CALL [EDX+0x3C]) | 50 (CALL [EAX+0x3C]) |

The independent baseline probe and final resolved scoped comparison reproduce the table with the complete target extent and no unresolved calls. The relevant receipts are build/cabe0-worker10/baseline-probe.log and build/cabe0-worker10/bank-final-scoped-gate.log. The latter exits with status 1 because the byte comparison fails. The preferred body's instruction lengths, branches, field offsets, call targets and stack layout agree with retail; only the listed operands differ. The allocation-web diagnostic is build/cabe0-worker10/allocation-webs-raw.log. Its instruction-difference count includes address operands and is not the byte-difference measurement.

## Rejected hypotheses

The complete in-class PlayerList lookup, Team accessor, active query and canonical Object module-lookup loop were tested individually and in a bounded interaction search with override resolution. The native index getter alone restores the previously recorded ESI/EDI mirror. Exposing the complete PlayerList lookup removes that mirror but restores the preferred bank's residue. The interaction search includes every combination of two or more of the five helper bodies, plus its unchanged control. Its source choices, labels and result receipts are build/cabe0-worker10/visibility-interactions-choices.json, build/cabe0-worker10/visibility-interactions-labels.json and build/cabe0-worker10/visibility-interactions-result.json. Every generated source and raw probe remains in the search directory named by that result receipt.

The complete existing NameKeyGenerator declaration, canonical enum, native 299-byte nameToKey body and native 162-byte Player relationship query were tested separately, in class and out of class, and together with all other direct callees. Both larger copied helpers independently pass resolved byte, callee, boundary, string and DIR32 checks in build/cabe0-worker10/visible-native-namekey-inclass-helper-scoped-gate.log and build/cabe0-worker10/visible-native-relationship-helper-scoped-gate.log. No copied helper is a new source recovery. Their definitions use inline COMDAT ownership, and the class-header copy stays in scratch.

Other rejected experiments cover an in-class target definition, the witnessed module secondary bases, canonical const override ownership, a shared selected-player reference, separated result initialization, a distinct lookup-result temporary, branch-specific null overwrite, native boolean and index getters together, native color construction, canonical active-query ownership, canonical owner views, mutable and const default-team overloads, one-case relationship and kind-of switches, receiver value/reference lifetimes, removal of the obsolete name-key cast, flag representations and object lifetimes, guard-only inline boundaries, public-method/private-storage order, helper definition order and named memory-load temporaries under complete lookup visibility. Explicit register hints were closed after two unchanged trials. A separate bounded copy-lifetime search of the new result temporary also failed to improve the bank; its receipt is build/cabe0-worker10/selected-copy-search-result.json.

The one-byte wrapper and temporary inheritance variants were compiler-shape controls, not proposed EA declarations. The integer flag changes the observed spill and test shape. Header setup failures involving placement-new guards, duplicate Relationship definitions and Color.h include roots are retained as failed setup trials; they do not refute the corresponding source hypothesis. Corrected native-header and complete local color-helper probes are separate source files and logs.

The nearest matched Object_rva001CAB00 source uses /EHs-c-. Testing that exact spelling, rather than the mechanical /EHsc- alternative, removes the required exception-registration shape and makes the target smaller. Both ordinary-index and native-index controls fail from the first instruction. The bank keeps its existing /DNDEBUG /MD /EHsc flags.

## Container and unwind checks

The name-key helper forms its auxiliary value from the four-byte key and the newly created Bucket pointer. The complete actual construction helper at 0x0008F6D0, reached through ILT 0x0003BAB1, checks a null destination and copies both source words at +0 and +4 into the corresponding destination words, with no other payload access. The insert helper passes node+4 as that destination. This establishes two payload fields independently of the node allocation size. Full decoding is in build/cabe0-worker10/map-helper-decoded.log.

The relationship find helpers at 0x000D0270 and 0x000D0550 read the complete four-byte key, follow node links, compare node+4 and return a two-word iterator through hidden storage with RET 8. The relationship caller reads the four-byte payload at node+8 and returns it as Relationship. Complete setters at 0x000D7600 and 0x000D7640 write their four-byte Relationship argument through the returned value reference. The complete subscript and insertion paths are in build/cabe0-worker10/relationship-construction-decoded.log and build/cabe0-worker10/relationship-insert-decoded.log. Their actual construction helpers at 0x000CD380 and 0x000CD3A0, reached through ILTs 0x0000A8DA and 0x0001AB59, each check the destination and copy exactly the two four-byte fields at +0 and +4; neither accesses another field. Complete helper and thunk decoding is in build/cabe0-worker10/relationship-value-copy-decoded.log. These are type audits for scratch copied helpers; no new container row or pin is introduced.

Retail's handler at 0x00C090CE points to FuncInfo at 0x00DF79D8 and its one-state unwind map at 0x00DF79D0. State 0 transitions to -1 through the complete cleanup at 0x00C090C0, which clears guard bit 0. The compiled 28-byte FuncInfo, eight-byte map and 14-byte cleanup reproduce the state transition and cleanup instructions outside their consistent relocations. The handler routes to CxxFrameHandler. There are no target-owned constructor members, element destructors or heap cleanups. Raw compiled structures, exact COFF symbol extents and retail comparison bytes are in build/cabe0-worker10/compiled-unwind-structure.log. BSS symbols in the earlier compiled-unwind.log are not initialized-data evidence.

## Verification and reopening

Pin consistency, preferred-bank class gate and ledger validation pass in build/cabe0-worker10/pin-consistency.log, build/cabe0-worker10/bank-class-gate.log and build/cabe0-worker10/check-csv-audit.log. Compiler arguments are retained without the process environment in build/cabe0-worker10/compiler-commands.json. The bank byte comparison remains failing on the table above. No shared header or production source changes, so these evidence-only changes do not require a full gate.

The final ledger check passes in build/cabe0-worker10/check-csv-final.log. The ordinary git diff whitespace check reports the CRLF terminator that re_log.py is specified to append. The added row has no trailing space or tab before that terminator, and the read-only diff check with core.whitespace=cr-at-eol passes. The raw results are build/cabe0-worker10/git-diff-check.log and build/cabe0-worker10/crlf-diff-check.log; the byte check is build/cabe0-worker10/final-close.json. The attempt log is left exactly as its sole writer produced it.

Reopening requires a supported source-lifetime or compiler-context hypothesis that predicts consumption of the module register while preserving the existing owner/controller coloring and the EDX virtual dispatch. Repeating the helper-visibility combinations, getter order, boolean guard boundaries or named memory-load controls here is not new evidence. No candidate measured closer, so the bank is not replaced. The exact run verdict is recorded once through re_log.py; elapsed time comes from build/cabe0-worker10/timing.json and the recording clock.

## Trial receipts

Raw probe output and source hashes are indexed in build/cabe0-worker10/measurements.json. The raw-difference and extent columns below are screening measurements for candidates whose relocation layout or instruction stream shifts. Only the resolved preferred-bank comparison establishes its exact remaining bytes. Every listed source and its unedited probe output is retained under build/.

| Trial | Emitted bytes | Raw differences | Extent lower bound | Relocations |
|---|---:|---:|---:|---:|
| all-complete-callees-visible-index | 376 | 4 | 4 | 22 |
| all-complete-callees-visible | 376 | 4 | 4 | 22 |
| baseline | 376 | 4 | 4 | 22 |
| canonical-active-owner-native-index | 376 | 21 | 21 | 22 |
| canonical-active-owner | 376 | 4 | 4 | 22 |
| canonical-inclass-override | 376 | 4 | 4 | 22 |
| canonical-override-native-index | 376 | 21 | 21 | 22 |
| canonical-owner-base-native-index | 376 | 21 | 21 | 22 |
| canonical-owner-base-view | 376 | 4 | 4 | 22 |
| inclass-active | 376 | 4 | 4 | 22 |
| inclass-module-lookup-native-index | 376 | 21 | 21 | 22 |
| inclass-module-lookup | 376 | 4 | 4 | 22 |
| inclass-nth-active | 376 | 4 | 4 | 22 |
| inclass-nth-native-index | 376 | 4 | 4 | 22 |
| inclass-nth | 376 | 4 | 4 | 22 |
| inclass-target | 376 | 4 | 4 | 22 |
| inclass-team | 376 | 4 | 4 | 22 |
| kindof-switch-join | 376 | 4 | 4 | 22 |
| kindof-switch-native-index | 376 | 21 | 21 | 22 |
| module-multiple-bases-native-index | 376 | 21 | 21 | 22 |
| module-multiple-bases | 376 | 4 | 4 | 22 |
| native-boolean-and-index | 376 | 21 | 21 | 22 |
| native-boolean-local-and-index | 376 | 21 | 21 | 22 |
| native-color-construction-includes | compile failure | | | |
| native-color-construction-local | 376 | 4 | 4 | 22 |
| native-color-construction | compile failure | | | |
| native-color-consumed-index-includes | compile failure | | | |
| native-color-consumed-index-local | 376 | 21 | 21 | 22 |
| native-color-consumed-index | compile failure | | | |
| native-index-before-private-storage | 376 | 21 | 21 | 22 |
| native-index-boolean-guard-boundary | 376 | 21 | 21 | 22 |
| native-index-boolean-guard-parameter-order | 376 | 21 | 21 | 22 |
| native-index-byte-flag | 376 | 21 | 21 | 22 |
| native-index-deferred-selection-init | 376 | 21 | 21 | 22 |
| native-index-defined-before-storage | 376 | 21 | 21 | 22 |
| native-index-integer-flag | 382 | 259 | 265 | 22 |
| native-index-mutable-controller | 376 | 21 | 21 | 22 |
| native-index-mutable-local-player | 376 | 21 | 21 | 22 |
| native-index-nth-defined-after-caller | 376 | 4 | 4 | 22 |
| native-index-nth-defined-before-caller | 376 | 4 | 4 | 22 |
| native-index-one-byte-flag-empty | 376 | 24 | 24 | 22 |
| native-index-one-byte-flag-value | 376 | 24 | 24 | 22 |
| native-index-owner-reference-view | 376 | 21 | 21 | 22 |
| native-index-owner-value-view | 376 | 21 | 21 | 22 |
| native-index-selected-result | 376 | 21 | 21 | 22 |
| native-index-shared-player-reference | 376 | 21 | 21 | 22 |
| native-key-expression-native-index | 376 | 21 | 21 | 22 |
| native-key-without-redundant-cast | 376 | 4 | 4 | 22 |
| native-namekey-header-corrected | 376 | 4 | 4 | 22 |
| native-namekey-header | compile failure | | | |
| neighbor-disabled-eh-flags | 300 | 227 | 303 | 16 |
| neighbor-disabled-eh-native-index | 300 | 227 | 303 | 16 |
| register-native-controller | 376 | 21 | 21 | 22 |
| register-native-module | 376 | 21 | 21 | 22 |
| relationship-switch-join | 376 | 5 | 5 | 22 |
| relationship-switch-native-index | 376 | 22 | 22 | 22 |
| selected-result-branch-join | 385 | 267 | 276 | 22 |
| selected-result-temporary | 376 | 4 | 4 | 22 |
| visible-native-namekey-corrected | 376 | 4 | 4 | 22 |
| visible-native-namekey-inclass-index | 376 | 21 | 21 | 22 |
| visible-native-namekey-inclass | 376 | 4 | 4 | 22 |
| visible-native-namekey | compile failure | | | |
| visible-native-relationship-inclass-index | 376 | 21 | 21 | 22 |
| visible-native-relationship-inclass | 376 | 4 | 4 | 22 |
| visible-native-relationship-index | 376 | 21 | 21 | 22 |
| visible-native-relationship | 376 | 4 | 4 | 22 |
| visible-nth-named-key-load | 376 | 4 | 4 | 22 |
| visible-nth-named-receiver-load | 376 | 4 | 4 | 22 |
| selected-copy-search/0 | 376 | 34 | 34 | 22 |
| selected-copy-search/1 | 376 | 34 | 34 | 22 |
| visibility-interactions/0 | 376 | 21 | 21 | 22 |
| visibility-interactions/1 | 376 | 4 | 4 | 22 |
| visibility-interactions/2 | 376 | 4 | 4 | 22 |
| visibility-interactions/3 | 376 | 4 | 4 | 22 |
| visibility-interactions/4 | 376 | 4 | 4 | 22 |
| visibility-interactions/5 | 376 | 21 | 21 | 22 |
| visibility-interactions/6 | 376 | 21 | 21 | 22 |
| visibility-interactions/7 | 376 | 21 | 21 | 22 |
| visibility-interactions/8 | 376 | 21 | 21 | 22 |
| visibility-interactions/9 | 376 | 21 | 21 | 22 |
| visibility-interactions/10 | 376 | 21 | 21 | 22 |
| visibility-interactions/11 | 376 | 4 | 4 | 22 |
| visibility-interactions/12 | 376 | 4 | 4 | 22 |
| visibility-interactions/13 | 376 | 4 | 4 | 22 |
| visibility-interactions/14 | 376 | 4 | 4 | 22 |
| visibility-interactions/15 | 376 | 4 | 4 | 22 |
| visibility-interactions/16 | 376 | 4 | 4 | 22 |
| visibility-interactions/17 | 376 | 21 | 21 | 22 |
| visibility-interactions/18 | 376 | 21 | 21 | 22 |
| visibility-interactions/19 | 376 | 21 | 21 | 22 |
| visibility-interactions/20 | 376 | 21 | 21 | 22 |
| visibility-interactions/21 | 376 | 4 | 4 | 22 |
| visibility-interactions/22 | 376 | 4 | 4 | 22 |
| visibility-interactions/23 | 376 | 4 | 4 | 22 |
| visibility-interactions/24 | 376 | 4 | 4 | 22 |
| visibility-interactions/25 | 376 | 21 | 21 | 22 |
| visibility-interactions/26 | 376 | 4 | 4 | 22 |
