struct Rva009F4900Stage
{
    unsigned int v;
    int r;
    // ??0Rva009F4900Stage@@QAE@IH@Z absent-from-retail
    Rva009F4900Stage(unsigned int value, int result) : v(value), r(result) {}
};
// ?step16_009F4900@@YA?AURva009F4900Stage@@U1@@Z absent-from-retail
static __forceinline Rva009F4900Stage step16_009F4900(Rva009F4900Stage s)
{
    if (s.v & 0xffff0000) {
        s.v >>= 16;
        s.r = 16;
    }
    return s;
}
struct Gen009F5040Item;

// Independently matched overlapping receiver views, both called without a
// receiver adjustment. These declarations do not assert inheritance.
class BfmeHostER
{
public:
	unsigned int bfmeIndexER(float value);
};
class BfmeHostES
{
public:
	unsigned int bfmeIndexES(float value);
};

struct Gen009F4900Value0
{
	char m_pad00[0x10];
	float m_value10;
};
struct Gen009F4900Value1
{
	float m_value00;
	float m_value04;
};

struct Gen009F5040Node
{
	char m_pad00[4];
	Gen009F5040Item *m_item;
	char m_pad08[8];
	Gen009F5040Node **m_secondaryPreviousLink;
	Gen009F5040Node *m_secondaryNext;
	Gen009F5040Node **m_previousLink;
	Gen009F5040Node *m_next;
	volatile int m_index;
	int m_result24;
	int m_result28;
	int m_result2c;
};

struct Gen009F5040Item
{
	virtual void *getValue0();
	virtual void *getValue1();
	virtual void *getValue2();
	virtual void *getValue3();
	virtual void *getValue4();
	virtual void *getValue5();
	virtual void *getValue6();
	virtual int getIndex();
};

struct Gen009F5040Counter
{
	int m_value;
	Gen009F5040Node *m_head;
};

struct Gen009F5040Bucket
{
	Gen009F5040Counter *m_counter;
	int m_pad04;
	int m_pad08;
};

class Gen009F5040
{
public:
	void handle();
	__declspec(noinline) void calculate_009F4900(Gen009F5040Node *node,
		int *result28, int *result2c, int *result24);
	__declspec(noinline) void remove(Gen009F5040Node *node);
	void linkNode_009F4D80(Gen009F5040Node *node);

	Gen009F5040Bucket m_buckets[2];
	Gen009F5040Counter *m_rangeBegin;
	Gen009F5040Counter *m_rangeEnd;
	char m_pad20[0xcc];
	unsigned int m_mask;
	Gen009F5040Node *m_node;
};

// Keep the first getter view live across the second virtual call.
// ?calculate_009F4900@Gen009F5040@@QAEXPAUGen009F5040Node@@PAH11@Z
void Gen009F5040::calculate_009F4900(Gen009F5040Node *node,
	int *result28, int *result2c, int *result24)
{
	Gen009F4900Value0 *value0 = (Gen009F4900Value0 *)node->m_item->getValue0();
	Gen009F4900Value1 *value1 = (Gen009F4900Value1 *)node->m_item->getValue1();
	float value10 = value0->m_value10;
	*result28 = ((BfmeHostER *)this)->bfmeIndexER(value1->m_value00 - value10);
	*result2c = ((BfmeHostES *)this)->bfmeIndexES(value1->m_value04 - value10);
	unsigned int difference = ((BfmeHostER *)this)->bfmeIndexER(value10 + value1->m_value00) ^ *result28;
	difference |= ((BfmeHostES *)this)->bfmeIndexES(value10 + value1->m_value04) ^ *result2c;
	*result24 = difference;
	if (difference != 0) {
		Rva009F4900Stage state(difference, 0);
		state = step16_009F4900(state);
		unsigned int v = state.v;
		int r = state.r;
		if (v & 0xff00) { v >>= 8; r |= 8; }
		if (v & 0xf0) { v >>= 4; r |= 4; }
		if (v & 0xc) { v >>= 2; r |= 2; }
		if (v & 2) r |= 1;
		unsigned int mask = ~(1u << r);
		*result28 &= mask;
		*result2c &= mask;
	}
}
