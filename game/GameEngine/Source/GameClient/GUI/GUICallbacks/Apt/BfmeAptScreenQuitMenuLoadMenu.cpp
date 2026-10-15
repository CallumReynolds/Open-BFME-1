// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// AptQuitMenu::SaveMenu and AptQuitMenu::LoadMenu callbacks with the inlined
// native multiplayer predicate.

#include "../../../window_layout.h"

class Keyboard
{
public:
	bool isShift();
};

class GlobalData
{
public:
	char m_head[ 0xa9e ];
	char m_flagA9E;
};

class GameLogic
{
public:
	char m_unmodelled[ 0x10c ];
	int m_gameMode;
	bool isInMultiplayerGame() { return m_gameMode == 1 || m_gameMode == 5; }
};

class Shell
{
public:
	WindowLayout *getSaveLoadMenuLayout( void );
};

extern Keyboard *TheKeyboard;
extern GlobalData *TheWritableGlobalData;
extern GameLogic * const TheGameLogic;
extern Shell *TheShell;

void showAptSaveLoad( void *arg0, int flags, const volatile char extra );

class BfmeAptScreenQuitMenu
{
public:
	void _bfme_saveMenu00569420( const char *name );
	void _bfme_loadMenu005694E0( const char *name );
};

// ?_bfme_saveMenu00569420@BfmeAptScreenQuitMenu@@QAEXPBD@Z
// The QuitMenu constructor (0x0056A2F0) binds the selector string
// AptQuitMenu::SaveMenu to the ILT that reaches 0x00569420; the body is the
// load callback's twin with save mode 3. The stem keeps the address because
// the original method spelling is unproven, as for the load callback.
void BfmeAptScreenQuitMenu::_bfme_saveMenu00569420( const char *name )
{
	(void)name;
	bool useMenu = ( TheWritableGlobalData->m_flagA9E == 0 );
	if( TheKeyboard->isShift() )
		useMenu = !useMenu;

	if( useMenu )
	{
		int flags;
		if( TheGameLogic->isInMultiplayerGame() )
			flags = 4;
		else
			flags = TheGameLogic->m_gameMode == 2 ? 2 : 1;
		showAptSaveLoad( (void *)3, flags, 1 );
	}
	else
	{
		WindowLayout *layout = TheShell->getSaveLoadMenuLayout();
		layout->runInit( 0 );
		layout->hide( 0 );
		layout->bringForward();
	}
}

// ?_bfme_loadMenu005694E0@BfmeAptScreenQuitMenu@@QAEXPBD@Z
void BfmeAptScreenQuitMenu::_bfme_loadMenu005694E0( const char *name )
{
	(void)name;
	bool useMenu = ( TheWritableGlobalData->m_flagA9E == 0 );
	if( TheKeyboard->isShift() )
		useMenu = !useMenu;

	if( useMenu )
	{
		int flags;
		if( TheGameLogic->isInMultiplayerGame() )
			flags = 4;
		else
			flags = TheGameLogic->m_gameMode == 2 ? 2 : 1;
		showAptSaveLoad( (void *)2, flags, 1 );
	}
	else
	{
		WindowLayout *layout = TheShell->getSaveLoadMenuLayout();
		layout->runInit( 0 );
		layout->hide( 0 );
		layout->bringForward();
	}
}
