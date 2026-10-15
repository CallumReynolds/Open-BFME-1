// cl: /O2 /G5 /DNDEBUG /MD /EHsc
struct Rva00804150ProtoMangleRef;
void Rva008054A0(Rva00804150ProtoMangleRef *);
int Rva00806040(Rva00804150ProtoMangleRef *,unsigned *,int *);
int Rva008060B0(Rva00804150ProtoMangleRef *,int,int);
struct Rva007E9B70Obj { virtual void v0(); virtual void v1(); };
Rva007E9B70Obj *Rva007E9B70Get();
class Gen_007e9b70 {public:virtual void v0();virtual void v1();virtual unsigned int m();};
class BfmeE1036 {public:void bfmeGo1036E();};
typedef void (__cdecl *Rva007F8840Callback)(void *,void *);
class Rva00803080 {public:virtual void slot0(unsigned int opaque);};
class Rva007F8840Owner : public Rva00803080 {
public:
 virtual void slot0(unsigned int opaque);
 Rva00804150ProtoMangleRef *ref04;int state08;
 unsigned callback0c[2];unsigned address14;int port18,time1c;unsigned char report20;
 Rva007F8840Callback callback24;void *context28;
};
// Open BFME 2: Code/GameEngine/Source/Common/SmallGaps/Rva00664EC0Method.cpp
// ?slot0@Rva007F8840Owner@@UAEXI@Z
void Rva007F8840Owner::slot0(unsigned int)
{
 if(ref04 && callback24) {
  Rva008054A0(ref04);
  int outPort=0;unsigned outAddr=0;
  int rc=Rva00806040(ref04,&outAddr,&outPort);
  address14=outAddr;port18=outPort;
  switch(state08) {
   case 1:
    if(rc>0) {
     callback24(callback0c,context28);
     if(report20) {
      int latency=((Gen_007e9b70 *)Rva007E9B70Get())->m()-time1c;
      Rva008060B0(ref04,0,latency);state08=2;
     } else state08=3;
    } else if(rc<0) {
     callback24(callback0c,context28);
     if(report20) {
      int latency=((Gen_007e9b70 *)Rva007E9B70Get())->m()-time1c;
      Rva008060B0(ref04,1,latency);state08=2;
     } else state08=3;
    }
    break;
   case 2:if(rc!=0)state08=3;break;
   case 3:((BfmeE1036 *)((char *)this-4))->bfmeGo1036E();state08=0;break;
  }
 }
}
