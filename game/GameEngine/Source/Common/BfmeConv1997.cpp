extern const char g_Rva0107301CEmptyString[];

struct BfmeHdrVKI
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPoolVKI
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
	void __declspec(nothrow) bfmeSetVKI(const char *text);
	~BfmeStrVKI()
	{
		BfmeHdrVKI *data = m_data;
		if (--data->m_refCount == 0)
			(*(BfmeStringPoolVKI **)&g_rva01337A30AllocPair)->free(data);
	}
	BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		other.m_data->m_refCount++;

		BfmeHdrVKI *old = m_data;
		if (--old->m_refCount == 0)
			(*(BfmeStringPoolVKI **)&g_rva01337A30AllocPair)->free(old);

		m_data = other.m_data;
		return *this;
	}

	BfmeHdrVKI *m_data;
};

void bfmeApplyEVF(void *ctx, BfmeStrVKI *text, int flag);

void bfmeResetEVF(void *ctx, BfmeStrVKI *text)
{
	*text = g_Rva0107301CEmptyString;

	bfmeApplyEVF(ctx, text, 1);
}
