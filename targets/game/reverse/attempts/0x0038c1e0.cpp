// ?d_0038c1e0@@YAXXZ
// partial score=0.1419 date=2026-10-15
// cl: /DNDEBUG /MD /EHsc
//
// 0x0038C1E0 (2892 B) -- BFME port of Zero Hour unitTimings()
// (ZH reference GameLogic.cpp:3074, called from the per-frame update at :3578).
// The ECX-passed state object is the global at VA 0x012F08A0:
//   * sole caller GameLogic::update 0x0038DA10, +0x188 mov ecx,0x12f08a0,
//     +0x18D call 0x407E32 (thunk rva 0x7E32: jmp 0x78C1E0, ECX preserved);
//   * matched caller source GameLogic.cpp:6499;
//   * symbol pin ?g_aiTargetDispatchSuppressed@@3_NA + matched initializer
//     @Rva00385FB0Initialize@4 zeroes exactly this layout.
// Layout + callee inventory: targets/game/reverse/identity_evidence/
//   0038c1e0-wave20-state-layout.md
//
// STATUS: foundations draft, not byte-exact. Implemented: frame-rate fild math,
// settleFrames/timeFrames countdowns, QPC/QPF pair, TheDisplay vt+0x14C draw
// counter, the 0..4 mode machine (LOGIC->ALL->NO_PARTICLES->NO_SPAWN->report),
// tail MSG_CLEAR_GAME_DATA 0x1D post + state resets + HideControlBar(true) +
// TheTacticalView vt+0x54 lookAt(800,800,0). CONDESED vs retail: the
// side/unit-type classification chain (17x ThingTemplate::isKindOf, AsciiString
// side list), the object teardown/spawn loops, and the 0x10EB45C CSV format
// call are stubbed; see the layout doc sections 3-5 for the pinned evidence.

struct Coord3D { float x, y, z; };

enum KindOfType { KINDOF_DUMMY = 0 };

class ThingTemplate
{
public:
	bool isKindOf( KindOfType kind ) const;
};

class Thing
{
public:
	const ThingTemplate *getTemplate( void ) const;
	void setOrientation( float angle );
	void setPosition( const Coord3D *pos );
};

class Object;

class GameLogic
{
public:
	void destroyObject( Object *obj );
};

class GameLogicPtr { public: GameLogic *p; };

class AsciiString
{
public:
	AsciiString();
	AsciiString( const AsciiString &other );
	AsciiString &operator=( const char *s );
	void format( AsciiString fmt, ... );
};

void HideControlBar( bool show );

// 0x00382AA0: fclose-style release; retail is called with ECX == the state
// object (its [+0x18] comma-log FILE*), so the member ABI is "this == FILE*".
struct Rva00382AA0 { void release( void ); };

struct Rva0038C1E0State
{
	bool enabled;                  // +0x00
	unsigned char pad01[ 3 ];
	const void *sideName;          // +0x04  AsciiString (StringBase<char>*)
	const void *sideName2;         // +0x08  AsciiString
	bool gotUnit;                  // +0x0C
	unsigned char pad0D[ 3 ];
	const ThingTemplate *curThing; // +0x10
	bool startTiming;              // +0x14
	unsigned char pad15[ 3 ];
	void *commaLog;                // +0x18  FILE*
	int settleFrames;              // +0x1C
	int timeFrames;                // +0x20
	int unitTypes;                 // +0x24
	bool veryFirstTime;            // +0x28
	unsigned char pad29[ 7 ];
	long long startTime64;         // +0x30
	long long endTime64;           // +0x38
	long long freq64;              // +0x40
	int drawCallTotal;             // +0x48
	int mode;                      // +0x4C  0=LOGIC 1=NO_SPAWN 2=REPORT 3=NO_PARTICLES 4=ALL
	double timeAll;                // +0x50
	double timeNoPart;             // +0x58
	double unused60;               // +0x60
	double timeNoSpawn;            // +0x68
	double timeLogic;              // +0x70
	double timeToUpdate;           // +0x78
	double unused80;               // +0x80
	float drawCallAll;             // +0x88
	float drawCallNoPart;          // +0x8C
	float drawCallNoSpawn;         // +0x90
	float drawCallLogic;           // +0x94
};

