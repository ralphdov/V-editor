#if !defined(AFX_SENDPATCH_H__E6E0878D_09B4_4BFE_A833_EAD3457E71BB__INCLUDED_)
#define AFX_SENDPATCH_H__E6E0878D_09B4_4BFE_A833_EAD3457E71BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendPatch.h : header file
//

#include "Afx.h"
#include "stdafx.h"
#include "veditor.h"

/////////////////////////////////////////////////////////////////////////////
// CSendPatch dialog

class CSendPatch : public CDialog
{
// Construction
public:
	CSendPatch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendPatch)
	enum { IDD = IDD_SENDPATCH };
	CProgressCtrl	m_progress;
	CStatic			m_label;
	//}}AFX_DATA

	BOOL m_cancel;
	bool m_modeReceive;

	void SetInfo(CString label, int pos, int maxPos);
	BOOL IsCanceled();
	void CSendPatch::Close();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendPatch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CSendPatch)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDPATCH_H__E6E0878D_09B4_4BFE_A833_EAD3457E71BB__INCLUDED_)
