// ?rva0075BE60@Rva0075BE60@@UAEXIH@Z
// partial score=1.0 date=2026-10-15
// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Include
#include "Lib/Coord3D.h"

class Player;
struct GlobalData;
class PlayerList;
extern GlobalData *TheWritableGlobalData;
extern PlayerList *ThePlayerList;

struct Rva0075BE60Globals { char prefix[0xA75]; unsigned char enabled; };
struct Rva0075BE60Players { char prefix[0xC]; Player *local; };
struct Rva0075BE60Scale { char prefix[0xE8]; float scale; };

struct Rva0075BE60Position : Coord3D
{
    Rva0075BE60Position() {}
    Rva0075BE60Position(const Rva0075BE60Position &other) { x=other.x; y=other.y; z=other.z; }
    ~Rva0075BE60Position() {}
};

class Object
{
public:
    Player *getControllingPlayer() const;
    Rva0075BE60Position bfmeGetPosition421AE(Coord3D *normal);
};

class RadiusDecal;
class RadiusDecalTemplate
{
public:
    void createRadiusDecal(Rva0075BE60Position, unsigned, int, RadiusDecal &, float);
};

struct Rva0075BE60Drawable { char prefix[0xFC]; Object *object; };
class Rva0075BE60
{
public:
    virtual void rva0075BE60(unsigned selected, int color);
    char prefix[4];
    Rva0075BE60Drawable *drawable;
    int unknown;
    Rva0075BE60Scale *holder;
    char middle[0x178 - 0x14];
    char m_decal[16];
    RadiusDecalTemplate m_template;
};

// Open BFME 2: Code/GameEngine/Source/Common/Rva000B31CB.cpp.
void Rva0075BE60::rva0075BE60(unsigned selected, int color)
{
    if (!reinterpret_cast<Rva0075BE60Globals *>(TheWritableGlobalData)->enabled)
        return;
    Rva0075BE60Drawable *draw = drawable;
    Object *object = draw->object;
    if (!object)
        return;
    if (ThePlayerList) {
        Player *local = reinterpret_cast<Rva0075BE60Players *>(ThePlayerList)->local;
        if (object->getControllingPlayer() != local)
            return;
    }
    float scale = holder ? holder->scale : 0.0f;
    typedef Rva0075BE60Position (Object::*PositionCall)(Coord3D *);
    typedef void (RadiusDecalTemplate::*CreateCall)(Rva0075BE60Position, unsigned, int, RadiusDecal &, float);
    m_template.createRadiusDecal(object->bfmeGetPosition421AE(0), selected, color, *reinterpret_cast<RadiusDecal *>(m_decal), scale);
}
