// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME: retail 0x003A4FD0 (220 bytes, ret 4). A living-world state
// update: unless its 0x003A4E30 check (BfmeHostCB::bfmePopCB on the same
// object) consumes the call, and when both flags at +0x1D/+0x1E are set, it
// looks up the region under the point (x, y, 0) through the campaign's region
// manager (0x012F1028 +0x28), and when 0x003CAE00 accepts that region it
// hands the region (+4), this object's name (0x003A4390) and the argument to
// the manager's 0x003C9CB0, then tells the campaign (0x003BE020). The flag at
// +0x1C is cleared on every path. Class and method names are address-derived.
//
// Shape note measured against retail: y is read into a local before the
// manager is loaded (retail's fld/fstp of y precedes the integer copy of x).
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class LivingWorldRegion;

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8160( Coord3D *point );
	bool rva003CAE00( LivingWorldRegion *region );
	void rva003C9CB0( void *a, void *b, void *c, void *d );
};

class Glo012F1028Type
{
public:
	void rva003BE020( LivingWorldRegion *region );

	char m_unmodelled00[ 0x28 ];
	LivingWorldRegionManager *m_regionManager;
};
extern Glo012F1028Type *Glo012F1028;

class BfmeHostCB
{
public:
	char bfmePopCB();
};

// 0x003A4390's pinned spelling: return by value the string member at +4.
class Gen003BD7D0Node
{
public:
	AsciiString rva003a4390();
};

class Rva003A4FD0State
{
public:
	void update( void *arg );

private:
	char m_unmodelled00[ 0x0C ];
	float m_x;
	float m_y;
	char m_unmodelled14[ 8 ];
	unsigned char m_rva1C;
	unsigned char m_rva1D;
	unsigned char m_rva1E;
};

void Rva003A4FD0State::update( void *arg )
{
	if( ( (BfmeHostCB *)this )->bfmePopCB() )
		return;
	if( m_rva1D && m_rva1E )
	{
		float y = m_y;
		LivingWorldRegionManager *manager = Glo012F1028->m_regionManager;
		Coord3D point;
		point.y = y;
		point.x = m_x;
		point.z = 0;
		LivingWorldRegion *region = manager->rva003C8160( &point );
		if( region && manager->rva003CAE00( region ) )
		{
			AsciiString name = ( (Gen003BD7D0Node *)this )->rva003a4390();
			manager->rva003C9CB0( (char *)region + 4, &name, 0, arg );
			Glo012F1028->rva003BE020( region );
		}
	}
	m_rva1C = 0;
}
