// ?Rva00894380@@YAXXZ
// partial score=0.8297 date=2026-10-15
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include <string.h>
typedef unsigned int UnsignedInt;

struct StringBlock00894380 { unsigned short refs, length, capacity, flags; char text[1]; };
struct StringPool00894380 { void *unused; void (__cdecl *free)(void *); };
struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class BfmeStrVKI {
public:
	BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
	void bfmeSetVKI(const char *);
	~BfmeStrVKI() { StringBlock00894380 *p = m_block; if (--p->refs == 0) ((StringPool00894380 *)g_bfmeStringPool1284)->free(p); }
	StringBlock00894380 *m_block;
};

struct Item00894380 { StringBlock00894380 *m_00; UnsignedInt kind; };
class List00894380
{
public:
	volatile UnsignedInt count;
	UnsignedInt m_04;
	Item00894380 *volatile items;
	void rva008941A0(const BfmeStrVKI &name);
	__forceinline bool allSettled() {
        struct State00894380 { Item00894380 *p, *end; UnsignedInt bytes; } s;
        s.p = items;
        s.bytes = count * sizeof(Item00894380);
        s.end = s.p;
        s.end = (Item00894380 *)((char *)s.end + s.bytes);
        for (; s.p != s.end; ++s.p, s.end = (Item00894380 *)((char *)items + s.bytes))
            if (s.p->kind != 4 && s.p->kind != 2) return false;
        return true;
    }
	__forceinline bool allSettled(int) {
        union End00894380 { Item00894380 *p; unsigned int bits : 32; };
        struct State00894380 { Item00894380 *p; End00894380 end; UnsignedInt bytes; } s;
        s.p = items;
        s.bytes = count * sizeof(Item00894380);
        s.end.p = s.p;
        s.end.bits += s.bytes;
        for (; s.p != s.end.p; ++s.p, s.end.p = items, s.end.bits += s.bytes) {
            if (s.p->kind != 4 && s.p->kind != 2) return false;
        }
        return true;
    }
};

class BfmeJ1017 { public: void bfmeInsert(UnsignedInt word); };
class BfmeTracker4310 { public: void rva00896710(); };

struct Record00894380 { int value; int kind; };

extern char *Rva008A5380Holder;          // 0x013377D8
extern int g_bfme1017I;                  // 0x013377DC stream base
extern int g_013377E0;          // stream cursor
extern int g_013377E4;                   // stream length
extern int g_013377EC;           // current frame
extern List00894380 *g_013377F0;
extern BfmeTracker4310 *g_013377F8;
extern int g_rva00891FA0Ready;
extern int g_rva00891FA0Value;
extern void (__cdecl *g_bfmeSlot06VB)(void);
extern void (__cdecl *g_bfmeSlot05VB)(void);
static __forceinline void Rva00891FA0SendText(const char *text) {
    ((void (__cdecl *)(const char *))g_bfmeSlot06VB)(text);
}
static __forceinline void Rva00891FA0SendRecord(Record00894380 *record, int size) {
    ((void (__cdecl *)(Record00894380 *, int))g_bfmeSlot05VB)(record, size);
}
extern "C" int __cdecl sprintf(char *, const char *, ...);


#define cursor00894380() ((unsigned char *&)g_013377E0)

struct Flags00894380 {
    union { UnsignedInt m_04; struct { UnsignedInt m_kind6 : 6; UnsignedInt m_bits6 : 9; UnsignedInt m_valid15 : 1; }; };
    bool isSettledKind() const {
        bool invalid = !m_valid15;
        if (m_kind6 == 0x12 && !invalid)
            return true;
        return false;
    }
};

struct Value00894380
{
	void *m_vtbl;
	union { UnsignedInt m_04; struct { UnsignedInt m_kind6 : 6; UnsignedInt m_bits6 : 9; UnsignedInt m_valid15 : 1; }; };
	char m_08[0x48];
	struct Output00892A70 *m_50;
	bool isSettledKind() const {
        bool invalid = !m_valid15;
        if (m_kind6 == 0x12 && !invalid)
            return true;
        return false;
    }
};
struct Owner00894380 { char m_00[0x58]; Value00894380 *m_58; };


struct Nested00892A70 { char m_00[0x24]; UnsignedInt m_24; };
struct Output00892A70 {
    char m_00[0xc];
    Nested00892A70 *m_0c;
    char m_10[0x20];
    UnsignedInt m_30;
};
class Rva008A15F0 { public: void method(int frames); };
class BfmeFilterWalk1236 { public: void bfmeFilterWalk1236(); };
class Rva008A1940Queue { public: void flush(); };
class BfmeSlotDispatcher1281 { public: void bfmeFlushSlots1289(); };

