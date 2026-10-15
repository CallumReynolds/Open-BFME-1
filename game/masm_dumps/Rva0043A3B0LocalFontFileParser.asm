.386
.model flat
; ?parseFontFileName@GlobalLanguage@@SAXPAVINI@@PAX1PBX@Z
; Retail @ 0x0043A3B0 size 203
;
; MASM dump carrying a measured codegen blocker. Identity is proven first-hand:
; the FieldParse row at VA 0x010F3B18 (table 0x010F3AD8) pairs the string
; "LocalFontFile" (VA 0x010F3FDC) with the ILT thunk at VA 0x004178FF, whose
; jmp rel32 targets this body; the Zero Hour reference source names that row
; GlobalLanguage::parseFontFileName with this exact signature, and
; symbols.csv already pins the name at 0x0043A3B0. ABI from decode: static
; FieldParse callback (INI *, void *instance, void *store, const void *
; userData); SEH frame `push -1; push g_Va010228C9`; the instance's local-font
; list pointer sits at +0x134. The body reads one AsciiString token, default
; constructs the eight-byte two-AsciiString record on the stack, sets the
; record's first string to the token, then appends the record to the list:
; STLport _M_create_node allocates the 0x10-byte node and the out-of-line
; record copy constructor at 0x00439370 is called through the ILT 0x00020BAD
; thunk, with the insert-before-end splice and the three releaseBuffer cleanup
; calls after it.
;
; The reconstructible C++ body (targets/game/reverse/attempts/0x0043a3b0.cpp)
; compiles to exactly 203 bytes with 11 relocations and shape 1.000; its whole
; residue is two non-relocation bytes at +0x76 and +0x7A, where the pushed
; record-address temporary uses EAX instead of retail's EDX. The wall is
; measured, not assumed: earlier waves recorded thirteen spellings plus a
; seventeen-flag sweep, 33 shape-family/EH trials (sib register bool test copy
; store loop branch constant frame x four combinations plus throw/ehsc/stlp/
; nodelete and callee-throw variants), 10 rotation-sweep call and local forms,
; and operator=, insert(end(), x), volatile-pointer-alias and const-reference
; variants. This session added 16 fresh spellings (reference receivers,
; forced-inline helpers taking the list and the record, an explicit
; _STL::_Construct<Open2Rec439370, Open2Rec439370> instantiation, an iterator
; temp with insert, typedef, comma and deref forms) and a 10-flag sweep
; (/Os /Ot /G7 /G6 /GR- /Op- /O2+Og- /O2+Ob1 /GA /Gf); every shape-preserving
; trial lands on the identical two bytes, while /Os (107 B) and /O2+Og- (167 B)
; lose the 203-byte shape entirely. docs/shape_levers.md records this address's
; residual and states the register-only sweeps are exhausted. The dump body is
; byte-identical to retail outside its relocation slots.
; Evidence: targets/game/reverse/identity_evidence/0043a3b0-masm-codegen-blocker.md
EXTERN g_Va010228C9:NEAR
EXTERN ?getNextAsciiString@INI@@QAE?AVAsciiString@@XZ:NEAR
EXTERN ?set@?$StringBase@D@@QAEXABV1@@Z:NEAR
EXTERN ?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z:NEAR
EXTERN ?j_00020bad@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
_TEXT SEGMENT
public ?parseFontFileName@GlobalLanguage@@SAXPAVINI@@PAX1PBX@Z
?parseFontFileName@GlobalLanguage@@SAXPAVINI@@PAX1PBX@Z PROC
    db 06Ah, 0FFh, 068h
    dd g_Va010228C9
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 010h, 08Bh, 04Ch, 024h, 020h, 053h, 056h, 057h, 08Dh, 044h, 024h, 00Ch, 050h
    call ?getNextAsciiString@INI@@QAE?AVAsciiString@@XZ
    db 033h, 0DBh, 089h, 05Ch, 024h, 024h, 089h, 05Ch, 024h, 014h, 089h, 05Ch, 024h, 018h, 08Dh, 04Ch
    db 024h, 00Ch, 051h, 08Dh, 04Ch, 024h, 018h, 0C6h, 044h, 024h, 028h, 001h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 08Bh, 054h, 024h, 030h, 08Bh, 082h, 034h, 001h, 000h, 000h, 08Bh, 038h, 06Ah, 010h
    call ?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z
    db 08Bh, 0F0h, 08Dh, 04Eh, 008h, 083h, 0C4h, 004h, 089h, 04Ch, 024h, 030h, 089h, 04Ch, 024h, 010h
    db 03Bh, 0CBh, 0C6h, 044h, 024h, 024h, 002h, 074h, 00Ah, 08Dh, 054h, 024h, 014h, 052h
    call ?j_00020bad@@YAXXZ
    db 08Bh, 047h, 004h, 089h, 03Eh, 089h, 046h, 004h, 089h, 030h, 089h, 077h, 004h, 08Dh, 04Ch, 024h
    db 018h, 0C6h, 044h, 024h, 024h, 003h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 014h, 088h, 05Ch, 024h, 024h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 00Ch, 0C7h, 044h, 024h, 024h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 04Ch, 024h, 01Ch, 05Fh, 05Eh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h, 0C4h
    db 01Ch, 0C3h
?parseFontFileName@GlobalLanguage@@SAXPAVINI@@PAX1PBX@Z ENDP
_TEXT ENDS
END
