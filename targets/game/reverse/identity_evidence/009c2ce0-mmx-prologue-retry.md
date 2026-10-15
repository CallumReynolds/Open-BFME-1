# 0x009C2CE0 reconstruction retry

No C++ recovery was verified. The preferred bank remains unchanged at targets/game/reverse/attempts/0x009c2ce0.cpp. Its actual defined symbol is `?Rva009C2CE0@@YAXPBF0PAF@Z`, rather than the dump symbol in its header. The bank is a complete inline assembly transcription. The six differing bytes are its compiler-owned entry and exit saves, not an almost-complete intrinsic reconstruction.

The tested revision is `945a9518f21363ad7b76cf9f3d4d5eff32a7d428`. The model is gpt-6.1-sol. All eleven earlier verdicts were retrieved and checked against the current bank. The raw retrieval is build/009c2ce0-retry/session-target.log. Each trial source and its unedited probe output remains under build/009c2ce0-retry/. The running verdict is build/verdict.txt. These scratch artifacts must be collected before the checkout is reused.

The complete retail extent is RVA `0x009C2CE0` through `0x009C3626` exclusive. All 2,374 bytes decode as 710 instructions. The preceding body ends in a return followed by three INT3 bytes. The target has no direct or indirect call, conditional branch, tail jump, or exception frame. Its only return is the plain RET at `+0x0945`, followed by ten INT3 bytes before the next body's entry. The complete successful decode is build/009c2ce0-retry/decode-complete.log. The checked-callee inventory is build/009c2ce0-retry/checked-target.log. The complete decode was checked for every control transfer; instruction alignment alone was not used as the boundary proof.

The fresh unchanged-bank probe emits 2,374 bytes with one relocation. The exact differing bytes are:

| Offset | Retail | Bank | Instruction difference |
|---|---|---|---|
| `+0x0000` | `52` | `53` | `push edx` versus `push ebx` |
| `+0x0001` | `51` | `52` | `push ecx` versus `push edx` |
| `+0x0002` | `53` | `51` | `push ebx` versus `push ecx` |
| `+0x0942` | `5B` | `59` | `pop ebx` versus `pop ecx` |
| `+0x0943` | `59` | `5A` | `pop ecx` versus `pop edx` |
| `+0x0944` | `5A` | `5B` | `pop edx` versus `pop ebx` |

All other non-relocation bytes agree. The relocation operand begins at `+0x0022`. Raw evidence is build/009c2ce0-retry/bank-probe.log. The wrapper failed while displaying a diagnostic character after saving the raw output; bank-probe.receipt.txt records the probe's successful execution. This is a successful measurement of a non-match, not a successful byte gate.

The new local-slot hypothesis was that the first two pushes might represent compiler-created locals rather than explicit register saves. Two unsigned local slots with assembly stores and reloads preserve the bank's EDX and ECX values, but MSVC allocates them using `sub esp, 8` before saving EBX. It then emits separate memory stores and reloads and releases the slots with `add esp, 8`. Reversing their declaration order gives the same compiled instruction and relocation result. This rejects these local-slot spellings; it does not establish that every possible C++ program is impossible.

The new intrinsic lifetime hypothesis was that the earlier transcription's mutable locals caused its spills. A fresh transcription of all 693 packed operations was compiled as a control, then rewritten with a separate const local for each result. Both include the six initial output-buffer reads and preserve the packed operation and store order in source. The const-local form increases the aligned frame and body size. The size-optimization and disabled-global-optimization trials test whether the compiler can retain the schedule or consolidate its repeated table references. Neither does so. The finite frame and register family generator found no applicable source transformation; its raw refusal is build/009c2ce0-retry/frame-generator.log. The earlier assembly-bank `/Od` and `/G6` experiments were not repeated.

Each row below is one measured compile (n=1). Difference counts are the probe's reported overlapping, non-relocation byte counts; the emitted sizes and displaced relocation operands also prevent equality.

| Trial source under build/009c2ce0-retry/ | Emitted bytes | Reported differences | Relocations | Raw output |
|---|---:|---:|---:|---|
| bank.cpp | 2374 | 6 | 1 | build/009c2ce0-retry/bank-probe.log |
| canonical-flags.cpp | 2374 | 6 | 1 | build/009c2ce0-retry/canonical-flags.log |
| compiler-locals.cpp | 2392 | 2148 | 1 | build/009c2ce0-retry/compiler-locals.log |
| compiler-locals-reverse.cpp | 2392 | 2148 | 1 | build/009c2ce0-retry/compiler-locals-reverse.log |
| intrinsics-mutable.cpp | 3244 | 1929 | 62 | build/009c2ce0-retry/intrinsics-mutable.log |
| intrinsics-ssa.cpp | 3771 | 1985 | 64 | build/009c2ce0-retry/intrinsics-ssa.log |
| intrinsics-size.cpp | 3232 | 1998 | 57 | build/009c2ce0-retry/intrinsics-size.log |
| intrinsics-local-optimizer.cpp | 22886 | 2242 | 70 | build/009c2ce0-retry/intrinsics-local-optimizer.log |

