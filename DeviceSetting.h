#if !defined(AFX_DEVICESETTING_H__E3B20213_F63B_43CA_833B_DFF80E0B929A__INCLUDED_)
#define AFX_DEVICESETTING_H__E3B20213_F63B_43CA_833B_DFF80E0B929A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeviceSetting dialog

class CDeviceSetting : public CDialog
{
// Construction
public:
	CDeviceSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeviceSetting)
	enum { IDD = IDD_DEVICE };
	int		m_midiOutput;
	CString	m_deviceName;
	int		m_midiInput;
	BYTE	m_deviceID;
	int		m_deviceType;
	int		m_auditionPatch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeviceSetting)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICESETTING_H__E3B20213_F63B_43CA_833B_DFF80E0B929A__INCLUDED_)
