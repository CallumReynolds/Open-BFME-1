// cl: /O2 /MD /EHsc
class BfmeElemCU
{
public:
    BfmeElemCU();
    ~BfmeElemCU();
    void *m_value;
};

class Rva008947A0Elem : public BfmeElemCU
{
public:
    Rva008947A0Elem();
    ~Rva008947A0Elem();
};

class Rva00892C00Owner
{
public:
    Rva00892C00Owner();
private:
    int m_count;
    int m_used;
    Rva008947A0Elem *m_items;
    Rva008947A0Elem m_inline[2];
};

// ??0Rva00892C00Owner@@QAE@XZ
// Open BFME 2 Code/Libraries/Source/Apt/Apt.cpp.
Rva00892C00Owner::Rva00892C00Owner() : m_count(0), m_used(0), m_items(m_inline)
{
}
