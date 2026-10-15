// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME5: retail 0x00617FB0 -- LivingWorldManager's virtual destructor
// (constructor 0x006171D0 installs the same two vftables, 0x01116BFC and
// 0x01116BE8).  The body ends in RET at +0x495 and the next function starts
// after INT3 padding, so the true extent is 1174 bytes (0x496), not the 1168
// the carved gen-dump row recorded.
//
// The AsciiString hasher routes through STLport's hash<const char *> (the
// h*5+c walk), exactly as the matched WindowTableNameClearForEach.cpp does.
// That spelling, not an open-coded loop, fixes the schedule of the inlined
// _Ht_iterator::_M_skip_to_next bucket-count load.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
#include "GameEngine/Source/Common/System/subsystem_interface.h"
#include "GameEngine/Source/Common/System/snapshot.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long *);

namespace rts
{
	template <class T> struct hash;

	template <> struct hash<AsciiString>
	{
		size_t operator()(AsciiString value) const
		{
			_STL::hash<const char *> tmp;
			return tmp((const char *)value.str());
		}
	};
}

class LwmOwned { public: virtual ~LwmOwned(); };
class Rva0060B6B0 { public: ~Rva0060B6B0(); };
class BfmeHostAAY { public: void bfmeShutdownAAY(); };

class Rva0060EBB0 { public: ~Rva0060EBB0(); char m_00[0x188]; };
class Rva00614820 { public: ~Rva00614820(); char m_00[0x14]; };
class Rva006129E0 { public: ~Rva006129E0(); char m_00[0x14]; };
class Rva006152A0 { public: ~Rva006152A0(); char m_00[0xc]; };

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

// Value types carry address-derived names: the mangled container names are
// part of the pinned callee identities (retail's thunk table cannot confirm a
// guessed class name, so the placeholder spelling is the honest one).
struct Rva00614150Value { LwmOwned *m_p; };
struct Rva00614280Value { int m_v; };
struct Rva00611500Value { LwmOwned *m_p; };

typedef _STL::hash_map<AsciiString, Rva00614150Value, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Lwm194Map;
typedef _STL::hash_map<AsciiString, Rva00614280Value, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Lwm224Map;
typedef _STL::map<int, Rva00611500Value> Lwm27CMap;

// Retail's two vftables for this class (0x01116BFC primary, 0x01116BE8 for the
// Snapshot base) must be referenced under names that encode their own
// addresses, which the DIR32 gate requires of a vftable no data row owns.  The
// vftable name carries the base-class name, so each base is spelled through a
// thin address-named wrapper.  The wrappers add no members and no stores.
class Rva00D16BFC : public SubsystemInterface {};
class Rva00D16BE8 : public Snapshot {};

class LivingWorldManager : public Rva00D16BFC, public Rva00D16BE8
{
public:
	virtual ~LivingWorldManager();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

	Rva0060EBB0 m_00C;
	Lwm194Map m_194;
	int m_1A8;
	Rva00614820 m_1AC[5];
	Rva006129E0 m_210;
	Lwm224Map m_224;
	LwmRefPtr m_238;
	int m_23C;
	_STL::vector<int> m_240;
	_STL::vector<int> m_24C;
	_STL::vector<LwmOwned *> m_258;
	_STL::vector<Rva0060B6B0 *> m_264;
	Rva006152A0 m_270;
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
		delete it->second.m_p;
	m_194.clear();
	m_1A8 = 0;
	if (TheLivingWorldManager == this)
		TheLivingWorldManager = 0;
	for (Lwm27CMap::iterator jt = m_27C.begin(); jt != m_27C.end(); ++jt)
		delete jt->second.m_p;
	m_27C.clear();
}
