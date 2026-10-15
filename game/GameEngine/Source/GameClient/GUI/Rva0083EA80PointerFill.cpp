// cl: /DNDEBUG /MD /EHsc
// stlport
#include <algorithm>

// STLport fill<T**, T*> over a pointer range, retail 0x0083EA80 (30 bytes).
//
// Not fill<void**, void*>: that is 0x00066530, the copy vector<void*>::_M_fill_insert
// 0x00067740 calls twice through ILT 0x00018412 (identity_evidence/
// 00067740-vector-voidptr-fill-insert.md). Retail has no identical-COMDAT folding,
// and nothing in retail reaches this copy by rel32 (no ILT, no direct call), so its
// element type is unproven: an address-named opaque pointer.

struct Rva0083EA80Elem;

template void _STL::fill<Rva0083EA80Elem **, Rva0083EA80Elem *>(
	Rva0083EA80Elem **, Rva0083EA80Elem **, Rva0083EA80Elem *const &);
