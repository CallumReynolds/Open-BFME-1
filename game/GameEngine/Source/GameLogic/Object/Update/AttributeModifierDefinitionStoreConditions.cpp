// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: the two model-condition mask getters of
// AttributeModifierDefinitionStore, retail 0x0036B250 and 0x0036B330 (169
// bytes each). Both bounds-check the index against the definition vector at
// +0x08 (the same check valueAt and the other getters in
// AttributeModifierDefinitionStore.cpp make) and return a 320-bit mask by
// value: definition+0x1C (the conditions applyAttributeModifier sets) or
// definition+0x44 (the ones it clears), else an empty mask.
// Both names are address-derived: rva0036B250ConditionsAt is the pinned one,
// and retail's ILT order contradicts the copyClearMask pin at the twin's ILT
// 0x00018E3F (tools/ilt_oracle.py), so the twin is rva0036B330ConditionsAt.
//
// Shape notes measured against retail: the empty mask is default-constructed
// and then cleared (retail zeroes it twice, interleaved), and the definitions
// are a real STLport vector, whose size() and operator[] give retail's
// register choice.
#include <bitset>
#include <vector>

template <int NUMBITS>
class BitFlags
{
public:
	BitFlags() {}
	void clear() { m_bits.reset(); }

private:
	_STL::bitset< NUMBITS > m_bits;
};

typedef BitFlags< 320 > ModelConditionFlags;

struct AttributeModifierDefinition
{
	char m_unreconstructed00[ 0x1C ];
	ModelConditionFlags m_setConditions;		// +0x1C
	ModelConditionFlags m_clearConditions;		// +0x44
};

class AttributeModifierDefinitionStore
{
public:
	ModelConditionFlags rva0036B250ConditionsAt( int index ) const;
	ModelConditionFlags rva0036B330ConditionsAt( int index ) const;

private:
	char m_unreconstructed00[ 8 ];
	_STL::vector< AttributeModifierDefinition * > m_definitions;
};

ModelConditionFlags AttributeModifierDefinitionStore::rva0036B250ConditionsAt( int index ) const
{
	ModelConditionFlags none;
	none.clear();
	if( index < 0 || index > m_definitions.size() - 1 )
		return none;
	AttributeModifierDefinition *definition = m_definitions[ index ];
	if( definition == 0 )
		return none;
	return definition->m_setConditions;
}

ModelConditionFlags AttributeModifierDefinitionStore::rva0036B330ConditionsAt( int index ) const
{
	ModelConditionFlags none;
	none.clear();
	if( index < 0 || index > m_definitions.size() - 1 )
		return none;
	AttributeModifierDefinition *definition = m_definitions[ index ];
	if( definition == 0 )
		return none;
	return definition->m_clearConditions;
}
