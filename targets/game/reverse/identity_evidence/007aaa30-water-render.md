# 0x007AAA30 WaterRenderObjClass::Render (244 B)

- Extent: int3-aligned start, `pop edi; pop esi; ret 4` at +0xDD..+0xE1, two
  `mov edi,edi` pad bytes, then the four-entry switch table at +0xE4..+0xF3.
- Identity: the matched constructor 0x007A46E0 stores vtable 0x01128148 at
  `this` and vtable 0x01127ED8 at the RenderObjClass subobject (`this+4`).
  Slot 12 (+0x30) of 0x01127ED8 is ILT 0x00040E0D -> 0x007AAA30, the
  RenderObjClass `Render(RenderInfoClass&)` slot; the body itself renders the
  sky box through the same +0x30 slot.
- The body receives the subobject pointer and calls the matched
  `WaterRenderObjClass::drawSea` (0x007A37B0, ILT 0x000364BC) through
  `lea ecx,[esi-4]` for water type 2, as the ZH twin's Render does.
- Types 0/3 and type 1 call the matched bodies 0x007AA820 and 0x007A2330
  with the same `this-4` receiver and `rinfo`. Those bodies are matched under
  the opaque owner `Rva007A2330`; Render calls them through that existing
  route. The removed ZH reflection block (its `Vector3` locals) is not in BFME's
  Render: BFME outlined that path into 0x007A2330. `Rva007A2330` does not
  replace `Vector3`; the name-regression pairing is a false match.
