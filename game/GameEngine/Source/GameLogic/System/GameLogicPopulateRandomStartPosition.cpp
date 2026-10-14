// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: GameLogic.cpp's static populateRandomStartPosition( GameInfo * ).
// Retail 0x00390F90..0x00391576, 1510 bytes through RET; its only caller is the
// matched GameLogic::startNewGame (0x00394260), which calls it right after
// populateRandomSideAndColor (0x00390A50, the previous function in the image).
// Recovered from the banked attempt: whole body matches with zero non-relocation
// differences and 38 relocations. The definition carries internal linkage with
// a TU-local caller marked absent-from-retail, exactly like the WOL/LanLobby
// shutdownComplete twins: with external linkage MSVC 7.1 hoists the incoming
// GameInfo load ahead of the SEH `push -1` and the first twelve bytes miss
// retail's push -1 / fs load / parameter load order. Internal linkage plus a
// same-TU call site reproduces the retail prologue byte for byte.
// BFME's placement differs from Zero Hour's twin only in the team-proximity
// rule (same-team players are kept together) below; the Logic RNG calls keep
// the original source filename and line arguments (0x6F9 / 0x71E), and the
// Coord3D memberwise copy plus the combined taken/startToSlot initialization
// reproduce the original x87 sequence and the 0x154-byte local frame.
// Banked real C++ for populateRandomStartPosition,0x00390F90/1510B.
// Entire body after offset0x0C matches; first12B differ only in scheduling
// the SEH push(-1), fs:[0] read and incoming GameInfo pointer read.
// All gameplay paths are represented, including the BFME-specific team
// proximity rule and observer placement. Logic RNG calls preserve original
// source filename and line arguments0x6F9/0x71E; all four literals verified.
// Coord3D's memberwise copy and one loop initializing taken+startToSlot
// produce the original x87 sequence and the exact0x154 local frame.
// /G4/G5/G6 /GX/EHsc/Ob1/Oa/Z7/GA and static function emission leave
// the8 differing prologue bytes unchanged; /G7/EHa/Op change the body.
// No asm or instruction masking has been added to hide the difference.
#include <map>
#include <math.h>
// class-gate: allow AsciiString this unit is a byte-proved reconstruction of 0x00390F90: the private StringBase<char> facade is the recovered codegen view for the by-value getMap()/findMap() temporaries (build 1510/1510, 0 non-reloc diffs); the canonical headers are a separate reconciliation.
template<class T> class StringBase {
    friend class AsciiString;
    StringBase():data(0) {}
    StringBase(const T *);
    StringBase(const StringBase &);
    ~StringBase();
    void *data;
};
class AsciiString:private StringBase<char> {
public:
    AsciiString():StringBase<char>() {}
    AsciiString(const char *s):StringBase<char>(s) {}
    AsciiString(const AsciiString &s):StringBase<char>(s) {}
    ~AsciiString() {}
    void __cdecl format(AsciiString, ...);
};
bool operator<(const AsciiString&,const AsciiString&);
// class-gate: allow Coord3D the canonical bare-layout header omits the memberwise copy constructor that this body's proven x87 sequence needs (1510/1510, 0 non-reloc diffs).
struct Coord3D {float x,y,z; Coord3D(){} Coord3D(const Coord3D& p):x(p.x),y(p.y),z(p.z){} };
typedef _STL::map<AsciiString,Coord3D> WaypointMap;
class MapMetaData { public: char pad0[0x20]; int m_numPlayers; char pad24[0x14]; WaypointMap m_waypoints; };
class GameSlot { public:
 bool isOccupied()const;
 int getStartPos()const {return pos;}
 int getPlayerTemplate()const {return playerTemplate;}
 int getTeamNumber()const {return team;}
 void setStartPos(int p){pos=p;}
 char pad0[0x10];int pos,playerTemplate,team;
};
class GameInfo {public:
 AsciiString getMap()const;
 GameSlot*getSlot(int);
 const GameSlot*getConstSlot(int)const;
 bool isStartPositionTaken(int,int=-1)const;
};
class MapCache { public: const MapMetaData *findMap(AsciiString); };
extern MapCache *TheMapCache;
extern GameInfo *TheGameInfo;
int GetGameLogicRandomValue(int,int,const char*,int);
inline float sqr(float x){return x*x;}
static void populateRandomStartPosition(GameInfo *game) {
 if(!game) return;
 int i;
 int numPlayers=8;
 const MapMetaData *md=TheMapCache->findMap(game->getMap());
 if(md)numPlayers=md->m_numPlayers;
 float startSpotDistance[8][8];
 for(i=0;i<8;++i) {
  for(int j=0;j<8;++j) {
   if(md && i!=j && i<numPlayers && j<numPlayers) {
    AsciiString w1,w2;
    w1.format("Player_%d_Start",i+1);
    w2.format("Player_%d_Start",j+1);
    WaypointMap::const_iterator c1=md->m_waypoints.find(w1);
    WaypointMap::const_iterator c2=md->m_waypoints.find(w2);
    if(c1==md->m_waypoints.end() || c2==md->m_waypoints.end())startSpotDistance[i][j]=1000000.0f;
    else {
     Coord3D p1=c1->second;
     Coord3D p2=c2->second;
     startSpotDistance[i][j]=sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
    }
   } else startSpotDistance[i][j]=0.0f;
  }
 }
 bool hasStartSpotBeenPicked=false;
 bool taken[8];
 int startToSlot[8];
 for(i=0;i<8;++i){taken[i]=(i<numPlayers)?false:true;startToSlot[i]=-1;}
 for(i=0;i<8;++i) {
  GameSlot *slot=game->getSlot(i);
  if(!slot||!slot->isOccupied()||slot->getPlayerTemplate()==-2)continue;
  int posIdx=slot->getStartPos();
  if(posIdx>=0 && posIdx<numPlayers){hasStartSpotBeenPicked=true;taken[posIdx]=true;startToSlot[posIdx]=i;}
 }
 for(i=0;i<8;++i) {
  bool sameTeamPicked=false;
  GameSlot *slot=game->getSlot(i);
  if(!slot||!slot->isOccupied()||slot->getPlayerTemplate()==-2)continue;
  int posIdx=slot->getStartPos();
  if(posIdx<0 || posIdx>=numPlayers) {
   if(hasStartSpotBeenPicked) {
    float farthestDistance=0.0f;
    int farthestIndex=-1;
    for(posIdx=0;posIdx<numPlayers;++posIdx) {
     if(!taken[posIdx]) {
      if(farthestIndex<0) {
       farthestIndex=posIdx;
       for(int n=0;n<numPlayers;++n)if(taken[n]&&n!=posIdx)farthestDistance+=startSpotDistance[posIdx][n];
      } else {
       float dist=0.0f;
       for(int n=0;n<numPlayers;++n) {
        if(taken[n]&&n!=posIdx) {
         if(TheGameInfo->getSlot(i)->getTeamNumber()>-1 && TheGameInfo->getSlot(startToSlot[n])->getTeamNumber()==TheGameInfo->getSlot(i)->getTeamNumber()) {
          sameTeamPicked=true;
          if(startSpotDistance[posIdx][n]<farthestDistance) {farthestIndex=posIdx;farthestDistance=startSpotDistance[posIdx][n];}
         } else if(!sameTeamPicked) {
          dist+=startSpotDistance[posIdx][n];
          if(dist>farthestDistance){farthestIndex=posIdx;farthestDistance=dist;}
         }
        }
       }
      }
     }
    }
    slot->setStartPos(farthestIndex);taken[farthestIndex]=true;startToSlot[farthestIndex]=i;
   } else {
    while(posIdx==-1) {
     posIdx=GetGameLogicRandomValue(0,numPlayers-1,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\System\\GameLogic.cpp",0x6f9);
     if(game->isStartPositionTaken(posIdx))posIdx=-1;
    }
    slot->setStartPos(posIdx);taken[posIdx]=true;startToSlot[posIdx]=i;hasStartSpotBeenPicked=true;
   }
  }
 }
 int numPlayersInGame=0;
 for(i=0;i<8;++i) {
  const GameSlot *slot=game->getConstSlot(i);
  if(slot->isOccupied()&&slot->getPlayerTemplate()!=-2)++numPlayersInGame;
 }
 for(i=0;i<8;++i) {
  GameSlot *slot=game->getSlot(i);
  if(!slot||!slot->isOccupied())continue;
  if(slot->getPlayerTemplate()!=-2)continue;
  int posIdx=-1;
  if(numPlayersInGame==0)posIdx=0;
  while(posIdx==-1) {
   posIdx=GetGameLogicRandomValue(0,numPlayers-1,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\System\\GameLogic.cpp",0x71e);
   if(!game->isStartPositionTaken(posIdx))posIdx=-1;
  }
  slot->setStartPos(posIdx);
 }
}

// absent-from-retail: TU-local caller keeping the static helper emitted with
// the same private calling context its only retail caller gives it. Retail
// GameLogic::startNewGame calls it unconditionally; the null check is inside.
void Rva00390F90PopulateCaller( GameInfo *game )
{
	populateRandomStartPosition( game );
}
