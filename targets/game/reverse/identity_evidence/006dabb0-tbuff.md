# 0x006DABB0 / 0x006DB470: TBuff destructor and constructor

The class whose vtable is 0x0111E134 (`??_7TBuff@@6B@` in symbols.csv) is EA's
`TBuff`:

- `targets/game/reverse/ea_evidence.csv` names 0x006DB470 `TBuff::TBuff`
  (chain+direct, strong) and places 0x006DABB0, 0x006DB470 and 0x006DB540 in
  `GameEngineDevice/Source/W3DDevice/GameClient/W3DBuffBuffer.cpp`.
- Vtable slot 0 routes through ILT 0x00009444 (`??_GTBuff@@EAEPAXI@Z`) to the
  matched scalar deleting destructor 0x006DB540, which calls ILT 0x0003AF5D
  (`??1TBuff@@EAE@XZ`), the jump stub to 0x006DABB0.
- Slot 3 is the matched `TBuff::xfer` (0x006DBD00); 0x006DAC30 returns the
  literal "TBuff".
- 0x006DB470 and 0x006DABB0 install the same vtable and adjust the same
  instance counter 0x012F801C (increment and decrement).

So the matched destructor row `??1Rva006DABB0@@UAE@XZ` is `TBuff::~TBuff`,
private virtual as the existing pin decorates it, and the constructor is
`TBuff::TBuff(Drawable *, int)`. The constructor's source argument is a
Drawable: it calls Drawable::getScale (ILT 0x0003939C) and
Drawable::getPosition (ILT 0x0004B12D). Both bodies compile byte-exact in
game/GameEngine/Source/Common/Bfme/Rva006DABB0Destructor.cpp.
