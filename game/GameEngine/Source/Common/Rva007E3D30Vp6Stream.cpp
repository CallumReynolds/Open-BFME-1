// ?decodeFrame@Rva007E3D30Vp6Stream@@QAEXXZ [retail body 0x007E3D30]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// VP6 stream: scan BfmeB996 packets for the next audio ('AV0K'/'AV0F')
// and video ('MV0K'/'MV0F') chunk and hand each to the 0x009A5800 decoder.
// Retail pushes five cdecl arguments to that decoder, whose matched body
// reads only the first three, so the call goes through a five-argument
// cast of the matched declaration.

class BfmeDev996;

class BfmeB996
{
public:
    char movePair(int *output, int *first, unsigned int *second,
        unsigned int limit);

private:
    char m_pad[4];
    BfmeDev996 *m_dev;
    int m_kind;
    int m_unused;
};

void Rva009A5800Forward(int, int, int);
typedef void (__cdecl *Rva009A5800Decode5)(int, char *, unsigned int, int, int);

extern void *g_Va01309840;
extern int g_Va0130983C;

class Rva007E3D30Vp6Stream
{
public:
    void decodeFrame(void);

private:
    char m_pad0[0x14];
    int m_videoOutput;
    int m_audioOutput;
    BfmeB996 m_reader;
    char m_pad2c[4];
    int m_width;
    int m_height;
    unsigned char m_audioEnabled;
    char m_pad39[3];
    int m_limit;
    char m_pad40[8];
    int m_frame;
    char m_pad4c[8];
    char *m_input;
    unsigned int m_inputLimit;
};

void Rva007E3D30Vp6Stream::decodeFrame(void)
{
    int first;
    unsigned int second;
    unsigned char audioEnabled = m_audioEnabled;

    g_Va01309840 = this;

    if (audioEnabled) {
        BfmeB996 *reader = &m_reader;
audioNext:
        if (!reader->movePair((int *)m_input, &first, &second, m_inputLimit))
            goto audioFailed;
        if (first != 0x4b305641 && first != 0x46305641)
            goto audioNext;
        ((Rva009A5800Decode5)Rva009A5800Forward)(m_audioOutput, m_input + 8,
            second, m_width, m_height);
    }

    {
        BfmeB996 *reader = &m_reader;
videoNext:
        char found = reader->movePair((int *)m_input, &first, &second, m_inputLimit);
        ++g_Va0130983C;
        if (!found)
            goto videoFailed;
        if (first != 0x4b30564d && first != 0x4630564d)
            goto videoNext;
        ((Rva009A5800Decode5)Rva009A5800Forward)(m_videoOutput, m_input + 8,
            second, m_width, m_height);
        ++m_frame;
        return;
    }

audioFailed:
    m_frame = m_limit - 1;
    return;

videoFailed:
    m_frame = m_limit - 1;
}
