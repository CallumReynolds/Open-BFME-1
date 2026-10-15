// _DeblockLoopFilteredBand_WMT_Rva009BFA40
// cl: /O2 /G6 /Z7 /MD
extern __declspec(align(16)) const unsigned short kRva012D87C0Three[8];
extern __declspec(align(16)) const unsigned short kRva012D87D0Four[8];
extern __declspec(align(16)) const unsigned short kRva012D8820One[8] = {
	1, 1, 1, 1, 1, 1, 1, 1
};

extern int *g_rva01356A9C;

struct Rva009BFA40Ctx
{
	unsigned char m_pad0[0x0c];
	int m_tableIndex;
	unsigned char m_pad1[0x24 - 0x10];
	unsigned int *m_fragmentQIndex;
	unsigned int *m_fragmentVariances;
};

// Ported from Open BFME 2 Code/Libraries/Source/VP6/DeblockNonFilteredBandWmt.cpp.
extern "C" void __cdecl DeblockLoopFilteredBand_WMT_Rva009BFA40(Rva009BFA40Ctx *ctx, unsigned char *source, unsigned char *destination, unsigned int stride, unsigned int count, int first, const unsigned int *limits)
{
	__declspec(align(16)) unsigned short lowerActivity[8];
	__declspec(align(16)) unsigned short upperActivity[8];
	unsigned char *dstRow;
	unsigned char *srcRow;
	__declspec(align(16)) unsigned short qv[8];
	__declspec(align(16)) unsigned short loopLimit[8];
	unsigned int q;
	__declspec(align(16)) unsigned short firstFiltered[8];
	__declspec(align(16)) unsigned short smoothLimit[8];
	__declspec(align(16)) unsigned short secondFiltered[8];
	__declspec(align(16)) unsigned short rows[80];
	unsigned char *edge;
	unsigned int index;
	unsigned int end;
	int limit;
	unsigned int s3;
	unsigned int s5;
	unsigned int s6;
	unsigned int s7;
	unsigned int p1;

	index = first;
	p1 = stride;
	limit = g_rva01356A9C[ctx->m_tableIndex];
	loopLimit[0] = (unsigned short)limit;
	loopLimit[1] = (unsigned short)limit;
	loopLimit[2] = (unsigned short)limit;
	loopLimit[3] = (unsigned short)limit;
	loopLimit[4] = (unsigned short)limit;
	loopLimit[5] = (unsigned short)limit;
	loopLimit[6] = (unsigned short)limit;
	loopLimit[7] = (unsigned short)limit;

	end = first + count;
	if (index < end) {
	do {
		srcRow = source + (index - first) * 8;
		dstRow = destination + (index - first) * 8;
		q = limits[ctx->m_fragmentQIndex[index + count]];
		__asm {
		push eax
		push ecx
		push edx
		push esi
		push edi
		mov eax, dword ptr q
		xor edx, edx
		mov ecx, stride
		pcmpeqw xmm6, xmm6
		movd mm5, eax
		psrlw xmm6, 0xe
		punpcklwd mm5, mm5
		mov eax, dword ptr srcRow
		punpckldq mm5, mm5
		sub edx, ecx
		movq2dq xmm5, mm5
		punpcklqdq xmm5, xmm5
		pmullw xmm6, xmm5
		movdqa xmmword ptr qv, xmm5
		lea edi, rows
		pxor xmm7, xmm7
		mov esi, dword ptr dstRow
		pmullw xmm6, xmm5
		lea eax, [eax+edx*4]
		lea esi, [esi+edx*2]
		psraw xmm6, 5
		movdqa xmmword ptr smoothLimit, xmm6
		movq xmm0, qword ptr [eax+edx]
		movq xmm1, qword ptr [eax]
		punpcklbw xmm0, xmm7
		punpcklbw xmm1, xmm7
		movdqa xmmword ptr [edi], xmm0
		movdqa xmmword ptr [edi+0x10], xmm1
		movq xmm2, qword ptr [eax+ecx]
		movq xmm3, qword ptr [eax+ecx*2]
		punpcklbw xmm2, xmm7
		punpcklbw xmm3, xmm7
		movdqa xmmword ptr [edi+0x20], xmm2
		movdqa xmmword ptr [edi+0x30], xmm3
		lea eax, [eax+ecx*4]
		movq xmm0, qword ptr [eax+edx]
		movq xmm1, qword ptr [eax]
		punpcklbw xmm0, xmm7
		punpcklbw xmm1, xmm7
		movdqa xmmword ptr [edi+0x40], xmm0
		movdqa xmmword ptr [edi+0x50], xmm1
		movq xmm2, qword ptr [eax+ecx]
		movq xmm3, qword ptr [eax+ecx*2]
		punpcklbw xmm2, xmm7
		punpcklbw xmm3, xmm7
		movdqa xmmword ptr [edi+0x60], xmm2
		movdqa xmmword ptr [edi+0x70], xmm3
		lea eax, [eax+ecx*4]
		movq xmm0, qword ptr [eax+edx]
		movq xmm1, qword ptr [eax]
		punpcklbw xmm0, xmm7
		punpcklbw xmm1, xmm7
		movdqa xmmword ptr [edi+0x80], xmm0
		movdqa xmmword ptr [edi+0x90], xmm1
		pcmpeqw xmm3, xmm3
		psllw xmm3, 0xf
		psrlw xmm3, 8
		movdqa xmm2, xmmword ptr [edi+0x10]
		movdqa xmm6, xmmword ptr [edi+0x50]
		psubw xmm2, xmm3
		psubw xmm6, xmm3
		movdqa xmm0, xmm2
		movdqa xmm4, xmm6
		pmullw xmm2, xmm2
		pmullw xmm6, xmm6
		movdqa xmm1, xmm2
		movdqa xmm5, xmm6
		movdqa xmm2, xmmword ptr [edi+0x20]
		movdqa xmm6, xmmword ptr [edi+0x60]
		psubw xmm2, xmm3
		psubw xmm6, xmm3
		paddw xmm0, xmm2
		paddw xmm4, xmm6
		pmullw xmm2, xmm2
		pmullw xmm6, xmm6
		paddw xmm1, xmm2
		paddw xmm5, xmm6
		movdqa xmm2, xmmword ptr [edi+0x30]
		movdqa xmm6, xmmword ptr [edi+0x70]
		psubw xmm2, xmm3
		psubw xmm6, xmm3
		paddw xmm0, xmm2
		paddw xmm4, xmm6
		pmullw xmm2, xmm2
		pmullw xmm6, xmm6
		paddw xmm1, xmm2
		paddw xmm5, xmm6
		movdqa xmm2, xmmword ptr [edi+0x40]
		movdqa xmm6, xmmword ptr [edi+0x80]
		psubw xmm2, xmm3
		psubw xmm6, xmm3
		paddw xmm0, xmm2
		paddw xmm4, xmm6
		pmullw xmm2, xmm2
		pmullw xmm6, xmm6
		paddw xmm1, xmm2
		paddw xmm5, xmm6
		movdqa xmm7, xmm3
		psrlw xmm7, 7
		movdqa xmm2, xmm0
		movdqa xmm6, xmm4
		paddw xmm0, xmm7
		paddw xmm4, xmm7
		psraw xmm2, 1
		psraw xmm6, 1
		psraw xmm0, 1
		psraw xmm4, 1
		pmullw xmm2, xmm0
		pmullw xmm6, xmm4
		psubw xmm1, xmm2
		psubw xmm5, xmm6
		movdqa xmm7, xmmword ptr smoothLimit
		movdqa xmm2, xmm1
		movdqa xmmword ptr upperActivity, xmm1
		movdqa xmmword ptr lowerActivity, xmm5
		movdqa xmm6, xmm5
		psubw xmm1, xmm7
		psubw xmm5, xmm7
		psraw xmm2, 0xf
		psraw xmm6, 0xf
		psraw xmm1, 0xf
		psraw xmm5, 0xf
		movdqa xmm7, xmmword ptr [edi+0x40]
		pandn xmm2, xmm1
		pandn xmm6, xmm5
		movdqa xmm4, xmmword ptr [edi+0x50]
		pand xmm6, xmm2
		movdqa xmm2, xmm7
		psubusw xmm7, xmm4
		psubusw xmm4, xmm2
		por xmm7, xmm4
		psubw xmm7, xmmword ptr qv
		psraw xmm7, 0xf
		pand xmm7, xmm6
		movdqa xmm1, xmmword ptr loopLimit
		movdqa xmm3, xmmword ptr [edi+0x30]
		movdqa xmm4, xmmword ptr [edi+0x40]
		movdqa xmm5, xmmword ptr [edi+0x50]
		movdqa xmm6, xmmword ptr [edi+0x60]
		psubw xmm5, xmm4
		psubw xmm3, xmm6
		movdqa xmm4, xmm5
		paddw xmm4, xmm5
		paddw xmm3, xmmword ptr kRva012D87D0Four
		paddw xmm5, xmm4
		paddw xmm3, xmm5
		psraw xmm3, 3
		movdqa xmm2, xmm3
		psraw xmm3, 0xf
		pxor xmm2, xmm3
		psubsw xmm2, xmm3
		por xmm3, xmmword ptr kRva012D8820One
		movdqa xmm4, xmm1
		psubw xmm1, xmm2
		movdqa xmm5, xmm1
		psraw xmm1, 0xf
		pxor xmm5, xmm1
		psubsw xmm5, xmm1
		psubusw xmm4, xmm5
		pmullw xmm4, xmm3
		movdqa xmm1, xmmword ptr [edi+0x40]
		movdqa xmm2, xmmword ptr [edi+0x50]
		paddw xmm1, xmm4
		psubw xmm2, xmm4
		pxor xmm6, xmm6
		packuswb xmm1, xmm1
		packuswb xmm2, xmm2
		punpcklbw xmm1, xmm6
		movdqa xmmword ptr firstFiltered, xmm1
		punpcklbw xmm2, xmm6
		movdqa xmmword ptr secondFiltered, xmm2
		movdqa xmm5, xmmword ptr [edi]
		movdqa xmm4, xmmword ptr [edi+0x10]
		movdqa xmm3, xmm4
		movdqa xmm6, xmm5
		psubusw xmm4, xmm6
		psubusw xmm5, xmm3
		por xmm4, xmm5
		psubw xmm4, xmmword ptr qv
		psraw xmm4, 0xf
		movdqa xmm1, xmm4
		pand xmm4, xmm6
		pandn xmm1, xmm3
		por xmm1, xmm4
		movdqa xmm4, xmmword ptr [edi+0x80]
		movdqa xmm5, xmmword ptr [edi+0x90]
		movdqa xmm3, xmm4
		movdqa xmm6, xmm5
		psubusw xmm4, xmm6
		psubusw xmm5, xmm3
		por xmm4, xmm5
		psubw xmm4, xmmword ptr qv
		psraw xmm4, 0xf
		movdqa xmm2, xmm4
		pand xmm4, xmm6
		pandn xmm2, xmm3
		por xmm2, xmm4
		pxor xmm0, xmm0
		movdqa xmm3, xmm1
		paddw xmm3, xmm3
		paddw xmm3, xmm1
		movdqa xmm4, xmmword ptr [edi+0x10]
		paddw xmm3, xmmword ptr [edi+0x20]
		paddw xmm4, xmmword ptr [edi+0x30]
		paddw xmm3, xmmword ptr [edi+0x40]
		paddw xmm4, xmmword ptr kRva012D87D0Four
		paddw xmm3, xmm4
		movdqa xmm4, xmm3
		movdqa xmm5, xmmword ptr [edi+0x10]
		paddw xmm4, xmm5
		psllw xmm4, 1
		psubw xmm4, xmmword ptr [edi+0x40]
		paddw xmm4, xmmword ptr [edi+0x50]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movq qword ptr [esi+edx*2], xmm4
		movdqa xmm5, xmmword ptr [edi+0x20]
		psubw xmm3, xmm1
		paddw xmm3, xmmword ptr [edi+0x50]
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		psubw xmm4, xmmword ptr [edi+0x50]
		paddw xmm4, xmmword ptr [edi+0x60]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movq qword ptr [esi+edx], xmm4
		movdqa xmm5, xmmword ptr [edi+0x30]
		psubw xmm3, xmm1
		paddw xmm3, xmmword ptr [edi+0x60]
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		psubw xmm4, xmmword ptr [edi+0x60]
		paddw xmm4, xmmword ptr [edi+0x70]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movq qword ptr [esi], xmm4
		movdqa xmm5, xmmword ptr [edi+0x40]
		psubw xmm3, xmm1
		paddw xmm3, xmmword ptr [edi+0x70]
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		paddw xmm4, xmm1
		psubw xmm4, xmmword ptr [edi+0x10]
		psubw xmm4, xmmword ptr [edi+0x70]
		paddw xmm4, xmmword ptr [edi+0x80]
		movdqa xmm5, xmmword ptr firstFiltered
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movq qword ptr [esi+ecx], xmm4
		movdqa xmm5, xmmword ptr [edi+0x50]
		psubw xmm3, xmmword ptr [edi+0x10]
		paddw xmm3, xmmword ptr [edi+0x80]
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		paddw xmm4, xmmword ptr [edi+0x10]
		psubw xmm4, xmmword ptr [edi+0x20]
		psubw xmm4, xmmword ptr [edi+0x80]
		paddw xmm4, xmm2
		movdqa xmm5, xmmword ptr secondFiltered
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		lea esi, [esi+ecx*4]
		packuswb xmm4, xmm0
		movq qword ptr [esi+edx*2], xmm4
		movdqa xmm5, xmmword ptr [edi+0x60]
		psubw xmm3, xmmword ptr [edi+0x20]
		paddw xmm3, xmm2
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		paddw xmm4, xmmword ptr [edi+0x20]
		psubw xmm4, xmmword ptr [edi+0x30]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movq qword ptr [esi+edx], xmm4
		movdqa xmm5, xmmword ptr [edi+0x70]
		psubw xmm3, xmmword ptr [edi+0x30]
		paddw xmm3, xmm2
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		paddw xmm4, xmmword ptr [edi+0x30]
		psubw xmm4, xmmword ptr [edi+0x40]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movq qword ptr [esi], xmm4
		movdqa xmm5, xmmword ptr [edi+0x80]
		psubw xmm3, xmmword ptr [edi+0x40]
		paddw xmm3, xmm2
		movdqa xmm4, xmm5
		paddw xmm4, xmm3
		paddw xmm4, xmm4
		paddw xmm4, xmmword ptr [edi+0x40]
		psubw xmm4, xmmword ptr [edi+0x50]
		psraw xmm4, 4
		psubw xmm4, xmm5
		pand xmm4, xmm7
		paddw xmm4, xmm5
		packuswb xmm4, xmm0
		movq qword ptr [esi+ecx], xmm4
		pop edi
		pop esi
		pop edx
		pop ecx
		pop eax
		}
		ctx->m_fragmentVariances[index] += upperActivity[0] + upperActivity[1] + upperActivity[2] + upperActivity[3] + upperActivity[4] + upperActivity[5] + upperActivity[6] + upperActivity[7];
		ctx->m_fragmentVariances[index + count] += lowerActivity[0] + lowerActivity[1] + lowerActivity[2] + lowerActivity[3] + lowerActivity[4] + lowerActivity[5] + lowerActivity[6] + lowerActivity[7];
		if (index == first) {
			index++;
			continue;
		}
		{
			edge = destination + (index - first) * 8 - p1 * 8;
			dstRow = edge;
			srcRow = edge;
			q = limits[ctx->m_fragmentQIndex[index]];
			qv[0] = (unsigned short)q;
			qv[1] = (unsigned short)q;
			qv[2] = (unsigned short)q;
			qv[3] = (unsigned short)q;
			qv[4] = (unsigned short)q;
			qv[5] = (unsigned short)q;
			qv[6] = (unsigned short)q;
			qv[7] = (unsigned short)q;
			rows[0] = edge[-5];
			rows[72] = edge[4];
			rows[1] = edge[stride - 5];
			rows[73] = edge[stride + 4];
			rows[2] = edge[p1 * 2 - 5];
			rows[74] = edge[p1 * 2 + 4];
			s3 = stride * 3;
			rows[3] = edge[s3 - 5];
			rows[75] = edge[s3 + 4];
			rows[4] = edge[p1 * 4 - 5];
			rows[76] = edge[p1 * 4 + 4];
			s5 = stride * 5;
			rows[5] = edge[s5 - 5];
			rows[77] = edge[s5 + 4];
			s6 = stride * 6;
			rows[6] = edge[s6 - 5];
			rows[78] = edge[s6 + 4];
			s7 = stride * 7;
			rows[7] = edge[s7 - 5];
			rows[79] = edge[s7 + 4];
			__asm {
			push eax
			push ecx
			push edx
			push esi
			push edi
			movdqa xmm0, xmmword ptr qv
			movdqa xmm1, xmmword ptr kRva012D87C0Three
			pmullw xmm1, xmm0
			pmullw xmm1, xmm0
			psrlw xmm1, 5
			movdqa xmmword ptr smoothLimit, xmm1
			mov eax, dword ptr srcRow
			xor edx, edx
			mov esi, dword ptr dstRow
			sub eax, 4
			sub esi, 4
			lea edi, rows
			mov ecx, stride
			sub edx, ecx
			lea esi, [esi+ecx*2]
			movq mm0, qword ptr [eax]
			movq mm1, qword ptr [eax+ecx]
			movq mm2, qword ptr [eax+ecx*2]
			lea eax, [eax+ecx*4]
			movq mm3, qword ptr [eax+edx]
			movq mm4, mm0
			punpcklbw mm0, mm1
			punpckhbw mm4, mm1
			movq mm5, mm2
			punpcklbw mm2, mm3
			punpckhbw mm5, mm3
			movq mm1, mm0
			punpcklwd mm0, mm2
			punpckhwd mm1, mm2
			movq mm2, mm4
			punpckhwd mm4, mm5
			punpcklwd mm2, mm5
			pxor mm7, mm7
			movq mm5, mm0
			punpcklbw mm0, mm7
			movq qword ptr [edi+0x10], mm0
			punpckhbw mm5, mm7
			movq mm0, mm1
			movq qword ptr [edi+0x20], mm5
			punpcklbw mm1, mm7
			punpckhbw mm0, mm7
			movq qword ptr [edi+0x30], mm1
			movq mm3, mm2
			movq mm5, mm4
			movq qword ptr [edi+0x40], mm0
			punpcklbw mm2, mm7
			punpckhbw mm3, mm7
			movq qword ptr [edi+0x50], mm2
			punpcklbw mm4, mm7
			punpckhbw mm5, mm7
			movq qword ptr [edi+0x60], mm3
			movq mm0, qword ptr [eax]
			movq mm1, qword ptr [eax+ecx]
			movq qword ptr [edi+0x70], mm4
			movq mm2, qword ptr [eax+ecx*2]
			lea eax, [eax+ecx*4]
			movq qword ptr [edi+0x80], mm5
			movq mm4, mm0
			movq mm3, qword ptr [eax+edx]
			punpcklbw mm0, mm1
			punpckhbw mm4, mm1
			movq mm5, mm2
			punpcklbw mm2, mm3
			punpckhbw mm5, mm3
			movq mm1, mm0
			punpcklwd mm0, mm2
			punpckhwd mm1, mm2
			movq mm2, mm4
			punpckhwd mm4, mm5
			punpcklwd mm2, mm5
			movq mm5, mm0
			punpcklbw mm0, mm7
			movq qword ptr [edi+0x18], mm0
			punpckhbw mm5, mm7
			movq mm0, mm1
			movq qword ptr [edi+0x28], mm5
			punpcklbw mm1, mm7
			punpckhbw mm0, mm7
			movq qword ptr [edi+0x38], mm1
			movq mm3, mm2
			movq mm5, mm4
			movq qword ptr [edi+0x48], mm0
			punpcklbw mm2, mm7
			punpckhbw mm3, mm7
			movq qword ptr [edi+0x58], mm2
			punpcklbw mm4, mm7
			punpckhbw mm5, mm7
			movq qword ptr [edi+0x68], mm3
			movq qword ptr [edi+0x78], mm4
			movq qword ptr [edi+0x88], mm5
			pcmpeqw xmm3, xmm3
			psllw xmm3, 0xf
			psrlw xmm3, 8
			movdqa xmm2, xmmword ptr [edi+0x10]
			movdqa xmm6, xmmword ptr [edi+0x50]
			psubw xmm2, xmm3
			psubw xmm6, xmm3
			movdqa xmm0, xmm2
			movdqa xmm4, xmm6
			pmullw xmm2, xmm2
			pmullw xmm6, xmm6
			movdqa xmm1, xmm2
			movdqa xmm5, xmm6
			movdqa xmm2, xmmword ptr [edi+0x20]
			movdqa xmm6, xmmword ptr [edi+0x60]
			psubw xmm2, xmm3
			psubw xmm6, xmm3
			paddw xmm0, xmm2
			paddw xmm4, xmm6
			pmullw xmm2, xmm2
			pmullw xmm6, xmm6
			paddw xmm1, xmm2
			paddw xmm5, xmm6
			movdqa xmm2, xmmword ptr [edi+0x30]
			movdqa xmm6, xmmword ptr [edi+0x70]
			psubw xmm2, xmm3
			psubw xmm6, xmm3
			paddw xmm0, xmm2
			paddw xmm4, xmm6
			pmullw xmm2, xmm2
			pmullw xmm6, xmm6
			paddw xmm1, xmm2
			paddw xmm5, xmm6
			movdqa xmm2, xmmword ptr [edi+0x40]
			movdqa xmm6, xmmword ptr [edi+0x80]
			psubw xmm2, xmm3
			psubw xmm6, xmm3
			paddw xmm0, xmm2
			paddw xmm4, xmm6
			pmullw xmm2, xmm2
			pmullw xmm6, xmm6
			paddw xmm1, xmm2
			paddw xmm5, xmm6
			movdqa xmm7, xmm3
			psrlw xmm7, 7
			movdqa xmm2, xmm0
			movdqa xmm6, xmm4
			paddw xmm0, xmm7
			paddw xmm4, xmm7
			psraw xmm2, 1
			psraw xmm6, 1
			psraw xmm0, 1
			psraw xmm4, 1
			pmullw xmm2, xmm0
			pmullw xmm6, xmm4
			psubw xmm1, xmm2
			psubw xmm5, xmm6
			movdqa xmm7, xmmword ptr smoothLimit
			movdqa xmm2, xmm1
			movdqa xmmword ptr upperActivity, xmm1
			movdqa xmmword ptr lowerActivity, xmm5
			movdqa xmm6, xmm5
			psubw xmm1, xmm7
			psubw xmm5, xmm7
			psraw xmm2, 0xf
			psraw xmm6, 0xf
			psraw xmm1, 0xf
			psraw xmm5, 0xf
			movdqa xmm7, xmmword ptr [edi+0x40]
			pandn xmm2, xmm1
			pandn xmm6, xmm5
			movdqa xmm4, xmmword ptr [edi+0x50]
			pand xmm6, xmm2
			movdqa xmm2, xmm7
			psubusw xmm7, xmm4
			psubusw xmm4, xmm2
			por xmm7, xmm4
			psubw xmm7, xmmword ptr qv
			psraw xmm7, 0xf
			pand xmm7, xmm6
			movdqa xmm1, xmmword ptr loopLimit
			movdqa xmm3, xmmword ptr [edi+0x30]
			movdqa xmm4, xmmword ptr [edi+0x40]
			movdqa xmm5, xmmword ptr [edi+0x50]
			movdqa xmm6, xmmword ptr [edi+0x60]
			psubw xmm5, xmm4
			psubw xmm3, xmm6
			movdqa xmm4, xmm5
			paddw xmm4, xmm5
			paddw xmm3, xmmword ptr kRva012D87D0Four
			paddw xmm5, xmm4
			paddw xmm3, xmm5
			psraw xmm3, 3
			movdqa xmm2, xmm3
			psraw xmm3, 0xf
			pxor xmm2, xmm3
			psubsw xmm2, xmm3
			por xmm3, xmmword ptr kRva012D8820One
			movdqa xmm4, xmm1
			psubw xmm1, xmm2
			movdqa xmm5, xmm1
			psraw xmm1, 0xf
			pxor xmm5, xmm1
			psubsw xmm5, xmm1
			psubusw xmm4, xmm5
			pmullw xmm4, xmm3
			movdqa xmm1, xmmword ptr [edi+0x40]
			movdqa xmm2, xmmword ptr [edi+0x50]
			paddw xmm1, xmm4
			psubw xmm2, xmm4
			pxor xmm6, xmm6
			packuswb xmm1, xmm1
			packuswb xmm2, xmm2
			punpcklbw xmm1, xmm6
			movdqa xmmword ptr firstFiltered, xmm1
			punpcklbw xmm2, xmm6
			movdqa xmmword ptr secondFiltered, xmm2
			movdqa xmm5, xmmword ptr [edi]
			movdqa xmm4, xmmword ptr [edi+0x10]
			movdqa xmm3, xmm4
			movdqa xmm6, xmm5
			psubusw xmm4, xmm6
			psubusw xmm5, xmm3
			por xmm4, xmm5
			psubw xmm4, xmmword ptr qv
			psraw xmm4, 0xf
			movdqa xmm1, xmm4
			pand xmm4, xmm6
			pandn xmm1, xmm3
			por xmm1, xmm4
			movdqa xmm4, xmmword ptr [edi+0x80]
			movdqa xmm5, xmmword ptr [edi+0x90]
			movdqa xmm3, xmm4
			movdqa xmm6, xmm5
			psubusw xmm4, xmm6
			psubusw xmm5, xmm3
			por xmm4, xmm5
			psubw xmm4, xmmword ptr qv
			psraw xmm4, 0xf
			movdqa xmm2, xmm4
			pand xmm4, xmm6
			pandn xmm2, xmm3
			por xmm2, xmm4
			pxor xmm0, xmm0
			movdqa xmm3, xmm1
			paddw xmm3, xmm3
			paddw xmm3, xmm1
			movdqa xmm4, xmmword ptr [edi+0x10]
			paddw xmm3, xmmword ptr [edi+0x20]
			paddw xmm4, xmmword ptr [edi+0x30]
			paddw xmm3, xmmword ptr [edi+0x40]
			paddw xmm4, xmmword ptr kRva012D87D0Four
			paddw xmm3, xmm4
			movdqa xmm4, xmm3
			movdqa xmm5, xmmword ptr [edi+0x10]
			paddw xmm4, xmm5
			psllw xmm4, 1
			psubw xmm4, xmmword ptr [edi+0x40]
			paddw xmm4, xmmword ptr [edi+0x50]
			psraw xmm4, 4
			psubw xmm4, xmm5
			pand xmm4, xmm7
			paddw xmm4, xmm5
			packuswb xmm4, xmm0
			movdq2q mm0, xmm4
			movdqa xmm5, xmmword ptr [edi+0x20]
			psubw xmm3, xmm1
			paddw xmm3, xmmword ptr [edi+0x50]
			movdqa xmm4, xmm5
			paddw xmm4, xmm3
			paddw xmm4, xmm4
			psubw xmm4, xmmword ptr [edi+0x50]
			paddw xmm4, xmmword ptr [edi+0x60]
			psraw xmm4, 4
			psubw xmm4, xmm5
			pand xmm4, xmm7
			paddw xmm4, xmm5
			packuswb xmm4, xmm0
			movdq2q mm1, xmm4
			movdqa xmm5, xmmword ptr [edi+0x30]
			psubw xmm3, xmm1
			paddw xmm3, xmmword ptr [edi+0x60]
			movdqa xmm4, xmm5
			paddw xmm4, xmm3
			paddw xmm4, xmm4
			psubw xmm4, xmmword ptr [edi+0x60]
			paddw xmm4, xmmword ptr [edi+0x70]
			psraw xmm4, 4
			psubw xmm4, xmm5
			pand xmm4, xmm7
			paddw xmm4, xmm5
			packuswb xmm4, xmm0
			movdq2q mm2, xmm4
			movdqa xmm5, xmmword ptr [edi+0x40]
			psubw xmm3, xmm1
			paddw xmm3, xmmword ptr [edi+0x70]
			movdqa xmm4, xmm5
			paddw xmm4, xmm3
			paddw xmm4, xmm4
			paddw xmm4, xmm1
			psubw xmm4, xmmword ptr [edi+0x10]
			psubw xmm4, xmmword ptr [edi+0x70]
			paddw xmm4, xmmword ptr [edi+0x80]
			movdqa xmm5, xmmword ptr firstFiltered
			psraw xmm4, 4
			psubw xmm4, xmm5
			pand xmm4, xmm7
			paddw xmm4, xmm5
			packuswb xmm4, xmm0
			movdq2q mm3, xmm4
			movdqa xmm5, xmmword ptr [edi+0x50]
			psubw xmm3, xmmword ptr [edi+0x10]
			paddw xmm3, xmmword ptr [edi+0x80]
			movdqa xmm4, xmm5
			paddw xmm4, xmm3
			paddw xmm4, xmm4
			paddw xmm4, xmmword ptr [edi+0x10]
			psubw xmm4, xmmword ptr [edi+0x20]
			psubw xmm4, xmmword ptr [edi+0x80]
			paddw xmm4, xmm2
			movdqa xmm5, xmmword ptr secondFiltered
			psraw xmm4, 4
			psubw xmm4, xmm5
			pand xmm4, xmm7
			paddw xmm4, xmm5
			packuswb xmm4, xmm0
			movdq2q mm4, xmm4
			movdqa xmm5, xmmword ptr [edi+0x60]
			psubw xmm3, xmmword ptr [edi+0x20]
			paddw xmm3, xmm2
			movdqa xmm4, xmm5
			paddw xmm4, xmm3
			paddw xmm4, xmm4
			paddw xmm4, xmmword ptr [edi+0x20]
			psubw xmm4, xmmword ptr [edi+0x30]
			psraw xmm4, 4
			psubw xmm4, xmm5
			pand xmm4, xmm7
			paddw xmm4, xmm5
			packuswb xmm4, xmm0
			movdq2q mm5, xmm4
			movdqa xmm5, xmmword ptr [edi+0x70]
			psubw xmm3, xmmword ptr [edi+0x30]
			paddw xmm3, xmm2
			movdqa xmm4, xmm5
			paddw xmm4, xmm3
			paddw xmm4, xmm4
			paddw xmm4, xmmword ptr [edi+0x30]
			psubw xmm4, xmmword ptr [edi+0x40]
			psraw xmm4, 4
			psubw xmm4, xmm5
			pand xmm4, xmm7
			paddw xmm4, xmm5
			packuswb xmm4, xmm0
			movdq2q mm6, xmm4
			movdqa xmm5, xmmword ptr [edi+0x80]
			psubw xmm3, xmmword ptr [edi+0x40]
			paddw xmm3, xmm2
			movdqa xmm4, xmm5
			paddw xmm4, xmm3
			paddw xmm4, xmm4
			paddw xmm4, xmmword ptr [edi+0x40]
			psubw xmm4, xmmword ptr [edi+0x50]
			psraw xmm4, 4
			psubw xmm4, xmm5
			pand xmm4, xmm7
			paddw xmm4, xmm5
			packuswb xmm4, xmm0
			movdq2q mm7, xmm4
			movq2dq xmm0, mm0
			movq2dq xmm1, mm1
			movq2dq xmm2, mm2
			movq2dq xmm3, mm3
			punpcklbw xmm0, xmm1
			punpcklbw xmm2, xmm3
			movdqa xmm1, xmm0
			punpcklwd xmm0, xmm2
			punpckhwd xmm1, xmm2
			movq2dq xmm4, mm4
			movq2dq xmm5, mm5
			movq2dq xmm6, mm6
			movq2dq xmm7, mm7
			punpcklbw xmm4, xmm5
			punpcklbw xmm6, xmm7
			movdqa xmm5, xmm4
			punpcklwd xmm4, xmm6
			punpckhwd xmm5, xmm6
			movdqa xmm2, xmm0
			punpckldq xmm0, xmm4
			movq qword ptr [esi+edx*2], xmm0
			psrldq xmm0, 8
			punpckhdq xmm2, xmm4
			movq qword ptr [esi+edx], xmm0
			movdqa xmm3, xmm1
			punpckldq xmm1, xmm5
			movq qword ptr [esi], xmm2
			psrldq xmm2, 8
			punpckhdq xmm3, xmm5
			movq qword ptr [esi+ecx], xmm2
			lea esi, [esi+ecx*4]
			movq qword ptr [esi+edx*2], xmm1
			movq qword ptr [esi], xmm3
			psrldq xmm1, 8
			psrldq xmm3, 8
			movq qword ptr [esi+edx], xmm1
			movq qword ptr [esi+ecx], xmm3
			pop edi
			pop esi
			pop edx
			pop ecx
			pop eax
			}
			ctx->m_fragmentVariances[index - 1] += upperActivity[0] + upperActivity[1] + upperActivity[2] + upperActivity[3] + upperActivity[4] + upperActivity[5] + upperActivity[6] + upperActivity[7];
			ctx->m_fragmentVariances[index] += lowerActivity[0] + lowerActivity[1] + lowerActivity[2] + lowerActivity[3] + lowerActivity[4] + lowerActivity[5] + lowerActivity[6] + lowerActivity[7];
		}
		index++;
	} while (index < end);
	}
}
