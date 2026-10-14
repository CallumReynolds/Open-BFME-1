// cl: /DNDEBUG /MD /O2
#include "System/xfer.h"

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

extern "C" Xfer &__cdecl xferThreeInts(Xfer &xfer, int (&targets)[3])
{
	int remaining = 3;
	unsigned int version = remaining;
	xfer == version;
	if (version != 3)
	{
		throw XferException(0, 0);
	}

	int *target = targets;
	do
	{
		xfer == *target;
		++target;
	}
	while (--remaining != 0);

	return xfer;
}

// retail 0x009D6900
void Rva009D6900( Xfer &xfer )
{
	int targets[3];
	xferThreeInts( xfer, targets );
}
