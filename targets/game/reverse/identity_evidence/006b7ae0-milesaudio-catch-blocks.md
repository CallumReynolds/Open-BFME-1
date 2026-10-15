# MilesAudioManager 0x006B7AE0 catch blocks and their continuations (0x006B7B9B to 0x006B7D6A)

`?rva006B7AE0@MilesAudioManager@@QAEXXZ` at 0x006B7AE0 is one 650-byte function
(`push ebp` at 0x006B7AE0, final `ret` at 0x006B7D69, INT3 from 0x006B7D6A). Its
source, `game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerRva006B7AE0.cpp`,
compiles to 650 bytes that `tools/probe.py ... --size 650` reports EXACT modulo
relocations. The ledger row claims only the first 187 bytes; the rest of the range
was carved into gen-dump rows.

## Retail EH data

The prologue pushes handler stub 0x00C491E8 (`mov eax, 0x01238C04`), so FuncInfo is
VA 0x01238C04 (magic 0x19930520, 7 states). Its try map at VA 0x01238BDC holds two
entries, each with one typed catch (type descriptor VA 0x012A704C, adjectives 9):

| try states | catch state | catch object | handler |
|---|---|---|---|
| 1..2 | 3 | ebp-0x20 | 0x006B7B9B |
| 4..5 | 6 | ebp-0x2C | 0x006B7CCF |

Each handler ends `mov eax, <continuation>; ret`: the first returns VA 0x00AB7BF0,
the second VA 0x00AB7D24, so the parent resumes at RVA 0x006B7BF0 and 0x006B7D24.

## Object labels

The compiled object's `.text` section for the parent is 650 bytes and carries:

| offset | label | retail RVA | bytes | role |
|---|---|---|---|---|
| +0x0BB | `$L7833` | 0x006B7B9B | 85 | catch handler 1 |
| +0x110 | `$L7861` | 0x006B7BF0 | 223 | continuation after catch 1 |
| +0x1EF | `$L7835` | 0x006B7CCF | 85 | catch handler 2 |
| +0x244 | `$L7862` | 0x006B7D24 | 70 | continuation after catch 2, to the final ret |

The old carves started the two continuations at 0x006B7BF3 (220 B) and 0x006B7D2D
(61 B), three and nine bytes late: the catch handlers return to 0x006B7BF0 and
0x006B7D24, so those are the real starts.
