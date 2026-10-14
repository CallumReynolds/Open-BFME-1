// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Exact STLport 4.5.3 list clear instantiations.  The synthetic payload names
// encode only the element width proven by the retail node deallocation size;
// their destructor pins preserve the concrete call targets without claiming
// an unproven game-class identity.

#include <list>

#define BFME_LIST_CLEAR(TAG, WIDTH)                                      \
    struct Z1Elem##TAG                                                   \
    {                                                                    \
        ~Z1Elem##TAG();                                                  \
        char m_pad[WIDTH];                                               \
    };                                                                   \
    template void _STL::_List_base<Z1Elem##TAG,                          \
        _STL::allocator<Z1Elem##TAG> >::clear();

BFME_LIST_CLEAR(00129220, 0x1C)
BFME_LIST_CLEAR(0013BF00, 0x24)

// The 0x0056D960 element is AvailableGameInfo: its 0x3C payload fills the
// 0x44 node, clear() destroys it through ILT 0x0001CFFD (matched
// ~AvailableGameInfo at 0x0010DAE0), and BfmeAptScreenSaveLoad's member at
// +0x284 (list<AvailableGameInfo>) is torn down by the 0x0056E160 ~_List_base.
struct AvailableGameInfo
{
    ~AvailableGameInfo();
    char m_pad[0x3C];
};
template void _STL::_List_base<AvailableGameInfo,
    _STL::allocator<AvailableGameInfo> >::clear();
BFME_LIST_CLEAR(0076AE50, 0x14)

// The destructor at 0x0056E160 calls the 0x0056D960 clear() above and then
// hands the head node back to the node allocator at the 0x44 width that
// element proves.  Its only callers are the unwind funclets 0x00C35468 and
// 0x00C354C0, both through ILT 0x000016CC, which destroy a
// list<AvailableGameInfo> member at +0x284, so it is ~list.  Destroying one
// through a helper is what instantiates it; the helper itself is absent from
// retail.
void destroyAvailableGameInfoList(_STL::list<AvailableGameInfo> *games)
{
	games->~list();
}
