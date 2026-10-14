// ?rva00112F30@@YAXABVAsciiString@@AAV1@@Z
// cl: /O2 /DNDEBUG /MD /GX /Igame/Libraries/Source/WWVegas/WWLib
// Clean C++ reconstruction of the anonymous GameStateMap save-path helper at
// retail RVA 0x00112F30 (151 bytes).  The body reads the source string's
// length, subtracts four, builds a substring without the extension, appends
// the literal ".wak" and assigns the result through StringBase::set; a source
// shorter than five characters takes the empty-string branch instead.  The
// three retail call sites inside the 0x00113280 GameStateMap xfer body load
// the source into ECX and the destination into ESI, MSVC 7.1's private
// register convention for this file-static helper; the caller anchor at the
// end keeps that shape without pulling the unverified 1396-byte parent body
// into the build.  Boundary RET at 0x00112FC6 followed by INT3; the ".wak"
// literal is g_Va010896AC in the d_0010e580.asm dump.

#include "ascii_string.h"

inline AsciiString::AsciiString(const AsciiString &source, int start, int length)
    : StringBase<char>(source, start, length) {}

static __declspec(noinline) void rva00112F30(const AsciiString &source, AsciiString &destination)
{
    int length = source.StringBase<char>::getLength() - 4;
    if (length > 0)
    {
        AsciiString temporary(source, 0, length);
        temporary.StringBase<char>::concat(".wak", 4);
        destination = temporary;
    }
    else
        destination.StringBase<char>::set("", 0);
}

void forceRva00112F30(const AsciiString &source, AsciiString &destination)
{
    rva00112F30(source, destination);
}
