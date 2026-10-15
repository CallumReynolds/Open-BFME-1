// cl: /O2 /MD /EHsc
void d_00895790();

class Rva008958B0
{
public:
    void invoke(const void *key);
};

// ?invoke@Rva008958B0@@QAEXPBX@Z
// Open BFME 2 Code/Libraries/Source/Apt/AptValue/PlaybackBufferResize.cpp.
void Rva008958B0::invoke(const void *key)
{
    typedef void (Rva008958B0::*Entry)(const void *, int, int, int);
    union { void (*entry)(); Entry member; } native;
    typedef char SamePointerWidth[sizeof(native.entry) == sizeof(native.member) ? 1 : -1];
    native.entry = d_00895790;
    (this->*native.member)(key, 1, 3, 2);
}
