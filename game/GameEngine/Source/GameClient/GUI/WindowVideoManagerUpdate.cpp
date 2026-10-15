// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/GameClient /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Evidence: targets/game/reverse/identity_evidence/00499050-update.md

#include <map>
#include <hash_map>

#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"
#include "window_video_manager.h"
class GameWindow { public: Bool winIsHidden( void ); };

namespace BfmeUpdate
{
	class VideoBuffer
	{
	public:
		virtual void slot00();
		virtual void slot01();
		virtual void slot02();
		virtual void slot03();
		virtual void slot04();
		virtual void slot05();
		virtual unsigned int slot06( Int mode );		// slot 6, vtable+0x18
		virtual void slot07();
		virtual Int  slot08();					// slot 8, vtable+0x20
		virtual void slot09();
		virtual void slot10();
		virtual void slot11();
		virtual void slot12();
		virtual void slot13();
		virtual void slot14();
		virtual int useBuffer();				// slot 15, vtable+0x3c
	};

	typedef ::GameWindow GameWindow;

	// BFME keeps the name at +0x0c and the state at +0x10.
	// This view is used only to read existing WindowVideo objects.
	class WindowVideo
	{
	public:
		WindowVideoPlayType getPlayType( void ) { return m_playType; }
		GameWindow *getWin( void ) { return m_win; }
		VideoBuffer *getVideoBuffer( void ) { return m_videoBuffer; }
		// ?getBufferHandle00499050@WindowVideo@BfmeUpdate@@QAEHXZ absent-from-retail
		int getBufferHandle00499050( void ) { return m_videoBuffer ? m_videoBuffer->useBuffer() : 0; }
		WindowVideoStates getState( void ) { return m_state; }

	private:
		WindowVideoPlayType m_playType;
		GameWindow *m_win;
		VideoBuffer *m_videoBuffer;
		AsciiString m_movieName;
		WindowVideoStates m_state;
	};
}

// ?update@WindowVideoManager@@UAEXXZ
void WindowVideoManager::update( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();

	if ( m_pauseAllMovies || m_stopAllMovies )
		return;

	//Iterate through the maps
	while ( it != m_playingVideos.end() )
	{
		BfmeUpdate::WindowVideo *winVid = (BfmeUpdate::WindowVideo *)it->second;

		if ( !winVid )
		{
			DEBUG_CRASH(("There's No WindowVideo in the m_playignVideos list"));
			return;
		}
		BfmeUpdate::GameWindow *win = winVid->getWin();

		if ( winVid->getState() == WINDOW_VIDEO_STATE_HIDDEN && ( win->winIsHidden() == FALSE ) )
			resumeMovie( (GameWindow *)win );

		if ( winVid->getState() == WINDOW_VIDEO_STATE_PLAY && win->winIsHidden() )
			hideMovie( (GameWindow *)win );

		// Only advance the frame if we're playing
		if ( winVid->getState() != WINDOW_VIDEO_STATE_PLAY )
		{
			it++;
			continue;
		}

		// Get the Stream and the buffer to update for each animation
		BfmeUpdate::VideoBuffer *videoBuffer = winVid->getVideoBuffer();
		Int handle = winVid->getBufferHandle00499050();

		if ( videoBuffer && handle )
		{
			switch ( winVid->getPlayType() )
			{
			default:
			case WINDOW_PLAY_MOVIE_ONCE:
				if ( videoBuffer->slot06( 0 ) & 1 )
				{
					// If we reach frame Index of 0, we might have to pause, or loop.
					if ( videoBuffer->slot08() == 0 )
						stopMovie( (GameWindow *)win );
				}
				break;
			case WINDOW_PLAY_MOVIE_LOOP:
				videoBuffer->slot06( 4 );
				break;
			case WINDOW_PLAY_MOVIE_SHOW_LAST_FRAME:
				if ( videoBuffer->slot06( 0 ) & 1 )
				{
					// If we reach frame Index of 0, we might have to pause, or loop.
					if ( videoBuffer->slot08() == 0 )
						pauseMovie( (GameWindow *)win );
				}
				break;
			}
		}

		it++;
	}
}
