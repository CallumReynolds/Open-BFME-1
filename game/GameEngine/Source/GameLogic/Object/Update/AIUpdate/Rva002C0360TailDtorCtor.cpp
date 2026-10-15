// ??0Rva002C0360TailDtor@@QAE@PAXVAsciiString@@@Z
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class Object;
class State;

typedef unsigned int StateID;

struct StateConditionInfo
{
	void *test;
	StateID toStateID;
	void *userData;
};

class StateMachine
{
protected:
	// retail's StateMachine destructor is protected: ??1StateMachine@@MAE@XZ
	virtual ~StateMachine();

	void defineState( StateID id, State *state, StateID successID,
		StateID failureID, const StateConditionInfo *conditions );
};

class AIStateMachine : public StateMachine
{
public:
	AIStateMachine( Object *owner, AsciiString name );

protected:
	// retail's destructor is protected: ??1AIStateMachine@@MAE@XZ (ILT 0x00020D9C)
	virtual ~AIStateMachine();
};

// Rva000A19E0StateBase is the ledger's address-derived name for
// State::State(StateMachine*, AsciiString) at retail 0x000A19E0 (thunk
// 0x000035B2), as in AIAttackSwoopThenIdleStateMachineCtor.cpp.
class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase( void *machine, AsciiString name );

	virtual void stateBaseAnchor();
};

// byte-exact reconstructions, verbatim from GiantBirdStateConstructors.cpp
// (matched out of line); inlined here at the new call sites.
class GiantBirdNormalFlightState : public Rva000A19E0StateBase
{
public:
	GiantBirdNormalFlightState( void *machine, bool initiallyActive );

private:
	char m_gap04[ 0x20 ];
	bool m_initiallyActive;
};

GiantBirdNormalFlightState::GiantBirdNormalFlightState( void *machine, bool initiallyActive )
	: Rva000A19E0StateBase( machine, AsciiString( "GiantBirdNormalFlightState" ) )
{
	m_initiallyActive = initiallyActive;
}

class AIGiantBirdSwoopState : public Rva000A19E0StateBase
{
public:
	AIGiantBirdSwoopState( void *machine, int targetID, bool enabled );

private:
	char m_gap04[ 0x20 ];
	int m_targetID;
	char m_gap28[ 0x0C ];
	bool m_enabled;
	char m_gap35[ 3 ];
	int m_counter;
	float m_scale;
};

AIGiantBirdSwoopState::AIGiantBirdSwoopState( void *machine, int targetID, bool enabled )
	: Rva000A19E0StateBase( machine, AsciiString( "AIGiantBirdSwoopState" ) )
{
	m_targetID = targetID;
	m_enabled = enabled;
	m_counter = 0;
	m_scale = 1.0f;
}

class AIGiantBirdAttackState : public Rva000A19E0StateBase
{
public:
	AIGiantBirdAttackState( void *machine, int mode );

private:
	char m_gap04[ 0x20 ];
	int m_mode;
};

AIGiantBirdAttackState::AIGiantBirdAttackState( void *machine, int mode )
	: Rva000A19E0StateBase( machine, AsciiString( "AIGiantBirdAttackState" ) )
{
	m_mode = mode;
}

class AIGiantBirdFollowThruState : public Rva000A19E0StateBase
{
public:
	AIGiantBirdFollowThruState( void *machine, bool enabled );

private:
	char m_gap04[ 0x20 ];
	bool m_enabled;
	char m_gap25[ 3 ];
	int m_counter;
};

AIGiantBirdFollowThruState::AIGiantBirdFollowThruState( void *machine, bool enabled )
	: Rva000A19E0StateBase( machine, AsciiString( "AIGiantBirdFollowThruState" ) )
{
	m_enabled = enabled;
	m_counter = 0;
}

class GiantBirdFollowWaypointPathState : public Rva000A19E0StateBase
{
public:
	GiantBirdFollowWaypointPathState( void *machine, bool enabled );

private:
	char m_gap04[ 0x20 ];
	int m_counter;
	bool m_enabled;
};

GiantBirdFollowWaypointPathState::GiantBirdFollowWaypointPathState( void *machine, bool enabled )
	: Rva000A19E0StateBase( machine, AsciiString( "GiantBirdFollowWaypointPathState" ) )
{
	m_enabled = enabled;
	m_counter = 0;
}

