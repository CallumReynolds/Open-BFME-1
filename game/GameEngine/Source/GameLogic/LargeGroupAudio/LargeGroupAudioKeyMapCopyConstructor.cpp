// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: LargeGroupAudioKeyMap copy constructor, retail 0x003D3BB0,
// 133 bytes. The word vector is vector<unsigned int>: retail calls its
// _Vector_base(n, a) 0x003D3540 (ILT 0x0000799B) and get_allocator 0x003D32D0
// (ILT 0x0002CE4E), both pinned under the unsigned int names; see
// Rva003D3D50VectorFillInsert.cpp.

#include <vector>

class LargeGroupAudioKeyMap :
	public _STL::vector<unsigned int, _STL::allocator<unsigned int> >
{
public:
	LargeGroupAudioKeyMap(const LargeGroupAudioKeyMap &other);
};

void bfmeRetainMembers(LargeGroupAudioKeyMap *map);

// ??0LargeGroupAudioKeyMap@@QAE@ABV0@@Z
LargeGroupAudioKeyMap::LargeGroupAudioKeyMap(
	const LargeGroupAudioKeyMap &other) :
	_STL::vector<unsigned int, _STL::allocator<unsigned int> >(other)
{
	bfmeRetainMembers(this);
}
