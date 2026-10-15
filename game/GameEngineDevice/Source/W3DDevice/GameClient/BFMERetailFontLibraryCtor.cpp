// cl: /DNDEBUG /MD /EHsc
// stlport

// ??0BFMERetailFontLibrary@@QAE@XZ
// Retail 0x004769A0 constructs the BFME font-library extension.  The
// createFontLibrary caller in W3DGameClient.cpp and the vtable at 0x010F7650
// establish the owner and the inherited SubsystemInterface layout.

namespace _STL
{

// STLport's node allocator entry point is the private
// _STL::__node_alloc<true, 0>::_M_allocate (retail 0x0082E540); this
// TU-local helper reaches it under its real name.
static void *nodePoolAllocate(unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *nodePoolAllocate(unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
};
static inline void *nodePoolAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }

}

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *str);
	void set(const BFMERetailAsciiString &other);
	void releaseBuffer();
};

class UnicodeString : public BFMERetailAsciiString
{
public:
	UnicodeString(const char *str) : BFMERetailAsciiString(str) {}
	~UnicodeString(void) { releaseBuffer(); }
	void set(const UnicodeString &other);
	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}
};

class SubsystemInterface
{
public:
	SubsystemInterface(void);
	virtual ~SubsystemInterface(void);

	UnicodeString m_bfmeName;
};

struct BfmeTreeHeader
{
	unsigned char m_color;
	unsigned int m_parent;
	BfmeTreeHeader *m_left;
	BfmeTreeHeader *m_right;
};

class BfmeMemACA
{
public:
	BfmeMemACA(void)
	{
		m_node = 0;
		m_node = (BfmeTreeHeader *)_STL::nodePoolAllocate(0x18);
		m_count = 0;
		m_node->m_color = 0;
		m_node->m_parent = 0;
		m_node->m_left = m_node;
		m_node->m_right = m_node;
	}
	~BfmeMemACA(void);

	BfmeTreeHeader *m_node;
	unsigned int m_count;
	unsigned int m_compare;
};

class BfmeMemBCA
{
public:
	BfmeMemBCA(void)
	{
		m_node = 0;
		m_node = (BfmeTreeHeader *)_STL::nodePoolAllocate(0x18);
		m_count = 0;
		m_node->m_color = 0;
		m_node->m_parent = 0;
		m_node->m_left = m_node;
		m_node->m_right = m_node;
	}
	~BfmeMemBCA(void);

	BfmeTreeHeader *m_node;
	unsigned int m_count;
};

class BFMERetailFontLibrary : public SubsystemInterface
{
public:
	BFMERetailFontLibrary(void);
	virtual void anchor(void) = 0;

	unsigned int m_fontList;
	unsigned int m_count;
	BfmeMemACA m_fontTreeA;
	BfmeMemBCA m_fontTreeB;

};

BFMERetailFontLibrary::BFMERetailFontLibrary(void)
{
	m_fontList = 0;
	m_count = 0;

	UnicodeString name("TheFontLibrary");
	m_bfmeName = name;
}
