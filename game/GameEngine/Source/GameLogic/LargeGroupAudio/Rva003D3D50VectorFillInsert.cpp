// cl: /DNDEBUG /MD /EHsc
// stlport
#include <vector>

// STLport vector<T>::_M_fill_insert for the four-byte, trivially assignable
// element of the LargeGroupAudioKeyMap word vector, retail 0x003D3D50.
//
// Not vector<void*>: retail was linked without identical-COMDAT folding, and
// vector<void*>::_M_fill_insert is 0x00067740, the body every hashtable
// _M_initialize_buckets/_M_copy_from calls (STLport _hashtable.h: the bucket
// vector is vector<void*>).  This copy is reached only from the resize at
// 0x003D4210 (ILT 0x0002570C), whose callers are LargeGroupAudioKeyMap
// bfmeMerge 0x003D4580 and bfmeAddKey 0x003D46A0.  The real element type is
// unproven; it is spelled as a pointer to an address-named opaque struct so
// STLport's __type_traits pick the trivial (memmove/__true_type) path retail
// takes.  Callees: fill ILT 0x0000A060 -> 0x003D31A0, _M_insert_overflow ILT
// 0x0001CBFC -> 0x000BBC80.

struct Rva003D3D50Elem;

template void _STL::vector<Rva003D3D50Elem *, _STL::allocator<Rva003D3D50Elem *> >::_M_fill_insert(
	Rva003D3D50Elem **, unsigned int, Rva003D3D50Elem *const &);
