# Retry of 0x008941A0

## Result and reopening condition

The saved reconstruction reproduces 429 bytes with 142 masked differences. A nonowning comparison view containing the input pointer and its promoted length reduces that to 141 differences without adding a helper definition. This is a partial reconstruction, with no production source or ledger change. The first difference remains at +0x1D. One relocation at +0x7B is not aligned with a retail address operand, so the masked counts are screening measurements, not acceptance evidence.

Reopen with a source hypothesis that changes the coupled scan allocation and endpoint construction while preserving the verified value ownership and exception cleanup. Merely exposing the manager lookup, changing integer signedness, changing iterator argument qualifiers, reordering declarations or wrapping the allocator callback has been tested. No result proves that assembly is required. The remaining blocker is codegen-order/loop-end-and-insertion.

The tested revision is 07a219def195b93798ffefa35aef97d473559f40. The worker receipt identifies gpt-6.1-sol. Raw sources and unedited probe outputs are retained under build/rva008941a0-20261015. The trial index is measurements.jsonl in that directory. Earlier records were retrieved in session-target.log; the previous evidence note is 0x008941a0-native-handle-and-pair.md in this directory.

## Boundary, types and ABI

The target decodes completely through its second RET 4, ending at RVA 0x0089434D. Every conditional destination is an instruction boundary inside the target. The complete caller has 711 code bytes, a NOP and a four-entry switch table in its 728-byte ledger extent. All four switch destinations enter decoded instructions. At 0x0089448C it passes the address of a locally constructed string wrapper, with the container in ECX, and later releases that wrapper. The target has no used return value or receiver adjustment. This proves the physical argument and ownership behavior, not the original C++ parameter spelling or method identity.

The complete actual value-copy helpers at 0x008926D0 and 0x00892730 transfer both fields with stride eight. Assignment at 0x008924B0 increments the source string's WORD count, releases the former destination string and copies both four-byte fields. Together with the target's own construction this establishes an owned string pointer and a four-byte state. It is not a scalar inferred from allocation size or a donor name. The string constructor at 0x0089E680 writes WORD reference count and length at offsets zero and two, then characters at offset eight. The state representation retains its observed width and values; an original enum identity or signedness is not claimed.

The complete manager callee at 0x00895950 returns a one-pointer owning handle through hidden storage, returns that storage pointer in EAX and cleans eight stack bytes. The string wrapper is pushed before the hidden result address. The returned object's count is a DWORD, distinct from the pooled string's WORD count. The target releases that handle through the complete 0x00894D90 decrement and 0x00895320 drop bodies. The latter calls the complete 0x00895260 object destructor and frees 24 bytes. The allocator-pair call at offset four is a cdecl callback with one stack argument; it is not a virtual call. The current canonical manager source was read and its visible copy independently probes exactly, but it does not improve this target.

The target FuncInfo has two independent cleanup states, both returning to state minus one. Their actions use EBP minus 0x1C and EBP minus 0x14 and tail-jump to the complete 22-byte string-owning item destructor at 0x00892890. The final candidate emits those same two adjustments and transitions. Its item destructor independently matches those 22 bytes modulo its one data relocation. The manager's conditional returned-handle and local-handle cleanup actions were followed through ILT 0x000463AD to the complete 35-byte cleanup at 0x00784A70. No new destructor identity or pin is claimed.

The existing address-derived class and method names are retained. EA evidence supplies only the Apt.cpp source-file association. The ILT oracle API reports UNTESTABLE for the target name and canonical manager name. There is no recovered original owner identity.

## Located residue

| Retail offset range | Masked differences | Located cause |
| --- | ---: | --- |
| +0x1C through +0x74 | 78 | Scan endpoint construction, register webs, length home and alignment |
| +0x79 through +0x89 | 8 | Manager receiver and hidden return argument scheduling |
| +0x8C through +0xB2 | 4 | Returned handle home and cleanup operand |
| +0xC8 through +0x102 | 23 | First insertion endpoint and argument homes |
| +0x109 through +0x11D | 2 | Successful scan iterator register |
| +0x13F through +0x175 | 24 | Second insertion endpoint and argument homes |
| +0x18B through +0x197 | 2 | Release callback base register |

