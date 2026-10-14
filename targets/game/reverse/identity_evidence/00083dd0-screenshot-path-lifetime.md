# Screenshot path getter at 00083DD0

The matched `W3DDisplay::saveScreenShot` in W3DDisplay.cpp calls
`ScreenshotGlobalData::getPath_UserData` through ILT00036D9A. Its return
is a single-pointer ScreenshotAsciiString with string-buffer release.
Retail uses ECX for the receiver, the hidden return pointer on the stack,
and RET4 at +18E followed by INT3 at +191: the complete extent is401 bytes.

The member header is read from receiver+1284. GlobalDataParseDefinition.cpp
places m_userDataDirLegacy at that offset. The fetched label is
APPDATA:PictureFolder. SHELL32 SHGetSpecialFolderPathA uses0x27 and create1.

Retail constructs the AsciiString leaf at +65, fetches and translates the
UnicodeString at +69..93, and releases the temporary at +A3. Only then does
it inspect the trailing separator with strlen at +A8. The prior bank had
those operations reversed. Restoring their order and returning the member
directly, without the synthetic volatile pointer, emits all401 bytes with
17 relocation slots masked. Baseline423B308diff; order-only417B313diff;
order plus direct member return401B masked exact. No names or pins changed.

Scratch measurements: build/worker4-round20/{baseline,lifetime,natural}.log.
Strict verification is required separately for promotion.

Strict add_match passed1/1 with2 literal references and6 DIR32 references verified;
body guard has0 baselined findings. See build/worker4-round20/strict.log.

Name: landed as the address-derived ScreenshotGlobalData::getPath00083DD0.
`tools/ilt_oracle.py check` puts getPath_UserData (any GlobalData or
ScreenshotGlobalData decoration) outside every window of this body's slots
44113:26458-26468, and the real GlobalData::getPath_UserData is the separate
matched 35-byte body at 0x00083D70. The PictureFolder behaviour suggests a
screenshot-path getter, but no evidence fixes its spelling.
