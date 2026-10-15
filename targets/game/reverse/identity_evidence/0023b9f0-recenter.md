# Slot recentering at 0x0023B9F0

The recovered body retains the bank's address-derived identity, `BfmeHordeContainRoster::rva0023B9F0`. This identifies a translation-unit layout view, not a proven retail class or method name. EA evidence assigns this address to HordeContain.cpp but supplies no method name. No Zero Hour body was ported.

## Boundary and ABI

The complete target spans 0x0023B9F0 through 0x0023BB30 inclusive. Its sole return is at +0x118. The block at +0x119 copies the selected position and ends with the internal jump at +0x13F to +0xD3. Every conditional branch remains inside the extent; the next byte at +0x141 begins padding. The body has no exception registration, indirect call, virtual call, allocation, destructor or external tail jump. The stack frame is twelve bytes and the epilogue restores all four saved registers before a plain `ret`.

The complete 828-byte caller at 0x00245010 calls ILT 0x0001D9D0 at +0x326 after loading ECX from its saved receiver. It pushes no argument for this call and does not consume a return value. The five-byte ILT jumps directly to 0x0023B9F0. This establishes a no-argument, void thiscall with no receiver adjustment or hidden result storage.

Raw evidence: build/target-0023b9f0/decoded.log, build/target-0023b9f0/target-callees.log and build/target-0023b9f0/caller-callees.log. The decoded listing includes the target plus padding, the complete caller and both relevant ILTs. It also includes the complete matched name-test body at 0x00242630, which independently uses the same owner and slot-vector offsets.

## Layout and value evidence

The target loads the owner from receiver+4, traverses the owner's pointer vector at +0x224 and +0x228, and passes each entry+4 as a four-byte string reference. Canonical ascii_string.h supplies that declaration. Entry+8 and entry+0xC are the inner vector bounds. Their difference is divided by twelve. `BfmeHordeInner12` retains three opaque words because this target consumes only the stride and makes no numeric claim about that payload.

The receiver's slot bounds are +0x12C and +0x130, with sixteen-byte iterator steps. The target performs floating-point additions and subtractions only on slot+4 and slot+8. The complete caller at 0x00245010 reads inner values with twelve-byte strides, writes the slot's leading key from the roster entry's leading dword, writes floating-point positions at +4 and +8, and transfers the third position word to +0xC. The complete 0x00242630 body compares the leading slot and entry words against an object identifier. The source therefore retains an opaque unsigned key and a float pair at +4; this recovery does not use the trailing float.

The actual value-construction helper called by 0x00245010 is ILT 0x0001476D to 0x00233490. All 35 bytes were decoded: it takes destination and source pointers on the stack, skips a null destination, copies exactly the four source dwords at +0, +4, +8 and +0xC to the same destination offsets, and returns with caller cleanup. It has no hidden allocation, ownership transfer or destructor. The actual default constructor is ILT 0x00033D39 to 0x00233C80; all sixteen bytes write zero at +0 and +0xC and leave the middle pair alone. The separate 31-byte copy constructor at 0x00232470 also copies all four words and returns its destination with `ret 4`; it is corroboration, not a substitute for decoding the helper the caller actually uses.

Raw helper evidence: build/target-0023b9f0/decoded.log, build/target-0023b9f0/value-construct-callees.log, build/target-0023b9f0/record-ctor-callees.log and build/target-0023b9f0/record-copy-callees.log. This layout would be refuted by a decoded access outside these records, a different helper edge at the cited call sites, or an additional field copied by the complete helper.

## Callee identity and relocation

The target's sole direct call is +0x40 to ILT 0x00028560, which jumps to 0x00137E80. Its ECX is the singleton recorded as `TheThingFactory` at VA 0x012EF1D8; its one stack argument is the entry's string address. All 284 bytes of the callee were decoded, including its three return paths. It reads the string's pointer, searches the receiver's table at +0x10, returns the found value from node+8 in EAX, handles the testing-name path, and returns zero on failure. Every return uses `ret 4`; there is no hidden return pointer.

