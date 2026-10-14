// Retail 0x005CAD10, 223 bytes. Native STLport 4.5.3 string-plus-character operator.
// Explicit-RVA ILT oracle confirms the instantiated identity; see
// targets/game/reverse/identity_evidence/005cad10-native-string-concat.md.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <string>
namespace _STL {
template basic_string<char, char_traits<char>, allocator<char> > operator+(const basic_string<char, char_traits<char>, allocator<char> > &, const char);
}
