// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class UpdateModuleInterface;

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
	virtual UpdateModuleInterface *getUpdate() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	// ??1UpdateModule@@MAE@XZ: protected, as the retail thunk-table order proves (ilt_oracle).
	virtual ~UpdateModule() {}
public:
	// ?getUpdate@UpdateModule@@UAEPAVUpdateModuleInterface@@XZ (0x001B2D20): entered
	// through the BehaviorModuleInterface subobject at +0xC, returns the +0x10 interface.
	virtual UpdateModuleInterface *getUpdate() { return this; }

private:
	unsigned int m_14;
	int m_18;
	int m_1c;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

class AutoAbilityBehavior : public UpdateModule
{
public:
	virtual ~AutoAbilityBehavior();

private:
	AsciiString m_20;
};

// ??1AutoAbilityBehavior@@UAE@XZ
AutoAbilityBehavior::~AutoAbilityBehavior()
{
}
