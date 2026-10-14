// cl: /DNDEBUG /MD /O2
#include "System/xfer.h"

struct XferTriple32
{
	int a;
	int b;
	int c;
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};
extern "C" void __cdecl gen00344750(Xfer *xfer, void *target);
extern "C" void __cdecl gen000d7010(Xfer *xfer, void *target);

extern "C" Xfer &__cdecl xferRva00347BB0(Xfer &xfer, int (&targets)[32])
{
	int remaining = 32;
	unsigned int version = remaining;
	xfer == version;
	if (version != 32)
	{
		throw XferException(0, 0);
	}

	int *target = targets;
	do
	{
		gen00344750(&xfer, target);
		++target;
	}
	while (--remaining != 0);

	return xfer;
}

extern "C" Xfer &__cdecl xferRva00347C40(Xfer &xfer, XferTriple32 (&targets)[32])
{
	int remaining = 32;
	unsigned int version = remaining;
	xfer == version;
	if (version != 32)
	{
		throw XferException(0, 0);
	}

	XferTriple32 *target = targets;
	do
	{
		gen000d7010(&xfer, target);
		++target;
	}
	while (--remaining != 0);

	return xfer;
}
