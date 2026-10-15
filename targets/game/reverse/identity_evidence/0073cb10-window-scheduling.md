# W3DView waypoint path scheduling at 0x0073CB10

The target remains a partial reconstruction at revision d723fb900ff6674c0f0edc7e34de65f1d0a94cff. No conversion is claimed. The saved ordinary C++ candidate emits 1540 bytes and has 43 differing bytes outside the probe's relocation mask. Its scoped byte gate fails on its own instruction order. The raw gate output is build/worker7-73cb10/bank-final-byte-gate.log. These are working-tree measurements with model gpt-6.1-sol.

| Candidate | Compiled bytes | Retail bytes | Probe differences | Raw output |
| --- | ---: | ---: | ---: | --- |
| Original bank | 1546 | 1540 | 333 | build/worker7-73cb10/baseline-full.log |
| Improved bank source | 1540 | 1540 | 43 | build/worker7-73cb10/bank-final-probe.log |

The new hypothesis is that the duplicated waypoint base comes from the compiler's address expression, rather than a wrong field layout or an x87 formula. Retail computes this + curSegment * 20 and projects coordinates at owner-relative offsets +0x298, +0x2AC, +0x2C0 and +0x2D4. The Rva0073CB10Window view expresses those same projections. A reference to cameraOffset.y keeps its store ahead of the segment read. This removes the extra base calculation and the downstream EAX/ECX exchange. The hypothesis would be refuted by a different decoded record stride or coordinate projection, or by a remaining arithmetic/type difference after instruction alignment.

The remaining differing byte offsets are measured below. The mask leaves one unaligned DIR32 site at +0x3D8 for the float 0.5 operand, so the probe count is a diagnostic rather than acceptance.

| Differing offsets | Count |
| --- | ---: |
| +0x3C9 through +0x3D7 | 15 |
| +0x3DC through +0x3E3 | 8 |
| +0x414 through +0x41D | 10 |
| +0x4C6 through +0x4CF | 10 |

At +0x3C9 through +0x3E3, the candidate reads the segment and computes its base before FNSTSW and TEST. Retail performs the floating comparison and status test first. EAX is overwritten by the coordinate-X load before it is read on both successors (+0x3F0 and +0x4A2), so the different dead low word after FNSTSW is not consumed. At +0x414 through +0x41D and +0x4C6 through +0x4CF, a start.z stack store and the next coordinate-address LEA appear in the opposite order. Each pair is independent.

The reproducible diagnostic build/worker7-73cb10/reorder_diagnostic.py only permutes those three decoded instruction ranges and moves the corresponding relocation offset. Its raw output is build/worker7-73cb10/diagnostic-reorder.log. It obtains zero masked differences and zero unaligned relocation sites without changing any instruction's operands. The diagnostic binary is not a recovery and is never a gate input. The unmodified C++ source remains red.

Identity and ABI are independent of that diagnostic. The complete matched updateCameraMovements body at 0x00744530 has one relevant call at +0x110, after a four-byte milliseconds push and MOV ECX,ESI. ILT 0x000321FA decodes directly to 0x0073CB10. The method-name oracle confirms ?moveAlongWaypointPath@W3DView@@AAEXH@Z when called with the actual body RVA through the Python API. Raw evidence is build/worker7-73cb10/decode-00744530.txt and build/worker7-73cb10/oracle.log. A different instruction-aligned call route or argument setup would refute this ABI evidence.

The complete target decode has RET 4 at +0x53, +0x151, +0x17A, +0x499 and +0x601. The last RET ends at +0x604, which is the exclusive end of the 1540-byte body; INT3 padding starts there. Every conditional branch stays inside the body and there is no outgoing tail jump. The target has no EH prologue, unwind map or cleanup call. It copies only the coordinate fields of a waypoint, not its opaque name bytes. Raw evidence is build/worker7-73cb10/decode-0073cb10.txt, build/worker7-73cb10/boundary.txt and build/worker7-73cb10/callees-target.log.

The target performs float operations on X and Y and copies the third coordinate word. The complete 228-byte body at 0x0073C1B0 uses the same +0x2AC records and 20-byte stride, subtracts all three coordinate fields as floats, then adds all three back to each record. In particular, +0x7A and +0x7E operate on the saved Z value, while +0xBE through +0xD1 load, add and store record +8. This independently establishes three float coordinates at offsets 0, 4 and 8; its historical method name is not used as identity evidence. Raw evidence is build/worker7-73cb10/decode-0073c1b0.txt and build/worker7-73cb10/callees-waypoint-z-evidence.log. The record stride is proved by the decoded LEA scale, not an allocation size. The word at record +0x10 is pushed to the integer setter, whose complete body compares and stores a four-byte integer and returns with RET 4. No STL key, payload or ownership inference is made. The partial object views do not claim to reconstruct every owning class member.

