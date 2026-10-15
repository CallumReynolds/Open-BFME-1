# Segmented-line renderer native-read retry

The preferred bank for `SegLineRendererClass::Render` at `0x00960A30` now has 9 actual resolved byte differences across 14,081 bytes, down from 51. It remains a partial reconstruction. The generated assembly ledger row is unchanged and no converted bytes are claimed. The authoritative measurements and hashes are in the receipt (build/00960a30-retry/00960a30-native-read-retry.json).

## Source change and refutation

The original bank reproduced its earlier object hash and relocation tuples. Removing only the ordered `point.Z` and `plane.X` reads in `DotSegLineLastTopSequential` corrects all forty merge address encodings and the four expansion TOP-X bytes. Two output TOP-X product bytes become different, giving the smaller complete-body residue. Four additional ordered reads can be removed without changing that object. The retained source is [the preferred bank](../attempts/0x00960a30.cpp), with its existing support include unchanged.

This measured counterexample refutes the earlier blanket conclusion that these merge SIB bytes cannot be reached from C++. The emitted operand choices change in a distant region when these two casts are removed. The optimization mechanism is not established. The change introduces no assembly, pin, global address literal, shared header change or new descriptive name. Runtime correctness and an exact conversion are not claimed.

## Boundary, identity and ABI

The complete retail decode covers 3787 instructions and 14081 bytes. Every one of its 152 branches targets an instruction boundary inside the body. Its only return is `ret 0x18` at `+0x36FE`; fifteen `INT3` bytes follow the endpoint at `+0x3701`. Raw evidence is in `build/segline-20261015/target-decoded.txt`, `complete-control.json` and `checked-callees.log` in the same directory.

The matched SegmentedLine, StreakLine and ParticleBuffer renderer callers target this exact entry and pass six stack arguments. Their complete decoded bodies and call setups are retained. Their normal scoped gate passes three functions from three sources in `build/segline-20261015/callers-scoped-gate-python.log`. The ILT oracle public API returns UNTESTABLE because this method is directly called; it supplies no contradictory name evidence. EA's aligned method row corroborates the existing name.

The constructor and destructor bodies for both dynamic buffer access objects and their locks were decoded in full. The receiver is ECX; the vertex-buffer constructor cleans sixteen stack bytes and stores the third argument as a word at `+0x10`, while the index-buffer constructor reads two word arguments and cleans eight bytes. Lock objects carry their access pointer at zero and their data pointer at four. The buffer release bodies and both lock destructor tail jumps were checked, including the complete shared unlock helper. Other direct callees, normalization, matrix transformation and subdivision providers have retained complete decodes and checked inventories. These checks use decoded field accesses, not allocation sizes or donor names.

Both exception states match retail. State zero destroys the vertex-buffer access at `[ebp-0x1B0]` and returns to state minus one; state one destroys the index-buffer access at `[ebp-0x124]` and returns to state zero. Cleanup receiver adjustments and tail targets agree with the actual destructor bodies. Raw evidence is `build/segline-20261015/eh-audit.txt` and the `checked-*` and `decoded-*` files for the cleanup actions. All seventeen existing canonical sibling emissions remain exact in the selected object, with no unresolved symbols or fallback masking.

## Remaining mismatch

The differing byte offsets are `+0x2149`, `+0x214D`, `+0x2953`, `+0x2959`, `+0x2A15`, `+0x2A18`, `+0x2A32`, `+0x2C3B`, `+0x2C3D`.

| Region | Decoded difference |
|---|---|
| `+0x2147` and `+0x214B` | The merge dot loads the other segment's X operand before multiplying. |
| `+0x2951`, `+0x2957`, `+0x2A13`, `+0x2A16` and `+0x2A30` | Five initial vertex stores exchange the SIB base and index slots while computing the same addresses. |
| `+0x2C3A` and `+0x2C3C` | The output TOP dot loads the point's X instead of the direction's X before multiplying. |

The complete resolved instruction comparison is `build/segline-20261015/bank-final-differences.txt`. A fresh compile from the preferred bank path reproduces the same resolved body in `build/segline-20261015/bank-final-strict.log`. The raw scoped candidate byte gate is red, as expected, in `build/segline-20261015/bank-final-scoped-byte-gate.log`. It must not be described as an exact recovery. Pin consistency passes in `build/segline-20261015/pin-consistency.log`; CSV integrity and the bank class gate pass in `build/segline-20261015/check_csv_final.log` and `build/segline-20261015/class-gate.log`. The declared-unmatched check rejects the bank because it has no matched rows owned by its source path; its raw output is `build/segline-20261015/declared-unmatched.log`. No whitelist, baseline or ledger claim was changed to silence that result. The core source-to-source name regression check reports no lost descriptive names in `build/segline-20261015/name-comparison-api.log`; the CLI accepts revisions rather than the file-path invocation suggested in the brief. No full gate is required for this bank-only result; no game source or shared header changed.

## Rejected hypotheses and retained experiments

The trial manifest records 431 probe executions, including rejected compile forms, with source hashes, hypotheses, measured output and raw probe paths. The receipt records the number of distinct source hashes separately. Their retained trial sources, objects and probe outputs remain under `build/segline-20261015/`. Each probe used the independently decoded retail extent.

Helper visibility, definition order, typed edge accessors, value parameters, shorter vector lifetimes, native setters, aggregate position and UV copies, literal vertex indices, color-result lifetimes and local declaration order did not improve the retained body. Precise float and ordinary inlining compiler modes regressed. Primitive X boundaries, explicit X precision and canonical component accessors also regressed. Selective helper read cleanup produced the improvement; its read masks, call-site splits, combinations and subsequent single-read and incremental cleanup searches are retained by the corresponding scripts and manifests. Broader native StartSign or bottom-normalization cleanup can correct the remaining output SIB bytes but introduces larger normalization or later float-order differences, so it was rejected.

A justified retry must preserve the corrected merge and expansion regions while improving the complete nine-byte comparison. A local correction that restores the old forty-byte merge residue or introduces other float mismatches does not improve this bank. Do not infer an assembly requirement from the earlier negative searches. Keep the existing descriptive names and the support include, and reproduce both the raw probe and the strict relocated result before further iteration.
