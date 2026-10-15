// ?writeCacheINI@MapCache@@AAEX_N@Z
// partial score=0.9135 date=2026-10-15
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport /Igame/Libraries/Source/WWVegas/WWLib

#include <stdio.h>
#include <string.h>
#include <stl/_config.h>
#include <list>
#include <map>
#include <set>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef float Real;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void set(const StringBase<T> &other);
	void concat(const T *text, Int len);
	void toLower();
	bool startsWithNoCase(const T *text, Int len) const;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	struct Data
	{
		Int m_refCount;
		UnsignedShort m_length;
		UnsignedShort m_capacity;
		T m_text[1];
	};
	Data *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void set(const AsciiString &other) { StringBase<char>::set(other); }
	void concat(const char *text, Int len) { StringBase<char>::concat(text, len); }
	void concat(const char c) { concat(&c, 1); }
	void toLower() { StringBase<char>::toLower(); }
	bool startsWithNoCase(const char *text, Int len) const { return StringBase<char>::startsWithNoCase(text, len); }

	Int compare(const AsciiString &other) const
	{
		const Int thatLen = other.m_data ? other.m_data->m_length : 0;
		const char *thatData = other.m_data ? other.m_data->m_text : "";
		const Int thisLen = m_data ? m_data->m_length : 0;
		const char *thisData = m_data ? m_data->m_text : "";
		const Int result = memcmp(thisData, thatData, thisLen < thatLen ? thisLen : thatLen);
		if (result != 0) return result;
		return thisLen - thatLen;
	}


	const char *str() const { return m_data ? m_data->m_text : ""; }
};

bool operator<(const AsciiString &left, const AsciiString &right);
inline bool operator==(const AsciiString &left, const AsciiString &right) { return left.compare(right) == 0; }

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() : StringBase<UnsignedShort>() {}
	UnicodeString(const UnicodeString &other) : StringBase<UnsignedShort>(other) {}
	~UnicodeString() {}

	const UnsignedShort *str() const { return m_data ? m_data->m_text : (const UnsignedShort *)L""; }
};

struct Coord3D
{
	Real x, y, z;
};

struct Region3D
{
	Coord3D lo, hi;
};

struct WinTimeStamp
{
	UnsignedInt m_lowTimeStamp;
	UnsignedInt m_highTimeStamp;
};

struct PlayerSlot
{
	Bool m_human;
	Bool m_computer;
	Bool m_loadAIScripts;
	Int m_forcePlayerTeam;
	std::set<AsciiString> m_factions;
};

class WaypointMap : public std::map<AsciiString, Coord3D>
{
public:
	Int m_numStartSpots;
};

typedef std::list<Coord3D> Coord3DList;

class MapMetaData
{
public:
	MapMetaData();
	MapMetaData &operator=(const MapMetaData &);
	~MapMetaData();

	UnicodeString m_displayName;
	UnicodeString m_description;
	Region3D m_extent;
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isScenarioMP;
	Bool m_isOfficial;
	UnsignedInt m_filesize;
	UnsignedInt m_CRC;
	WinTimeStamp m_timestamp;
	WaypointMap m_waypoints;
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
	AsciiString m_fileName;
	PlayerSlot m_players[8];
	unsigned char m_tail[8];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char _pad_b7d[0xB7D];
	Bool m_buildMapCache;
};

extern GlobalData *TheWritableGlobalData;

class FileSystem
{
public:
	Bool createDirectory(AsciiString directory);
};

extern FileSystem *TheFileSystem;

AsciiString AsciiStringToQuotedPrintable(AsciiString original);
AsciiString UnicodeStringToQuotedPrintable(UnicodeString original);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache : public std::map<AsciiString, MapMetaData>
{
public:
	AsciiString getUserMapDir() const;
	AsciiString getMapDir() const;

private:
	void writeCacheINI(bool userDir);
};

