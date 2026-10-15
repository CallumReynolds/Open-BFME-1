// cl: /DNDEBUG /MD /EHsc
// stlport

#include <algorithm>
#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

// The retail comparator has no additional EH cleanup state for the no-case comparison.
template <>
__declspec(nothrow) int StringBase<unsigned short>::compareNoCase(
	const StringBase<unsigned short> &other) const;

inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

class MapMetaData
{
public:
	UnicodeString getFileName() const;
};


// The operator is defined in the class, as the sort's own TU had it: the
// optimiser declines to expand it (UnicodeString temporaries under EH), and
// __partial_sort<int *, int, Q4Sort004566F0> (retail 0x00455E20, 121 bytes)
// then keeps the comparator value cached in EBP and reloads `last` from its
// argument slot, as retail does.  An out-of-line declaration swaps the two.
struct Q4Sort004566F0
{
	bool operator()(int a, int b) const
	{
		return ((const StringBase<unsigned short> &)((const MapMetaData *)a)->getFileName()).compareNoCase(
			(const StringBase<unsigned short> &)((const MapMetaData *)b)->getFileName()) < 0;
	}
};

// Retail 0x00455E20: the heap-select fallback of the Q4Sort004566F0 sort;
// its __make_heap, __adjust_heap and sort_heap calls go through ILTs
// 0x0002AC5C, 0x0002B6D4 and 0x0003AF62, whose bodies reach this comparator.
template void _STL::__partial_sort<int *, int, Q4Sort004566F0>(
	int *, int *, int *, int *, Q4Sort004566F0);
