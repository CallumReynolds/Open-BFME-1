// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/GameLogic
//
// Open-BFME: retail 0x000C4080 (113 bytes), reached through ILT 0x00012B57.
// The matched InGameUI::canSelectedObjectsDoAction calls it as
// BFMEActionManager::rva000C4080 for command case 16, and
// BFMEActionManager::rva000C6820 (BFMEActionManagerRva000C6820.cpp) refuses
// whenever it answers true. Both objects are resolved through the relation
// resolver at 0x001CB0C0 (ILT 0x00035995); identical results answer false;
// otherwise the resolved side that has a partner when the other has none
// (or else the target's) supplies its relation interface (0x001BFE20,
// ILT 0x0000D3B9), whose slot 0x6C is asked about the opposite object.
// The method name is address-derived.
//
// Shape notes measured against retail: every failing test returns false on
// its own line and the one success is the final `return true', which is what
// puts retail's shared false epilogue ahead of the true one.
#include "command_source_type.h"

struct RvaC4390First;

class RvaC4390Second
{
public:
	RvaC4390First *resolve( int allowLookup );
};

class Rva000C4080Relation
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual bool slot6C( const void *other );
};

class Object
{
public:
	void *unidentified_001BFE20() const;
};

class BFMEActionManager
{
public:
	bool rva000C4080( const Object *obj, const Object *target, CommandSourceType commandSource );
};

bool BFMEActionManager::rva000C4080( const Object *obj, const Object *target, CommandSourceType commandSource )
{
	if( obj == 0 || target == 0 )
		return false;
	RvaC4390First *objFirst = ( (RvaC4390Second *)obj )->resolve( 0 );
	RvaC4390First *targetFirst = ( (RvaC4390Second *)target )->resolve( 0 );
	if( objFirst == targetFirst )
		return false;
	if( objFirst != 0 && targetFirst == 0 )
	{
		Rva000C4080Relation *relation = (Rva000C4080Relation *)( (const Object *)objFirst )->unidentified_001BFE20();
		if( relation == 0 )
			return false;
		if( !relation->slot6C( target ) )
			return false;
	}
	else
	{
		Rva000C4080Relation *relation = (Rva000C4080Relation *)( (const Object *)targetFirst )->unidentified_001BFE20();
		if( relation == 0 )
			return false;
		if( !relation->slot6C( obj ) )
			return false;
	}
	return true;
}
