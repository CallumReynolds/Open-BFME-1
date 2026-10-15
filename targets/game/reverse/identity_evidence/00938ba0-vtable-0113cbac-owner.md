# 0x00938BA0 constructor of the class whose vftable is 0x0113CBAC (17 B)

- Extent unchanged: `mov eax,ecx; xor ecx,ecx; mov [eax],0x0113CBAC;
  mov [eax+4],ecx; mov [eax+8],ecx; ret` (17 B).
- The ledger named this ctor's class `Rva00938BA0Triple` and gave it its own
  `??_7Rva00938BA0Triple@@6B@`, while `dir32_addresses.csv` already records
  retail 0x0113CBAC as `??_7Rva00938BF0Deleting@@6B@`: the scalar deleting
  destructor at 0x00938BF0 (matched, ScalarDeletingDestructors.cpp) seats the
  same table (`mov [esi],0x0113CBAC` at +0x08). Retail had no ICF, so one
  vftable has one class: two placeholder classes for it were one class split
  in two (body_guard_baseline dir32 line for 0x0113CBAC).
- The ctor is therefore `Rva00938BF0Deleting::Rva00938BF0Deleting()`, still an
  address-derived placeholder; no real class name is claimed.
