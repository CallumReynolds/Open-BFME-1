// ?d_00617fb0@@YAXXZ
// partial score=0.982 date=2026-10-15
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME5: retail 0x00617FB0, 1168 bytes -- LivingWorldManager's virtual
// destructor (constructor 0x006171D0 installs the same two vftables).

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
#include "GameEngine/Source/Common/System/subsystem_interface.h"
#include "GameEngine/Source/Common/System/snapshot.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long *);

extern const char g_bfmeEmptyAscii[];
typedef unsigned short Word;

struct LwmStringHeader
{
	int m_refCount;
	Word m_length;
	Word m_capacity;
	char m_data[1];
};

struct LwmStringView
{
	LwmStringHeader *m_data;
};

namespace rts
{
	template <class T> struct hash;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const
		{
			LwmStringHeader *data = reinterpret_cast<LwmStringView *>(&value)->m_data;
			const char *p = &data->m_data[0];
			if (data == 0)
				p = g_bfmeEmptyAscii;
			unsigned int result = 0;
			while (*p != '\0')
			{
				result = result * 5 + *p;
				++p;
			}
			return result;
		}
	};
}

class LwmOwned { public: virtual ~LwmOwned(); };
class LwmOwned264 { public: ~LwmOwned264(); };
class BfmeHostAAY { public: void bfmeShutdownAAY(); };

class Lwm00C { public: ~Lwm00C(); char m_00[0x188]; };
class Lwm1AC { public: ~Lwm1AC(); char m_00[0x14]; };
class Lwm210 { public: ~Lwm210(); char m_00[0x14]; };
class Lwm270 { public: ~Lwm270(); char m_00[0xc]; };

class LwmRef
{
public:
	virtual ~LwmRef();
	long m_refs;
	__forceinline void Release_Ref()
	{
		long n = InterlockedDecrement(&m_refs);
		if (n <= 0)
			delete this;
	}
};

class LwmRefPtr
{
public:
	~LwmRefPtr()
	{
		if (m_p != 0)
			m_p->Release_Ref();
	}
	LwmRef *m_p;
};

typedef _STL::hash_map<AsciiString, LwmOwned *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Lwm194Map;
typedef _STL::hash_map<AsciiString, int, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Lwm224Map;
typedef _STL::map<int, LwmOwned *> Lwm27CMap;

class LivingWorldManager : public SubsystemInterface, public Snapshot
{
public:
	virtual ~LivingWorldManager();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

	Lwm00C m_00C;
	Lwm194Map m_194;
	int m_1A8;
	Lwm1AC m_1AC[5];
	Lwm210 m_210;
	Lwm224Map m_224;
	LwmRefPtr m_238;
	int m_23C;
	_STL::vector<int> m_240;
	_STL::vector<int> m_24C;
	_STL::vector<LwmOwned *> m_258;
	_STL::vector<LwmOwned264 *> m_264;
	Lwm270 m_270;
	Lwm27CMap m_27C;
	int m_288;
	LwmOwned *m_28C;
	int m_290;
	int m_294;
	_STL::vector<int> m_298;
};

extern LivingWorldManager *TheLivingWorldManager;

LivingWorldManager::~LivingWorldManager()
{
	((BfmeHostAAY *)this)->bfmeShutdownAAY();
	if (m_28C != 0)
	{
		delete m_28C;
		m_28C = 0;
	}
	for (unsigned int i = 0; i < m_258.size(); ++i)
		delete m_258[i];
	m_258.clear();
	for (unsigned int j = 0; j < m_264.size(); ++j)
		delete m_264[j];
	m_264.clear();
	for (Lwm194Map::iterator it = m_194.begin(); it != m_194.end(); ++it)
		delete it->second;
	m_194.clear();
	m_1A8 = 0;
	if (TheLivingWorldManager == this)
		TheLivingWorldManager = 0;
	for (Lwm27CMap::iterator jt = m_27C.begin(); jt != m_27C.end(); ++jt)
		delete jt->second;
	m_27C.clear();
}
