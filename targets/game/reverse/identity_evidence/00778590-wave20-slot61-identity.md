# RVA 0x00778590 is the W3DModelDraw-family slot 61 (+0xF4) virtual; best-supported name `W3DModelDraw::setModelState(newState, Bool, ModelConditionInfo*)`

Wave 20, agent H. Result: owner slot, boundary, ABI, argument roles and the
two module-data state lookups are resolved from retail bytes and matched
neighbours. The spelled method name is not provable from the exe (no RTTI,
no BFME headers), but `setModelState` remains the best-supported candidate.
No byte-exact rebuild was attempted; no bank.

## 1. Slot membership (owner class proven)

`tools/vtable_lookup.py --target 0x00778590`: RVA 0x00778590 is slot 61
(+0xF4) through ILT 0x0041FC44 in six tables:

| table | class | evidence |
|---|---|---|
| 0x01123D38 | W3DModelDraw-chain base (primary, ctor 0x00773360) | dir32_addresses.csv; 0076b980-scriptedmodel-condition.md |
| 0x01122EA8 | W3DPoliceCarDraw (= W3DTruckDrawPrimaryBase) | dir32_addresses.csv |
| 0x01123390 | W3DQuadrupedDraw | dir32_addresses.csv |
| 0x011256D0 | W3DSupplyDraw | dir32_addresses.csv |
| 0x01125AB0 | W3DTankDraw | dir32_addresses.csv |
| 0x011265B0 | W3DTruckDraw | dir32_addresses.csv |
| 0x01122470 | W3DHordeModelDraw slot 61 -> ILT 0x00430F94 -> 0x00755F70 | only family override |

All six tables also share slots 59/62/63 (thunks 0x00438c53, 0x0042c589,
0x004494f9); only slot 60 and 61 differ among some of them. So the target is
the shared base implementation of one W3DModelDraw virtual that
W3DHordeModelDraw overrides, not a ModelConditionInfo method.

## 2. ABI from retail bytes

* SEH prologue `push -1; push 0x01050126`; frame `sub esp,0x17C`.
* Stack args: `[esp+0x19C]` = arg1 (pointer), `[esp+0x1A0]` = arg2
  (1 byte: read only as `mov al,[esp+0x1A0]; test al,al`), `[esp+0x1A4]` = arg3
  (pointer). Shared epilogue at +0xF8F: `ret 0xC` then INT3. 3 rets total.
* Result is `Bool` in AL: `xor al,al` return-false path at +0x86 and
  `mov al,1` success at +0xF75 followed by the shared epilogue.
* 4 `__ftol2` sites; 52 direct callees, every one ledger-named
  (`tools/callees.py 0x00778590 3986`).

## 3. Behavior landmarks (base body, /tmp/a8_778590_rel.asm)

* +0x26 `if (moduleData[0x133] && this[0xA0]) return false`
* +0x3C `if (!arg1) return false` (nullable argument)
* +0x47 `call 0x431F75(this=this[8] /*drawable*/, &arg1[0x3C])` — arg1 carries
  AsciiString-shaped data at +0x3C and a byte at +0x38
* +0x53 `changed = (this[0xA0] != this[0xA4]); this[0xA0] = this[0xA4];`
* +0x65 `if (this[0x10] && this[0x10] == arg1 && !changed && !arg2) return false`
* +0x8D `if (!(drawable[0x110] & 8)) this[0x2C] = 1;` then `push 1; call 0x41EBF5`
* +0xA6..+0xB3 `0x75FB90(arg1, arg3, this[0x34] /*m_renderObject*/)`
* +0xBF.. m_curState path: AsciiString work (0x412A7B x2, 0x4220C5)
* render-object rebuild region (matched callees): nukeCurrentRender 0x75C050,
  Create_Render_Obj 0x901F80, rebuildWeaponRecoilInfo 0x770FA0 (called at +0x8FD
  with arg3), attachable-submodel pass 0x769720, direct call turretNamesDiffer
  0x75C240 at +0x116, TextureSelection::collect 0x7781C0, resolveModelVariant
  0x7739F0
* tail +0xF20 `this[0x171] = 1; this[0x10] = arg1; return true`

The Horde override 0x00755F70 (table 0x01122470, ILT 0x00430F94) has the same
argument footprint (`arg1` at `[esp+0x188]` pointer, `arg2` byte at
`[esp+0x18C]`) and the same `[+0xA0]/[+0xA4]` copy, `m_curState == arg1 &&
!changed && !arg2 -> return false` early-out, i.e. one shared 3-argument
virtual interface with a W3DHordeModelDraw override.

