// cl: /Od /Ob1

struct Rva0082C6E0Value
{
	unsigned long m_value;
};

struct Rva0082C6E0FalseType
{
};

// BFME2 uses STLport's real helper here; BFME1 erase independently calls
// the same 41-byte trivial-copy implementation through ILT 0x00018179 -> 0x00065E30.
namespace _STL
{
	void *__cdecl __copy_trivial(const void *first, const void *last, void *result);
}

inline Rva0082C6E0Value *rva0082C6E0CopyPointers(
	Rva0082C6E0Value *first,
	Rva0082C6E0Value *last,
	Rva0082C6E0Value *result,
	const Rva0082C6E0FalseType & )
{
	return (Rva0082C6E0Value *)_STL::__copy_trivial(first, last, result);
}

inline void rva0082C6E0Destroy( Rva0082C6E0Value * )
{
}

class Rva0082C6E0Vector
{
public:
	Rva0082C6E0Value *erase( Rva0082C6E0Value *position );

private:
	Rva0082C6E0Value *end()
	{
		return m_finish;
	}

	Rva0082C6E0Value *m_start;
	Rva0082C6E0Value *m_finish;
	Rva0082C6E0Value *m_capacity;
};

Rva0082C6E0Value *Rva0082C6E0Vector::erase( Rva0082C6E0Value *position )
{
	if ( position + 1 != end() )
	{
		rva0082C6E0CopyPointers(
			position + 1, m_finish, position, Rva0082C6E0FalseType() );
	}

	--m_finish;
	rva0082C6E0Destroy( m_finish );
	return position;
}
