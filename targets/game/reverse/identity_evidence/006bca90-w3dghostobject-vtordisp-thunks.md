# 0x006BCA90..0x006BCB10 are W3DGhostObject's five vtordisp thunks

## Bodies

`python3 tools/dis_retail.py 0x006BCA90 0x90` shows five 14-byte thunks, 0x20 apart and int3-padded:

    sub ecx,[ecx-4] / sub ecx,0x98 / jmp <ILT>

| thunk      | ILT        | body       | body bytes                         |
|------------|------------|------------|------------------------------------|
| 0x006BCA90 | 0x00015DC0 | 0x001B3A60 | `lea eax,[ecx-0x64]; ret`          |
| 0x006BCAB0 | 0x00038BEA | 0x001B3A70 | `lea eax,[ecx-0x74]; ret`          |
| 0x006BCAD0 | 0x00043635 | 0x001B3A80 | `fld dword [ecx-0x68]; ret`        |
| 0x006BCAF0 | 0x0000B9DD | 0x001B3E30 | `mov [ecx-8],[esp+4]; ret 4`       |
| 0x006BCB10 | 0x000302DD | 0x001B3E50 | `mov eax,[ecx-8]; ret`             |

## Owner

- The rdata vtable 0x00D1CF8C holds exactly these five thunks, through ILTs 0x9D27, 0x24370, 0x48E41,
  0x13070 and 0xE1AB, followed by a zero.
- The matched `??0W3DGhostObject@@QAE@XZ` (0x006BCEC0, W3DGhostObjectAdd.cpp) has the hidden
  virtual-base flag. It stores the vbtable at +8 and the virtual base's vptr at +0x11c, installs
  0x0111CF8C (RVA 0x00D1CF8C) through the vbtable at +0x3A, and writes the vtordisp at +0x118.
- The bodies are also reached, through the same ILTs, by GhostObject's own vtordisp{-4,0} thunks
  0x001B3DF0..0x001B3E40. Those are matched in VirtualBaseThunks.cpp under per-address class names.
  So the bodies are GhostObject's overrides of the virtual base's five functions, with the virtual base
  at +0x84 in GhostObject. 0x11c - 0x84 = 0x98, the thunks' static adjustment.
- targets/game/reverse/ea_evidence.csv maps 0x006BCA93 to EA's GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObject.cpp
  (retail-run), not to an RTS scene file.
- No caller, string or symbol names the five functions, so the methods keep address-derived names
  (`GhostObject::rva001B3A60` and the others). The virtual base keeps the source's opaque name
  `GhostVirtualBase`.

## What the old rows were

- `??_ERTS2DScene@@WJI@AEPAXI@Z` and `??_ERTS3DScene@@WJI@AEPAXI@Z` were both claimed at 0x006BCA93/11,
  three bytes into the first thunk.
- The pins `??_ERTS2DScene@@UAEPAXI@Z` / `??_ERTS3DScene@@UAEPAXI@Z` named ILT 0x00015DC0, which jumps
  to 0x001B3A60, not to a deleting destructor.
- `?j_006bcab9`, `?j_006bcad9`, `?j_006bcaf9` and `?j_006bcb19` (gen_small/gthunks_085.cpp) claimed
  the jmp tails at +9 of the other four thunks as 5-byte thunks.

## Verification

W3DGhostObjectAdd.cpp declares the five slots on GhostVirtualBase, overrides them in GhostObject and
not in W3DGhostObject. MSVC then emits `?rva001B3A60@GhostObject@@$4PPPPPPPM@JI@BEPAXXZ` and the four
siblings, and each probes EXACT against retail. The file's four other matched bodies (ctor 343 B, dtor
48 B, deleting dtor 30 B, addGhostObject 203 B) stay EXACT.
