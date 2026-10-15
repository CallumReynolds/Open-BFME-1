# 0x00387A50: GameLogic Game Over Details formatter, not EstablishConnectionsMenu::endMenu

The 657-byte body at `0x00387A50` (SEH prologue, `ret` at +0x290) was lifted
under `?endMenu@EstablishConnectionsMenu@@`. Zero Hour's
`EstablishConnectionsMenu::endMenu` is a one-call window teardown
(`HideEstablishConnectionsWindow()`); this body is not.

Callers (raw retail bytes):

    0x0038B597  e8 6f eb cb ff   call 0x0004A10B
    0x00397789  e8 7d 29 cb ff   call 0x0004A10B
    0x0004A10B  e9 40 d9 33 00   jmp  0x00387A50

`0x0038B597` lies inside the matched `GameLogic::bfme_processLogicCRC`
(`0x0038B430`, `game/GameEngine/Source/GameLogic/System/GameLogicPeerCRC.cpp`),
whose source calls `bfme_appendGameOverDetails()` on `this` (a GameLogic) at
that site; the dispatcher site `0x00397789` passes `ecx = TheGameLogic`.

The body itself formats the retail literals `"    Game Over Details:\n"`,
`"      Slot %d: Victory frame: %d, Quit frame: %d(%s)\n"`,
`"      Slot %d: Defeat frame: %d, Quit frame: %d(%s)\n"`,
`"      Slot %d: n/a\n"`, `"      Slot %d: Present at final frame\n"`,
`"      Slot %d: PlayerLeaveStatus does not exist.\n"` and the reasons
`n/a`/`graceful`/`voted out`/`unknown` over the eight PlayerLeaveStatus records
at GameLogic+0x1B0, guarded by the once-only flag at GameLogic+0x68.

The original method name is not in the image. The row takes the ledger's
existing descriptive pin `?bfme_appendGameOverDetails@GameLogic@@QAEXXZ`
(symbols.csv, same address), which the matched caller already spells.
