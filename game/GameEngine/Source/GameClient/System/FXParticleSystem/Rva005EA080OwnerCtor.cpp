// ??0Rva005EA080@@QAE@PAVOwnerY005E7940@@@Z
// Second constructor of class Rva005EA080 (RVA 0x006009B0, 440 bytes), named
// by the matched HostY005E7940::create caller in Q4NewInlineCtorAdjusted.cpp.
// IDENTITY: the final vptr stores (+0x70..+0x7d) are 0x01112A88 / 0x0111270C /
// 0x011126F8, the same three constants the landed forwarding ctor
// ??0Rva005EA080@@QAE@I@Z (0x005EA080) stamps, and dir32_addresses.csv records
// those addresses only as the ??_7Rva005EA080@@6B* vftables.  Retail has no
// COMDAT folding, so each vftable has one owner.  Earlier stores: 0x0110F9E8
// (T4A2_0110F9E8) at +4 and 0x01112A98 (T4B005EA0D0) at +8, the bases.
// The chain Rva005E9AB0 / Rva005E9AE0 below mirrors T4ForwardingCtorChainL2/L3
// but with implicit constructors, because retail inlines them here.
// Shape: handle from owner->makeHandle(), then the 13-dword value block
// T4B005EA0D0 filled from the owner's random values, the first three lanes
// biased by the particle system's +0x184 field.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include "../../../Common/System/game_client_random_variable.h"

class BfmeHandleERU;

// The helper's independently matched ABI uses this 0xA0-byte host view only
// for the intrusive handle list.  The constructor below reads the same host
// through the native ParticleSystem view for its random values and floats.
struct Rva005FB4D0Host
{
	char prefix[0x98];
	BfmeHandleERU *head;
	BfmeHandleERU *tail;
};

class BfmeHandleERU
{
public:
	BfmeHandleERU(Rva005FB4D0Host *host) : m_host(host)
	{
		if ( host )
		{
			m_previous = host->tail;
			m_next = 0;
			host->tail = this;
			if ( m_previous )
				m_previous->m_next = this;
			else
				m_host->head = this;
		}
		else
		{
			m_next = 0;
			m_previous = 0;
		}
	}
	~BfmeHandleERU() throw();

	Rva005FB4D0Host *m_host;
	BfmeHandleERU *m_previous;
	BfmeHandleERU *m_next;
};

class Rva005FB4D0Owner
{
public:
	BfmeHandleERU makeHandle() throw();

	int prefix;
	Rva005FB4D0Host *m_host;
};

class ParticleSystem
{
public:
	virtual ~ParticleSystem();

	char m_pad04[0x17c];
	float m_field180;
	float m_field184;
	float m_field188;
};

ParticleSystem *Make00001B18();

class OwnerY005E7940 : public Rva005FB4D0Owner
{
public:
	char m_pad08[0x18];
	GameClientRandomVariable m_random20;
	GameClientRandomVariable m_random2c;
	GameClientRandomVariable m_random38;
	GameClientRandomVariable m_random44;
	GameClientRandomVariable m_random50;
	GameClientRandomVariable m_random5c;
	GameClientRandomVariable m_random68;
	GameClientRandomVariable m_random74;
	GameClientRandomVariable m_random80;
	GameClientRandomVariable m_random8c;
	GameClientRandomVariable m_random98;
	GameClientRandomVariable m_randomA4;
	unsigned int m_fieldB0;
};

class T4P0_Rva005E9AE0
{
public:
	virtual void s0();
};

class T4A2_0110F9E8
{
public:
	virtual void s0();
};

class Rva005E9AE0 : public T4P0_Rva005E9AE0, public T4A2_0110F9E8
{
public:
	Rva005E9AE0() {}
	virtual ~Rva005E9AE0();
};

class Rva005E9AB0 : public Rva005E9AE0
{
};

// The thirteen-dword value block whose copy constructor is 0x005EA0D0.
class T4B005EA0D0
{
public:
	T4B005EA0D0() throw()
		: m_scale0( 1.0f ), m_scale1( 1.0f ), m_scale2( 1.0f ),
		  m_value0( 0.0f ), m_value1( 0.0f ), m_value2( 0.0f ),
		  m_value3( 0.0f ), m_value4( 0.0f ), m_value5( 0.0f ),
		  m_value6( 0.0f ), m_value7( 0.0f ), m_value8( 0.0f ),
		  m_trailingValue( 1 )
	{
	}
	virtual ~T4B005EA0D0();

protected:
	float m_scale0, m_scale1, m_scale2;
	float m_value0, m_value1, m_value2, m_value3, m_value4;
	float m_value5, m_value6, m_value7, m_value8;
	unsigned int m_trailingValue;
};

class Rva005EA080 : public Rva005E9AB0, public T4B005EA0D0
{
public:
	Rva005EA080( OwnerY005E7940 *owner );
};

Rva005EA080::Rva005EA080( OwnerY005E7940 *owner )
{
	BfmeHandleERU handle = owner->makeHandle();
	m_scale0 = owner->m_random20.getValue();
	ParticleSystem *scaleSystem = (ParticleSystem *)handle.m_host;
	if ( scaleSystem == 0 )
		scaleSystem = Make00001B18();
	float scale = scaleSystem->m_field188;
	m_scale1 = owner->m_random2c.getValue() * scale;
	m_scale2 = owner->m_random38.getValue();
	m_value0 = owner->m_random44.getValue();
	m_value1 = owner->m_random50.getValue();
	m_value2 = owner->m_random5c.getValue();
	m_value3 = owner->m_random68.getValue();
	m_value4 = owner->m_random74.getValue();
	m_value5 = owner->m_random80.getValue();
	ParticleSystem *biasSystem0 = !handle.m_host
		? Make00001B18() : (ParticleSystem *)handle.m_host;
	m_scale0 += biasSystem0->m_field184;
	ParticleSystem *biasSystem1 = !handle.m_host
		? Make00001B18() : (ParticleSystem *)handle.m_host;
	m_scale1 += biasSystem1->m_field184;
	ParticleSystem *biasSystem2 = !handle.m_host
		? Make00001B18() : (ParticleSystem *)handle.m_host;
	m_scale2 += biasSystem2->m_field184;
	m_value6 = owner->m_random8c.getValue();
	m_value7 = owner->m_random98.getValue();
	m_value8 = owner->m_randomA4.getValue();
	m_trailingValue = owner->m_fieldB0;
}
