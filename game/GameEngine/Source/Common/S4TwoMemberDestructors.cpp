// cl: /Igame/Libraries/Source/WWVegas/WWLib
//
// Four destructors -- two of 95 bytes and two of 101 -- of polymorphic classes
// with exactly two destructible members and a destructible base:
//
//     X::~X()
//     {
//         // compiler-emitted vptr restore
//         m_second.~B();
//         m_first.~A();
//         Base::~Base();
//     }
//
// WHAT THE BYTES SHOW.  `mov dword ptr [esi],<vftable>` is the FIRST thing after
// `this` is saved, and it comes BEFORE the EH state is touched -- a
// compiler-emitted store, not a source assignment.  A destructor that restores a
// vptr at offset 0 and then calls the base destructor with `ecx` UNADJUSTED puts
// the polymorphic base at offset 0 too: the vptr being restored is the base's.
//
// THE EH STATE COUNTS THE MEMBERS DOWN.  1 before the first member destructor,
// 0 before the second, -1 before the base's.  Each store says what is still
// alive if the call that follows throws, so the count is the number of
// sub-objects left -- which is how these bodies are known to have exactly TWO
// members and one base, without reading a single callee.  MSVC writes the middle
// store as a BYTE (`mov byte ptr [esp+0x10],0`) and the outer two as dwords;
// that is an encoding choice on a value that fits, not a different variable.
//
// MEMBER DESTRUCTION RUNS IN REVERSE DECLARATION ORDER, so the member at the
// HIGHER offset is destroyed first.  Retail's four pairs of offsets are
// (0x218, 0x254), (0x18, 0x24), (0x08, 0x14) and (0x15C, 0x160); the two bodies
// whose offsets need a full-width `lea` displacement are the 101-byte ones, and
// six bytes over two `lea`s is the whole 95-to-101 spread.
//
// CALLEES REPEAT ACROSS AND WITHIN ROWS, which is why the types below are named
// after DESTRUCTOR ADDRESSES rather than after the rows that use them.  One row
// destroys both its members with the SAME destructor (0x005B33B0), another does
// too (0x00887940), and 0x00887940 is also one member of a third row -- so those
// are one member type seen three times, not three.  Two rows share the base
// destructor 0x009A1A40 and so share a base type.
//
// WHAT THE BYTES CANNOT DECIDE.  How BIG the members are: only their offsets are
// observable, so each stand-in is one byte and the space between offsets is
// padding.  Whether the class has virtual functions beyond the destructor -- the
// vptr store shows only that slot zero exists.  What the total object size is:
// nothing here allocates or frees it.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; every
// callee is DECLARED, never defined, and pinned to the address its REL32
// resolves to through the ILT thunk in the way.

// The 0x009A1A40 base is the real SubsystemInterface, not a TU-local stand-in:
// retail's body there is its destructor, and the header's `AsciiString m_name` at
// +0x04 is the four bytes the old vptr-only stand-in padded around. BASESIZE
// carries the base's size so the two members keep retail's offsets.
typedef bool Bool;
#include "System/subsystem_interface.h"

#define S4_MEMBER( ADDR ) struct S4Mem##ADDR { ~S4Mem##ADDR(); };
#define S4_BASE( ADDR ) struct S4Base##ADDR { virtual ~S4Base##ADDR(); };

struct S4Mem004948B0
{
	S4Mem004948B0( void *owner );
	~S4Mem004948B0();
};
S4_MEMBER( 005864A0 )
S4_MEMBER( 005879C0 )
S4_MEMBER( 005B33B0 )
S4_MEMBER( 00887940 )

struct S4Base00479CD0
{
	S4Base00479CD0( void *owner );
	virtual ~S4Base00479CD0();

	char m_pad04[ 4 ];
	unsigned int m_flags08;
};
S4_BASE( 0077C1F0 )

// The two SubsystemInterface rows spell their padding explicitly because the
// real base is eight bytes wide: the 0x005B37C0 row's first member starts at the
// base's very end, with no gap at all for the old vptr-only stand-in to leave.
#define S4_TWO_MEMBER_DTOR( NAME, BASE, PAD_A, FIRST, PAD_B, SECOND )           \
	struct S4Dtor##NAME : BASE                                                 \
	{                                                                          \
		char m_padA[ PAD_A ];                                                  \
		S4Mem##FIRST m_first;                                                  \
		char m_padB[ PAD_B ];                                                  \
		S4Mem##SECOND m_second;                                                \
		virtual ~S4Dtor##NAME();                                               \
	};                                                                         \
	S4Dtor##NAME::~S4Dtor##NAME()                                              \
	{                                                                          \
	}

#define S4_TWO_MEMBER_DTOR_NOPAD_A( NAME, BASE, FIRST, PAD_B, SECOND )          \
	struct S4Dtor##NAME : BASE                                                 \
	{                                                                          \
		S4Mem##FIRST m_first;                                                  \
		char m_padB[ PAD_B ];                                                  \
		S4Mem##SECOND m_second;                                                \
		virtual ~S4Dtor##NAME();                                               \
	};                                                                         \
	S4Dtor##NAME::~S4Dtor##NAME()                                              \
	{                                                                          \
	}

// The +0x254 member of the 0x00494090 class is the 0x00887940 type seen with
// its four-byte handle, which its constructor zeroes.
struct S4Str00887940 : S4Mem00887940
{
	S4Str00887940() : m_data( 0 ) {}
	void *m_data;
};

// Retail 0x00494110 (132 bytes) constructs the 0x00494090 class: base
// constructor (ILT 0x0001B9FA) with the owner, the +0x218 member
// (Rva004948B0OwnedSubsystem's constructor, ILT 0x0004054D) with 0, then the
// zeroed string handle and three zeroed words, the base flags at +0x08 or'ed
// with 0x640 and copied to +0x250, and a cleared bool.  The three words are one
// member object: as separate initialised members MSVC schedules their stores
// after the flag update, where retail stores them before.
struct S4Triple00494110
{
	S4Triple00494110() : m_a( 0 ), m_b( 0 ), m_c( 0 ) {}
	int m_a;
	int m_b;
	int m_c;
};

struct S4Dtor00494090 : S4Base00479CD0
{
	S4Dtor00494090( void *owner );
	virtual ~S4Dtor00494090();

	char m_padA[ 0x218 - 0xC ];
	S4Mem004948B0 m_first;
	char m_padB[ 0x250 - 0x219 ];
	unsigned int m_flags250;
	S4Str00887940 m_second;
	S4Triple00494110 m_258;
	bool m_264;
};

S4Dtor00494090::S4Dtor00494090( void *owner )
	: S4Base00479CD0( owner ), m_first( 0 )
{
	m_flags08 |= 0x640;
	m_flags250 = m_flags08;
	m_264 = false;
}

S4Dtor00494090::~S4Dtor00494090()
{
}
S4_TWO_MEMBER_DTOR( 00587B30, SubsystemInterface, 0x18 - 8, 005864A0, 0xB, 005879C0 )
S4_TWO_MEMBER_DTOR_NOPAD_A( 005B37C0, SubsystemInterface, 005B33B0, 0xB, 005B33B0 )
S4_TWO_MEMBER_DTOR( 0077EB20, S4Base0077C1F0, 0x15C - 4, 00887940, 3, 00887940 )
