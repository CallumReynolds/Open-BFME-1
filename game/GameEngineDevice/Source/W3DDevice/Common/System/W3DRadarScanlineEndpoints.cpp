// cl: /DNDEBUG /MD /EHsc
// stlport
// Retail 0x006C1D00: the static helper W3DRadar::renderObjectList (0x006C43F0)
// calls twice per DiscreteCircle scanline (+0x35D and +0x371) to plot the
// two end points of a castle's radar circle.  Each end point is clipped to
// the 128x128 radar cell grid and drawn with SurfaceClass::DrawPixel in the
// color the caller stores just before the loop (VA 0x012F7F44).
//
// The private register convention (xStart in EAX, xEnd in EDI, y in ESI and
// the surface wrapper in EBX, caller-cleaned) is MSVC's static-function
// convention.  The TU-local caller below exists only so the static has a
// visible call site shaped like renderObjectList's scanline loop.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
// BFME's DrawPixel takes the packed color directly (0x008FCE00).
class SurfaceClass
{
public:
	void DrawPixel(unsigned x, unsigned y, unsigned color);
};

// BFME2 W3DRadar.cpp defines the corresponding endpoint colour cell.
// BFME1 keeps its existing address-derived name; retail starts it at zero.
int g_Va012F7F44 = 0;

// upstream body: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar.cpp
inline bool legalRadarPoint(int x, int y)
{
	if (x < 0 || y < 0 || x >= 128 || y >= 128)
		return false;
	return true;
}

static __declspec(noinline) void rva006C1D00(int xStart, int xEnd, int y, SurfaceClass *surface)
{
	if (legalRadarPoint(xStart, y))
		surface->DrawPixel(xStart, y, g_Va012F7F44);
	if (legalRadarPoint(xEnd, y))
		surface->DrawPixel(xEnd, y, g_Va012F7F44);
}

// absent-from-retail: TU-local caller shaped like W3DRadar::renderObjectList's
// scanline loop, so MSVC gives the static above its private register convention.
struct HorzLine006C1D00
{
	int yPos;
	int xStart;
	int xEnd;
};

void Rva006C1D00Caller(const HorzLine006C1D00 *begin, const HorzLine006C1D00 *end,
	int yDoubled, SurfaceClass *surface)
{
	for (const HorzLine006C1D00 *it = begin; it != end; ++it)
	{
		rva006C1D00(it->xStart, it->xEnd, it->yPos, surface);
		rva006C1D00(it->xStart, it->xEnd, yDoubled - it->yPos, surface);
	}
}
