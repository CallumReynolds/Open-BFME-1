# 0x002A59F0 returns Bool: `?needToFace@Gen_002A59F0@@QBE_NXZ`

Retired claim: `?needToFace@Gen_002A59F0@@QBEHXZ` (45 bytes, SpecialAbilityUpdate_update.cpp), an int
return kept byte-true only by an inline `xor al,al; ret` block.

Only the return type changes; the opaque owner `Gen_002A59F0` and method name are kept.

## Evidence (retail 1.03 unpacked, tools/dis_retail.py 0x2A59F0 45)

- Shape is ZH `SpecialAbilityUpdate::needToFace() const` (GeneralsMD SpecialAbilityUpdate.cpp:1874):
  `getObject()` (+0x08) `->getAIUpdateInterface()` (Object +0x204) null -> `return false`; then
  `return !m_facingInitiated || !m_facingComplete;` (bytes +0xE0 / +0xE1). ZH declares it `Bool`.
- Retail returns the constant false as a byte (`xor al,al`) and the logical tail as full-width 0/1
  (`xor eax,eax` / `mov eax,1`). That mix is what MSVC 7.1 emits for a `bool` return: a constant is
  materialised at return width, a logical expression is computed as int 0/1 and truncated. An int return
  merges the two zeros (42 B, four prior sessions); a `return 0/1` bool body gives `mov al,1` (39 B).
- The only caller, update 0x002AA9D0 in the same TU, tests only AL after the call (`test al,al`), i.e. a
  byte-wide result.
- The clean bool body (no asm) compiles EXACT: `tools/probe.py ... '?needToFace@Gen_002A59F0@@QBE_NXZ'
  0x2A59F0 --size 45` -> EXACT, and the caller's call reloc resolves to the new name.
