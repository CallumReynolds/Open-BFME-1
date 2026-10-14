# 0x0073AD70 drawTerrainNormal

- Boundary: retail [0x0073AD70, 0x0073AE85), 277 bytes, `ret` at +0x114 then INT3.
- Caller: the matched `drawablePostDraw` (0x0073AED0) calls it directly, not
  through the ILT, only when `TheWritableGlobalData` byte +0xA81
  (`m_showTerrainNormals`) is set, with the drawable left in ECX. That is the
  Zero Hour `W3DView.cpp` call site `if (TheGlobalData->m_showTerrainNormals)
  drawTerrainNormal(draw, userData);`, and the direct call is the file-static
  private ABI.
- Body: the same sequence as Zero Hour's `static void drawTerrainNormal`.
  It checks `TheTerrainLogic`, copies `draw->getPosition()`, then
  `getGroundHeight(x, y, &normal)` (vslot +0x18). It extends the normal by
  `NORMLEN` (the 20.0f constant at 0x010977E0) and makes two
  `TheTacticalView->worldToScreen` calls (vslot +0x15C). It ends with
  `TheDisplay` line drawing in the yellow 0xFFFFFF00 =
  `GameMakeColor(255, 255, 0, 255)`.
- BFME differences: the line goes through float coordinates, wrapped in
  Display slots +0xB0 and +0xDC around `drawLine` (+0xB8). The source keeps
  those slots opaque.
- Probe: exact, 277/277 with 9 relocations, compiled beside the caller.
