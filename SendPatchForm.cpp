// SendPatchForm.cpp : implementation file
//

#include "stdafx.h"
#include "veditor.h"
#include "SendPatchForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendPatchForm dialog


CSendPatchForm::CSendPatchForm(CWnd* pParent /*=NULL*/)
	: CDialog(CSendPatchForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendPatchForm)
	m_startPatch = -1;
	m_toPach = -1;
	m_toProgram = -1;
	//}}AFX_DATA_INIT
}


void CSendPatchForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendPatchForm)
	DDX_CBIndex(pDX, IDC_FROM_PATCH, m_startPatch);
	DDX_CBIndex(pDX, IDC_TO_PATCH, m_toPach);
	DDX_CBIndex(pDX, IDC_TO_PROGRAM, m_toProgram);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendPatchForm, CDialog)
	//{{AFX_MSG_MAP(CSendPatchForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendPatchForm message handlers

BOOL CSendPatchForm::OnInitDialog() 
{
	char buffer[1024];
	char *libraryName;
	char	patchName[32];
	CPatch	*patch;
	CString	str;
	POSITION	position;
	int		i;
	int		numPatch;
	int		patchCount;
	CComboBox	*pCmbFrom, *pCmbTo, *pCmbProg;
	CButton	*pChkSystem;

	CDialog::OnInitDialog();

	// Set the Dialog Title

	// Remove the path and the .syx extension from the name
	strcpy(buffer, m_library->file);
	buffer[strlen(buffer) - 4] = 0;
	libraryName = strrchr(buffer, '\\');

	if (libraryName)
		libraryName = libraryName + 1;
	else
		libraryName = buffer;

	((CStatic *) GetDlgItem(IDC_TITLE))->SetWindowText(libraryName);


	// Fill combo boxes with library patches names
	// add an item for each patch
	patchCount = m_library->patchList.GetCount();
	position = m_library->patchList.GetHeadPosition();

	numPatch = m_library->firstPatchNumber;
	pCmbFrom = (CComboBox *) GetDlgItem(IDC_FROM_PATCH);
	pCmbTo = (CComboBox *) GetDlgItem(IDC_TO_PATCH);
	pCmbProg = (CComboBox *) GetDlgItem(IDC_TO_PROGRAM);

	for (i = 0; i < patchCount; i++)
	{
		patch = (CPatch *) m_library->patchList.GetNext(position);
		patch->assignNC.name.getString(patchName);
		str.Format("%2d - %d    %s", (char)((numPatch + i) / 4) + 1, (char)((numPatch + i) % 4) + 1, patchName);

		pCmbFrom->AddString(str);
		pCmbTo->AddString(str);
	}

	if (m_patchToSend != -1)
	{
		pCmbFrom->SetCurSel(m_patchToSend);
		pCmbTo->SetCurSel(m_patchToSend);
		pCmbProg->SetCurSel(m_library->firstPatchNumber + m_patchToSend);
	}
	else
	{
		pCmbFrom->SetCurSel(0);
		pCmbTo->SetCurSel(patchCount - 1);
		pCmbProg->SetCurSel(m_library->firstPatchNumber);
	}

	pChkSystem = (CButton *) GetDlgItem(IDC_SYSTEM);

	//if (!m_system)
		pChkSystem->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSendPatchForm::OnOK() 
{
	CComboBox	*pCmbFrom, *pCmbTo, *pCmbProg;
	
	pCmbFrom = (CComboBox *) GetDlgItem(IDC_FROM_PATCH);
	pCmbTo = (CComboBox *) GetDlgItem(IDC_TO_PATCH);
	pCmbProg = (CComboBox *) GetDlgItem(IDC_TO_PROGRAM);

	if (pCmbTo->GetCurSel() < pCmbFrom->GetCurSel())
	{
		MessageBox("First patch must be lower than last patch");

		return;
	}

	if ((pCmbTo->GetCurSel() - pCmbFrom->GetCurSel() + 1) > 100 - pCmbProg->GetCurSel())
	{
		MessageBox("Pleach choose a lower target patch");

		return;
	}

	CDialog::OnOK();
}
