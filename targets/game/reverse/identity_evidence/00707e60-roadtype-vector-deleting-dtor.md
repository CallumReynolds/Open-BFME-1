# 0x00707E60 is RoadType's vector deleting destructor

The 84-byte body at 0x00707E60 (ledgered as the generated placeholder
`??_EGen_dtorv_00707e60@@UAEPAXI@Z`) is a standard MSVC 7.1 vector deleting
destructor: flag bit 2 selects the array path, which reads the element count at
`this-4` and calls `` `eh vector destructor iterator' `` (0x009F6D76) with element
size 0x24 and destructor ILT 0x0001DE49, then `operator delete[]` (0x00881EF0)
when bit 1 is set; the scalar path calls ILT 0x0001DE49 directly and then
`operator delete` (0x00881EB0). ILT 0x0001DE49 jumps to 0x007070C0, the matched
`??1RoadType@@QAE@XZ` (RoadTypeDestructor.cpp); the array-element size 0x24 is
RoadType's (W3DRoadBuffer's own new[]/delete[] of RoadType pass the same ILT,
see BfmeElementDVectorDeletingDestructor.cpp). The body is masked-identical
(only the destructor target differs) to the matched
`??_E?$CategoryModuleTemplate@$00@FXParticleSystem@@UAEPAXI@Z` at 0x005BF2C0.

RoadType's destructor is non-virtual, so the compiler symbol is
`??_ERoadType@@QAEPAXI@Z`. W3DRoadBuffer.cpp already emits exactly that symbol
(from `delete[] m_roadTypes` in `W3DRoadBuffer::freeRoadBuffers`), and its
compiled bytes match retail at the full 84-byte extent. The address lies
between the RoadType destructor and other W3DRoadBuffer.cpp bodies
(0x00707EE0 RoadSegment::GetRoadSegInfo, 0x00707F30 flipTheRoad). No direct
call, jump or absolute reference to 0x00707E60 or its ILT thunk 0x0000821A
exists in the retail image, which is consistent with an emitted COMDAT that
the retail delete[] sites do not call.

Refuted by: a different destructor target, a different element size, or a
scoped build of W3DRoadBuffer.cpp that does not reproduce the bytes.