The canonical-flags trial uses the neighbouring BfmeFilterBlockMmx.cpp source's `/DNDEBUG /MD /O2` flags and the current canonical table declaration. The intrinsic control uses the same flags. Its SSA variant changes result lifetimes; its size variant appends `/O1`; its local-optimizer variant appends `/Og-`. The complete intrinsic control independently reproduces the historical 3,244-byte measurement. The earlier intrinsic source was not present in the saved attempt history, so no claim depends on a previous agent's description of that source.

The body loads its first pointer from entry ESP+4, its second from entry ESP+8, and its output pointer from entry ESP+12 after accounting for the three pushes. No stack adjustment occurs between those pushes and the final three pops. The first two pointers supply sixteen eight-byte input blocks each. The third pointer supplies the six initial four-byte reads and the complete 128-byte transform workspace and output. Packed low-word multiplication, signed high-word multiplication, signed saturation, and arithmetic word shifts establish the machine operations. They do not prove an original typedef or the signedness of both input declarations. EAX still holds the first pointer at return. That alone does not establish a native return value. Container construction, ownership, virtual dispatch, and constructor unwind checks do not apply to this leaf.

The complete 766-byte installer at RVA `0x009B3B40` loads target VA `0x00DC2CE0` at offsets `+0x0069` and `+0x012A`. Its corresponding loops store that value into the second dispatch array based at VA `0x01356C80` when the byte index is greater than `0x28`. This confirms the address-derived dispatch identity, not a semantic function name. Complete decode and checked inventory are build/009c2ce0-retry/installer-decode.log and build/009c2ce0-retry/checked-installer.log. Its three returns and branches remain inside its extent. The CPU-query call's detailed contract is not used as type evidence for the target.

Selected raw table-address hits were validated on decoded instruction boundaries inside their containing complete ledger bodies. The search also screened nearby codec bodies for the stored table pointer and second-array indirect-call offsets. It did not find a validated target caller. The known first-array callback in Rva009B58F0.cpp is not independent evidence for this second-array target. These limited searches do not prove that no callers exist. Raw search results are build/009c2ce0-retry/find-dispatch-v2.log and build/009c2ce0-retry/scan-consumers.log. Native return use and a complete indirect caller contract remain unresolved; no new signature or identity pin is added.

The historical claim that VA `0x01356640` is unbound is stale. dir32_addresses.csv records `?Rva009B3A00Table@@3PAGA` there, and S3GuardedDelegates3.cpp declares `extern unsigned short Rva009B3A00Table[48]`. The complete 140-byte initializer at RVA `0x009B3A00` clears sixteen words, places four word masks, fills seven four-word constant groups, and writes four final words through VA `0x0135669E`. The target reads twelve eight-byte constant blocks at offsets `0x00` through `0x58`, inside that span. The declaration is supported by these decoded writes and reads, rather than by allocation size or a donor name. Raw decode and checked inventory are build/009c2ce0-retry/table-initializer-decode.log and build/009c2ce0-retry/checked-table-initializer.log.

Strict scoped verification of the canonical trial fails one of one functions on byte comparison. Raw output is build/009c2ce0-retry/scoped-candidate-gate.log. The existing dump passes the normal scoped byte gate, string and constant checks, its one DIR32 operand, and body guard; this validates the retained assembly row only. Raw output is build/009c2ce0-retry/scoped-dump-gate-python.log. build.cmd was attempted first, but its Python launcher failed in this sandbox with exit 112; the identical tools/build.py entry point was run with the working interpreter. The raw launcher failures are retained separately. No source or shared header changed, so a full gate is not required for this evidence-only result.

Reproducing the bank exactly requires control over the save order outside the normal compiler-owned prologue. The tested C++ local-slot forms do not provide that control, and the tested complete intrinsic forms diverge throughout the body. Promoting an entire-body assembly transcription to C++ would overstate the recovery. Reopen with a validated indirect caller establishing return use and with a concrete source-level experiment that removes the measured frame or scheduling differences. An exact assembly dump alone would refute neither blocker. No trial improves the preferred bank, so it is not re-banked.

Exactly one blocked verdict was appended through tools/re_log.py. The final ledger-integrity check passes; its raw output is build/009c2ce0-retry/check_csv-after-verdict.log. Source hashes, the unchanged-bank assertion, canonical dump eligibility, and the corrected read/write access inventory are in build/009c2ce0-retry/verified-summary-v2.log. The exact clock endpoints and elapsed duration are in build/009c2ce0-retry/finish.receipt.txt. No Git write, synchronization, source change, or pin change was performed.
