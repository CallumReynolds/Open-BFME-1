.386
.model flat
; ??0RankPoints@@QAE@XZ  -- retail 206 B @ 0x004DAFA0.
; BFME RankPoints is 0x30 bytes: int m_ranks[10] (0x00..0x27), float
; m_winMultiplier (0x28 = 3.0f), float m_lostMultiplier (0x2C = 1.0f); the
; Zero Hour source in PopupPlayerInfo.cpp carries four extra trailing floats
; and is not this body.  Layout confirmed by the landed consumers
; PopupPlayerInfoRankPointsFromStats.cpp (bfmeRankPointsFromStats, 0x004DA980)
; and PopupPlayerInfoCalculateRank.cpp, which weight by +0x28/+0x2C.
;
; The constructor seeds m_ranks[0]=0 and then calls the GameSpyConfig
; interface's virtual getPointsForRank slot +0x28 for ranks 1..9 (the same
; slot the ILT at 0x000106EA routes to), storing results at +4..+0x24, then
; the two multipliers.  A bare VC7.1 EH frame wraps it: the FuncInfo at
; 0x00E1B278 (handler 0x00C2AD50) carries one unwind state -> -1 with no
; cleanup action and no try blocks, so the body has no state stores.
;
; C++ blocked: no tested spelling of the source produces that frame.  Dead
; lifetimes (declared-only destructor types in an if(0) scope) register no EH
; frame at all once they are the function's only EH (measured on the same
; cl 13.10.3077 / -O2 -EHsc toolchain), and a live declared-only destructor
; emits a real cleanup action instead of retail's null one.  A naked pose
; over the C++ body is 206 bytes of exact text but the compiler appends its
; ctor return-this tail (8Bh,045h,0FCh = mov eax,[ebp-4]) after the ret, so
; the TU stays byte-assembled.  All call sites, operand encodings and the
; [esp+4] FS restore come from the retail bytes, not from a dump guess.

EXTERN ?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A:BYTE

_TEXT SEGMENT
public ??0RankPoints@@QAE@XZ
??0RankPoints@@QAE@XZ PROC
    db 064h,0A1h,00h,00h,00h,00h,06Ah,0FFh,068h,050h,0ADh,02h,01h,050h,064h,089h,025h,00h,00h,00h,00h,056h,08Bh,0F1h,0C7h,06h,00h,00h,00h,00h
    db 08Bh,00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A
    db 08Bh,01h,06Ah,01h,0FFh,050h,028h,089h,046h,04h
    db 08Bh,00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A
    db 08Bh,011h,06Ah,02h,0FFh,052h,028h,089h,046h,08h
    db 08Bh,00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A
    db 08Bh,01h,06Ah,03h,0FFh,050h,028h,089h,046h,00Ch
    db 08Bh,00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A
    db 08Bh,011h,06Ah,04h,0FFh,052h,028h,089h,046h,010h
    db 08Bh,00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A
    db 08Bh,01h,06Ah,05h,0FFh,050h,028h,089h,046h,014h
    db 08Bh,00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A
    db 08Bh,011h,06Ah,06h,0FFh,052h,028h,089h,046h,018h
    db 08Bh,00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A
    db 08Bh,01h,06Ah,07h,0FFh,050h,028h,089h,046h,01Ch
    db 08Bh,00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A
    db 08Bh,011h,06Ah,08h,0FFh,052h,028h,089h,046h,020h
    db 08Bh,00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A
    db 08Bh,01h,06Ah,09h,0FFh,050h,028h,08Bh,04Ch,024h,04h,089h,046h,024h,0C7h,046h,028h,00h,00h,040h,040h,0C7h,046h,02Ch,00h,00h,080h,03Fh,08Bh,0C6h,064h,089h,00Dh,00h,00h,00h,00h,05Eh,083h,0C4h,00Ch,0C3h
??0RankPoints@@QAE@XZ ENDP
_TEXT ENDS
end
