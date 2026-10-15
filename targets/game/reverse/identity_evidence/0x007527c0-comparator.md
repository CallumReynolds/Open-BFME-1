# Opaque comparator at 0x007527C0

The recovered symbol remains `?method@Rva007527C0@@QBE_NABU1@@Z`. The address-derived owner and the bank's existing field and helper names are retained. This recovery establishes an instruction-level layout and ABI, without attributing an original class or source identity. The EA evidence ledger has no row for this address. The decoded ILT entry at 0x0001D4CB jumps directly to this body.

## Boundary and ABI

The complete retail extent is 485 bytes, from 0x007527C0 through the three-byte `ret 4` at 0x007529A2, followed by `int3` padding. Every conditional branch stays inside the extent. There are no outgoing tail jumps, indirect calls, virtual calls, exception handlers, constructors or container operations. All eleven return sites clean one four-byte stack argument. ECX addresses the left record and the stack argument addresses the right record. The result is consumed and produced as a boolean in AL; no hidden result storage or receiver adjustment appears.

The left and right records have pointer-shaped fields at +0x00 and +0x04 and a signed dword at +0x08. The first pointer orders in descending unsigned address order; the remaining pointer comparisons use ascending unsigned order. The signed dword uses `setl`. The +0x04 pointee has another pointee at +0x08 whose float at +0x1F8 is compared with x87 instructions, plus a state pointer at +0x14. Its two records start at +0xDC with a stride of +0x1C. Each record reads a pointer at +0x00, a float at +0x04, signed dwords at +0x10 and +0x14, and a byte at +0x18. The byte's return path explicitly converts nonzero to true. Padding and field names make no further ownership or semantic claims.

The call at target +0x8C goes through ILT 0x0001938A to the complete 128-byte `Q4Sort00751F50Record::compare` body at 0x00751F50. Its ECX is the left nested record; its three stack arguments are the right nested record, the left signed-dword output address, and the right signed-dword output address. Both return paths execute `ret 12`, with the boolean in AL. The helper initializes both output dwords, compares the state pointers at +0x14, reads the drawable pointers at +0x08, computes signed remainders, and converts `ready()` to bool. Its real source is copied as an inline, non-inlined definition so it supplies compiler visibility without adding another strong out-of-line definition.

The helper's complete callees were decoded as well: `Drawable::getID` at 0x004116B0 is the seven-byte dword getter from +0x100, and `Rva00765AC0::ready` at 0x00765AC0 is the 38-byte ten-slot scan with byte and bit fallback returns. The declarations match the existing helper translation unit. No registered shared class declaration applies to these local views. The direct-body ILT oracle confirms `Drawable::getID`; the address-derived comparator, helper and ready names remain placeholders, with no original-name claim. No independently named caller of the target has been established.

These conclusions would be refuted by an outgoing edge outside the claimed body, an independently decoded caller requiring different stack arguments or return storage, a helper path accessing a different field width or offset, or relocation verification resolving the call or zero constants to different targets.

## Compiler experiments

The starting bank reproduced as 481 bytes with 130 differing non-relocation bytes, plus four missing bytes. Its first structural divergence is at +0xCE: retail preserves the right record base in the incoming argument slot, keeps the left base in EDI, and later reloads separate bases for the float expressions. The bank discards the saved bases. This gives a new lifetime hypothesis rather than an unknown-owner blocker.

| Experiment | Emitted bytes | Differing non-relocation bytes | Interpretation |
| --- | ---: | ---: | --- |
| Cached bases also used by the loop, barrier retained | 523 | 450 | Extra pointer-difference induction and frame storage reject this loop spelling. |
| Cached final-comparison bases with external helper declaration | 515 | 456 | Opaque helper escape information prevents the required output-slot reuse. |
| Authentic helper visible, cached final bases, loop uses member reads | 485 | 120 | Helper visibility restores the frame and saved-base lifetime. |
| Saved bases declared left first | 485 | 115 | Declaration order assigns the saved bases to the appropriate locations. |
| Separate float-tail bases, saved bases declared left first | 485 | 6 | Explicit tail temporaries recover the early right-base reload and all float scheduling. |
| Initialize the loop counter before the saved bases | 485 | 0 | Restores the adjacent XOR and spill order at +0xCC and +0xCE. |

Reversing the final pointer comparison spelling made no improvement. Removing the barrier emitted 475 bytes and lost the required reloads. Replacing the bank's external zero with the plain literal `0.0f` preserves the exact body and emits the already-recorded `__real@00000000` constant. The retained barrier expresses measured reconstruction shaping and claims no original source spelling.

## Raw evidence and validation

The tested base revision is `07a219def195b93798ffefa35aef97d473559f40`. Complete retail decoding and compiler commands are retained in build/worker-007527c0/retail-decode.log. Checked inventories are in build/worker-007527c0/checked-target.log, build/worker-007527c0/checked-helper.log, build/worker-007527c0/checked-getid.log and build/worker-007527c0/checked-ready.log. Each trial source and its unedited probe output are retained together under build/worker-007527c0/; the running measurements are in build/verdict.txt.

The final source and copied helper both probe exact at their independently verified extents. build/worker-007527c0/metadata-and-object.log retains complete emitted disassembly, aligned relocation inventories, direct-body oracle results and the bank-to-source name regression API result. The CLI named `name_regression.py OLD NEW` expects Git revisions in this checkout, so the file comparison uses its `regressions` function directly and reports no name regressions.

The scoped byte gate passes in build/worker-007527c0/add-match.log and build/worker-007527c0/scoped-byte-gate-bash.log, including the two float constant references, recorded DIR32 identities and body guard. The explicit Git Bash entry point was used after the batch entry point could not find an installed Python through its launcher. Pin consistency passes in build/worker-007527c0/final-pins.log. The declaration and class checks pass in build/worker-007527c0/final-declarations.log and build/worker-007527c0/final-class.log. The initial CSV check passed before implementation. The final check in build/worker-007527c0/final-csv.log raises `FileNotFoundError` because its index-derived bank inventory still names the deleted bank. The new source is also untracked until collection. These are consequences of leaving Git unchanged in the worker, not a passing final CSV result. Collection must stage the source, ledger transaction, evidence and bank deletion together and rerun the CSV and index-dependent hooks. No header or shim changed, so this source-only conversion does not require a full gate.

build/worker-007527c0/transaction-verified.log confirms that the ledger changed only the assigned row, all other ledger bytes are preserved, the tombstone is an append, the symbol ledger has no Git diff and retains CRLF endings, and the bank removal followed the successful byte gate. No source outside the generated dump names the retired `?d_007527c0@@YAXXZ`, so an address-only compatibility pin is unnecessary.