// ?writeCacheINI@MapCache@@AAEX_N@Z
void MapCache::writeCacheINI(bool userDir)
{
	AsciiString mapDir;
	if (!userDir || TheWritableGlobalData->m_buildMapCache)
		mapDir.set(getMapDir());
	else
		mapDir.set(getUserMapDir());

	AsciiString filepath(mapDir);
	filepath.concat('\\');

	TheFileSystem->createDirectory(mapDir);
	filepath.concat("MapCache.ini", 12);

	FILE *fp = fopen(filepath.str(), "w");
	if (fp == 0)
		return;

	fprintf(fp, "; FILE: %s /////////////////////////////////////////////////////////////\n", filepath.str());
	fprintf(fp, "; This INI file is auto-generated - do not modify\n");
	fprintf(fp, "; /////////////////////////////////////////////////////////////////////////////\n");
	mapDir.toLower();

	MapCache::iterator it = begin();
	MapMetaData md;
	while (it != end())
	{
		Coord3D pos;
		const AsciiString *mapName = &it->first;
		const char *dir = mapDir.str();
		Int dirLen = 0;
		if (dir)
			dirLen = (Int)strlen(dir);
		if (mapName->startsWithNoCase(dir, dirLen))
		{
		md = it->second;
		{
			AsciiString encodedText = AsciiStringToQuotedPrintable(mapName->str());
			fprintf(fp, "\nMapCache %s\n", encodedText.str());
		}
		fprintf(fp, "  fileSize = %u\n", md.m_filesize);
		fprintf(fp, "  fileCRC = %u\n", md.m_CRC);
		fprintf(fp, "  timestampLo = %d\n", md.m_timestamp.m_lowTimeStamp);
		fprintf(fp, "  timestampHi = %d\n", md.m_timestamp.m_highTimeStamp);
		fprintf(fp, "  isOfficial = %s\n", md.m_isOfficial ? "yes" : "no");
		fprintf(fp, "  isMultiplayer = %s\n", md.m_isMultiplayer ? "yes" : "no");
		fprintf(fp, "  isScenarioMP = %s\n", md.m_isScenarioMP ? "yes" : "no");
		fprintf(fp, "  numPlayers = %d\n", md.m_numPlayers);
		fprintf(fp, "  extentMin = X:%2.2f Y:%2.2f Z:%2.2f\n", md.m_extent.lo.x, md.m_extent.lo.y, md.m_extent.lo.z);
		fprintf(fp, "  extentMax = X:%2.2f Y:%2.2f Z:%2.2f\n", md.m_extent.hi.x, md.m_extent.hi.y, md.m_extent.hi.z);
// BAD AND NOW UNUSED:  the mapcache.ini should not contain localized data... using the lookup tag instead
//			fprintf(fp, "  displayName = %s\n", UnicodeStringToQuotedPrintable(md.m_displayName).str());
		fprintf(fp, "  displayName = %s\n", UnicodeStringToQuotedPrintable(md.m_displayName).str());
		fprintf(fp, "  description = %s\n", UnicodeStringToQuotedPrintable(md.m_description).str());

		WaypointMap::iterator itw = md.m_waypoints.begin();
		while (itw != md.m_waypoints.end())
		{
			pos = itw->second;
			fprintf(fp, "  %s = X:%2.2f Y:%2.2f Z:%2.2f\n", itw->first.str(), pos.x, pos.y, pos.z);
			++itw;
		}

		Coord3DList::iterator itc3d = md.m_techPositions.begin();
		while (itc3d != md.m_techPositions.end())
		{
			pos = *itc3d;
			fprintf(fp, "  techPosition = X:%2.2f Y:%2.2f Z:%2.2f\n", pos.x, pos.y, pos.z);
			++itc3d;
		}

		itc3d = md.m_supplyPositions.begin();
		while (itc3d != md.m_supplyPositions.end())
		{
			pos = *itc3d;
			fprintf(fp, "  supplyPosition = X:%2.2f Y:%2.2f Z:%2.2f\n", pos.x, pos.y, pos.z);
			++itc3d;
		}

		for (Int i = 0; i < 8; ++i)
		{
			PlayerSlot *slot = &md.m_players[i];
			static PlayerSlot s_default = { 1, 1, 1, (Int)-1 };
			if (slot->m_human == s_default.m_human &&
				slot->m_computer == s_default.m_computer &&
				slot->m_loadAIScripts == s_default.m_loadAIScripts &&
				slot->m_forcePlayerTeam == s_default.m_forcePlayerTeam &&
				slot->m_factions == s_default.m_factions)
				continue;
			fprintf(fp, "  PlayerPosition %d\n", i + 1);
			fprintf(fp, "    Human = %s\n", slot->m_human ? "Yes" : "No");
			fprintf(fp, "    Computer = %s\n", slot->m_computer ? "Yes" : "No");
			fprintf(fp, "    LoadAIScripts = %s\n", slot->m_loadAIScripts ? "Yes" : "No");
			fprintf(fp, "    ForcePlayerTeam = %d\n", slot->m_forcePlayerTeam);
			if (!slot->m_factions.empty())
			{
				fprintf(fp, "    AllowedFactions =");
				for (std::set<AsciiString>::iterator f = slot->m_factions.begin();
					f != slot->m_factions.end(); ++f)
					fprintf(fp, " %s", f->str());
				fprintf(fp, "\n");
			}
			fprintf(fp, "  END\n");
		}
		fprintf(fp, "END\n\n");
		}
		else
		{
			//DEBUG_LOG(("%s does not start %s\n", mapDir.str(), it->first.str()));
		}
		++it;
	}

	fclose(fp);
}
