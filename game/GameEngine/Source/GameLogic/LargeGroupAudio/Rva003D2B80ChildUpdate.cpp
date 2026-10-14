// cl: /DNDEBUG /MD /EHsc

struct Rva003D2B80Source
{
	char m_pad00[0x0c];
	volatile float m_step;
};

struct Rva003D1380Elem;

struct Rva003D2B80Coord
{
	float m_x;
	float m_y;

	Rva003D2B80Coord(void) throw() {}
	Rva003D2B80Coord(const Rva003D2B80Coord &that) throw()
		: m_x(that.m_x), m_y(that.m_y) {}
	~Rva003D2B80Coord(void) throw() {}
};

class Y1SlotArray
{
public:
	Rva003D1380Elem *m_slot[8];
};

class Rva003CBA90
{
public:
	char m_lead[0x0c];
	void *m_owned;
	Rva003D1380Elem *m_slot[8];
	int m_pad30;
	int m_extra;
	unsigned char m_refCount;
	unsigned char m_nullCount;
	__declspec(noinline) void setSlots(Y1SlotArray *incoming);
};

struct Rva003D1380Elem
{
	float m_x;
	float m_y;
	char m_pad08[0x08];
	char m_body10[0x2c];
};

class Rva003D2B80Child
{
public:
	char m_pad00[0x08];
	Rva003D1380Elem *m_begin;
	Rva003D1380Elem *m_end;
	Rva003D1380Elem *m_capacity;
	Rva003D2B80Source *m_source;

	Rva003D1380Elem *lookup(const Rva003D2B80Coord point);
	void update(Rva003D2B80Child *first, Rva003D2B80Child *second,
		Rva003D2B80Child *third);
};

// ?update@Rva003D2B80Child@@QAEXPAV1@00@Z
void Rva003D2B80Child::update(Rva003D2B80Child *first,
	Rva003D2B80Child *second, Rva003D2B80Child *third)
{
	float half = m_source->m_step;
	Rva003D1380Elem *entry = m_begin;
	if (entry != m_end)
	{
		half *= 0.5f;
		do
		{
			Y1SlotArray slots;
			Rva003D2B80Coord point;
			point.m_x = entry->m_x + half;
			point.m_y = entry->m_y;
			slots.m_slot[0] = first->lookup(point);
			point.m_x = entry->m_x - half;
			slots.m_slot[1] = first->lookup(point);
			point.m_x = entry->m_x;
			point.m_y = entry->m_y + half;
			slots.m_slot[2] = second->lookup(point);
			point.m_y = entry->m_y - half;
			slots.m_slot[3] = second->lookup(point);
			point.m_x = entry->m_x + half;
			point.m_y = entry->m_y + half;
			slots.m_slot[4] = third->lookup(point);
			point.m_y = entry->m_y - half;
			slots.m_slot[5] = third->lookup(point);
			point.m_x = entry->m_x - half;
			// the (-x,-y) sample fills slot 7 and the (-x,+y) sample slot 6
			slots.m_slot[7] = third->lookup(point);
			point.m_y = entry->m_y + half;
			slots.m_slot[6] = third->lookup(point);
			((Rva003CBA90 *)entry)->setSlots(&slots);
			++entry;
		} while (entry != m_end);
	}
}

// ?setSlots@Rva003CBA90@@QAEXPAVY1SlotArray@@@Z
// The caller needs the complete helper visible for its schedule; this is the only definition.
inline void Rva003CBA90::setSlots(Y1SlotArray *incoming)
{
	m_nullCount = 0;
	if (incoming->m_slot[0] == 0) ++m_nullCount;
	m_slot[0] = incoming->m_slot[0];
	if (incoming->m_slot[1] == 0) ++m_nullCount;
	m_slot[1] = incoming->m_slot[1];
	if (incoming->m_slot[2] == 0) ++m_nullCount;
	m_slot[2] = incoming->m_slot[2];
	if (incoming->m_slot[3] == 0) ++m_nullCount;
	m_slot[3] = incoming->m_slot[3];
	if (incoming->m_slot[4] == 0) ++m_nullCount;
	m_slot[4] = incoming->m_slot[4];
	if (incoming->m_slot[5] == 0) ++m_nullCount;
	m_slot[5] = incoming->m_slot[5];
	if (incoming->m_slot[6] == 0) ++m_nullCount;
	m_slot[6] = incoming->m_slot[6];
	if (incoming->m_slot[7] == 0) ++m_nullCount;
	m_slot[7] = incoming->m_slot[7];
}
