// cl: /Od
// Open-BFME5 conversions.

// BFME2 BfmeConv1155 calls this existing wrapper. BFME1 0x0082F7C0
// independently calls its 0x0082F1A0 body and consumes the pointer in EAX.
extern void __cdecl bfmeGoOV(void *first, void *last, void *setFirst, void *setLast);
typedef char *(__cdecl *BfmeSearch1155Fn)(char *, char *, const char *, const char *);

class BfmeS1155
{
public:
	unsigned int bfmeFind1155(const char *s, unsigned int pos, unsigned int n);
	char *m_bfme00;
	char *m_bfme04;
};

unsigned int BfmeS1155::bfmeFind1155(const char *s, unsigned int pos, unsigned int n)
{
	char *n1;
	const char *n2;
	const char *n3;

	if (pos > (unsigned int)(m_bfme04 - m_bfme00))
		return 0xffffffff;

	n2 = s;
	n3 = s + n;
	n1 = ((BfmeSearch1155Fn)bfmeGoOV)(m_bfme00 + pos, m_bfme04, n2, n3);
	return (n1 != m_bfme04) ? (unsigned int)(n1 - m_bfme00) : 0xffffffff;
}
