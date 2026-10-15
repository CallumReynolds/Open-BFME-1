# Heading snapshots and native subtraction at 0x0027C250

No exact source recovery is claimed. The owner and method remain `Rva0027C250::method`; the EA evidence row identifies only the source file. The tested revision is `d3ea0432e7619d4abbc37c35ea521def2d3bdd02`, and the model is `gpt-6.1-sol`. The improved body is banked at targets/game/reverse/attempts/0x0027c250.cpp. Its reviewed input remains build/0027c250-finish-20261015/bank-candidate.cpp. All trial sources, unedited probe output and the experiment journal remain under build/0027c250-finish-20261015/. Trial source headers inherited the earlier bank metadata; the measurements below and measurements.jsonl are authoritative.

## Measured result

| Candidate | Compiled bytes | Retail bytes | Differing bytes | First difference | Measured score |
|---|---:|---:|---:|---|---:|
| trial00-bank | 2652 | 2669 | 1009 | +0x42E | 0.6092 |
| trial01-angle-snapshots | 2668 | 2669 | 906 | +0x42E | 0.6598 |
| trial68-native-distance-subtract | 2669 | 2669 | 684 | +0x42E | 0.7437 |
| trial100-state-update-return | 2669 | 2669 | 684 | +0x42E | 0.7437 |

The comparison uses the independently decoded ledger extent. Missing bytes are not treated as equal. The score is the repository finish-measure diagnostic, including its size penalty, rather than a byte gate. remaining-differences.json records every remaining differing byte under the probe's compiled-relocation mask, both masked byte values, the relocation list and source, target and compiled hashes. Shifted relocation positions make this a diagnostic count, not a relocation or identity certificate. bank-candidate-probe.log reproduces the reviewed input with CRLF body lines; the final preferred bank retains CRLF throughout. The complete instruction alignment is retained in trial68-native-distance-subtract-regions.txt; the two later return-declaration corrections do not change its machine code.

## Hypotheses and source changes

The retry began with the possibility that native helper visibility explains the store scheduling and receiver reloads. The first independently useful observation was at retail +0x731 and +0x82A: retail snapshots the Object heading before calling the relative-angle helper, while the old candidate reads it after the call. Explicit heading temporaries reproduce those loads. An unchanged comparison at those instructions would refute this lever; the actual decoded sequences improve.

The compiler listing trial66.cod then showed that the angle-distance temporary spilled X but addressed goal Y directly through the receiver. The retail code instead retains the same goal pointer for both component subtractions. Using the actual coordinate subtraction operation on the temporary, followed by its two-dimensional distance calculation, improves that region. A source-only change with unchanged instructions would have refuted it. No class, member or method from the old bank was renamed.

The selected candidate also corrects two unused virtual result declarations to four-byte integer results. Tables at VA 0x010BA8A8 and VA 0x010C5668 both route slot +0x214 through ILT 0x00048D88 to the update-result body at RVA 0x002768A0. The state-machine table at VA 0x0109AEF8 routes slot +0x10 to RVA 0x001703C0, whose tail reaches the independently decoded StateReturnType implementation at RVA 0x000A0760. The caller ignores these results, so the corrected declarations do not change bytes. These table labels come from existing records and do not establish the target's original owner.

## Boundary, fields and ABI

The complete target ends with RET at +0xA6C. Its nine returns use plain RET, its direct branch destinations remain inside the extent on decoded instructions, and it has no EH registration or unwind cleanup. audits.json, 0027c250-decoded.txt and 0027c250-checked-callees.log retain the checks. eligibility.json records the repository predicate's open dump row. The complete caller at RVA 0x0027E5A0 adjusts its secondary receiver by -0x10, pushes no arguments at the call through ILT 0x00020FA9, and stores the full EAX result. Its existing destructor ledger name is not adopted as identity evidence.

Every direct target was followed through its actual ILT and decoded over its complete executable extent. all-helper-audits.json and direct-routes.json identify the extents and routes; each helper has an unedited checked-callees log and full decoded instruction file. The locomotor dispatcher's executable extent excludes its inline jump table; locomotor-switch.json checks every table destination. The initial selected-virtual audit deliberately retains its failed linear decode of the update body's inline tables. The corrected executable extent and both validated tables are in 002768a0-code-decoded.txt, 002768a0-code-checked.log and 002768a0-switches.json.

The actual path output helper at RVA 0x003FD7D0 unconditionally initializes its explicit output record and uses all fields at offsets 0, 4, 8, 0xC, 0x10, 0x14, 0x18, 0x1C and 0x20. The first field participates in floating distance arithmetic, both three-float groups are copied as coordinates, and the last fields are layer and node data. RET 16 confirms Object, locomotor, output address and final low-byte Boolean stack slots. It is not a hidden return object or an inferred STL value type. The complete movement dispatcher confirms the coordinate address, two float arguments and Boolean output address with RET 20. The path destructor walks and deletes its node chain before the target deletes and clears the owned path allocation.

