# Wave-20 B: 0x00165D50 call-context variant sweep - fold not reachable from source

Bank unchanged: `targets/game/reverse/attempts/0x00165d50.cpp` (md5
e29c8434fe7a84c6fae5a629fdef64d4), 2333 B / 63 relocs, the same 10 masked
bytes at +0x376..+0x38A (4-instruction cash fold). Verdict: partial.

## New evidence this wave (30+ genuinely new variants, each one probe)

All variants were built from an exact copy of the bank in `build/w20/` and, in
the bank TU, emitted **byte-identical** output to the bank (2333 B, 63 relocs,
10 diffs, same fold shape). Categories:

1. Scheduling / temporaries: boxes local; base local; both locals both orders;
   temp-swap with final copy; compound `*=` on the base temp, on the boxes
   temp, and on a result temp; `boxes` loaded from a second getBoxesStored()
   call; `+0` on either side; `*1`; redundant var copy; long/unsigned temp.
2. Call-result consumption: module copy temp; source alias local; key local;
   key cast; direct `findModule` on the Rva001BEE60Object path (same call).
3. Control flow / TU context: goto-form null skip; `if/else` empty; `!= NULL`;
   do/while(0) (frame grows to 2317 B, rejected); a tiny and a ~50-op dummy
   function placed BEFORE the target in the TU (no effect).
4. Hoists/sinks around the call: base value hoisted before the call
   (2349 B/1487 diffs, spill); base after call before null check (identical);
   boxes before null check (spill / rejected); `GlobalData *` pointer local
   before the check (2349 B, spill; fold moves to `imul ecx,[edi]` shape);
   address-of base pointer before the check (2349 B, spill).
5. Helper functions: `__forceinline int mul(a,b)` both operand orders;
   `__forceinline getBase(const GlobalData*)`.
6. TU flags (via `// cl:`): `/Oa` (2352 B) and `/Ob1` (2438 B) break the
   body; `/GR-` and `/Ox` are byte-identical - flags are not the lever.

## Micro evidence (build/w20/micro1.cpp, same toolchain flags -O2 -GR- -EHsc-)

- `m0_no_call`: no call before the fold -> RETAIL shape
  `mov ecx,[G] / mov edx,[ecx+0xb24] / imul edx,[eax+0x88]`.
- `m1_call` (and 2-step, compound, boxes-local, both orders): call ->
  bank-like shape `mov eax,[eax+0x88] / mov ecx,[G] / imul eax,[ecx+0xb24]`.
- `m3_call_loop`, `m4_call_nested`: call inside a loop with `continue` ->
  THIRD shape `mov ecx,[G] / mov ecx,[ecx+0xb24] / imul ecx,[eax+0x88]`
  (boxes folded, but global pointer+value merged into one register).

No call-context construct tested produces retail's exact
ECX(ptr)+EDX(value)+folded-boxes split; only the no-call context does. This
extends wave 19: the residue is a compiler-internal allocation tie-break that
source scheduling, temporaries, control form, TU context and TU flags do not
move in this TU. Reopening would need an external lever (different allocator
phase state), not another source shape.

Raw logs: `build/w20/logs/*.log`; generators `build/w20/gen*.py`, `micro.py`.