The full byte list, retail and emitted values, source hash and object hash are in build/rva008941a0-20261015/remaining-differences.json and remaining-differences.log. The raw side-by-side instructions are in best-clean-probe.log. Retail keeps the scaled count in EBX and the current item in EDX while reloading the item base. The candidate keeps the base in EBX and the current item in EAX while reloading the count. That changes the intrinsic comparison's scratch register, its spills and its alignment. The returned handle uses a local home instead of the dead parameter home. Both insertion arms assign the begin and next homes and schedule their address arguments differently. The final callback base uses ECX instead of EDX.

## Measured experiments

Each named source trial and helper comparison is a single probe (n=1). The selected main body was also reproduced after formatting and at its retained bank path.

| Experiment | Emitted bytes | Probe differences | Missing bytes |
| --- | ---: | ---: | ---: |
| Saved bank | 429 | 142 | 0 |
| Best self-contained body | 429 | 141 | 0 |
| Count supplied by reference | 428 | 328 | 1 |
| Native owned key and private base | 429 | 142 | 0 |
| Named returned handle | 427 | 337 | 2 |
| Exact visible manager body | 429 | 142 | 0 |
| Visible insertion and exact resize | 429 | 140 | 0 |
| Visible insertion with comparison view | 429 | 139 | 0 |
| Matched insertion adapter | 429 | 165 | 0 |
| Explicit comparison and range storage reuse | 429 | 150 | 0 |

Each missing emitted byte also counts against the diagnostic score. The table reports the probe's masked differences separately from missing bytes. The frame and copy generator was run against the improved comparison view through shape_search with a STOP_WORKER check before every evaluation. It left that result unchanged. Raw generator choices, every trial source and both raw probes are retained by frame-search.log and its named shape_search directory.

Complete in-class insertion-helper visibility moves the returned handle into the parameter home. Its caller reaches 140 differences, or 139 with the comparison view. However, that copied helper emits 455 bytes against its 457-byte retail body and has 77 masked differences. Its resize dependency independently matches 270 bytes. These lower caller counts are retained as experiments, not selected for the self-contained bank: the additional helper definition is not verified and would broaden the recovery. The relevant files are visible-helper-caller-delta.log, complete-visible-helper-own-probe.log, visible-resize-own-probe.log and visible-helper-key-view-combination-probe.log. No helper source is added to game/ and no helper pin or row is changed.

Other retained trials cover native parameter pointer, reference and four-byte value views; native handle conversions and scoped lifetimes; signed counts and states; iterator reference and value arithmetic; direct pointer and iterator loops; extracted searches and shared failure tails; owned key members and private bases; declaration, assignment and adapter argument order; complete container storage; in-class and out-of-class inline definitions; processor scheduling; pair factories; explicit scratch lifetime reuse; and callback forwarding layers. Per-trial hypotheses, measurements and raw outputs remain in the trial index. Failed setup trials are retained with their diagnostics and their corrected follow-ups, not counted as evidence against a source hypothesis.

## Verification and raw evidence

Complete decodes are decoded-evidence.log and extra-helper-decode.log. The checked call inventories are target-callees.log, helper-checked-callees.log and extra-helper-checked.log. EH metadata and emitted cleanup are target-eh.log, manager-eh.log and best-unwind.cod. best-pair-destructor-probe.log records the independent cleanup-body match. caller-table-and-unwind-corrected.log parses the caller table as data and corrects the initial audit's padding label: the byte is NOP, not INT3. The initial raw audit remains retained.

The strict candidate-byte-gate.log and final-bank-byte-gate.log fail byte comparison and report no unresolved call. The Python scoped gate passes the unchanged generated target row only, as recorded in baseline-scoped-gate.log. build.cmd could not find its Python installation through the launcher; its raw failure is baseline-build-cmd.log. final-name-regression.log reports no regressions, name-oracle.log retains the oracle results, final-class-gate.log passes and pin-consistency.log passes. declared-unmatched.log refuses the trial because it has no matched ledger row; this is not a converted source. A full gate is not required for this bank and evidence change. check-csv-final.log passes, and final-bank-probe.log reproduces the selected bank at its retained path. The CRLF-aware whitespace check passes in diff-check-crlf.log; Git's default check flags the CR in the tool-written log row, which has no trailing space or tab.
