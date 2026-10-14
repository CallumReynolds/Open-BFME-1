// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME: constructor of the Apt-layer screen whose vftable is 0x010F74E8
// (??_7Rva00470360@@6B@; destructor 0x00470360 in Rva00470360Destructor.cpp,
// slot 0 0x004703F0 in Rva00470360FitWindow.cpp), retail 0x00470720, 199
// bytes. It chains to BfmeQuickMatchScreenBase's constructor (0x00470620,
// through ILT 0x00025D7E), clears the window pointer at +0x24 and the
// registered flag at +0x28, asks TheWindowManager (slot 0xD4) to create the
// window under the base's +0x08 handle, and when that comes back as the same
// handle registers it with the manager at 0x012F19E8 (slot 0x3C, "Apt\\" plus
// the window's Apt name), storing an index below 12 at window+0x250.
// The class name is address-derived; the method is the constructor.
//
// Shape notes measured against retail: the base handle is read into a local
// before the create call, and the window's name is passed through a const
// reference local.
#include "Common/AsciiString.h"

class GameWindow
{
public:
	unsigned char m_pad[ 0x24C ];
	AsciiString m_aptName;
	int m_aptIndex;
};

class GameWindowManager
{
public:
	virtual void vslot00(); virtual void vslot04(); virtual void vslot08(); virtual void vslot0c();
	virtual void vslot10(); virtual void vslot14(); virtual void vslot18(); virtual void vslot1c();
	virtual void vslot20(); virtual void vslot24(); virtual void vslot28(); virtual void vslot2c();
	virtual void vslot30(); virtual void vslot34(); virtual void vslot38(); virtual void vslot3c();
	virtual void vslot40(); virtual void vslot44(); virtual void vslot48(); virtual void vslot4c();
	virtual void vslot50(); virtual void vslot54(); virtual void vslot58(); virtual void vslot5c();
	virtual void vslot60(); virtual void vslot64(); virtual void vslot68(); virtual void vslot6c();
	virtual void vslot70(); virtual void vslot74(); virtual void vslot78(); virtual void vslot7c();
	virtual void vslot80(); virtual void vslot84(); virtual void vslot88(); virtual void vslot8c();
	virtual void vslot90(); virtual void vslot94(); virtual void vslot98(); virtual void vslot9c();
	virtual void vslota0(); virtual void vslota4(); virtual void vslota8(); virtual void vslotac();
	virtual void vslotb0(); virtual void vslotb4(); virtual void vslotb8(); virtual void vslotbc();
	virtual void vslotc0(); virtual void vslotc4(); virtual void vslotc8(); virtual void vslotcc();
	virtual void vslotd0();
	virtual void vslotd4( int parent, int a, int b, GameWindow **window );
};
extern GameWindowManager *TheWindowManager;

class WindowManager
{
public:
	virtual void vslot00(); virtual void vslot04(); virtual void vslot08(); virtual void vslot0c();
	virtual void vslot10(); virtual void vslot14(); virtual void vslot18(); virtual void vslot1c();
	virtual void vslot20(); virtual void vslot24(); virtual void vslot28(); virtual void vslot2c();
	virtual void vslot30(); virtual void vslot34(); virtual void vslot38();
	virtual unsigned int vslot3c( AsciiString path, AsciiString name, int a, GameWindow *window, int b );
};
extern WindowManager *g_rva012F19E8WindowManager;

class BfmeQuickMatchScreenBase
{
public:
	BfmeQuickMatchScreenBase( void *screen );
	virtual ~BfmeQuickMatchScreenBase();

	unsigned char m_pad04[ 4 ];
	int m_bfme08;
	unsigned char m_pad0C[ 0x24 - 0xC ];
};

class Rva00470360 : public BfmeQuickMatchScreenBase
{
public:
	Rva00470360( void *screen );
	virtual ~Rva00470360();

	GameWindow *m_window;
	bool m_registered;
};

Rva00470360::Rva00470360( void *screen ) : BfmeQuickMatchScreenBase( screen )
{
	int parent = m_bfme08;
	m_window = 0;
	m_registered = false;
	TheWindowManager->vslotd4( parent, 0x1D, 0x7D0, &m_window );
	if( m_window == (GameWindow *)parent )
	{
		const AsciiString &name = m_window->m_aptName;
		unsigned int index = g_rva012F19E8WindowManager->vslot3c( AsciiString( "Apt\\" ), name, 0, m_window, -1 );
		if( index < 12 )
			m_window->m_aptIndex = index;
	}
}