extern char *g_bfmeHolderBU;
extern BfmeTracker4310 *g_bfmeTracker4310;
extern void d_008a15f0();
extern void d_00896710();
class Rva008A15F0Call { public: void method(int); };
class Rva00896710Call { public: void method(); };
typedef void (Rva00896710Call::*TrackerCall)();
typedef void (Rva008A15F0Call::*TimerCall)(int);
template<class T> T memberCall(void (*p)()) { union {void (*plain)(); T member;} call; call.plain = p; return call.member; }
struct Rva00892A70Interval { char pad[0x24]; unsigned interval; };
struct Rva00894660Value
{
    void *vptr;
    union { unsigned flags; struct { unsigned kind:6; unsigned rest:26; }; };
    bool isUndefined() const { return ((flags >> 15) & 1) == 0; }
    char pad08[0x48];
    Output00892A70 *state;
};
struct Rva00894660Node { char pad[0x58]; Rva00894660Value *value; };
struct Rva00894660Root { char pad[0x122c]; Rva00894660Node **nodes; char pad1230[8]; int count; };
__forceinline Rva00894660Value *currentRva00894660Value() { return (*((Rva00894660Root *)g_bfmeHolderBU)->nodes)->value; }
__forceinline bool isTickAnimation(Rva00894660Value *value) { return value->kind == 0x12 && !value->isUndefined(); }
// ?Rva00892A70@@YAHI@Z
// Open BFME 2: Code/Libraries/Source/Apt/Apt.cpp.
static int Rva00892A70(unsigned elapsed)
{
    int advanced = 0;
    if (!isTickAnimation(currentRva00894660Value())) return advanced;
    Output00892A70 *state = currentRva00894660Value()->state;
    elapsed += state->m_30;
    unsigned interval = state->m_0c->m_24;
    while (elapsed >= interval)
    {
        (((Rva008A15F0Call *)g_bfmeHolderBU)->*memberCall<TimerCall>(d_008a15f0))(interval);
        ((BfmeFilterWalk1236 *)&((Rva00894660Root *)g_bfmeHolderBU)->nodes)->bfmeFilterWalk1236();
        ((Rva008A1940Queue *)g_bfmeHolderBU)->flush();
        ((BfmeSlotDispatcher1281 *)g_bfmeHolderBU)->bfmeFlushSlots1289();
        (((Rva00896710Call *)g_bfmeTracker4310)->*memberCall<TrackerCall>(d_00896710))();
        elapsed -= interval;
        g_rva00891FA0Value += interval;
        advanced = 1;
        if (!isTickAnimation(currentRva00894660Value())) return advanced;
        if (g_rva00891FA0Ready) break;
    }
    if (isTickAnimation(currentRva00894660Value())) currentRva00894660Value()->state->m_30 = elapsed;
    return advanced;
}

extern void d_008941a0();
typedef void (List00894380::*ListCall00894380)(const BfmeStrVKI &);
inline void List00894380::rva008941A0(const BfmeStrVKI &name) {
    (this->*memberCall<ListCall00894380>(d_008941a0))(name);
}
inline void BfmeTracker4310::rva00896710() {
    (((Rva00896710Call *)this)->*memberCall<TrackerCall>(d_00896710))();
}
void Rva00894380()
{
	UnsignedInt frame = g_013377EC;
	UnsignedInt stop = frame + 1;
	if (!g_bfme1017I)
		return;

	do
	{
		if (frame == stop)
			break;
		List00894380 *list = g_013377F0;
		if (list->allSettled())
		{
			while (*(UnsignedInt *)cursor00894380() <= frame)
			{
				bool reload = true;
				unsigned char *cursor = cursor00894380() += 4;
				switch (*(unsigned char *)cursor & 3)
				{
				case 0:
				case 1:
				{
					UnsignedInt word = *(UnsignedInt *)cursor;
					cursor00894380() = cursor + 4;
					((BfmeJ1017 *)Rva008A5380Holder)->bfmeInsert(word);
					break;
				}
				case 2:
				{
					++cursor00894380();
					char *text = (char *)cursor00894380();
					cursor00894380() += strlen(text) + 1;
					BfmeStrVKI name(text);
					g_013377F0->rva008941A0(name);
					break;
				}
				case 3:
					cursor00894380() = (unsigned char *)((char *)cursor + 1);
					if (!g_rva00891FA0Ready)
					{
						char buffer[16];
						sprintf(buffer, "%06d", frame);
						Rva00891FA0SendText(buffer);
					}
					else
						reload = false;
					break;
				}
				if (reload)
					list = g_013377F0;
				frame = g_013377EC;
			}
		}

		if ((int)((char *)cursor00894380() - (char *)g_bfme1017I) >= g_013377E4)
		{
			g_bfme1017I = 0;
			cursor00894380() = 0;
			if (g_rva00891FA0Ready)
				g_rva00891FA0Ready = 0;
			return;
		}

		if (!list->allSettled(0))
			goto flush;
		{
			Value00894380 *value = (**(Owner00894380 ***)(Rva008A5380Holder + 0x122c))->m_58;
			if (!value || !value->isSettledKind())
				goto flush;
		}

		if (Rva00892A70(1) && g_rva00891FA0Ready)
		{
			char buffer[16];
			sprintf(buffer, "%06d", g_rva00891FA0Value);
			Rva00891FA0SendText(buffer);
			Record00894380 record;
			record.value = g_rva00891FA0Value;
			record.kind = 3;
			Rva00891FA0SendRecord(&record, 5);
		}

		frame = ++g_013377EC;
	} while (g_bfme1017I);
	return;

flush:
	g_013377F8->rva00896710();
}
