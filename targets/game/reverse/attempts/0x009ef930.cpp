// ?Rva009EF930@@YAXXZ
// partial score=1.0 date=2026-10-15
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <deque>

class Rva009EF0D0Element;
namespace _STL {
template <> void deque<Rva009EF0D0Element *>::_M_reallocate_map(unsigned int, bool);
template <> void deque<Rva009EF0D0Element *>::_M_push_front_aux_v(Rva009EF0D0Element *const &);
// Open BFME 2: Code/Libraries/Source/WWVegas/WWLib/stlport_deque_int.cpp
template void deque<Rva009EF0D0Element *>::push_front(Rva009EF0D0Element *const &);
}
