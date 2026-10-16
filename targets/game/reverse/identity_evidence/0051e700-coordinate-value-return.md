# Partial reconstruction of RVA 0x0051E700

Do not promote this body as an exact recovery. The retained candidate has the complete retail instruction forms and aligned relocations, but its register encodings still differ. Reopen with evidence that changes the cached mode and key lifetimes while retaining the decoded argument and field widths, or a concrete source explanation for the remaining EAX/ECX choices. The existing bank names are retained for continuity; their original decorations are not established.

## Result and retained source

The tested revision is 8268588a5ffd8fc12db96dff101f6d21f050fe7b. The model is gpt-6.1-sol. The preferred body is targets/game/reverse/attempts/0x0051e700.cpp. It is a partial reconstruction and contributes no converted bytes. All trial sources, unedited probe output, decoded bodies, scoped gate output and the running verdict are retained under build/apt-input-0051e700 and build/verdict.txt.

Returning the decoded coordinates by value removes the unnecessary EDI save and restore and restores the two retail CDQ absolute-value idioms. An integer-valued conditional key guard then restores call setup scheduling. The helper uses the canonical ICoord2D declaration from Lib/BaseType.h and disappears completely through inlining. This is a local source construction choice, not evidence that retail had an out-of-line coordinate helper or that WindowMsgData was a struct. Its two fields are assigned from the decoded low and high unsigned halves of the incoming DWORD.

The manual image-address guard accesses are replaced by native function-local static initialization. The compiler emits the witnessed shared guard bits and the two initial coordinate stores. This adds relocation records without changing the instruction forms or reducing the measured residue. No image address literal or new pin is introduced by the preferred bank.

| Candidate | Emitted bytes | Masked differences | Differences with independently bound addresses | Instruction forms |
|---|---:|---:|---:|---|
| Original shape with corrected literals | 405 | 144 | 156 | Extra EDI preservation and call scheduling changes |
| Preferred conditional form | 405 | 20 | 20 | All forms match; every relocation field aligns |
| Lower masked-count alternative | 405 | 19 | 31 | Three relocation fields drift; one string reference is unverifiable |

The preferred form passes the official independent check for all three string references. Its official scoped byte comparison fails. The lower masked-count alternative is not preferred because its misplaced relocation fields hide instruction and address differences; the official string check rejects its EscapeKeyPressed reference. Independent semantic address binding is diagnostic and does not replace the official gate. Raw output: build/apt-input-0051e700/166-bank-candidate.strict-gate.log, build/apt-input-0051e700/167-drift-alternative.strict-gate.log and build/apt-input-0051e700/semantic-linked-comparison.json.

## Literal correction

The previous bank had three incorrect literals. Retail VA 0x01106274 contains HideCredits, VA 0x011063E4 contains EscapeKeyPressed and VA 0x011063D4 contains ShowMainMenu. The former MainMenuLevel, MainMenuContinueCampaign and BlinkBattleSchoolOff strings were not validated by the masked probe. The preferred bank uses the actual NUL-terminated retail bytes. Raw reads are in build/apt-input-0051e700/retail-literals.txt; the original bank fails the official string check in build/apt-input-0051e700/00-bank.strict-gate.log.

## Boundary, identity and ABI evidence

The entire 405-byte extent decodes. Every conditional branch and local jump stays inside it. There are five RET 12 paths, including the final epilogue at offsets +0x192 through +0x194. No target EH registration, unwind cleanup or container value constructor is present. Raw decode: build/apt-input-0051e700/decode-0051e700.txt. The checked inventory is build/apt-input-0051e700/checked-target.log.

The primary vtable at VA 0x011061C4 has slot 1 pointing through ILT RVA 0x000060A0 to this body. Its pinned constructor at RVA 0x0051F3A0 installs that vtable for the MainMenu APT screen. This proves the screen association and slot route, not the bank method decoration. The target and its callee names were checked through the oracle API with body RVAs, avoiding the command-line address ambiguity. The bank input decoration and the other tested input decorations are contradicted. No name correction or new identity pin is submitted. A future exact production promotion must resolve naming under the repository address-token rule. Raw evidence: build/apt-input-0051e700/vtable.log and build/apt-input-0051e700/eligibility-and-names.log.

The complete input caller at RVA 0x0047CA30 pushes state, data and message in that order, loads the window receiver into ECX and calls ILT RVA 0x00003148. Its complete 22-byte target at RVA 0x004791F0 forwards the unadjusted receiver, or its optional +0x1DC delegate, by tail jump through virtual slot +4. Together with RET 12 and the target DWORD EAX returns, this establishes a three-DWORD thiscall input ABI without hidden return storage. It does not distinguish an original int return decoration from the protocol enum. Raw decoded callers and checked inventories are build/apt-input-0051e700/decode-0047ca30.txt, build/apt-input-0051e700/decode-004791f0.txt, build/apt-input-0051e700/checked-input-caller.log and build/apt-input-0051e700/checked-input-dispatch.log.

