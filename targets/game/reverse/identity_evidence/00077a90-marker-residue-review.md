# 0x00077A90 marker residue review

The saved bank still compiles to 373 bytes with zero differences outside 18 relocation operands. This is not a C++ recovery: the bank supplies two complete 27-byte marker blocks with inline assembly, and its strict scoped byte gate fails on eight unresolved STLport names. The bank, ledger and pins are unchanged. The tested revision is `62a114d84525e2c935cb8f4a26e1d0929c242f52`; the model is `gpt-6.1-sol`.

## Hypothesis and stopping condition

The finish assignment suggested a remaining compiler-shape problem in a bank screened as exact. This review tested whether that zero-difference result instead depended on assembly and unresolved call bindings. A complete native source or compiler mechanism producing the marker intervals within the accepted conversion rules would refute the marker blocker. The complete decode and the bank itself confirm that its exact result includes assembly-supplied discarded register assignments. There is no non-relocation residue on which to base a new register, temporary, declaration-order, helper-visibility or branch-shape trial.

All eight prior target verdicts and all three immutable source archives were inspected. The archives contain the old skeleton and the preferred complete interior, both with assembly markers. The recorded native-container, named-pair and local-lifetime trials already recovered the interior. The earlier marker-free and plain-C++ marker trials were rejected, and symbolic markers with unsigned-long bindings retained assembly. Those earlier measurements are history, not new results from this run; their scratch sources and raw outputs are absent from this checkout. They were not rerun. No new source experiment or closer candidate was justified. This meets the assignment's early stopping condition for an assembly marker blocker, rather than exhausting the budget on repeated shapes.

## Current measurements

The unedited probe output is build/77a90-20261015/probe-bank.log. Its child process exited zero, as recorded in probe-bank.json; the first log-display wrapper failed only after saving that output because its console could not encode a replacement character. The complete scoped gate output is build/77a90-20261015/scoped-bank-gate.log. The gate used the existing bank as an in-memory candidate row through the normal `build.verify_functions` implementation, without changing the ledger or symbol map.

The strict gate leaves eleven unresolved four-byte call operands beginning at +0x003F, +0x004F, +0x00C4, +0x00D0, +0x00E4, +0x00FA, +0x0106, +0x011A, +0x0130, +0x013C and +0x0150. Every remaining concrete byte difference lies inside these operands. The marker audit checks this directly against the gate's full target and compiled byte strings and verifies both marker intervals independently. Raw output is build/77a90-20261015/marker-audit-v2.log.

| Retail offsets, inclusive | Exact bytes supplied by assembly |
|---|---|
| +0x0009 through +0x0023 | `50 b8 cc cd ce cf b8 9f 7a 47 00 b8 00 00 00 00 b8 00 00 00 00 b8 cc cd ce cf 58` |
| +0x0154 through +0x016E | `50 b8 cc cd ce cf b8 9f 7a 47 00 b8 00 00 00 00 b8 00 00 00 00 b8 cb cc cd ce 58` |

Both blocks save EAX, load five immediates into it, then restore EAX. None of those assigned values is consumed before being overwritten or restored. The self-address immediate is literal in the bank rather than an object relocation. Moving this stream into a macro, helper or symbolic assembly spelling would retain the rejected lift.

## Boundaries, ABI and value fields

Fresh full decoding is retained in build/77a90-20261015/decoded-full.log, with individual checked-callee logs named checked-XXXXXXXX.log in that folder. All requested extents decoded completely. The target ends at 0x00077C05 after its sole `ret 4` at +0x0172 and is followed by `int3` padding. Its branch at +0x0061 reaches the common exit marker at +0x0154. It has no outgoing branch, tail jump, indirect call, virtual call or EH registration. The receiver is spilled at frame offset -0x60 and never read again.

The complete 502-byte caller at 0x00078640 calls the decoded five-byte ILT thunk at 0x00043897, which jumps to this target. Its instruction-aligned call at caller +0x01D6 supplies the address of an eight-byte request as the stack argument and a separate byte-sized local's address in ECX. It does not consume the target's return value. This supports the bank's existing address-derived member declaration, not a semantic owner identity. The caller's constructor unwind ownership is outside this review; no recovery of that constructor is claimed.

The target reads request fields +0 and +4. Its pointed-to record supplies dwords at +8, +0x10, +0x14, +0x1C, +0x28 and +0x2C; the target writes a pointer at +0x24. The count at +0x28 is scaled by four, and +0x2C is an array index. The complete helpers at 0x0006B500 and 0x0006B520 each dereference both incoming reference arguments and write destination +0 and +4. The complete conversion helpers at 0x0006C5A0 and 0x0006C5C0 copy exactly those two fields. The actual insertion paths through 0x00076F80 and 0x00077040 reach node insertion at 0x000768D0 and 0x000769B0, whose two allocation paths call complete value helpers at 0x00072390 and 0x000723B0. Those helpers copy source +0 and +4 after a null destination check. This independently verifies the two-word values without inferring payloads from allocation size.

The complete lookup and insertion bodies, including both result paths, agree with unsigned comparisons and hidden return storage. Their wrappers return the output address in EAX and clean eight stack bytes. The end helper writes one word through hidden storage and cleans four stack bytes. The iterator comparison consumes one word and returns a Boolean that the target reads through AL. Complete comparison and array-allocation wrapper decoding is in build/77a90-20261015/extra-decode.log. The inspected pair and value helpers have no EH registration or destructor calls. The canonical STLport pair, map and set declarations were read; no canonical declaration or shared header was changed.

Current oracle checks through the Python API contradict the bank's five real unsigned-int spellings and confirm all five mechanically derived unsigned-long spellings at 0x0006B500, 0x0006C5C0, 0x00072510, 0x000762B0 and 0x00077510. They are retained verbatim in marker-audit-v2.log. The first audit's mechanically incomplete decorations are preserved in marker-audit.log and marker_audit-v1.py; only the corrected second audit supports this conclusion. No new spelling was compiled, pinned or claimed as a new identity. Oracle confirmation does not establish the keys' semantic meaning or the record's owner.

## Checks and handoff

Initial CSV validation, pin consistency and the bank's class gate pass. Their raw outputs are build/77a90-20261015/check-csv-initial.log, build/77a90-20261015/pin-consistency.log and build/77a90-20261015/class-gate-bank.log. CSV validation after recording the verdict also passes, with raw output in build/77a90-20261015/check-csv-after-verdict.log. The whitespace check passes when CRLF line endings are recognized; raw output is build/77a90-20261015/diff-check-crlf.log. No source, shared header or shim changed, so this evidence-only outcome requires no full gate. No Git index writes or synchronization were performed.

The preserved body is targets/game/reverse/attempts/0x00077a90.cpp, with an exact scratch snapshot in build/77a90-20261015/bank-original.cpp. The blocker remains `codegen-order/unrepresentable-marker-stream`, with unresolved and contradicted bindings also present in the unchanged bank. Reopening needs authentic source or a concrete accepted compiler mechanism for both complete marker intervals; correcting the already-tested unsigned-long bindings alone does not resolve it. Exactly one blocked verdict is recorded for this run, with no re-bank because no closer body was produced.
