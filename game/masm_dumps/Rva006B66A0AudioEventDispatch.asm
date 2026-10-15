.386
.model flat
; ?rva006B66A0@Rva006B66A0AudioOwner@@QAE_NPAVRva006B66A0AudioHolder@@HH@Z
; Retail @ 0x006B66A0 size 495
;
; MASM dump carrying a measured codegen blocker. Identity is not provable: the
; 0x006B9500 Miles request path reaches this body through its owner recorder,
; but no string or caller names the split BFME record, so the name stays
; address-derived. ABI from decode: __thiscall member (ECX owner) with a
; holder pointer and two ints; SEH frame `push -1; push g_Va01049118`. It fills
; the record from the source event, refcounts the shared holder, advances the
; slow elapsed-scale float, and routes soundType 2 to the file-handle allocator.
; The reconstructible C++ body (targets/game/reverse/attempts/0x006b66a0.cpp)
; compiles to exactly 495 bytes with 25 relocations and shape 1.000; its whole
; residue is one dead-register reuse choice at +0x106 +0x109: retail reloads
; the event pointer into EBP (8b 6d 00 / c6 45 47 00), VC7.1 into ECX
; (8b 4d 00 / c6 41 47 00), for the store `record->m_event.m_pointer->m_flag47
; = 0`; EBP is dead after the store in both. ~60 spellings measured on
; 2026-09-24..2026-10-13 (expression and accessor variants, get(), [0], casts,
; reference and register locals, setEvent, statement swaps, /Ob2, no-Ob1, /EHsc,
; /Gs and the /Oa /Ow /Ob2 /Os /Ot flag sweep) all land on exactly these two
; bytes, and fresh 2026-10-13 variants (char-pointer local, volatile store,
; pointer-plus-offset local) score 2/360/373 diffs: an allocator tie-break, not
; source-spellable. The dump body is byte-identical to retail outside its
; relocation slots.
; Evidence: targets/game/reverse/identity_evidence/006b66a0-masm-codegen-blocker.md
EXTERN g_Va01049118:NEAR
EXTERN ?j_000464ca@@YAXXZ:NEAR
EXTERN ?g_bfmeElapsedScale@@3MA:BYTE
EXTERN ?j_00011fcc@@YAXXZ:NEAR
EXTERN ?j_00046a33@@YAXXZ:NEAR
EXTERN ?j_0001079e@@YAXXZ:NEAR
EXTERN ?g_Va0112E8B0@@3MA:BYTE
EXTERN ?j_00001b77@@YAXXZ:NEAR
EXTERN ?j_00023f79@@YAXXZ:NEAR
EXTERN __imp__InterlockedIncrement@4:BYTE
EXTERN __imp__InterlockedDecrement@4:BYTE
EXTERN ?j_00015a69@@YAXXZ:NEAR
EXTERN ?j_0003aa6c@@YAXXZ:NEAR
EXTERN ?j_0004066f@@YAXXZ:NEAR
EXTERN ?j_000298e8@@YAXXZ:NEAR
EXTERN ?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z:NEAR
_TEXT SEGMENT
public ?rva006B66A0@Rva006B66A0AudioOwner@@QAE_NPAVRva006B66A0AudioHolder@@HH@Z
?rva006B66A0@Rva006B66A0AudioOwner@@QAE_NPAVRva006B66A0AudioHolder@@HH@Z PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va01049118
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 053h, 055h, 056h, 08Bh, 074h, 024h, 01Ch, 08Bh
    db 006h, 057h, 050h, 08Bh, 0D9h
    call ?j_000464ca@@YAXXZ
    db 084h, 0C0h, 075h, 07Ch, 08Bh, 00Eh, 0D9h, 041h, 054h, 0D8h, 01Dh
    dd ?g_bfmeElapsedScale@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 03Ah
    call ?j_00011fcc@@YAXXZ
    db 084h, 0C0h, 074h, 031h, 08Bh, 00Eh
    call ?j_00046a33@@YAXXZ
    db 08Bh, 00Eh
    call ?j_00011fcc@@YAXXZ
    db 084h, 0C0h, 074h, 01Fh, 08Bh, 00Eh
    call ?j_0001079e@@YAXXZ
    db 08Bh, 006h, 0C6h, 040h, 044h, 001h, 0A1h
    dd ?g_Va0112E8B0@@3MA
    db 08Bh, 00Eh, 050h, 068h, 055h, 055h, 009h, 042h
    call ?j_00001b77@@YAXXZ
    db 08Bh, 00Eh, 0D9h, 041h, 054h, 0D8h, 01Dh
    dd ?g_bfmeElapsedScale@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 001h, 074h, 01Eh
    call ?j_00011fcc@@YAXXZ
    db 084h, 0C0h, 075h, 015h, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh
    db 05Eh, 05Dh, 05Bh, 083h, 0C4h, 00Ch, 0C2h, 00Ch, 000h, 08Bh, 0CBh
    call ?j_00023f79@@YAXXZ
    db 08Bh, 0F8h, 08Dh, 06Fh, 004h, 03Bh, 0EEh, 089h, 07Ch, 024h, 020h, 074h, 03Dh, 08Bh, 006h, 085h
    db 0C0h, 074h, 00Ah, 083h, 0C0h, 074h, 050h, 0FFh, 015h
    dd __imp__InterlockedIncrement@4
    db 08Bh, 045h, 000h, 085h, 0C0h, 074h, 021h, 08Dh, 078h, 070h, 08Dh, 04Fh, 004h, 051h, 0FFh, 015h
    dd __imp__InterlockedDecrement@4
    db 085h, 0C0h, 07Fh, 00Ch, 085h, 0FFh, 074h, 008h, 08Bh, 017h, 06Ah, 001h, 08Bh, 0CFh, 0FFh, 012h
    db 08Bh, 07Ch, 024h, 020h, 08Bh, 006h, 089h, 045h, 000h, 083h, 07Ch, 024h, 024h, 001h, 0C7h, 007h
    db 000h, 000h, 000h, 000h, 075h, 00Bh, 08Bh, 06Dh, 000h, 0C6h, 045h, 047h, 000h, 0C6h, 047h, 014h
    db 001h, 08Bh, 00Eh
    call ?j_00015a69@@YAXXZ
    db 08Bh, 00Eh, 08Bh, 049h, 028h, 085h, 084h, 08Bh, 03Ch, 006h, 000h, 000h, 074h, 004h, 0C6h, 047h
    db 012h, 001h, 08Bh, 00Eh, 08Bh, 049h, 028h, 085h, 084h, 08Bh, 048h, 006h, 000h, 000h, 074h, 004h
    db 0C6h, 047h, 013h, 001h, 08Bh, 016h, 08Bh, 042h, 008h, 08Bh, 080h, 084h, 000h, 000h, 000h, 083h
    db 0F8h, 002h, 075h, 06Ah, 0D9h, 042h, 054h, 0D8h, 01Dh
    dd ?g_bfmeElapsedScale@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 001h, 075h, 004h, 033h, 0C9h, 0EBh, 005h, 0B9h, 001h, 000h, 000h, 000h
    db 0D9h, 042h, 054h, 0D8h, 01Dh
    dd ?g_bfmeElapsedScale@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Dh, 08Bh, 044h, 024h, 028h, 085h, 0C0h, 075h, 005h, 0B9h
    db 002h, 000h, 000h, 000h, 051h, 056h, 08Dh, 04Ch, 024h, 028h, 051h, 08Bh, 08Bh, 000h, 00Bh, 000h
    db 000h
    call ?j_0003aa6c@@YAXXZ
    db 050h, 08Dh, 04Fh, 00Ch, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h
    call ?j_0004066f@@YAXXZ
    db 08Dh, 04Ch, 024h, 020h, 0C7h, 044h, 024h, 018h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_000298e8@@YAXXZ
    db 08Bh, 073h, 04Ch, 06Ah, 00Ch
    call ?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z
    db 08Dh, 048h, 008h, 083h, 0C4h, 004h, 085h, 0C9h, 074h, 002h, 089h, 039h, 08Bh, 04Eh, 004h, 089h
    db 030h, 089h, 048h, 004h, 089h, 001h, 08Bh, 04Ch, 024h, 010h, 05Fh, 089h, 046h, 004h, 05Eh, 05Dh
    db 0B0h, 001h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h, 0C4h, 00Ch, 0C2h, 00Ch, 000h
?rva006B66A0@Rva006B66A0AudioOwner@@QAE_NPAVRva006B66A0AudioHolder@@HH@Z ENDP
_TEXT ENDS
END
