// cl: /O2 /MD /EHsc
// Retail [0x0045C080,0x0045C0AA): ret 4 followed by INT3 padding.
// The source-run path is GameEngine/Source/GameClient/View.cpp; no owner
// identity is proven, so the callable name retains its retail address.

// Unidentified retail leaf: conditionally scales a float and accumulates it into a
// this-relative field at +0x98. No built emitter or named caller establishes
// the owner, so this address-derived shim isolates the body for probing.
class Rva0045C080Owner
{
public:
	char m_pad[0x98];
	float m_field98;
	void bfmeAdd(float value);
};

// Retail reads the compiler literals __real@00000000 and __real@bf800000.
// Written as literals in a conditional expression, MSVC 7.1 pops the compare
// with fcomp and reloads the argument, as retail does; the if-statement form
// keeps it live with fcom (38B).
void Rva0045C080Owner::bfmeAdd(float value)
{
    m_field98 += (value < 0.0f) ? value * -1.0f : value;
}
