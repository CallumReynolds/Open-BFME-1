// ?input@AptMainMenu@@UAEHIII@Z
// partial score=0.9506 date=2026-10-16
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

#include <stdlib.h>

#include "Lib/BaseType.h"

// ?decodePosition0051E700@@YA?AUICoord2D@@I@Z absent-from-retail
static __forceinline ICoord2D decodePosition0051E700(unsigned int data)
{
	ICoord2D result;
	result.y = (int)(data >> 16);
	result.x = (int)(data & 0xffff);
	return result;
}

class WindowManager
{
public:
	void *_bfme_callAptFunction( unsigned int level, const char *functionName,
		int argCount, const char *a0, const char *a1, const char *a2,
		const char *a3, const char *a4 );
};

extern WindowManager *g_theWindowManager;

class Mouse
{
public:
	void _bfme_setEngineVisibility( bool visible );
};

extern Mouse *TheMouse;

class AptMainMenu
{
public:
	virtual ~AptMainMenu();
	virtual int input( unsigned int message, unsigned int data, unsigned int state );
	void BattleSchool( void *unused );

private:
	unsigned char m_unmodelled04[ 0x24C ];
	unsigned int m_field250;
	unsigned char m_unmodelled254[ 5 ];
	unsigned char m_b259;
	unsigned char m_b25a;
	unsigned char m_unmodelled25b[ 5 ];
	int m_z260;
	int m_i264;
};

// ?input@AptMainMenu@@UAEHIII@Z present-unmatched
int AptMainMenu::input( unsigned int message, unsigned int data, unsigned int state )
{
	if ( m_i264 == 8 )
		return 0;

	if ( m_b259 )
	{
		if (message == 0x15 ? (unsigned char)data - 1 : 1)
			return 0;

		if ( ( state & 1 ) == 0 )
			return 1;

		if ( m_i264 == 1 || m_i264 == 2 )
			return 1;

		if ( m_i264 == 4 )
		{
			g_theWindowManager->_bfme_callAptFunction(
				m_field250, "HideCredits", 0, 0, 0, 0, 0, 0 );
			return 1;
		}

		if ( m_i264 == 7 )
		{
			BattleSchool( 0 );
			return 1;
		}

		g_theWindowManager->_bfme_callAptFunction(
			m_field250, "EscapeKeyPressed", 0, 0, 0, 0, 0, 0 );

		return 1;
	}

	if ( m_b25a )
		m_b259 = 1;

	if ( message != 0x15 )
	{
		if ( message == 0x18 )
		{
			ICoord2D position = decodePosition0051E700(data);

			if ( position.x != 0 || position.y != 0 )
			{
				static int previousX = position.x;
				static int previousY = position.y;

				if ( abs( position.x - previousX ) > 20 ||
					abs( position.y - previousY ) > 20 )
					m_b259 = 1;
			}
		}
	}
	else if ( m_i264 != 4 )
		m_b259 = 1;

	if ( m_b259 )
	{
		TheMouse->_bfme_setEngineVisibility( true );
		m_b259 = 1;
		g_theWindowManager->_bfme_callAptFunction(
			m_field250, "ShowMainMenu", 0, 0, 0, 0, 0, 0 );
	}

	return 0;
}
