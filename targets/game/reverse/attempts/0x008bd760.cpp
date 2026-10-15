// ?unlinkAfterQuery@BfmeQuery1279@@QAEXPAURva008BD760Node@@@Z
// partial score=0.0423 date=2026-10-15
// ?unlinkAfterQuery@BfmeQuery1279@@QAEXPAURva008BD760Node@@@Z
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

void BfmeQuery1279::unlinkAfterQuery(Rva008BD760Node *node)
{
	Rva008BD760Node *found = (Rva008BD760Node *)find(node);
	if (found->m_prev != 0)
		found->m_prev->m_next = found->m_next;
	if (found->m_next != 0)
		found->m_next->m_prev = found->m_prev;
	found->m_prev = 0;
	found->m_next = 0;
}
