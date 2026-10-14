// _bfmeReload1221
// partial score=0.7673 date=2026-10-14
// Open-BFME5 conversions.

extern int g_bfmeLeft1221;
extern unsigned int *g_bfmeNext1221;

extern int g_bfmeStateFA[];
extern void __cdecl bfmeSeed(int seed);

#define hiBit1221(u)       ((u) & 0x80000000U)
#define loBit1221(u)       ((u) & 0x00000001U)
#define loBits1221(u)      ((u) & 0x7FFFFFFFU)
#define mixBits1221(u, v)  (hiBit1221(u)|loBits1221(v))

// _bfmeReload1221
// Retail 0x008D3AE0 (281 bytes, ret at +0x118): the twist that refills all
// 624 words once the countdown runs out, then tempers and returns the first.
// It is the reload half of the Mersenne Twister generator whose draw is
// bfmeNext1221 below (seed 4357, N=624, M=397, K=0x9908B0DF), written in the
// pointer-walking form of the published generator.
extern "C" unsigned int bfmeReload1221(void)
{
	register unsigned int *p0 = (unsigned int *)g_bfmeStateFA;
	register unsigned int *p2 = (unsigned int *)g_bfmeStateFA + 2;
	register unsigned int *pM = (unsigned int *)g_bfmeStateFA + 397;
	register unsigned int s0, s1;
	register int j;

	if (g_bfmeLeft1221 < -1)
		bfmeSeed(4357);

	g_bfmeLeft1221 = 624 - 1, g_bfmeNext1221 = (unsigned int *)g_bfmeStateFA + 1;

	for (s0 = g_bfmeStateFA[0], s1 = g_bfmeStateFA[1], j = 624 - 397 + 1; --j; s0 = s1, s1 = *p2++)
		*p0++ = *pM++ ^ (mixBits1221(s0, s1) >> 1) ^ (loBit1221(s1) ? 0x9908B0DFU : 0U);

	for (pM = (unsigned int *)g_bfmeStateFA, j = 397; --j; s0 = s1, s1 = *p2++)
		*p0++ = *pM++ ^ (mixBits1221(s0, s1) >> 1) ^ (loBit1221(s1) ? 0x9908B0DFU : 0U);

	s1 = g_bfmeStateFA[0], *p0 = *pM ^ (mixBits1221(s0, s1) >> 1) ^ (loBit1221(s1) ? 0x9908B0DFU : 0U);
	s1 ^= (s1 >> 11);
	s1 ^= (s1 << 7) & 0x9D2C5680U;
	s1 ^= (s1 << 15) & 0xEFC60000U;
	return (s1 ^ (s1 >> 18));
}

unsigned int bfmeNext1221(void)
{
	unsigned int y;

	if (--g_bfmeLeft1221 < 0)
		return bfmeReload1221();

	y = *g_bfmeNext1221++;
	y ^= y >> 11;
	y ^= (y << 7) & 0x9d2c5680;
	y ^= (y << 15) & 0xefc60000;
	return y ^ (y >> 18);
}
