// ?unlinkAfterQuery@BfmeQuery1279@@QAEXPAURva008BD760Node@@@Z
// partial score=0.4085 date=2026-10-15
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
struct Rva008BD760Node
{
	char m_padding00[0x54];
	Rva008BD760Node *m_prev;
	Rva008BD760Node *m_next;
};

class BfmeQuery1279
{
public:
	void bfmeQuery1279(void *key, int name, void **previousResult, void **nodeResult);
	void unlinkAfterQuery(Rva008BD760Node *node);

	void *find(void *key)
	{
		void *previous;
		bfmeQuery1279(key, 0, &previous, &key);
		return key;
	}
};

static __forceinline Rva008BD760Node *unlinkFoundNode(Rva008BD760Node *found)
{
    if (found->m_prev) found->m_prev->m_next = found->m_next;
    if (found->m_next) found->m_next->m_prev = found->m_prev;
    memset(&found->m_prev, 0, sizeof(found->m_prev) + sizeof(found->m_next));
    return found;
}

// Open BFME 2: Code/Libraries/Source/Apt/AptDisplayList.cpp.
void BfmeQuery1279::unlinkAfterQuery(Rva008BD760Node *node)
{
    void *previous;
    bfmeQuery1279(node, 0, &previous, (void **)&node);
    unlinkFoundNode(node);
}
