// VGWindow.h : interface of the VGWindow class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VGWindow_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_)
#define AFX_VGWindow_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

#include "tools.h"
#include "libTreeWnd.h"
#include "vg-88.h"

#define VGWindow_WIDTH	184

class CListCtrlCustom : public CListCtrl
{
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlCustom)
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlCustom)
	afx_msg void OnBeginDrag(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



// VGWindow window

class CVGWindow : public CWnd
{
// Construction
public:
	CVGWindow();

// Attributes
public:
	CMaskedBitmap	m_LTVGWin1;
	CMaskedBitmap	m_MTVGWin1;
	CMaskedBitmap	m_RTVGWin1;
	CMaskedBitmap	m_LVGWin1;
	CMaskedBitmap	m_RVGWin1;
	CMaskedBitmap	m_LBVGWin1;
	CMaskedBitmap	m_MBVGWin1;
	CMaskedBitmap	m_RBVGWin1;
	CMaskedBitmap	m_icon;

	CListCtrlCustom	m_listView;
	CNameEditor *m_nameEditor;
	CVG88SysEx	*m_library;
	int			m_widget;
	int			m_capture;

	AttachLibrary(CVG88SysEx *lib);
	int CVGWindow::InsertItem(CPatch *patch, int pos, int numPatch);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVGWindow)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVGWindow();

	// Generated message map functions
public:
	//{{AFX_MSG(CVGWindow)
	afx_msg void OnNcPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNotify(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void BeginLabelEdit(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void ItemActivate(LPNMHDR pnmhdr, LRESULT *pLResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VGWindow_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_)
