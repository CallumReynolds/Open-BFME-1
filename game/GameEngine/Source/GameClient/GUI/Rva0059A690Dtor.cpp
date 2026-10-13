// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0059A690 (18 B): re-seats vftable 0x0110C604, clears the int at
// +0x0C and tail-jumps to the base destructor at ILT 0x0001AA9B (the same
// base the VptrTailJumpDestructors family jumps to).  vftable 0x0110C604 is
// recorded in dir32_addresses.csv under the address-derived class
// Rva0059AA90, so this body references that class name; the owning class is
// ButtonFlashTransition per ilt_oracle, but the DIR32 rename is not done.

class Rva0001AA9BTailBase
{
public:
	virtual ~Rva0001AA9BTailBase();
};

class Rva0059AA90 : public Rva0001AA9BTailBase
{
public:
	virtual ~Rva0059AA90();

private:
	int m_04;
	int m_08;
	int m_0C;
};

Rva0059AA90::~Rva0059AA90()
{
	m_0C = 0;
}
