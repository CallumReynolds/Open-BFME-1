// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
// Westwood vector template instances that hanim.obj does not provide in retail.
// hanim.obj was built without always.h's operator new[]/delete[] (see hanim.cpp);
// these copies call operator new[]/delete[] (??_U 0x00881F70, ??_V 0x00881EF0),
// so retail took them from an object that declared them.  Same flags and headers
// as hanim.cpp otherwise.
#include "wwstring.h"
#define MUTEX_H
#include "../../../../../inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mempool.h"
#include "hanim.h"
#include "vector.h"

template VectorClass<HAnimComboDataClass *>::VectorClass(int, HAnimComboDataClass * const *);
template bool VectorClass<HAnimComboDataClass *>::Resize(int, HAnimComboDataClass * const *);
template void DynamicVectorClass<HAnimComboDataClass *>::Clear(void);
template class DynamicVectorClass<NamedPivotMapClass::WeightInfoStruct>;

// 0x001A3D10/24: the same code as TimeCodedMotionChannelClass's destructor, but
// with operator delete[]; no caller names it, so its owner is address-derived.
class Rva001A3D10
{
public:
	void body(void);

private:
	char m_lead[0x18];
	unsigned char *m_data;
};

void Rva001A3D10::body(void)
{
	delete [] m_data;
	m_data = 0;
}
