// cl: /O2 /GX- /DNDEBUG /MD


struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get(void);

class Rva007E8810Message
{
public:
	Rva007E8810Message();
	~Rva007E8810Message();
	int getInt(const char *key, int defaultValue);
	// ?attach@Rva007E8810Message@@QAEXPBE@Z absent-from-retail
	void attach(const unsigned char *record) { m_record = record; }

private:
	char m_pad[0x10];
	const unsigned char *m_record;
	char m_pad14[0x20];
};

class Rva00800780Addr
{
public:
	~Rva00800780Addr();
	virtual void v0();

	int m_04;
	int m_08;
	int m_0C;
};

struct Rva7F4CC0ConstructorThunk
{
	Rva7F4CC0ConstructorThunk();

	unsigned mType;
	unsigned mId;
	const unsigned char *mData;
	unsigned mSize;
	bool mFlag;
	Rva00800780Addr mAddr;
};

class Rva007F4BB0Handler
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void onPacket(Rva7F4CC0ConstructorThunk *packet);
};

class Rva007F4BB0Base
{
public:
	virtual ~Rva007F4BB0Base();
};

class Rva007F4BB0Listener
{
public:
	virtual ~Rva007F4BB0Listener();
	virtual int eq(const void *other, int, int) const;
	virtual bool dispatch(const Rva00800780Addr &from,
		const unsigned char *data, int length);
};

class Gen007F4D00 : public Rva007F4BB0Base, public Rva007F4BB0Listener
{
public:
	virtual bool dispatch(const Rva00800780Addr &from,
		const unsigned char *data, int length);

	// ?getHandler@Gen007F4D00@@QAEPAVRva007F4BB0Handler@@H@Z absent-from-retail
	Rva007F4BB0Handler *getHandler(int type)
	{
		if (type >= 0 && type < 2)
			return m_handlers[type];
		return 0;
	}

private:
	Rva007F4BB0Handler *m_handlers[2];
	int m_10;
	int m_14;
};

// Open BFME 2: Code/GameEngine/Source/GameNetwork/Rva00661650AriesUdp.cpp
// ?dispatch@Gen007F4D00@@UAE_NABVRva00800780Addr@@PBEH@Z
bool Gen007F4D00::dispatch(const Rva00800780Addr &from,
	const unsigned char *data, int length)
{
	Rva7F4CC0ConstructorThunk fap;
	fap.mAddr = from;
	fap.mType = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
	fap.mId = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
	fap.mSize = (data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11];
	fap.mData = data + 12;
	if (!(length >= (int)fap.mSize))
		Rva007EB810Get()->fail("length >= (int)fap.mSize",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\ariesudp.cpp", 176);
	fap.mSize -= 12;

	Rva007E8810Message msg;
	msg.attach(fap.mData);
	Rva007F4BB0Handler *handler = getHandler(msg.getInt("TYPE", 0));
	if (handler)
		handler->onPacket(&fap);
	return true;
}
