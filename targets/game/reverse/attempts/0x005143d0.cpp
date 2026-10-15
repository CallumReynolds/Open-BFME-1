// ?h005143D0@Glo00EF4988@@QAEXXZ
// partial score=0.9872 date=2026-10-15
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include
// stlport
// The visible selection helper preserves vector ownership through cleanup.
#include "GameClient/BfmeAptScreenBaseLayout.h"
typedef bool Bool;
typedef int Int;
typedef unsigned short WideChar;

#include <vector>

class GameWindow;

#include "unicode_string.h"
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const UnicodeString &other)
{
 ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&other);
}
inline UnicodeString::~UnicodeString()
{
 ((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &other)
{
 ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&other);
 return *this;
}

class GameTextInterface
{
public:
	virtual void bfmeSlot00GT();
	virtual void bfmeSlot01GT();
	virtual void bfmeSlot02GT();
	virtual void bfmeSlot03GT();
	virtual void bfmeSlot04GT();
	virtual void bfmeSlot05GT();
	virtual void bfmeSlot06GT();
	virtual void bfmeSlot07GT();
	virtual void bfmeSlot08GT();
	virtual void bfmeSlot09GT();
	virtual UnicodeString fetch( const char *label, bool *found );
};

extern GameTextInterface *TheGameText;

// Retain the owner layout already verified by the selection helper and
// the matched constructor at RVA 0x005160E0.
class BfmeAptScreenBase
{
public:
	virtual ~BfmeAptScreenBase();
	virtual int aptSlot1(unsigned int, unsigned int, unsigned int);
	virtual int aptSlot2(unsigned int, unsigned int, unsigned int);
	virtual int aptSlot3(unsigned int);
	virtual int aptSlot4(unsigned int, unsigned int);
	virtual int aptSlot5();
	virtual int aptSlot6();
	virtual void *aptSlot7();
	virtual int aptSlot8();
	virtual int aptSlot9();
	virtual bool aptSlot10();
	virtual bool aptSlot11();
	virtual void aptSlot12();
	virtual void aptSlot13();
private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

class S4Owner
{
public:
	virtual ~S4Owner();
private:
	unsigned char m_unmodelled[0x30];
};

class _bfme_AptGameWindow : public BfmeAptScreenBase, public S4Owner
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	unsigned char m_tail[0xc];
};

class __multiple_inheritance AptInGameChat
	: public _bfme_AptGameWindow
{
public:
	void OnBttnAddFriend(const char *name);
	void OnBttnRemoveFriend(const char *name);
	Int rva00513BF0( GameWindow *list, void *selected, Int buddyMask, Bool skipStatusFilter );
	Int _bfme_getInternetPlayerStatus( const UnicodeString &name );
	Int rva00512890( Int profileID, UnicodeString &result );

private:
	int m_field258;
	unsigned char m_padding25c[ 4 ];
	int m_field260;
	GameWindow *m_friendsList;
	int m_field268;
	unsigned char m_padding26c[ 4 ];
	unsigned char m_tail[ 0x34 ];
};

Int GadgetListBoxGetNumEntries( GameWindow *listbox );
void GadgetListBoxGetSelected( GameWindow *listbox, Int *selectList );
UnicodeString GadgetListBoxGetText( GameWindow *listbox, Int row, Int column );
void *GadgetListBoxGetItemData( GameWindow *listbox, Int row, Int column );

class Player
{
public:
	UnicodeString getPlayerDisplayName();
};

struct Rva002EE330PlayerList
{
	unsigned char m_unmodelled000[ 0xc ];
	Player *m_local;
};

class PlayerList;
extern PlayerList *ThePlayerList;	// retail [0x012ED748]

// The same object as ThePlayerList; this body reads it through this view.
static inline Rva002EE330PlayerList *rva002EE330ThePlayers( void )
{
	return (Rva002EE330PlayerList *)ThePlayerList;
}

// List-box text column read from .rdata at VA 0x01106F04 (value 2).
extern const Int Rva01106F04;

// ?rva00513BF0@AptInGameChat@@QAEHPAVGameWindow@@PAXH_N@Z
inline __declspec(noinline) Int AptInGameChat::rva00513BF0( GameWindow *list, void *selected, Int buddyMask, Bool skipStatusFilter )
{
	std::vector<Int> *profileIDs = (std::vector<Int> *)selected;
	Int entries = GadgetListBoxGetNumEntries( list );
	profileIDs->erase( profileIDs->begin(), profileIDs->end() );

	Int index = 0;
	Int localStatus = 0;
	if ( !skipStatusFilter )
	{
		Player *localPlayer = rva002EE330ThePlayers()->m_local;
		if ( localPlayer != 0 )
			localStatus = _bfme_getInternetPlayerStatus( localPlayer->getPlayerDisplayName() );
	}
	if ( entries != 0 )
	{
		Int *selectedRows = 0;
		GadgetListBoxGetSelected( list, (Int *)&selectedRows );

		for ( index = 0; index < entries; ++index )
		{
			if ( selectedRows[ index ] < 0 )
				break;

			Bool keep = true;
			if ( localStatus != 0 )
			{
				UnicodeString rowName = GadgetListBoxGetText( m_friendsList, selectedRows[ index ], Rva01106F04 );
				Int rowStatus = _bfme_getInternetPlayerStatus( rowName );
				if ( ( rowStatus == 2 ) ^ ( localStatus == 2 ) )
					keep = false;
			}

			if ( keep )
			{
				Int profileID = (Int)GadgetListBoxGetItemData( m_friendsList, selectedRows[ index ], 0 );
				UnicodeString buddyName;
				if ( buddyMask == 0 || ( buddyMask & rva00512890( profileID, buddyName ) ) )
					profileIDs->push_back( profileID );
			}
		}
	}

	return (Int)profileIDs->size();
}

class BfmeLevelAN
{
public:
    char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5,
        int p6, int p7, int p8);
};

