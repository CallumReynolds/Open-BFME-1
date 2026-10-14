// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00674D20, 191 bytes.  One of
// thirteen sibling descriptions in the same translation unit: each returns a
// string by value, built from a name fetched by value and a few fields.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// ILT 0x0002D204 reaches the matched NetCommandMsg description at
// 0x006747C0. The qualified call below invokes that base implementation.
class NetCommandMsg
{
public:
	virtual AsciiString getContentsAsAsciiString();
};

class BfmeOrderZI
{
public:
	AsciiString bfmeDescribeZI(void);

	char m_bfmePadZI[0x1c];
	unsigned short m_bfmeCommandZI;
	unsigned char m_bfmePlayerZI;
	int m_bfmeFrameZI;
};

AsciiString BfmeOrderZI::bfmeDescribeZI(void)
{
	AsciiString text;

	text.format(AsciiString("%s, commandID=%d, originalPlayer=%d, originalExecFrame=%d"),
			((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString().str(), m_bfmeCommandZI, m_bfmePlayerZI, m_bfmeFrameZI);

	return text;
}
