# GameState::saveGame catch blocks and continuation (0x001103D2 to 0x00110510)

`?saveGame@GameState@@QAE?AW4SaveCode@@VAsciiString@@VUnicodeString@@W4SaveFileType@@W4SnapshotType@@_N@Z`
starts at 0x00110170. Its source, `game/GameEngine/Source/Common/System/SaveGame/GameStateSaveGame.cpp`,
compiles to a 928-byte `.text` section that `tools/probe.py ... --size 928` reports EXACT
modulo relocations against retail 0x00110170..0x00110510.

## Retail EH data

The prologue pushes handler stub 0x00BFDBA8 (`mov eax, 0x011EB308`). FuncInfo VA 0x011EB308
(magic 0x19930520, 13 states) has two try entries, each with one `catch(...)`:

| try states | catch state | handler |
|---|---|---|
| 5..5 | 6 | 0x001104E4 |
| 7..7 | 11 | 0x001103D2 |

Both handlers end `mov eax, 0x00510499; ret`, so the parent resumes at RVA 0x00110499.

## Object labels

| offset | label | retail RVA | bytes | role |
|---|---|---|---|---|
| +0x262 | `$L899` | 0x001103D2 | 199 | catch(...) of the xferSaveData try (row `?dup_001103d2`) |
| +0x329 | `$L917` (also `$L919`) | 0x00110499 | 75 | continuation both catches return to |
| +0x374 | `$L897` | 0x001104E4 | 44 | catch(...) of the earlier try |

The old gen-dump row `?d_001104a5` started 12 bytes into the continuation (at 0x001104A5);
the catches return to 0x00110499, which is its real start.
