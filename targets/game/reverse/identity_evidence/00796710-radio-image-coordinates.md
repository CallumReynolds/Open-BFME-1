# Radio-button image callback at00796710

The actual-RVA ilt_oracle API confirms the real spelling
?W3DGadgetRadioButtonImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z.
The matched radio dispatcher007969E0 and Zero Hour W3DRadioButton.cpp
independently support the same callback. Retail RET+0x21A and INT3+0x21B
establish539 bytes. Two pointer arguments remain caller-cleaned.

Starting bank:546B/310nonrelocation differences, first+6. Reusing the empty
coordinate constructor established by matched sibling00796480 yields533B,
203differences and the first193bytes exact. It adds no stores or fields.
Retail Display calls use slots+88/+90; the bank's Zero Hour header uses+68/+70.
Correcting the TU-local virtual interface reproduces539B with just one byte
wrong: text length must call+0C, not+10. Both Display slots are also witnessed
by matched W3DPushButtonImageDrawVertical00794790.cpp. Existing home-TU
Rva00796480InstanceData supplies the verified text interface. With these
views the callback probes EXACT539B with9relocations.

Production reuses W3DRadioButtonText.cpp, its matched static text helper,
canonical ICoord2D/WinInstanceData declarations, and existing constructor
wrapper. No shared header, pin, generated source, or baseline changes.
The image-array view at window+30 comes from the preferred bank and all
corresponding loads agree with retail. Virtual views change only dispatch
slots, not object storage; no alternate-name binding or numeric address call.

Direct callees, read before reconstruction: GameWindow::winGetScreenPosition
via ILT2F94B->4781D0, winGetSize via36EBC->4782A0, winGetStatus via23DDA->478480,
and the existing same-TU drawRadioButtonText at796310. The latter takes
window in ECX and instance data in EAX, as its verified body already does.
The two matched sibling bodies remain part of strict whole-TU validation.

Raw evidence and probes: build/worker3-round41/{identity.json,boundary.asm,
base.log,native.log,slots.log,home.log}. No speculative descriptive renames.
