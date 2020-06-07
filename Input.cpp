// Input.cpp : implementation file
//

#include "stdafx.h"
#include "veditor.h"
#include "Input.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInput dialog


CInput::CInput(CWnd* pParent /*=NULL*/)
	: CDialog(CInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInput)
	m_name = _T("");
	//}}AFX_DATA_INIT
}


void CInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInput)
	DDX_Text(pDX, IDC_NAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInput, CDialog)
	//{{AFX_MSG_MAP(CInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInput message handlers

void CInput::OnOK() 
{
	CString name;

	GetDlgItemText(IDC_NAME, name);

	if (name.Compare("") == 0)
	{
		((CEdit *) GetDlgItem(IDC_NAME))->SetFocus();

		return;
	}

	if (name.Find('/') != -1 || name.Find('\\') != -1 || name.Find('<') != -1 
		|| name.Find('>') != -1 || name.Find(':') != -1 || name.Find('*') != -1 || 
		name.Find('?') != -1 || name.Find('|') != -1)
	{
		MessageBox("Invalid character : / \\ : * ? < > | ");
		((CEdit *) GetDlgItem(IDC_NAME))->SetFocus();

		return;
	}

	CDialog::OnOK();
}
