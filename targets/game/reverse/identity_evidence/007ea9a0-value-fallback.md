# Word accessor at 0x007EA9A0

The preceding 0x007EA970 accessor returns at +0x23 and is followed by twelve INT3 bytes. The target begins at 0x007EA9A0 and ends with RET at +0x1D, followed by two INT3 bytes before 0x007EA9C0. Its complete extent is 30 bytes. Both conditional branches remain within the body; the other exit is an indirect virtual tail jump at +0x18.

The incoming ECX receiver supplies an inner pointer at +4. The body reads one 32-bit word at inner +0x228 and returns it in EAX when nonzero. Otherwise it reads the optional source at inner +0x0C. A null source returns zero. A nonnull source becomes ECX and its virtual slot +0x20 is tail-called without stack arguments. This establishes the thiscall receiver adjustment, eight preceding virtual slots, unchanged return-address stack and 32-bit result width. Signedness and original owner identity are unknown. The Rva007EA9A0 names and opaque padding retain that uncertainty; no original API name or source-object implementation is inferred from the donor.

Open BFME 2 donor Code/GameEngine/Source/GameNetwork/Rva007EA970TextFallback.cpp at game.dat 0x00657940 supplies the same nested-word and optional-fallback structure. The port emits 30 exact bytes without relocation sites. It is appended beside the existing text accessor with its existing /O2 flags. A different inner offset, argument stack, virtual slot, return width or non-relocation byte would refute it. There is no owned member, container or exception handler in the target. The Python ILT API reports UNTESTABLE for the address-derived owner.

Raw evidence: build/donor-port/value/history.log, build/donor-port/value/retail.log, build/donor-port/value/callees.log, build/donor-port/value/port-probe.log and build/donor-port/value/oracle.log.
