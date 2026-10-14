.386
.model flat
; MASM dump carrying a measured VC7.1 codegen blocker. The body is an
; xfer-shaped W3DGhostObject virtual: thiscall with one stack argument
; (ret 4 at +0x305), extending the GhostObject transfer body at 0x001B3B70
; (gen-dump row ?d_001b3b70@@YAXXZ), and ILT 0x000268D7 reaches it from slot 3 of the W3DGhostObject
; vftable 0x0111CFB8 (slot 0 ??_GW3DGhostObject, slot 1 the matched
; loadPostProcess, slot 2 the class-name getter returning the literal
; "W3DGhostObject" at 0x0111CFCC). Identity is NOT provable, so the row keeps
; the placeholder name and asserts nothing: tools/ilt_oracle.py CONTRADICTS
; both ?xfer@W3DGhostObject@@MAEXPAVXfer@@@Z and the unsigned variant at this
; address (p_false 5.22e-04, outside its slot 30762 window 19262-19269), and
; the same oracle also contradicts the already-landed sibling
; ?loadPostProcess@W3DGhostObject@@MAEXXZ, so neither name can be decided
; from it; a rename stays a name-lane action.
; The reconstructible C++ body (targets/game/reverse/attempts/0x006bd6e0.cpp,
; score 0.9892984542211652) compiles to 841 bytes with 22 relocations and
; shape 0.996; the whole residue is stack-slot placement for the snapshot
; index and the index cursor (retail keeps `i` at [esp+28h]/[esp+2Ch] and the
; cursor at [esp+24h]/[esp+28h]; VC7.1 parks the cursor in the dead
; incoming-argument slot and shifts the Snapshot spill to [esp+2Ch]), eight
; non-relocation bytes at +0xBB +0xC5 +0x219 +0x25F +0x2A9 +0x2AD +0x2B8
; +0x2BC, plus one trailing INT3 from the 841-byte compile. Dozens of
; formulations over seven sessions (flat scopes, top-of-loop error, index
; hoisted out of the for, cursor declared first/outside the loop, count
; declaration order, XferVersion union) never move the residues.
; Evidence: targets/game/reverse/identity_evidence/006bd6e0-masm-codegen-blocker.md

