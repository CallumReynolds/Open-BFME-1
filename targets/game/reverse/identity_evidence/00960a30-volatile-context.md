# SegLineRendererClass::Render: volatile context retry

The preferred reconstruction at RVA 0x00960A30 improves from 51 differing bytes to 9 across the complete 14,081-byte body. It remains a partial. The assembly ledger row is unchanged and no recovered bytes are claimed. Verification used revision 1b7e19a7b71bf7b3c84d25003532fac6e72e0b43 and model gpt-6.1-sol.

## Source change and measurement

Only two volatile reads are removed from `DotSegLineLastTopSequential`: `point.Z` in the first product and `plane.X` in the last product. Its volatile `point.Y` read, statement order, expression tree, declarations, names and support include are retained. The first broad cleanup produced 35 differences; isolating these two reads produced the retained result.

This removes all 40 merge-address differences and the four expansion TOP-X differences from the old bank, while introducing two interior-top X-product differences. The relocation tuples remain identical to the original bank. Strict resolution reports no unresolved symbols and uses no fallback masking. The earlier conclusion that these merge SIB choices were unreachable from C++ is refuted by this experiment.

The source and unedited probe output are in build/segline-00960a30/last-top-plain-ZX/trial.cpp and build/segline-00960a30/last-top-plain-ZX/probe.log. Original measurement: build/segline-00960a30/baseline-probe.log. Strict receipts and every changed instruction are in build/segline-00960a30/audit-9/receipt.json and build/segline-00960a30/audit-9/diff-instructions.txt.

## Remaining bytes

Offsets are relative to the entry point; values are hexadecimal bytes generated from the compiled-object comparison.

| Offset | Retail | Candidate |
|---|---|---|
| +0x2149 | 0F | 17 |
| +0x214D | 17 | 0F |
| +0x2953 | 08 | 01 |
| +0x2959 | 10 | 02 |
| +0x2A15 | 07 | 38 |
| +0x2A18 | 17 | 3A |
| +0x2A32 | 0F | 39 |
| +0x2C3B | 00 | 02 |
| +0x2C3D | 0A | 08 |

The pair at +0x2149 and +0x214D exchanges the X-product FLD and FMUL operands during merge classification. Five bytes in the initial output stores exchange the SIB base and index without changing the effective address. The pair at +0x2C3B and +0x2C3D exchanges the interior-top X-product operands. These are real byte mismatches, even though the decoded operations are equivalent.

## Identity, extent and cleanup

Both complete 78-byte matched callers at RVAs 0x00919A70 and 0x00950960 call this body directly with six stack arguments and a renderer receiver. Their source calls name `SegLineRendererClass::Render` and agree with its canonical declaration. EA's aligned name row agrees. The Render ILT oracle API is untestable, so it supplies no additional identity evidence. The target decodes completely, has one `ret 0x18` at +0x36FE, ends at +0x3701 and is followed by INT3 padding. All direct branches remain inside the extent and land on decoded instruction boundaries. Raw evidence is in build/segline-00960a30/audit-baseline/ and build/segline-00960a30/checked-callees.log.

The generated object and retail have the same seven-word FuncInfo and two unwind states. State 0 cleans up the vertex-buffer owner at frame offset -0x1B0 through 0x0091D9E0; state 1 cleans up the index-buffer owner at -0x124 through 0x0091D350. Both compiled funclets match the retail receiver adjustments and destructor bindings. The complete destructor bodies, lock bodies and the unlock tail target were decoded separately. Raw evidence is in build/segline-00960a30/eh-audit.log, build/segline-00960a30/object-eh-audit.log and the callee-*-checked.log and callee-*-decode.txt files in that directory.

The array-construction route 0x00045561 to 0x000FBB40 was decoded completely. The body only returns its receiver and supplies no field-layout evidence. The ILT oracle confirms the existing Vector4 constructor decoration at that actual callback body. The canonical ledger lists the same decoration at another body that the oracle contradicts; that separate row is outside this assignment and is unchanged. Raw evidence is in build/segline-00960a30/callback-oracle.log and callee-000fbb40-decode.txt.

## Rejected hypotheses and checks

Empty local constructors, arithmetic-definition order, read-only segment pointers, index and pointer scope changes, authentic Transform and texture-binder visibility, native cross/add/subtract operations, scalar and vector temporaries, initial vertex reference/value lifetimes, all initial XYZ store permutations, isolated and coupled volatile cleanup, site-specific normalization, class-defined dot helpers, native include order, product precision, the real vertex-buffer helper's definition context and complete initial-output integer-address spellings did not improve on the retained body. Each trial has an immutable source, hypothesis receipt and raw probe.log under build/segline-00960a30/. The store search uses build/shape_search/6ab720ff92d14ead9bfa3409c80bf2f2/ plus the store-search-*.log files. The coupled cleanup choices are in build/segline-00960a30/coupled-cleanup-choices.json.

The scoped Render byte gate fails on the retained mismatch. All 17 canonical owner siblings pass from the candidate translation unit. Independent string, constant, DIR32 address and DIR32 consistency checks pass. Pin consistency and class checks pass. Raw output is in build/segline-00960a30/final-scoped-gate.log, reference-checks-9.log, pin-consistency.log and class-gate.log. The file-argument name-regression CLI invocation is unsupported by this revision; its underlying two-text comparison returns no regressions in name-regression-api.log. The declared-unmatched check correctly reports that a bank has no matched source ledger rows; its raw refusal is in declared-unmatched.log. No whitelist or baseline was changed.

Reopen from the preferred bank with a new source hypothesis that improves the complete mismatch while preserving the relocation tuples, owner emissions and cleanup map. A matching instruction shape or a locally fixed operand pair is insufficient. This run does not prove that the remaining encodings require assembly.
