// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x006758C0, 185 bytes.
// Sibling of 0x00674C30; the fields it reports are what differ.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// ILT 0x0002D204 reaches the matched NetCommandMsg description at
// 0x006747C0. The qualified call below invokes that base implementation.
class NetCommandMsg
{
public:
	virtual AsciiString getContentsAsAsciiString();
};

class BfmeOrderZQ
{
public:
	AsciiString bfmeDescribeZQ(void);

	char m_bfmePadZQ[0x1c];
	int m_bfmeStartFrameZQ;
	int m_bfmeEndFrameZQ;
};

AsciiString BfmeOrderZQ::bfmeDescribeZQ(void)
{
	AsciiString text;

	text.format(AsciiString("%s, startFrame=%d endFrame=%d"),
			((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString().str(), m_bfmeStartFrameZQ, m_bfmeEndFrameZQ);

	return text;
}
