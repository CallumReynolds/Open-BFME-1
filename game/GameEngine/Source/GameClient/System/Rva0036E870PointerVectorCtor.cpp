// cl: /DNDEBUG /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep
// stlport

// Retail 0x0036E870 (52 bytes): an STLport vector<T*>(size_type, const T*&,
// const allocator&) whose _Vector_base<T*>(n, a) call goes through ILT
// 0x000212D3 -> 0x001F9330. Its only reference is the unreferenced ILT
// 0x0002C430. It is NOT vector<void*>: retail links without identical-COMDAT
// folding, and the hashtable bucket vector's own vector<void*>(n, v, a) is
// 0x00066EB0 (identity_evidence/00066eb0-vector-voidptr-fill-ctor.md).
// The pointee type is unknown, so it stays opaque and address-derived.

#include <vector>

struct Rva0036E870Elem;

template _STL::vector<Rva0036E870Elem *, _STL::allocator<Rva0036E870Elem *> >::vector(
	_STL::vector<Rva0036E870Elem *, _STL::allocator<Rva0036E870Elem *> >::size_type,
	Rva0036E870Elem *const &,
	const _STL::allocator<Rva0036E870Elem *> &);
