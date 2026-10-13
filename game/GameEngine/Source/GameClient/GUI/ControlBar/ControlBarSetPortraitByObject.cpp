// cl: /DNDEBUG /MD /EHsc

// ControlBar::setPortraitByObject, retail 0x0049CFE0/3: a bare "ret 4".
// populateBeacon (0x004A3830), populateOCLTimer (0x004AAA70) and
// populateUnderConstruction (0x004AF6A0) call it through ILT 0x0002262E at
// the points where Zero Hour calls setPortraitByObject; BFME shows no portrait,
// so the body is empty.  It lives in its own file so that no caller can inline
// it away: retail keeps every call.

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
protected:
	void setPortraitByObject( Object *obj );
};

void ControlBar::setPortraitByObject( Object *obj )
{
}
