// ?rva00205AC0@ShareExperienceBehavior@@UAEXM@Z
// partial score=0.9365 date=2026-10-15
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00205AC0 (630 B, ret 4 at +0x273).  The ledger calls this
// ??1ShareExperienceBehavior, but it is not a destructor: the constructor at
// 0x00205740 stamps the one-slot interface table VA 0x010A5FC0 at +0x20, its
// slot zero routes through ILT 0x000477E9 here, and the body reads module data
// and object through this-0x1C/-0x18, takes one float (ret 4, reused as an x87
// slot), iterates objects in data->radius through five linked temporary
// filters and hands each accepting ExperienceTracker a scaled share.  The
// method's own spelling is unproved, so the name keeps the address.
// Residue (48 B): retail loads pos.x/pos.z before the five filter vtable resets
// and keeps other in EDI / tracker in ESI; this build copies pos interleaved
// with the resets and swaps the two registers.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
#define NULL 0

struct Coord3D { Real x, y, z; };

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
	void *_vptr;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	UnsignedInt getKindOfWord2() const { return m_kindof[2]; }
private:
	unsigned char m_pad[0xc0];
	UnsignedInt m_kindof[3];
};

enum KindOfType { KINDOF_59 = 0x59 };
enum { KINDOF_WORD2_BIT25_MASK = 0x02000000 };

template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable) return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	const T *operator*() const
	{
		if (!m_overridable) return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	operator const T *() const { return operator*(); }

	const T *m_overridable;
};

class Player;
class ExperienceTracker
{
public:
	Bool isAcceptingExperiencePoints() const;
	void addExperiencePoints(Real experienceGain, Bool a, Bool b, Bool c, Bool d);
};

class Thing
{
public:
	Bool isKindOf(KindOfType t) const;
	const ThingTemplate *getTemplate() const { return m_template; }
private:
	void *_vptr;
	OVERRIDE<ThingTemplate> m_template;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	const Coord3D *getPosition() const { return &m_position; }
	UnsignedInt getStatus98() const { return m_status98; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
private:
	unsigned char m_pad08[0x30];
	Coord3D m_position;
	unsigned char m_pad44[0x54];
	UnsignedInt m_status98;
	unsigned char m_pad9c[0x174];
	ExperienceTracker *m_experienceTracker;
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
class Rva002DC6D0Filter;
class Rva00265150RJFilter : public PartitionFilter
{
public:
	Rva00265150RJFilter(const Rva002DC6D0Filter *filter, Player *p, Bool match)
		: m_subobject(filter), m_player(p), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual Bool allow(Object *);
	const Rva002DC6D0Filter *m_subobject;
	Player *m_player;
	Bool m_match;
};
class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(Object *object) : m_object(object) {}
	virtual ~PartitionFilterSameMapStatus() {}
	virtual Bool allow(Object *);
	Object *m_object;
};
class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *p, Int flags, Bool match)
		: m_object(p), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();
	Object *m_object;
	Int m_flags;
	Bool m_match;
};
class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};
class Rva00260180SelfFilter : public PartitionFilter
{
public:
	Rva00260180SelfFilter(Object *p) : m_object(p) {}
	virtual ~Rva00260180SelfFilter() {}
	virtual Bool allow(Object *);
	Object *m_object;
};

struct SimpleObjectIteratorClump
{
	Object *m_object;
	Real m_distance;
};
struct SimpleObjectIterator
{
	_STL::vector<SimpleObjectIteratorClump> m_entries;
	SimpleObjectIteratorClump *m_cursor;
	Int m_refCount;
};
struct BfmeWideResult
{
	SimpleObjectIterator *m_mpo;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult()
	{
		if (--m_mpo->m_refCount == 0)
			delete m_mpo;
	}
	Object *next()
	{
		if (m_mpo->m_cursor == m_mpo->m_entries.end())
			return NULL;
		return (m_mpo->m_cursor++)->m_object;
	}
};

enum IterOrderType { ITER_FASTEST = 0 };
class PartitionManager
{
public:
	BfmeWideResult iterate(const Coord3D *, Real, IterOrderType, PartitionFilter *, Bool);
};
extern PartitionManager *ThePartitionManager;

class GameLogic
{
public:
	Bool getFlag96() const { return m_flag96; }
private:
	unsigned char m_pad[0x96];
	Bool m_flag96;
};
extern GameLogic *TheGameLogic;

struct Rva00205A20Pos { Real x, y, z; };
struct Rva00205A20Thing;
struct Rva00205A20Owner
{
	Real method(const Rva00205A20Pos *, const Rva00205A20Thing *) const;
};

class ShareExperienceBehaviorModuleData
{
public:
	void *_vptr;
	UnsignedInt m_04;
	Real m_radius;
	UnsignedInt m_0c;
	Real m_scale;
	Rva002DC6D0Filter *m_filter14[1];
};

class ShareExperienceBehaviorFront
{
public:
	virtual ~ShareExperienceBehaviorFront();
	const ShareExperienceBehaviorModuleData *getData() const { return m_data; }
	Object *getObject() const { return m_object; }
private:
	const ShareExperienceBehaviorModuleData *m_data;
	Object *m_object;
	unsigned char m_pad[0x14];
};

class ShareExperienceBehaviorInterface
{
public:
	virtual void rva00205AC0(Real experience) = 0;
};

class ShareExperienceBehavior : public ShareExperienceBehaviorFront, public ShareExperienceBehaviorInterface
{
public:
	virtual void rva00205AC0(Real experience);
};

void ShareExperienceBehavior::rva00205AC0(Real experience)
{
	const ShareExperienceBehaviorModuleData *data = getData();
	Object *object = getObject();
	if (!(data->m_scale > 0.0f) || (object->getStatus98() & 1) != 0)
		return;

	Bool isKind = object->isKindOf(KINDOF_59);
	BfmeWideResult iter = ThePartitionManager->iterate(object->getPosition(), data->m_radius, ITER_FASTEST,
		Rva00260180SelfFilter(object)
			.link(&Rva0025ED50RootFilter())
			->link(&PartitionFilterRelationship(object, 4, false))
			->link(&PartitionFilterSameMapStatus(object))
			->link(&Rva00265150RJFilter((const Rva002DC6D0Filter *)&data->m_filter14, object->getControllingPlayer(), true)),
		false);
	Coord3D pos = *object->getPosition();

	Object *other;
	while ((other = iter.next()) != NULL)
	{
		if (isKind && !TheGameLogic->getFlag96()
			&& (other->getTemplate()->getKindOfWord2() & KINDOF_WORD2_BIT25_MASK) != 0)
			continue;
		ExperienceTracker *tracker = other->getExperienceTracker();
		if (tracker == NULL || !tracker->isAcceptingExperiencePoints())
			continue;
		experience = reinterpret_cast<const Rva00205A20Owner *>(this)->method(
				(const Rva00205A20Pos *)&pos, (const Rva00205A20Thing *)other) * (experience * data->m_scale);
		if (experience > 0.0f)
			tracker->addExperiencePoints(experience, true, true, true, false);
	}
}
