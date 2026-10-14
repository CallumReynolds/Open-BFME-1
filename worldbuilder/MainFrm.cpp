#include <afxwin.h>

class CMainFrame : public CFrameWnd
{
protected:
    void OnViewBrushfeedback();
    void OnUpdateViewBrushfeedback(CCmdUI *pCmdUI);
};

// The donor's inline accessors would be authored definitions here; the
// handlers read the flag directly instead.
class DrawObject
{
    friend class CMainFrame;

protected:
    static bool m_disableFeedback;
};

void CMainFrame::OnViewBrushfeedback()
{
    if (!DrawObject::m_disableFeedback) {
        DrawObject::m_disableFeedback = true;
        ::AfxGetApp()->WriteProfileInt("MainFrame", "ShowBrushFeedback", 0);
    } else {
        DrawObject::m_disableFeedback = false;
        ::AfxGetApp()->WriteProfileInt("MainFrame", "ShowBrushFeedback", 1);
    }
}

void CMainFrame::OnUpdateViewBrushfeedback(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(!DrawObject::m_disableFeedback ? 1 : 0);
}
