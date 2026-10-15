// ?rvaUniqueName0035a060@@YAXPAXPAVAsciiString@@@Z
// partial score=0.6114 date=2026-10-15
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x0035A060, 350 bytes, bare RET: file-static unique-name helper.  Its
// only caller 0x0035DD40 passes the owner in ECX and the AsciiString* on the
// stack and pops it itself (VC7.1 private convention for a static whose every
// caller is in the TU), so the helper is static and one scaffold call site
// keeps it emitted.  Owner layout per the matched 0x00359FE0 sibling
// (Code/GameEngine/Source/GameLogic/ScriptEngine/Rva00359FE0LookupReleased.cpp):
// name table at +0x0C, records at table +0x0C, released byte at record +0x0C.
//
// Reassigning the owner variable to its table (instead of a separate table
// reference) is what makes owner and table share EBX (`mov ebx,ecx ... add
// ebx,0xc`) and puts the null constant in ESI: byte-exact through +0xA6.
// First divergence +0xA7: MSVC CSEs &records[ri] into a spilled pointer, where
// retail keeps ri*20 in EBP, spills ri for the -1 test and reloads
// [table+0x0C] for m_released.  Every spelling that reads m_released through
// the owner (the 0x00359FE0 shape, which DOES give retail's reload) puts a
// use of the incoming owner inside the loop, and then VC7.1 passes the owner
// on the stack instead of in ECX.

#include "ascii_string.h"

template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
    int otherLength = str.m_data ? str.m_data->length : 0;
    const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
    int length = m_data ? m_data->length : 0;
    const char *data = m_data ? m_data->data : (const char *)"";
    int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
    return result ? result : length - otherLength;
}


class UnicodeString
{
public:
	void set(const UnicodeString &source);
};

bool rvaLookupReleased00359fe0(void *owner, AsciiString *name);

struct Rva00359330Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	bool m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

static void rvaUniqueName0035a060(void *owner, AsciiString *name);

class Rva00359330StringRecordTable
{
friend void rvaUniqueName0035a060(void *, AsciiString *);
friend bool rvaLookupReleased00359fe0(void *, AsciiString *);
private:
	int findNameIndex(AsciiString *name);
public:

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva00359330Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

class Rva00359FE0Owner
{
public:
	unsigned char m_head[0xc];
	Rva00359330StringRecordTable m_nameTable;
};

static inline const char *rvaText(const AsciiString *name)
{
	const char *data = *(const char * const *)name;
	return data ? data + 8 : "";
}

static inline int rvaCompareText(const AsciiString &own, const char *text,
	int length)
{
	const char *data = *(const char * const *)&own;
	const int ownLength = data ? *(const unsigned short *)(data + 4) : 0;
	const char *ownText = data ? data + 8 : "";
	int result = memcmp(ownText, text, ownLength < length ? ownLength : length);
	if (result == 0)
		result = ownLength - length;
	return result;
}

static inline int rvaCompare(const AsciiString &own, const AsciiString &other)
{
	const char *data = *(const char * const *)&other;
	const int length = data ? *(const unsigned short *)(data + 4) : 0;
	const char *text = data ? data + 8 : "";
	return rvaCompareText(own, text, length);
}

static void rvaUniqueName0035a060(void *owner, AsciiString *name)
{
	if (rvaLookupReleased00359fe0(owner, name))
		return;

	AsciiString candidate;
	int suffix = 0;
	owner = &((Rva00359FE0Owner *)owner)->m_nameTable;
	for (;;)
	{
		++suffix;
		candidate.format(AsciiString("%s %d"), rvaText(name), suffix);

		unsigned int nameIndex = ((Rva00359330StringRecordTable *)owner)->findNameIndex(&candidate);
		if (nameIndex >= (unsigned int)(((Rva00359330StringRecordTable *)owner)->m_nameIndexesEnd - ((Rva00359330StringRecordTable *)owner)->m_nameIndexesBegin))
			break;

		int recordIndex = ((Rva00359330StringRecordTable *)owner)->m_nameIndexesBegin[nameIndex];
		int comparison = ((StringBase<char> &)((Rva00359330StringRecordTable *)owner)->m_records[recordIndex].m_name).compare(candidate);
        if (comparison < 0 || comparison > 0 || recordIndex == -1 || ((Rva00359330StringRecordTable *)owner)->m_records[recordIndex].m_released)
            break;
	}

	name->set(candidate);
}

struct Rva0035DD40Holder
{
	unsigned char m_head[0xc];
	void *m_owner;
};

// ?rvaScaffold0035dd40@@YAXPAURva0035DD40Holder@@VAsciiString@@@Z absent-from-retail
void rvaScaffold0035dd40(Rva0035DD40Holder *holder, AsciiString name)
{
	rvaUniqueName0035a060(holder->m_owner, &name);
}
