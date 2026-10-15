// ?update@GiantBirdGuardIdleState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9517 date=2026-10-15
// cl: /DNDEBUG /MD /EHsc
// GiantBirdGuardIdleState::update retail 0x002C0FE0 (290B): ZH AIGuardIdleState::update with the crate check via machine setState(0x138C) and the team-to-guard fallback. Arm-order lever: an up-front `if (target == NULL && team == NULL) return sleep;` makes the team arm the fallthrough (was 95 diffs). Residue 14 diffs at +0xEB: retail loads x/y/z of the object position into ebx/esi/edx before storing x/y; ours interleaves load/store.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int TeamID;
typedef bool Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AIUpdateInterface
{
public:
	Int getCrateID() const { return *(const Int *)((const char *)this + 0x218); }
};

class Object
{
public:
	const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); }
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((const char *)this + 0x204); }
};

class Team
{
public:
	void getEstimateTeamPosition_000EDCD0(Coord3D *position) const;
};

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
	UnsignedInt getFrame() const { return *(const UnsignedInt *)((const char *)this + 0x3c); }
};

class AIData
{
public:
	unsigned char m_fields[0x40];
	UnsignedInt m_guardEnemyScanRate;
};

class AI
{
public:
	unsigned char m_fields[0x14];
	AIData *m_data;
	AIData *getAiData() { return m_data; }
};

extern GameLogic *TheGameLogic;
extern TeamFactory *TheTeamFactory;
extern AI *TheAI;

class AIGuardMachine
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
	virtual void setState(int state);

	Object *getOwner() const { return m_owner; }
	Object *findTargetToGuardByID() { return TheGameLogic->findObjectByID(m_targetToGuard); }
	Team *findTeamToGuardByID() { return TheTeamFactory->findTeamByID(m_teamToGuard); }

protected:
	unsigned char m_unmodelled04[0x0C];
	Object *m_owner;
	unsigned char m_unmodelled14[0x30];
	Int m_targetToGuard;
	TeamID m_teamToGuard;
};

class GiantBirdGuardMachine : public AIGuardMachine
{
public:
	Bool lookForInnerTarget(void);
};

class GiantBirdGuardIdleState
{
public:
	virtual StateReturnType update();

private:
	unsigned char m_stateFields04[0x18];
	GiantBirdGuardMachine *m_machine;
	unsigned char m_unreconstructed20[4];
	UnsignedInt m_nextEnemyScanTime;
	Coord3D m_guardeePos;
};

#define PATHFIND_CELL_SIZE_F 10.0f

#define NULL 0
static inline Bool getGuardeePos(Object *target, Team *team, Coord3D *pos)
{
	if (target) { *pos = *target->getPosition(); return true; }
	if (team) { team->getEstimateTeamPosition_000EDCD0(pos); return true; }
	return false;
}
StateReturnType GiantBirdGuardIdleState::update()
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (now < m_nextEnemyScanTime)
		return (StateReturnType)(m_nextEnemyScanTime - now);

	m_nextEnemyScanTime = now + TheAI->getAiData()->m_guardEnemyScanRate;

	GiantBirdGuardMachine *machine = m_machine;
	if (machine->getOwner()->getAI()->getCrateID() != 0)
	{
		machine->setState(0x138c);
		return (StateReturnType)(m_nextEnemyScanTime - now);
	}

	if (machine->lookForInnerTarget())
		return STATE_SUCCESS;

	Object *targetToGuard = machine->findTargetToGuardByID();
	Team *teamToGuard = machine->findTeamToGuardByID();
	Coord3D pos;
	if (targetToGuard == NULL && teamToGuard == NULL) return (StateReturnType)(m_nextEnemyScanTime - now);
	if (targetToGuard) pos = *targetToGuard->getPosition();
	else teamToGuard->getEstimateTeamPosition_000EDCD0(&pos);

	Real delta = m_guardeePos.x - pos.x;
	if (delta * delta > 4 * PATHFIND_CELL_SIZE_F * PATHFIND_CELL_SIZE_F)
	{
		m_guardeePos = pos;
		return STATE_FAILURE;
	}
	delta = m_guardeePos.y - pos.y;
	if (delta * delta > 4 * PATHFIND_CELL_SIZE_F * PATHFIND_CELL_SIZE_F)
	{
		m_guardeePos = pos;
		return STATE_FAILURE;
	}
	return (StateReturnType)(m_nextEnemyScanTime - now);
}
