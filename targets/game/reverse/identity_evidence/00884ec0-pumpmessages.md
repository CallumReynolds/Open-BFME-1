# CDownload::PumpMessages at RVA 0x00884EC0

The complete target is recovered as `?PumpMessages@CDownload@@UAEJXZ` in `game/Libraries/Source/WWVegas/WWDownload/CDownloadDownloadFile.cpp`. Verification used base revision `95eeb3bef370a7cd730b0ad5f228c317c8756e72` and the current retail baseline. No shared header, pin, baseline or tooling change is required.

## New evidence and compiler experiments

Open BFME 2 donor `Code/Libraries/Source/WWVegas/WWDownload/CDownloadDownloadFile.cpp` at game.dat `0x006C99D0` supplies a complete typed reconstruction. The retry hypothesis was that its member declarations, virtual interface, import declarations and inline visibility reproduce the callback receiver allocations that earlier attempts called compiler residue. An unchanged first divergent callback after porting these declarations would refute that hypothesis. The individual contributions of these changes were not isolated.

The original bank was read in full, together with its five attempt records and the landed neighbouring sources. The bank's unsigned clock arithmetic and explicit `_strnicmp` import were retained in meaning. The donor declares the actual unsigned `timeGetTime` import, so its signed `timetaken` local receives an unsigned quotient. The port keeps the bank's `Listener`, `Rva00884DownloadListener`, `Rva00884Ftp`, `FileRecoveryPosition`, `RestartFrom` and `Get_Command_Socket` names. The source uses the donor's `/Ob2` flag. Original Zero Hour comments, including commented code and the resume-check closer, are retained in the recovered body.

| Trial | Measurement | Raw output |
|---|---|---|
| Original saved bank | 1047 bytes against 1065; 789 positional non-relocation byte differences and 18 bytes missing. The first positional difference is the branch displacement at +0x52; the first divergent operation is the callback receiver load at +0x85. | build/pumpmessages-00884ec0/original-bank-raw.log |
| Typed donor port | 1065 bytes, exact outside relocation operands. | build/pumpmessages-00884ec0/01-donor-typed.log |
| Port merged into the existing owning source | 1065 bytes, exact outside relocation operands. | build/pumpmessages-00884ec0/03-merged-fixed.log |
| Original EA body comments and visible RestartFrom setter | 1065 bytes, exact outside relocation operands. | build/pumpmessages-00884ec0/04-original-comments.log |

Each trial source and unedited probe output remains under `build/pumpmessages-00884ec0/`. `00-bank-original.cpp` preserves the deleted bank verbatim. The first merge had duplicate enum declarations and produced no object; its source is `02-merged-redefined-enums.cpp` and its compiler output is `02-merged.log`.

## Boundary and identity

The retail extent is RVA `0x00884EC0` through `0x008852E8`, inclusive. It decodes completely into 313 instructions, with ten return paths. Every direct branch targets a decoded instruction inside the extent. There is no outgoing tail jump, EH registration or hidden result pointer. The final return is followed by seven `INT3` padding bytes before the next function. Raw evidence is `build/pumpmessages-00884ec0/retail-target.log`, `checked-target.log` and `structure.log` in the same directory.

The independently named CDownload constructor at RVA `0x006267A0` installs vtable VA `0x01117B30`. That table has this target at slot 0, the abort body at slot 1, the landed DownloadFile body at slot 2 and the last-local-file body at slot 3. `DownloadManager::update` at RVA `0x00626950` loads its CDownload pointer, loads that pointer's vtable and tail-jumps through slot 0. The official Zero Hour `Download.h` declares PumpMessages in precisely this slot. The constructor stores its IDownload argument at offset `0x5C4` and its constructed Cftp pointer at `0x5C0`. This establishes owner and method independently of the donor's spelling.

The Python API `ilt_oracle.check('?PumpMessages@CDownload@@UAEJXZ', 0x00884EC0)` returns `UNTESTABLE`, with no contradiction. The name is supported by the constructor, vtable slot, matched caller and reference interface. The existing source's nonvirtual DownloadFile declaration and ledger spelling are preserved; this translation unit emits no CDownload vtable or constructor. No registered canonical header exists for these local classes. The target uses a virtual declaration and the implicit vptr in place of the former four-byte padding array.

Only the target's own generated assembly definition names the retired dump symbol. No other game source or assembly caller references it, so no compatibility pin is added.

## Fields, direct callees and imports

The constructor, landed DownloadFile sibling and complete target agree on the seven character buffers at offsets `0x004`, `0x104`, `0x144`, `0x184`, `0x284`, `0x384` and `0x484`; the five dword state values at `0x584` through `0x594`; the byte resume flag at `0x598`; the prediction count at `0x59C`; and all eight dword prediction values at `0x5A0` through `0x5BC`. There is no STL container, value-copy helper or element cleanup in this target.

