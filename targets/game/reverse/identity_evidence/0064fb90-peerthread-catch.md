# PeerThreadClass::Thread_Function catch block at 0x00651054

`?Thread_Function@PeerThreadClass@@UAEXXZ` starts at 0x0064FB90 (`push ebp; mov ebp, esp;
push -1; push 0x01042BFE`). Its source, `game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread_ThreadFunction.cpp`,
compiles to a 5508-byte `.text` section equal to retail outside relocations.

Handler stub 0x01042BFE loads FuncInfo VA 0x0123267C (magic 0x19930520, 21 states), whose
try map at VA 0x01232654 holds:

| try states | catch state | handler |
|---|---|---|
| 0..16 | 20 | 0x00651054 `catch(...)` |
| 18..19 | 20 | 0x006510A5 `catch(...)` (nested inside the first handler) |

The first handler runs 0x00651054..0x006510A5 (81 bytes): it opens the nested try, and ends
`mov eax, 0x00A4FF00; ret` at 0x0065109F, which is also where the nested handler returns.
In the compiled object it starts at label `$L45122` (+0x14C4); the nested handler is
`$L45124` (+0x1515) and the shared return point `$L38012` (+0x150F).
