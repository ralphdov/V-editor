#if !defined(AFX_LIBPROP_H__CE1DEE7D_79A7_4936_AE7B_B60694F9DFB9__INCLUDED_)
#define AFX_LIBPROP_H__CE1DEE7D_79A7_4936_AE7B_B60694F9DFB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LibProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLibProp dialog

class CLibProp : public CDialog
{
// Construction
public:
	CLibProp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLibProp)
	enum { IDD = IDD_LIBPROP };
	int		m_firstPatch;
	CString	m_file;
	CString	m_libraryName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLibProp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBPROP_H__CE1DEE7D_79A7_4936_AE7B_B60694F9DFB9__INCLUDED_)
