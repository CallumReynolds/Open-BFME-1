# Bridge-object bank: kind-filter ABI and remaining visibility blocker

The reconstruction at `targets/game/reverse/attempts/0x003916f0.cpp` remains a non-matching bank. Reopen it with a complete, independently verified definition of callee RVA `0x0038F7B0` available in the caller's translation unit. Its saved reconstruction ignores all four parameters and is unsuitable for that purpose. This audit changes neither the preferred bank nor the function ledger.

The tested revision is `5ef5ef7df5384303e915d0a24fa47d2f2f4314fa`; the model is `gpt-6.1-sol`. Raw evidence and every trial source are retained under `build/r003916f0_20261015/`. Paths below name local raw files, which are not tracked artifacts.

## New ABI evidence

RVA `0x0038F7B0` has a complete 2,335-byte body ending at RVA `0x003900CF`, immediately after `ret 0x10` at `0x003900CC`. Its prologue subtracts `0xF8` after the three EH pushes, then saves four registers. The incoming arguments are therefore at steady-state ESP offsets `0x118`, `0x11C`, `0x120` and `0x124`.

At callee offsets `+0x1DF` and `+0x20A`, arguments two and three are loaded and tested for null. Each non-null argument is dereferenced as a four-byte integer. The value selects a dword and a bit in the template's kind flags at `template + 0xC8`: the code shifts the value right by five and uses its low five bits as a shift count. The first filter skips a set bit; the second skips an absent bit. Neither argument is a Boolean or a progress output. The last argument is read as one byte at `+0x3CF` and `+0x818`.

At the assigned target's `+0x1A4..+0x1C4`, the four arguments are the vector address, null, the address of a four-byte local containing 59, and the incoming loading flag. The retail kind-name table at RVA `0x00EAA068` resolves entry 59 to `WALK_ON_TOP_OF_WALL`. The pointer read from that table and the string were checked against retail, rather than inferred from the Zero Hour enum. The two additional calls in the fully decoded `0x00394260` caller, at `+0xBCD` and `+0xBED`, pass the same local value as the first filter and null as the second filter. This independently supports two optional input filters.

Evidence: `retail_0038f7b0.txt`, `retail_003916f0.txt`, `retail_00394260.txt`, `checked_loadAllObjects.log`, and `checked_00394260.log` in the raw-evidence directory. The corrected pointer and enum declarations are preserved in `helper_kind_filters.cpp` and `helper_kind_enum.cpp` with their unedited probe output. Both retain the bank's descriptive method name.

## Boundaries, values and cleanup

The assigned body occupies `0x003916F0..0x00391944`. Its two exits are complete `ret 4` instructions at `+0x232` and `+0x251`. All direct conditional branches stay inside that extent. The `0x00394260` caller loads the receiver into ECX and pushes one loading argument before calling ILT RVA `0x0002835D`, which jumps to this body. This supports the bank's member-call ABI and GameLogic context; it does not establish the original method name. The EA evidence supplies a source-file association but no method name for this address.

The actual vector insertion route is ILT `0x0003A855` to `0x0038EB40`. Its complete 62-byte body copies through ILT `0x0002A56D`, which reaches the complete 23-byte helper at `0x00385CC0`. That helper reads source offsets zero and four and writes both destination fields, with no additional field or cleanup. The target writes the created-object pointer first and the map-object pointer second. Its final loop calls the first pointer's level-start method with `second + 0x24`, and advances eight bytes. These accesses establish two pointer payloads. They do not independently establish the `std::pair` template spelling. A local two-pointer value-class trial produces the same residue.

The 306-byte reallocation helper at `0x0038BAD0` was also completely decoded and compared with its existing C++ source. Every construction path reaches the same two-field copy helper. Its only other calls allocate or deallocate backing storage. The vector-header receiver is not passed to those calls or stored externally. The 62-byte `push_back` similarly passes the receiver only to that reallocation helper. In `0x0038F7B0`, the first incoming argument is used at `+0x5CD` as the receiver of this insertion path; the inserted fields are the object and map-object pointers. Thus the decoded path does not retain the caller's vector-header address. An external declaration cannot convey this fact to the caller's compiler.

The target's unwind map has state zero clean up the vector base at EBP minus `0x38`, through `0x003895C0`; state one cleans the temporary at EBP minus `0x20`, through `0x00141CC0`, `0x00015D7A` and `0x00140950`. These complete helpers were decoded, including all returns and the jump chain. The vector cleanup deallocates storage and has no element-destruction loop. The temporary's constructor at `0x00143B20` and normal destructor at `0x00140950` were also decoded. This establishes the cleanup locations and routes; no new real class identity is claimed for the opaque temporary. The target's indirect calls remain the witnessed slots `+0x14`, `+0x18` and `+0xB0`. The ground-height call's argument and return widths agree with the canonical TerrainLogic declaration; its normal-output pointer is null. The landmark-bridge call passes one object pointer, as the canonical declaration expects. No full runtime validation of those virtual targets is claimed.

