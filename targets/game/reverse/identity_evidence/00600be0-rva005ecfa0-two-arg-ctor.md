# 0x00600BE0 is a two-argument constructor of class Rva005ECFA0, not T1Base_00600BE0

After its base calls retail `0x00600BE0` (440 B) stamps `[esi]=0x0111327C`,
`[esi+0x14]=0x01113278`, `[esi+0x18]=0x01113274` and `[ebx=esi+0x1C]=0x01113290`.
The landed copy constructor `??0Rva005ECFA0@@QAE@ABV0@@Z` (0x005ECFA0) stamps
the same four constants at the same offsets (`tools/dis_retail.py 0x005ECFA0 89`).
`targets/game/reverse/dir32_addresses.csv` records these addresses only as the
Rva005ECFA0 vftables (`6BV3Slot0` / `6BV3Slot1` / `6BV3Slot2` / `6B@`).
Retail has no COMDAT folding, so each vftable has one owner; a body stamping a
class's final vftables is that class's constructor.

Bases, as in the 0x005ECFA0 model: the V3Mid01113190 head chain (stamps
0x01113190/0x0111318C/0x01113188; here its constructor is inlined, with the
0x005DD290 call and the secondary bases' own 0x0111089C / 0x0110F9E8 stamps)
and FXParticleSystem::RenderObjectUpdateModuleInfo at +0x1C (call 0x00600460,
a matched row).  The caller 0x005E78A0 (T1Derived_005E78A0 in
T1BaseForwardingCtors.cpp) forwards its two arguments here and then stamps its
own vptrs, so it is a derived class.  Byte-exact (probe EXACT 440/440).
