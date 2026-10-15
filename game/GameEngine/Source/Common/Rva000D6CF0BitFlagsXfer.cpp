// ?xfer@Rva000D6CF0BitFlags@@QAEXPAVXfer@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame
// Retail 0x000D6CF0, 484-byte extent: 483 bytes of body ending on the
// throw call plus the throw-site INT3, the convention of the byte-matched
// siblings 0x001CB270 and 0x001CB730.
// A 181-bit named-flag transfer. The width is proven by the 0x18-byte
// object (six-dword count loop) and the 0xB5 save-loop bound; the name
// table VA 0x012AA068 is recorded as BitFlags<181>::s_bitNameList and the
// lookup ILT 0x0004AFFC is pinned as BitFlags<181>::getSingleBitFromName
// (identity_evidence/000cb330-BitFlags181-getSingleBitFromName.md). The CRC
// path calls the matched BitFlags<181>::xfer at 0x000D3DF0 through ILT
// 0x00006596. The owning wrapper class is not proven, so it keeps an
// address-derived name, as 0x001CB270 does.
// stlport
#include <bitset>
#include "Libraries/Source/WWVegas/WWLib/ascii_string.h"

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

struct __declspec(align(4)) Version0D6CF0 { unsigned char version,current; };

class Xfer { public:
 virtual void pad00();
 virtual void pad04();
 virtual bool save();
 virtual void pad0C();
 virtual bool crc();
 virtual void pad14();
 virtual void pad18();
 virtual void pad1C();
 virtual void pad20();
 virtual void pad24();
 virtual void version(Version0D6CF0 *);
 virtual void pad2C();
 virtual void pad30();
 virtual void pad34();
 virtual void pad38();
 virtual void pad3C();
 virtual void pad40();
 virtual void pad44();
 virtual void pad48();
 virtual void pad4C();
 virtual void pad50();
 virtual void pad54();
 virtual void pad58();
 virtual void pad5C();
 virtual void pad60();
 virtual void pad64();
 virtual void text(AsciiString *);
 virtual void pad6C();
 virtual void pad70();
 virtual void pad74();
 virtual void integer(int *);
};

template<int N> class BitFlags { public:
 _STL::bitset<N> bits;
 void xfer(Xfer *);
 static int getSingleBitFromName(const char *);
 friend class Rva000D6CF0BitFlags;
private:
 static const char *s_bitNameList[];
};

class Rva000D6CF0BitFlags { _STL::bitset<181> bits; public: void xfer(Xfer *xfer); };

void Rva000D6CF0BitFlags::xfer(Xfer *xfer)
{
 Version0D6CF0 v; v.version=1; v.current=1;
 xfer->version(&v);
 if (xfer->crc()) { ((BitFlags<181> *)this)->xfer(xfer); return; }
 if (xfer->save()) {
  int count=bits.count();
  xfer->integer(&count);
  for (int i=0;i<181;++i) {
   if (bits._Unchecked_test(i) && BitFlags<181>::s_bitNameList[i]) {
    AsciiString name(BitFlags<181>::s_bitNameList[i]);
    xfer->text(&name);
    --count;
   }
  }
 } else {
  bits.reset();
  int count;
  xfer->integer(&count);
  AsciiString name;
  for (int i=0;i<count;++i) {
   xfer->text(&name);
   int bit=BitFlags<181>::getSingleBitFromName(name.str());
   if (bit<0) {
    throw XferException(0,0);
   }
   bits._Unchecked_set(bit);
  }
 }
}
