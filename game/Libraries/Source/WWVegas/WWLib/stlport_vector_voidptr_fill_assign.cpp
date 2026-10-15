// cl: /Od /EHsc /Ob2
// stlport
#include <vector>

// ?_M_fill_assign@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXIABQAX@Z, retail 0x0082EF90.
// It builds its temporary with vector<void*>(n, v, a) 0x00066EB0 (the hashtable bucket ctor)
// and calls the void* get_allocator 0x000665A0, erase 0x000CF750, swap 0x00066F00 and
// ~_Vector_base 0x00066C30; see identity_evidence/0082ef90-vector-voidptr-fill-assign.md.
template class _STL::vector<void *>;
