class BfmeOwnerCDE
{
public:
	void bfmeOneCDE(void *what);
};

class BfmeThingCDE
{
public:
	void bfmeDtorCDE();
	void bfmeGoCDE();
	BfmeOwnerCDE *m_bfmeOwner;
	void *m_bfmePtr;
};


void BfmeThingCDE::bfmeGoCDE()
{
	if (m_bfmePtr != 0)
	{
		m_bfmeOwner->bfmeOneCDE(m_bfmePtr);
		return;
	}
	bfmeDtorCDE();
	::operator delete(this);
}
