// cl: /DNDEBUG /MD /O2
#include "../../Common/System/xfer.h"

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};
class Xfer; class MidVirtualSlot90Receiver;
Xfer & __cdecl Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *target);

extern "C" Xfer &__cdecl xferRva003D6CB0(Xfer &xfer, int (&targets)[512])
{
	int remaining = 512;
	unsigned int version = remaining;
	xfer == version;
	if (version != 512)
	{
		throw XferException(0, 0);
	}

	int *target = targets;
	do
	{
		Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, target);
		++target;
	}
	while (--remaining != 0);

	return xfer;
}

extern "C" Xfer &__cdecl xferRva003D6D40(Xfer &xfer, float (&targets)[64])
{
	int remaining = 64;
	unsigned int version = remaining;
	xfer == version;
	if (version != 64)
	{
		throw XferException(0, 0);
	}

	float *target = targets;
	do
	{
		xfer == *target;
		++target;
	}
	while (--remaining != 0);

	return xfer;
}
