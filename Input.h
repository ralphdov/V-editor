#if !defined(AFX_INPUT_H__EB9C4419_835A_4BC7_83B4_93A37BF9CFF6__INCLUDED_)
#define AFX_INPUT_H__EB9C4419_835A_4BC7_83B4_93A37BF9CFF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Input.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInput dialog

class CInput : public CDialog
{
// Construction
public:
	CInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInput)
	enum { IDD = IDD_INPUT };
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInput)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUT_H__EB9C4419_835A_4BC7_83B4_93A37BF9CFF6__INCLUDED_)
