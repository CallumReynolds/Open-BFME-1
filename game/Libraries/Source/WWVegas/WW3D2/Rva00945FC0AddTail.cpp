// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

#include "../WWLib/multilist.h"

class Rva00945FC0List : public GenericMultiListClass
{
public:
    // ?addTail@Rva00945FC0List@@QAE_NPAVMultiListObjectClass@@@Z absent-from-retail
    bool addTail(MultiListObjectClass *obj) { return Internal_Add_Tail(obj, true); }
};

class Rva00945FC0
{
public:
    void addTail(MultiListObjectClass *obj);
private:
    char m_pad00[0x1C];
    Rva00945FC0List m_list;
};

// ?addTail@Rva00945FC0@@QAEXPAVMultiListObjectClass@@@Z
// Open BFME 2: Code/GameEngine/Source/Common/GapBodiesGE43.cpp
void Rva00945FC0::addTail(MultiListObjectClass *obj)
{
    if (obj)
        m_list.addTail(obj);
}
