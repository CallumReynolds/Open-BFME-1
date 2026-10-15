# 0x0022C2A0 clean C++ transfer (replaces the MASM dump)

The MASM dump `game/masm_dumps/Rva0022C2A0SeedAccept.asm` carried this
559-byte body under the placeholder `?Rva0022C2A0@@YAXXZ`, a free function
with no arguments. That placeholder's ABI is wrong, and the clean C++ body
replaces it with the ABI-correct opaque member
`?method@Rva0022C2A0@@QAEXPAVXfer@@@Z`. No EA name is claimed.

## Receiver and argument

- Slot +0C of the primary vtable at VA 0x010AD088 holds ILT 0x00016027 (VA 0x00416027)
  (`e9 74 62 21 00`), which jumps to RVA 0x0022C2A0. The complete
  SiegeEngineContain constructor at 0x0022BC50 installs that table, so the
  body is a thiscall member with no receiver adjustment.
- The body ends `ret 4` at +0x22C, and every stack argument use is the
  Xfer receiver of the transfer virtuals (+0x08 storing, +0x10 light-CRC,
  +0x28 version, +0x74/+0x78/+0x8C value transfers). That is one Xfer*
  argument and no return value.

## Twin evidence

The body is field-for-field the twin of 0x0024ABA0 (`Rva0024ABA0::method`,
HordeSiegeEngineContain, landed df4588d44b). Its primary vtable 0x010B02A8
slot +0C reaches 0x0024ABA0 through ILT 0x0003E99B the same way. Every
this-relative offset is eight lower here, and the leading seed call goes to
Gen_0022CD40::bfmeSeed (0x0022CD40, ILT 0x0003D37A) instead of
Gen_0024B870::bfmeSeed. The same source, with those changes, compiles EXACT
modulo the 12 relocation slots.

## The former codegen blocker

The MASM evidence (0022c2a0-masm-codegen-blocker.md) recorded seven
count/key frame-slot bytes. Those bytes are a source-shape question, not a
compiler wall. The body matches when one function-scope objectID is shared by
both list loops, which lets it win the dead Xfer argument slot. Each map
branch has its own count local, and the save loop copies key and value into
two int locals instead of a std::pair. A `/FAsc` `_name$` table of the match
shows version -16, both counts -12, save key -8 and value -4, load value -8
and key -4, and objectID +8.

The retired dump name `?d_0022c2a0@@YAXXZ` stays as an address-only
compatibility pin because S3SeedPairsSweep.cpp still takes the body by that
name.
