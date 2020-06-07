// DeviceSetting.cpp : implementation file
//

#include "stdafx.h"
#include "veditor.h"
#include <mmsystem.h>
#include "DeviceSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceSetting dialog


CDeviceSetting::CDeviceSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeviceSetting)
	m_midiOutput = -1;
	m_deviceName = _T("");
	m_midiInput = -1;
	m_deviceID = 0;
	m_deviceType = -1;
	m_auditionPatch = -1;
	//}}AFX_DATA_INIT
}


void CDeviceSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CDeviceSetting)
	DDX_CBIndex(pDX, IDC_MIDIOUTPUT, m_midiOutput);
	DDX_Text(pDX, IDC_DEVICENAME, m_deviceName);
	DDX_CBIndex(pDX, IDC_MIDIINPUT, m_midiInput);
	DDX_Text(pDX, IDC_DEVICEID, m_deviceID);
	DDV_MinMaxByte(pDX, m_deviceID, 1, 32);
	DDX_CBIndex(pDX, IDC_DEVICETYPE, m_deviceType);
	DDX_CBIndex(pDX, IDC_AUDITIONPATCH, m_auditionPatch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeviceSetting, CDialog)
	//{{AFX_MSG_MAP(CDeviceSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceSetting message handlers

BOOL CDeviceSetting::OnInitDialog() 
{
	int i, devCount;
	MIDIINCAPS	midiInCaps;
	MIDIOUTCAPS	midiOutCaps;
	CComboBox	*pCmb;

	devCount = midiInGetNumDevs();

	pCmb = (CComboBox *) GetDlgItem(IDC_MIDIINPUT);

	for (i = 0; i < devCount; i++)
	{
		midiInGetDevCaps(i, &midiInCaps, sizeof(MIDIINCAPS));
		pCmb->AddString(midiInCaps.szPname);
	}

	
	devCount = midiOutGetNumDevs();

	pCmb = (CComboBox *) GetDlgItem(IDC_MIDIOUTPUT);

	//midiOutGetDevCaps(MIDI_MAPPER, &midiOutCaps, sizeof(MIDIOUTCAPS));
	//pCmb->AddString(midiOutCaps.szPname);

	for (i = 0; i < devCount ; i++)
	{
		midiOutGetDevCaps(i, &midiOutCaps, sizeof(MIDIOUTCAPS));
		pCmb->AddString(midiOutCaps.szPname);
	}


	((CEdit *) GetDlgItem(IDC_DEVICENAME))->SetLimitText(31);

	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDeviceSetting::OnOK() 
{
	CComboBox	*pCmb;

	pCmb = (CComboBox *) GetDlgItem(IDC_MIDIINPUT);	
	
	if (pCmb->GetCurSel() == CB_ERR)
	{
		MessageBox("You have to select a midi input port", "VEditor", MB_OK | MB_ICONWARNING);
		pCmb->SetFocus();

		return;
	}


	pCmb = (CComboBox *) GetDlgItem(IDC_MIDIOUTPUT);	
	
	if (pCmb->GetCurSel() == CB_ERR)
	{
		MessageBox("You have to select a midi output port", "VEditor", MB_OK | MB_ICONWARNING);
		pCmb->SetFocus();

		return;
	}


	pCmb = (CComboBox *) GetDlgItem(IDC_AUDITIONPATCH);
	
	if (pCmb->GetCurSel() == CB_ERR)
	{
		MessageBox("You have to choose the audition patch number", "VEditor", MB_OK | MB_ICONWARNING);
		pCmb->SetFocus();

		return;
	}

	CDialog::OnOK();
}
