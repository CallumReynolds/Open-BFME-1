// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ot

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void __cdecl log(int level, const char *format, ...);
};

Rva007EB810Diag *Rva007EB810Get(void);


struct BfmeThingVFD;
void __stdcall bfmeGoVFD(BfmeThingVFD *task);

class Rva007F7CF0Handle {public:
// ??0Rva007F7CF0Handle@@QAE@XZ absent-from-retail
 Rva007F7CF0Handle() {} Rva007F7CF0Handle(const Rva007F7CF0Handle &); int m_id;};

struct BfmeThingVFD
{
	virtual void v0();
	virtual Rva007F7CF0Handle *getA(Rva007F7CF0Handle *out);
	virtual Rva007F7CF0Handle *getB(Rva007F7CF0Handle *out);
	int m_04;
	int m_state;
};

class Rva007F7CF0M14
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07();
	virtual void t08(); virtual void t09(); virtual void t0a();
	virtual void t0b(BfmeThingVFD *task, int resource);
};

class Rva007F7CF0Sibling
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16();
	virtual void s17(int a, int b);
	int m_04;
	// ?finish@Rva007F7CF0Sibling@@QAEXPAUBfmeThingVFD@@@Z absent-from-retail
	void finish(BfmeThingVFD *task)
	{
		union { void (__stdcall *entry)(BfmeThingVFD *); void (Rva007F7CF0Sibling::*method)(BfmeThingVFD *); } call;
		call.entry = bfmeGoVFD;
		(this->*call.method)(task);
	}
};

class Rva007F7CF0Iface
{
public:
	virtual void rva007F7CF0(int resource, BfmeThingVFD *task);
	char m_pad04[0x14 - 0x04];
	Rva007F7CF0M14 *m_14;
};

class Rva007F7CF0Owner : public Rva007F7CF0Sibling, public Rva007F7CF0Iface
{
public:
	virtual void rva007F7CF0(int resource, BfmeThingVFD *task);
};

// Open BFME 2: Code/GameEngine/Source/GameNetwork/Rva00664370Probe.cpp
// ?rva007F7CF0@Rva007F7CF0Owner@@UAEXHPAUBfmeThingVFD@@@Z
void Rva007F7CF0Owner::rva007F7CF0(int resource, BfmeThingVFD *task)
{
	if (task && task->m_state == 4)
	{
		if (resource)
		{
			Rva007EB810Get()->log(0, "probe err %d\n", resource);
			Rva007F7CF0Handle a, b;
			Rva007F7CF0Sibling *self = this;
			Rva007F7CF0Handle *ap = task->getA(&a);
			Rva007F7CF0Handle *bp = task->getB(&b);
			self->s17(bp->m_id, ap->m_id);
			task->m_state = 0;
			m_14->t0b(task, resource);
			self->finish(task);
		}
		else
		{
			task->m_state = 5;
			m_14->t0b(task, 0);
		}
	}
}
