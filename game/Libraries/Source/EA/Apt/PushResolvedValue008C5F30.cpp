// Retail 0x008C5F30, 114 bytes (ret 4 at +0x44; the tag-4 arm sits after it
// and jumps back into the shared push, int3 padding follows +0x71).
//
// A __thiscall method that takes one Apt value and pushes it onto the
// receiver's value stack (count +0x00, array +0x08, the layout the matched
// AptActionInterpreter* bodies use).  A pooled value tagged 8 is replaced by
// the entry its +0x08 index selects in the +0x60 table; a pooled value tagged 4
// by the +0x58 table entry, or by g_bfmeFallbackDB when that entry is null.  The
// pushed value is AddRef'd unless its max-refcount bit is set, as in
// Bfme5PushInteger8C8120.cpp.  The type/pooled bitfield predicate is the one
// Rva008981E0AptTypeChecks.cpp matched.  No caller names the method, so the
// receiver keeps its address-derived name.
//
// Shape: each arm pushes on its own (MSVC cross-jumps the copies into one
// tail), which is what keeps the receiver in EAX and the value in ECX.

class AptValue
{
public:
	virtual void AddRef();

	int isPooledType(unsigned int type)
	{
		bool notPooled = !m_pooled;
		if (m_type == type && !notPooled)
			return 1;
		return 0;
	}

	union {
		unsigned int m_valueBits;
		struct {
			unsigned int m_type : 6;
			unsigned int m_bits06 : 9;
			unsigned int m_pooled : 1;
			unsigned int m_bits16 : 14;
			unsigned int m_maxRefCountHit : 1;
		};
	};
	int m_index;							// +0x08
};

extern AptValue *g_bfmeFallbackDB;

class Rva008C5F30Stack
{
public:
	void pushResolved(AptValue *value);

private:
	void push(AptValue *value)
	{
		m_values[m_count] = value;
		m_count++;
		bool maxRefCountHit = value->m_maxRefCountHit;
		if (!maxRefCountHit)
			value->AddRef();
	}

	int m_count;							// +0x00
	int m_capacity;							// +0x04
	AptValue **m_values;					// +0x08
	unsigned char m_unmodelled_0C[0x58 - 0x0C];
	AptValue **m_table58;					// +0x58
	unsigned char m_unmodelled_5C[0x60 - 0x5C];
	AptValue **m_table60;					// +0x60
};

// ?pushResolved@Rva008C5F30Stack@@QAEXPAVAptValue@@@Z
void Rva008C5F30Stack::pushResolved(AptValue *value)
{
	if (value->isPooledType(8))
	{
		push(m_table60[value->m_index]);
		return;
	}
	if (value->isPooledType(4))
	{
		AptValue *found = m_table58[value->m_index];
		if (found)
			push(found);
		else
			push(g_bfmeFallbackDB);
		return;
	}
	push(value);
}
