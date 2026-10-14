# 0x003CAE00/45 is a LivingWorldRegionManager member, not a free __stdcall

The matched row spelled the body `?bfmeGoFHA@@YG_NPAUBfmeArgFHA@@@Z`, a free `__stdcall`
function. Both names are placeholders.

## The only call site

Retail 0x003A4FD0 (`Rva003A4FD0State::update`) is the only caller: `whocalls.py` finds
one reach, through ILT 0x00003611. That caller:

- loads ECX from `Glo012F1028+0x28`, the living-world region manager it also uses as
  `this` for the neighbouring 0x003C8160 and 0x003C9CB0 member calls (both matched as
  `LivingWorldRegionManager` methods);
- pushes the region and calls.

A free `__stdcall` call never sets up ECX, so the call is `__thiscall`.

## The body

The body never reads ECX and ends `ret 4`. A `__thiscall` member that ignores `this`
compiles to exactly the bytes the `__stdcall` spelling did, so the bytes cannot tell the
two apart; the caller can. It reads the region's flag at +0xA8 and passes its +0xB4 value
twice to the cdecl helper (unchanged, `bfmeCallFHA`).

## Change

- The row becomes `?rva003CAE00@LivingWorldRegionManager@@QAE_NPAVLivingWorldRegion@@@Z`,
  still address-derived, defined in BfmeConv897.cpp.
- This lets 0x003A4FD0 land without the `/alternatename` its bank used.
