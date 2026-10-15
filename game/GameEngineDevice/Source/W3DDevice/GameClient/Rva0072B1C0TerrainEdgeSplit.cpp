// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// RVA 0072B1C0 (759 B, thiscall, ret 2Ch): terrain quad split by edge state.
// Clears four caller flags, asks the matched checkEdges (0x00729D30, same
// object) which edge midpoints of the square (x, y, w) fail the bit-plane test,
// then recurses into the 0x0072A3D0 body (ILT 0x0000FB00) on half-width
// strips and sets the flags. EA file per the wb1 run: W3DTerrainBackground.cpp;
// no Zero Hour twin, so class and method names stay address-derived.
typedef unsigned char Byte;
struct Rva00729300BitPlane;

class Rva00729D30Terrain
{
public:
	void checkEdges( int xOffset, int yOffset, int width,
		bool *top, bool *right, bool *bottom, bool *left );
	void rva0072B1C0( int arg0, int arg1, int xOffset, int yOffset, int width,
		bool *flag0, bool *flag1, bool *flag2, bool *flag3, int arg9, int arg10 );

private:
	Byte m_opaque00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva00729300BitPlane *m_map;
};

// The 0x0072A3D0 body is still only the gen_asm dump ?d_0072a3d0, so no
// object defines a member name for it. Retail reaches it through the ILT
// thunk at 0x0000FB00 (?j_0000fb00, defined by thunks_007.cpp): reference the
// thunk by name through a member-pointer union (the WeaponSet.cpp recipe),
// which keeps the thiscall push/ecx call shape and the reloc to 0x0000FB00.
extern void j_0000fb00();
typedef void (Rva00729D30Terrain::*Rva0072A3D0Fn)( int, int, int, int, int, int, int, int );

void Rva00729D30Terrain::rva0072B1C0( int arg0, int arg1, int xOffset, int yOffset, int width,
	bool *flag0, bool *flag1, bool *flag2, bool *flag3, int arg9, int arg10 )
{
	union { void (*fn)(); Rva0072A3D0Fn call; } rva0072A3D0 = { j_0000fb00 };
	*flag0 = *flag1 = *flag2 = *flag3 = false;
	bool top, right, bottom, left;
	checkEdges( xOffset, yOffset, width, &top, &right, &bottom, &left );
	int half = width / 2;
	if( right )
	{
		if( top )
		{
			(this->*rva0072A3D0.call)( arg0, arg1, xOffset, yOffset, half, width, arg9, arg10 );
			(this->*rva0072A3D0.call)( arg0, arg1, xOffset, yOffset + half, width, half, arg9, arg10 );
			*flag3 = true;
		}
		else if( bottom )
		{
			(this->*rva0072A3D0.call)( arg0, arg1, xOffset, yOffset + half, width, half, arg9, arg10 );
			(this->*rva0072A3D0.call)( arg0, arg1, xOffset + half, yOffset, half, width, arg9, arg10 );
			*flag2 = true;
		}
		else
		{
			(this->*rva0072A3D0.call)( arg0, arg1, xOffset, yOffset + half, width, half, arg9, arg10 );
			*flag3 = true;
			*flag2 = true;
		}
	}
	else if( left )
	{
		if( top )
		{
			(this->*rva0072A3D0.call)( arg0, arg1, xOffset, yOffset, half, width, arg9, arg10 );
			(this->*rva0072A3D0.call)( arg0, arg1, xOffset, yOffset, width, half, arg9, arg10 );
			*flag1 = true;
		}
		else if( bottom )
		{
			(this->*rva0072A3D0.call)( arg0, arg1, xOffset, yOffset, width, half, arg9, arg10 );
			(this->*rva0072A3D0.call)( arg0, arg1, xOffset + half, yOffset, half, width, arg9, arg10 );
			*flag0 = true;
		}
		else
		{
			(this->*rva0072A3D0.call)( arg0, arg1, xOffset, yOffset, width, half, arg9, arg10 );
			*flag1 = true;
			*flag0 = true;
		}
	}
	else if( top )
	{
		*flag3 = true;
		*flag1 = true;
		(this->*rva0072A3D0.call)( arg0, arg1, xOffset, yOffset, half, width, arg9, arg10 );
	}
	else if( bottom )
	{
		*flag2 = true;
		*flag0 = true;
		(this->*rva0072A3D0.call)( arg0, arg1, xOffset + half, yOffset, half, width, arg9, arg10 );
	}
	else
	{
		*flag3 = true;
		*flag2 = true;
		*flag1 = true;
		*flag0 = true;
	}
}
