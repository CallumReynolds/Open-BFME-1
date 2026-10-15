# SpawnTownsmen update counter and mask lifetime retry

This is a preserved partial, not a verified source recovery. The preferred body improves from a one-byte-short reconstruction with an ESI and EDI mirror to the full retail extent with only the late instruction scheduling and scratch-register residue. No function row, shared header, policy, tooling, baseline or pin is changed.

## Revision, hypotheses and measurements

The tested revision is d6d165c7aabbfea181992e9cacbab322694cc31b. The actual model is gpt-6.1-sol. The target ledger row, every recorded verdict and the immutable earlier bank were inspected before implementation. build/r0020ce30-finish/target-records.log retains the retrieval. build/r0020ce30-finish/measurements.jsonl and build/verdict.txt record each trial's hypothesis, explicit refutation condition and measured outcome; each trial source and unedited probe output remains in the same task directory.

The new counter hypothesis was that retail's repeated counter writes affect allocation, rather than an unreachable register spelling. A volatile counter fixes the saved-register mirror but adds a read and changes scratch registers. Restricting volatility to the already witnessed allocation-path write preserves ordinary counter reads and fixes the whole prefix. The first refutation condition was an unchanged register map or an extra counter operation; the retained write-only form has neither. It is a source-shaping annotation, not evidence that EA declared a volatile counter.

The second hypothesis was that mask construction as an intrinsic result changes argument-zero materialization. Returning the initialized mask address from memset makes MSVC emit retail's literal push zero, but initially overlaps mask and position storage. A function-scope position restores the retail frame and distinct stack homes. The mask declaration keeps the bank's BitFlags and m_bits names and models three unsigned-long words. Its empty constructor is used only before zero0020CE30 initializes every word at the factory call. This is an ABI view of the witnessed mask storage, not a recovered native BitFlags implementation. Additional writes, partial initialization, mismatched argument widths or changed cleanup would refute the view.

| Trial | Emitted bytes | Overlap differences | Quality |
| --- | ---: | ---: | ---: |
| baseline-raw | 455 | 162 | 0.6404 |
| counter-volatile-reference | 457 | 181 | 0.5987 |
| counter-write-allocation | 455 | 140 | 0.6886 |
| allocation-mask-zero-result | 456 | 51 | 0.8882 |
| position-function-scope | 456 | 40 | 0.9123 |
| best | 456 | 40 | 0.9123 |

Quality uses the repository's finish-measure formula, including its double penalty for size error. The prior bank's shorter body causes relocation-layout drift, so its score is diagnostic. The final candidate's relocation fields align with retail, and its size equals the complete target. build/r0020ce30-finish/final-candidate.log is the final raw probe; build/r0020ce30-finish/source-equality.log checks it against the measured best.cpp body.

## Boundary, identity, ABI and ownership

build/r0020ce30-finish/decoded.log retains complete decoded target and helper extents. Each extent has a checked-ADDRESS.log from checked_callees.py. Every direct branch and return was inspected. The target is 456 bytes, has returns at +0x1B3 and +0x1C7, has no outgoing tail jump, and has no conditional branch leaving its extent. ECX is the update-interface receiver, module data is at receiver minus 0x0C, and the Object pointer is at receiver minus eight. Both returns produce EAX and pop no arguments.

The complete constructor at 0x0020CC70 installs the primary table at object zero, behavior table at +0x0C and update table at +0x10. Update slot zero reaches this target through ILT 0x000416DC. Primary slot four reaches getModuleNameKey through ILT 0x0002F504 and its existing SpawnTownsmenBehavior literal. The retained method name is also confirmed by the oracle in build/r0020ce30-finish/update-oracle-best.log. The GeneralsMD UpdateModuleInterface declares update first. No SpawnTownsmen body was ported from a Zero Hour twin.

The list constructor at 0x001DB0F0 writes both words and returns its ECX receiver, with no stack arguments. Its route is ILT 0x00048135. The 33-byte find helper consumes one four-byte key, compares node +0x0C, follows next at +0x10 and returns a node with ret four. Node construction initializes vector begin, end and capacity, stores the key and clears next. The complete 265-byte overflow helper reached through ILT 0x0003B075 reads exactly one word from the value reference, writes that word and advances four bytes. Prefix and suffix copies use memmove. The complete add body agrees, takes key then value, and returns with ret eight. This proves the single-word key and ObjectID payload representation; it does not establish whether EA's native scalar template argument was a pointer, enum or integer. The inherited vector<void *> is retained as a representation view.

