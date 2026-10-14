# Wave-19 a4: 0x00165D50 cash-multiply fold is a context tie-break, not a source shape

Bank unchanged: `targets/game/reverse/attempts/0x00165d50.cpp`, 2333B/63 relocs,
10 non-reloc diffs (+0x376..+0x38A), masked score 0.9957134. Retail +0x376:
`mov ecx,[0x12ED5C8]` / `mov edx,[ecx+0xB24]` / `imul edx,[eax+0x88]`
(global pointer+value materialised, boxes folded). Ours: boxes -> ECX,
global ptr -> EDX, `imul ecx,[edx+0xB24]` (global folded).

## New evidence

1. ZH original order is the OPPOSITE of the bank: AIPlayer.cpp:302 writes
   `warehouseModule->getBoxesStored()*TheGlobalData->m_baseValuePerSupplyBox`.
   Probed both orders in the bank TU: byte-identical output. Operand order is
   inert here (confirms the earlier wave's swap trial).
2. Minimal MSVC 7.1 repro (same toolchain, /O2 -GR- -EHsc-): WITHOUT a
   preceding call, `w->get() * g->field` emits the RETAIL shape (global
   materialised, `[eax+0x88]` folded). WITH a preceding call it always emits
   the bank shape, for both orders, member vs call, const/pointer/reference
   locals, address-of derefs, casts, and if-condition forms. The fold is a
   context/allocator tie-break after a call, not a property of the expression.
3. Same binary, same expression, third shape: matched `findSupplyCenter`
   (0x00164C10) emits `mov ecx,[eax+0x88]` / `mov eax,[0x12ED5C8]` /
   `mov eax,[eax+0xB24]` / `imul eax,ecx` (both operands materialised, no
   memory operand) - allocator context fully determines this.
4. Call identity at +0x36D verified this session: retail target resolves to
   `j_0002ae23` (ILT -> Object::findModule 0x1BEE60), same as the bank.

## Refuted this wave (bank context, all 2333B/63 relocs/10 diffs)

ZH operand order; `GlobalData *gd` pointer local both orders; `const Int`
local; `(Int)` cast; `const GlobalData &` reference; `&field` address-of
derefs (4 variants); `*(Int*)((char*)gd+0xB24)`; unsigned casts; multiply
inside the `if` condition both orders; `_ReadWriteBarrier()` (frame explodes to
2350B, 1872 diffs - not usable).

Reopening requires evidence that changes the IR context after the call (e.g.
retail TU-level optimization difference), not another expression spelling.
