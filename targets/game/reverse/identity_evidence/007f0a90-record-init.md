# Initialization at 0x007F0A90

The previous body at 0x007F0A80 returns at +3 and is followed by twelve INT3 bytes. The target begins at 0x007F0A90 and returns at +0x2E, followed by one INT3 before the next body at 0x007F0AC0. Its extent is exactly 47 bytes, with no branches, calls or relocation operands. It receives a record pointer in ECX, returns that same pointer in EAX and consumes no stack arguments.

All written fields are represented explicitly: zero at +0, -1 at +4, zero at +8 through +0x18, byte 1 at +0x1C, byte 0 at +0x1D, -1 at +0x20 and +0x24, and zero at +0x28 and +0x2C. Padding at +0x1E and +0x1F is not written. The opaque Rva007F0A90Record name claims no original owner identity or field semantics. The constructor spelling describes this no-argument initialization shape; the Python ILT API reports UNTESTABLE.

Open BFME 2 donor Code/GameEngine/Source/Common/SmallGaps/Rva007F0910RecordCtor.cpp at game.dat 0x0065D760 supplies precisely this initializer list and field-width layout. The port emits 47 identical bytes with zero relocations. A differing field width, store offset, endpoint or byte would refute the port. Raw evidence: build/donor-port/record/history.log, build/donor-port/record/retail.log, build/donor-port/record/callees.log, build/donor-port/record/port-probe.log and build/donor-port/record/oracle.log.