struct Rva00579160Manager
{
    // ?fire@Rva00579160Manager@@QAEXIPBDHHHHHH@Z absent-from-retail
    void fire(unsigned int target, const char *name, Int a, Int b, Int c, Int d,
        Int e, Int f)
    {
        ((BfmeLevelAN *)this)->bfmeBuildAN((unsigned int)target, (int)name,
            a, b, c, d, e, f);
    }
};
extern Rva00579160Manager *Rva00579160TheManager;
extern char g_bfmeFmtC1064[];

typedef std::vector<int> Rva005143D0Vector;

extern void Rva004EF980AcceptBuddyRequest( Int profileID );

class BfmeAptScreenInGameChat : public AptInGameChat {};

class Glo00EF4988
{
public:
	void h005143D0();

private:
	unsigned char m_before250[0x250];
	unsigned int m_target;
	unsigned char m_between254And264[0x10];
	GameWindow *m_list;
	unsigned char m_between268And292[0x2a];
	unsigned char m_addDirty;
	unsigned char m_addEnabled;
	unsigned char m_removeDirty;
	unsigned char m_removeEnabled;
	unsigned char m_after296[0x0c];
};

// ?h005143D0@Glo00EF4988@@QAEXXZ
void Glo00EF4988::h005143D0()
{
	Rva005143D0Vector values;

	if (m_addDirty || m_addEnabled)
	{
		m_addDirty = false;
		m_addEnabled = false;
		Rva00579160TheManager->fire( m_target, "DisableAddButton", 0, 0, 0, 0, 0, 0 );
	}

	if (m_removeDirty || m_removeEnabled)
	{
		unsigned int target = m_target;
		m_removeDirty = false;
		m_removeEnabled = false;
		Rva00579160TheManager->fire( target, g_bfmeFmtC1064, 0, 0, 0, 0, 0, 0 );
	}

	GameWindow *list = m_list;
	if (((BfmeAptScreenInGameChat *)this)->rva00513BF0(
		list, &values, 7, true ) > 0)
	{
		int *it = values.begin();
		int *end = values.end();
		if (it != end)
		{
			do
			{
				Rva004EF980AcceptBuddyRequest( *it );
				++it;
			}
			while (it != end);
		}
	}
}
