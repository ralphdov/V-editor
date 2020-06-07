// WorkspaceView.h : interface of the CWorkspaceView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WorkspaceView_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_)
#define AFX_WorkspaceView_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView window

class CWorkspaceView : public CWnd
{
// Construction
public:
	CWorkspaceView();

// Attributes
public:

// Operations
public:
	void TileWindows(UINT type);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWorkspaceView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WorkspaceView_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_)
