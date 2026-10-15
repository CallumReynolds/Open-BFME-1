// Open-BFME5 conversions.

extern "C" char g_bfmeV1187[];

struct BfmePair1187
{
	BfmePair1187(void)
	{
		m_bfme00 = 0;
		m_bfme04 = 0;
	}
	int m_bfme00;
	int m_bfme04;
};

class BfmeBase1187
{
public:
	BfmeBase1187(void) { m_bfme00 = g_bfmeV1187; }
	char *volatile m_bfme00;
	volatile int m_bfme04;
};

class BfmeA1187 : public BfmeBase1187
{
public:
	BfmeA1187(void);
	void *rva00806430(unsigned int flags);
	BfmePair1187 m_bfme08[8];
};

BfmeA1187::BfmeA1187(void)
{
	m_bfme04 = 0;
}

extern "C" void *__identifier("??_7T2EmptyDtor_00806460@@6B@")[];
struct Gen007F4D00 {static void operator delete(void *, unsigned);};

// Open BFME 2: Code/Libraries/Source/DirtySock/Y2ScalarDeleters.cpp
// ?rva00806430@BfmeA1187@@QAEPAXI@Z
void *BfmeA1187::rva00806430(unsigned int flags)
{
 m_bfme00 = (char *)__identifier("??_7T2EmptyDtor_00806460@@6B@");
 if (flags & 1)
  Gen007F4D00::operator delete(this, 0x48);
 return this;
}