extern void *TheGameEngine;      // 0x012ED524, fps limit int at +0x34
extern void *TheDisplay;         // 0x012F1270
extern void *TheTacticalView;    // 0x012F1600
extern void *TheMessageStream;   // 0x012ED5EC
extern void *TheParticleSystemManager;   // 0x012F64BC

static const double bfmeOneMillion = 1.0e6;   // 0x010EB500

void d_0038c1e0( void )
{
	Rva0038C1E0State *self;
	__asm { mov self, ecx }

	// IAT slots 0x1358EB4 / 0x1358EB8 (KERNEL32 QPC/QPF). Reached as absolute
	// indirect calls; retail encodes `call dword ptr [slot]`. (Direct
	// per-site casts measured worse: ours=774 diffs=671 shape=0.217 vs
	// hoisted pointers ours=775 diffs=665 shape=0.228.)
	typedef long (__stdcall *BfmeQpcFn)( long long * );
	BfmeQpcFn qpc = *(BfmeQpcFn *)0x01358EB4;
	BfmeQpcFn qpf = *(BfmeQpcFn *)0x01358EB8;

	// fild [TheGameEngine+0x34]; twice -> frameRate*2 (retail +0x29..+0x37).
	float frameRateX2;
	__asm {
		mov eax, dword ptr [TheGameEngine]
		fild dword ptr [eax+34h]
		fadd st, st(0)
		fstp dword ptr [frameRateX2]
	}

	if ( !self->startTiming )
		return;

	if ( self->settleFrames > 0 )
	{
		int settle = self->settleFrames - 1;
		self->settleFrames = settle;
		if ( settle > 0 )
			return;

		qpc( &self->startTime64 );
		qpf( &self->freq64 );
		self->timeFrames = 2;
		self->drawCallTotal = 0;
		return;
	}

	if ( self->timeFrames > 0 )
	{
		int drawCalls;
		__asm {
			mov ecx, dword ptr [TheDisplay]
			mov eax, dword ptr [ecx]
			call dword ptr [eax+14Ch]
			mov drawCalls, eax
		}
		self->drawCallTotal = drawCalls;

		if ( --self->timeFrames > 0 )
			return;

		qpc( &self->endTime64 );

		double timeToUpdate = (double)( self->endTime64 - self->startTime64 );
		timeToUpdate /= (double)self->freq64;
		timeToUpdate *= bfmeOneMillion;
		timeToUpdate /= (double)frameRateX2 * 100.0;

		// Retail materializes (400,300,0) once before the mode dispatch and
		// reuses it for the LOGIC and NO_PARTICLES lookAt calls.
		Coord3D pos400;
		pos400.x = 400.0f;
		pos400.y = 300.0f;
		pos400.z = 0.0f;

		int mode = self->mode;
		if ( mode == 0 )
		{
			// LOGIC: timings for the logic-only pass; look at (400,300,0).
			self->timeToUpdate = timeToUpdate;
			self->mode = 4;
			self->settleFrames = 2;
			self->drawCallLogic = (float)self->drawCallTotal * 0.01f;
			float savedZoom;
			__asm {
				mov ecx, dword ptr [TheTacticalView]
				mov eax, dword ptr [ecx]
				call dword ptr [eax+128h]
				fstp dword ptr [savedZoom]
			}
			// 0x12B44BC: saved look-at distance restored by the NO_PARTICLES pass.
			*(float *)0x012B44BC = savedZoom;
			__asm {
				mov ecx, dword ptr [TheTacticalView]
				mov edx, dword ptr [ecx]
				lea eax, [pos400]
				push eax
				call dword ptr [edx+54h]
			}
			return;
		}
		if ( mode == 4 )
		{
			// ALL: full-house timing; then switch the view for the deltas.
			self->timeAll = timeToUpdate;
			self->drawCallAll = (float)self->drawCallTotal * 0.01f;
			__asm {
				mov ecx, dword ptr [TheDisplay]
				mov edx, dword ptr [ecx]
				call dword ptr [edx+150h]
			}
			*(int *)0x012F0A98 /= 100;
			*(int *)0x012F0A9C /= 100;
			*(int *)0x012F0A94 /= 100;
			self->mode = 3;
			self->settleFrames = 2;
			__asm {
				mov ecx, dword ptr [TheTacticalView]
				mov edx, dword ptr [ecx]
				push 0
				call dword ptr [edx+1Ch]
				mov ecx, dword ptr [TheTacticalView]
				mov eax, dword ptr [ecx]
				push 442f0000h
				call dword ptr [eax+12Ch]
				mov ecx, dword ptr [TheTacticalView]
				mov edx, dword ptr [ecx]
				push 400ccccdh
				call dword ptr [edx+124h]
			}
			return;
		}
		if ( mode == 3 )
		{
			// NO_PARTICLES: reset particle manager (count at +0x84 > 1).
			self->timeNoPart = timeToUpdate;
			self->mode = 1;
			self->settleFrames = 2;
			void *psm = *(void **)0x012F64BC;
			if ( *(int *)((char *)psm + 0x84) > 1 )
			{
				__asm {
					mov ecx, dword ptr [TheParticleSystemManager]
					mov eax, dword ptr [ecx]
					call dword ptr [eax+10h]
				}
			}
			__asm {
				mov ecx, dword ptr [TheTacticalView]
				mov edx, dword ptr [ecx]
				push 3f800000h
				call dword ptr [edx+124h]
				mov ecx, dword ptr [TheTacticalView]
				mov edx, dword ptr [012b44bch]
				mov eax, dword ptr [ecx]
				push edx
				call dword ptr [eax+12Ch]
				mov ecx, dword ptr [TheTacticalView]
				mov eax, dword ptr [ecx]
				lea edx, [pos400]
				push edx
				call dword ptr [eax+54h]
			}
			return;
		}
		if ( mode == 1 )
		{
			// NO_SPAWN: keep the timing for the report pass.
			self->timeNoSpawn = timeToUpdate;
			self->drawCallNoSpawn = (float)self->drawCallTotal * 0.01f;
			self->mode = 2;
			return;
		}

		// mode == 2: report/reset pass (retail +0x335..+0xB4B, condensed here:
		// the side/unit classification + CSV write at 0x10EB45C are omitted;
		// the reset/message tail below is byte-faithful shape).
		if ( self->curThing != 0 && self->commaLog != 0 )
		{
			// CSV line through AsciiString::format (varargs, 0x10EB45C fmt).
		}
		self->gotUnit = true;

		self->startTiming = false;
		((Rva00382AA0 *)self)->release();          // fclose(commaLog)
		__asm {
			mov ecx, dword ptr [TheMessageStream]
			mov edx, dword ptr [ecx]
			push 1Dh
			call dword ptr [edx+34h]
		}
		if ( self->gotUnit )
		{
			self->settleFrames = 4;
			if ( self->veryFirstTime )
			{
				HideControlBar( true );
				self->settleFrames = self->settleFrames * 100;
			}
		}
		Coord3D endPos;
		endPos.x = 800.0f;
		endPos.y = 800.0f;
		endPos.z = 0.0f;
		__asm {
			mov ecx, dword ptr [TheTacticalView]
			mov edx, dword ptr [ecx]
			lea eax, [endPos]
			push eax
			call dword ptr [edx+54h]
		}
		self->mode = 0;
	}
}
