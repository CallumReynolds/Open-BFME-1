// ?render@Rva0090FEE0Renderer@@QAEXI@Z
// partial score=0.8348 date=2026-10-16
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#define Matrix4x4 Matrix4
#include "sharebuf.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "ww3d.h"
#include "texture.h"
#include "vertmaterial.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
extern bool Rva012D6D75;
extern DX8IndexBufferClass *Rva01341214IndexBuffer;
extern SortingIndexBufferClass *Rva01341218SortingIndexBuffer;
class Rva0090FEE0Renderer {
public:
 void render(unsigned);
 ShareBufferClass<Vector3> *Positions;
 ShareBufferClass<Vector4> *Colors;
 ShareBufferClass<Vector3> *Normals;
 ShareBufferClass<Vector2> *UVs;
 int Count;
 TextureBaseClass *Texture;
 ShaderClass Shader;
 Vector4 DefaultColor;
};
class BoxDynamicVBAccessClass
{
	const FVFInfoClass & FVFInfo;
	unsigned Type;
	unsigned FVF;
	unsigned Start;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	class BoxVertexBufferClass * VertexBuffer;

public:
	BoxDynamicVBAccessClass(unsigned type,unsigned fvf,unsigned short vertex_count,unsigned buffer);
	~BoxDynamicVBAccessClass();

	const FVFInfoClass & FVF_Info() const { return FVFInfo; }

	class WriteLockClass
	{
		BoxDynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;

	public:
		WriteLockClass(BoxDynamicVBAccessClass *vb_access);
		~WriteLockClass();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

extern void BoxSetTexture(unsigned stage,TextureBaseClass *& texture);

struct Rva0093B340Center
{
 float X, Y, Z;
 Rva0093B340Center() : X(0.0f), Y(0.0f), Z(0.0f) {}
};
#include "sortingrenderer.h"
static __forceinline void InsertPointTriangles(unsigned short a, unsigned short b, unsigned short c, unsigned short d)
{
 Rva0093B340Center center;
 SortingRendererClass::Insert_Triangles(reinterpret_cast<const SphereClass&>(center),a,b,c,d);
}

// Clamp each float component with the runtime CMOV feature flag.
static __forceinline void ClampPointColor(Vector4 &color)
{
	if (!CPUDetectClass::Has_CMOV_Instruction())
	{
		color.X = color.X <= 0.0f ? 0.0f : (color.X > 1.0f ? 1.0f : color.X);
		color.Y = color.Y <= 0.0f ? 0.0f : (color.Y > 1.0f ? 1.0f : color.Y);
		color.Z = color.Z <= 0.0f ? 0.0f : (color.Z > 1.0f ? 1.0f : color.Z);
		color.W = color.W <= 0.0f ? 0.0f : (color.W > 1.0f ? 1.0f : color.W);
		return;
	}

	__asm
	{
		mov	esi,dword ptr color

		mov edx,0x3f800000

		mov edi,dword ptr[esi]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi],edi

		mov edi,dword ptr[esi+4]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi+4],edi

		mov edi,dword ptr[esi+8]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi+8],edi

		mov edi,dword ptr[esi+12]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi+12],edi
	}
}

static __forceinline unsigned ConvertPointColor(Vector4 color){
 ClampPointColor(color);
 return DX8Wrapper::Convert_Color(reinterpret_cast<const Vector3&>(color),color[3]);
}

static __forceinline void Rva0090FEE0NextUV(Vector2 *destination,Vector2 &value)
{
 *destination=value;
 if(value.X!=0){value.X=0;value.Y=1-value.Y;}else value.X=1;
}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void Rva0090FEE0Renderer::render(unsigned)
{
 if(!Count)return;
 Shader.Set_Primary_Gradient((ShaderClass::PriGradientType)6);
 Shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
 Matrix4 world,view;
 DX8Wrapper::Get_Transform(D3DTS_WORLD,world);
 DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
 Matrix4 identity(true);
 DX8Wrapper::Set_Transform(D3DTS_WORLD,identity);
 DX8Wrapper::Set_Transform(D3DTS_VIEW,identity);
 VertexMaterialClass *material=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 DX8Wrapper::Set_Material(material);
 material->Release_Ref();
 DX8Wrapper::Set_Shader(Shader);
 BoxSetTexture(0,Texture);
 const bool sort=(Shader.Get_Dst_Blend_Func()!=ShaderClass::DSTBLEND_ZERO) && (Shader.Get_Alpha_Test()==ShaderClass::ALPHATEST_DISABLE) && WW3D::Is_Sorting_Enabled() && Rva012D6D75;
 DX8Wrapper::Set_Index_Buffer(sort?static_cast<IndexBufferClass*>(Rva01341218SortingIndexBuffer):static_cast<IndexBufferClass*>(Rva01341214IndexBuffer),0);
 unsigned defaultColor=ConvertPointColor(Vector4(DefaultColor.X,DefaultColor.Y,DefaultColor.Z,DefaultColor.W));
 int current=0;
 while(current<Count){
  int delta=MIN(Count-current,512);
  BoxDynamicVBAccessClass vertices(sort?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8,5,delta*4,0);
  {
   BoxDynamicVBAccessClass::WriteLockClass lock(&vertices);
   const FVFInfoClass &fvf=vertices.FVF_Info();
   volatile unsigned stride=fvf.Get_FVF_Size();
   unsigned locationOffset=fvf.Get_Location_Offset();
   unsigned char *vb=(unsigned char*)lock.Get_Formatted_Vertex_Array();
   int count=delta*4;
   Vector3 *source=Positions->Get_Array()+current*4;
   unsigned char *position=vb+locationOffset;
   for(int i=count;i;--i){*(Vector3*)position=*source++;position+=stride;}
   if(Colors){
    Vector4 *source=Colors->Get_Array()+current*4;
    unsigned char *color=vb+fvf.Get_Diffuse_Offset();
    for(int i=count;i;--i){*(unsigned*)color=ConvertPointColor(*source);++source;color+=stride;}
   }else{
    unsigned char *color=vb+fvf.Get_Diffuse_Offset();
    for(int i=count;i;--i){*(unsigned*)color=defaultColor;color+=stride;}
   }
   if(Normals){
    Vector3 *source=Normals->Get_Array()+current*4;
    unsigned char *normal=vb+fvf.Get_Normal_Offset();
    for(int i=count;i;--i){*(Vector3*)normal=*source++;normal+=stride;}
   }else{
    unsigned char *normal=vb+fvf.Get_Normal_Offset();
    for(int i=count;i;--i){unsigned step=stride;*(Vector3*)normal=Vector3(0,0,1);normal+=step;}
   }
   unsigned char *uv=vb+fvf.Get_Tex_Offset(0);
   if(UVs){
    Vector2 *source=UVs->Get_Array()+current*4;
    for(int i=count;i;--i){unsigned x=((unsigned*)source)[0];unsigned step=stride;((unsigned*)uv)[0]=x;((unsigned*)uv)[1]=((unsigned*)source)[1];++source;uv+=step;}
   }else{
    Vector2 value(0,0);
    for(int i=count;i;--i){Rva0090FEE0NextUV((Vector2*)uv,value);uv+=stride;}
   }
  }
  DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass*>(&vertices));
  if(sort)InsertPointTriangles(0,delta*2,0,delta*6);
  else DX8Wrapper::Draw_Triangles(0,delta*2,0,delta*6);
  current+=delta;
 }
 DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
 DX8Wrapper::Set_Transform(D3DTS_WORLD,world);
 // Keep the transform-state stores ahead of the function exit.
 _ReadWriteBarrier();
}
