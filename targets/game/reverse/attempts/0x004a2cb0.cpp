// ?rva004A2CB0@ControlBar@@QAEXXZ
// partial score=0.9688 date=2026-10-14
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib
#include "Common/AsciiString.h"

class Image
{
public:
	void load();
};

class ImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};
extern ImageCollection *TheMappedImageCollection;

class BfmeHolderBF
{
public:
	void *bfmeResolveBF();
};

class ThingTemplatePortraitShim
{
public:
	const Image *getSelectedPortraitImage() const;
};

class ThingTemplate
{
public:
	char m_rva000[ 0x28 ];
	AsciiString m_side;
	AsciiString m_commandSetString;
	char m_rva030[ 0xC8 - 0x30 ];
	unsigned int m_kindof[ 3 ];
	char m_rva0D4[ 0x38C - 0xD4 ];
	ThingTemplate *m_nextThingTemplate;

	const Image *getSelectedPortraitImage() const { return ( (const ThingTemplatePortraitShim *)this )->getSelectedPortraitImage(); }
	Image *getRva13EE70Image() { return (Image *)( (BfmeHolderBF *)this )->bfmeResolveBF(); }
	ThingTemplate *friend_getNextTemplate() const { return m_nextThingTemplate; }
};

class ThingFactory
{
public:
	char m_rva00[ 8 ];
	ThingTemplate *m_firstTemplate;
	ThingTemplate *firstTemplate() { return m_firstTemplate; }
};
extern ThingFactory *TheThingFactory;

class PlayerTemplate
{
public:
	char m_rva000[ 0xA4 ];
	AsciiString m_rvaA4CommandSet;
};

class Player
{
public:
	char m_rva00[ 4 ];
	const PlayerTemplate *m_playerTemplate;
	char m_rva08[ 0x28 - 8 ];
	AsciiString m_side;
};

class PlayerList
{
public:
	char m_rva00[ 0xC ];
	Player *m_local;
	Player *getLocalPlayer() { return m_local; }
};
extern PlayerList *ThePlayerList;

class ControlBar
{
public:
	void commandSetButtonWalk( const AsciiString &commandSet );
	void rva004A2CB0();
};

void ControlBar::rva004A2CB0()
{
	if( ThePlayerList == 0 || TheThingFactory == 0 )
		return;
	Player *player = ThePlayerList->getLocalPlayer();
	if( player == 0 )
		return;

	AsciiString side = player->m_side;
	for( ThingTemplate *tmplate = TheThingFactory->firstTemplate(); tmplate; tmplate = tmplate->friend_getNextTemplate() )
	{
		if( ( tmplate->m_kindof[ 0 ] & 2 ) == 0 )
			continue;
		if( ( (const StringBase<char> *)&tmplate->m_side )->compare( *(const StringBase<char> *)&side ) != 0 )
			continue;
		commandSetButtonWalk( tmplate->m_commandSetString );
		if( tmplate->getSelectedPortraitImage() )
			( (Image *)tmplate->getSelectedPortraitImage() )->load();
		if( tmplate->getRva13EE70Image() )
			tmplate->getRva13EE70Image()->load();
	}

	if( player->m_playerTemplate )
		commandSetButtonWalk( player->m_playerTemplate->m_rvaA4CommandSet );

	if( TheMappedImageCollection )
	{
		Image *push = (Image *)TheMappedImageCollection->findImageByName( AsciiString( "RadialPush" ) );
		Image *over = (Image *)TheMappedImageCollection->findImageByName( AsciiString( "RadialOver" ) );
		Image *border = (Image *)TheMappedImageCollection->findImageByName( AsciiString( "RadialBorder" ) );
		Image *clock1 = (Image *)TheMappedImageCollection->findImageByName( AsciiString( "RadialClockOverlay1" ) );
		Image *clock2 = (Image *)TheMappedImageCollection->findImageByName( AsciiString( "RadialClockOverlay2" ) );
		if( push )
			push->load();
		if( over )
			over->load();
		if( border )
			border->load();
		if( clock1 )
			clock1->load();
		if( clock2 )
			clock2->load();
	}
}
