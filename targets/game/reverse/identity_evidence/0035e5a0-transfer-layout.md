# Recovery at 0x0035E5A0

The 284-byte body is recovered as `Rva0035E710Owner::bfmeDoZN`, retaining the bank's opaque owner and descriptive identifiers. The tested base is `0e5229fcf0270d88c23fc876d989391260ec80e1`. No semantic parser or engine-class identity is asserted. Retail's ILT oracle contradicts this invented decoration; its address-derived owner is a placeholder under `ilt_guard.py`, rather than a claim to EA's name. There is no name row for this address in `ea_evidence.csv`.

## Boundary and calling convention

The entry at 0x0035E5A0 is the destination of the decoded ILT jump at 0x0000CEC8. The complete 284-byte decode has internal conditional branches only, no tail jumps, and two epilogues ending in `ret 12` at offsets +0x101 and +0x119. The second return ends at 0x0035E6BC, followed by `int3` padding. All paths reach one of these returns. Incoming ECX is retained in EBX and supplies receiver-relative accesses and calls, so this is a member with three pointer-sized stack arguments. There is no hidden return storage or receiver adjustment at entry.

The complete matched callers at 0x0035E710 (56 bytes) and 0x0035C9C0 (518 bytes) call ILT 0x0000CEC8 with the original receiver in ECX. The former pushes the chosen or fallback slot, the address of the predecessor link, then the source owner. The latter pushes its destination slot, a saved predecessor-link address, then the source owner. Neither caller consumes EAX. Return paths in the target leave different incidental pointer values in EAX, consistent with the existing void declaration.

Raw complete decodes, including padding after each extent, are in build/0035e5a0-finish/retail-decoded.txt. Checked callee inventories are in build/0035e5a0-finish/target-callees.log, build/0035e5a0-finish/walk-callees.log and build/0035e5a0-finish/link-callees.log.

## Layout and helper evidence

The link has a next pointer at +0, a 32-bit index at +4 and a 32-bit ordinal at +8. The source owner has its record-table pointer at +0x18. Two LEAs multiply the index by 20. The record count is a signed 16-bit field at +0x0E (`movsx`), and the first entry pointer is at +0x10. The loop follows entry +0 exactly count minus ordinal times when that difference is positive. Entry +8 and +0x0C are two independently retained link slots. Their former pointer values are passed by address to the two traversal helpers. The receiver has corresponding record-table and fallback-head offsets at +0x18, +4 and +8. No container key or payload value type is inferred from an allocation size or a template name.

| Actual call | Complete body | ABI and accesses |
|---|---|---|
| +0x65 to ILT 0x0002792B | 0x0035CE60, 95 bytes | ECX is receiver +0x0C. Stack arguments are source +0x0C and the 32-bit index. Both exits use `ret 8`; EAX is the signed destination index or -1. The body indexes 20-byte records through subobject +0x0C, moves their +0x10 entry pointer and calls the source release helper. |
| +0xA7 to ILT 0x00028650 | 0x0035C9C0, 518 bytes | Original receiver in ECX, then source owner, address of the saved first link and original entry +8 slot. Both exits use `ret 12`. The body stores predecessor-link addresses as four-byte values and passes each saved address back to 0x0035E5A0; this proves the mutable pointer-slot indirection independently of the existing declaration. |
| +0xD6 to ILT 0x0000D2BA | 0x0035D9B0, 662 bytes | Original receiver in ECX, then source owner, address of the saved second link and original entry +0x0C slot. Both exits use `ret 12`. It reads through each saved link address before reading node +4 and writing node +4/+8; its secondary tables are reached at owner +0x2C. It rewrites both the caller's link and the destination slot. |

Each extent was completely decoded and passed `checked_callees.py`; none has outgoing conditional branches or tail jumps. The helper logs are build/0035e5a0-finish/move-callees.log, build/0035e5a0-finish/link-callees.log and build/0035e5a0-finish/relink-callees.log. None of these bodies has an indirect or virtual call. The recovered target constructs no owning value and has no exception frame or unwind cleanup. The traversal callees' existing internal deque implementations are not reimplemented or retyped here.

The source copies the canonical method declarations from `BfmeConv1850.cpp` and `Rva0035E510LinkEAT.cpp` and the target declaration shared by that file and `Rva0035E710LinkWalk.cpp`. Only opaque receiver declarations are needed: no helper definitions, inheritance layout or shared headers are copied into the new translation unit. No registered shared header exists for these receiver classes. The explicit owner and entry views describe the decoded offsets only. No new pins or globals are introduced.

## Compiler experiments

The saved bank measured 284 bytes with 52 non-relocation differences. Explicit link ordinal and index temporaries, followed by a count load before the entry load, reduced this to 24 differences. A separate index temporary for the transfer call reduced it to 10. Pairing each entry member load with its zero store inside the entry's scope produced exact bytes. Moving these operations through the retained slot pointers instead left six differences, while copying the second value through an extra temporary left 26. This refutes the previous diagnosis that the whole residue was inaccessible register allocation.

Every trial source and unedited probe output is retained under build/0035e5a0-finish/. The baseline is baseline-probe.log; improvements are 01-explicit-input-order.log and 06-move-index-temp.log. Both 18-field-extraction-pairs.log and 20-field-extraction-late-addresses.log are exact masked probes. production-probe.log reproduces exact bytes from the final standalone source without helper definitions. The generated register/store/copy alternatives and their measurements are in family-choices.json, family-search.json and family-search.log in that same directory. The running measurements are also in build/verdict.txt.

The ABI and layout account would be refuted by a decoded caller passing values instead of predecessor-link addresses, a helper reading a wider or differently offset field, an unexamined branch leaving one of the claimed extents, or a relocation resolving to a different body. A strict scoped build is required in addition to the masked probe before collection.

## Verification and collection

`add_match.py` verified the new row through the strict scoped build, resolved all three calls, retired the dump row with a tombstone and removed the obsolete bank. The explicit Git Bash invocation of `build.sh` independently passed source claims, the function comparison, reference verification and the body guard. Raw outputs are build/0035e5a0-finish/add-match.log and build/0035e5a0-finish/scoped-gate.log. No header or shim changed, so this change does not require a full gate.

`find_declared_unmatched.py --fail`, `class_gate.py`, `name_oracle.py --check`, `pin_consistency.py --check` and `identity_guard.py` passed. The current `name_regression.py` command accepts Git revisions rather than file arguments; its file-pair regression function was applied directly to the original bank and final source and returned no findings. All non-preprocessor identifiers from the bank remain in the source. Raw outputs are build/0035e5a0-finish/declared-unmatched.log, build/0035e5a0-finish/class-gate.log, build/0035e5a0-finish/name-oracle-source.log, build/0035e5a0-finish/pin-consistency.log, build/0035e5a0-finish/identity-guard.log and build/0035e5a0-finish/name-regression-api.log.

The initial `check_csv.py` passed. The final invocation cannot complete before collection because its tracked-file inventory still includes the removed bank and excludes the unstaged new source. It raises `FileNotFoundError` while opening the removed bank. The raw output is build/0035e5a0-finish/check-csv-final.log. Stage the source, evidence note, ledger replacement, tombstone, attempt record and bank deletion together, then rerun the normal staged checks. Git writes were unavailable in this worker; the verified conversion is retained unchanged for collection.
