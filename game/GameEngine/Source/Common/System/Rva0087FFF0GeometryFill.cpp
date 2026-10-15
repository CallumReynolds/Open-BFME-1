// cl: /DNDEBUG /MD /EHsc- /GX- /Ob2
#include <new>

class GeometryInfo
{
public:
    GeometryInfo(const GeometryInfo &);
    virtual ~GeometryInfo();
private:
    bool m_isSmall;
    char m_padding05[3];
    unsigned int m_scalar08;
    unsigned int m_scalar0c;
    float m_boundingCircleRadius;
    float m_boundingSphereRadius;
    float m_boundsCenter18[3];
    float m_extent24;
    float m_extent28;
    void *m_shapes[3];
    void *m_records[3];
    unsigned int m_cached44[6];
};
typedef char Rva0087FFF0GeometrySize[sizeof(GeometryInfo) == 0x5c ? 1 : -1];

// ?Rva0087FFF0Fill@@YAPAVGeometryInfo@@PAV1@IABV1@@Z
// Open BFME 2 Code/GameEngine/Source/Common/System/GeometryParseOther.cpp.
GeometryInfo *Rva0087FFF0Fill(GeometryInfo *first, unsigned int count, const GeometryInfo &value)
{
    GeometryInfo *current = first;
    for (; count > 0; --count, ++current)
        new (current) GeometryInfo(value);
    return current;
}