| Callee evidence | Complete decoded extent | Verified contract |
| --- | --- | --- |
| ILT 0x00007E69 to reset at 0x0073C520 | 72 bytes | Unadjusted ECX receiver, no stack argument, plain RET. |
| ILT 0x000442BF to ParabolicEase at 0x00094AF0 | 185 bytes | ECX receiver, one float stack argument, ST0 result, RET 4 on all exits. The name is oracle-confirmed. |
| normAngle at 0x0073A900 | 134 bytes | ECX reference, plain RET, no EDX write. The saved static copy now declares the canonical fastcall ABI. |
| ILT 0x00012931 to the min/max helper at 0x0073A6F0 | 48 bytes | Cdecl pointer, float value, pointer; plain RET. |
| W3DView vtable 0x011217A0 slot +0x6C through ILT 0x00039220 | 58 bytes at 0x0073D880 | One integer argument, unadjusted receiver, RET 4 on both exits. |
| Limit vtable 0x0111E188 slot +0x48 through ILT 0x0003D8ED | 167 bytes at 0x006DF110 | Output pointer then optional angle pointer, RET 8. The output helper reads/writes all three float fields; the target passes the owner +0x23D8 address and a null angle pointer. |

The 49-byte limit constructor installs vtable 0x0111E188 and establishes its scalar fields through +0x28. The W3DView constructor calls that constructor on owner +0x24B8. Raw evidence is build/worker7-73cb10/decode-limit-constructor.txt and build/worker7-73cb10/decode-00745b10.txt. This vtable evidence concerns the constructed instance; it is not a claim about every possible derived runtime object. The target's imported floor call supplies an eight-byte double, receives ST0, narrows to float and uses the existing native FISTP conversion helper. GlobalData +0xA74 is independently named m_disableCameraMovement by the field-name oracle in build/worker7-73cb10/global-a74-oracle.log.

The complete callees were checked with the read-only checked_callees helper. Their inventories are in build/worker7-73cb10/callees-reset.log, callees-ease.log, callees-norm.log, callees-minmax.log, callees-limits.log, callees-virtual-setter.log and callees-limit-constructor.log. The standalone copied normalizer and min/max bodies byte-match their full extents in build/worker7-73cb10/normalizer-helper.log and minmax-helper.log. Genuine visible ease and reset definitions also match their own extents, but do not improve the target (21-ease-helper.log and 92-reset-helper.log).

The running journal build/verdict.txt names every trial and its measured result. Saved sources, full unedited probe outputs, emitted bytes, relocations and complete emitted decodes are under build/worker7-73cb10/. Rejected families include reference and value accessors, native coordinate copy/lifetime operations, helper visibility, a fully native W3DView translation unit, inherited View layout, complete limit layout, branch polarity and switch/goto forms, midpoint expression grouping, aggregate-copy statement order, split bit copies, scalar temporary scopes, argument rotation and compiler scheduling/precision switches. The native translation-unit experiment still has the same schedule residue, plus one swapped multiply operand (88-native-tu-float-overload.log).

A diagnostic compiler barrier reaches 39 probe differences, but it has no established source-level need and is not included in the saved bank (61-scheduling-barrier-control.log). No new assembly, pin or baseline change is proposed. The existing native float-to-integer assembly helper is retained unchanged.

The bank keeps every existing descriptive name. The final direct name_regression.regressions comparison reports no regression in build/worker7-73cb10/name-regression-api.log. This checkout's name_regression CLI expects Git revisions rather than source paths, so the supplied file-path invocation fails; build/worker7-73cb10/name-regression.log retains that failure. The original EA comment tokens, including the disabled lines and debug block, are retained and checked in build/worker7-73cb10/ea-comments-check.json.

The unchanged callee spellings reset@Rva0073B8C0 and updateMinMax are contradicted by the name oracle. Their decoded targets and ABIs are independently established, but their historical names are not new identity claims. A landing must resolve any applicable name-guard refusal without changing shared policy or inventing an identity. The target method name itself is confirmed.

Reopen for an ordinary C++ structure that delays the common base computation until after the floating status test and places the two coordinate-address LEAs before their independent Z stores. The current residue is instruction scheduling; a new field-offset, frame-size or generic register-permutation experiment needs fresh decoded evidence. The diagnostic reordering claim is refuted if any byte outside these permutations still differs after proper relocation alignment.

Final preservation uses targets/game/reverse/attempts/0x0073cb10.cpp. Its probe at that final path reproduces the same size and difference count. check_csv, class_gate and the direct name-regression comparison pass; the source byte gate remains red. Raw outputs are build/worker7-73cb10/check-csv-final.log, build/worker7-73cb10/class-gate-final.log, build/worker7-73cb10/bank-final-name-regression.log, build/worker7-73cb10/bank-final-probe.log and build/worker7-73cb10/bank-final-byte-gate.log. Exactly one partial verdict is appended. The source ledger and pins are unchanged.

The default Git whitespace check flags the CRLF terminator written by re_log.py on the appended verdict row. The check with CRLF recognized as a line ending passes; neither the log nor Git configuration is rewritten. Raw outputs are build/worker7-73cb10/diff-check.log and build/worker7-73cb10/diff-check-crlf.log.
