// cl: /EHsc /Igame/GameEngine/Source/GameClient/System/FXParticleSystem /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
//
// Two-argument constructor of class Rva005ECFA0 (retail 0x00600BE0, 440 B).
// IDENTITY: after its base calls it stamps 0x0111327C / 0x01113278 /
// 0x01113274 at +0/+0x14/+0x18 and 0x01113290 at +0x1C, the four vftables the
// landed copy constructor ??0Rva005ECFA0@@QAE@ABV0@@Z (0x005ECFA0,
// V3ModuleInfoCompositeCopyCtors.cpp) stamps, and dir32_addresses.csv records
// them only as Rva005ECFA0 vftables.  The bases are the same as that copy
// constructor's: the V3Mid01113190 head chain (here with its constructor
// inlined: BfmeHolderCU-shaped 0x005DD290 call, then the +0x14/+0x18 bases'
// own vptrs 0x0111089C / 0x0110F9E8 and the 0x01113190/8C/88 mid stamps) and
// FXParticleSystem::RenderObjectUpdateModuleInfo at +0x1C (0x00600460).
// The body then copies twelve 12-byte blocks and a dword out of the second
// argument into this+0x20.. .

#include "fx_particle_system.h"

class BfmeListCU;

class V3Slot0
{
public:
	V3Slot0( BfmeListCU **list, void *b );
	virtual void s0();
	virtual ~V3Slot0() {}
	int m_a, m_b, m_c, m_d;
};
// The +0x14 and +0x18 bases keep their own vptrs 0x0111089C / 0x0110F9E8 in
// retail, which dir32_addresses.csv records as these two named classes.
namespace FXParticleSystem {
class DefaultModule2SecondarySlice { public: virtual void s0(); };
class DefaultModule2CategorySlice { public: virtual void s0(); };
}
class __declspec(novtable) V3Slot1 : public FXParticleSystem::DefaultModule2SecondarySlice {};
class __declspec(novtable) V3Slot2 : public FXParticleSystem::DefaultModule2CategorySlice {};

class Rva005EC930 : public V3Slot0, public V3Slot1, public V3Slot2
{
public:
	Rva005EC930( void *a, void *b ) : V3Slot0( (BfmeListCU **)a, b ) {}
};

class V3Mid01113190 : public Rva005EC930
{
public:
	V3Mid01113190( void *a, void *b ) : Rva005EC930( a, b ) {}
};

class Rva005ECFA0
	: public V3Mid01113190,
	  public FXParticleSystem::RenderObjectUpdateModuleInfo
{
public:
	Rva005ECFA0( void *a, void *b );
};

struct Rva005ECFA0Block
{
	unsigned int w0, w4, w8;
};

Rva005ECFA0::Rva005ECFA0( void *a, void *b )
	: V3Mid01113190( a, b ),
	  RenderObjectUpdateModuleInfo()
{
	char *dst = (char *)this;
	const char *src = (const char *)b;
	*(Rva005ECFA0Block *)( dst + 0x20 ) = *(const Rva005ECFA0Block *)( src + 0xc );
	*(Rva005ECFA0Block *)( dst + 0x2c ) = *(const Rva005ECFA0Block *)( src + 0x18 );
	*(Rva005ECFA0Block *)( dst + 0x38 ) = *(const Rva005ECFA0Block *)( src + 0x24 );
	*(Rva005ECFA0Block *)( dst + 0x44 ) = *(const Rva005ECFA0Block *)( src + 0x30 );
	*(Rva005ECFA0Block *)( dst + 0x50 ) = *(const Rva005ECFA0Block *)( src + 0x3c );
	*(Rva005ECFA0Block *)( dst + 0x5c ) = *(const Rva005ECFA0Block *)( src + 0x48 );
	*(Rva005ECFA0Block *)( dst + 0x68 ) = *(const Rva005ECFA0Block *)( src + 0x54 );
	*(Rva005ECFA0Block *)( dst + 0x74 ) = *(const Rva005ECFA0Block *)( src + 0x60 );
	*(Rva005ECFA0Block *)( dst + 0x80 ) = *(const Rva005ECFA0Block *)( src + 0x6c );
	*(Rva005ECFA0Block *)( dst + 0x8c ) = *(const Rva005ECFA0Block *)( src + 0x78 );
	*(Rva005ECFA0Block *)( dst + 0x98 ) = *(const Rva005ECFA0Block *)( src + 0x84 );
	*(Rva005ECFA0Block *)( dst + 0xa4 ) = *(const Rva005ECFA0Block *)( src + 0x90 );
	*(unsigned int *)( dst + 0xb0 ) = *(const unsigned int *)( src + 0x9c );
}
