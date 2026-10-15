# Exact W3DView camera snapshot restore

The tested revision is `c38b6915dc092a3cc1d40316b264ed58ef3aac3f`. The retained identity is `?apply@Rva0073D6D0@@UAEXI@Z`. The saved reconstruction now reproduces the complete 306-byte body after independently binding every external reference. The body is converted into game/GameEngineDevice/Source/W3DDevice/GameClient/Rva0073D6D0SnapshotRestore.cpp under its address-derived name. No complete retail caller establishes the unread argument's type or the return contract, so those parts of the declaration remain hypotheses.

## Result and remaining blocker

The incoming bank emitted 306 bytes with 11 relocation-masked differences. Independent binding gave 19 differing bytes, at every offset from +0x27 through +0x39. Retail computes the coordinate destination and stores X before loading Y, then stores Y before loading Z. The incoming bank's /Oa assumption moved those two loads earlier. All instructions outside that interval agreed after independent binding. Raw evidence is build/0073d6d0-access/00-bank-probe.log and build/0073d6d0-access/00-bank-independent.log.

The new candidate removes /Oa and the compiler barrier, retains the external coordinate snapshot, and gives only scalar snapshots Rva012F9DD0 and Rva012F9DD4 internal linkage. These two declarations permit the later scalar preloads without relaxing aliasing for the aggregate copy. Each scalar independently repairs its corresponding load/store pair. With both changed, the complete body has zero masked differences and zero independently resolved differences. Rva012F9DD8 remains external. The final trial is build/0073d6d0-access/29-minimal-exact-candidate.cpp; its unedited probe, scoped gate and independent binding logs have the same prefix.

The target receives its owner in ECX, consumes one unread four-byte stack slot, writes no hidden return storage, and returns with an empty x87 stack. Its final EAX residue is the raw Y component copied to the result member. This does not distinguish a void declaration from an intentionally returned integer value. The unchanged bank declaration uses void and unsigned as hypotheses. The seat held the body back for that reason; the coordinator converted it, because an address-derived name claims no identity and every byte matches. A complete retail caller or an independent declaration witness would settle the argument and return types. Further scheduling experiments are unnecessary unless a new compiler context changes the exact result.

## Hypothesis and refutation

The new hypothesis was that storage visibility, rather than register allocation or scalar type width, controls the two independent schedules. Earlier attempts defined external scalar globals but did not isolate internal scalar linkage from external aggregate linkage. Making every snapshot internal changes the coordinate schedule too. Making only the scalar snapshots internal produces the exact target under ordinary alias settings. A differing byte after independent binding refutes exactness; a conflicting decoded writer or address identity refutes the storage mapping. This result does not prove EA's historical linkage declarations.

The two internal scalar symbols are bound to the original retail snapshot storage, not to invented addresses. Complete decoded snapshot writer 0x00743CE0 writes the same two addresses from receiver fields +0x50 and +0x3C, while its other stores establish the coordinate and +0x6C mappings. A reference screen finds those scalar accesses in the target, that writer, and the separate restore body at 0x0073D4C0. Both restore bodies have EA file evidence for W3DView.cpp. The screen does not prove original linkage or exclude computed references. Raw evidence is build/0073d6d0-access/snapshot-refs.log and build/0073d6d0-access/snapshot-ref-bodies.log. Snapshot addresses lie in loader-zero-filled storage; section measurements are in build/0073d6d0-access/snapshot-storage-sections.log. The bank's file-local declarations are a compiler visibility view over those observed addresses. A future source integration of the writer must share this storage.

## Boundaries, helpers and identity

The only target return is ret 4 at 0x0073D7FF, ending at 0x0073D802 before padding. Every immediate branch stays inside the complete extent. There are no direct calls, external tail jumps, EH states, allocations or container operations. Constructor cleanup and container payload checks do not apply to this body.

The constructor at 0x00745B10 installs the primary table at VA 0x011217A0 and witnesses base offsets +0xB4 and +0xFC and the embedded object at +0x24B8. Primary slot 150 routes through ILT 0x00003102 to the target. The target's slot 103 routes to the complete 72-byte reset at 0x0073F960. Slot 117 routes to the complete 13-byte setter at 0x0045BF90, which consumes a full dword and returns with ret 4. These remain virtual calls in the candidate.

The complete 49-byte embedded constructor at 0x006DF550 installs table VA 0x0111E188. Its slots 1, 2 and 3 route to complete four-byte getters at 0x006DF5A0, 0x006DF5B0 and 0x006DF5C0. They read float fields +0x08, +0x0C and +0x10, return in ST0, and consume no arguments. The target passes this+0x24B8 without another adjustment. The candidate includes canonical Coord3D and retains every descriptive bank name.

