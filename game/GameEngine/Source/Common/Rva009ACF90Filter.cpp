// cl: /O2 /G6 /DNDEBUG /MD
struct Rva009ACF90Context
{
	unsigned char m_pad00[0x24];
	unsigned int *m_tableIndex;
	int *m_variance;
};

// Ported from Open BFME 2 Code/Libraries/Source/VP6/DeblockLoopFilteredBandC.cpp.
// ?filterBand009ACF90@@YAXPAURva009ACF90Context@@PAE1IIIPBI@Z
void __cdecl filterBand009ACF90(Rva009ACF90Context *context,
	unsigned char *source, unsigned char *destination, unsigned int stride,
	unsigned int width, unsigned int first, const unsigned int *scale)
{
	unsigned int current;
	int x[10];
	int sum1, sum2, variance1, variance2, running;
	int q, limit;
	int left, right;
	unsigned int row;
	unsigned char *src, *dst;
	current = first;
	int step1 = stride;
	int step2 = 2 * stride;
	int step3 = 3 * stride;
	int step4 = 4 * stride;
	int step5 = 5 * stride;
	for (; current < first + width; ++current) {
		src = source + 8 * (current - first);
		q = scale[context->m_tableIndex[current + width]];
		limit = (q * q * 3) >> 5;
		dst = destination + 8 * (current - first);
		for (row = 0; row < 8; ++row) {
			x[1] = src[-step4];
			x[2] = src[-step3];
			x[3] = src[-step2];
			x[4] = src[-step1];
			x[5] = src[0];
			x[6] = src[stride];
			x[7] = src[step2];
			x[8] = src[step3];
			sum1 = sum2 = variance1 = variance2 = 0;
			for (unsigned int k = 1; k <= 4; ++k) {
				sum1 += x[k];
				variance1 += x[k] * x[k];
				sum2 += x[k + 4];
				variance2 += x[k + 4] * x[k + 4];
			}
			variance1 -= ((sum1 + 1) >> 1) * (sum1 >> 1);
			variance2 -= ((sum2 + 1) >> 1) * (sum2 >> 1);
			context->m_variance[current] += variance1;
			context->m_variance[current + width] += variance2;
			if (variance1 < limit && variance2 < limit && x[5] - x[4] < q && x[4] - x[5] < q) {
				if (((src[-step4] - src[-step5]) > 0 ? (src[-step4] - src[-step5]) : (src[-step5] - src[-step4])) < q) left = src[-step5];
				else left = src[-step4];
				if (((src[step3] - src[step4]) > 0 ? (src[step3] - src[step4]) : (src[step4] - src[step3])) < q) right = src[step4];
				else right = src[step3];
				running = x[4] + 3*left + x[3] + x[2] + 4 + x[1];
				dst[-step4] = (unsigned char)(((running+x[1])*2-x[4]+x[5])>>4);
				running += x[5]-left;
				dst[-step3] = (unsigned char)(((running+x[2])*2-x[5]+x[6])>>4);
				running += x[6]-left;
				dst[-step2] = (unsigned char)(((running+x[3])*2-x[6]+x[7])>>4);
				running += x[7]-left;
				dst[-(int)stride] = (unsigned char)(((running+x[4])*2-x[7]-x[1]+left+x[8])>>4);
				running += x[8]-x[1];
				dst[0] = (unsigned char)(((running+x[5])*2-x[8]-x[2]+right+x[1])>>4);
				running += right-x[2];
				dst[stride] = (unsigned char)(((running+x[6])*2-x[3]+x[2])>>4);
				running += right-x[3];
				dst[step2] = (unsigned char)(((running+x[7])*2-x[4]+x[3])>>4);
				dst[step3] = (unsigned char)(((running+right+x[8])*2-x[5] - x[4])>>4);
			} else {
				dst[-step4] = src[-step4];
				dst[-step3] = src[-step3];
				dst[-step2] = src[-step2];
				dst[-(int)stride] = src[-(int)stride];
				dst[0] = src[0];
				dst[stride] = src[stride];
				dst[step2] = src[step2];
				dst[step3] = src[step3];
			}
			src++;
			dst++;
		}
	}
	for (current = first; current < first + width - 1; ++current) {
		q = scale[context->m_tableIndex[current + 1]];
		limit = (q * q * 3) >> 5;
		src = dst = destination - 8 * stride + 8 * (current - first + 1);
		for (row = 0; row < 8; ++row) {
			x[1] = src[-4];
			x[2] = src[-3];
			x[3] = src[-2];
			x[4] = src[-1];
			x[5] = src[0];
			x[6] = src[1];
			x[7] = src[2];
			x[8] = src[3];
			sum1 = sum2 = variance1 = variance2 = 0;
			for (unsigned int k = 1; k <= 4; ++k) {
				sum1 += x[k];
				variance1 += x[k] * x[k];
				sum2 += x[k + 4];
				variance2 += x[k + 4] * x[k + 4];
			}
			variance1 -= ((sum1 + 1) >> 1) * (sum1 >> 1);
			variance2 -= ((sum2 + 1) >> 1) * (sum2 >> 1);
			context->m_variance[current] += variance1;
			context->m_variance[current + 1] += variance2;
			if (variance1 < limit && variance2 < limit && x[5] - x[4] < q && x[4] - x[5] < q) {
				if (((src[-4] - src[-5]) > 0 ? (src[-4] - src[-5]) : (src[-5] - src[-4])) < q) left = src[-5];
				else left = src[-4];
				if (((src[3] - src[4]) > 0 ? (src[3] - src[4]) : (src[4] - src[3])) < q) right = src[4];
				else right = src[3];
				running = x[4] + 3*left + x[3] + x[2] + 4 + x[1];
				dst[-4] = (unsigned char)(((running+x[1])*2-x[4]+x[5])>>4);
				running += x[5]-left;
				dst[-3] = (unsigned char)(((running+x[2])*2-x[5]+x[6])>>4);
				running += x[6]-left;
				dst[-2] = (unsigned char)(((running+x[3])*2-x[6]+x[7])>>4);
				running += x[7]-left;
				dst[-1] = (unsigned char)(((running+x[4])*2-x[7]-x[1]+left+x[8])>>4);
				running += x[8]-x[1];
				dst[0] = (unsigned char)(((running+x[5])*2-x[8]-x[2]+right+x[1])>>4);
				running += right-x[2];
				dst[1] = (unsigned char)(((running+x[6])*2-x[3]+x[2])>>4);
				running += right-x[3];
				dst[2] = (unsigned char)(((running+x[7])*2-x[4]+x[3])>>4);
				dst[3] = (unsigned char)(((running+right+x[8])*2-x[5] - x[4])>>4);
			}
			src += stride;
			dst += stride;
		}
	}
}
