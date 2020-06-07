// SendPatch.cpp : implementation file
//

#include "stdafx.h"
#include "veditor.h"
#include "SendPatch.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendPatch dialog


CSendPatch::CSendPatch(CWnd* pParent /*=NULL*/)
	: CDialog(CSendPatch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendPatch)
	//}}AFX_DATA_INIT
}


void CSendPatch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendPatch)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_LABEL, m_label);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendPatch, CDialog)
	//{{AFX_MSG_MAP(CSendPatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendPatch message handlers

BOOL CSendPatch::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (m_modeReceive)
	{
		SetWindowText("Waiting...");
		m_label.SetWindowText("Please send now your patches from the VG-88 Bulk Dump Mode");
	}
	else
	{
		SetWindowText("Sending...");
		m_label.SetWindowText("");
	}
	

	m_cancel = FALSE;
	((CMainFrame *) AfxGetMainWnd())->m_sendPatchCanceled = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CSendPatch::SetInfo(CString label, int pos, int maxPos)
{
	char buffer[255];

	m_progress.SetPos((pos * 100) / maxPos);

	if (m_modeReceive)
		sprintf(buffer, "  %d   patches received", pos);
	else
		sprintf(buffer, "Patch  %d / %d   (%d %%) :   %s", pos, maxPos, (pos * 100) / maxPos, label);

	m_label.SetWindowText(buffer);
}


BOOL CSendPatch::IsCanceled()
{
	return m_cancel;
}

void CSendPatch::Close()
{
	CDialog::OnCancel();
}


void CSendPatch::OnCancel() 
{
	m_cancel = TRUE;
	((CMainFrame *) AfxGetMainWnd())->m_sendPatchCanceled = TRUE;
	CDialog::OnCancel();
}
