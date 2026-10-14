extern "C" unsigned char bfmeVftVH[];


class BfmeSubVH
{
public:
	virtual void bfmeReleaseVH(int what);
};

class BfmeThingVH
{
public:
	void *bfmeKillVH(int flags);
	void *m_bfmeVft;
	BfmeSubVH *m_bfmeSub;
};

void *BfmeThingVH::bfmeKillVH(int flags)
{
	BfmeSubVH *sub = m_bfmeSub;
	m_bfmeVft = bfmeVftVH;
	if (sub != 0)
		sub->bfmeReleaseVH(1);
	if ((flags & 1) != 0)
		::operator delete(this);
	return this;
}
