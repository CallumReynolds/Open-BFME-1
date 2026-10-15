// cl: /Od /Ob2 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// RVA 0x0082EA80: STLport vector<void*>::vector(size_type n).
// Retail calls _Vector_base<void*>(n, a) through ILT 0x00026085 -> 0x00066A90
// (identity_evidence/00066eb0-vector-voidptr-fill-ctor.md: the base the
// hashtable bucket ctor 0x00066EB0 and the vector<void*> copy ctor 0x0082EB30
// call). Retail has no identical-COMDAT folding, so a member that calls the
// void* base is a vector<void*> member. No rel32 caller reaches this body.
// The native header supplies the allocator temporary, POD fill loop and
// exception cleanup.
#include <vector>

template _STL::vector<void *, _STL::allocator<void *> >::vector(unsigned int);
