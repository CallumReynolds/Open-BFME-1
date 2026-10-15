// cl: /O2
// Return nested +0x101 text, falling back to virtual slot 7 on its optional source.
struct Rva007EA970Source
{
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6();
    virtual char *fallback();
};

struct Rva007EA970Inner
{
    char m_pad0[12];
    Rva007EA970Source *m_source;
    char m_pad10[0xF1];
    char m_text[1];
};

struct Rva007EA970Owner
{
    int m_reserved;
    Rva007EA970Inner *m_inner;
    char *getText();
};

char *Rva007EA970Owner::getText()
{
    Rva007EA970Inner *inner = m_inner;
    char *local = inner->m_text;
    if (*local)
        return local;
    return inner->m_source ? inner->m_source->fallback() : 0;
}

struct Rva007EA9A0Source
{
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7();
    virtual int fallback();
};

struct Rva007EA9A0Inner
{
    char m_pad0[12];
    Rva007EA9A0Source *m_source;
    char m_pad10[0x228 - 0x10];
    int m_value;
};

struct Rva007EA9A0Owner
{
    int m_reserved;
    Rva007EA9A0Inner *m_inner;
    int getValue();
};

// Open BFME 2: Code/GameEngine/Source/GameNetwork/Rva007EA970TextFallback.cpp
// ?getValue@Rva007EA9A0Owner@@QAEHXZ
int Rva007EA9A0Owner::getValue()
{
    Rva007EA9A0Inner *inner = m_inner;
    int value = inner->m_value;
    if (value)
        return value;
    return inner->m_source ? inner->m_source->fallback() : 0;
}
