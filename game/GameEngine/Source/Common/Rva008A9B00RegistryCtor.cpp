// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class Rva008A9B00Base;

struct BfmeRegistryKind1
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(Rva008A9B00Base *obj);
};

struct Rva00899560Pool;
extern Rva00899560Pool *g_rva01337810GcRoots;

struct Rva00891B80Block
{
	unsigned short m_ref;
};

class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;	// shared empty string block 0x012D5298

class Rva008A9B00Base
{
public:
	__forceinline Rva008A9B00Base(unsigned int kind)
	{
		unsigned int flags = m_flags;
		flags &= 0xf0008000 | kind;
		flags |= 0x40008000 | kind;
		m_flags = flags;
		((BfmeRegistryKind1 *)g_rva01337810GcRoots)->addOrClear(this);
	}

	virtual ~Rva008A9B00Base() {}

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

private:
	unsigned int m_flags;
};

__forceinline void BfmeRegistryKind1::addOrClear(Rva008A9B00Base *obj)
{
	int index = m_count;
	if (index >= m_capacity)
	{
		obj->clearRegistered();
		return;
	}

	m_entries[index] = obj;
	++m_count;
}

class Rva008A9B00String
{
public:
	Rva008A9B00String()
	{
		m_block = (Rva00891B80Block *)&g_rva012D5298Empty;
		++(*(Rva00891B80Block *)&g_rva012D5298Empty).m_ref;
	}

private:
	Rva00891B80Block *m_block;
};

class Rva008A9B00 : public Rva008A9B00Base
{
public:
	Rva008A9B00();

private:
	Rva008A9B00String m_string;
	int m_extra;
};

Rva008A9B00::Rva008A9B00() :
	Rva008A9B00Base(1),
	m_extra(0)
{
}
