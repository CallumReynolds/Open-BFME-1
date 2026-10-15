// cl: /DNDEBUG /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep
// stlport

// Retail 0x0036E870 (52 bytes): STLport vector<T*>(size_type, T* const&,
// const allocator&). Its _Vector_base<T*>(n, a) call goes through ILT
// 0x000212D3 -> 0x001F9330, which is also the base of the vector copy at
// 0x001F9520 and of the 0x0035E030 / 0x0035E1F0 / 0x009002C0 constructors,
// all spelled with the stand-in element Gen_ve_001f9520 (pinned there).
// Retail has no identical-COMDAT folding, so this ctor belongs to that same
// element type. It is NOT vector<void*>: the hashtable bucket vector's ctor
// is 0x00066EB0 (identity_evidence/00066eb0-vector-voidptr-fill-ctor.md).

#include <vector>

class Gen_ve_001f9520;

template _STL::vector<Gen_ve_001f9520 *, _STL::allocator<Gen_ve_001f9520 *> >::vector(
	_STL::vector<Gen_ve_001f9520 *, _STL::allocator<Gen_ve_001f9520 *> >::size_type,
	Gen_ve_001f9520 *const &,
	const _STL::allocator<Gen_ve_001f9520 *> &);
