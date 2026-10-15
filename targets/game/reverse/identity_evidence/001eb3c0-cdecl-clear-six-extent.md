# 0x001EB3C0 cdecl six-dword clear: one 24-byte body, not 4 + 20

The ledger split retail 0x001EB3C0..0x001EB3D8 into a 4-byte gen-dump head
(`?d_001eb3c0@@YAXXZ`, 0x001EB3C0/4) and a 20-byte gen-alias tail
(`?dup_001eb3c4@@YAXXZ`, 0x001EB3C4/20, aliased to
`?clear@TurretInfo@ModelConditionInfo@@QAEXXZ`).

`python3 tools/dis_retail.py 0x001EB3C0 32`:

    +0000 8b 4c 24 04   mov ecx, [esp+4]
    +0004 33 c0         xor eax, eax
    +0006..+0014        mov [ecx+0..0x14], eax   (six dwords)
    +0017 c3            ret
    +0018 cc ...        padding

The head has no `ret` or `jmp`: it falls straight into the stores, so the two
rows are one function. A scan of the whole retail image finds no `call`/`jmp`
rel32 and no absolute pointer targeting 0x001EB3C4; the only reference to the
range is ILT thunk 0x00019FFB (`jmp 0x001EB3C0`). MSVC never falls through
from one function into another, so 0x001EB3C4 is not an entry point. The real
`ModelConditionInfo::TurretInfo::clear` is its own body at 0x000C43F0/20; the
0x001EB3C4 alias only matched because a thiscall clear of six dwords compiles
to the same 20 bytes as this body's tail.

Shape matches the sibling `bfmeAnySix` at 0x001EB3A0 (cdecl pointer argument
loaded into ecx, then the same body as the thiscall 0x001EB380). No caller or
owner is known (the ILT thunk itself has no reference), so the body keeps an
address-derived name: `Rva001EB3C0::clearSix(int *)`.