All three direct callee bodies and their ILT jumps were decoded in full. The APT helper route is ILT RVA 0x00015235 to body RVA 0x004675F0, whose RET 32 consumes eight DWORD arguments and whose return is a pointer in EAX. The target ignores that return. Its first shared PUSH 0 at +0x53 belongs to the selected eight-argument APT call or the one-argument BattleSchool call, depending on the branch. The BattleSchool route is ILT RVA 0x00004985 to body RVA 0x0051DE00, whose RET 4 consumes the unused zero argument and whose complete body writes receiver +0x264. The Mouse route is ILT RVA 0x0003D578 to body RVA 0x005A4B50, whose RET 4 consumes the visibility argument. That body separately forwards two DWORDs through virtual slot +0x5C: visibility and the cursor-state pointer at receiver +0x4DA1. The dynamic implementation of that virtual slot is not claimed here. The existing matched helper sources were read directly; no helper identity was inferred solely from a donor name.

Raw callee decodes are build/apt-input-0051e700/decode-004675f0.txt, build/apt-input-0051e700/decode-0051de00.txt and build/apt-input-0051e700/decode-005a4b50.txt. Their checked inventories are checked-path.log, checked-battleschool.log and checked-mouse.log in the same directory. Pin consistency passes without pin changes.

## Every remaining difference

The independently bound preferred body differs at exactly these byte offsets: +0x004, +0x00A, +0x015, +0x01B, +0x030, +0x033, +0x03B, +0x044, +0x048, +0x04C, +0x051, +0x080, +0x0BB, +0x0C1, +0x0D0, +0x0D4, +0x0D9, +0x0DE, +0x0E2, +0x145. The complete byte-to-instruction map is build/apt-input-0051e700/166-bank-candidate.differences.json.

| Offsets | Retail and candidate difference |
|---|---|
| +0x004, +0x00A, +0x048, +0x04C, +0x051, +0x080, +0x145 | The cached mode occupies retail EAX and candidate ECX. Every comparison retains its width, value and branch destination. |
| +0x015, +0x01B, +0x03B, +0x044, +0x0BB, +0x0C1 | The short-lived active, state and automatic flag bytes occupy retail CL and candidate AL. |
| +0x030, +0x033 | The zero-extended key and its decrement occupy retail ECX and candidate EAX. |
| +0x0D0, +0x0D4, +0x0D9 | The later message load and comparisons occupy retail ECX and candidate EAX. |
| +0x0DE, +0x0E2 | The packed-coordinate load and initial copy exchange EAX and ECX. The subsequent AND, SHR, guards, absolute values and state updates match. |

## Rejected hypotheses and verification limits

The complete trial manifest is build/apt-input-0051e700/trials.jsonl. It records the hypothesis, refutation condition, measurement and raw output path for each preserved source. Definitions and scope changes, state and level accessors, parameter copies, native byte views, scalar and aggregate construction, reference and output helpers, complete matched callee visibility, argument defaults, absolute-value implementations and focused optimizer settings were tested. None closes the remaining register mirror in the preferred form. The earlier packed-argument, outer switch/goto, two-base layout and frame-array experiments were not used as recovery evidence.

The initial theory that intrinsic abs itself forced a callee-saved coordinate was refuted by the standalone decoded predicate in build/apt-input-0051e700/diagnostic.disasm.txt. Ordinary local aggregate construction and output parameters retained EDI; returning the coordinate aggregate by value removed it. An arithmetic abs spelling lowered the masked difference count but emitted different operations, so it was not selected. Removing portions of the function in diagnostic trials 80 through 84 was explicitly non-equivalent and those sources are not bank candidates.

An independent scratch interpreter compared retail and the preferred candidate over 18432 sampled combinations of modes, flags, messages, packed positions, state bits and guard states. Returns, changed fields, external-call arguments and stack cleanup agreed. Calls were stubbed, so this is a diagnostic check rather than a proof for arbitrary callbacks or a substitute for byte equality. Raw result: build/apt-input-0051e700/semantic-state-comparison.json. The interpreter and its inputs remain in the same scratch directory.

The scoped byte gate remains the blocker. The original method decoration remains unproven and contradicted by the oracle. No full gate is required for this bank-only update, and no source under game/, shared header, policy, tool, ledger row or symbol pin is changed.

The stored bank was probed again after re_log.py wrote it. It retains the measured residue and passes all three official string checks. Final raw output is build/apt-input-0051e700/bank-final.probe.log and build/apt-input-0051e700/bank-final.strict-gate.log. The CSV check, pin consistency, class gate and direct source-text name regression comparison pass. Their receipts are build/apt-input-0051e700/check_csv-final.log, build/apt-input-0051e700/pin-consistency.log, build/apt-input-0051e700/class_gate-final.log and build/apt-input-0051e700/handoff-checks.json. The declaration checker refuses the scratch source because it has no matched ledger rows; no whitelist or baseline is changed to make a bank qualify as production source. Exactly one partial verdict was appended.
