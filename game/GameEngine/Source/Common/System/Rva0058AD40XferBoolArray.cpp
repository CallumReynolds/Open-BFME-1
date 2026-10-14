// cl: /DNDEBUG /MD /O2
// Calls through Xfer slots 29 and 35 match operator==(unsigned int&) and
// operator==(bool&), then the function transfers twelve booleans. Its name
// keeps RVA 0x0058AD40 because the body has no proven semantic owner.
#include "xfer.h"

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

Xfer &__cdecl xferBoolArray12Rva0058AD40(Xfer &xfer, bool *values)
{
	unsigned int version = 12;
	xfer == version;
	if (version != 12)
	{
		throw XferException(0, 0);
	}

	unsigned int index = 0;
	do
	{
		xfer == values[index];
		++index;
	}
	while (index < 12);

	return xfer;
}
