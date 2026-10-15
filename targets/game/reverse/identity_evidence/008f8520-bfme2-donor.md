# Rectangular fill donor experiment

The tested revision is 9f335a9ec9ff012c5103195540fa82ccc3e7877e. The new hypothesis was that Open BFME 2 donor Code/GameEngine/Source/Common/RTS/ShroudManagerDataDoSmallFill.cpp at game.dat 0x0073AAE0 supplies the missing debug expression and iterator lifetime. This would be refuted if those source forms retained the register and stack differences after adapting the BFME 1 fields and calls. The measurements refute a direct port as an exact recovery.

The complete BFME 1 decode ends with RET 12 at +0x2DB. The following two bytes are INT3 and the next entry is +0x2E0. The decoded matched updateCellsTouched caller pushes radius, Y and X before setting ECX to its PartitionData receiver and calling this entry. This supports a member taking three floats. It does not justify giving a second body the doSmallFill identity already used at 0x008F83F0. The bank's spelling is retained only for reproducing its emitted symbol.

The target reads grid origin at +4/+8, cell size at +0x1C, scale at +0x20, width/height at +0x24/+0x28 and cell storage at +0x2C. The cell stride is 0x68 and the intersection stride is 0x10. The matched getCellRange implementation supplies the same bounds and clamped range operations. The donor's 0xA8 cell stride and three debug-context arguments do not apply: BFME 1 pushes two arguments at virtual slot +0x6C. Its string-return virtual receives hidden storage, and the two conditional temporaries are released at +0x146 and +0x15C. The EH map has two guarded cleanup states. Complete target, constructor, releaseBuffer and debug helper decodes are retained under build/x15/8f8520/; the checked call inventories use the same extents.

| Measured source | Emitted bytes | Non-relocation differences | First difference |
|---|---:|---:|---|
| Saved body after removing the stale StringBase specialization | 719 | 506 | +0x1C |
| Donor debug expression | 739 | 606 | +0x19 |
| Donor row helper and outer loop | 744 | 559 | +0x1A |
| Ordinary C conversion with /QIfist | 707 | 468 | +0x17 |
| Grouped coordinate declarations | 732 | 595 | +0x1A |
| Stream operators | 744 | 587 | +0x17 |

Reference returns, a unified debug view, an inline member name writer, backlink pointer typing, name-virtual constness and direct floor spelling reproduce an already measured donor shape. Two unchanged experiments close the corresponding register or x87 lever. The EH search exhausted six trials without improvement; the family search exhausted four. Ordinary C changes the frame and conversion spill sequence and is not evidence for removing the x87 helper from the saved reconstruction.

The original preferred bank remains unchanged. The compiling baseline and every donor trial remain under build/x15/8f8520/. Raw probe outputs are build/x15/8f-baseline.log, build/x15/8f-donor-debug.log, build/x15/8f-donor-outer.log, build/x15/8f-donor-plain.log, build/x15/8f-grouped-coordinates.log and build/x15/8f-debug-operators.log. Search receipts are build/x15/8f-eh-search-utf8.log and build/x15/8f-family-search.log. The unresolved source differences are the initial register allocation, argument-slot reuse and loop allocation. Reopening requires independently supported lifetime or declaration evidence that changes those measured instructions; an instruction-shape score alone is insufficient.
