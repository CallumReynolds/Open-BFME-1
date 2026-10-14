// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define private public
#include <hash_map>
#undef private
#include <string>
#include <string.h>

struct BfmeFormattedText
{
	char *text;
	int tag;
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

// ?rva009D86E0@Rva009D8630BlockWriter@@QAEXPBD@Z
class BfmeByteStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual int write(const void *buffer, int size);
};

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	Rva009D86E0String;
typedef _STL::pair<const Rva009D86E0String, int> Rva009D86E0Pair;
typedef _STL::hash_map<Rva009D86E0String, int,
	_STL::hash<Rva009D86E0String>, _STL::equal_to<Rva009D86E0String>,
	_STL::allocator<Rva009D86E0Pair> > Rva009D86E0NameMap;
typedef Rva009D86E0NameMap::_Ht::_Node Rva009D86E0Node;

struct Rva009D86E0AuxValue
{
	int words[3];
};
typedef _STL::pair<const int, Rva009D86E0AuxValue> Rva009D86E0AuxPair;
typedef _STL::hash_map<int, Rva009D86E0AuxValue, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<Rva009D86E0AuxPair> >
	Rva009D86E0AuxMap;

// ?rva009D86E0@Rva009D8630BlockWriter@@QAEXPBD@Z
class Rva009D86E0XferSaveBase
{
public:
	virtual void slot0();

protected:
	BfmeByteStream *m_stream;
	bool m_flag;
	unsigned char m_pad09[3];
	unsigned char m_positions[0x0c];
};

// ?rva009D86E0@Rva009D8630BlockWriter@@QAEXPBD@Z
class Rva009D8630BlockWriter : public Rva009D86E0XferSaveBase
{
public:
	void rva009D86E0(const char *name);

private:
	Rva009D86E0NameMap m_names;
	Rva009D86E0AuxMap m_aux;
};

// ?rva009D86E0@Rva009D8630BlockWriter@@QAEXPBD@Z
void Rva009D8630BlockWriter::rva009D86E0(const char *name)
{
	Rva009D86E0Node *found;
	const char *cursor;
	unsigned int length;

	if (name == 0 || *name == 0)
	{
		unsigned char marker = 0;
		if (m_stream->write(&marker, 1) != 1)
		{
			throw XferException(1, 0);
		}
		return;
	}

	{
		const Rva009D86E0String key(name);
		found = m_names._M_ht._M_find(key);
	}
	if (found)
	{
		unsigned char marker = 0xff;
		if (m_stream->write(&marker, 1) != 1)
		{
			throw XferException(1, 0);
		}

		if (m_stream->write(&found->_M_val.second, 4) != 4)
		{
			throw XferException(1, 0);
		}
		return;
	}

	length = static_cast<unsigned int>(strlen(name));
	if (length > 0xfe)
		length = 0xfe;

	if (m_stream->write(&length, 1) != 1)
	{
		throw XferException(1, 0);
	}
	if (m_stream->write(name, static_cast<int>(length)) !=
		static_cast<int>(length))
	{
		throw XferException(1, 0);
	}

	{
		const Rva009D86E0String key(name);
		const int auxCount = static_cast<int>(m_aux.size());
		const int nameCount = static_cast<int>(m_names.size());
		m_names[key] = nameCount + auxCount;
	}
}