The existing ordinary `ThingFactory::findTemplate` name is contradicted by the ILT oracle for all twelve tested access, receiver-const and pointer-return-const decorations. The call goes through ILT 0x00028560, which symbols.csv already pins as `?findTemplateInternal@ThingFactory@@QAEPAVThingTemplate@@ABVAsciiString@@@Z` (EA evidence names the body at 0x00137E80 `ThingFactory::findTemplateInternal`), so the source declares that one-argument method and adds no pin. The ILT oracle does not confirm that decoration either, so the original spelling stays open. The target's existing address-derived method is likewise a placeholder, not a real-name claim.

Raw evidence: build/target-0023b9f0/name-checks.log, build/target-0023b9f0/factory-callees.log and build/target-0023b9f0/finalize-source.log. The reused pin would be refuted by a different decoded ILT destination, argument cleanup, receiver, or return representation.

## Compiler experiments

The saved bank reproduced at 324 bytes with 102 differences over the explicit 321-byte extent. The first differing byte was +0x88. The first roster loop was equal; later discrepancies covered the begin/count allocation, empty-path branch, reciprocal multiplication order, final-loop induction and selected-position load scheduling. The complete raw comparison is build/target-0023b9f0/bank-probe.log.

The new structural hypothesis was that retaining the slot-vector begin local across both traversals and spelling coordinate updates as independent scalars concealed native lifetimes. Reloading the begin member for the final traversal yielded 321 bytes with 25 differences and restored the register allocation and record-based induction. Aggregating the center and the final pair subtraction removed the remaining floating-point scheduling differences. Trials retained at build/target-0023b9f0/10-reload-begin.cpp and build/target-0023b9f0/16-aggregate-reload-begin.cpp have unedited probe logs beside them. Each hypothesis and measurement was appended to build/verdict.txt.

Literal constants, compound scalar updates, nested copy constructors, named and expression copy temporaries, iterator reuse, const roster aliases, a scoped roster lifetime and a final slot reference were also tested. Their exact sources and raw outputs are retained under build/target-0023b9f0. Cleanup replaced the bank's integer alias casts with typed aggregate copies, used the canonical string header, preserved established descriptive stems and changed the constants to plain literals. Each cleanup still measured exact before the relocation-resolving gate. The baseline and final translation units retain the same /DNDEBUG /MD /EHsc options; no shared header or compiler-policy change is needed.

The final source preserves the local name `begin` by assigning it a fresh `m_bfmeSlotBegin` load immediately before the final loop. This retains the measured lifetime change and avoids an identifier-alignment false positive in the name regression check. That cleanup also remains byte-exact. Its source and unedited probe output are build/target-0023b9f0/23-preserve-begin-local.cpp and build/target-0023b9f0/23-preserve-begin-local.log.

## Verification

The tested revision is 33c62fb763b690d472690c044ce4bd76868de74d plus this working-tree conversion. The scoped byte gate passes for one function, including all relocation operands, three float constants, recorded global references and the body guard. Raw output and its zero exit status are build/target-0023b9f0/scoped-gate-bash.log and build/target-0023b9f0/scoped-gate-bash.exit. add_match.py separately verified the conversion and removed the bank; its original output is build/target-0023b9f0/add-match.log. The final cleanup was recompiled and gated afterward.

Global pin consistency, declared-definition coverage, the canonical-class check, the member-name oracle, source name preservation and the working-tree ILT guard all pass. Raw outputs are build/target-0023b9f0/pin-consistency.log, build/target-0023b9f0/declared-unmatched.log, build/target-0023b9f0/class-gate-final.log, build/target-0023b9f0/member-oracle.log and build/target-0023b9f0/names-clean-final.log. The installed name_regression.py CLI accepts Git revisions rather than two source filenames, so the scratch checker calls its source-comparison and respelling APIs directly against the archived bank and final source. It reports no regressions. The coordinator still runs the staged hook.

check_csv.py passed before the conversion but its final invocation raises FileNotFoundError while reading the now-deleted bank through the still-unchanged Git index. The source addition and bank deletion cannot be staged in this worker's read-only Git sandbox. Raw output is build/target-0023b9f0/check-csv.log. The coordinator must stage the complete transaction and rerun that check; the bank was not restored. No full gate is required by a source-only conversion with no shared-header or shim edit.
