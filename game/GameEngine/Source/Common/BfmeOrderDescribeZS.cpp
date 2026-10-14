// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00675D40, 219 bytes.
// Sibling of 0x00675A80 with two string fields rather than one.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// ILT 0x0002D204 reaches the base description at 0x006747C0.
class NetCommandMsg
{
public:
	virtual AsciiString getContentsAsAsciiString();
};

class BfmeOrderZS
{
public:
	AsciiString bfmeDescribeZS(void);

	char m_bfmePadZS[0x1c];
	AsciiString m_bfmeAuthKeyZS;
	AsciiString m_bfmeAuthTokenZS;
};

AsciiString BfmeOrderZS::bfmeDescribeZS(void)
{
	AsciiString text;

	text.format(AsciiString("%s, authToken=%s, authKey=%s"),
			((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString().str(),
			m_bfmeAuthTokenZS.str(),
			m_bfmeAuthKeyZS.str());

	return text;
}
