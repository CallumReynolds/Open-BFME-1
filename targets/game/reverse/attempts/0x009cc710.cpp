// ?openArchiveFile@Win32BIGFileSystem@@UAEPAVArchiveFile@@PBD@Z
// partial score=0.8546 date=2026-10-15
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep

#include <stddef.h>
#include <string.h>
#include "string_base.h"

extern void * __cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *p);

typedef char Char;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "ascii_string.h"

inline AsciiString::AsciiString(const AsciiString &src, int start, int len) : StringBase<char>(src, start, len) {}

// ?ntohl_inline@@YAHH@Z absent-from-retail
static inline Int ntohl_inline( Int v )
{
	unsigned int u = (unsigned int)v;
	return (Int)((u << 24) + ((u << 8) & 0xFF0000) + (u >> 24) + ((u >> 8) & 0xFF00));
}

struct ArchivedFileInfo
{
	AsciiString m_filename;
	AsciiString m_archiveFilename;
	UnsignedInt m_offset;
	UnsignedInt m_size;

	ArchivedFileInfo();
};

class ArchiveFile
{
public:
	virtual ~ArchiveFile();
	virtual void A1();
	virtual void A2();
	virtual void A3();
	virtual void A4();
	virtual void A5();
	virtual void A6();
	virtual void A7();
	virtual void A8();
	virtual void setNameAndPath( const AsciiString &nameAndPath );

	void addFile( const AsciiString &path, const ArchivedFileInfo *info );
	void attachFile( class File *file );
};

class Win32BIGFile : public ArchiveFile
{
public:
	Win32BIGFile();

private:
	char m_opaque[40];
};

class File
{
public:
	enum { READ = 0x01, BINARY = 0x40 };
	virtual ~File();
	virtual Bool open( const Char *filename, Int access );
	virtual void close( void );
	virtual Int read( void *buffer, Int bytes );
};

class LocalFileSystem
{
public:
	virtual ~LocalFileSystem();
	virtual void L1() = 0;
	virtual File *openFile( const Char *filename, Int access ) = 0;
};

extern LocalFileSystem *TheLocalFileSystem;

extern const char *TheBigfIdentifier;
extern const char *TheBig4Identifier;

class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();
	virtual void init( void );
	virtual ArchiveFile *openArchiveFile( const Char *filename );
};

// ?openArchiveFile@Win32BIGFileSystem@@UAEPAVArchiveFile@@PBD@Z present-unmatched
ArchiveFile *Win32BIGFileSystem::openArchiveFile( const Char *filename )
{
	File *fp = TheLocalFileSystem->openFile( filename, File::READ | File::BINARY );

	AsciiString archiveFileName;
	archiveFileName.StringBase<char>::set( filename, filename ? (int)strlen( filename ) : 0 );
	archiveFileName.toLower();
	UnsignedInt archiveFileSize = 0;
	UnsignedInt numLittleFiles = 0;

	ArchiveFile *archiveFile = (ArchiveFile *)new Win32BIGFile;
	archiveFile->setNameAndPath( AsciiString( filename ) );

	// Only the missing-file branch returns a null archive.
	if (fp == NULL) {
		return NULL;
	}

	// Retail reads the complete header before testing either tag.
	// A rejected header still reaches attachFile.
	char header[16];
	if (fp->read( header, 16 ) == 16 &&
		(strncmp( TheBigfIdentifier, header, 4 ) == 0 ||
		 strncmp( TheBig4Identifier, header, 4 ) == 0)) {

	ArchivedFileInfo fileInfo;

	// The directory extent is the header word at offset twelve.
	archiveFileSize = ntohl_inline( *(Int *)(header + 12) );
	numLittleFiles = (UnsignedInt)ntohl_inline( *(Int *)(header + 8) );

	char *table = new char[archiveFileSize];
	if (fp->read( table, archiveFileSize - 0x10 ) == archiveFileSize - 0x10) {

	char *p = table;
	// Each entry stores an offset, a size and a NUL-terminated name.
	for (UnsignedInt i = numLittleFiles; i != 0; --i) {
		fileInfo.m_archiveFilename.set( archiveFileName );
		fileInfo.m_offset = ntohl_inline( *(Int *)p );
		fileInfo.m_size   = ntohl_inline( *(Int *)(p + 4) );

		const char *name = p + 8;

		// The prefix ending at the final separator becomes the path.
		Int sep = (Int)strlen( name );
		while (sep >= 0 && name[sep] != '\\' && name[sep] != '/') {
			--sep;
		}

		const char *base = name + sep + 1;
		fileInfo.m_filename.StringBase<char>::set( base, base ? (int)strlen( base ) : 0 );
		fileInfo.m_filename.toLower();

		// The full-name temporary ends before addFile.
		AsciiString path( AsciiString( name ), 0, sep + 1 );

		archiveFile->addFile( path, &fileInfo );

		// addFile can mutate the input, so recompute the name length.
		p += (Int)strlen( name ) + 9;
	}
	}

	delete[] table;
	}

	archiveFile->attachFile( fp );

	return archiveFile;
}

