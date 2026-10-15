// Retail 0x00493F30/105: state update for the transition controller.
// The retail body reads m_flags at +0x08, the controller flag byte at +0x238,
// and the previous flags at +0x250. The controller calls use vtable slots
// +0x10 and +0x14. The finishTransition thunk is the matched retail target
// at 0x00005925 and its body is 0x00493EA0. Retail returns with
// mov eax, 1, a full int result, not a bool.
// cl: /DNDEBUG /DWIN32 /MD /EHsc

class Rva00493F30Controller
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();

	bool flag20() const { return (m_flags20 & 1) != 0; }

private:
	unsigned char m_padding4[0x1c];
	unsigned char m_flags20;
};

class Rva00493F30TransitionState
{
public:
	int updateState(void);
	void finishTransition(void);

private:
	unsigned char m_padding0[8];
	unsigned int m_flags;
	unsigned char m_padding1[0x20c];
	Rva00493F30Controller m_controller;
	unsigned char m_padding3[0x14];
	unsigned int m_previousFlags;
};

int Rva00493F30TransitionState::updateState(void)
{
	if (!(m_previousFlags & 0x10) && (m_flags & 0x10))
	{
		if (m_controller.flag20())
			m_controller.slot4();
	}
	else if ((m_previousFlags & 0x10) && !(m_flags & 0x10))
	{
		finishTransition();
	}
	m_previousFlags = m_flags;
	if (m_controller.flag20())
		m_controller.slot5();
	return 1;
}