Evidence: `eh_target.log`, the `retail_*.txt` files and corresponding `checked_*.log` files. The existing `Rva0038BAD0VectorInsertOverflowBody.cpp` was read directly. Its opaque element declaration was not treated as type evidence. The earlier reports' synthetic exact harnesses are absent from this checkout and their claimed exact result was not reused as a measurement.

## Measured residue and rejected hypotheses

The original bank emits 597 bytes against retail's 596. Probe reports 182 differing bytes within the common extent; the extra emitted byte makes 183 when extent differences are counted. Nine relocation sites are displaced, so these positional counts are diagnostic, not a strict relocation proof. The exact reported offsets and their owning retail instructions are retained in `diff_offsets.json` and `diff_instructions.txt`. The unedited complete comparison is `bank_probe_raw.log`.

Every reported position falls in three regions: `+0x19..+0x40`, the frame references at `+0xF9`, `+0x106`, `+0x10D`, `+0x111`, `+0x119`, `+0x121`, `+0x12B`, `+0x14B`, `+0x173`, or the tail at `+0x1A4..+0x253`. The first region saves EBP at function entry in retail, but only around the creation loop in the bank. Relative to entry ESP, the vector header and position temporary exchange the twelve-byte regions at minus `0x38` and minus `0x44`; the saved receiver, filter local, opaque temporary and EH-state slot retain their absolute frame locations. The float operations agree after accounting for the position displacement. The final region retains the original vector beginning in EBP in retail, copies it into the walking ESI register, and uses EBP in teardown. The bank walks with ESI and reloads the beginning after the callbacks. This changes branch lengths, both epilogues and downstream relocation positions.

| Trial source stem | Result | Hypothesis rejected |
|---|---|---|
| `helper_kind_filters`, `helper_kind_enum` | 597 bytes; 182 reported differences | Corrected kind-filter pointer and enum declarations alone fix shape. |
| `helper_reference`, `helper_ilt_inline`, `push_back_ilt_view` | 597 bytes; 182 reported differences | Reference passing or the witnessed ILT call view supplies the missing visibility. |
| `compile_alias_Oa`, `compile_alias_Ow` | 597 bytes; 182 reported differences | Compiler alias switches retain the beginning across callbacks. |
| `compile_inline_Ob1` | 611 bytes; 404 reported differences | The alternative inline-expansion policy reproduces retail. |
| `compile_stlp_no_exceptions` | 597 bytes; 182 reported differences | The matched neighbours' STLport exception setting changes the corrected trial. |
| `vector_aggregate_wrapper`, `pair_value_view` | 597 bytes; 182 reported differences | An aggregate owner or a two-pointer value class fixes the lifetime or frame. |
| `final_begin_alias`, `final_const_iterator` | 597 bytes; 182 reported differences | Explicit beginning aliases or const iterators preserve retail's beginning register. |
| `final_vector_swap` | 698 bytes; 450 reported differences | An ownership transfer before notification removes the escape residue without extra code. |
| `helper_restrict_reference` | Compilation refused | VC7.1 supports a restrict-qualified reference declaration. It reports C4235. |

Each listed variant was probed once (n=1); the baseline was reproduced repeatedly. Each stem has its complete source and unedited `.log`. The family generator reported no applicable copy, register or frame rewrite for the corrected source. Existing history already records broad EH and local-scope sweeps; those were not used as evidence of success. The two unchanged alias-switch experiments close that lever. No assembly, synthetic callee, new pin or baseline change was introduced.

## Gates and reopening condition

The original bank fails the repository's strict `build.verify_functions` comparison and has unresolved decorations for the invented helper and its pointer-pair `push_back`. Routing the helper through its actual ILT removes only that unresolved helper decoration; the byte comparison still fails. Raw output: `bank_strict_gate.log` and `ilt_strict_gate.log`. The earlier `*_resolver_only_NOT_GATE.log` files exercise resolution only and are not verification results.

The existing dump passes the exact scoped row gate, including string, constant, DIR32 and body checks: `dump_scoped_gate.log`. The initial malformed selector is retained separately as `dump_invalid_selector.log`. These passes certify the existing dump, not the C++ bank. Ledger checks pass in `check_csv_initial.log` and `check_csv_final.log`; pin consistency passes in `pin_consistency.log`. No source or shared header was changed, so a full gate is not required for this evidence-only outcome.

The callee has EA name evidence for `GameLogic::loadAllObjects`, but the twelve pointer-vector decorations tested across access and filter constness are contradicted by the ILT oracle. Consequently neither its exact source decoration nor the `std::pair` identity is asserted or pinned. Raw compiler inputs and results are in `callee_*.cpp`, `callee_*.compile.log` and `callee_oracle.log`. The assigned target retains its address-bearing bank name.

The reopening experiment is to compile the independently verified, complete `0x0038F7B0` definition beside this body and gate both real bodies, with the kind-filter ABI above. A retained beginning reload and the same frame swap after that change would refute the visibility explanation. An independently justified declaration or lifetime change that removes these residues while passing the strict gate would also refute the present stopping condition. Another arbitrary stub or another permutation of the unchanged locals is not such evidence.
