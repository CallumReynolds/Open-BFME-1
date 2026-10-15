extern int g_bfmeLeft1221;
extern int g_bfmeStateFA[625];
extern unsigned int *g_bfmeNext1221;
void __cdecl bfmeSeed(int seed);
#define hiBit1221(u)	((u) & 0x80000000U)
#define loBit1221(u)	((u) & 0x00000001U)
#define loBits1221(u)	((u) & 0x7FFFFFFFU)
#define mixBits1221(u, v)	(hiBit1221(u) | loBits1221(v))
// Open BFME 2: Code/GameEngine/Source/Common/BfmeReload1221.cpp
// _bfmeReload1221
extern "C" unsigned int bfmeReload1221(void)
{
	register unsigned int *p0 = (unsigned int *)g_bfmeStateFA;
	register unsigned int *p2 = (unsigned int *)g_bfmeStateFA + 2;
	register unsigned int *pM = (unsigned int *)g_bfmeStateFA + 397;
	register unsigned int s0, s1;
	register int j;
	if (g_bfmeLeft1221 < -1)
		bfmeSeed(4357);
	g_bfmeLeft1221 = 624 - 1;
	g_bfmeNext1221 = (unsigned int *)g_bfmeStateFA + 1;
	for (s0 = g_bfmeStateFA[0], s1 = g_bfmeStateFA[1], j = 624 - 397 + 1; --j; s0 = s1, s1 = *p2++)
		*p0++ = *pM++ ^ (mixBits1221(s0, s1) >> 1) ^ (loBit1221(s1) ? 0x9908B0DFU : 0U);
	for (pM = (unsigned int *)g_bfmeStateFA, j = 397; --j; s0 = s1, s1 = *p2++)
		*p0++ = *pM++ ^ (mixBits1221(s0, s1) >> 1) ^ (loBit1221(s1) ? 0x9908B0DFU : 0U);
	s1 = g_bfmeStateFA[0];
	unsigned int y = g_bfmeStateFA[0];
	*p0 = *pM ^ (mixBits1221(s0, s1) >> 1) ^ (loBit1221(s1) ? 0x9908B0DFU : 0U);
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9D2C5680U;
	y ^= (y << 15) & 0xEFC60000U;
	return y ^ (y >> 18);
}