EXTERN g_Va0104972B:NEAR
EXTERN ?j_0003c1cd@@YAXXZ:NEAR
EXTERN ?j_0000c9b4@@YAXXZ:NEAR
EXTERN ?j_00009b01@@YAXXZ:NEAR
EXTERN ?j_00008ca1@@YAXXZ:NEAR
EXTERN ?ClientAt012F1464@@3PAVClient0009A580@@A:BYTE
EXTERN ?set@?$StringBase@D@@QAEXPBDH@Z:NEAR
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Create_Render_Obj@@YAPAVRenderObjClass@@PBDMH@Z:NEAR
EXTERN ?j_00030576@@YAXXZ:NEAR
EXTERN ??2@YAPAXI@Z:NEAR
EXTERN ??_7W3DRenderObjectSnapshot@@6B@:BYTE
EXTERN ?Rva012F8058@@3PAVRva00712F60@@A:BYTE
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?PlayerList005999B0@@3PAUPlayers005999B0@@A:BYTE
EXTERN ?j_0000914c@@YAXXZ:NEAR
EXTERN ??0XferException@@QAA@HPBDZZ:NEAR
EXTERN __TI1?AVXferException@@:BYTE
EXTERN ?ji_009f6d00@@YAXXZ:NEAR
_TEXT SEGMENT
; retail VA 0x00ABD6E0 size 840
public ?Rva006BD6E0@@YAXXZ
?Rva006BD6E0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0104972B
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 028h, 055h, 056h, 08Bh, 074h, 024h, 040h, 08Bh, 0E9h, 056h, 089h, 06Ch, 024h, 020h
    call ?j_0003c1cd@@YAXXZ
    db 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h, 010h, 084h, 0C0h, 00Fh, 085h, 0BCh, 002h, 000h, 000h, 08Bh
    db 016h, 0B0h, 001h, 088h, 044h, 024h, 020h, 088h, 044h, 024h, 021h, 057h, 08Dh, 044h, 024h, 024h
    db 050h, 08Bh, 0CEh, 0FFh, 052h, 028h, 08Dh, 085h, 000h, 001h, 000h, 000h, 050h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 08Bh, 016h, 083h, 0C4h, 008h, 08Dh, 085h, 00Ch, 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h
    db 078h, 08Bh, 08Dh, 004h, 001h, 000h, 000h, 033h, 0FFh, 03Bh, 0CFh, 074h, 00Bh
    call ?j_00009b01@@YAXXZ
    db 089h, 044h, 024h, 014h, 0EBh, 004h, 089h, 07Ch, 024h, 014h, 08Dh, 04Ch, 024h, 014h, 051h, 056h
    call ?j_00008ca1@@YAXXZ
    db 08Bh, 016h, 083h, 0C4h, 008h, 08Bh, 0CEh, 0FFh, 052h, 004h, 084h, 0C0h, 074h, 016h, 08Bh, 00Dh
    dd ?ClientAt012F1464@@3PAVClient0009A580@@A
    db 08Bh, 054h, 024h, 014h, 08Bh, 001h, 052h, 0FFh, 050h, 02Ch, 089h, 085h, 004h, 001h, 000h, 000h
    db 089h, 07Ch, 024h, 028h, 08Dh, 0BDh, 080h, 000h, 000h, 000h, 089h, 07Ch, 024h, 024h, 053h, 08Bh
    db 007h, 085h, 0C0h, 0C6h, 044h, 024h, 048h, 000h, 074h, 00Bh, 0FEh, 044h, 024h, 048h, 08Bh, 040h
    db 008h, 085h, 0C0h, 075h, 0F5h, 08Bh, 006h, 08Dh, 04Ch, 024h, 048h, 051h, 08Bh, 0CEh, 0FFh, 090h
    db 084h, 000h, 000h, 000h, 08Ah, 044h, 024h, 048h, 084h, 0C0h, 075h, 009h, 083h, 03Fh, 000h, 00Fh
    db 085h, 00Bh, 002h, 000h, 000h, 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h, 08Bh, 016h, 08Bh
    db 0CEh, 0C7h, 044h, 024h, 040h, 000h, 000h, 000h, 000h, 0FFh, 052h, 008h, 084h, 0C0h, 00Fh, 084h
    db 083h, 000h, 000h, 000h, 08Bh, 03Fh, 085h, 0FFh, 00Fh, 084h, 06Fh, 001h, 000h, 000h, 08Bh, 04Fh
    db 004h, 08Bh, 001h, 0FFh, 050h, 018h, 085h, 0C0h, 074h, 014h, 08Bh, 0C8h, 08Dh, 069h, 001h, 08Ah
    db 011h, 041h, 084h, 0D2h, 075h, 0F9h, 02Bh, 0CDh, 08Bh, 06Ch, 024h, 024h, 0EBh, 002h, 033h, 0C9h
    db 051h, 050h, 08Dh, 04Ch, 024h, 01Ch
    call ?set@?$StringBase@D@@QAEXPBDH@Z
    db 08Bh, 016h, 08Dh, 044h, 024h, 014h, 050h, 08Bh, 0CEh, 0FFh, 052h, 068h, 08Bh, 04Fh, 004h, 08Bh
    db 051h, 048h, 08Bh, 006h, 08Dh, 04Ch, 024h, 020h, 051h, 08Bh, 0CEh, 089h, 054h, 024h, 024h, 0FFh
    db 050h, 06Ch, 08Bh, 057h, 004h, 08Bh, 042h, 04Ch, 08Bh, 016h, 089h, 044h, 024h, 01Ch, 08Dh, 044h
    db 024h, 01Ch, 050h, 08Bh, 0CEh, 0FFh, 052h, 074h, 08Bh, 016h, 057h, 08Bh, 0CEh, 0FFh, 052h, 030h
    db 08Bh, 07Fh, 008h, 085h, 0FFh, 075h, 08Ch, 0E9h, 0F6h, 000h, 000h, 000h, 08Ah, 044h, 024h, 048h
    db 033h, 0DBh, 084h, 0C0h, 088h, 05Ch, 024h, 013h, 00Fh, 086h, 0E4h, 000h, 000h, 000h, 08Bh, 006h
    db 08Dh, 04Ch, 024h, 014h, 051h, 08Bh, 0CEh, 0FFh, 050h, 068h, 08Bh, 016h, 08Dh, 044h, 024h, 020h
    db 050h, 08Bh, 0CEh, 0FFh, 052h, 06Ch, 08Bh, 016h, 08Dh, 044h, 024h, 01Ch, 050h, 08Bh, 0CEh, 0FFh
    db 052h, 074h, 08Bh, 044h, 024h, 014h, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 04Ch, 024h, 01Ch, 08Bh, 054h, 024h, 020h, 051h, 052h, 050h
    call ?Create_Render_Obj@@YAPAVRenderObjClass@@PBDMH@Z
    db 08Bh, 0E8h, 083h, 0C4h, 00Ch, 085h, 0EDh, 00Fh, 084h, 024h, 001h, 000h, 000h, 055h
    call ?j_00030576@@YAXXZ
    db 06Ah, 00Ch
    call ??2@YAPAXI@Z
    db 08Bh, 0F8h, 083h, 0C4h, 008h, 089h, 07Ch, 024h, 030h, 085h, 0FFh, 074h, 02Eh, 08Bh, 044h, 024h
    db 024h, 06Ah, 000h, 005h, 000h, 001h, 000h, 000h, 0C7h, 007h
    dd ??_7W3DRenderObjectSnapshot@@6B@
    db 0C7h, 047h, 008h, 000h, 000h, 000h, 000h, 089h, 06Fh, 004h, 08Bh, 055h, 000h, 050h, 08Bh, 0CDh
    db 0C6h, 044h, 024h, 048h, 002h, 0FFh, 092h, 054h, 001h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 085h
    db 0DBh, 0C6h, 044h, 024h, 040h, 000h, 074h, 005h, 089h, 07Bh, 008h, 0EBh, 006h, 08Bh, 044h, 024h
    db 028h, 089h, 038h, 08Bh, 016h, 057h, 08Bh, 0CEh, 08Bh, 0DFh, 0FFh, 052h, 030h, 08Bh, 00Dh
    dd ?Rva012F8058@@3PAVRva00712F60@@A
    db 08Bh, 057h, 004h, 08Bh, 001h, 052h, 0FFh, 050h, 008h, 08Ah, 044h, 024h, 013h, 08Ah, 04Ch, 024h
    db 048h, 0FEh, 0C0h, 03Ah, 0C1h, 088h, 044h, 024h, 013h, 00Fh, 082h, 020h, 0FFh, 0FFh, 0FFh, 08Bh
    db 06Ch, 024h, 024h, 08Dh, 04Ch, 024h, 014h, 0C7h, 044h, 024h, 040h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 044h, 024h, 02Ch, 08Bh, 07Ch, 024h, 028h, 040h, 083h, 0C7h, 004h, 083h, 0F8h, 020h, 089h
    db 044h, 024h, 02Ch, 089h, 07Ch, 024h, 028h, 00Fh, 08Ch, 004h, 0FEh, 0FFh, 0FFh, 08Bh, 045h, 00Ch
    db 085h, 0C0h, 074h, 029h, 08Bh, 00Dh
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 08Bh, 051h, 00Ch, 08Bh, 042h, 024h, 08Bh, 08Ch, 085h, 080h, 000h, 000h, 000h, 085h, 0C9h, 074h
    db 012h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 004h, 084h, 0C0h, 074h, 007h, 08Bh, 0CDh
    call ?j_0000914c@@YAXXZ
    db 05Bh, 05Fh, 08Bh, 04Ch, 024h, 030h, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 034h, 0C2h, 004h, 000h, 06Ah, 000h, 08Dh, 044h, 024h, 034h, 06Ah, 004h, 050h
    call ??0XferException@@QAA@HPBDZZ
    db 083h, 0C4h, 00Ch, 068h
    dd __TI1?AVXferException@@
    db 08Dh, 04Ch, 024h, 034h, 051h
    call ?ji_009f6d00@@YAXXZ
    db 06Ah, 000h, 08Dh, 054h, 024h, 034h, 06Ah, 004h, 052h
    call ??0XferException@@QAA@HPBDZZ
    db 083h, 0C4h, 00Ch, 068h
    dd __TI1?AVXferException@@
    db 08Dh, 044h, 024h, 034h, 050h
    call ?ji_009f6d00@@YAXXZ
?Rva006BD6E0@@YAXXZ ENDP
_TEXT ENDS
END
