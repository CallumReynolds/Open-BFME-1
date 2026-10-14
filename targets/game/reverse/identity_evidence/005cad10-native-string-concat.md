# 005CAD10 native string concatenation

The 223-byte body ends in plain RET at +DE, before alignment padding.
The caller ParticleSystemTemplate::writeINI reaches it through ILT3F41D.
The explicit actual-RVA oracle confirms the exact native STLport overload
(string reference, character) with tier=real, CONFIRMED, p=0.00026091948.
The native pointer overload is already landed at005CAE30 in
STLportStringConcatPointer.cpp. Vendored _string.h operator+(string,char)
uses the same reserve/append/push_back/return-copy lifetime seen here.

The old bank hand-redeclares allocator and basic_string and reports compiler
C1001. This experiment uses only <string> and explicit instantiation of the
existing native operator, correcting home-header context rather than trying
another expression spelling. Probe223/223B EXACT modulo12relocations.

Independent direct-reference audit:
- ILTFD17->4F9C60 returns its hidden allocator output pointer, RET4,7bytes.
  Existing get_allocator binding is the same as the landed pointer sibling.
- ILT16527->5C46C0 initializes the three-pointer base and allocates the
  requested reserve count, RET8. Existing native constructor binding.
- ILT11522->A4030 takes mutable pointer range and forward-iterator tag;
  existing exact append specialization.
- ILT3BC23->53AE60 pushes one character; existing native push_back binding.
- ILT1CB11->4FB1B0 is the existing native copy constructor.
- Node deallocation82E5F0 and operator delete881EB0 use existing bindings.

No user global or floating constant is referenced by the body: the absolute
reference in its prefix is compiler EH metadata, not a bank-local datum.
The only other accesses are object fields, stack locals and call operands.
Native headers supply the EH metadata and cleanup funclet. No new pin,
shared header edit, guessed name or generated-file edit is needed.

Strict add_match scoped gate passed1/1 with zero skipped constants/literals
and zero data references. t=1.79min model=gpt-6-astra lane=R budget=30m.
