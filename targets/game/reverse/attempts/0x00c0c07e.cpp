// ?d_00c0c07e@@YAXXZ
// partial score=0.0 date=2026-10-16
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ for the retail SlowDeathBehaviorModuleData layout.

#include <string.h>

// MSVC 7.1 otherwise adds a null check and misses the retail exception-state
// byte before the RadiusDecalTemplate placement constructor.
__forceinline void *operator new(unsigned int, void *address)
{
	__assume(address != 0);
	return address;
}


class __declspec(novtable) ModuleData
{
public:
	ModuleData() {}
	virtual void moduleDataAnchor();
	~ModuleData();

	unsigned int m_field04;
};

class InstantDeathDieMuxData
{
public:
	InstantDeathDieMuxData();

private:
	unsigned char m_storage[0x2c];
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	~RadiusDecalTemplate();

private:
	unsigned char m_storage[0x30];
};

class TailGuard
{
public:
	// This destructor emits the retail +0x124 store and keeps MSVC's delayed
	// exception-frame restore after that store.
	__forceinline ~TailGuard()
	{
		__asm {
			mov [esi+124h], ebx
		}
	}
};

class StructureCollapseOCLVector
{
public:
	StructureCollapseOCLVector();
	~StructureCollapseOCLVector();

private:
	unsigned char m_storage[0xc];
};

class StructureCollapseFXVector
{
public:
	StructureCollapseFXVector();
	~StructureCollapseFXVector();

private:
	unsigned char m_storage[0xc];
};

class Gen_uwm_0000513c
{
public:
	Gen_uwm_0000513c();
	~Gen_uwm_0000513c();

private:
	unsigned char m_storage[0xc];
};

class InstantDeathBehaviorModuleDataAllocator
{
public:
	InstantDeathBehaviorModuleDataAllocator();
	~InstantDeathBehaviorModuleDataAllocator();

private:
	unsigned char m_storage[0xc];
};

class SlowDeathZero128
{
public:
	SlowDeathZero128()
	{ memset(m_value, 0, sizeof(m_value)); }

	float m_value[10];
};

class SlowDeathZero150
{
public:
	SlowDeathZero150() { memset(m_value, 0, sizeof(m_value)); }

	float m_value[3];
};

// Twelve-byte member whose destructor is the ILT at 0x00026AB2 (retail unwind state 5).
class Rva00026AB2Vec12
{
public:
	Rva00026AB2Vec12() : m_begin(0), m_end(0), m_capacity(0) {}
	~Rva00026AB2Vec12();

private:
	unsigned int m_begin;
	unsigned int m_end;
	unsigned int m_capacity;
};

class SlowDeathBehaviorModuleData : public ModuleData
{
public:
	SlowDeathBehaviorModuleData();

	InstantDeathDieMuxData m_dieMuxData;
	volatile float m_sinkRate;
	volatile int m_probabilityModifier;
	volatile float m_modifierBonusPerOverkillPercent;
	volatile unsigned int m_sinkDelay;
	volatile unsigned int m_sinkDelayVariance;
	volatile float m_destructionAltitude;
	volatile unsigned int m_destructionDelay;
	volatile unsigned int m_destructionDelayVariance;
	volatile unsigned int m_field54;
	StructureCollapseOCLVector m_fx[4];
	StructureCollapseFXVector m_ocls[4];
	Gen_uwm_0000513c m_weapons[4];
	InstantDeathBehaviorModuleDataAllocator m_extraVectors[4];
	volatile float m_flingForce;
	volatile float m_flingForceVariance;
	volatile float m_flingPitch;
	volatile float m_flingPitchVariance;
	SlowDeathZero128 m_zero128;
	SlowDeathZero150 m_zero150;
	volatile unsigned char m_maskOfLoadedEffects;
	unsigned char m_pad15d[3];
	Rva00026AB2Vec12 m_vector160;
	unsigned char m_radius[0x30];
	volatile unsigned int m_field19c;
	volatile unsigned int m_field1a0;
	volatile unsigned char m_flags[3];
};

__forceinline void writeSlowFloat(volatile float *address, float value)
{
	*address = value;
}

SlowDeathBehaviorModuleData::SlowDeathBehaviorModuleData()
{
	register SlowDeathBehaviorModuleData *self = this;
	new (self->m_radius) RadiusDecalTemplate;
	writeSlowFloat(&self->m_sinkRate, 0.0f);
	self->m_probabilityModifier = 10;
	writeSlowFloat(&self->m_modifierBonusPerOverkillPercent, 0.0f);
	self->m_sinkDelay = 0;
	self->m_sinkDelayVariance = 0;
	self->m_destructionDelay = 0;
	self->m_destructionDelayVariance = 0;
	writeSlowFloat(&self->m_destructionAltitude, -10.0f);
	self->m_field54 = 0;
	self->m_flags[0] = 0;
	writeSlowFloat(&self->m_flingForce, 0.0f);
	writeSlowFloat(&self->m_flingForceVariance, 0.0f);
	writeSlowFloat(&self->m_flingPitch, 0.0f);
	{
		TailGuard guard;
	}
	self->m_flags[1] = 0;
	self->m_flags[2] = 0;
	self->m_maskOfLoadedEffects = 0;
	self->m_field19c = 6;
	self->m_field1a0 = 0xfacade00;
}