Canonical Thing and Object layouts supply the Object position and angle, model-condition storage, containment, AI and physics fields. The target's final arithmetic independently uses every saved position component as a float. The unrelated three-dword assignment body at RVA 0x0005BC20 does not independently prove a Coord3D constructor or three scalar floats; its current ledger identity is a key assignment for a Vector2 animation channel. It was decoded as prior-attempt evidence, not used as type identity proof. No STL key or payload is inferred from its size or copied words.

The terrain table slot +0x1C reaches ILT 0x00036F4D and the complete height helper at RVA 0x006BE2A0. Its return paths confirm floating return and RET 20. extra-routes.json also follows the notifier's outgoing tail and the state predicate/update tails. Remaining containment and Horde interface implementations, state-object virtual dispatches and all possible receiver classes are not exhaustively audited. They remain blockers to an exact identity and ABI claim, even if a later probe matches.

## Located residue and rejected levers

| Retail region | Remaining difference and measured experiments |
|---|---|
| +0x42B through +0x466 | Mixed integer and x87 snapshot copies, source-position alias materialization and the goal comparison. Native constructors, initializer lists, direct copies, paired stores, aggregate initializers, split declarations, scopes, enum accessors and widened Z precision do not improve the selected body. |
| +0x46A through +0x488 | Goal component evaluation and source alias order before the first distance calculation. Native subtractions, explicit argument lifetimes and goal-pointer snapshots do not improve this region. |
| +0x4C5 through +0x4E7 | The extra receiver copy before the container AI accessor and its subsequent reload. Typed accessors, guarded accessor forms and native AI global/getter views produce no improvement. |
| +0x516 through +0x54C | Extra scaled X/Y stores and x87 addition scheduling. Independently exact visible normalizers remove stores but worsen the complete body, including a POD-based version that preserves struct parameter decorations. |
| +0x571 through +0x605 | Coordinate copy registers and pathfinder receiver and argument evaluation order. Explicit snapshots, pointer/reference ABI views and native wrapper forms do not improve the best body. |
| +0x62A through +0x679 | Path helper arguments, virtual-call scratch registers and last-node coordinate address scheduling. Actual typed route receivers and independently exact visible path predicate produce unchanged output. |
| +0x7D2 through +0x7E2 | Remaining Y-square lifetime after the successful native subtraction change. Sum order, product and result temporaries, native length helpers, field references, destructor lifetime and float sqrt declarations do not improve it. |
| +0x86C through +0x8DE | Native matrix row-product and x87 stack scheduling. Native overloads, reference and pointer helpers, argument declarations and equivalent subtraction forms do not improve the complete comparison. |
| +0x902 through +0x92A | Object, surfaces and pathfinder argument loads around the layer query. Explicit receiver/argument temporaries and native member wrapper contexts do not improve it. |
| +0x9A1 through +0x9BE | Height clamp value selection differs from retail's reference selection. A reference-returning maximum with a short early output lifetime reproduces this local shape but worsens the complete comparison. Combining this shape with the improved matrix-row parameter context and explicit native argument snapshots also fails to improve the best body. |

measurements.jsonl records each hypothesis and result; each trial has its original source and probe log. Two unchanged arithmetic spelling or register trials closed that specific lever. Explicit inline policy and P6 scheduling produce unchanged output. The family generator reports no applicable register, copy or frame choice for the selected source in family-generator-raw.log, so no invalid generated choice set was passed to shape_search. The independently retained helper probes are trial103-independent-predicate.log, trial112-independent-kind.log and trial113-independent-normalizer.log. These reproduce existing helpers and are not new recovered progress.

## Verification and reopening

The strict scoped target gate fails for both the old bank and the selected candidate in scoped-old-gate-raw.log and scoped-best-gate-raw.log. The shifted-offset relocation diagnostics in a failed comparison do not establish new callee mismatches. Pin consistency passes in pin-consistency.log. The selected candidate's class check passes in class-best.log and the source-to-source name comparison has no regressions in name-regression.log. No shared header, pin, policy, tooling, game source or ledger row changes, so a full gate is not required. The declaration-to-ledger check fails as expected for an unlanded bank in declared-candidate.log; this is not waived as a landing check. The final preferred bank and CSV checks are retained separately as scoped-banked-gate.log, class-banked.log and check-csv-final.log. The bank remains evidence rather than authored progress.

Reopen with a concrete native lifetime or helper context that changes the first mixed coordinate snapshot or a measured improvement in one of the mapped regions. The failed forms above alone do not prove an assembly blocker. The opaque owner is retained; a low-level ILT hash check of its placeholder decoration is not an identity claim. Collection still requires all ordinary byte, declaration, identity and ABI checks after an exact source is found.

The single verdict for this run records 48.44 measured minutes from the first UTC clock reading at 20:24:13. The preferred bank was selected by its reproduced comparison; no exact C++ bytes were recovered and no synchronization or Git writes were performed.
