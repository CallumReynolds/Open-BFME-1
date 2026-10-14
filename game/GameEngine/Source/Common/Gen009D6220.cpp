// cl: /DNDEBUG /MD /O2
// XferException variadic constructor at retail RVA 0x009D6220: the RTTI
// CatchableType for .?AVXferException@@ (0xDDFE34, ThrowInfo 0xDDFE5C) is
// thrown after this __cdecl member call at every retail throw site.
#include <stdarg.h>
#include <string.h>
#include <new>

// This formatter has its own scratch buffer at VA 0x0134D4B8. The INI
// exception constructor's g_bfmeFormatBuffer is the distinct VA 0x0130C650.
extern char Rva0134D4B8FormatBuffer[];
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *, unsigned int, const char *, va_list);
// The block is allocated through the global `operator new[]`, the 17-byte
// body at retail 0x00881F70 (??_U@YAPAXI@Z, matched in WWLib/mem_ops.cpp).

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	char *text;
	int tag;
};

XferException::XferException(int tag, const char *format, ...)
{
	this->tag = tag;
	text = 0;
	if (format != 0)
	{
		va_list args;
		va_start(args, format);
		int length = _vsnprintf(Rva0134D4B8FormatBuffer, 2047, format, args);
		text = static_cast<char *>(::operator new[](length + 1));
		memcpy(text, Rva0134D4B8FormatBuffer, length);
		text[length] = 0;
		va_end(args);
	}
}

// Native _vsnprintf receives capacity 0x7FF for this writable scratch view.
// Own only that used range; the original allocation extent is not claimed.
// See identity_evidence/0134d4b8-format-buffer-used-view.md.
char Rva0134D4B8FormatBuffer[2047];
