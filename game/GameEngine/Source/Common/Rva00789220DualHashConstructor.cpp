// cl: /DNDEBUG /MD /EHsc /O2
// 0x00789220 -- copy the leading string-like base and initialize two
// 100-bucket hash containers.

class Rva00789220Base
{
public:
	Rva00789220Base(void *source);
	~Rva00789220Base();
	void *m_table;
};

// The retail unwind map destroys this storage at vector+4 while a vector
// is still being constructed (funclets 0x00C51008/0x00C5101E), so it is a
// member after a leading dword rather than a base at +0.
class Rva00789220VectorStorage
{
public:
	Rva00789220VectorStorage()
	{
		m_begin = 0;
		m_end = 0;
	}
	~Rva00789220VectorStorage();

	void * volatile m_begin;
	void * volatile m_end;
};

class Rva00789220VectorA
{
public:
	Rva00789220VectorA(unsigned int count)
	{
		m_capacityEnd = 0;
		m_extra = 0;
		bfmeReserve(count);
	}
	~Rva00789220VectorA();
	void bfmeReserve(unsigned int count);

	void *m_pad00;
	Rva00789220VectorStorage m_storage;
	void * volatile m_capacityEnd;
	void *m_extra;
};

class Rva00789220VectorB
{
public:
	Rva00789220VectorB(unsigned int count)
	{
		void * volatile *capacityEnd = &m_capacityEnd;
		*capacityEnd = 0;
		m_extra = 0;
		bfmeReserve(count);
	}
	void bfmeReserve(unsigned int count);

	void *m_pad00;
	Rva00789220VectorStorage m_storage;
	void * volatile m_capacityEnd;
	void *m_extra;
};

class Rva00789220Holder : public Rva00789220Base
{
public:
	Rva00789220Holder(void *source);
	int m_value04;
	Rva00789220VectorA m_first;
	Rva00789220VectorB m_second;
};

// @??0Rva00789220Holder@@QAE@PAX@Z 0x00789220
Rva00789220Holder::Rva00789220Holder(void *source) :
	Rva00789220Base(source),
	m_value04(0),
	m_first(100),
	m_second(100)
{
}
