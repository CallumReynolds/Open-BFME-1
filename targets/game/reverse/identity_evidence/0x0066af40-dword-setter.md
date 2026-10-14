# `GameLogic::rva0066AF40` at 0x0066AF40 (was `Object::setSafeOcclusionFrame`)

- **Body.** 13 bytes: `mov eax,[esp+4] / mov [ecx+0x290],eax / ret 4`, a plain dword-field setter
  (tools/dis_retail.py 0x0066AF40 13).
- **Why the old name is retired.** The row carried the Zero Hour name only because the ZH-shaped
  GarrisonContain::onRemoving copy in GarrisonContain.cpp emitted that inline. No BFME evidence puts
  the safe occlusion frame at +0x290:
  - the matched Object::bfmeResetSafeOcclusionFrame (0x001C3020, ObjectTemplateQueries.cpp) stores a
    frame at +0x334;
  - the retail-equal GarrisonContain::onRemoving (0x0021F0A0, GarrisonContain_onRemoving.cpp) stores
    one inline at +0x330 and does not call this body.
- **Retail never calls it.** A scan of the whole image for rel32 calls, jumps and DIR32 words that
  target 0x0066AF40 or its ILT thunk 0x00016FD1 finds one hit: the thunk's own `jmp`.
- **Owner: GameLogic.**
  - The body sits at the head of DisconnectManager's code. Before it is the equally uncalled
    out-of-line copy of GameSlot::markAsDisconnected at 0x0066AF30 (`mov byte [ecx+0x40],1; ret`,
    referenced only by its ILT 0x00019D4E). After it comes the DisconnectManager constructor at
    0x0066AF50.
  - In that code, the only stores to +0x290 go to TheGameLogic (0x012F0898).
    DisconnectManager::processDisconnectPlayer (0x0066C760) writes 1 there.
    DisconnectManager::updateDisconnectStatus (0x0066C3B0) writes 0 and 2. Both are inline, in
    DisconnectManager.cpp at lines 343-345 and 447-454.
  - So the body is a GameLogic setter that the unit inlines, like markAsDisconnected, with its
    out-of-line copy kept.
- **The method name stays address-derived.** tools/name_oracle.py finds no GameLogic+0x290 witness,
  Zero Hour's GameLogic has no member there, and no caller or string names the method.
