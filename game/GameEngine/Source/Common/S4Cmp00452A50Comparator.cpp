// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// stlport
//
// S4 sort compares the numbered BFME display name after it compares the
// entry count.  The count branch and the two UnicodeString temporaries match
// the comparator shared by the retail S4 insertion and heap callers.

#include <algorithm>
#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

// Retail does not establish an additional EH state for this comparison.
template <>
__declspec(nothrow) int StringBase<unsigned short>::compareNoCase(
    const StringBase<unsigned short> &other) const;

inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

// Keep the comparison on the canonical wide buffer, without emitting a second
// public UnicodeString comparison provider from this comparator TU.
static inline int compareDisplayNames(
    const UnicodeString &left, const UnicodeString &right)
{
    return ((const StringBase<unsigned short> *)&left)->compareNoCase(
        *(const StringBase<unsigned short> *)&right);
}

class MapMetaData
{
public:
	UnicodeString bfme_getDisplayName(void);

	char m_pad[0x20];
	int m_count;
};

// The operator is defined in the class, as the sort's own TU had it: the
// optimiser declines to expand it (UnicodeString temporaries under EH), and
// __partial_sort<int *, int, S4Cmp00452A50> (retail 0x00455EC0, 121 bytes)
// then keeps the comparator value cached in EBP and reloads `last` from its
// argument slot, as retail does.  An out-of-line declaration swaps the two.
struct S4Cmp00452A50
{
	void *m_state;
	bool operator()(int a, int b) const
	{
		if (((const MapMetaData *)a)->m_count == ((const MapMetaData *)b)->m_count)
			return compareDisplayNames(((MapMetaData *)a)->bfme_getDisplayName(),
				((MapMetaData *)b)->bfme_getDisplayName()) < 0;

		return ((const MapMetaData *)a)->m_count < ((const MapMetaData *)b)->m_count;
	}
};

// Retail 0x00455EC0: the heap-select fallback of this comparator's sort
// (Q4IntrosortLoop.cpp names the same instantiation Q4Sort004567A0); its
// __make_heap, __adjust_heap and sort_heap calls go through ILTs 0x000313EF,
// 0x000023C4 and 0x00046FB0, whose bodies reach comparator ILT 0x00039CB1.
template void _STL::__partial_sort<int *, int, S4Cmp00452A50>(
	int *, int *, int *, int *, S4Cmp00452A50);
