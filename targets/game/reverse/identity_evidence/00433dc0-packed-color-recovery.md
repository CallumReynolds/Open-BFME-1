# Rectangle draw recovery at 0x00433DC0

## Result

The complete 360-byte body is recovered as `Rva00435270Layout::setRect` in `game/GameEngine/Source/GameClient/GUI/Rva00435270SetRect.cpp`. The tested base is `07a219def195b93798ffefa35aef97d473559f40`, with this conversion uncommitted. `build/rectangle-finish-00433dc0/final-source-probe.log` records exact instruction bytes, and `scoped-candidate-gate.log` independently verifies relocation bindings and an unchanged executable after patching. The original EA owner and method identity remain unknown. The existing address-derived owner and descriptive method name are retained.

## Hypothesis and compiler evidence

The incoming bank reproduces 127 differing bytes. Retail completes the masked RGB and clamped alpha before the first virtual begin call, whereas the bank carries separate RGB and alpha values across that call. The hypothesis was that a value passed into the inline drawing adapter would preserve the completed color lifetime. It would be refuted if the resulting instructions retained the bank's delayed packing. A one-word packed-color value passed by value restores the entire prefix through offset 0x82; passing that value by reference loses the improvement. This is a compiler-facing local value object, not a claim that retail had a class of that name. Its complete constructor copies one integer, its alpha setter replaces the high byte, its conversion reads the same integer, and its implicit copy owns no resource. All these helpers fold away.

The remaining structural difference is at offset 0x84: the candidate computes a fresh doubled alpha with `lea eax,[edi+edi]`, while retail shifts the existing alpha with `shl edi,1`. Passing the compound-assignment lvalue `(alpha <<= 1)` to the reference-returning minimum produces exact bytes. A shift expression without the assignment retains the mismatching LEA. This interaction was not established by the earlier attempts' scalar mutation experiments.

The complete measured trial sources and unedited probe outputs are paired under `build/rectangle-finish-00433dc0/`. `trials.jsonl` records command receipts and results, and `bank-differences.json` associates every incoming differing byte with the decoded instructions and its scheduling or register-lifetime explanation. `color-conversion-value.log`, `second-shift-expression.log` and `second-shift-lvalue.log` retain the decisive comparisons. The rejected helper-order, free-wrapper, aggregate-coordinate, minimum-representation, color-bitfield and color-lifetime shapes remain available there. `incoming-bank.cpp` preserves the original bank byte for byte.

## Complete boundary and ABI

The target begins after alignment bytes at 0x00433DC0 and has one return, `ret 0x18` at 0x00433F25, ending at 0x00433F28 before more alignment bytes. Every direct conditional branch stays inside this extent and lands on a decoded instruction boundary. There are no direct calls, outgoing tail jumps, exception registrations, owning constructions or containers in this target. Constructor unwind and container-payload checks therefore do not apply.

The complete matched caller at 0x00435270 passes the words at receiver offsets 0x4C, 0x50, 0x54 and 0x58, the packed word at 0x2C, and signed integer border width 1. Its call at 0x0043529B reaches ILT 0x00007356, whose complete jump reaches this target. ECX is the unadjusted layout receiver. There is no hidden return storage or consumed result. The existing private void declaration is retained. Target x87 subtraction proves the four single-precision coordinates, and signed `fild` proves the four-byte border width. The target reads the signed progress word at receiver offset 0x28, consistent with the existing apply and range declarations. Both outlines execute unconditionally.

The actual W3DDisplay vtable at VA 0x0111EDD0 supplies the following independently decoded routes. The zero-argument setup and completion slots preserve their captured display receiver across each drawing operation.

| Slot | ILT RVA | Body RVA | Complete contract |
|---|---|---|---|
| 0xB0 | 0x000096F6 | 0x006E9B70 | Load ECX from receiver offset 0x164 and tail-jump to complete 0x00934820; its only return is plain `ret`. |
| 0xC0 | 0x0000A06A | 0x006EA050 | Four float coordinates and a packed four-byte color; both return paths clean 0x14 bytes. |
| 0xBC | 0x00046E39 | 0x006E9D40 | Four float coordinates, a float line width and a packed four-byte color; both return paths clean 0x18 bytes. |
| 0xDC | 0x00008265 | 0x006E9B80 | Load ECX from receiver offset 0x164 and tail-jump to complete 0x00934940; its only return is plain `ret`. |

All complete target, caller, minimum, thunk, wrapper, fill, outline and renderer instructions are retained as named `.disasm` files. `boundaries.json` records exact extents, hashes, every direct branch and every return. Each extent has its own `checked-*.log` from the required checked-callee helper. The large renderer bodies are used only to establish their receiver and zero-stack-argument contracts; their internal ownership and exception machinery are not reconstructed here.

The adjacent complete 17-byte integer minimum and the target's signed conditional branches agree with the local reference-returning helper. Adjacency is not used as owner or type identity evidence. The canonical global remains `Display *TheDisplay`, recorded at VA 0x012F1270. The shared Display header has integer-coordinate declarations and a different virtual layout, so this source uses the bank's opaque slot view rather than claiming that header's layout. The two float references are plain `1.0f` literals. No pin or shared declaration was added. Searching `game/` finds the retired dump name only in its unchanged assembly definition, so no compatibility pin is required.

## Verification and collection

`add-match.log` records the successful normal replacement and bank removal. `scoped-bash-gate.log` passes source claims, exact bytes, string references, float constants, recorded DIR32 addresses and the body guard. `baseline-hash.log`, `pin-consistency.log`, `class-gate-final.log` and `declared-unmatched-final.log` pass. `name-regression-files.log` checks the bank against the new source with the repository module and finds no descriptive-name regression. The ILT oracle contradicts the invented decoration as an original retail name; the unchanged name is classified as a placeholder, and the actual ILT guard reports no rejection. This is not a claim of EA naming evidence.

`check-csv-raw.log` cannot complete because the retired bank remains in the read-only index and the new source cannot be staged in this seat. The tool attempts to read that deleted bank. The coordinator must stage the source, bank deletion, ledgers, evidence and sole verdict row together, then rerun the CSV check and commit hooks. The exact verified conversion remains in the working tree. The Windows launcher also failed to locate Python in `scoped-ledger-gate.log`; the explicitly invoked Git Bash entry point passes in `scoped-bash-gate.log`. No shared header, shim, policy, tooling or baseline changed, so a full gate is not required for this source-only conversion. No background task remains running.
