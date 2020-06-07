// LibTreeWnd.h : interface of the CLibTreeWnd class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LibTreeWnd_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_)
#define AFX_LibTreeWnd_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

#define LIBTREEWND_WIDTH	229

#include "DragDrop.h"
#include "vg-88.h"

class CNameEditor;

class CEditCustom : public CEdit
{
public:
	CNameEditor *m_parent;

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditCustom)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
};

class CNameEditor : public CWnd
{
void	Paint(CDC *dc);

// Operations
public:
	CWnd *m_parent;
	CEditCustom	m_edit;
	CPatch *m_patch;
	int m_currentCar;
	bool m_wndCarIsOnBottom;

	BOOL Create(RECT *rect, CWnd *pParentWnd);

	CNameEditor();
	CNameEditor(CPatch *patch);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNameEditor)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CNameEditor)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CTreeCtrlCustom : public CTreeCtrl, public CDragDrop
{
public:
	CMenu menu;
	CTreeCtrlCustom();
	void ProcessData(CString Data);

protected:
	//{{AFX_MSG(CTreeCtrlCustom)
	afx_msg void OnBeginDrag(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
};

// CLibTreeWnd window

class CLibTreeWnd : public CWnd
{
// Attributes
public:
	CTreeCtrlCustom	m_libraryTree;
	CFont		*m_font;
	CNameEditor *m_nameEditor;

void	PaintLibTreeWnd(CDC *dc);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibTreeWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLibTreeWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLibTreeWnd)
	afx_msg int OnCreate (LPCREATESTRUCT);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNotify(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void BeginLabelEdit(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void EndLabelEdit(LPNMHDR pnmhdr, LRESULT *pLResult);
	afx_msg void RClick(LPNMHDR pnmhdr, LRESULT *pLResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LibTreeWnd_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_)
