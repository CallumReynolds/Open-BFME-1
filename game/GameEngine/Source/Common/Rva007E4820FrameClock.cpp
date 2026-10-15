// ?frame@Rva007E4820FrameClock@@QAEHH@Z [retail body 0x007E4820]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// VP6 frame clock: elapsed timeGetTime ticks scaled to a frame number.
// Called by the matched Rva007E4B80Vp6Stream::update. When paused or
// throttled, the next frame wins only while it is still behind the clock.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
// Byte flag read by 0x007E4820 and 0x007E4B80 (VA 0x01309838); zero-filled in retail.
unsigned char g_01309838;

class Rva007E4820FrameClock
{
public:
    int frame(int flags);

private:
    char m_pad0[0x40];
    int m_scale;
    int m_denominator;
    int m_frame;
    int m_pad4c;
    int m_startTime;
};

int Rva007E4820FrameClock::frame(int flags)
{
    if (!g_01309838 && !(flags & 0x44))
        return (int)((__int64)((int)timeGetTime() - m_startTime) * m_scale
            / m_denominator / 1000);

    int scale = m_scale;
    if (flags & 0x800000)
        scale >>= 1;

    int now = (int)timeGetTime();
    __int64 wide = scale;
    if (m_frame + 1 < (int)((__int64)(now - m_startTime) * wide
            / m_denominator / 1000))
        return m_frame + 1;
    return (int)((__int64)((int)timeGetTime() - m_startTime) * wide
        / m_denominator / 1000);
}
