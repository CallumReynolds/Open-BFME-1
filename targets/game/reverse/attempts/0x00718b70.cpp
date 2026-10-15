// ?LoadAndCreateD3DShader@BfmeShaderLoader16@@SAHPBDPAI@Z
// partial score=0.7792 date=2026-10-15
// cl: /Iinputs/reference/shims/zhcanonascii /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims /Iinputs/reference/shims/sweep
// stlport
#include "dx8wrapper.h"

//
// BFME's two-argument pixel-shader loader.  The retail body is the target of
// the 0x0001FC99 ILT used by the flat-terrain shader initializers.  The file-system types come from their existing headers. The BFME-specific
// D3D loader retains its two-argument declaration and shifted device slot.
#include "string_base.h"
#include "d3d8_shim_validated.h"

#ifndef NULL
#define NULL 0
#endif

typedef int Int;
typedef bool Bool;

#define HEAP_ZERO_MEMORY 8
extern "C" __declspec(dllimport) void * __stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void * __stdcall HeapAlloc(void *, unsigned long, unsigned long);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void *, unsigned long, void *);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);
#define OutputDebugString OutputDebugStringA

#include "ascii_string.h"

#include "Common/file.h"
#include "Common/FileSystem.h"

// Address-scoped dispatch view: retail File's slots differ from Zero Hour's.
// Only +0x08 (close) and +0x0C (read) are used at this call site.
struct Rva00718A10Dispatch
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual Int slot0C(void *, Int);
};

extern FileSystem *TheFileSystem;

// The BFME device stores the shader methods at the shifted table offsets
// represented by the validated interface shim.  This global is the retail
// [0x01340534] device pointer.
typedef HRESULT (__stdcall *BfmeCreatePixelShader)(IDirect3DDevice8 *, const DWORD *, DWORD *);

// ?LoadAndCreateD3DShader@BfmeShaderLoader@@SAJPBDPAK@Z
class BfmeShaderLoader
{
public:
	static HRESULT LoadAndCreateD3DShader( const char *filename, DWORD *shader );
};

HRESULT BfmeShaderLoader::LoadAndCreateD3DShader( const char *filename, DWORD *shader )
{
	try
	{
		File *file = TheFileSystem->openFile( filename, File::READ | File::BINARY );
		if ( file == NULL )
		{
			OutputDebugString( "Could not find file \n" );
			return (HRESULT)0x80004005L;
		}

		FileInfo fileInfo;
		TheFileSystem->getFileInfo( AsciiString( filename ), &fileInfo );
		DWORD fileSize = fileInfo.sizeLow;

		const DWORD *shaderData = (const DWORD *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, fileSize );
		if ( shaderData == NULL )
		{
			OutputDebugString( "Failed to allocate memory to load shader\n " );
			return (HRESULT)0x80004005L;
		}

		// BFME File slots are read +0x0C and close +0x08; Zero Hour adds a slot.
		((Rva00718A10Dispatch *)file)->slot0C((void *)shaderData, fileSize);
		((Rva00718A10Dispatch *)file)->slot08();

			IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
			HRESULT result = (*(BfmeCreatePixelShader **)device)[106]( device, shaderData, shader );
		HeapFree( GetProcessHeap(), 0, (void *)shaderData );

		if ( result < 0 )
		{
			OutputDebugString( "Failed to create shader\n " );
			return (HRESULT)0x80004005L;
		}
	}
	catch ( ... )
	{
		OutputDebugString( "Error opening file \n" );
		return (HRESULT)0x80004005L;
	}

	return 0;
}

// Address-scoped view of the D3DX buffer interface used by 0x00718B70: only
// Release (+0x08) and GetBufferPointer (+0x0C) are called.
struct Rva00718B70Buffer
{
	virtual long __stdcall QueryInterface( const void *, void ** );
	virtual unsigned long __stdcall AddRef( void );
	virtual unsigned long __stdcall Release( void );
	virtual void * __stdcall GetBufferPointer( void );
};

extern "C" long __stdcall D3DXAssembleShader( const char *, unsigned int, const void *, void *, unsigned long, Rva00718B70Buffer **, Rva00718B70Buffer ** );

typedef HRESULT (__stdcall *BfmeCreateShader16)(IDirect3DDevice8 *, void *, unsigned int *);

// ?LoadAndCreateD3DShader@BfmeShaderLoader16@@SAHPBDPAI@Z
// The source-text sibling: assembles the shader file with D3DX, retrying the
// assembly up to ten times, then creates it through the same device slot.
class BfmeShaderLoader16
{
public:
	static int LoadAndCreateD3DShader( const char *filename, unsigned int *shader );
};

int BfmeShaderLoader16::LoadAndCreateD3DShader( const char *filename, unsigned int *shader )
{
	try
	{
		for ( Int attempt = 0; attempt < 10; ++attempt )
		{
			Rva00718B70Buffer *compiled = NULL;
			Rva00718B70Buffer *errors = NULL;
			File *file = NULL;
			HRESULT hr;

			file = TheFileSystem->openFile( filename, File::READ | File::BINARY );
			if ( file == NULL )
			{
				OutputDebugString( "Could not find file \n" );
				return (HRESULT)0x80004005L;
			}

			FileInfo fileInfo;
			TheFileSystem->getFileInfo( AsciiString( filename ), &fileInfo );
			Int fileSize = fileInfo.sizeLow;

			char *source = (char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, fileSize + 8 );
			if ( source == NULL )
			{
				OutputDebugString( "Failed to allocate memory to load shader\n " );
				return (HRESULT)0x80004005L;
			}

			((Rva00718A10Dispatch *)file)->slot0C( source, fileSize );
			source[fileSize] = 0;
			((Rva00718A10Dispatch *)file)->slot08();
			file = NULL;

			hr = D3DXAssembleShader( source, fileSize, NULL, NULL, 0, &compiled, &errors );
			HeapFree( GetProcessHeap(), 0, source );

			if ( hr < 0 )
			{
				if ( compiled != NULL )
				{
					compiled->Release();
					compiled = NULL;
				}
				if ( errors == NULL )
					return (HRESULT)0x80004005L;
				errors->GetBufferPointer();
				errors->Release();
				if ( attempt >= 9 )
					return (HRESULT)0x80004005L;
				continue;
			}

			IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
			hr = (*(BfmeCreateShader16 **)device)[106]( device, compiled->GetBufferPointer(), shader );
			if ( compiled != NULL )
			{
				compiled->Release();
				compiled = NULL;
			}

			if ( hr < 0 )
			{
				OutputDebugString( "Failed to create shader\n " );
				return (HRESULT)0x80004005L;
			}
			break;
		}
	}
	catch ( ... )
	{
		OutputDebugString( "Error opening file \n" );
		return (HRESULT)0x80004005L;
	}

	return 0;
}