Terrain slot 6 routes through the complete 59-byte forwarder at 0x006BE250. Its null-render-object path returns a float with ret 12. Its other path adjusts the receiver to the render singleton and tail-jumps through slot +0x248. The installed BaseHeightMap table routes that slot to the complete 957-byte body at 0x006CBB50. Each of its three return paths returns in ST0 and consumes 12 bytes. Its first two inputs are read as floats, and a nonnull normal receives all three float components. Those complete bodies establish argument order, receiver handling and output layout independently of ledger names.

Complete decoded bodies are in build/0073d6d0-access/decoded-bodies.log, with separate checked-<rva>.log inventories for each supporting extent. Table routes are in vtable-routes.log. The owner constructor is layout evidence only; this attempt makes no new claim about its ownership or unwind implementation. The snapshot writer and supporting constructors were not converted. No body was newly ported from Zero Hour.

The raw caller screen validates potential direct branches and +0x258 operands against decoded containing bodies. Its only aligned branch to the target is the existing ILT jump. It finds no direct dispatch through slot 150. The two immediate register loads of 0x258 belong to resolution dimensions, not vtable indexing. The target's thunk pointer occurs in the primary table. This negative screen cannot exclude computed dispatch. Raw evidence is build/0073d6d0-access/caller-screen.log, caller-candidate-bodies.log and target-pointer-refs.log.

The ILT Python API contradicts the unchanged address-derived name, while the current guard classifies it as a placeholder and produces no rejection. It is not a claimed real method name. Metadata and the descriptive-name comparison are retained in build/0073d6d0-access/metadata.json.

## Measured alternatives

Every complete trial source and unedited probe output is retained under build/0073d6d0-access/. The running record is build/verdict.txt and the structured record is trials.jsonl. Failed compilations remain in their raw logs.

| Trials | Hypothesis | Result |
|---|---|---|
| 01 and 02 | Volatile aggregate source or destination | Canonical assignment rejects the qualifier. |
| 03 and 04 | Union scalar storage or raw integer copies | 306 bytes with the older 12 masked differences. |
| 05 | Every snapshot internal | 306 bytes with 15 masked differences. |
| 06 | Const aggregate source | Incoming 11-difference result. |
| 07 through 13 | Selected volatile fields inside an implicit aggregate copy | Incoming 11-difference result. |
| 14 and 18 | Copy-helper global optimization or frame scope | Incoming 11-difference result. |
| 15 | Copy-helper size optimization scope | 264 bytes with 226 masked differences. |
| 16 and 17 | Copy-helper alias scopes | Older 12-difference result. These controls reproduce the earlier alias mechanism. |
| 19 | Only scalar storage internal | Exact 306-byte result. |
| 20 | Only coordinate storage internal | 306 bytes with 27 masked differences. |
| 21 | C linkage for the external coordinate | Exact, with internal scalars. |
| 22 | Only the coordinate defined externally | Older 12-difference result. |
| 23 | Only the two late scalars internal | Exact 306-byte result. |
| 24 | Only Rva012F9DD4 internal | 306 bytes with 7 masked differences. |
| 25 | Only Rva012F9DD0 internal | 306 bytes with 5 masked differences. |
| 26 and 27 | External COMDAT definitions or class-static declarations | Older 12-difference result. |
| 28 and 29 | Remove unused barrier declarations from exact candidates | Exact 306-byte result. |

## Verification and preservation

The final candidate passes the scoped byte check, string references, all three constant references, DIR32 identity checks and the body guard. Independent resolution also gives zero differences over all 306 bytes. The two internal scalar definitions are uninitialized data; the body guard reports them as static_skip, not initialized-data comparisons. The separate section measurement establishes zero-fill placement. The raw scoped result is build/0073d6d0-access/29-minimal-exact-candidate-full-scoped.log, and independent bindings are in 29-minimal-exact-candidate-independent.log.

CSV integrity, pin consistency, the class gate and the member-name oracle pass. The declaration check refuses the scratch candidate because it has no authored matched ledger row, as expected for a bank. Raw results are csv-final.log, pins-final.log, class-final.log, name-oracle-final.log and declarations-final.log under the same task directory. No whitelist or baseline is changed. A full gate is not required for this bank and evidence update. Exactly one partial verdict is recorded, and the former bank is preserved in immutable attempt history. No production source, function ledger, symbol pin, shared header, policy or tool is changed.

The saved bank was recompiled at its final path after recording the verdict. It still passes all scoped byte and reference checks in build/0073d6d0-access/bank-final-scoped.log. The final-path probe is bank-final-probe.log. CSV integrity, class and name checks pass again in check-csv-banked.log, class-banked.log and names-banked.log. The bank declaration check still reports zero authored ledger rows in declarations-banked.log. The source body matches the measured final candidate exactly apart from bank metadata. The recording receipt is verdict-receipt.json, and final-receipt.json records source preservation, name preservation, elapsed time and the actual model. All task sessions have completed.