The complete lookup consumes a four-byte ID, compares hash-node key +4, reads Object pointer +8 and returns with ret four. Template lookup consumes one AsciiString reference. The complete newObject takes template, team, a status reference and an extra word with ret 0x10. SetPosition consumes one Coord3D pointer with ret four. Terrain slot +0x18 receives ECX, two four-byte float arguments and a null normal pointer, returns through x87 and is corroborated by the complete default implementation's ret 0x0C. Concrete terrain overrides are not separately reconstructed. The inherited SpawnTownsmen module-data declaration remains a local view of accessed offsets, not independently recovered data-constructor source.

The constructor failure state is zero with predecessor minus one. The complete allocation and deletion routes are also decoded in build/r0020ce30-finish/ownership-evidence-v2.log. They call the pluggable memory manager with allocation kind one. The retail name-key literal is read directly from its referenced address. The complete cleanup at 0x00C0C300 deletes the allocation saved at EBP minus 0x2C through scalar delete at 0x00881EB0. build/r0020ce30-finish/eh-evidence-best.log verifies the candidate's sole unwind state, all eleven cleanup bytes and that relocation target. No element or spawned-object destructor is attached to this state.

## Remaining differences and rejected hypotheses

The first residual is the mask-address LEA at +0x11D, which MSVC schedules before the third zero store and team load instead of after them. The terrain vtable load uses EDX early rather than EAX after the spawned-object return has moved to EDI. The coordinate pointer, appended ID and final receiver reload then use the preceding scratch register in the same cycle. The call argument push for the appended ID precedes the list receiver load. All remaining differing overlap byte offsets are:

+0x11D, +0x11E, +0x120, +0x121, +0x122, +0x123, +0x124, +0x125, +0x126, +0x127, +0x128, +0x129, +0x12A, +0x145, +0x146, +0x147, +0x148, +0x149, +0x14A, +0x14B, +0x14C, +0x14D, +0x14E, +0x14F, +0x150, +0x151, +0x152, +0x153, +0x154, +0x15C, +0x162, +0x168, +0x186, +0x188, +0x189, +0x18A, +0x18B, +0x18C, +0x195, +0x199.

The exact offset inventory and object relocation list are in build/r0020ce30-finish/best-byte-offsets.json. No missing target bytes remain. These are code-generation differences; assembly necessity has not been proved.

The rejected trials include list counter member and static-member visibility; pointer, aggregate, unsigned and array counter storage; owner and spawned-object references; lexical and allocation wrappers; trivial record and enum payloads; the actual list-add source visible beside the caller; setter visibility adaptations; default arguments; status forwarding wrappers; mask scalar, loop, reset, clear, copy, split memset and constructor forms; aggregate module offsets and qualifiers; architecture scheduling and intrinsic flags; native accessors; constant member pointers; argument binding order; volatile reads; compiler memory barriers; and position array and reference storage. The parameter, size and receiver variants of the mask initializer leave the final residue unchanged. Two unchanged scratch experiments close each such lever. No discarded source was placed under game/.

The actual visible list-add helper independently probes exact at 301 bytes, while its caller remains unchanged. The setter adaptations never independently reach the retail 272-byte body, so they supply no accepted native-visibility evidence. The early single-register fastcall terrain adapter is rejected as an ABI-invalid experiment: its normal pointer can occupy EDX instead of its required stack slot. The dummy-register adapter and later one-word member-pointer views were separate experiments and also worsen the target. No result from these rejected adapters is used to justify the bank's ABI.

The EH generator choices repeat earlier experiments and do not implicate the correctly matched unwind structure. The copy and frame family generator supplies no applicable choice for the original bank. Generated manifests remain under build/r0020ce30-finish/. Source-specific structural trials were used instead of repeating exhausted spelling sweeps.

## Checks and reopening condition

The ordinary scoped byte gate fails one of one in build/r0020ce30-finish/scoped-gate-best.log. It reports the inherited unresolved ??0BfmeListAK@@QAE@XZ declaration in addition to the remaining code differences. No pin is invented to hide either result. The candidate gate uses an in-memory row and leaves functions.csv untouched.

CSV validation, pin consistency, class gate, name oracle, descriptive-name preservation, complete decode and unwind comparison pass. Their raw outputs are check-csv-best.log, pin-consistency-best.log, class-gate-best.log, name-oracle-best.log, checks-summary.log and eh-evidence-best.log in the task directory. No game source, header or shim change requires a full gate. The declaration-ownership check is not a source-landing certificate for a bank owning zero ledger rows.

Reopen with a demonstrated declaration, intrinsic-return or temporary-lifetime form that changes mask LEA scheduling without losing the correct prefix, literal zero push, frame, ABI and unwind map. A successful source also needs the independently evidenced list constructor route resolved. Repeating the measured unchanged forms has no justification. All uncollected trial bodies, objects and raw logs remain under build/.

The measured work interval began at 2026-10-15 17:53:01 UTC. The verdict was recorded after 49.15 minutes with model gpt-6.1-sol.
