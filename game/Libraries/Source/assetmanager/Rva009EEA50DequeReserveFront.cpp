// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <deque>

class Rva009EF0D0Element;
namespace _STL {
template <> void deque<Rva009EF0D0Element *>::_M_reallocate_map(unsigned int, bool);
}
struct Rva009EEA50DequeView : _STL::deque<Rva009EF0D0Element *>
{
    void reserve_front(unsigned int nodes);
};

// Open BFME 2: Code/Libraries/Source/WWVegas/WWLib/stlport_deque_int.cpp
void Rva009EEA50DequeView::reserve_front(unsigned int nodes)
{
    _M_reserve_map_at_front(nodes);
}
