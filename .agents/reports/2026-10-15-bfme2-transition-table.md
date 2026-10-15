# BFME2 transition-table port: verified data, blocked DIR32 type correction

Date: 2026-10-15. Model: gpt-6.1-sol. BFME1 base: `0dbe7e53e56a3e319104c52f9d59c13668158374`.
Donor: Open-BFME-2 `d0dbde2408`,
`Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsParseWindow.cpp`.
Queue: link row 350, undefined `?Rva0048BD60FieldTable@@3QBEB`.

The donor supplies a typed FieldParse table for WinName, Transition and
FrameDelay. BFME1 independently has those three entries and a zero terminator
at VA 0x010F97D0. Its existing parseWindow function remains byte-exact for all
104 bytes. The three token providers and the full table passed add_data_match:

| Provider VA | Size | Verified contents |
|---|---:|---|
| 0x010F97C4 | 8 | WinName including NUL |
| 0x010F97B4 | 11 | Transition including NUL |
| 0x010F97A4 | 11 | FrameDelay including NUL |
| 0x010F97D0 | 64 | Four FieldParse entries; all six relocations correct |

The callback targets are INI::parseAsciiString at RVA 0x00851EE0,
ILT 0x0001A8FC to the existing opaque four-slot cdecl bfmeGo1060D at
0x0048BD00, and INI::parseInt at 0x00852A60. Offsets are 0, 0, 4.
Names and layout claims are carried only as far as that target evidence.

The scoped build passed the function, four data rows and body guard, then
refused the typed table's DIR32 name because the same VA is recorded as the
old unsigned-char array. The new verified symbol is
`?Rva0048BD60FieldTable@@3QBUFieldParse@@B`; the old symbol is
`?Rva0048BD60FieldTable@@3QBEB`.

With source and all four verified rows staged, the sanctioned command

```sh
python3 tools/dir32_record.py retire '?Rva0048BD60FieldTable@@3QBEB' --for '?Rva0048BD60FieldTable@@3QBUFieldParse@@B'
```

refused:

```text
dir32_record: refused: ?Rva0048BD60FieldTable@@3QBEB (or Rva0048BD60FieldTable) still appears in game/GameEngine/Source/GameClient/GUI/GameWindowTransitions_parseWindow.cpp
```

This is the bare-identifier heuristic rejecting a type correction: the new
staged declaration retains the identifier but emits the new, data-owned COFF
symbol. The old raw-array declaration is gone. The first call before staging
correctly reported that the proposed data ownership was not in the index;
the result above is the subsequent call with ownership staged.

No verifier, record, baseline or alias was changed. The source and all four
unpublished data rows were reverted and the queue claim released. LINKED gain
is zero; this report is evidence, not an implementation landing. Reopen after
a separate verifier fix admits this proven type correction. The patch below
recreates the verified prototype; admit its four data rows through
add_data_match before reproducing the DIR32 check.

```diff
diff --git a/game/GameEngine/Source/GameClient/GUI/GameWindowTransitions_parseWindow.cpp b/game/GameEngine/Source/GameClient/GUI/GameWindowTransitions_parseWindow.cpp
index 9f5caacd12..15dcde138c 100644
--- a/game/GameEngine/Source/GameClient/GUI/GameWindowTransitions_parseWindow.cpp
+++ b/game/GameEngine/Source/GameClient/GUI/GameWindowTransitions_parseWindow.cpp
@@ -54,7 +54,25 @@ private:
 	_STL::list<TransitionWindow *> m_transitionWindowList;
 };
 
-extern const unsigned char Rva0048BD60FieldTable[];
+// BFME2 GameWindowTransitionsParseWindow.cpp supplies the typed table lead.
+// Use the existing INI declaration; parseInt's verified COFF signature is
+// exposed directly, as in S5Parse0059D600.cpp, because this thin header omits it.
+extern "C" void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")(
+ INI *, void *, void *, const void *);
+class BfmeO1060;
+void bfmeGo1060D(BfmeO1060 *, int, int, int);
+
+// The data verifier requires each pointed-to token to have its own provider.
+extern const char g_rva010F97C4[8] = "WinName";
+extern const char g_rva010F97B4[11] = "Transition";
+extern const char g_rva010F97A4[11] = "FrameDelay";
+
+extern const FieldParse Rva0048BD60FieldTable[4] = {
+ { g_rva010F97C4, &INI::parseAsciiString, 0, 0 },
+ { g_rva010F97B4, reinterpret_cast<INIFieldParseProc>(&bfmeGo1060D), 0, 0 },
+ { g_rva010F97A4, __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 4 },
+ { 0, 0, 0, 0 }
+};
 
 class GameWindowTransitionsHandler
 {
@@ -68,6 +86,6 @@ void GameWindowTransitionsHandler::parseWindow( INI *ini, void *instance,
 	void *store, const void *userData )
 {
 	TransitionWindow *transWin = new TransitionWindow;
-	ini->initFromINI( transWin, (const FieldParse *)Rva0048BD60FieldTable );
+	ini->initFromINI( transWin, Rva0048BD60FieldTable );
 	((TransitionGroup *)instance)->addWindow( transWin );
 }
```
