// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

// STLport vector<T*>::swap, retail 0x00069C80 (45 bytes).
//
// Not vector<void*>::swap: that is 0x00066F00, the swap vector<void*>::_M_fill_assign
// 0x0082EF90 calls through ILT 0x000063E3 (identity_evidence/
// 0082ef90-vector-voidptr-fill-assign.md). Retail has no identical-COMDAT folding.
// No rel32 site reaches this copy (its only reference is its ILT jmp 0x00042997), so
// the element type is unproven: an address-named opaque pointer.

struct Rva00069C80Elem;

template void _STL::vector<Rva00069C80Elem *, _STL::allocator<Rva00069C80Elem *> >::swap(
	_STL::vector<Rva00069C80Elem *, _STL::allocator<Rva00069C80Elem *> > &);

