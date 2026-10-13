#include <afxwin.h>

// Only the fields the recovered handlers read are named; the rest stays unnamed storage.
class CWorldBuilderDoc
{
    unsigned char m_unrecovered_000[0x64];
    bool m_linkCenters;

protected:
    void OnEditLinkCenters();
    void OnUpdateEditLinkCenters(CCmdUI *pCmdUI);
};

void CWorldBuilderDoc::OnEditLinkCenters()
{
    m_linkCenters = !m_linkCenters;
}

void CWorldBuilderDoc::OnUpdateEditLinkCenters(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_linkCenters ? 1 : 0);
}