## 4. Call sites (only three reach this body)

Exe-wide byte scan for `call [reg+0xF4]` finds 114 sites (wave 19, re-run in
wave 20); the three with a W3DModelDraw-family receiver were each disassembled
and verified:

1. **0x76E8F1** inside the row-less SEH function 0x0076E7F0 (ledger gap:
   row 0x76E7D0 is 26 bytes, next row 0x76E90A; 0x76E7F0..0x76E909 is
   unpartitioned): `push edi; push 0; push ebx; mov ecx,esi; call [edx+0xF4]`
   with ebx = 0x765B70(flags) result (arg1; when null the caller throws
   INIException 0x01123B88 = "*** ASSET ERROR: all draw modules must have a
   default model state") and edi = 0x765DC0(flags) result (arg3), arg2 = 0.
2. **0x76BD02** in matched W3DScriptedModelDraw::replaceModelConditionState
   (row 0x76B980): arg3 = 0x765DC0 result (or `[ebp+8]` swap), arg1/arg2 =
   frame dwords; `ecx = ebp-0xC` (the base subobject of vtable 0x01123D38).
3. **0x75C36A** in matched `?bfmeSetXP@BfmeOwnerXP@@QAEXI@Z`
   (BfmeConv1849.cpp, 85B): `push ecx; push 0; push eax; call [edx+0xF4]`,
   i.e. (old current value, 0, new value).

## 5. Argument typing

* **arg1** = pointer to the module-data condition-state record selected by
  0x765B70 (vector at module data +0x18/+0x1C, records stride 0x128, default
  index at module data +0x4C; this is the lookup whose null result is the
  "default model state" asset error). It is stored into `[this+0x10]`
  (m_curState slot of the family layout used by Select0076B800.cpp) and read at
  +0x38 / +0x3C / (via 0x75FB90) +0x120.
* **arg2** = 1-byte Bool, "force/restart" role in the duplicate-state
  early-out. Sites 1 and 3 pass 0; site 2 passes a frame dword. Never a
  pointer (only the low byte is read).
* **arg3** = `const ModelConditionInfo*` from the second lookup 0x765DC0
  (vector at module data +0x24/+0x28, records stride 0xBC with mask at +4,
  matched source W3DModelDrawModuleDataRva00765DC0.cpp). It is forwarded to
  matched 0x770FA0 `rebuildWeaponRecoilInfo(const ModelConditionInfo* state)`
  at +0x8FD and as second argument of matched 0x75FB90
  (Gen0075FB90RecoilVectorRelease): there it exposes four 12-byte barrel
  vectors at +0x7C..+0xA4 and a flag byte at +0xAC, matching the matched
  0x770FA0 note "state barrel vectors start at +0x7C in ModelConditionInfo"
  and "four-slot recoil vectors at W3DModelDraw+0xAC". 0x75FB90 guards arg3
  for null.

## 6. Twin and BFME interface precedent

Zero Hour `void W3DModelDraw::setModelState(const ModelConditionInfo*)`
(inputs/reference/CnC_Generals_Zero_Hour/.../W3DModelDraw.cpp:2911; declaration
Include/.../W3DModelDraw.h:439) is the role twin: it is the only writer of
m_curState and performs the same render-object rebuild, but it is 1-argument
and void, so it cannot match the retail `ret 0xC` Bool body. BFME widened
family virtuals with the same pattern: matched Drawable::updateDrawable
0x0041BE60 calls replaceModelConditionState with three arguments
(identity_evidence/0076b980-scriptedmodel-condition.md), and the present
unmatched twin in game/.../Draw/W3DModelDraw.cpp:2977+ is this method.

## 7. Refuted

`?validateCachedBones@ModelConditionInfo@@ABEXPAVRenderObjectClass@@@Z`
(ledger row 126410): declared ModelConditionInfo method returning void with
ret 4/8, versus retail slot-61 vtable membership of six W3DModelDraw tables,
`ret 0xC`, and a Bool AL result. The label is a stand-in only.

## 8. Remaining unknowns for the byte-exact rebuild

1. Exact spelled method name and member names cannot be proven from the exe.
2. arg1's record type (stride 0x128) versus arg3's ModelConditionInfo
   (stride 0xBC): both live in W3DModelDrawModuleData, so BFME carries two
   state-record vectors; whether arg1 is literally `const ModelConditionInfo*`
   is unresolved.
3. The exact meaning of arg2 (force vs restart) and of the +0xA0/+0xA4 pair.
4. The 10 EH states and the full render-object rebuild body must be modeled
   before byte-exactness; the present twin is a starting point only.
