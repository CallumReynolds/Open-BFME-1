// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674F00, 182 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// ILT 0x0002D204 reaches the matched NetCommandMsg description at
// 0x006747C0. The qualified call below invokes that base implementation.
class NetCommandMsg
{
public:
	virtual AsciiString getContentsAsAsciiString();
};

class BfmeOrderZM
{
public:
	AsciiString bfmeDescribeZM(void);

	char m_bfmePadZM[0x1c];
	unsigned char m_bfmeLeavingZM;
};

AsciiString BfmeOrderZM::bfmeDescribeZM(void)
{
	AsciiString text;

	text.format(AsciiString("%s, leavingPlayer=%d"),
			((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString().str(), m_bfmeLeavingZM);

	return text;
}
