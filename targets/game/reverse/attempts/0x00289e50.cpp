// ?update@BroadcastStealthUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9926 date=2026-10-15
// ?update@BroadcastStealthUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9926 date=2026-10-15 (6 bytes: ESI/EDI swap in the final iterator release)
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Retail RVA 0x00289E50, 806 bytes (0x326): the complete object ends at the
// `ret` at +0x325 and 0x0028A176 is int3 padding before the 16-aligned start
// of the next body -- the ledger's 803 stops three bytes short, mid-`add esp`.
//
// IDENTITY: retail table 0x010BCB3C, installed by the named constructor
// 0x00289880 at owner+0x10, slot 0.  Slot 1 of the same table is the matched
// ?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0N@@@XZ, and the
// Zero Hour UpdateModuleInterface declares `update()` first and
// `getDisabledTypesToProcess()` second
// (inputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include/
// GameLogic/Module/UpdateModule.h), so slot 0 is
// `virtual UpdateSleepTime update() = 0`.  The body is not a destructor: it
// builds a partition filter chain, walks the refcounted result, and calls
// Object::setStatus.  The lift's ??1BroadcastStealthUpdate@@UAE@XZ is refuted.
//
// The interface sits at owner+0x10, so module data and object are this-0x0C
// and this-0x08, and the two lists are this+0x18 / this+0x1C -- the layout the
// landed constructor and BannerCarrierUpdate_update.cpp already carry.
//
// Filters are temporaries linked inside the query call, as in the matched
// StealthDetectorUpdate::update (0x002AB690); retail destroys them right after
// bfmeForwardWideC (EH state 5).  The find runs before the self test, and the
// null/remove branches step the iterator back (`--it`) as retail does.
// Residue: retail keeps the return value in ESI and the released payload in
// EDI; this source swaps them (+0x2B6, +0x2D7, +0x302, +0x312).  Return,
// destructor, accessor, declaration-order and rotation_sweep spellings did
// not move it.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <list>
#include <algorithm>
#include <bitset>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// The retail mask type is ?$BitFlags@$0FG@@ -- 86 bits, three words -- which is
// what ObjectStatusBits.h proves for Object::m_status at +0x90.  KINDOF is
// ?$BitFlags@$0MA@@ -- 192 bits, six words -- the mask 0x000C3DD0 copies.
template <int NUMBITS> class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags() { }

	BitFlags(_dummy_kInit, Int index)
	{
		m_bits._Unchecked_set(index);
	}

	void set(Int index)
	{
		m_bits._Unchecked_set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

struct VptrZeroBlock24
{
	unsigned int m_dwords[6];
};

class Object
{
public:
	// ObjectStatusBits.h's spelling, so the decorated name binds the matched
	// body at 0x001C7370.
	__declspec(noinline) void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);

	// The status mask at +0x90 is the one ObjectStatusBits.h proves; the
	// position block at +0x38 and the +0x190 flag byte are the offsets this
	// body reads and writes.
	unsigned char m_unmodelled_00[0x90];
	UnsignedInt m_status[3];				// +0x90
};

// Object members this body reaches: the position block at +0x38, the status
// mask at +0x90 and the +0x190 flag byte.
#define OBJECT_FLAG_190(o)	(*(unsigned char *)((char *)(o) + 0x190))
#define OBJECT_POSITION(o)	(*(Coord3D *)((char *)(o) + 0x38))

class ModuleData
{
public:
	unsigned char m_unmodelled_00[0x08];
	VptrZeroBlock24 m_kindOf;				// +0x08
	Real m_radius;							// +0x20
	Int m_sleepTime;						// +0x24
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

// Retail vtable 0x01085DD0.
class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

// Retail vtable 0x01083B80.
class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

// Retail vtable 0x01085DC0.
class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_obj(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};


extern const BitFlags<192> KINDOFMASK_NONE;

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const BitFlags<192> &, const BitFlags<192> &);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	BitFlags<192> m_yes;
	BitFlags<192> m_no;
};

struct Rva0025ED50Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0025ED50ResultData
{
	std::vector<Rva0025ED50Entry> entries;
	Rva0025ED50Entry *current;
	Int references;
};

struct BfmeWideResult
{
	Rva0025ED50ResultData *value;

	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);

	Object *next()
	{
		if (value->current == value->entries.end())
			return 0;
		return (value->current++)->object;
	}

	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

extern BfmeWideForwardC *ThePartitionManager;

class ObjectModule
{
public:
	virtual void s00();

protected:
	const ModuleData *m_moduleData;			// +0x04
	Object *m_object;						// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void s00();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	virtual Int getDisabledTypesToProcess() const = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class BroadcastStealthUpdate : public BehaviorModule,
				public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();

private:
	unsigned char m_unmodelled_14[0x28 - 0x14];
	_STL::list<Object *> m_broadcastObjects;		// +0x28
	Int m_broadcastObjectCount;				// +0x2C
};

// ?update@BroadcastStealthUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime BroadcastStealthUpdate::update()
{
	const ModuleData *data = m_moduleData;
	Object *self = m_object;

	BfmeWideResult iter = ThePartitionManager->bfmeForwardWideC(
		(int)&OBJECT_POSITION(self), *(const int *)&data->m_radius, 0,
		(int)PartitionFilterRelationship(self, 4, false).link(
			Rva0025ED50RootFilter().link(
			Rva0025ED50ObjectFilter(self).link(
			&PartitionFilterAcceptByKindOf(*(const BitFlags<192> *)&data->m_kindOf, KINDOFMASK_NONE)))),
		0);

	while (Object *other = iter.next())
	{
		_STL::list<Object *>::iterator found = _STL::find(
			m_broadcastObjects.begin(), m_broadcastObjects.end(), other);
		if (other == self)
			continue;
		if (found != m_broadcastObjects.end())
		{
			OBJECT_FLAG_190(*found) = 1;
		}
		else
		{
			OBJECT_FLAG_190(other) = 1;
			m_broadcastObjects.push_back(other);
			m_broadcastObjectCount = m_broadcastObjects.size();
		}
	}

	for (_STL::list<Object *>::iterator it = m_broadcastObjects.begin();
		it != m_broadcastObjects.end(); ++it)
	{
		Object *target = *it;
		if (target == 0)
		{
			m_broadcastObjects.erase(it);
			m_broadcastObjectCount = m_broadcastObjects.size();
			--it;
			continue;
		}
		if (!OBJECT_FLAG_190(target))
		{
			m_broadcastObjects.remove(target);
			m_broadcastObjectCount = m_broadcastObjects.size();
			--it;
			target->setStatus(MAKE_OBJECT_STATUS_MASK(18), false);
			target->setStatus(MAKE_OBJECT_STATUS_MASK(15), false);
		}
		else
		{
			if (!(target->m_status[0] & 0x40000))
				target->setStatus(MAKE_OBJECT_STATUS_MASK(18), true);
			if (!(target->m_status[0] & 0x8000))
				target->setStatus(MAKE_OBJECT_STATUS_MASK(15), true);
		}
		OBJECT_FLAG_190(target) = 0;
	}

	return (UpdateSleepTime)m_moduleData->m_sleepTime;
}