| Direct callee RVA | Call contract verified from caller and complete callee |
|---|---|
| 0x00885B50 | ECX is the Cftp receiver; one server-string pointer; EAX status; every return cleans four bytes. |
| 0x00885D90 | ECX receiver; username then password pointer; EAX status; every return cleans eight bytes. |
| 0x00886020 | ECX receiver; remote filename then writable int pointer; the successful paths write one dword through that pointer; every return cleans eight bytes. |
| 0x00886A20 | ECX receiver; local filename then registry-root pointer bits; the second word is unused; both returns clean eight bytes and return EAX. |
| 0x00886520 | ECX receiver; local filename then writable byte-count pointer; the update writes one dword through that pointer; every return cleans eight bytes. |

All five are real bodies, not jump thunks. Complete decoded listings and checked inventories are retained as `retail-connect.log`, `retail-login.log`, `retail-find.log`, `retail-recovery.log`, `retail-next-block.log` and their `checked-` counterparts under `build/pumpmessages-00884ec0/`. `structure.log` enumerates every return and confirms that all direct branch destinations are internal instruction starts.

The complete recovery helper reads its first filename argument, constructs the temporary filename, opens it, writes zero or the `ftell` result to Cftp offset `0x2C`, and returns that stored value. Its second stack word is not read on either path. The retained descriptive FileRecoveryPosition alias is an existing pin; this port introduces no new identity for that body. The existing RestartFrom body and the inline socket getter respectively write offset `0x2C` and read offset `0x04`, as the target's expanded instructions require.

The PE import directory identifies the four import slots as WINMM `timeGetTime`, KERNEL32 `MulDiv`, MSVCR71 `_stat` and MSVCR71 `_strnicmp`. Their source declarations preserve unsigned 32-bit ticks, three signed 32-bit MulDiv arguments, the MSVC 7.1 `_stat` structure and a 32-bit string-comparison count. The generated import names agree with the existing DIR32 records. The clock pointer is loaded once and reused, as in retail. Raw import evidence is in `structure.log`.

## Indirect callback contracts

DownloadManager's vtable at VA `0x01117D04` independently confirms all five listener slots. Its ILT entries resolve to bodies at RVAs `0x00626DA0`, `0x00626960`, `0x00626970`, `0x00626980` and `0x00626EE0`. These respectively consume one error dword, no arguments, no arguments, four progress dwords and one status dword. Their return cleanup is `RET 4`, `RET`, `RET`, `RET 16` and `RET 4`; each returns a 32-bit EAX value. No receiver adjustment is present. PumpMessages pushes progress arguments in reverse order as time-left, elapsed seconds, total size and bytes read. It compares the resume callback's full EAX value with `0x80040006`.

The error callback's 252-byte ledger extent includes a 28-byte switch table. Its complete instruction region is 224 bytes. The status callback's 264-byte extent includes alignment and a 36-byte switch table; its complete instruction region is 226 bytes. Checked inventories use the instruction regions. Every switch-table destination was separately decoded and validated inside those regions. The first failed linear decode of the error callback's code-plus-table extent is preserved as `checked-callback-error-ledger-extent.log`. This does not truncate either callback's control flow. Complete callback code, inventory and table evidence are retained in the `retail-callback-*.log`, `checked-callback-*.log` and `structure.log` files.

## Verification and collection

`add_match.py` verified all three rows in the owning source, including the existing DownloadFile and RestartFrom bodies. String references, constants, DIR32 addresses and body guard passed. Raw output is `build/pumpmessages-00884ec0/add-match.log`; the separate scoped gate is `build/pumpmessages-00884ec0/scoped-gate.log`. The independent DownloadFile probe is `merged-downloadfile-probe.log`. Declaration, class and pin checks are retained in `declared-unmatched-final.log`, `class-gate-final.log` and `pin-consistency.log`. `name-regression-final.log` reports no descriptive-to-placeholder regression against the preserved original bank. The name-oracle check and EA name check also report no conflict, with their coverage limits retained in `name-oracle-check.log` and `ea-name-check.log`.

The working-tree `check_csv.py` invocation stops while reading the bank that add_match removed. The deletion is unstaged because this sandbox forbids Git writes. Its raw traceback is `build/pumpmessages-00884ec0/check-csv-final.log`. Stage the source, ledger replacement, tombstone, bank deletion, evidence and verdict together, then run the staged ledger check with the normal hooks. The bank has not been restored. No full gate is required by a source-only change; no shared header or shim was edited.
