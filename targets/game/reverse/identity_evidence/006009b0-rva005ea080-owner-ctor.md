# 0x006009B0 is a constructor of class Rva005EA080, not BaseY005E7940

Retail `0x006009B0` (440 B) ends its vptr stage (+0x70..+0x7d) with
`[esi]=0x01112A88`, `[esi+4]=0x0111270C`, `[esi+8]=0x011126F8`. The landed
forwarding constructor `??0Rva005EA080@@QAE@I@Z` (0x005EA080, 62 B) stamps
the identical three constants at the identical offsets (`tools/dis_retail.py
0x005EA080 62`).

`targets/game/reverse/dir32_addresses.csv` records these addresses only as
Rva005EA080 vftables:
- 0x01112A88 `??_7Rva005EA080@@6BT4P0_Rva005E9AE0@@@` (sole name)
- 0x0111270C `??_7Rva005EA080@@6BT4A2_0110F9E8@@@` (plus Rva005E7A30/7AA0
  variants, which are other classes' bases)
- 0x011126F8 `??_7Rva005EA080@@6B@`

Retail was linked without COMDAT folding, so each vftable has one owner; a
body that stamps a class's own final vftables is that class's constructor.
The earlier base-subobject stores (0x0110F9E8 at +4, 0x01112A98 at +8, the
13-dword value block T4B005EA0D0) match the L2 model
`T4_TWO_BASE_FORWARD( 005EA080, Rva005E9AB0, T4B005EA0D0 )`.
Caller: HostY005E7940::create (0x005E7940) calls the ILT thunk 0x00049184 ->
0x006009B0 with `this - 0x14`; it then stamps its own, different vptrs
(0x011126BC/0x011126B8/0x011126A4), so it is a derived class of Rva005EA080.
The byte-exact reconstruction (probe EXACT 440/440) uses the recorded names.
