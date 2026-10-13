#include <afxwin.h>

// Only the fields the recovered handlers read are named; the rest stays unnamed storage.
class WbView3d
{
    unsigned char m_unrecovered_000[0x224];
    bool m_showWireframe;
    unsigned char m_unrecovered_225[0x34];
    bool m_showEntireMap;

protected:
    void OnUpdateViewShowwireframe(CCmdUI *pCmdUI);
    void OnUpdateViewShowentire3dmap(CCmdUI *pCmdUI);
};

void WbView3d::OnUpdateViewShowwireframe(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_showWireframe ? 1 : 0);
}

void WbView3d::OnUpdateViewShowentire3dmap(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_showEntireMap ? 1 : 0);
}
