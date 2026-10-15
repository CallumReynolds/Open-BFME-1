// ?update@Player@@QAEXXZ
// partial score=0.2269 date=2026-10-15
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// Retail 0x000D9A80, 551 bytes: Player::update. Sole caller is the matched
// PlayerList::update (0x000DF2D0) through ILT 0x0004771C. Zero Hour twin:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/RTS/Player.cpp.
// BFME adds the countdown table at +0x200 (the AsciiString-keyed hash_map
// whose begin() is 0x000D0A30 and whose xfer is 0x000DA250): an entry that
// counts down to zero copies its key's value from the float map at +0x1EC
// into the one at +0x1D8. The team walk iterates a copy of the prototype
// list, and the ZH power-sabotage and academy updates are gone.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>
#include <list>
#include "string_base.h"
#include "ascii_string.h"

namespace rts
{
	template<class T> struct hash;
	template<> struct hash<AsciiString>
	{
		size_t operator()(AsciiString ast) const
		{
			_STL::hash<const char *> tmp;
			return tmp((const char *)ast.str());
		}
	};
}
enum Rva000D6C60Mapped { Rva000D6C60MappedZero = 0 };
typedef _STL::hash_map<AsciiString, Rva000D6C60Mapped, rts::hash<AsciiString> > HashB;
typedef HashB::value_type HashBValue;
typedef _STL::hashtable<HashBValue, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<HashBValue>, _STL::equal_to<AsciiString>,
	_STL::allocator<HashBValue> > HashBTable;

// Out-of-line begin() of the +0x200 table (matched in Rva000DA250.cpp).
class Rva000D0A30
{
public:
	HashB::iterator method();
};

inline HashB::iterator rva000D9A80Begin(HashB *table)
{
	HashB::iterator first = reinterpret_cast<Rva000D0A30 *>(table)->method();
	return first;
}

typedef _STL::map<AsciiString, float> AsciiStringFloatMap;
template<> float &AsciiStringFloatMap::operator[](const AsciiString &);

class TeamPrototype;
typedef _STL::list<TeamPrototype *> PlayerTeamList;
template<> PlayerTeamList::list(const PlayerTeamList &);

class Team
{
public:
	void updateGenericScripts();
	Team *_bfme_nextInInstanceList();
};

// TeamPrototype+0x274 heads its team instance list (ZH iterate_TeamInstanceList).
struct Rva000D9A80PrototypeView
{
	unsigned char m_unreconstructed_000[0x274];
	Team *m_teamInstanceHead;
};

class AIPlayer
{
public:
	virtual ~AIPlayer();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void update();		// slot 5, vtable+0x14
};

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
	void appendBooleanArgument(bool arg);
};

class MessageStream
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual GameMessage *appendMessage(int type);	// slot 13, vtable+0x34
};

class Player;
class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_unreconstructed_000[0x0c];
	Player *m_local;
};

class GameLogic
{
public:
	unsigned int getFrame() { return m_frame; }
private:
	unsigned char m_unreconstructed_000[0x3c];
	unsigned int m_frame;
};

class GlobalData
{
public:
	unsigned char m_unreconstructed_000[0x126c];
	bool m_clientRetaliationModeEnabled;
};

extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
extern MessageStream *TheMessageStream;

enum { LOGICFRAMES_PER_SECOND = 5 };
enum { MSG_ENABLE_RETALIATION_MODE = 0x461 };

class Player
{
public:
	void update();
	int getPlayerIndex() const { return m_playerIndex; }
	bool isLogicalRetaliationModeEnabled() const { return m_logicalRetaliationModeEnabled; }
private:
	unsigned char m_unreconstructed_000[0x24];
	int m_playerIndex;
	unsigned char m_bfme028[0x1d8 - 0x28];
	AsciiStringFloatMap m_rva1D8Values;
	unsigned char m_bfme1D8Tail[0x14 - sizeof(AsciiStringFloatMap)];
	AsciiStringFloatMap m_rva1ECValues;
	unsigned char m_bfme1ECTail[0x14 - sizeof(AsciiStringFloatMap)];
	HashB m_rva200Countdowns;
	unsigned char m_bfme200Tail[0x20 - sizeof(HashB)];
	AIPlayer *m_ai;
	unsigned char m_bfme224[0x288 - 0x224];
	PlayerTeamList m_playerTeamPrototypes;
	unsigned char m_bfme288Tail[0x29e - 0x288 - sizeof(PlayerTeamList)];
	bool m_logicalRetaliationModeEnabled;
};

void Player::update()
{
	if (m_ai)
		m_ai->update();

	for (HashB::iterator it = rva000D9A80Begin(&m_rva200Countdowns); it != m_rva200Countdowns.end(); ++it)
	{
		if (it->second != 0)
		{
			if ((it->second = (Rva000D6C60Mapped)(it->second - 1)) == 0)
				m_rva1D8Values[it->first] = m_rva1ECValues[it->first];
		}
	}

	// Allow the teams this player owns to update themselves.
	PlayerTeamList prototypes(m_playerTeamPrototypes);
	for (PlayerTeamList::iterator pit = prototypes.begin(); pit != prototypes.end(); ++pit)
	{
		for (Team *team = ((Rva000D9A80PrototypeView *)*pit)->m_teamInstanceHead;
			team != 0; team = team->_bfme_nextInInstanceList())
		{
			if (!team)
				continue;
			team->updateGenericScripts();
		}
	}

	//Kris: August 25, 2003 (DAY OF CODE LOCK -- NO NEW FEATURES, REALLY!)
	if (ThePlayerList->getLocalPlayer() == this)
	{
		unsigned int now = TheGameLogic->getFrame();
		//Only check and post the message once every second so we don't spam the message stream to account for lag.
		if (now % LOGICFRAMES_PER_SECOND == 0)
		{
			if (TheWritableGlobalData->m_clientRetaliationModeEnabled != isLogicalRetaliationModeEnabled())
			{
				//Post a logical message that will switch the retaliation mode on or off.
				GameMessage *msg = TheMessageStream->appendMessage(MSG_ENABLE_RETALIATION_MODE);
				if (msg)
				{
					msg->appendIntegerArgument(getPlayerIndex());
					msg->appendBooleanArgument(TheWritableGlobalData->m_clientRetaliationModeEnabled);
				}
			}
		}
	}
}
