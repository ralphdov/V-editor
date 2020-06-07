#if !defined(AFX_SENDPATCHFORM_H__C4369909_5B15_4458_874D_CD84C9A64241__INCLUDED_)
#define AFX_SENDPATCHFORM_H__C4369909_5B15_4458_874D_CD84C9A64241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendPatchForm.h : header file
//

#include "vg-88.h"

/////////////////////////////////////////////////////////////////////////////
// CSendPatchForm dialog

class CSendPatchForm : public CDialog
{
// Construction
public:
	CSendPatchForm(CWnd* pParent = NULL);   // standard constructor
	CVG88SysEx	*m_library;
	bool		m_system;
	int			m_patchToSend;

// Dialog Data
	//{{AFX_DATA(CSendPatchForm)
	enum { IDD = IDD_SENDPATCHFORM };
	int		m_startPatch;
	int		m_toPach;
	int		m_toProgram;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendPatchForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendPatchForm)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDPATCHFORM_H__C4369909_5B15_4458_874D_CD84C9A64241__INCLUDED_)
