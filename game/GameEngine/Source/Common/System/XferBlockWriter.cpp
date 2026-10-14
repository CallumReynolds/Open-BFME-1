// cl: /DNDEBUG /MD /O2 /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
// Signed 32-bit storage is chosen for this reconstructed file-position interface;
// retail's original int-versus-long template spelling is unresolved.
class XferBlockPositionStack : private std::vector<int>
{
public:
    typedef int position_type;
    __declspec(noinline) void pushPosition(const position_type &position);
};

// Keep the retail call boundary while exposing the vendor body to its caller.
void XferBlockPositionStack::pushPosition(const position_type &position)
{
    std::vector<int>::push_back(position);
}

// The constructor at 0x009D8630 installs vtable 0x01144090; its original
// class spelling is unresolved. This interface names the observed block-writing role.

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};
// Retail ThrowInfo names XferException and describes its eight-byte value.
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class BfmeByteStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual int write(const void *buffer, int size);
	virtual int skip(int count, int flag);
};

class Rva009D8630BlockWriter
{
public:
	virtual ~Rva009D8630BlockWriter();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual int beginBlock(const char *name);
	void rva009D86E0(const char *name);

private:
	BfmeByteStream *m_stream;
	bool m_flag;
	unsigned char m_pad09[3];
	XferBlockPositionStack m_positions;
};

int Rva009D8630BlockWriter::beginBlock(const char *name)
{
	if (m_stream == 0)
		return 0;

	int marker = 0x424c4f4b;
	if (m_stream->write(&marker, 4) != 4)
	{
		throw XferException(1, 0);
	}

	if (m_flag)
		rva009D86E0(name);

	int streamPosition = m_stream->skip(0, 1);
	if (streamPosition == -1)
	{
		// Preserve retail's position store after the failure check.
		_ReadWriteBarrier();
		throw XferException(1, 0);
	}

	int position = streamPosition;
	m_positions.pushPosition(position);

	int zero = 0;
	if (m_stream->write(&zero, 4) != 4)
	{
		throw XferException(1, 0);
	}

	return 0;
}
