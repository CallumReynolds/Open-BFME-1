// Open-BFME5 conversions.

// 0x009F8AB0 registers the Miles shutdown tail (_Rva009F8AA0@0, 0x009F8AA0)
// with CRT atexit (0x009F6E26).
extern "C" void __stdcall Rva009F8AA0();
extern "C" int __cdecl atexit(void (__cdecl *)(void));

int bfmeGo937A(void)
{
	atexit((void (__cdecl *)(void))Rva009F8AA0);
	return 0;
}

// 0x0090CD00, the matched Rva0090C2F0Inner::rva0090CD00LoadFromMemory.
class Rva0090C2F0Inner
{
public:
	void rva0090CD00LoadFromMemory(const char *r);
};

class BfmeThing937B
{
public:
	virtual void *bfmeVirt937B();
	void bfmeGo937B();
	char m_bfmePad[0x10];
	Rva0090C2F0Inner *m_bfmeSub;
};

void BfmeThing937B::bfmeGo937B()
{
	void *r = bfmeVirt937B();
	m_bfmeSub->rva0090CD00LoadFromMemory((const char *)r);
}

// comutil.h declares `void __stdcall _com_issue_error(HRESULT)`; the sweep
// comutil.h shim does not, so the declaration is repeated here under its exact
// defining spelling (?_com_issue_error@@YGXJ@Z).
extern void __stdcall _com_issue_error(long);

class BfmeThing937C
{
public:
	void *bfmeGo937C();
	void *m_bfmeP;
};

void *BfmeThing937C::bfmeGo937C()
{
	if (m_bfmeP == 0)
		_com_issue_error((long)0x80004003);
	return m_bfmeP;
}

class BfmeItem937E
{
public:
	virtual void bfmeVirt937E();
};

class BfmeThing937E
{
public:
	void bfmeGo937E(BfmeItem937E *item);
	int m_bfmeCount;
	int m_bfmePad;
	BfmeItem937E **m_bfmeArr;
};

void BfmeThing937E::bfmeGo937E(BfmeItem937E *item)
{
	int n = m_bfmeCount;
	m_bfmeArr[n] = item;
	++m_bfmeCount;
	item->bfmeVirt937E();
}
