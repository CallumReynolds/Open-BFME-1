// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// getDefaultMap (retail 0x00457FB0, 361 bytes). MapUtil.cpp still builds on the
// ZH AsciiString, whose inline copy constructor retail does not have, so this
// body uses the canonical BFME string like the map-list population TU. Retail
// expands MapCache::updateCache inline, then collects the matching maps through
// 0x00453480 (its body stays visible so the vector does not escape), sorts them through 0x004568C0 and returns the first file name.
#include "Rva00453480MapPointerCollector.h"
#include "ascii_string.h"

void setFPMode();

class FileSystem
{
public:
	bool createDirectory(AsciiString directory);
};
extern FileSystem *TheFileSystem;

class MapMetaData
{
public:
	char field00[0x50];
	AsciiString m_fileName;
};

class MapCache
{
public:
	AsciiString getUserMapDir() const;
	friend void updateMapCache(MapCache *cache);

private:
	void loadStandardMaps(void);
	bool loadUserMaps(void);
	void writeCacheINI(bool userDir);
};

struct Q3SortElem4;
struct Q3SortCompare
{
	bool field0;
	Q3SortCompare() : field0(false) {}
};
void Rva004568C0(Q3SortElem4 *first, Q3SortElem4 *last, Q3SortCompare compare);

// MapCache::updateCache (0x00457E70, MapUtil.cpp), which retail inlines here.
__forceinline void updateMapCache(MapCache *cache)
{
	setFPMode();

	TheFileSystem->createDirectory(cache->getUserMapDir());

	if (cache->loadUserMaps())
	{
		cache->writeCacheINI(true);
	}
	cache->loadStandardMaps();
}

AsciiString getDefaultMap(bool isMultiplayer)
{
	if (!TheMapCache)
		return AsciiString::TheEmptyString;
	updateMapCache(TheMapCache);

	unsigned int flags = (isMultiplayer ? 8 : 4) | 1;
	std::vector<const MapMetaData *> maps;
	Rva00453480Collect(flags, &maps);
	Rva004568C0((Q3SortElem4 *)maps.begin(), (Q3SortElem4 *)maps.end(), Q3SortCompare());
	if (maps.size() != 0)
		return (*maps.begin())->m_fileName;

	return AsciiString::TheEmptyString;
}
