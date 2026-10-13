// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674FF0, 181 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// ILT 0x0002D204 reaches the matched NetCommandMsg description at
// 0x006747C0. The qualified call below invokes that base implementation.
class NetCommandMsg
{
public:
	virtual AsciiString getContentsAsAsciiString();
};

class BfmeOrderZN
{
public:
	AsciiString bfmeDescribeZN(void);

	char m_bfmePadZN[0x1c];
	int m_bfmeDestroyZN;
};

AsciiString BfmeOrderZN::bfmeDescribeZN(void)
{
	AsciiString text;

	text.format(AsciiString("%s, destroyPlayer=%d"),
			((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString().str(), m_bfmeDestroyZN);

	return text;
}
