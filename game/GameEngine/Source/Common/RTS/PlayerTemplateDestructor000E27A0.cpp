// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// PlayerTemplate teardown follows the decoded BFME member layout.
#include "Common/INI.h"
#define ANIM2D_INLINE_SNAPSHOT_DTOR
#include "Common/Money.h"
#include "Common/NameKeyGenerator.h"
#include <vector>

template <class CharT> class Rva000E27A0StringBase
{
public:
	~Rva000E27A0StringBase() { releaseBuffer(); }
private:
	void releaseBuffer() { ((StringBase<CharT> *)this)->clear(); }
	CharT *m_data;
};

typedef AsciiString Rva000E27A0StringView;

struct Rva000E27A0ColorStorage
{
	float red;
	float green;
	float blue;
};

class Rva000D0310IntFourByteTree
{
public:
	~Rva000D0310IntFourByteTree();
	char m_data[0x0c];
};
typedef Rva000D0310IntFourByteTree Rva000E27A0Object060;

class Rva000D8250AsciiStringFourByteHash
{
public:
	~Rva000D8250AsciiStringFourByteHash();
	char m_data[0x14];
};
typedef Rva000D8250AsciiStringFourByteHash Rva000E27A0Object06C;

class Rva000D0430IntFourByteTree
{
public:
	~Rva000D0430IntFourByteTree();
	char m_data[0x0c];
};
typedef Rva000D0430IntFourByteTree Rva000E27A0Object080;

typedef _STL::vector<AsciiString> Rva000E27A0Object0E8;

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long *value);

class Rva000E27A0SoundRef
{
public:
	virtual ~Rva000E27A0SoundRef();
	void releaseAtRva000E27A0()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}
	volatile long m_refCount;
};

class Rva000E27A0SoundSlot
{
public:
	~Rva000E27A0SoundSlot()
	{
		if (m_object != 0)
			m_object->releaseAtRva000E27A0();
	}

	Rva000E27A0SoundRef *m_object;
};

// The shared PlayerTemplate header keeps Zero Hour field order; this view uses BFME offsets.
// The ILT row 0x000181CE still carries ??1PlayerTemplate@@QAE@XZ, so the body takes this address name.
class PlayerTemplate000E27A0
{
public:
	~PlayerTemplate000E27A0();

private:
	NameKeyType m_at_000;                                        // +0x000
	Rva000E27A0StringBase<unsigned short> m_at_004;              // +0x004
	Rva000E27A0StringView m_at_008;                              // +0x008
	char m_at_00c[0x10];                                         // +0x00c
	Money m_at_01c;                                              // +0x01c
	Rva000E27A0ColorStorage m_at_028;                            // +0x028
	Rva000E27A0StringView m_at_034;                              // +0x034
	Rva000E27A0StringView m_at_038[10];                          // +0x038
	Rva000E27A0Object060 m_at_060;                               // +0x060
	Rva000E27A0Object06C m_at_06c;                               // +0x06c
	Rva000E27A0Object080 m_at_080;                               // +0x080
	_STL::vector<int> m_intrinsicSciences;                       // +0x08c
	_STL::vector<int> m_at_098;                                  // +0x098
	Rva000E27A0StringView m_at_0a4;                              // +0x0a4
	Rva000E27A0StringView m_at_0a8;                              // +0x0a8
	Rva000E27A0StringView m_at_0ac;                              // +0x0ac
	Rva000E27A0StringView m_at_0b0;                              // +0x0b0
	int m_at_0b4;                                                // +0x0b4
	Rva000E27A0StringView m_at_0b8;                              // +0x0b8
	bool m_at_0bc;                                               // +0x0bc
	bool m_at_0bd;                                               // +0x0bd
	char m_at_0be[2];
	int m_at_0c0;                                                // +0x0c0
	int m_at_0c4;                                                // +0x0c4
	int m_at_0c8;                                                // +0x0c8
	Rva000E27A0StringView m_at_0cc;                              // +0x0cc
	Rva000E27A0StringView m_at_0d0;                              // +0x0d0
	Rva000E27A0StringView m_at_0d4;                              // +0x0d4
	Rva000E27A0StringView m_at_0d8;                              // +0x0d8
	Rva000E27A0StringView m_at_0dc;                              // +0x0dc
	Rva000E27A0StringView m_at_0e0;                              // +0x0e0
	Rva000E27A0StringView m_at_0e4;                              // +0x0e4
	Rva000E27A0Object0E8 m_at_0e8;                               // +0x0e8
	Rva000E27A0Object0E8 m_at_0f4;                               // +0x0f4
	Rva000E27A0SoundSlot m_at_100;                               // +0x100
	Rva000E27A0SoundSlot m_at_104;                               // +0x104
	Rva000E27A0SoundSlot m_at_108;                               // +0x108
	Rva000E27A0StringView m_at_10c;                              // +0x10c
	Rva000E27A0StringView m_at_110;                              // +0x110
	Rva000E27A0StringView m_at_114;                              // +0x114
	bool m_at_118;                                               // +0x118
	char m_at_119[3];
	Rva000E27A0StringView m_at_11c;                              // +0x11c
	Rva000E27A0StringView m_at_120;                              // +0x120
};

// ??1PlayerTemplate000E27A0@@QAE@XZ
PlayerTemplate000E27A0::~PlayerTemplate000E27A0()
{
}

typedef char Rva000E27A0SizeCheck[sizeof(PlayerTemplate000E27A0) == 0x124 ? 1 : -1];
