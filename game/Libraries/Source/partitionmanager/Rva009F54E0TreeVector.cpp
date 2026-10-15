// cl: /O2 /G6 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>
#include <algorithm>

struct Gen_t_009f51f0_p8cd { unsigned char storage[8]; };
namespace _STL {
template<> _Vector_base<Gen_t_009f51f0_p8cd,allocator<Gen_t_009f51f0_p8cd> >::_Vector_base(unsigned int,const allocator<Gen_t_009f51f0_p8cd>&);
}

struct Rva009F54E0Words
{
    unsigned word0;
    unsigned word1;
    // ??0Rva009F54E0Words@@QAE@XZ absent-from-retail
    Rva009F54E0Words() : word0(0), word1(0) {}
};

class Rva009F54E0TreeVector : public _STL::_Vector_base<Gen_t_009f51f0_p8cd,_STL::allocator<Gen_t_009f51f0_p8cd> >
{
    typedef _STL::_Vector_base<Gen_t_009f51f0_p8cd,_STL::allocator<Gen_t_009f51f0_p8cd> > Base;
public:
    Rva009F54E0TreeVector(unsigned n);
};

// ??0Rva009F54E0TreeVector@@QAE@I@Z
// Open BFME 2: Code/Libraries/Source/partitionmanager/partitionmanager_impl.cpp
Rva009F54E0TreeVector::Rva009F54E0TreeVector(unsigned n)
    : Base(n,_STL::allocator<Gen_t_009f51f0_p8cd>())
{
    _M_finish = reinterpret_cast<Gen_t_009f51f0_p8cd *>(_STL::uninitialized_fill_n(
        reinterpret_cast<Rva009F54E0Words *>(_M_start),n,Rva009F54E0Words()));
}