// AIFollowPathState's ctor stays out of line (retail 0x0017FC60 via ILT
// 0x000250BD).  The derived vtable 0x010C7778 names GiantBirdFollowPathState;
// its recorded address-derived name is ??_7Rva002BDB30State@@6B@, after the
// out-of-line copy of this ctor at 0x002BDB30 (StateSelfNamingCtorsWithFields.cpp).
class AIFollowPathState
{
public:
	AIFollowPathState( StateMachine *machine, AsciiString name );

	virtual void stateBaseAnchor();

private:
	char m_gap04[ 0x58 ];
};

class Rva002BDB30State : public AIFollowPathState
{
public:
	Rva002BDB30State( void *machine )
		: AIFollowPathState( (StateMachine *)machine,
			AsciiString( "GiantBirdFollowPathState" ) ),
		  m_field5c( 0 )
	{
	}

private:
	int m_field5c;
};

// Declared only: retail keeps this ctor out of line at 0x002BF6D0 (ILT
// 0x0001560E, matched in GiantBirdAttackMoveToStateCtor.cpp).
class GiantBirdAttackMoveToState
{
public:
	GiantBirdAttackMoveToState( void *machine );

	virtual void stateBaseAnchor();

private:
	char m_gap04[ 0x30 ];
};

// The machine's vtable 0x010C7AD8 is recorded as ??_7Rva002C0360TailDtor@@6B@,
// after its destructor at 0x002C0360 (VptrTailJumpDestructors.cpp); the
// factory at 0x002C1260 declares the same class as Rva002C1260StateMachine.
class Rva002C0360TailDtor : public AIStateMachine
{
public:
	Rva002C0360TailDtor( void *owner, AsciiString name );
	virtual ~Rva002C0360TailDtor();
};

// retail RVA 0x002BFB00, 1671B. Identity: the only caller is the matched
// factory Rva002C1260Factory::create (0x002C1260), which allocates this
// machine with the literal "GiantBirdAIStateMachine" and calls it through
// ILT 0x00022F5C. The body builds on AIStateMachine (ILT 0x0002981B ->
// 0x00185A20), installs vtable 0x010C7AD8 and defines seventeen GiantBird
// states; its FuncInfo 0x00E0301C has 19 unwind states (name, base, then
// one scalar-delete cleanup 0x00C138E0..0x00C13990 per new-expression).
Rva002C0360TailDtor::Rva002C0360TailDtor( void *owner, AsciiString name )
	: AIStateMachine( (Object *)owner, name )
{
	defineState( 1001, (State *)new GiantBirdNormalFlightState( this, false ), 0, 0, 0 );
	defineState( 1002, (State *)new GiantBirdNormalFlightState( this, true ), 0, 0, 0 );

	defineState( 1010, (State *)new AIGiantBirdSwoopState( this, 1, false ), 1012, 0, 0 );
	defineState( 1011, (State *)new AIGiantBirdSwoopState( this, 1, true ), 1012, 0, 0 );
	defineState( 1012, (State *)new AIGiantBirdAttackState( this, 1 ), 1013, 1013, 0 );
	defineState( 1013, (State *)new AIGiantBirdFollowThruState( this, false ), 0, 1010, 0 );

	defineState( 1007, (State *)new AIGiantBirdSwoopState( this, 1, false ), 1008, 0, 0 );
	defineState( 1008, (State *)new AIGiantBirdAttackState( this, 1 ), 1009, 1009, 0 );
	defineState( 1009, (State *)new AIGiantBirdFollowThruState( this, true ), 1007, 1007, 0 );

	defineState( 1003, (State *)new AIGiantBirdSwoopState( this, 0, false ), 1005, 0, 0 );
	defineState( 1004, (State *)new AIGiantBirdSwoopState( this, 0, true ), 1012, 0, 0 );
	defineState( 1005, (State *)new AIGiantBirdAttackState( this, 0 ), 1006, 1006, 0 );
	defineState( 1006, (State *)new AIGiantBirdFollowThruState( this, false ), 0, 0, 0 );

	defineState( 1014, (State *)new Rva002BDB30State( this ), 0, 0, 0 );
	defineState( 1015, (State *)new GiantBirdFollowWaypointPathState( this, false ), 0, 0, 0 );
	defineState( 1016, (State *)new GiantBirdFollowWaypointPathState( this, true ), 0, 0, 0 );
	defineState( 1019, (State *)new GiantBirdAttackMoveToState( this ), 0, 0, 0 );
}
