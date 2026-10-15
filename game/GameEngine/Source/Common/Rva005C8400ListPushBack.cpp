// cl: /DNDEBUG /MD /EHsc
// experiment: retail 0x005C8400 (69 bytes)
namespace _STL
{
	// STLport's node allocator entry point is the private
	// _STL::__node_alloc<true, 0>::_M_allocate (retail 0x0082E540); this
	// TU-local helper reaches it under its real name.
	static void *nodePoolAllocate(unsigned int bytes);
	template <bool __threads, int __inst>
	class __node_alloc
	{
		friend void *nodePoolAllocate(unsigned int);
		static void *__cdecl _M_allocate(unsigned int __n);
	};
	static inline void *nodePoolAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }

	template <typename T>
	void _Construct(T *p, const T &val);
}

struct Rva005C6730Value
{
	void release();

	int m_id;
	unsigned char m_pad[8];
};

struct Rva005C6730Node
{
	Rva005C6730Node *m_next;
	Rva005C6730Node *m_prev;
	Rva005C6730Value m_value;
};

class Rva005C6730List
{
public:
	void pushBack(const Rva005C6730Value &value);

	unsigned char m_head[0x80];
	Rva005C6730Node *m_sentinel;
	unsigned char m_mid[8];
	int m_count;
};

void Rva005C6730List::pushBack(const Rva005C6730Value &value)
{
	Rva005C6730Node *sentinel = m_sentinel;
	Rva005C6730Node *node = (Rva005C6730Node *)_STL::nodePoolAllocate(0x14);
	_STL::_Construct(&node->m_value, value);

	Rva005C6730Node *last = sentinel->m_prev;
	node->m_next = sentinel;
	node->m_prev = last;
	last->m_next = node;
	sentinel->m_prev = node;

	m_count++;
}
