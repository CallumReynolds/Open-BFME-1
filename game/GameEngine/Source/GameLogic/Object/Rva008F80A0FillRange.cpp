// cl: /O2

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)



class Element;
class PartitionCell
{
public:
    Element *m_firstElem;
    unsigned char m_pad04[0x64];
};
class Element
{
public:
    void *m_cell;
    void *m_04;
    Element **m_pprev;
    Element *m_next;
    // ?addCoverage@Element@@QAE_NPAVPartitionCell@@@Z absent-from-retail
    __forceinline bool addCoverage(PartitionCell *cell)
    {
        m_cell = cell;
        Element *head = cell->m_firstElem;
        m_next = head;
        if (head != 0)
            head->m_pprev = &m_next;
        m_pprev = (Element **)cell;
        cell->m_firstElem = this;
        return true;
    }
};

class PartitionManager
{
public:
	void getCellRange(PartitionCell **first, PartitionCell **last, int x1, int x2, int y);
};

class Rva008F80A0
{
public:
	bool method(int x1, int x2, int y);

	PartitionManager *m_00;
	Element *m_04;
	Element *m_08;
};

// __vref absent-from-retail
template<class T> inline volatile T &__vref(T &x) { return *(volatile T *)&x; }

// ?method@Rva008F80A0@@QAE_NHHH@Z
// Open BFME 2: Code/GameEngine/Source/Common/RTS/ShroudVariantCircle008F9BB0.cpp
bool Rva008F80A0::method(int x1, int x2, int y)
{
    PartitionCell *first;
    PartitionCell *last;
    m_00->getCellRange(&first, &last, x1, x2, y);
    PartitionCell *cell = first;
    PartitionCell *end = last;
    _ReadWriteBarrier();
    if (__vref(cell) != end)
    {
        do
        {
            if (m_04 >= m_08)
                return false;
            (m_04++)->addCoverage(cell++);
        } while (cell != end);
    }
    return true;
}
