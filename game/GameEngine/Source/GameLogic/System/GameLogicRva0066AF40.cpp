// cl: /DNDEBUG /MD /EHsc
//
// GameLogic::rva0066AF40, retail 0x0066AF40 (13 bytes, RET 4):
//
//     mov eax,[esp+4] / mov [ecx+0x290],eax / ret 4
//
// Retail never calls it: the only reference in the image is its own ILT thunk
// 0x00016FD1, which nothing calls or points at. It sits at the head of
// DisconnectManager's code, after the equally uncalled out-of-line copy of
// GameSlot::markAsDisconnected (0x0066AF30) and before DisconnectManager's
// constructor (0x0066AF50), the way a header inline the unit uses is kept.
// The only +0x290 stores in that unit go to TheGameLogic (0x012F0898):
// processDisconnectPlayer (0x0066C760) and updateDisconnectStatus (0x0066C3B0)
// write 0, 1 or 2 there inline (DisconnectManager.cpp). So the owner is
// GameLogic. Zero Hour's GameLogic has no member at +0x290 and no caller or
// string names the method, so it keeps its address. It was matched as
// Object::setSafeOcclusionFrame only because a Zero Hour donor copy of
// GarrisonContain::onRemoving compiled to the same 13 bytes; BFME keeps that
// frame at +0x334 (0x001C3020).

class GameLogic
{
public:
	void rva0066AF40(int value);

private:
	char m_lead[0x290];
	int m_field290;
};

// ?rva0066AF40@GameLogic@@QAEXH@Z
void GameLogic::rva0066AF40(int value)
{
	m_field290 = value;
}
