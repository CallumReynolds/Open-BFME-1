// cl: /EHsc
#include <excpt.h>

// ?bfmeProbeSse2@@YAHXZ
int __cdecl bfmeProbeSse2(void)
{
	volatile unsigned int code;
	__try {
		__asm { xorpd xmm0, xmm0 }
	} __except ((code = **(unsigned int **)GetExceptionInformation(),
			EXCEPTION_EXECUTE_HANDLER)) {
		code;
		return 0;
	}
	return 1;
}
