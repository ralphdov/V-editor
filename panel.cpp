// Panel.cpp : implementation of the CPanel class
//

#include <stdio.h>
#include <io.h>
#include <time.h>
#include "stdafx.h"
#include "VEditor.h"
#include "MainFrm.h"
#include "panel.h"
#include "tools.h"
#include "VG-88.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPanel

CPanel::CPanel()
{
	m_font = &g_font1;
}


CPanel::~CPanel()
{
}


BEGIN_MESSAGE_MAP(CPanel,CWnd )
	//{{AFX_MSG_MAP(CPanel)
	ON_WM_CREATE ()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPanel message handlers

BOOL CPanel::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS, 
		AfxGetApp()->LoadCursor(IDC_CURSOR), NULL, NULL);

	return TRUE;
}


int CPanel::OnCreate (LPCREATESTRUCT lpcs)
{
	m_background = &g_panelEmpty;
	m_bottom	 = &g_panelBottom;
	m_presetData.m_needSaving = FALSE;
	m_presetData.setValue(0);
	
	return 0;
}


void CPanel::AttachVGData(CPatch *patch)
{

}


void CPanel::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	PaintPanel(&dc);
}


void CPanel::PaintPanel(CDC *dc) 
{
	RECT rect;
	CFont *pOldFont;
	char buffer[100];

	GetWindowRect(&rect);
	
	m_background->Draw(dc, 0, 0);
	m_bottom->Draw(dc, 0, rect.bottom - rect.top - 10);

	GetWindowText(buffer, 100);

	pOldFont = dc->SelectObject(&g_font3);
	dc->SetTextColor(RGB(238, 142, 27));
	dc->SetBkMode(TRANSPARENT);
	dc->DrawText(buffer, -1, CRect(0, 12 , PANEL_WIDTH, 27), DT_CENTER);
	dc->SelectObject(pOldFont);
}


void CPanel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_INSERT:
			if (m_onOff.m_vgData)
			{
				m_onOff.m_vgData->setValue(1 - m_onOff.m_vgData->getValue());

				g_currentPatch->checkPatch();
				g_currentPatch->initializePatchObjects();

				//m_parent->SendMessage(WM_COMMAND, (int) LOWORD(IDC_SEL_CHANGE), (long) this);

				((CMainFrame *) AfxGetMainWnd())->m_chainWnd.OnPatchChange();
				((CMainFrame *) AfxGetMainWnd())->m_patchWnd.m_patchWindowLayer.OnPatchChange();

				m_onOff.SetFocus();
			}
								
			break;

		default:
				CWnd ::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}



BOOL CPanel::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	RECT rect;

	switch (wParam)
	{
		case IDC_PRESET:
			int left, top;
			RECT desktopRect;
			m_presetWnd = new CPreset;
			
			m_preset.GetWindowRect(&rect);

			SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID) &desktopRect, 0);

			if (rect.left + 200 >= desktopRect.right)
				left = desktopRect.right - 200;
			else
				left = rect.left;

			if (rect.top - 300 < 0)
				top = 0;
			else
				top = rect.top - 300;

			m_presetWnd->CreateControl("PRESET", 0, left, top, 200, 300, this, 0);

			m_presetWnd->m_listBox.SetFocus();

			break;

		case IDC_PRESET_CANCEL:
		case IDC_PRESET_VALIDATE:
			delete m_presetWnd;
			m_presetWnd = NULL;
			m_presetData.setValue(0);
			g_currentLibrary->SetModifiedFlag();
			SetFocus();
			break;
	}

	// Notify the parent window that a refresh of the panel is needed
	GetParent()->PostMessage(WM_COMMAND, wParam, (long) this);

	return CWnd ::OnCommand(wParam, lParam);
}


CString CPanel::getPresetDir()
{
	return "";
}


int CPanel::setAllPanelData(char *buffer)
{
	return 0;
}

int CPanel::getAllPanelData(char *buffer)
{
	return 0;
}

CString CPanel::copy()
{
	CString name, fileName;
	char patchName[32];
	int count;
	char buffer[175000];
	unsigned int i;
	int numPatch;

	g_currentPatch->assignNC.name.getString(patchName);
	numPatch = g_currentLibrary->firstPatchNumber;

	for (i = 0; i < strlen(patchName); i++)
		if (patchName[i] < 32 || patchName[i] > 128 || patchName[i] == '<' || patchName[i] == '>' || patchName[i] == ':'
			 || patchName[i] == '?' || patchName[i] == '|' || patchName[i] == '*' || patchName[i] == '"' || patchName[i] == '/' || patchName[i] == '\\')
			patchName[i] = ' ';

	name.Format("    CLIPBOARD %2d - %d    %s", (char)((numPatch + g_currentPatchNumber) / 4) + 1, (char)((numPatch + g_currentPatchNumber) % 4) + 1, patchName);
	fileName = ((CMainFrame *) AfxGetMainWnd())->m_editorPath + "\\" + getPresetDir() + name;

	CFileException	e;
	CFile file;
	
	// Open the file
	if (!file.Open(fileName, CFile::modeWrite | CFile::modeCreate, &e))
	{
		MessageBox((char *) e.m_cause);

		return "";
	}

	count = getAllPanelData(buffer);

	// Read the entire content of the file
	file.Write(buffer, count);
	file.Close();

	return name;
}


//////////////// CPanelEmpty ///////////////

BEGIN_MESSAGE_MAP(CPanelEmpty, CPanel)
	//{{AFX_MSG_MAP(CPanelEmpty)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelEmpty::CPanelEmpty()
{
}


//////////////// CPanelAmp ///////////////

BEGIN_MESSAGE_MAP(CPanelAmp, CPanel)
	//{{AFX_MSG_MAP(CPanelAmp)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelAmp::CPanelAmp()
{
}


int CPanelAmp::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_AMP_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_AMP_ONOFF))
		return -1;

	// Amp type
	if (!m_ampType.CreateControl("TYPE", CTRL_EDIT1, 10, 44, this, IDC_AMP_TYPE))
		return -1;

	if (!m_ampTypeImage.CreateImageControl("TYPE", 10, 64, &g_amplifers, 32, this, IDC_AMP_TYPE))
		return -1;

	if (!m_sectionPreamp.CreateControl("PREAMP", 119, this, 0))
		return -1;

	// Volume
	if (!m_volume.CreateControl("VOLUME", CTRL_AMPKNOB1, 10, 135, this, 0))
		return -1;

	// PRESENCE
	if (!m_presence.CreateControl("PRESENCE", CTRL_AMPKNOB1, 69, 135, this, 0))
		return -1;

	// Master
	if (!m_master.CreateControl("MASTER", CTRL_AMPKNOB1, 125, 135, this, 0))
		return -1;

	// Bass
	if (!m_bass.CreateControl("BASS", CTRL_AMPKNOB1, 10, 189, this, 0))
		return -1;

	// Middle
	if (!m_middle.CreateControl("MIDDLE", CTRL_AMPKNOB1, 69, 189, this, 0))
		return -1;

	// Trebble
	if (!m_trebble.CreateControl("TREBBLE", CTRL_AMPKNOB1, 125, 189, this, 0))
		return -1;

	// Gain
	if (!m_gain.CreateControl("GAIN", CTRL_AMPKNOB2, 10, 249, this, 0))
		return -1;

	// Bright
	if (!m_bright.CreateControl("BRIGHT", CTRL_SWITCH1, 65, 249, this, 0))
		return -1;

	if (!m_sectionSpeaker.CreateControl("SPEAKER", 309, this, 0))
		return -1;

	// Speaker
	if (!m_speaker.CreateControl("TYPE", CTRL_EDIT1, 10, 326, this, 0))
		return -1;

	if (!m_mic1.CreateControl("", CTRL_MIC1, 20, 346, this, IDC_MIC))
		return -1;

	if (!m_mic2.CreateControl("", CTRL_MIC2, 40, 346, this, IDC_MIC))
		return -1;

	if (!m_speakerImage.CreateImageControl("TYPE", 70, 340, &g_speaker, 18, this, 0))
		return -1;

	// Mic set
	if (!m_micSet.CreateControl("MIC SET", CTRL_VGKNOB1, 10, 410, this, IDC_MIC))
		return -1;

	// balance
	if (!m_balance.CreateControl("BALANCE", CTRL_VGKNOB1, 90, 410, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelAmp::AttachVGData(CPatch *patch)
{
	int ampType;

	if (patch)
	{
		ampType = patch->cosmAmp.ampType.getValue();

		// Not all amps have a bright control
		if (ampType == AMP_JC_120 || ampType == AMP_JAZZ_COMBO || ampType == AMP_CLEAN_TWIN 
			|| ampType == AMP_PRO_CRUNCH || ampType == AMP_TWEED 
			|| ampType == AMP_CRUNCH || ampType == AMP_STACK_CRUNCH || ampType == AMP_BLUES
			|| ampType == AMP_BG_LEAD || ampType == AMP_BG_RYTHM)
			m_bright.ShowWindow(SW_SHOWNOACTIVATE);
		else
			m_bright.ShowWindow(SW_HIDE);

		if (ampType == AMP_MATCH_DRIVE || ampType == AMP_MATCH_LEAD || ampType == AMP_FAT_MATCH
			|| ampType ==  AMP_VO_DRIVE || ampType == AMP_VO_CLEAN || ampType == AMP_VO_LEAD)
			m_presence.SetWindowText("HIGH CUT");
		else
			m_presence.SetWindowText("PRESENCE");			

		m_onOff.AttachVGData(&patch->cosmAmp.ampOnOff);
		m_ledOnOff.AttachVGData(&patch->cosmAmp.ampOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}


	if (patch && patch->cosmAmp.ampOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_ampType.AttachVGData(&patch->cosmAmp.ampType);
		m_ampTypeImage.AttachVGData(&patch->cosmAmp.ampType);
		m_volume.AttachVGData(&patch->amp.volume);
		m_presence.AttachVGData(&patch->amp.presenceHighCut);
		m_master.AttachVGData(&patch->amp.master);
		m_bass.AttachVGData(&patch->amp.bass);
		m_middle.AttachVGData(&patch->amp.middle);
		m_trebble.AttachVGData(&patch->amp.trebble);
		m_gain.AttachVGData(&patch->amp.gain);
		m_bright.AttachVGData(&patch->amp.bright);
		m_speaker.AttachVGData(&patch->amp.speaker);
		m_speakerImage.AttachVGData(&patch->amp.speaker);
		m_balance.AttachVGData(&patch->amp.balance);
		m_micSet.AttachVGData(&patch->amp.micSet);
		m_mic1.AttachVGData(&patch->amp.micSet);
		m_mic2.AttachVGData(&patch->amp.micSet);

		switch (patch->amp.speaker.getValue())
		{
			case SPEAKER_TWIN_OFF:
			case SPEAKER_MATCH_OFF:
			case SPEAKER_VO_OFF:
			case SPEAKER_BG_STACK_OFF:
			case SPEAKER_MS_STACK_OFF:
			case SPEAKER_METAL_STACK:
			case SPEAKER_R_FIER:
				m_mic1.ShowWindow(SW_SHOWNA);
				m_mic2.ShowWindow(SW_HIDE);
				m_balance.ShowWindow(SW_SHOWNA);
				m_micSet.ShowWindow(SW_SHOWNA);
				break;

			case SPEAKER_SMALL:
			case SPEAKER_MIDDLE:
			case SPEAKER_JC_120:
			case SPEAKER_TWIN_ON:
			case SPEAKER_MATCH_ON:
			case SPEAKER_VO_ON:
			case SPEAKER_BG_STACK_ON:
			case SPEAKER_MS_STACK_ON:
			case SPEAKER_PRO_RVB:
			case SPEAKER_TWEED:
				m_mic1.ShowWindow(SW_HIDE);
				m_mic2.ShowWindow(SW_SHOWNA);
				m_balance.ShowWindow(SW_SHOWNA);
				m_micSet.ShowWindow(SW_SHOWNA);
				break;

			default:
				m_mic1.ShowWindow(SW_HIDE);
				m_mic2.ShowWindow(SW_HIDE);
				m_balance.ShowWindow(SW_HIDE);
				m_micSet.ShowWindow(SW_HIDE);
				break;
		}
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_ampType.AttachVGData(NULL);
		m_ampTypeImage.AttachVGData(NULL);
		m_volume.AttachVGData(NULL);
		m_presence.AttachVGData(NULL);
		m_master.AttachVGData(NULL);
		m_bass.AttachVGData(NULL);
		m_middle.AttachVGData(NULL);
		m_trebble.AttachVGData(NULL);
		m_gain.AttachVGData(NULL);
		m_bright.AttachVGData(NULL);
		m_speaker.AttachVGData(NULL);
		m_speakerImage.AttachVGData(NULL);
		m_balance.AttachVGData(NULL);
		m_micSet.AttachVGData(NULL);
		m_mic1.AttachVGData(NULL);
		m_mic2.AttachVGData(NULL);

		m_mic2.ShowWindow(SW_HIDE);
		m_mic1.ShowWindow(SW_HIDE);
	}	
}


BOOL CPanelAmp::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == IDC_MIC)
	{
		m_mic1.Invalidate(FALSE);
		m_mic2.Invalidate(FALSE);
		m_micSet.Invalidate(FALSE);
	}
	else
	if (wParam == IDC_AMP_TYPE)
	{
		switch(m_ampType.m_vgData->getValue())
		{
			case AMP_JC_120:
			case AMP_JAZZ_COMBO:
				m_speaker.m_vgData->setValue(SPEAKER_JC_120);
				break;

			case AMP_CLEAN_TWIN:
				m_speaker.m_vgData->setValue(SPEAKER_TWIN_ON);
				break;

			case AMP_CRUNCH:
			case AMP_MATCH_DRIVE:
			case AMP_BLUES:
			case AMP_MATCH_LEAD:
			case AMP_FAT_MATCH:
				m_speaker.m_vgData->setValue(SPEAKER_MATCH_ON);
				break;
			
			case AMP_VO_DRIVE:
			case AMP_VO_CLEAN:
			case AMP_VO_LEAD:
				m_speaker.m_vgData->setValue(SPEAKER_VO_ON);
				break;
			
			case AMP_BG_LEAD:
			case AMP_BG_RYTHM:
			case AMP_BG_DRIVE:
				m_speaker.m_vgData->setValue(SPEAKER_BG_STACK_OFF);
				break;

			case AMP_MS1959_I:
			case AMP_MS1959_II:
			case AMP_MS1959_I_II:
			case AMP_MS_HIGH_GAIN:
			case AMP_SLDN_LEAD:
				m_speaker.m_vgData->setValue(SPEAKER_MS_STACK_OFF);
				break;
			
			case AMP_METAL5150:
			case AMP_METAL_DRIVE:
			case AMP_STACK_CRUNCH:
			case AMP_DRIVE_STACK:
			case AMP_LEAD_STACK:
			case AMP_METAL_STACK:
			case AMP_METAL_LEAD:
				m_speaker.m_vgData->setValue(SPEAKER_METAL_STACK);
				break;
			
			case AMP_AC_GUITAR:
				m_speaker.m_vgData->setValue(SPEAKER_ACOUSTIC);
				break;

			case AMP_R_FIER_RED:
			case AMP_R_FIER_ORANGE:
			case AMP_R_FIER_VINT:
				m_speaker.m_vgData->setValue(SPEAKER_R_FIER);
				break;

			case AMP_TWEED:
				m_speaker.m_vgData->setValue(SPEAKER_TWEED);
				break;

			case AMP_PRO_CRUNCH:
				m_speaker.m_vgData->setValue(SPEAKER_PRO_RVB);
				break;
		}
	}
	else
	{
		// Notify the parent window that a refresh of the panel is needed
		GetParent()->PostMessage(WM_COMMAND, wParam, (long) this);
	}

	return CPanel::OnCommand(wParam, lParam);
}

CString	CPanelAmp::getPresetDir()
{
	return "preset\\Amp\\";
}


int CPanelAmp::setAllPanelData(char *buffer)
{
	int count;

	count = g_currentPatch->cosmAmp.setVGData(&buffer);
	count += g_currentPatch->amp.setVGData(&buffer);
	return count;
}


int CPanelAmp::getAllPanelData(char *buffer)
{
	int count;
	
	count = g_currentPatch->cosmAmp.getVGData(&buffer);
	count += g_currentPatch->amp.getVGData(&buffer);

	return count;
}

//////////////// CPanelEqualizer ///////////////

BEGIN_MESSAGE_MAP(CPanelEqualizer, CPanel)
	//{{AFX_MSG_MAP(CPanelEqualizer)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelEqualizer::CPanelEqualizer()
{
}


int CPanelEqualizer::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_COSMEQ_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_COSMEQ_ONOFF))
		return -1;

	if (!m_labels.CreateImageControl("", 17, 135, &g_eqLabel, 0, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VFADER1, 10, 35, this, 0))
		return -1;

	if (!m_lowG.CreateControl("LOW G", CTRL_VFADER1, 28, 35, this, 0))
		return -1;

	if (!m_highG.CreateControl("HIGH G", CTRL_VFADER1, 46, 35, this, 0))
		return -1;

	if (!m_lMidG.CreateControl("L-MID G", CTRL_VFADER1, 64, 35, this, 0))
		return -1;

	if (!m_hMidG.CreateControl("H-MID G", CTRL_VFADER1, 82, 35, this, 0))
		return -1;

	if (!m_lMidQ.CreateControl("L-MID Q", CTRL_VFADER1, 100, 35, this, 0))
		return -1;

	if (!m_hMidQ.CreateControl("H-MID Q", CTRL_VFADER1, 118, 35, this, 0))
		return -1;

	if (!m_hMidF.CreateControl("H-MID F", CTRL_VFADER1, 136, 35, this, 0))
		return -1;

	if (!m_lMidF.CreateControl("L-MID F", CTRL_VFADER1, 154, 35, this, 0))
		return -1;

	m_level.m_labelPosition = DATA_NONE;
	m_lowG.m_labelPosition  = DATA_NONE;
	m_highG.m_labelPosition = DATA_NONE;
	m_lMidG.m_labelPosition = DATA_NONE;
	m_hMidG.m_labelPosition = DATA_NONE;
	m_lMidQ.m_labelPosition = DATA_NONE;
	m_hMidQ.m_labelPosition = DATA_NONE;
	m_hMidF.m_labelPosition = DATA_NONE;
	m_lMidF.m_labelPosition = DATA_NONE;

	AttachVGData(g_currentPatch);

	return 0;
}




void CPanelEqualizer::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_onOff.AttachVGData(&patch->cosmEqOnOff);
		m_ledOnOff.AttachVGData(&patch->cosmEqOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->cosmEqOnOff.getValue() && patch->cosmGT.guitarOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_level.AttachVGData(&patch->cosmEq.level);
		m_lowG.AttachVGData(&patch->cosmEq.lowG);
		m_hMidG.AttachVGData(&patch->cosmEq.hMidG);
		m_lMidG.AttachVGData(&patch->cosmEq.lMidG);
		m_highG.AttachVGData(&patch->cosmEq.highG);
		m_lMidQ.AttachVGData(&patch->cosmEq.lMidQ);
		m_hMidQ.AttachVGData(&patch->cosmEq.hMidQ);
		m_hMidF.AttachVGData(&patch->cosmEq.hMidF);
		m_lMidF.AttachVGData(&patch->cosmEq.lMidF);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_lowG.AttachVGData(NULL);
		m_hMidG.AttachVGData(NULL);
		m_lMidG.AttachVGData(NULL);
		m_highG.AttachVGData(NULL);
		m_lMidQ.AttachVGData(NULL);
		m_hMidQ.AttachVGData(NULL);
		m_hMidF.AttachVGData(NULL);
		m_lMidF.AttachVGData(NULL);
	}
}


CString	CPanelEqualizer::getPresetDir()
{
	return "preset\\CosmEq\\";
}


int CPanelEqualizer::setAllPanelData(char *buffer)
{
	return g_currentPatch->cosmEq.setVGData(&buffer);
}


int CPanelEqualizer::getAllPanelData(char *buffer)
{
	return g_currentPatch->cosmEq.getVGData(&buffer);
}

//////////////// CPanelEqualizerEff ///////////////

BEGIN_MESSAGE_MAP(CPanelEqualizerEff, CPanel)
	//{{AFX_MSG_MAP(CPanelEqualizerEff)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelEqualizerEff::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_EQ_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_EQ_ONOFF))
		return -1;

	if (!m_labels.CreateImageControl("", 17, 195, &g_eqLabel, 0, this, 0))
		return -1;

	if (!m_eqImage.CreateImageControl("", 9, 40, &g_sEffEq, 0, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VFADER1, 10, 95, this, 0))
		return -1;

	if (!m_lowG.CreateControl("LOW G", CTRL_VFADER1, 28, 95, this, 0))
		return -1;

	if (!m_highG.CreateControl("HIGH G", CTRL_VFADER1, 46, 95, this, 0))
		return -1;

	if (!m_lMidG.CreateControl("L-MID G", CTRL_VFADER1, 64, 95, this, 0))
		return -1;

	if (!m_hMidG.CreateControl("H-MID G", CTRL_VFADER1, 82, 95, this, 0))
		return -1;

	if (!m_lMidQ.CreateControl("L-MID Q", CTRL_VFADER1, 100, 95, this, 0))
		return -1;

	if (!m_hMidQ.CreateControl("H-MID Q", CTRL_VFADER1, 118, 95, this, 0))
		return -1;

	if (!m_hMidF.CreateControl("H-MID F", CTRL_VFADER1, 136, 95, this, 0))
		return -1;

	if (!m_lMidF.CreateControl("L-MID F", CTRL_VFADER1, 154, 95, this, 0))
		return -1;

	m_level.m_labelPosition = DATA_NONE;
	m_lowG.m_labelPosition  = DATA_NONE;
	m_highG.m_labelPosition = DATA_NONE;
	m_lMidG.m_labelPosition = DATA_NONE;
	m_hMidG.m_labelPosition = DATA_NONE;
	m_lMidQ.m_labelPosition = DATA_NONE;
	m_hMidQ.m_labelPosition = DATA_NONE;
	m_hMidF.m_labelPosition = DATA_NONE;
	m_lMidF.m_labelPosition = DATA_NONE;

	AttachVGData(g_currentPatch);

	return 0;
}

CPanelEqualizerEff::CPanelEqualizerEff()
{
}


void CPanelEqualizerEff::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->eqOnOff);
		m_ledOnOff.AttachVGData(&patch->eqOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->eqOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_level.AttachVGData(&patch->eq.level);
		m_lowG.AttachVGData(&patch->eq.lowG);
		m_hMidG.AttachVGData(&patch->eq.hMidG);
		m_lMidG.AttachVGData(&patch->eq.lMidG);
		m_highG.AttachVGData(&patch->eq.highG);
		m_lMidQ.AttachVGData(&patch->eq.lMidQ);
		m_hMidQ.AttachVGData(&patch->eq.hMidQ);
		m_hMidF.AttachVGData(&patch->eq.hMidF);
		m_lMidF.AttachVGData(&patch->eq.lMidF);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_lowG.AttachVGData(NULL);
		m_hMidG.AttachVGData(NULL);
		m_lMidG.AttachVGData(NULL);
		m_highG.AttachVGData(NULL);
		m_lMidQ.AttachVGData(NULL);
		m_hMidQ.AttachVGData(NULL);
		m_hMidF.AttachVGData(NULL);
		m_lMidF.AttachVGData(NULL);
	}
}


CString	CPanelEqualizerEff::getPresetDir()
{
	return "preset\\CosmEq\\";
}


int CPanelEqualizerEff::setAllPanelData(char *buffer)
{
	return g_currentPatch->eq.setVGData(&buffer);
}


int CPanelEqualizerEff::getAllPanelData(char *buffer)
{
	return g_currentPatch->eq.getVGData(&buffer);
}

//////////////// CPanelPan ///////////////

BEGIN_MESSAGE_MAP(CPanelPan, CPanel)
	//{{AFX_MSG_MAP(CPanelPan)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPan::CPanelPan()
{
}


int CPanelPan::OnCreate(LPCREATESTRUCT lpcs)
{
	//char caption[50];
	CPanel::OnCreate(lpcs);

	int i;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;


	if (!m_labels.CreateImageControl("", 11, 42, &g_labelPan, 0, this, 0))
		return -1;

	for (i = 0; i < 6; i++)
	{
		//sprintf(caption, "STRING-%d", i + 1);

		if (!m_string[i].CreateControl("", CTRL_HFADER1, 52, 32 + (24 * i), this, 0))
			return -1;
	}

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPan::AttachVGData(CPatch *patch)
{
	int i;

	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);

		for (i = 0; i < 6; i++)
			m_string[i].AttachVGData(&patch->cosmPan.string[i]);
	}
	else
	{
		m_preset.AttachVGData(NULL);

		for (i = 0; i < 6; i++)
			m_string[i].AttachVGData(NULL);
	}
}


CString	CPanelPan::getPresetDir()
{
	return "preset\\CosmPan\\";
}


int CPanelPan::setAllPanelData(char *buffer)
{
	return g_currentPatch->cosmPan.setVGData(&buffer);
}


int CPanelPan::getAllPanelData(char *buffer)
{
	return g_currentPatch->cosmPan.getVGData(&buffer);
}


//////////////// CPanelMixer ///////////////

BEGIN_MESSAGE_MAP(CPanelMixer, CPanel)
	//{{AFX_MSG_MAP(CPanelMixer)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelMixer::CPanelMixer()
{
}


int CPanelMixer::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_balance.CreateControl("BALANCE", CTRL_VGKNOB1, 24, 40, this, 0))
			return -1;

	if (!m_puPola.CreateControl("PU POLA", CTRL_SWITCH1, 84, 40, this, 0))
			return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 130, 40, this, 0))
			return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelMixer::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_balance.AttachVGData(&patch->cosmMixer.balance);
		m_puPola.AttachVGData(&patch->cosmMixer.puPola);
		m_level.AttachVGData(&patch->cosmMixer.level);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_balance.AttachVGData(NULL);
		m_puPola.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
	}
}


CString	CPanelMixer::getPresetDir()
{
	return "preset\\CosmMixer\\";
}


int CPanelMixer::setAllPanelData(char *buffer)
{
	return g_currentPatch->cosmMixer.setVGData(&buffer);
}


int CPanelMixer::getAllPanelData(char *buffer)
{
	return g_currentPatch->cosmMixer.getVGData(&buffer);
}

//////////////// CPanelPitchShift ///////////////

BEGIN_MESSAGE_MAP(CPanelPitchShift, CPanel)
	//{{AFX_MSG_MAP(CPanelPitchShift)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPitchShift::CPanelPitchShift()
{
}


int CPanelPitchShift::OnCreate(LPCREATESTRUCT lpcs)
{
	int i;
	char caption[50];

	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_PTSHIFT_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_PTSHIFT_ONOFF))
		return -1;

	if (!m_pedalImage.CreateImageControl("", 9, 40, &g_sEffPedShift, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("MODE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;



	if (!m_sectionShift.CreateControl("SHIFT", 80, this, 0))
		return -1;

	if (!m_sectionHarmo.CreateControl("HARMO", 80, this, 0))
		return -1;


	for (i = 0; i < 6; i++)
	{
		sprintf(caption, "ST-%d", 6 - i);

		if (!m_shift[5 - i].CreateControl(caption, CTRL_VFADER1, 11 + i * 27, 100, this, 0))
				return -1;
	}

	for (i = 0; i < 6; i++)
	{
		sprintf(caption, "ST-%d", 6 - i);

		if (!m_harmo[5 - i].CreateControl(caption, CTRL_VGKNOB2, 10 + i * 27, 102, this, 0))
			return -1;
	}

	if (!m_sectionKey.CreateControl("KEY", 165, this, 0))
		return -1;

	if (!m_key.CreateControl("KEY", CTRL_EDIT1, 10, 185, this, 0))
		return -1;

	if (!m_keyImage.CreateImageControl("KEY", 60, 230, &g_key, 12, this, 0))
		return -1;

	if (!m_sectionFine.CreateControl("FINE", 215, this, 0))
		return -1;

	for (i = 0; i < 6; i++)
	{
		sprintf(caption, "ST-%d", 6 - i);

		if (!m_fine[5 - i].CreateControl(caption, CTRL_VGKNOB2, 10 + i * 27, 237, this, 0))
			return -1;
	}



	if (!m_sectionELevel.CreateControl("E.LEVEL", 300, this, 0))
		return -1;

	for (i = 0; i < 6; i++)
	{
		sprintf(caption, "ST-%d", 6 - i);

		if (!m_eLevel[5 - i].CreateControl(caption, CTRL_VGKNOB2, 10 + i * 27, 327, this, 0))
			return -1;
	}



	if (!m_sectionDLevel.CreateControl("D.LEVEL", 390, this, 0))
		return -1;

	for (i = 0; i < 6; i++)
	{
		sprintf(caption, "ST-%d", 6 - i);

		if (!m_dLevel[5 - i].CreateControl(caption, CTRL_VGKNOB2, 10 + i * 27, 418, this, 0))
			return -1;
	}

	return 0;
}


void CPanelPitchShift::AttachVGData(CPatch *patch)
{
	CPitchShift	*ppitchShift;
	int i;

	if (patch)
	{
		if (patch->cosmGT.guitarType.getValue() != COSMGT_VARI_GT)
			return;
	
		ppitchShift = &(((CVariGuitar *) patch->instrument)->pitchShift);

		if (patch->cosmGT.guitarOnOff.getValue())
		{
			m_onOff.AttachVGData(&((CVariGuitar *) patch->instrument)->ptShiftOnOff);
			m_ledOnOff.AttachVGData(&((CVariGuitar *) patch->instrument)->ptShiftOnOff);
			m_preset.AttachVGData(&m_presetData);
		}
		else
		{
			m_onOff.AttachVGData(NULL);
			m_ledOnOff.AttachVGData(NULL);
		}

		if (ppitchShift->mode.getValue() == PS_SHIFT)
		{
			for (i = 0; i < 6; i++)
			{
				m_fine[i].ShowWindow(SW_SHOWNA);
				m_shift[i].ShowWindow(SW_SHOWNA);
				m_harmo[i].ShowWindow(SW_HIDE);
			}

			m_sectionShift.ShowWindow(SW_SHOWNA);
			m_sectionFine.ShowWindow(SW_SHOWNA);
			m_key.ShowWindow(SW_HIDE);
			m_keyImage.ShowWindow(SW_HIDE);
			m_sectionHarmo.ShowWindow(SW_HIDE);
			m_sectionKey.ShowWindow(SW_HIDE);
		}
		else
		{
			for (i = 0; i < 6; i++)
			{
				m_fine[i].ShowWindow(SW_HIDE);
				m_shift[i].ShowWindow(SW_HIDE);
				m_harmo[i].ShowWindow(SW_SHOWNA);
			}

			m_sectionShift.ShowWindow(SW_HIDE);
			m_sectionFine.ShowWindow(SW_HIDE);
			m_key.ShowWindow(SW_SHOWNA);
			m_keyImage.ShowWindow(SW_SHOWNA);
			m_sectionHarmo.ShowWindow(SW_SHOWNA);
			m_sectionKey.ShowWindow(SW_SHOWNA);
		}

	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);

		for (i = 0; i < 6; i++)
		{
			m_fine[i].ShowWindow(SW_SHOWNA);
			m_shift[i].ShowWindow(SW_SHOWNA);
			m_harmo[i].ShowWindow(SW_HIDE);
		}

		m_sectionShift.ShowWindow(SW_SHOWNA);
		m_sectionFine.ShowWindow(SW_SHOWNA);
		m_key.ShowWindow(SW_HIDE);
		m_keyImage.ShowWindow(SW_HIDE);
		m_sectionHarmo.ShowWindow(SW_HIDE);
		m_sectionKey.ShowWindow(SW_HIDE);
	}


	if (patch && ((CVariGuitar *) patch->instrument)->ptShiftOnOff.getValue() && patch->cosmGT.guitarOnOff.getValue())
	{
		m_mode.AttachVGData(&ppitchShift->mode);

		for (i = 0; i < 6; i++)
		{
			m_shift[i].AttachVGData(&ppitchShift->shift[i]);
			ppitchShift->shift[i].setStringNum(i);
			m_fine[i].AttachVGData(&ppitchShift->fine[i]);
			m_eLevel[i].AttachVGData(&ppitchShift->eLevel[i]);
			m_dLevel[i].AttachVGData(&ppitchShift->dLevel[i]);
			m_harmo[i].AttachVGData(&ppitchShift->harmo[i]);
		}

		m_key.AttachVGData(&patch->assignNC.key);
		m_keyImage.AttachVGData(&patch->assignNC.key);
	}
	else
	{
		m_mode.AttachVGData(NULL);
		m_preset.AttachVGData(NULL);

		for (i = 0; i < 6; i++)
		{
			m_shift[i].AttachVGData(NULL);
			m_fine[i].AttachVGData(NULL);
			m_eLevel[i].AttachVGData(NULL);
			m_dLevel[i].AttachVGData(NULL);
			m_harmo[i].AttachVGData(NULL);
		}

		m_key.AttachVGData(NULL);
		m_keyImage.AttachVGData(NULL);
	}
}



CString	CPanelPitchShift::getPresetDir()
{
	return "preset\\Instrument\\ptShift\\";
}


int CPanelPitchShift::setAllPanelData(char *buffer)
{
	CPitchShift	*ppitchShift = &(((CVariGuitar *) g_currentPatch->instrument)->pitchShift);

	return ppitchShift->setVGData(&buffer);
}


int CPanelPitchShift::getAllPanelData(char *buffer)
{
	CPitchShift	*ppitchShift = &(((CVariGuitar *) g_currentPatch->instrument)->pitchShift);

	return ppitchShift->getVGData(&buffer);
}



//////////////// CPanelFV ///////////////

BEGIN_MESSAGE_MAP(CPanelFV, CPanel)
	//{{AFX_MSG_MAP(CPanelFV)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelFV::CPanelFV()
{
}


int CPanelFV::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_volumeKnob.CreateControl("LEVEL", CTRL_VGKNOB1, 20, 45, this, IDC_FV_VOLUME))
			return -1;

	if (!m_volume.CreateImageControl("LEVEL", 75, 50, &g_wah2, 16, this, 0))
			return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelFV::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_volumeKnob.AttachVGData(&patch->fv.level);
		m_volume.AttachVGData(&patch->fv.level);
	}
	else
	{
		m_volumeKnob.AttachVGData(NULL);
		m_volume.AttachVGData(NULL);
	}
}


BOOL CPanelFV::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == IDC_FV_VOLUME)
	{
		m_volumeKnob.Invalidate(FALSE);
		m_volume.Invalidate(FALSE);
	}
	else
	{
		// Notify the parent window that a refresh of the panel is needed
		GetParent()->PostMessage(WM_COMMAND, wParam, (long) this);
	}

	return CWnd ::OnCommand(wParam, lParam);
}


//////////////// CPanelNS ///////////////

BEGIN_MESSAGE_MAP(CPanelNS, CPanel)
	//{{AFX_MSG_MAP(CPanelNS)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelNS::CPanelNS()
{
}


int CPanelNS::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_NS_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_NS_ONOFF))
		return -1;

	if (!m_nsImage.CreateImageControl("", 9, 40, &g_sEffNS, 0, this, 0))
		return -1;

	if (!m_threshold.CreateControl("THRESHOLD", CTRL_VGKNOB1, 66, 45, this, 0))
			return -1;

	if (!m_release.CreateControl("RELEASE", CTRL_VGKNOB1, 122, 45, this, 0))
			return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelNS::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->nsOnOff);
		m_ledOnOff.AttachVGData(&patch->nsOnOff);	
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->nsOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_threshold.AttachVGData(&patch->ns.threshold);
		m_release.AttachVGData(&patch->ns.release);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_threshold.AttachVGData(NULL);
		m_release.AttachVGData(NULL);
	}
}


CString	CPanelNS::getPresetDir()
{
	return "preset\\ns\\";
}


int CPanelNS::setAllPanelData(char *buffer)
{
	return g_currentPatch->ns.setVGData(&buffer);
}


int CPanelNS::getAllPanelData(char *buffer)
{
	return g_currentPatch->ns.getVGData(&buffer);
}


//////////////// CPanelReverb ///////////////

BEGIN_MESSAGE_MAP(CPanelReverb, CPanel)
	//{{AFX_MSG_MAP(CPanelReverb)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelReverb::CPanelReverb()
{
}


int CPanelReverb::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_REVERB_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_REVERB_ONOFF))
		return -1;

	if (!m_reverbImage.CreateImageControl("", 9, 40, &g_sEffReverb, 0, this, 0))
		return -1;

	// Reverb mode
	if (!m_mode.CreateControl("MODE", CTRL_EDIT2, 65, 41, this, 0))
		return -1;

	if (!m_density.CreateControl("DENSITY", CTRL_VGKNOB1, 10, 117, this, 0))
		return -1;

	// reverbTime
	if (!m_reverbTime.CreateControl("REV TIME", CTRL_VGKNOB1, 69, 117, this, 0))
		return -1;

	// lowCut
	if (!m_lowCut.CreateControl("LOW CUT", CTRL_VGKNOB1, 125, 117, this, 0))
		return -1;

	// highCut
	if (!m_highCut.CreateControl("HIGH CUT", CTRL_VGKNOB1, 10, 173, this, 0))
		return -1;

	// preDly
	if (!m_preDly.CreateControl("PRE _DLY", CTRL_VGKNOB1, 69, 173, this, 0))
		return -1;

	// revLev
	if (!m_revLev.CreateControl("REV LEV", CTRL_VGKNOB1, 125, 173, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelReverb::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->reverbOnOff);
		m_ledOnOff.AttachVGData(&patch->reverbOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->reverbOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->reverb.reverbMode);
		m_density.AttachVGData(&patch->reverb.density);
		m_reverbTime.AttachVGData(&patch->reverb.reverbTime);
		m_lowCut.AttachVGData(&patch->reverb.lowCut);
		m_highCut.AttachVGData(&patch->reverb.highCut);
		m_preDly.AttachVGData(&patch->reverb.preDly);
		m_revLev.AttachVGData(&patch->reverb.revLev);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_density.AttachVGData(NULL);
		m_reverbTime.AttachVGData(NULL);
		m_lowCut.AttachVGData(NULL);
		m_highCut.AttachVGData(NULL);
		m_preDly.AttachVGData(NULL);
		m_revLev.AttachVGData(NULL);
	}
}


CString	CPanelReverb::getPresetDir()
{
	return "preset\\Effect\\reverb\\";
}


int CPanelReverb::setAllPanelData(char *buffer)
{
	return g_currentPatch->reverb.setVGData(&buffer);
}


int CPanelReverb::getAllPanelData(char *buffer)
{
	return g_currentPatch->reverb.getVGData(&buffer);
}


//////////////// CPanelDelay ///////////////

BEGIN_MESSAGE_MAP(CPanelDelay, CPanel)
	//{{AFX_MSG_MAP(CPanelDelay)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelDelay::CPanelDelay()
{
}


int CPanelDelay::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);


	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_DELAY_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_DELAY_ONOFF))
		return -1;

	if (!m_dlyImage.CreateImageControl("", 9, 40, &g_sEffDelay, 0, this, 0))
		return -1;

	if (!m_dlyTime.CreateControl("DLY TIME", CTRL_VGKNOB1, 10, 117, this, 0))
			return -1;

	if (!m_tapeTime.CreateControl("TAP TIME", CTRL_VGKNOB1, 69, 117, this, 0))
			return -1;

	if (!m_feedback.CreateControl("FEEDBACK", CTRL_VGKNOB1, 125, 117, this, 0))
			return -1;

	if (!m_highCut.CreateControl("HIGH CUT", CTRL_VGKNOB1, 69, 173, this, 0))
		return -1;

	if (!m_dlyLev.CreateControl("DLY LEV", CTRL_VGKNOB1, 125, 173, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelDelay::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->delayOnOff);
		m_ledOnOff.AttachVGData(&patch->delayOnOff);	
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->delayOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_dlyLev.AttachVGData(&patch->delay.dlyLev);
		m_tapeTime.AttachVGData(&patch->delay.tapeTime);
		m_feedback.AttachVGData(&patch->delay.feedback);
		m_highCut.AttachVGData(&patch->delay.highCut);
		m_dlyTime.AttachVGData(&patch->delay.dlyTime);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_dlyLev.AttachVGData(NULL);
		m_tapeTime.AttachVGData(NULL);
		m_feedback.AttachVGData(NULL);
		m_highCut.AttachVGData(NULL);
		m_dlyTime.AttachVGData(NULL);
	}
}

CString	CPanelDelay::getPresetDir()
{
	return "preset\\Effect\\delay\\";
}


int CPanelDelay::setAllPanelData(char *buffer)
{
	return g_currentPatch->delay.setVGData(&buffer);
}


int CPanelDelay::getAllPanelData(char *buffer)
{
	return g_currentPatch->delay.getVGData(&buffer);
}



//////////////// CPanelChorus ///////////////

BEGIN_MESSAGE_MAP(CPanelChorus, CPanel)
	//{{AFX_MSG_MAP(CPanelChorus)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelChorus::CPanelChorus()
{
}


int CPanelChorus::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);


	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_CHORUS_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_CHORUS_ONOFF))
		return -1;

	if (!m_chorusImage.CreateImageControl("", 9, 40, &g_sEffChorus, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("MODE", CTRL_SWITCH1, 10, 117, this, 0))
			return -1;

	if (!m_rate.CreateControl("RATE", CTRL_VGKNOB1, 69, 117, this, 0))
			return -1;

	if (!m_depth.CreateControl("DEPTH", CTRL_VGKNOB1, 125, 117, this, 0))
			return -1;

	if (!m_preDly.CreateControl("PRE DLY", CTRL_VGKNOB1, 10, 173, this, 0))
			return -1;

	if (!m_highCut.CreateControl("HIGH CUT", CTRL_VGKNOB1, 69, 173, this, 0))
		return -1;

	if (!m_cLevel.CreateControl("CE LEVEL", CTRL_VGKNOB1, 125, 173, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelChorus::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->chorusOnOff);
		m_ledOnOff.AttachVGData(&patch->chorusOnOff);	
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->chorusOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->chorus.mode);
		m_rate.AttachVGData(&patch->chorus.rate);
		m_depth.AttachVGData(&patch->chorus.depth);
		m_preDly.AttachVGData(&patch->chorus.preDly);
		m_highCut.AttachVGData(&patch->chorus.highCut);
		m_cLevel.AttachVGData(&patch->chorus.cLevel);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_rate.AttachVGData(NULL);
		m_depth.AttachVGData(NULL);
		m_preDly.AttachVGData(NULL);
		m_highCut.AttachVGData(NULL);
		m_cLevel.AttachVGData(NULL);
	}
}

CString	CPanelChorus::getPresetDir()
{
	return "preset\\Effect\\chorus\\";
}


int CPanelChorus::setAllPanelData(char *buffer)
{
	return g_currentPatch->chorus.setVGData(&buffer);
}


int CPanelChorus::getAllPanelData(char *buffer)
{
	return g_currentPatch->chorus.getVGData(&buffer);
}



//////////////// CPanelCompressor ///////////////

BEGIN_MESSAGE_MAP(CPanelCompressor, CPanel)
	//{{AFX_MSG_MAP(CPanelCompressor)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelCompressor::CPanelCompressor()
{
}


int CPanelCompressor::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);


	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_COMP_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_COMP_ONOFF))
		return -1;

	if (!m_compImage.CreateImageControl("", 9, 40, &g_sEffComp, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("MODE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

	if (!m_sustain.CreateControl("SUSTAIN", CTRL_VGKNOB1, 69, 78, this, 0))
			return -1;

	if (!m_attack.CreateControl("ATTACK", CTRL_VGKNOB1, 125, 78, this, 0))
			return -1;

	if (!m_tone.CreateControl("TONE", CTRL_VGKNOB1, 10, 135, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 69, 135, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelCompressor::AttachVGData(CPatch *patch)
{
	CCompComp *comp;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->compOnOff);
		m_ledOnOff.AttachVGData(&patch->compOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->compOnOff.getValue())
	{
		comp = (CCompComp *) patch->comp.comp;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->comp.compType);
		m_sustain.AttachVGData(&comp->sustain);
		m_attack.AttachVGData(&comp->attack);
		m_tone.AttachVGData(&comp->tone);
		m_level.AttachVGData(&comp->level);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_sustain.AttachVGData(NULL);
		m_attack.AttachVGData(NULL);
		m_tone.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
	}
}


CString	CPanelCompressor::getPresetDir()
{
	return "preset\\Effect\\CompLim\\";
}


int CPanelCompressor::setAllPanelData(char *buffer)
{
	return g_currentPatch->comp.setVGData(&buffer);
}


int CPanelCompressor::getAllPanelData(char *buffer)
{
	return g_currentPatch->comp.getVGData(&buffer);
}


//////////////// CPanelLimiter ///////////////

BEGIN_MESSAGE_MAP(CPanelLimiter, CPanel)
	//{{AFX_MSG_MAP(CPanelLimiter)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelLimiter::CPanelLimiter()
{
}


int CPanelLimiter::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_COMP_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_COMP_ONOFF))
		return -1;

	if (!m_limiterImage.CreateImageControl("", 9, 40, &g_sEffComp, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("MODE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

	if (!m_threshold.CreateControl("THRESHOLD", CTRL_VGKNOB1, 69, 78, this, 0))
			return -1;

	if (!m_release.CreateControl("RELEASE", CTRL_VGKNOB1, 125, 78, this, 0))
			return -1;

	if (!m_tone.CreateControl("TONE", CTRL_VGKNOB1, 10, 135, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 69, 135, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelLimiter::AttachVGData(CPatch *patch)
{
	CCompLim *comp;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->compOnOff);
		m_ledOnOff.AttachVGData(&patch->compOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->compOnOff.getValue())
	{
		comp = (CCompLim *) patch->comp.comp;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->comp.compType);
		m_threshold.AttachVGData(&comp->threshold);
		m_release.AttachVGData(&comp->release);
		m_tone.AttachVGData(&comp->tone);
		m_level.AttachVGData(&comp->level);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_threshold.AttachVGData(NULL);
		m_release.AttachVGData(NULL);
		m_tone.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
	}
}


CString	CPanelLimiter::getPresetDir()
{
	return "preset\\Effect\\CompLim\\";
}


int CPanelLimiter::setAllPanelData(char *buffer)
{
	return g_currentPatch->comp.setVGData(&buffer);
}


int CPanelLimiter::getAllPanelData(char *buffer)
{
	return g_currentPatch->comp.getVGData(&buffer);
}


//////////////// CPanelPedalWah ///////////////

BEGIN_MESSAGE_MAP(CPanelPedalWah, CPanel)
	//{{AFX_MSG_MAP(CPanelPedalWah)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPedalWah::CPanelPedalWah()
{
}


int CPanelPedalWah::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_WAH_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_WAH_ONOFF))
		return -1;

	if (!m_pedalWahImage.CreateImageControl("", 9, 40, &g_sEffPedWah, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 41, this, 0))
		return -1;

	if (!m_model.CreateControl("MODEL", CTRL_EDIT2, 65, 68, this, 0))
		return -1;

	if (!m_freq.CreateControl("FREQ", CTRL_VGKNOB1, 69, 105, this, 0))
			return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 125, 105, this, 0))
			return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPedalWah::AttachVGData(CPatch *patch)
{
	CPedalWah *wah;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->wahOnOff);
		m_ledOnOff.AttachVGData(&patch->wahOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->wahOnOff.getValue())
	{
		wah = (CPedalWah *) patch->wah.wah;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->wah.wahType);
		m_model.AttachVGData(&wah->model);
		m_freq.AttachVGData(&wah->freq);
		m_level.AttachVGData(&wah->level);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_model.AttachVGData(NULL);
		m_freq.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
	}
}

CString	CPanelPedalWah::getPresetDir()
{
	return "preset\\Effect\\Wah\\";
}


int CPanelPedalWah::setAllPanelData(char *buffer)
{
	return g_currentPatch->wah.setVGData(&buffer);
}


int CPanelPedalWah::getAllPanelData(char *buffer)
{
	return g_currentPatch->wah.getVGData(&buffer);
}


//////////////// CPanelAutoWah ///////////////

BEGIN_MESSAGE_MAP(CPanelAutoWah, CPanel)
	//{{AFX_MSG_MAP(CPanelAutoWah)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelAutoWah::CPanelAutoWah()
{
}


int CPanelAutoWah::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_WAH_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_WAH_ONOFF))
		return -1;

	if (!m_autoWahImage.CreateImageControl("", 9, 40, &g_sEffAutoWah, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 41, this, 0))
		return -1;


	if (!m_autoWahMode.CreateControl("MODE", CTRL_SWITCH1, 66, 61, this, 0))
			return -1;

	if (!m_polarity.CreateControl("POLARITY", CTRL_SWITCH1, 122, 61, this, 0))
			return -1;

	if (!m_sens.CreateControl("SENS", CTRL_VGKNOB1, 10, 117, this, 0))
		return -1;

	if (!m_freq.CreateControl("FREQ", CTRL_VGKNOB1, 69, 117, this, 0))
		return -1;

	if (!m_peak.CreateControl("PEAK", CTRL_VGKNOB1, 125, 117, this, 0))
		return -1;

	if (!m_rate.CreateControl("RATE", CTRL_VGKNOB1, 10, 173, this, 0))
		return -1;

	if (!m_depth.CreateControl("DEPTH", CTRL_VGKNOB1, 69, 173, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 125, 173, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelAutoWah::AttachVGData(CPatch *patch)
{
	CAutoWah *wah;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->wahOnOff);
		m_ledOnOff.AttachVGData(&patch->wahOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->wahOnOff.getValue())
	{
		wah = (CAutoWah *) patch->wah.wah;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->wah.wahType);
		m_autoWahMode.AttachVGData(&wah->autoWahMode);
		m_polarity.AttachVGData(&wah->polarity);
		m_sens.AttachVGData(&wah->sens);
		m_freq.AttachVGData(&wah->freq);
		m_peak.AttachVGData(&wah->peak);
		m_rate.AttachVGData(&wah->rate);
		m_depth.AttachVGData(&wah->depth);
		m_level.AttachVGData(&wah->level);
	}
	else
	{
		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(NULL);
		m_autoWahMode.AttachVGData(NULL);
		m_polarity.AttachVGData(NULL);
		m_sens.AttachVGData(NULL);
		m_freq.AttachVGData(NULL);
		m_peak.AttachVGData(NULL);
		m_rate.AttachVGData(NULL);
		m_depth.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
	}
}


CString	CPanelAutoWah::getPresetDir()
{
	return "preset\\Effect\\Wah\\";
}


int CPanelAutoWah::setAllPanelData(char *buffer)
{
	return g_currentPatch->wah.setVGData(&buffer);
}


int CPanelAutoWah::getAllPanelData(char *buffer)
{
	return g_currentPatch->wah.getVGData(&buffer);
}


//////////////// CPanelVolBmpKey ///////////////

BEGIN_MESSAGE_MAP(CPanelVolBmpKey, CPanel)
	//{{AFX_MSG_MAP(CPanelVolBmpKey)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelVolBmpKey::CPanelVolBmpKey()
{
}


int CPanelVolBmpKey::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_level.CreateControl("LEVEL", 6, 20, 45, this, 0))
			return -1;

	if (!m_bmp.CreateControl("BPM", CTRL_VGKNOB1, 73, 45, this, 0))
			return -1;

	if (!m_key.CreateControl("KEY", CTRL_EDIT1, 10, 133, this, 0))
		return -1;

	if (!m_keyImage.CreateImageControl("KEY", 60, 168, &g_key, 12, this, 0))
		return -1;
	

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelVolBmpKey::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_level.AttachVGData(&patch->assignNC.level);
		m_bmp.AttachVGData(&patch->assignNC.bpm);
		m_key.AttachVGData(&patch->assignNC.key);
		m_keyImage.AttachVGData(&patch->assignNC.key);
	}
	else
	{
		m_level.AttachVGData(NULL);
		m_bmp.AttachVGData(NULL);
		m_key.AttachVGData(NULL);
		m_keyImage.AttachVGData(NULL);
	}
}





//////////////// CPanelVibrato ///////////////

BEGIN_MESSAGE_MAP(CPanelVibrato, CPanel)
	//{{AFX_MSG_MAP(CPanelVibrato)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelVibrato::CPanelVibrato()
{
}


int CPanelVibrato::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_vibratoImage.CreateImageControl("", 9, 40, &g_sEffVibrato, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;


	if (!m_trigger.CreateControl("TRIGGER", CTRL_SWITCH1, 66, 117, this, 0))
			return -1;

	if (!m_rate.CreateControl("RATE", CTRL_VGKNOB1, 122, 117, this, 0))
			return -1;

	if (!m_depth.CreateControl("DEPTH", CTRL_VGKNOB1, 10, 173, this, 0))
		return -1;

	if (!m_riseTime.CreateControl("RISE TIME", CTRL_VGKNOB1, 69, 173, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelVibrato::AttachVGData(CPatch *patch)
{
	CVibrato *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CVibrato *) patch->mod.mod;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->mod.modeType);
		m_trigger.AttachVGData(&mod->trigger);
		m_rate.AttachVGData(&mod->rate);
		m_depth.AttachVGData(&mod->depth);
		m_riseTime.AttachVGData(&mod->riseTime);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_trigger.AttachVGData(NULL);
		m_rate.AttachVGData(NULL);
		m_depth.AttachVGData(NULL);
		m_riseTime.AttachVGData(NULL);

	}
}

CString	CPanelVibrato::getPresetDir()
{
	return "preset\\Effect\\vibrato\\";
}


int CPanelVibrato::setAllPanelData(char *buffer)
{
	CVibrato *mod = (CVibrato *) g_currentPatch->mod.mod;

	return mod->setVGData(&buffer);
}


int CPanelVibrato::getAllPanelData(char *buffer)
{
	CVibrato *mod = (CVibrato *) g_currentPatch->mod.mod;

	return mod->getVGData(&buffer);
}


//////////////// CPanelPanEff ///////////////

BEGIN_MESSAGE_MAP(CPanelPanEff, CPanel)
	//{{AFX_MSG_MAP(CPanelPanEff)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPanEff::CPanelPanEff()
{
}


int CPanelPanEff::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_panImage.CreateImageControl("", 9, 40, &g_sEffPan, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;


	if (!m_depth.CreateControl("DEPTH", CTRL_VGKNOB1, 10, 117, this, 0))
		return -1;

	if (!m_wave.CreateControl("WAVE", CTRL_VGKNOB1, 66, 117, this, 0))
			return -1;

	if (!m_rate.CreateControl("RATE", CTRL_VGKNOB1, 122, 117, this, 0))
			return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPanEff::AttachVGData(CPatch *patch)
{
	CPan *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CPan *) patch->mod.mod;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->mod.modeType);
		m_wave.AttachVGData(&mod->wave);
		m_rate.AttachVGData(&mod->rate);
		m_depth.AttachVGData(&mod->depth);

	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_wave.AttachVGData(NULL);
		m_rate.AttachVGData(NULL);
		m_depth.AttachVGData(NULL);
	}
}

CString	CPanelPanEff::getPresetDir()
{
	return "preset\\Effect\\pan\\";
}


int CPanelPanEff::setAllPanelData(char *buffer)
{
	CPan *mod = (CPan *) g_currentPatch->mod.mod;

	return mod->setVGData(&buffer);
}


int CPanelPanEff::getAllPanelData(char *buffer)
{
	CPan *mod = (CPan *) g_currentPatch->mod.mod;

	return mod->getVGData(&buffer);
}

//////////////// CPanelTremolo ///////////////

BEGIN_MESSAGE_MAP(CPanelTremolo, CPanel)
	//{{AFX_MSG_MAP(CPanelTremolo)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelTremolo::CPanelTremolo()
{
}


int CPanelTremolo::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_tremoloImage.CreateImageControl("", 9, 40, &g_sEffVibrato, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

 
	if (!m_depth.CreateControl("DEPTH", CTRL_VGKNOB1, 10, 117, this, 0))
		return -1;

	if (!m_wave.CreateControl("WAVE", CTRL_VGKNOB1, 66, 117, this, 0))
			return -1;

	if (!m_rate.CreateControl("RATE", CTRL_VGKNOB1, 122, 117, this, 0))
			return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelTremolo::AttachVGData(CPatch *patch)
{
	CTremolo *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CTremolo *) patch->mod.mod;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->mod.modeType);
		m_wave.AttachVGData(&mod->wave);
		m_rate.AttachVGData(&mod->rate);
		m_depth.AttachVGData(&mod->depth);

	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_wave.AttachVGData(NULL);
		m_rate.AttachVGData(NULL);
		m_depth.AttachVGData(NULL);
	}
}

CString	CPanelTremolo::getPresetDir()
{
	return "preset\\Effect\\tremolo\\";
}


int CPanelTremolo::setAllPanelData(char *buffer)
{
	CTremolo *mod = (CTremolo *) g_currentPatch->mod.mod;

	return mod->setVGData(&buffer);
}


int CPanelTremolo::getAllPanelData(char *buffer)
{
	CTremolo *mod = (CTremolo *) g_currentPatch->mod.mod;

	return mod->getVGData(&buffer);
}
//////////////// CPanelUniV ///////////////

BEGIN_MESSAGE_MAP(CPanelUniV, CPanel)
	//{{AFX_MSG_MAP(CPanelUniV)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelUniV::CPanelUniV()
{
}


int CPanelUniV::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_univImage.CreateImageControl("", 9, 40, &g_sEffUniV, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

 
	if (!m_rate.CreateControl("RATE", CTRL_VGKNOB1, 10, 117, this, 0))
		return -1;

	if (!m_depth.CreateControl("DEPTH", CTRL_VGKNOB1, 66, 117, this, 0))
			return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 122, 117, this, 0))
			return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelUniV::AttachVGData(CPatch *patch)
{
	CUniV *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CUniV *) patch->mod.mod;

		m_mode.AttachVGData(&patch->mod.modeType);
		m_level.AttachVGData(&mod->level);
		m_rate.AttachVGData(&mod->rate);
		m_depth.AttachVGData(&mod->depth);

	}
	else
	{
		m_mode.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_rate.AttachVGData(NULL);
		m_depth.AttachVGData(NULL);
	}
}


//////////////// CPanelPdShift ///////////////

BEGIN_MESSAGE_MAP(CPanelPdShift, CPanel)
	//{{AFX_MSG_MAP(CPanelPdShift)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPdShift::CPanelPdShift()
{
}


int CPanelPdShift::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;
	
	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_pdShiftImage.CreateImageControl("", 9, 40, &g_sEffPedShift, 0, this, 0))
		return -1;

	if (!m_modeType.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;


	if (!m_pitch.CreateControl("PITCH", CTRL_VGKNOB1, 66, 117, this, 0))
			return -1;

	if (!m_mode.CreateControl("MODE", CTRL_SWITCH1, 122, 117, this, 0))
			return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPdShift::AttachVGData(CPatch *patch)
{
	CModPDShift *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CModPDShift *) patch->mod.mod;

		m_preset.AttachVGData(&m_presetData);
		m_modeType.AttachVGData(&patch->mod.modeType);
		m_pitch.AttachVGData(&mod->pitch);
		m_mode.AttachVGData(&mod->mode);

	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_modeType.AttachVGData(NULL);
		m_pitch.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
	}
}


CString	CPanelPdShift::getPresetDir()
{
	return "preset\\Effect\\PDShift\\";
}


int CPanelPdShift::setAllPanelData(char *buffer)
{
	CModPDShift *mod = (CModPDShift *) g_currentPatch->mod.mod;

	return mod->setVGData(&buffer);
}


int CPanelPdShift::getAllPanelData(char *buffer)
{
	CModPDShift *mod = (CModPDShift *) g_currentPatch->mod.mod;

	return mod->getVGData(&buffer);
}


//////////////// CPanelSubEq ///////////////

BEGIN_MESSAGE_MAP(CPanelSubEq, CPanel)
	//{{AFX_MSG_MAP(CPanelSubEq)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelSubEq::CPanelSubEq()
{
}


int CPanelSubEq::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_labels.CreateImageControl("", 17, 195, &g_eqLabel, 0, this, 0))
		return -1;

	if (!m_eqImage.CreateImageControl("", 9, 40, &g_sEffEq, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VFADER1, 10, 95, this, 0))
		return -1;

	if (!m_lowG.CreateControl("LOW G", CTRL_VFADER1, 28, 95, this, 0))
		return -1;

	if (!m_highG.CreateControl("HIGH G", CTRL_VFADER1, 46, 95, this, 0))
		return -1;

	if (!m_lMidG.CreateControl("L-MID G", CTRL_VFADER1, 64, 95, this, 0))
		return -1;

	if (!m_hMidG.CreateControl("H-MID G", CTRL_VFADER1, 82, 95, this, 0))
		return -1;

	if (!m_lMidQ.CreateControl("L-MID Q", CTRL_VFADER1, 100, 95, this, 0))
		return -1;

	if (!m_hMidQ.CreateControl("H-MID Q", CTRL_VFADER1, 118, 95, this, 0))
		return -1;

	if (!m_hMidF.CreateControl("H-MID F", CTRL_VFADER1, 136, 95, this, 0))
		return -1;

	if (!m_lMidF.CreateControl("L-MID F", CTRL_VFADER1, 154, 95, this, 0))
		return -1;

	m_level.m_labelPosition = DATA_NONE;
	m_lowG.m_labelPosition  = DATA_NONE;
	m_highG.m_labelPosition = DATA_NONE;
	m_lMidG.m_labelPosition = DATA_NONE;
	m_hMidG.m_labelPosition = DATA_NONE;
	m_lMidQ.m_labelPosition = DATA_NONE;
	m_hMidQ.m_labelPosition = DATA_NONE;
	m_hMidF.m_labelPosition = DATA_NONE;
	m_lMidF.m_labelPosition = DATA_NONE;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelSubEq::AttachVGData(CPatch *patch)
{
	CSubEq *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CSubEq *) patch->mod.mod;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->mod.modeType);
		m_level.AttachVGData(&mod->level);
		m_lowG.AttachVGData(&mod->lowG);
		m_hMidG.AttachVGData(&mod->hMidG);
		m_lMidG.AttachVGData(&mod->lMidG);
		m_highG.AttachVGData(&mod->highG);
		m_lMidQ.AttachVGData(&mod->lMidQ);
		m_hMidQ.AttachVGData(&mod->hMidQ);
		m_hMidF.AttachVGData(&mod->hMidF);
		m_lMidF.AttachVGData(&mod->lMidF);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_lowG.AttachVGData(NULL);
		m_hMidG.AttachVGData(NULL);
		m_lMidG.AttachVGData(NULL);
		m_highG.AttachVGData(NULL);
		m_lMidQ.AttachVGData(NULL);
		m_hMidQ.AttachVGData(NULL);
		m_hMidF.AttachVGData(NULL);
		m_lMidF.AttachVGData(NULL);
	}
}


CString	CPanelSubEq::getPresetDir()
{
	return "preset\\CosmEq\\";
}


int CPanelSubEq::setAllPanelData(char *buffer)
{
	int count;
	CSubEq *mod = (CSubEq *) g_currentPatch->mod.mod;

	count = mod->setVGData(&buffer);

	return count - (54 - 6);
}


int CPanelSubEq::getAllPanelData(char *buffer)
{
	int count;
	CSubEq *mod = (CSubEq *) g_currentPatch->mod.mod;

	count = mod->getVGData(&buffer);

	return count - (54 - 6);
}


//////////////// CPanel2x2Chorus ///////////////

BEGIN_MESSAGE_MAP(CPanel2x2Chorus, CPanel)
	//{{AFX_MSG_MAP(CPanel2x2Chorus)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanel2x2Chorus::CPanel2x2Chorus()
{
}


int CPanel2x2Chorus::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_chorusImage.CreateImageControl("", 9, 40, &g_sEffChorus, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

	if (!m_xOverf.CreateControl("X OVER F", CTRL_VGKNOB1, 10, 110, this, 0))
		return -1;


	if (!m_sectionLow.CreateControl("LOW", 166, this, 0))
		return -1;

	if (!m_lowRate.CreateControl("RATE", CTRL_VGKNOB1, 122, 190, this, 0))
			return -1;

	if (!m_lowDepth.CreateControl("DEPTH", CTRL_VGKNOB1, 10, 262, this, 0))
		return -1;

	if (!m_lowPreDly.CreateControl("PRE DLY", CTRL_VGKNOB1, 66, 262, this, 0))
			return -1;

	if (!m_lowLevel.CreateControl("LEVEL", CTRL_VGKNOB1, 122, 262, this, 0))
			return -1;


	if (!m_sectionHigh.CreateControl("HIGH", 318, this, 0))
		return -1;

	if (!m_highRate.CreateControl("RATE", CTRL_VGKNOB1, 122, 344, this, 0))
			return -1;

	if (!m_highDepth.CreateControl("DEPTH", CTRL_VGKNOB1, 10, 414, this, 0))
		return -1;

	if (!m_highPreDly.CreateControl("PRE DLY", CTRL_VGKNOB1, 66, 414, this, 0))
			return -1;

	if (!m_highLevel.CreateControl("LEVEL", CTRL_VGKNOB1, 122, 414, this, 0))
			return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanel2x2Chorus::AttachVGData(CPatch *patch)
{
	CChorus2x2 *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CChorus2x2 *) patch->mod.mod;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->mod.modeType);
		m_highDepth.AttachVGData(&mod->highDepth);
		m_highLevel.AttachVGData(&mod->highLevel);
		m_highPreDly.AttachVGData(&mod->highPreDly);
		m_highRate.AttachVGData(&mod->highRate);
		m_lowDepth.AttachVGData(&mod->lowDepth);
		m_lowLevel.AttachVGData(&mod->lowLevel);
		m_lowPreDly.AttachVGData(&mod->lowPreDly);
		m_lowRate.AttachVGData(&mod->lowRate);
		m_xOverf.AttachVGData(&mod->xOverf);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_highDepth.AttachVGData(NULL);
		m_highLevel.AttachVGData(NULL);
		m_highPreDly.AttachVGData(NULL);
		m_highRate.AttachVGData(NULL);
		m_lowDepth.AttachVGData(NULL);
		m_lowLevel.AttachVGData(NULL);
		m_lowPreDly.AttachVGData(NULL);
		m_lowRate.AttachVGData(NULL);
		m_xOverf.AttachVGData(NULL);
	}
}

CString	CPanel2x2Chorus::getPresetDir()
{
	return "preset\\Effect\\2x2Chorus\\";
}


int CPanel2x2Chorus::setAllPanelData(char *buffer)
{
	CChorus2x2 *mod = (CChorus2x2 *) g_currentPatch->mod.mod;

	return mod->setVGData(&buffer);
}


int CPanel2x2Chorus::getAllPanelData(char *buffer)
{
	CChorus2x2 *mod = (CChorus2x2 *) g_currentPatch->mod.mod;

	return mod->getVGData(&buffer);
}



//////////////// CPanelFlanger ///////////////

BEGIN_MESSAGE_MAP(CPanelFlanger, CPanel)
	//{{AFX_MSG_MAP(CPanelFlanger)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelFlanger::CPanelFlanger()
{
}


int CPanelFlanger::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_flangerImage.CreateImageControl("", 9, 40, &g_sEffFlanger, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

	if (!m_separate.CreateControl("SEPARATE", CTRL_VGKNOB1, 10, 117, this, 0))
		return -1;

	if (!m_rate.CreateControl("RATE", CTRL_VGKNOB1, 66, 117, this, 0))
			return -1;

	if (!m_depth.CreateControl("DEPTH", CTRL_VGKNOB1, 122, 117, this, 0))
			return -1;

	if (!m_manual.CreateControl("MANUAL", CTRL_VGKNOB1, 10, 173, this, 0))
		return -1;

	if (!m_reso.CreateControl("RESO", CTRL_VGKNOB1, 69, 173, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 122, 173, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelFlanger::AttachVGData(CPatch *patch)
{
	CFlanger *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CFlanger *) patch->mod.mod;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->mod.modeType);
		m_rate.AttachVGData(&mod->rate);
		m_depth.AttachVGData(&mod->depth);
		m_manual.AttachVGData(&mod->manual);
		m_reso.AttachVGData(&mod->reso);
		m_level.AttachVGData(&mod->level);
		m_separate.AttachVGData(&mod->separate);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_rate.AttachVGData(NULL);
		m_depth.AttachVGData(NULL);
		m_manual.AttachVGData(NULL);
		m_reso.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_separate.AttachVGData(NULL);
	}
}

CString	CPanelFlanger::getPresetDir()
{
	return "preset\\Effect\\flanger\\";
}


int CPanelFlanger::setAllPanelData(char *buffer)
{
	CFlanger *mod = (CFlanger *) g_currentPatch->mod.mod;

	return mod->setVGData(&buffer);
}


int CPanelFlanger::getAllPanelData(char *buffer)
{
	CFlanger *mod = (CFlanger *) g_currentPatch->mod.mod;

	return mod->getVGData(&buffer);
}

//////////////// CPanelDefretter ///////////////

BEGIN_MESSAGE_MAP(CPanelDefretter, CPanel)
	//{{AFX_MSG_MAP(CPanelDefretter)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
CPanelDefretter::CPanelDefretter()
{

}
*/

int CPanelDefretter::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);


	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_defretterImage.CreateImageControl("", 9, 40, &g_sEffDefretter, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;


	if (!m_sens.CreateControl("SENS", CTRL_VGKNOB1, 10, 117, this, 0))
			return -1;

	if (!m_attack.CreateControl("ATTACK", CTRL_VGKNOB1, 69, 117, this, 0))
			return -1;

	if (!m_depth.CreateControl("DEPTH", CTRL_VGKNOB1, 10, 173, this, 0))
		return -1;

	if (!m_reso.CreateControl("RESO", CTRL_VGKNOB1, 69, 173, this, 0))
		return -1;

	if (!m_elevel.CreateControl("E.LEVEL", CTRL_VGKNOB1, 122, 173, this, 0))
		return -1;

	if (!m_dlevel.CreateControl("D.LEVEL", CTRL_VGKNOB1, 122, 229, this, 0))
		return -1;

	if (!m_tone.CreateControl("TONE", CTRL_VGKNOB1, 69, 229, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelDefretter::AttachVGData(CPatch *patch)
{
	CDefretter *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CDefretter *) patch->mod.mod;

		m_mode.AttachVGData(&patch->mod.modeType);
		m_attack.AttachVGData(&mod->attack);
		m_depth.AttachVGData(&mod->depth);
		m_sens.AttachVGData(&mod->sens);
		m_reso.AttachVGData(&mod->reso);
		m_elevel.AttachVGData(&mod->elevel);
		m_dlevel.AttachVGData(&mod->dlevel);
		m_tone.AttachVGData(&mod->tone);
	}
	else
	{
		m_mode.AttachVGData(NULL);
		m_attack.AttachVGData(NULL);
		m_depth.AttachVGData(NULL);
		m_sens.AttachVGData(NULL);
		m_reso.AttachVGData(NULL);
		m_elevel.AttachVGData(NULL);
		m_dlevel.AttachVGData(NULL);
		m_tone.AttachVGData(NULL);
	}
}



//////////////// CPanelPhaser ///////////////

BEGIN_MESSAGE_MAP(CPanelPhaser, CPanel)
	//{{AFX_MSG_MAP(CPanelPhaser)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPhaser::CPanelPhaser()
{

}


int CPanelPhaser::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_phaserImage.CreateImageControl("", 9, 40, &g_sEffPhaser, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;


	if (!m_rate.CreateControl("RATE", CTRL_VGKNOB1, 66, 117, this, 0))
			return -1;

	if (!m_depth.CreateControl("DEPTH", CTRL_VGKNOB1, 122, 117, this, 0))
			return -1;

	if (!m_manual.CreateControl("MANUAL", CTRL_VGKNOB1, 10, 173, this, 0))
		return -1;

	if (!m_reso.CreateControl("RESO", CTRL_VGKNOB1, 69, 173, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 122, 173, this, 0))
		return -1;

	if (!m_stage.CreateControl("STAGE", CTRL_VGKNOB1, 10, 229, this, 0))
		return -1;

	if (!m_step.CreateControl("STEP", CTRL_VGKNOB1, 69, 229, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPhaser::AttachVGData(CPatch *patch)
{
	CPhaser *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CPhaser *) patch->mod.mod;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->mod.modeType);
		m_rate.AttachVGData(&mod->rate);
		m_depth.AttachVGData(&mod->depth);
		m_manual.AttachVGData(&mod->manual);
		m_reso.AttachVGData(&mod->reso);
		m_level.AttachVGData(&mod->level);
		m_stage.AttachVGData(&mod->stage);
		m_step.AttachVGData(&mod->step);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_rate.AttachVGData(NULL);
		m_depth.AttachVGData(NULL);
		m_manual.AttachVGData(NULL);
		m_reso.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_stage.AttachVGData(NULL);
		m_step.AttachVGData(NULL);
	}
}


CString	CPanelPhaser::getPresetDir()
{
	return "preset\\Effect\\phaser\\";
}


int CPanelPhaser::setAllPanelData(char *buffer)
{
	CPhaser *mod = (CPhaser *) g_currentPatch->mod.mod;

	return mod->setVGData(&buffer);
}


int CPanelPhaser::getAllPanelData(char *buffer)
{
	CPhaser *mod = (CPhaser *) g_currentPatch->mod.mod;

	return mod->getVGData(&buffer);
}

//////////////// CPanelHarmonist ///////////////

BEGIN_MESSAGE_MAP(CPanelHarmonist, CPanel)
	//{{AFX_MSG_MAP(CPanelHarmonist)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelHarmonist::CPanelHarmonist()
{
}


int CPanelHarmonist::OnCreate(LPCREATESTRUCT lpcs)
{
	int i; 
	char *tab[] = {"C", "Db", "D", "D#", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};

	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_harmoImage.CreateImageControl("", 9, 40, &g_sEffHarmo, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

	if (!m_dirLevel.CreateControl("DIR LEV", CTRL_VGKNOB1, 122, 74, this, 0))
			return -1;

	if (!m_sectionHr1.CreateControl("HR1", 134, this, 0))
		return -1;

	if (!m_hr1OnOff.CreateControl("ON/OFF", CTRL_SWITCH1, 10, 151, this, 0))
			return -1;

	for (i = 0; i < 12; i++)
		if (!m_hr1UserScale[i].CreateControl(tab[i], CTRL_VGKNOB3, 13 + i * 13, 207, this, 0))
			return -1;

	if (!m_hr1Harmony.CreateControl("HARMONY", CTRL_VGKNOB1, 122, 245, this, IDC_HARMONY1))
			return -1;

	if (!m_hr1Pan.CreateControl("PAN", CTRL_VGKNOB1, 10, 245, this, 0))
			return -1;

	if (!m_hr1Level.CreateControl("LEVEL", CTRL_VGKNOB1, 66, 245, this, 0))
		return -1;

	if (!m_sectionHr2.CreateControl("HR2", 305, this, 0))
		return -1;

	if (!m_hr2OnOff.CreateControl("ON/OFF", CTRL_SWITCH1, 10, 320, this, 0))
			return -1;

	for (i = 0; i < 12; i++)
		if (!m_hr2UserScale[i].CreateControl(tab[i], CTRL_VGKNOB3, 13 + i * 13, 376, this, 0))
			return -1;

	if (!m_hr2Harmony.CreateControl("HARMONY", CTRL_VGKNOB1, 122, 415, this, IDC_HARMONY2))
			return -1;

	if (!m_hr2Pan.CreateControl("PAN", CTRL_VGKNOB1, 10, 415, this, 0))
			return -1;

	if (!m_hr2Level.CreateControl("LEVEL", CTRL_VGKNOB1, 66, 415, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelHarmonist::AttachVGData(CPatch *patch)
{
	CHarmonist *mod;
	int i;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CHarmonist *) patch->mod.mod;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->mod.modeType);
		m_dirLevel.AttachVGData(&mod->dirLevel);

		m_hr1OnOff.AttachVGData(&mod->hr1OnOff);
		m_hr1Harmony.AttachVGData(&mod->hr1Harmony);
		m_hr1Pan.AttachVGData(&mod->hr1Pan);
		m_hr1Level.AttachVGData(&mod->hr1Level);

		m_hr2OnOff.AttachVGData(&mod->hr2OnOff);
		m_hr2Harmony.AttachVGData(&mod->hr2Harmony);
		m_hr2Pan.AttachVGData(&mod->hr2Pan);
		m_hr2Level.AttachVGData(&mod->hr2Level);

		if (mod->hr1Harmony.getValue() == HARMONY_USER)
		{
			for (i = 0; i < 12; i++)
			{
				m_hr1UserScale[i].AttachVGData(&mod->hr1UserScale[i]);
				m_hr1UserScale[i].ShowWindow(SW_SHOWNA);
			}
		}
		else
		{
			for (i = 0; i < 12; i++)
			{
				m_hr1UserScale[i].AttachVGData(NULL);
				m_hr1UserScale[i].ShowWindow(SW_HIDE);
			}
		}


		if (mod->hr2Harmony.getValue() == HARMONY_USER)
		{
			for (i = 0; i < 12; i++)
			{
				m_hr2UserScale[i].AttachVGData(&mod->hr2UserScale[i]);
				m_hr2UserScale[i].ShowWindow(SW_SHOWNA);
			}
		}
		else
		{
			for (i = 0; i < 12; i++)
			{
				m_hr2UserScale[i].AttachVGData(NULL);
				m_hr2UserScale[i].ShowWindow(SW_HIDE);
			}
		}

	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);

		m_mode.AttachVGData(NULL);
		m_dirLevel.AttachVGData(NULL);

		for (i = 0; i < 12; i++)
		{
			m_hr1UserScale[i].AttachVGData(NULL);
			m_hr1UserScale[i].ShowWindow(SW_HIDE);
		}

		m_hr1OnOff.AttachVGData(NULL);
		m_hr1Harmony.AttachVGData(NULL);
		m_hr1Pan.AttachVGData(NULL);
		m_hr1Level.AttachVGData(NULL);

		for (i = 0; i < 12; i++)
		{
			m_hr2UserScale[i].AttachVGData(NULL);
			m_hr2UserScale[i].ShowWindow(SW_HIDE);
		}

		m_hr2OnOff.AttachVGData(NULL);
		m_hr2Harmony.AttachVGData(NULL);
		m_hr2Pan.AttachVGData(NULL);
		m_hr2Level.AttachVGData(NULL);
	}
}


BOOL CPanelHarmonist::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == IDC_HARMONY1 || wParam == IDC_HARMONY2)
		AttachVGData(g_currentPatch);
	else
	{
		// Notify the parent window that a refresh of the panel is needed
		GetParent()->PostMessage(WM_COMMAND, wParam, (long) this);
	}

	return CPanel ::OnCommand(wParam, lParam);
}


CString	CPanelHarmonist::getPresetDir()
{
	return "preset\\Effect\\harmonist\\";
}


int CPanelHarmonist::setAllPanelData(char *buffer)
{
	CHarmonist *mod = (CHarmonist *) g_currentPatch->mod.mod;

	return mod->setVGData(&buffer);
}


int CPanelHarmonist::getAllPanelData(char *buffer)
{
	CHarmonist *mod = (CHarmonist *) g_currentPatch->mod.mod;

	return mod->getVGData(&buffer);
}


//////////////// CPanelSitar ///////////////

BEGIN_MESSAGE_MAP(CPanelSitar, CPanel)
	//{{AFX_MSG_MAP(CPanelSitar)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelSitar::CPanelSitar()
{
}


int CPanelSitar::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	// Pickup type
	if (!m_pickup.CreateControl("PICKUP", CTRL_EDIT1, 10, 44, this, 0))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_modelImage.CreateImageControl("", 30, 84, &g_sitarp, 0, this, 0))
		return -1;

	// Level
	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;

	// Tone
	if (!m_tone.CreateControl("TONE", CTRL_VGKNOB1, 69, 160, this, 0))
		return -1;

	// Pickup
	if (!m_sens.CreateControl("SENS", CTRL_VGKNOB1, 125, 160, this, 0))
		return -1;

	if (!m_color.CreateControl("COLOR", CTRL_VGKNOB1, 10, 218, this, 0))
		return -1;

	if (!m_decay.CreateControl("DECAY", CTRL_VGKNOB1, 69, 218, this, 0))
		return -1;

	if (!m_body.CreateControl("BODY", CTRL_VGKNOB1, 125, 218, this, 0))
		return -1;

	if (!m_buzz.CreateControl("BUZZ", CTRL_VGKNOB1, 10, 276, this, 0))
		return -1;

	if (!m_attackLevel.CreateControl("A. LEVEL", CTRL_VGKNOB1, 69, 276, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}

void CPanelSitar::AttachVGData(CPatch *patch)
{
	CSitar	*sitar;
	
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		sitar = (CSitar *) patch->instrument;

		m_preset.AttachVGData(&m_presetData);
		m_pickup.AttachVGData(&sitar->pickup);
		m_level.AttachVGData(&sitar->level);
		m_tone.AttachVGData(&sitar->tone);
		m_sens.AttachVGData(&sitar->sens);
		m_body.AttachVGData(&sitar->body);
		m_color.AttachVGData(&sitar->color);
		m_decay.AttachVGData(&sitar->decay);
		m_buzz.AttachVGData(&sitar->buzz);
		m_attackLevel.AttachVGData(&sitar->AttackLevel);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_pickup.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_tone.AttachVGData(NULL);
		m_sens.AttachVGData(NULL);
		m_body.AttachVGData(NULL);
		m_color.AttachVGData(NULL);
		m_decay.AttachVGData(NULL);
		m_buzz.AttachVGData(NULL);
		m_attackLevel.AttachVGData(NULL);
	}
}


CString	CPanelSitar::getPresetDir()
{
	return "preset\\Instrument\\sitar\\";
}


int CPanelSitar::setAllPanelData(char *buffer)
{
	CSitar	*sitar = (CSitar *) g_currentPatch->instrument;

	return sitar->setVGData(&buffer);
}


int CPanelSitar::getAllPanelData(char *buffer)
{
	CSitar	*sitar = (CSitar *) g_currentPatch->instrument;

	return sitar->getVGData(&buffer);

}


//////////////// CPanelWave ///////////////

BEGIN_MESSAGE_MAP(CPanelWave, CPanel)
	//{{AFX_MSG_MAP(CPanelWave)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelWave::CPanelWave()
{
}


int CPanelWave::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_shape.CreateControl("SHAPE", CTRL_EDIT1, 10, 44, this, 0))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_modelImage.CreateImageControl("", 30, 84, &g_wave, 2, this, 0))
		return -1;

	// Level
	if (!m_sens.CreateControl("SENS", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;

	// Tone
	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 69, 160, this, 0))
		return -1;

	if (!m_attack.CreateControl("ATTACK", CTRL_VGKNOB1, 10, 218, this, 0))
		return -1;

	if (!m_decay.CreateControl("DECAY", CTRL_VGKNOB1, 69, 218, this, 0))
		return -1;


	if (!m_cutoff.CreateControl("CUTOFF", CTRL_VGKNOB1, 10, 276, this, 0))
		return -1;

	if (!m_reso.CreateControl("RESO", CTRL_VGKNOB1, 69, 276, this, 0))
		return -1;

	if (!m_ftype.CreateControl("F. TYPE", CTRL_SWITCH1, 125, 276, this, 0))
		return -1;


	if (!m_fattack.CreateControl("F. ATTACK", CTRL_VGKNOB1, 10, 334, this, 0))
		return -1;

	if (!m_fdecay.CreateControl("F. DECAY", CTRL_VGKNOB1, 69, 334, this, 0))
		return -1;

	if (!m_fdepth.CreateControl("F. DEPTH", CTRL_VGKNOB1, 125, 334, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}

void CPanelWave::AttachVGData(CPatch *patch)
{
	CWave	*wave;
	
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		wave = (CWave *) patch->instrument;

		m_preset.AttachVGData(&m_presetData);
		m_shape.AttachVGData(&wave->shape);
		m_modelImage.AttachVGData(&wave->shape);
		m_sens.AttachVGData(&wave->sens);
		m_attack.AttachVGData(&wave->attack);
		m_decay.AttachVGData(&wave->decay);
		m_level.AttachVGData(&wave->level);
		m_cutoff.AttachVGData(&wave->cutoff);
		m_reso.AttachVGData(&wave->reso);
		m_ftype.AttachVGData(&wave->ftype);
		m_fattack.AttachVGData(&wave->fattack);
		m_fdecay.AttachVGData(&wave->fdecay);
		m_fdepth.AttachVGData(&wave->fdepth);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_shape.AttachVGData(NULL);
		m_modelImage.AttachVGData(NULL);
		m_sens.AttachVGData(NULL);
		m_attack.AttachVGData(NULL);
		m_decay.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_cutoff.AttachVGData(NULL);
		m_reso.AttachVGData(NULL);
		m_ftype.AttachVGData(NULL);
		m_fattack.AttachVGData(NULL);
		m_fdecay.AttachVGData(NULL);
		m_fdepth.AttachVGData(NULL);
	}
}


CString	CPanelWave::getPresetDir()
{
	return "preset\\Instrument\\Wave\\";
}


int CPanelWave::setAllPanelData(char *buffer)
{
	CWave *wave = (CWave *) g_currentPatch->instrument;

	return wave->setVGData(&buffer);
}


int CPanelWave::getAllPanelData(char *buffer)
{
	CWave	*wave = (CWave *) g_currentPatch->instrument;

	return wave->getVGData(&buffer);

}


//////////////// CPanelPickup ///////////////

BEGIN_MESSAGE_MAP(CPanelPickup, CPanel)
	//{{AFX_MSG_MAP(CPanelPickup)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPickup::CPanelPickup()
{
}


int CPanelPickup::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	// Pickup type
	if (!m_model.CreateControl("MODEL", CTRL_EDIT1, 10, 44, this, 0))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_modelImage.CreateImageControl("MODEL", 30, 84, &g_guitars, 11, this, 0))
		return -1;

	// Level
	if (!m_level.CreateControl("LEVEL", CTRL_GTKNOB1, 10, 160, this, 0))
		return -1;

	// Tone
	if (!m_tone.CreateControl("TONE", CTRL_GTKNOB1, 60, 160, this, 0))
		return -1;

	// Pickup
	if (!m_pickup.CreateControl("POSITION", CTRL_SELECTOR, 110, 160, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPickup::AttachVGData(CPatch *patch)
{
	CPickup	*pickup;
	
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		switch (patch->cosmGT.guitarType.getValue())
		{
			case COSMGT_VARI_GT:
				pickup = &((CVariGuitar *) patch->instrument)->pickup;
			break;

			case COSMGT_ACOUSTIC:
			break;

			case COSMGT_NYLON_STRINGS:
			break;

			case COSMGT_OPEN_TUNE:
				pickup = &((COpenTune *) patch->instrument)->pickup;
			break;

			case COSMGT_12STRINGS:
				pickup = &((CStrings12 *) patch->instrument)->pickup;
			break;

			case COSMGT_PD_SHIFT:
				pickup = &((CPdShift *) patch->instrument)->pickup;
			break;

			case COSMGT_POLY_DIST:
				pickup = &((CPolyDist *) patch->instrument)->pickup;
			break;

			case COSMGT_POLY_COMP:
				pickup = &((CPolyComp *) patch->instrument)->pickup;
			break;

			case COSMGT_POLY_OCT:
				pickup = &((CPolyOct *) patch->instrument)->pickup;
			break;

			case COSMGT_POLY_SG:
				pickup = &((CPolySG *) patch->instrument)->pickup;
			break;

			case COSMGT_BOWED:
			break;

			case COSMGT_DUAL:
			break;

			case COSMGT_FILTER_BASS:
			break;

			case COSMGT_PIPE:
			break;

			case COSMGT_SOLO:
			break;

			case COSMGT_PWM:
			break;

			case COSMGT_CRYSTAL:
			break;

			case COSMGT_ORGAN:
			break;

			case COSMGT_BRASS:
			break;
		}

		m_preset.AttachVGData(&m_presetData);
		m_model.AttachVGData(&pickup->model);
		m_modelImage.AttachVGData(&pickup->model);
		m_level.AttachVGData(&pickup->level);
		m_tone.AttachVGData(&pickup->tone);
		m_pickup.AttachVGData(&pickup->pickup);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_model.AttachVGData(NULL);
		m_modelImage.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_tone.AttachVGData(NULL);
		m_pickup.AttachVGData(NULL);
	}
}

CString	CPanelPickup::getPresetDir()
{
	return "preset\\Instrument\\Pickup\\";
}


int CPanelPickup::setAllPanelData(char *buffer)
{
	CPickup	*pickup;

	switch (g_currentPatch->cosmGT.guitarType.getValue())
	{
		case COSMGT_VARI_GT:
			pickup = &((CVariGuitar *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_OPEN_TUNE:
			pickup = &((COpenTune *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_12STRINGS:
			pickup = &((CStrings12 *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_PD_SHIFT:
			pickup = &((CPdShift *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_POLY_DIST:
			pickup = &((CPolyDist *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_POLY_COMP:
			pickup = &((CPolyComp *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_POLY_OCT:
			pickup = &((CPolyOct *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_POLY_SG:
			pickup = &((CPolySG *) g_currentPatch->instrument)->pickup;
		break;
	}

	return pickup->setVGData(&buffer);
}


int CPanelPickup::getAllPanelData(char *buffer)
{
	CPickup	*pickup;

	switch (g_currentPatch->cosmGT.guitarType.getValue())
	{
		case COSMGT_VARI_GT:
			pickup = &((CVariGuitar *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_OPEN_TUNE:
			pickup = &((COpenTune *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_12STRINGS:
			pickup = &((CStrings12 *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_PD_SHIFT:
			pickup = &((CPdShift *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_POLY_DIST:
			pickup = &((CPolyDist *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_POLY_COMP:
			pickup = &((CPolyComp *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_POLY_OCT:
			pickup = &((CPolyOct *) g_currentPatch->instrument)->pickup;
		break;

		case COSMGT_POLY_SG:
			pickup = &((CPolySG *) g_currentPatch->instrument)->pickup;
		break;
	}

	return pickup->getVGData(&buffer);
}

//////////////// CPanelPickupAcous ///////////////

BEGIN_MESSAGE_MAP(CPanelPickupAcous, CPanel)
	//{{AFX_MSG_MAP(CPanelPickupAcous)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPickupAcous::CPanelPickupAcous()
{
}


int CPanelPickupAcous::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	// Pickup type
	if (!m_type.CreateControl("TYPE", CTRL_EDIT1, 10, 44, this, 0))
		return -1;


	if (!m_typeImage.CreateImageControl("TYPE", 30, 84, &g_guitarsacous, 2, this, 0))
		return -1;

	// Level
	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;

	// Tone
	if (!m_tone.CreateControl("TONE", CTRL_VGKNOB1, 60, 160, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPickupAcous::AttachVGData(CPatch *patch)
{
	CAPickup	*pickup;
	
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		pickup = &((CAcoustic *) patch->instrument)->pickup;
	
		m_type.AttachVGData(&pickup->type);
		m_typeImage.AttachVGData(&pickup->type);
		m_level.AttachVGData(&pickup->level);
		m_tone.AttachVGData(&pickup->tone);
	}
	else
	{
		m_type.AttachVGData(NULL);
		m_typeImage.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_tone.AttachVGData(NULL);
	}
}




//////////////// CPanelPickupNylon ///////////////

BEGIN_MESSAGE_MAP(CPanelPickupNylon, CPanel)
	//{{AFX_MSG_MAP(CPanelPickupNylon)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPickupNylon::CPanelPickupNylon()
{
}


int CPanelPickupNylon::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_nylonImage.CreateImageControl("", 30, 84, &g_guitarNylon, 0, this, 0))
		return -1;

	if (!m_nylonImageII.CreateImageControl("", 30, 84, &g_guitarNylonII, 0, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPickupNylon::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarType.getValue() == COSMGT_NYLON_STRINGS)
	{
		m_nylonImage.ShowWindow(SW_SHOWNOACTIVATE);
		m_nylonImageII.ShowWindow(SW_HIDE);
	}
	else
	{
		m_nylonImage.ShowWindow(SW_HIDE);
		m_nylonImageII.ShowWindow(SW_SHOWNOACTIVATE);
	}
}


//////////////// CPanelPickupVari ///////////////

BEGIN_MESSAGE_MAP(CPanelPickupVari, CPanel)
	//{{AFX_MSG_MAP(CPanelPickupVari)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPickupVari::CPanelPickupVari()
{
}


int CPanelPickupVari::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	// Pickup type
	if (!m_model.CreateControl("MODEL", CTRL_EDIT1, 10, 44, this, 0))
		return -1;

	if (!m_pickupPos.CreateControl("", 1, 0, 74, this, IDC_PICKUP))
		return -1;

	// Level
	if (!m_level.CreateControl("LEVEL", CTRL_GTKNOB1, 10, 160, this, 0))
		return -1;

	// Tone
	if (!m_tone.CreateControl("TONE", CTRL_GTKNOB1, 60, 160, this, 0))
		return -1;

	// Pickup
	if (!m_pickup.CreateControl("POSITION", CTRL_SELECTOR, 110, 160, this, IDC_PICKUPPOS))
		return -1;

	// Phase
	if (!m_phase.CreateControl("PHASE", CTRL_SWITCH1, 10, 220, this, 0))
		return -1;

	if (!m_sectionRearPickup.CreateControl("REAR PICKUP", 280, this, 0))
		return -1;

	if (!m_rearPickuType.CreateControl("TYPE", CTRL_EDIT1, 10, 299, this, 0))
		return -1;

	if (!m_rearPickuTypeImage.CreateImageControl("TYPE", 20, 327, &g_pickuptype2, 4, this, 0))
		return -1;

	if (!m_rearPickupPosition.CreateControl("POSITION", CTRL_VGKNOB1, 69, 322, this, IDC_PICKUPPOS))
		return -1;

	if (!m_rearPickupAngle.CreateControl("ANGLE", CTRL_VGKNOB1, 122, 322, this, IDC_PICKUPPOS))
		return -1;

	if (!m_sectionFrontPickup.CreateControl("FRONT PICKUP", 378, this, 0))
		return -1;

	if (!m_frontPickuType.CreateControl("TYPE", CTRL_EDIT1, 10, 397, this, 0))
		return -1;

	if (!m_frontPickuTypeImage.CreateImageControl("TYPE", 20, 426, &g_pickuptype1, 4, this, 0))
		return -1;

	if (!m_frontPickupPosition.CreateControl("POSITION", CTRL_VGKNOB1, 69, 421, this, IDC_PICKUPPOS))
		return -1;

	if (!m_frontPickupAngle.CreateControl("ANGLE", CTRL_VGKNOB1, 122, 421,  this, IDC_PICKUPPOS))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPickupVari::AttachVGData(CPatch *patch)
{
	CPickup	*pickup;
	
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		pickup = &((CVariGuitar *) patch->instrument)->pickup;
	
		m_preset.AttachVGData(&m_presetData);
		m_model.AttachVGData(&pickup->model);
		m_level.AttachVGData(&pickup->level);
		m_tone.AttachVGData(&pickup->tone);
		m_pickup.AttachVGData(&pickup->pickup);
		
		m_phase.AttachVGData(&pickup->phase);

		m_pickupPos.AttachVGData(&pickup->frontPickuType, &pickup->frontPickupPosition, &pickup->frontPickupAngle,
		&pickup->rearPickuType, &pickup->rearPickupPosition, &pickup->rearPickupAngle, &pickup->pickup);
		m_frontPickuType.AttachVGData(&pickup->frontPickuType);
		m_frontPickuTypeImage.AttachVGData(&pickup->frontPickuType);

		if (pickup->frontPickuType.getValue() == TPICKUP_SINGLE || pickup->frontPickuType.getValue() == TPICKUP_DOUBLE)
		{
			m_frontPickupPosition.AttachVGData(&pickup->frontPickupPosition);
			m_frontPickupAngle.AttachVGData(&pickup->frontPickupAngle);
		}
		else
		{
			m_frontPickupPosition.AttachVGData(NULL);
			m_frontPickupAngle.AttachVGData(NULL);
		}

		m_rearPickuType.AttachVGData(&pickup->rearPickuType);
		m_rearPickuTypeImage.AttachVGData(&pickup->rearPickuType);

		if (pickup->rearPickuType.getValue() == TPICKUP_SINGLE || pickup->rearPickuType.getValue() == TPICKUP_DOUBLE)
		{
			m_rearPickupPosition.AttachVGData(&pickup->rearPickupPosition);
			m_rearPickupAngle.AttachVGData(&pickup->rearPickupAngle);
		}
		else
		{
			m_rearPickupPosition.AttachVGData(NULL);
			m_rearPickupAngle.AttachVGData(NULL);
		}
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_model.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_tone.AttachVGData(NULL);
		m_pickup.AttachVGData(NULL);
		
		m_phase.AttachVGData(NULL);
		m_pickupPos.AttachVGData(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		m_frontPickuType.AttachVGData(NULL);
		m_frontPickuTypeImage.AttachVGData(NULL);
		m_frontPickupPosition.AttachVGData(NULL);
		m_frontPickupAngle.AttachVGData(NULL);
		m_rearPickuType.AttachVGData(NULL);
		m_rearPickuTypeImage.AttachVGData(NULL);
		m_rearPickupPosition.AttachVGData(NULL);
		m_rearPickupAngle.AttachVGData(NULL);
	}
}



BOOL CPanelPickupVari::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == IDC_PICKUPPOS)
		m_pickupPos.Invalidate(FALSE);
	else if (wParam == IDC_PICKUP)
	{
		m_frontPickupPosition.Invalidate(FALSE);
		m_frontPickupAngle.Invalidate(FALSE);
		m_rearPickupPosition.Invalidate(FALSE);
		m_rearPickupAngle.Invalidate(FALSE);
	}
	else
	{
		// Notify the parent window that a refresh of the panel is needed
		GetParent()->PostMessage(WM_COMMAND, wParam, (long) this);
	}

	return CPanel ::OnCommand(wParam, lParam);
}


CString	CPanelPickupVari::getPresetDir()
{
	return "preset\\Instrument\\Pickup\\";
}


int CPanelPickupVari::setAllPanelData(char *buffer)
{
	CPickup *pickup = &((CVariGuitar *) g_currentPatch->instrument)->pickup;

	return pickup->setVGData(&buffer);
}


int CPanelPickupVari::getAllPanelData(char *buffer)
{
	CPickup *pickup = &((CVariGuitar *) g_currentPatch->instrument)->pickup;

	return g_currentPatch->getVGData(&buffer);
}


//////////////// CPanelBody ///////////////

BEGIN_MESSAGE_MAP(CPanelBody, CPanel)
	//{{AFX_MSG_MAP(CPanelBody)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelBody::CPanelBody()
{
}


int CPanelBody::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	// Attack
	if (!m_attack.CreateControl("ATTACK", CTRL_VGKNOB1, 10, 35, this, 0))
		return -1;

	// Body
	if (!m_body.CreateControl("BODY", CTRL_VGKNOB1, 69, 35, this, 0))
		return -1;

	// Low cut
	if (!m_lowCut.CreateControl("LOW CUT", CTRL_VGKNOB1, 125, 35, this, 0))
		return -1;

	// Level
	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 10, 93, this, 0))
		return -1;

	// Body type
	if (!m_bodyType.CreateControl("TYPE", CTRL_EDIT1, 10, 185, this, 0))
		return -1;

	if (!m_bodyTypeImage.CreateImageControl("TYPE", 20, 230, &g_bodytype, 5, this, 0))
		return -1;

	// Middle
	if (!m_size.CreateControl("SIZE", CTRL_VGKNOB1, 125, 220, this, 0))
		return -1;

	// Trebble
	if (!m_reso.CreateControl("TREBBLE", CTRL_VGKNOB1, 125, 278, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelBody::AttachVGData(CPatch *patch)
{
	CBody	*body;
	
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		switch (patch->cosmGT.guitarType.getValue())
		{
			case COSMGT_VARI_GT:
				body = &((CVariGuitar *) patch->instrument)->body;
			break;

			case COSMGT_ACOUSTIC:
				body = &((CAcoustic *) patch->instrument)->body;
			break;

			case COSMGT_NYLON_STRINGS:
			break;

			case COSMGT_OPEN_TUNE:
				body = &((COpenTune *) patch->instrument)->body;
			break;

			case COSMGT_12STRINGS:
				body = &((CStrings12 *) patch->instrument)->body;
			break;

			case COSMGT_PD_SHIFT:
				body = &((CPdShift *) patch->instrument)->body;
			break;

			case COSMGT_POLY_DIST:
			break;

			case COSMGT_POLY_COMP:
			break;

			case COSMGT_POLY_OCT:
			break;

			case COSMGT_POLY_SG:
			break;

			case COSMGT_BOWED:
			break;

			case COSMGT_DUAL:
			break;

			case COSMGT_FILTER_BASS:
			break;

			case COSMGT_PIPE:
			break;

			case COSMGT_SOLO:
			break;

			case COSMGT_PWM:
			break;

			case COSMGT_CRYSTAL:
			break;

			case COSMGT_ORGAN:
			break;

			case COSMGT_BRASS:
			break;
		}

		m_preset.AttachVGData(&m_presetData);
		m_attack.AttachVGData(&body->attack);
		m_body.AttachVGData(&body->body);
		m_lowCut.AttachVGData(&body->lowCut);
		m_level.AttachVGData(&body->level);
		m_bodyType.AttachVGData(&body->bodyType);
		m_bodyTypeImage.AttachVGData(&body->bodyType);
		m_size.AttachVGData(&body->size);
		m_reso.AttachVGData(&body->reso);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_attack.AttachVGData(NULL);
		m_body.AttachVGData(NULL);
		m_lowCut.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_bodyType.AttachVGData(NULL);
		m_bodyTypeImage.AttachVGData(NULL);
		m_size.AttachVGData(NULL);
		m_reso.AttachVGData(NULL);
	}
}


CString	CPanelBody::getPresetDir()
{
	return "preset\\Instrument\\body\\";
}


int CPanelBody::setAllPanelData(char *buffer)
{
	CBody	*body;
	
	switch (g_currentPatch->cosmGT.guitarType.getValue())
	{
		case COSMGT_VARI_GT:
			body = &((CVariGuitar *) g_currentPatch->instrument)->body;
		break;

		case COSMGT_ACOUSTIC:
		body = &((CAcoustic *) g_currentPatch->instrument)->body;
		break;

		case COSMGT_OPEN_TUNE:
			body = &((COpenTune *) g_currentPatch->instrument)->body;
		break;

		case COSMGT_12STRINGS:
			body = &((CStrings12 *) g_currentPatch->instrument)->body;
		break;

		case COSMGT_PD_SHIFT:
			body = &((CPdShift *) g_currentPatch->instrument)->body;
		break;
	}

	return body->setVGData(&buffer);
}


int CPanelBody::getAllPanelData(char *buffer)
{
	CBody	*body;
	
	switch (g_currentPatch->cosmGT.guitarType.getValue())
	{
		case COSMGT_VARI_GT:
			body = &((CVariGuitar *) g_currentPatch->instrument)->body;
		break;

		case COSMGT_ACOUSTIC:
		body = &((CAcoustic *) g_currentPatch->instrument)->body;
		break;

		case COSMGT_OPEN_TUNE:
			body = &((COpenTune *) g_currentPatch->instrument)->body;
		break;

		case COSMGT_12STRINGS:
			body = &((CStrings12 *) g_currentPatch->instrument)->body;
		break;

		case COSMGT_PD_SHIFT:
			body = &((CPdShift *) g_currentPatch->instrument)->body;
		break;
	}

	return body->getVGData(&buffer);
}

//////////////// CPanelBodyNylon ///////////////

BEGIN_MESSAGE_MAP(CPanelBodyNylon, CPanel)
	//{{AFX_MSG_MAP(CPanelBodyNylon)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelBodyNylon::CPanelBodyNylon()
{
}


int CPanelBodyNylon::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_size.CreateControl("SIZE", CTRL_VGKNOB1, 10, 35, this, 0))
		return -1;

	if (!m_bottom.CreateControl("BOTTOM", CTRL_VGKNOB1, 69, 35, this, 0))
		return -1;

	if (!m_reso.CreateControl("RESO", CTRL_VGKNOB1, 125, 35, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 10, 93, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelBodyNylon::AttachVGData(CPatch *patch)
{
	CNBody	*body;
	
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		body = &((CNylonStrings *) patch->instrument)->body;

		m_preset.AttachVGData(&m_presetData);
		m_size.AttachVGData(&body->size);
		m_bottom.AttachVGData(&body->bottom);
		m_reso.AttachVGData(&body->reso);
		m_level.AttachVGData(&body->level);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_size.AttachVGData(NULL);
		m_bottom.AttachVGData(NULL);
		m_reso.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
	}
}

CString	CPanelBodyNylon::getPresetDir()
{
	return "preset\\Instrument\\NBody\\";
}


int CPanelBodyNylon::setAllPanelData(char *buffer)
{
	CNBody	*body;
	
	body = &((CNylonStrings *) g_currentPatch->instrument)->body;

	return body->setVGData(&buffer);
}


int CPanelBodyNylon::getAllPanelData(char *buffer)
{
	CNBody	*body;
	
	body = &((CNylonStrings *) g_currentPatch->instrument)->body;

	return body->getVGData(&buffer);
}

//////////////// CPanelBodyNylonII ///////////////

BEGIN_MESSAGE_MAP(CPanelBodyNylonII, CPanel)
	//{{AFX_MSG_MAP(CPanelBodyNylonII)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelBodyNylonII::CPanelBodyNylonII()
{
}


int CPanelBodyNylonII::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_attack.CreateControl("ATTACK", CTRL_VGKNOB1, 10, 35, this, 0))
		return -1;

	if (!m_body.CreateControl("BODY", CTRL_VGKNOB1, 69, 35, this, 0))
		return -1;

	if (!m_tone.CreateControl("TONE", CTRL_VGKNOB1, 125, 35, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 10, 93, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelBodyNylonII::AttachVGData(CPatch *patch)
{
	CNIIBody	*body;
	
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		body = &((CNylonII *) patch->instrument)->body;

		m_preset.AttachVGData(&m_presetData);
		m_attack.AttachVGData(&body->attack);
		m_body.AttachVGData(&body->body);
		m_tone.AttachVGData(&body->tone);
		m_level.AttachVGData(&body->level);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_attack.AttachVGData(NULL);
		m_body.AttachVGData(NULL);
		m_tone.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
	}
}


CString	CPanelBodyNylonII::getPresetDir()
{
	return "preset\\Instrument\\NBodyII\\";
}


int CPanelBodyNylonII::setAllPanelData(char *buffer)
{
	CNIIBody	*body;
	
	body = &((CNylonII *) g_currentPatch->instrument)->body;

	return body->setVGData(&buffer);
}


int CPanelBodyNylonII::getAllPanelData(char *buffer)
{
	CNIIBody	*body;
	
	body = &((CNylonII *) g_currentPatch->instrument)->body;

	return body->getVGData(&buffer);
}


//////////////// CPanelCosmGT ///////////////

BEGIN_MESSAGE_MAP(CPanelCosmGT, CPanel)
	//{{AFX_MSG_MAP(CPanelCosmGT)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelCosmGT::CPanelCosmGT()
{
}


int CPanelCosmGT::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_GT_ONOFF))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_GT_ONOFF))
		return -1;

	// Cosm Guitar type
	if (!m_cosmGtType.CreateControl("TYPE", CTRL_EDIT1, 10, 44, this, IDC_COSM_GT))
		return -1;

	//if (!m_cosmGtTypeImage.CreateControl(9, 10, 64, this, 0))
	//	return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelCosmGT::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->cosmGT.guitarOnOff);
		m_ledOnOff.AttachVGData(&patch->cosmGT.guitarOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}


	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_cosmGtType.AttachVGData(&patch->cosmGT.guitarType);
	}
	else
	{
		m_cosmGtType.AttachVGData(NULL);
	}
}




//////////////// CPanelPShifter ///////////////

BEGIN_MESSAGE_MAP(CPanelPShifter, CPanel)
	//{{AFX_MSG_MAP(CPanelPShifter)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPShifter::CPanelPShifter()
{
}


int CPanelPShifter::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);


	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_MOD_ONOFF))
		return -1;

	if (!m_pShifterImage.CreateImageControl("", 9, 40, &g_sEffPedShift, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

	if (!m_sectionPS1.CreateControl("PS1", 90, this, 0))
		return -1;

	if (!m_ps1OnOff.CreateControl("ON/OFF", CTRL_SWITCH1, 10, 110, this, 0))
			return -1;

	if (!m_ps1Mode.CreateControl("MODE", CTRL_SWITCH1, 66, 110, this, 0))
			return -1;

	if (!m_dirLevel.CreateControl("DIR LEV", CTRL_VGKNOB1, 122, 110, this, 0))
			return -1;

	if (!m_ps1Shift.CreateControl("SHIFT", CTRL_VGKNOB1, 10, 166, this, 0))
			return -1;

	if (!m_ps1Fine.CreateControl("FINE", CTRL_VGKNOB1, 66, 166, this, 0))
			return -1;

	if (!m_ps1Feedback.CreateControl("FEEDBACK", CTRL_VGKNOB1, 122, 166, this, 0))
			return -1;

	if (!m_ps1PreDly.CreateControl("PRE DLY", CTRL_VGKNOB1, 10, 222, this, 0))
			return -1;

	if (!m_ps1Pan.CreateControl("PAN", CTRL_VGKNOB1, 66, 222, this, 0))
			return -1;

	if (!m_ps1Level.CreateControl("LEVEL", CTRL_VGKNOB1, 122, 222, this, 0))
			return -1;

	if (!m_sectionPS2.CreateControl("PS2", 280, this, 0))
		return -1;


	if (!m_ps2OnOff.CreateControl("ON/OFF", CTRL_SWITCH1, 10, 303, this, 0))
			return -1;

	if (!m_ps2Mode.CreateControl("MODE", CTRL_SWITCH1, 66, 303, this, 0))
			return -1;

	if (!m_ps2Shift.CreateControl("SHIFT", CTRL_VGKNOB1, 10, 359, this, 0))
			return -1;

	if (!m_ps2Fine.CreateControl("FINE", CTRL_VGKNOB1, 66, 359, this, 0))
			return -1;

	if (!m_ps2PreDly.CreateControl("PRE DLY", CTRL_VGKNOB1, 10, 415, this, 0))
			return -1;

	if (!m_ps2Pan.CreateControl("PAN", CTRL_VGKNOB1, 66, 415, this, 0))
			return -1;

	if (!m_ps2Level.CreateControl("LEVEL", CTRL_VGKNOB1, 122, 415, this, 0))
			return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPShifter::AttachVGData(CPatch *patch)
{
	CPitchShifter *mod;

	if (patch)
	{
		m_onOff.AttachVGData(&patch->modOnOff);
		m_ledOnOff.AttachVGData(&patch->modOnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && patch->modOnOff.getValue())
	{
		mod = (CPitchShifter *) patch->mod.mod;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&patch->mod.modeType);
		m_dirLevel.AttachVGData(&mod->dirLevel);
		m_ps1OnOff.AttachVGData(&mod->ps1OnOff);
		m_ps1Mode.AttachVGData(&mod->ps1Mode);
		m_ps1Shift.AttachVGData(&mod->ps1Shift);
		m_ps1Fine.AttachVGData(&mod->ps1Fine);
		m_ps1Feedback.AttachVGData(&mod->ps1Feedback);
		m_ps1PreDly.AttachVGData(&mod->ps1PreDly);
		m_ps1Pan.AttachVGData(&mod->ps1Pan);
		m_ps1Level.AttachVGData(&mod->ps1Level);
		m_ps2OnOff.AttachVGData(&mod->ps2OnOff);
		m_ps2Mode.AttachVGData(&mod->ps2Mode);
		m_ps2Shift.AttachVGData(&mod->ps2Shift);
		m_ps2Fine.AttachVGData(&mod->ps2Fine);
		m_ps2PreDly.AttachVGData(&mod->ps2PreDly);
		m_ps2Pan.AttachVGData(&mod->ps2Pan);
		m_ps2Level.AttachVGData(&mod->ps2Level);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_dirLevel.AttachVGData(NULL);
		m_ps1OnOff.AttachVGData(NULL);
		m_ps1Mode.AttachVGData(NULL);
		m_ps1Shift.AttachVGData(NULL);
		m_ps1Fine.AttachVGData(NULL);
		m_ps1Feedback.AttachVGData(NULL);
		m_ps1Level.AttachVGData(NULL);
		m_ps1Pan.AttachVGData(NULL);
		m_ps1PreDly.AttachVGData(NULL);
		m_ps2Fine.AttachVGData(NULL);
		m_ps2Level.AttachVGData(NULL);
		m_ps2Mode.AttachVGData(NULL);
		m_ps2OnOff.AttachVGData(NULL);
		m_ps2Pan.AttachVGData(NULL);
		m_ps2PreDly.AttachVGData(NULL);
		m_ps2Shift.AttachVGData(NULL);
	}
}


CString	CPanelPShifter::getPresetDir()
{
	return "preset\\Effect\\PShifter\\";
}


int CPanelPShifter::setAllPanelData(char *buffer)
{
	CPitchShifter *mod = (CPitchShifter *) g_currentPatch->mod.mod;

	return mod->setVGData(&buffer);
}


int CPanelPShifter::getAllPanelData(char *buffer)
{
	CPitchShifter *mod = (CPitchShifter *) g_currentPatch->mod.mod;

	return mod->getVGData(&buffer);
}


//////////////// CPanelPolyOct ///////////////

BEGIN_MESSAGE_MAP(CPanelPolyOct, CPanel)
	//{{AFX_MSG_MAP(CPanelPolyOct)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelPolyOct::CPanelPolyOct()
{
}


int CPanelPolyOct::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);


	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_POCT_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_POCT_ONOFF))
		return -1;

	if (!m_pedalImage.CreateImageControl("", 9, 40, &g_sEffPedShift, 0, this, 0))
		return -1;

		// 1Oct Controls

	if (!m_section1Oct.CreateControl("1 OCT", 80, this, 0))
		return -1;

	if (!m_1Oct[0].CreateControl("ST 1", CTRL_VGKNOB1, 10, 99, this, 0))
			return -1;

	if (!m_1Oct[1].CreateControl("ST 2", CTRL_VGKNOB1, 66, 99, this, 0))
			return -1;

	if (!m_1Oct[2].CreateControl("ST 3", CTRL_VGKNOB1, 122, 99, this, 0))
			return -1;

	if (!m_1Oct[3].CreateControl("ST 4", CTRL_VGKNOB1, 10, 155, this, 0))
			return -1;

	if (!m_1Oct[4].CreateControl("ST 5", CTRL_VGKNOB1, 66, 155, this, 0))
			return -1;

	if (!m_1Oct[5].CreateControl("ST 6", CTRL_VGKNOB1, 122, 155, this, 0))
			return -1;

	// Oct2 controls

	if (!m_section2Oct.CreateControl("2 OCT", 211, this, 0))
		return -1;

	if (!m_2Oct[0].CreateControl("ST 1", CTRL_VGKNOB1, 10, 229, this, 0))
			return -1;

	if (!m_2Oct[1].CreateControl("ST 2", CTRL_VGKNOB1, 66, 229, this, 0))
			return -1;

	if (!m_2Oct[2].CreateControl("ST 3", CTRL_VGKNOB1, 122, 229, this, 0))
			return -1;

	if (!m_2Oct[3].CreateControl("ST 4", CTRL_VGKNOB1, 10, 285, this, 0))
			return -1;

	if (!m_2Oct[4].CreateControl("ST 5", CTRL_VGKNOB1, 66, 285, this, 0))
			return -1;

	if (!m_2Oct[5].CreateControl("ST 6", CTRL_VGKNOB1, 122, 285, this, 0))
			return -1;


	// DIR Controls

	if (!m_sectionDir.CreateControl("DIR", 340, this, 0))
		return -1;

	if (!m_dir[0].CreateControl("ST 1", CTRL_VGKNOB1, 10, 359, this, 0))
			return -1;

	if (!m_dir[1].CreateControl("ST 2", CTRL_VGKNOB1, 66, 359, this, 0))
			return -1;

	if (!m_dir[2].CreateControl("ST 3", CTRL_VGKNOB1, 122, 359, this, 0))
			return -1;

	if (!m_dir[3].CreateControl("ST 4", CTRL_VGKNOB1, 10, 415, this, 0))
			return -1;

	if (!m_dir[4].CreateControl("ST 5", CTRL_VGKNOB1, 66, 415, this, 0))
			return -1;

	if (!m_dir[5].CreateControl("ST 6", CTRL_VGKNOB1, 122, 415, this, 0))
			return -1;
	

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPolyOct::AttachVGData(CPatch *patch)
{
	COctave	*pOct;

	int i;

	if (patch)
	{
		if (patch->cosmGT.guitarType.getValue() != COSMGT_POLY_OCT)
			return;
	
		pOct = &(((CPolyOct *) patch->instrument)->octave);

		if (patch->cosmGT.guitarOnOff.getValue())
		{
			m_preset.AttachVGData(&m_presetData);
			m_onOff.AttachVGData(&((CPolyOct *) patch->instrument)->ocataveOnOff);
			m_ledOnOff.AttachVGData(&((CPolyOct *) patch->instrument)->ocataveOnOff);
		}
		else
		{
			m_preset.AttachVGData(NULL);
			m_onOff.AttachVGData(NULL);
			m_ledOnOff.AttachVGData(NULL);
		}
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}


	if (patch && ((CPolyOct *) patch->instrument)->ocataveOnOff.getValue() && patch->cosmGT.guitarOnOff.getValue())
	{
		for (i = 0; i < 6; i++)
			m_1Oct[i].AttachVGData(&pOct->Oct1[i]);

		for (i = 0; i < 6; i++)
			m_2Oct[i].AttachVGData(&pOct->Oct2[i]);

		for (i = 0; i < 6; i++)
			m_dir[i].AttachVGData(&pOct->dir[i]);
	}
	else
	{
		for (i = 0; i < 6; i++)
			m_1Oct[i].AttachVGData(NULL);

		for (i = 0; i < 6; i++)
			m_2Oct[i].AttachVGData(NULL);

		for (i = 0; i < 6; i++)
			m_dir[i].AttachVGData(NULL);
	}
}


CString	CPanelPolyOct::getPresetDir()
{
	return "preset\\Instrument\\PolyOct\\";
}


int CPanelPolyOct::setAllPanelData(char *buffer)
{
	COctave *pOct = &(((CPolyOct *) g_currentPatch->instrument)->octave);	

	return pOct->setVGData(&buffer);
}


int CPanelPolyOct::getAllPanelData(char *buffer)
{
	COctave *pOct = &(((CPolyOct *) g_currentPatch->instrument)->octave);

	return pOct->getVGData(&buffer);
}

//////////////// CPanelAssign ///////////////

BEGIN_MESSAGE_MAP(CPanelAssign, CPanel)
	//{{AFX_MSG_MAP(CPanelAssign)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPanelAssign::CPanelAssign()
{
	m_assignNum = 0;
}


CString	CPanelAssign::getPresetDir()
{
	return "preset\\Assign\\";
}

int CPanelAssign::setAllPanelData(char *buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
	{
		count += g_currentPatch->assign[i].setVGData(&buffer);
	}

	count += g_currentPatch->exp.setVGData(&buffer);
	count += g_currentPatch->ctl.setVGData(&buffer);
	count += g_currentPatch->gkVol.setVGData(&buffer);
	count += g_currentPatch->gkS1S2.setVGData(&buffer);
	
	count += g_currentPatch->assignNC.expOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.ctlOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.gkVolOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.gkS1S2OnOff.setVGData(&buffer);

	for (i = 0; i < 8; i++)
		count +=  g_currentPatch->assignNC.assignOnOff[i].setVGData(&buffer);

	return count;
}


int CPanelAssign::getAllPanelData(char *buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
	{
		count += g_currentPatch->assign[i].getVGData(&buffer);
	}

	count += g_currentPatch->exp.getVGData(&buffer);
	count += g_currentPatch->ctl.getVGData(&buffer);
	count += g_currentPatch->gkVol.getVGData(&buffer);
	count += g_currentPatch->gkS1S2.getVGData(&buffer);

	count += g_currentPatch->assignNC.expOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.ctlOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.gkVolOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.gkS1S2OnOff.getVGData(&buffer);

	for (i = 0; i < 8; i++)
		count +=  g_currentPatch->assignNC.assignOnOff[i].getVGData(&buffer);

	return count;
}

void CPanelAssign::SetAssignNum(int num)
{
	m_assignNum = num;
}

int CPanelAssign::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_ASSIGN_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_ASSIGN_ONOFF))
		return -1;

	if (!m_assignTarget.CreateControl("TARGET", CTRL_EDIT1, 10, 36, this, IDC_ASSIGN_TARGET))
		return -1;

	if (!m_assignMin1.CreateControl("MIN", CTRL_VGKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax1.CreateControl("MAX", CTRL_VGKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin2.CreateControl("MIN", CTRL_AMPKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax2.CreateControl("MAX", CTRL_AMPKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin3.CreateControl("MIN", CTRL_AMPKNOB2, 8, 57, this, 0))
		return -1;

	if (!m_assignMax3.CreateControl("MAX", CTRL_AMPKNOB2, 70, 57, this, 0))
		return -1;

	if (!m_assignMin4.CreateControl("MIN", CTRL_SWITCH1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax4.CreateControl("MAX", CTRL_SWITCH1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin5.CreateControl("MIN", CTRL_GTKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax5.CreateControl("MAX", CTRL_GTKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin6.CreateControl("MIN", CTRL_SELECTOR, 8, 57, this, 0))
		return -1;

	if (!m_assignMax6.CreateControl("MAX", CTRL_SELECTOR, 69, 57, this, 0))
		return -1;

	if (!m_assignMode.CreateControl("MODE", CTRL_SWITCH1, 129, 57, this, 0))
		return -1;

	if (!m_assignSource.CreateControl("SOURCE", CTRL_EDIT2, 65, 135, this, 0))
		return -1;

	if (!m_assignSourceImagePedal.CreateImageControl("", 10, 120, &g_assignPedal, 0, this, 0))
		return -1;

	if (!m_assignSourceImageCtl.CreateImageControl("", 10, 120, &g_assignCtl, 0, this, 0))
		return -1;

	if (!m_assignSourceImageKGVol.CreateImageControl("", 10, 120, &g_assignGKVol, 0, this, 0))
		return -1;

	if (!m_assignSourceImageGKS1S2.CreateImageControl("", 10, 120, &g_assignGKS1S2, 0, this, 0))
		return -1;

	if (!m_assignSourceImageMidi.CreateImageControl("", 10, 120, &g_assignMidi, 0, this, 0))
		return -1;

	//if (!m_cosmGtTypeImage.CreateControl(9, 10, 64, this, 0))
	//	return -1;

	if (!m_activeRange.CreateControl("ACTIVE RANGE", 165, this, 0))
		return -1;

	if (!m_assignActiveRangeLo.CreateControl("LO", CTRL_VGKNOB1, 10, 180, this, 0))
		return -1;

	if (!m_assignActiveRangeHi.CreateControl("HI", CTRL_VGKNOB1, 76, 180, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelAssign::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->assignNC.assignOnOff[m_assignNum]);
		m_ledOnOff.AttachVGData(&patch->assignNC.assignOnOff[m_assignNum]);
		m_preset.AttachVGData(&m_presetData);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
		m_preset.AttachVGData(NULL);
	}


	if (patch && patch->assignNC.assignOnOff[m_assignNum].getValue())
	{
		m_assignTarget.AttachVGData(&patch->assign[m_assignNum].assignTarget);

		m_assignMin1.AttachVGData(&patch->assign[m_assignNum].assignMin);
		m_assignMax1.AttachVGData(&patch->assign[m_assignNum].assignMax);
		m_assignMin2.AttachVGData(&patch->assign[m_assignNum].assignMin);
		m_assignMax2.AttachVGData(&patch->assign[m_assignNum].assignMax);
		m_assignMin3.AttachVGData(&patch->assign[m_assignNum].assignMin);
		m_assignMax3.AttachVGData(&patch->assign[m_assignNum].assignMax);
		m_assignMin4.AttachVGData(&patch->assign[m_assignNum].assignMin);
		m_assignMax4.AttachVGData(&patch->assign[m_assignNum].assignMax);
		m_assignMin5.AttachVGData(&patch->assign[m_assignNum].assignMin);
		m_assignMax5.AttachVGData(&patch->assign[m_assignNum].assignMax);
		m_assignMin6.AttachVGData(&patch->assign[m_assignNum].assignMin);
		m_assignMax6.AttachVGData(&patch->assign[m_assignNum].assignMax);

		m_assignSource.AttachVGData(&patch->assign[m_assignNum].assignSource);
		m_assignMode.AttachVGData(&patch->assign[m_assignNum].assignMode);
		m_assignActiveRangeLo.AttachVGData(&patch->assignNC.assignActiveRangeLo[m_assignNum]);
		m_assignActiveRangeHi.AttachVGData(&patch->assignNC.assignActiveRangeHi[m_assignNum]);
	}
	else
	{
		m_assignTarget.AttachVGData(NULL);
		m_assignMin1.AttachVGData(NULL);
		m_assignMax1.AttachVGData(NULL);
		m_assignMin2.AttachVGData(NULL);
		m_assignMax2.AttachVGData(NULL);
		m_assignMin3.AttachVGData(NULL);
		m_assignMax3.AttachVGData(NULL);
		m_assignMin4.AttachVGData(NULL);
		m_assignMax4.AttachVGData(NULL);
		m_assignMin5.AttachVGData(NULL);
		m_assignMax5.AttachVGData(NULL);
		m_assignMin6.AttachVGData(NULL);
		m_assignMax6.AttachVGData(NULL);
		m_assignMode.AttachVGData(NULL);
		m_assignSource.AttachVGData(NULL);
		m_assignActiveRangeLo.AttachVGData(NULL);
		m_assignActiveRangeHi.AttachVGData(NULL);
	}

	if (patch)
	{
		ShowRightKnob(patch->assign[m_assignNum].assignTarget.getValue());

		switch(patch->assign[m_assignNum].assignSource.getValue())
		{
			case ASSIGN_CTL_PEDAL:
			case ASSIGN_SUB_CRL1:
			case ASSIGN_SUB_CTL2:
			case ASSIGN_GK_S1_S2:
				m_activeRange.ShowWindow(SW_HIDE);
				m_assignActiveRangeLo.ShowWindow(SW_HIDE);
				m_assignActiveRangeHi.ShowWindow(SW_HIDE);
				break;

			default:
				m_activeRange.ShowWindow(SW_SHOWNOACTIVATE);
				m_assignActiveRangeLo.ShowWindow(SW_SHOWNOACTIVATE);
				m_assignActiveRangeHi.ShowWindow(SW_SHOWNOACTIVATE);
		}

		switch(patch->assign[m_assignNum].assignSource.getValue())
		{
			case ASSIGN_EXP_PEDAL:
			case ASSIGN_SUB_EXP:
				m_assignSourceImagePedal.ShowWindow(SW_SHOWNOACTIVATE);
				m_assignSourceImageCtl.ShowWindow(SW_HIDE);
				m_assignSourceImageKGVol.ShowWindow(SW_HIDE);
				m_assignSourceImageGKS1S2.ShowWindow(SW_HIDE);
				m_assignSourceImageMidi.ShowWindow(SW_HIDE);
				break;

			case ASSIGN_CTL_PEDAL:
			case ASSIGN_SUB_CRL1:
			case ASSIGN_SUB_CTL2:
				m_assignSourceImagePedal.ShowWindow(SW_HIDE);
				m_assignSourceImageCtl.ShowWindow(SW_SHOWNOACTIVATE);
				m_assignSourceImageKGVol.ShowWindow(SW_HIDE);
				m_assignSourceImageGKS1S2.ShowWindow(SW_HIDE);
				m_assignSourceImageMidi.ShowWindow(SW_HIDE);
				break;

			case ASSIGN_GK_VOL:
				m_assignSourceImagePedal.ShowWindow(SW_HIDE);
				m_assignSourceImageCtl.ShowWindow(SW_HIDE);
				m_assignSourceImageKGVol.ShowWindow(SW_SHOWNOACTIVATE);
				m_assignSourceImageGKS1S2.ShowWindow(SW_HIDE);
				m_assignSourceImageMidi.ShowWindow(SW_HIDE);
				break;

			case ASSIGN_GK_S1_S2:
				m_assignSourceImagePedal.ShowWindow(SW_HIDE);
				m_assignSourceImageCtl.ShowWindow(SW_HIDE);
				m_assignSourceImageKGVol.ShowWindow(SW_HIDE);
				m_assignSourceImageGKS1S2.ShowWindow(SW_SHOWNOACTIVATE);
				m_assignSourceImageMidi.ShowWindow(SW_HIDE);
				break;

			default:
				m_assignSourceImagePedal.ShowWindow(SW_HIDE);
				m_assignSourceImageCtl.ShowWindow(SW_HIDE);
				m_assignSourceImageKGVol.ShowWindow(SW_HIDE);
				m_assignSourceImageGKS1S2.ShowWindow(SW_HIDE);
				m_assignSourceImageMidi.ShowWindow(SW_SHOWNOACTIVATE);
		}
	}
	else
	{
		m_assignMax1.ShowWindow(SW_HIDE);
		m_assignMin1.ShowWindow(SW_HIDE);
		m_assignMax2.ShowWindow(SW_HIDE);
		m_assignMin2.ShowWindow(SW_HIDE);
		m_assignMax3.ShowWindow(SW_HIDE);
		m_assignMin3.ShowWindow(SW_HIDE);
		m_assignMax4.ShowWindow(SW_HIDE);
		m_assignMin4.ShowWindow(SW_HIDE);
		m_assignMax5.ShowWindow(SW_HIDE);
		m_assignMin5.ShowWindow(SW_HIDE);
		m_assignMax6.ShowWindow(SW_HIDE);
		m_assignMin6.ShowWindow(SW_HIDE);
		m_assignSourceImagePedal.ShowWindow(SW_HIDE);
		m_assignSourceImageCtl.ShowWindow(SW_HIDE);
		m_assignSourceImageKGVol.ShowWindow(SW_HIDE);
		m_assignSourceImageGKS1S2.ShowWindow(SW_HIDE);
		m_assignSourceImageMidi.ShowWindow(SW_HIDE);
	}
}


void CPanelAssign::ShowRightKnob(int value)
{
	switch(value)
	{
		// Amp knob
		case 116:
		case 117:
		case 118:
		case 119:
		case 120:
		case 121:
		case 122:
			m_assignMax1.ShowWindow(SW_HIDE);
			m_assignMin1.ShowWindow(SW_HIDE);
			m_assignMax2.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMin2.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMax3.ShowWindow(SW_HIDE);
			m_assignMin3.ShowWindow(SW_HIDE);
			m_assignMax4.ShowWindow(SW_HIDE);
			m_assignMin4.ShowWindow(SW_HIDE);
			m_assignMax5.ShowWindow(SW_HIDE);
			m_assignMin5.ShowWindow(SW_HIDE);
			m_assignMax6.ShowWindow(SW_HIDE);
			m_assignMin6.ShowWindow(SW_HIDE);
			break;

		// COSM AMP      GAIN
		case 123:
			m_assignMax1.ShowWindow(SW_HIDE);
			m_assignMin1.ShowWindow(SW_HIDE);
			m_assignMax2.ShowWindow(SW_HIDE);
			m_assignMin2.ShowWindow(SW_HIDE);
			m_assignMax3.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMin3.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMax4.ShowWindow(SW_HIDE);
			m_assignMin4.ShowWindow(SW_HIDE);
			m_assignMax5.ShowWindow(SW_HIDE);
			m_assignMin5.ShowWindow(SW_HIDE);
			m_assignMax6.ShowWindow(SW_HIDE);
			m_assignMin6.ShowWindow(SW_HIDE);
			break;

		// Switch control
		case 0:
		case 6:
		case 15:
		case 46:
		case 54:
		case 62:
		case 64:
		case 65:
		case 66:
		case 67:
		case 68:
		case 69:
		case 70:
		case 75:
		case 80:
		case 99:
		case 115:
		case 125:
		case 132:
		case 140:
		case 146:
		case 147:
		case 152:
		case 156:
		case 163:
		case 198:
		case 202:
		case 206:
		case 209:
		case 214:
		case 228:
			m_assignMax1.ShowWindow(SW_HIDE);
			m_assignMin1.ShowWindow(SW_HIDE);
			m_assignMax2.ShowWindow(SW_HIDE);
			m_assignMin2.ShowWindow(SW_HIDE);
			m_assignMax3.ShowWindow(SW_HIDE);
			m_assignMin3.ShowWindow(SW_HIDE);
			m_assignMax4.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMin4.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMax5.ShowWindow(SW_HIDE);
			m_assignMin5.ShowWindow(SW_HIDE);
			m_assignMax6.ShowWindow(SW_HIDE);
			m_assignMin6.ShowWindow(SW_HIDE);
			break;

		case 12:
			m_assignMax1.ShowWindow(SW_HIDE);
			m_assignMin1.ShowWindow(SW_HIDE);
			m_assignMax2.ShowWindow(SW_HIDE);
			m_assignMin2.ShowWindow(SW_HIDE);
			m_assignMax3.ShowWindow(SW_HIDE);
			m_assignMin3.ShowWindow(SW_HIDE);
			m_assignMax4.ShowWindow(SW_HIDE);
			m_assignMin4.ShowWindow(SW_HIDE);
			m_assignMax5.ShowWindow(SW_HIDE);
			m_assignMin5.ShowWindow(SW_HIDE);
			m_assignMax6.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMin6.ShowWindow(SW_SHOWNOACTIVATE);
			break;

		case 13:
		case 14:
			m_assignMax1.ShowWindow(SW_HIDE);
			m_assignMin1.ShowWindow(SW_HIDE);
			m_assignMax2.ShowWindow(SW_HIDE);
			m_assignMin2.ShowWindow(SW_HIDE);
			m_assignMax3.ShowWindow(SW_HIDE);
			m_assignMin3.ShowWindow(SW_HIDE);
			m_assignMax4.ShowWindow(SW_HIDE);
			m_assignMin4.ShowWindow(SW_HIDE);
			m_assignMax5.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMin5.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMax6.ShowWindow(SW_HIDE);
			m_assignMin6.ShowWindow(SW_HIDE);
			break;

		default:
			m_assignMax1.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMin1.ShowWindow(SW_SHOWNOACTIVATE);
			m_assignMax2.ShowWindow(SW_HIDE);
			m_assignMin2.ShowWindow(SW_HIDE);
			m_assignMax3.ShowWindow(SW_HIDE);
			m_assignMin3.ShowWindow(SW_HIDE);
			m_assignMax4.ShowWindow(SW_HIDE);
			m_assignMin4.ShowWindow(SW_HIDE);
			m_assignMax5.ShowWindow(SW_HIDE);
			m_assignMin5.ShowWindow(SW_HIDE);
			m_assignMax6.ShowWindow(SW_HIDE);
			m_assignMin6.ShowWindow(SW_HIDE);
	}
}

BOOL CPanelAssign::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == IDC_ASSIGN_TARGET)
	{
		int firstValue = ((CAssignMinMax *) m_assignMin1.m_vgData)->vgData->getFirstValue();

		m_assignMin1.m_vgData->setValue(firstValue);
		m_assignMax1.m_vgData->setValue(((CAssignMinMax *) m_assignMax1.m_vgData)->vgData->getRange() - 1 + firstValue);
	}
	else
	{
		// Notify the parent window that a refresh of the panel is needed
		GetParent()->PostMessage(WM_COMMAND, wParam, (long) this);
	}

	return CPanel ::OnCommand(wParam, lParam);
}



//////////////// CPanelAssignExp ///////////////

BEGIN_MESSAGE_MAP(CPanelAssignExp, CPanelAssign)
	//{{AFX_MSG_MAP(CPanelAssignExp)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString	CPanelAssignExp::getPresetDir()
{
	return "preset\\Assign\\";
}

int CPanelAssignExp::setAllPanelData(char *buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
	{
		count += g_currentPatch->assign[i].setVGData(&buffer);
	}

	count += g_currentPatch->exp.setVGData(&buffer);
	count += g_currentPatch->ctl.setVGData(&buffer);
	count += g_currentPatch->gkVol.setVGData(&buffer);
	count += g_currentPatch->gkS1S2.setVGData(&buffer);
	
	count += g_currentPatch->assignNC.expOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.ctlOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.gkVolOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.gkS1S2OnOff.setVGData(&buffer);

	for (i = 0; i < 8; i++)
		count +=  g_currentPatch->assignNC.assignOnOff[i].setVGData(&buffer);

	return count;
}


int CPanelAssignExp::getAllPanelData(char *buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
	{
		count += g_currentPatch->assign[i].getVGData(&buffer);
	}

	count += g_currentPatch->exp.getVGData(&buffer);
	count += g_currentPatch->ctl.getVGData(&buffer);
	count += g_currentPatch->gkVol.getVGData(&buffer);
	count += g_currentPatch->gkS1S2.getVGData(&buffer);

	count += g_currentPatch->assignNC.expOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.ctlOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.gkVolOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.gkS1S2OnOff.getVGData(&buffer);

	for (i = 0; i < 8; i++)
		count +=  g_currentPatch->assignNC.assignOnOff[i].getVGData(&buffer);

	return count;
}

int CPanelAssignExp::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_ASSIGN_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_ASSIGN_ONOFF))
		return -1;

	if (!m_assignTarget.CreateControl("TARGET", CTRL_EDIT1, 10, 36, this, IDC_ASSIGN_TARGET))
		return -1;

	if (!m_assignMin1.CreateControl("MIN", CTRL_VGKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax1.CreateControl("MAX", CTRL_VGKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin2.CreateControl("MIN", CTRL_AMPKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax2.CreateControl("MAX", CTRL_AMPKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin3.CreateControl("MIN", CTRL_AMPKNOB2, 8, 57, this, 0))
		return -1;

	if (!m_assignMax3.CreateControl("MAX", CTRL_AMPKNOB2, 70, 57, this, 0))
		return -1;

	if (!m_assignMin4.CreateControl("MIN", CTRL_SWITCH1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax4.CreateControl("MAX", CTRL_SWITCH1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin5.CreateControl("MIN", CTRL_GTKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax5.CreateControl("MAX", CTRL_GTKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin6.CreateControl("MIN", CTRL_SELECTOR, 8, 57, this, 0))
		return -1;

	if (!m_assignMax6.CreateControl("MAX", CTRL_SELECTOR, 69, 57, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelAssignExp::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->assignNC.expOnOff);
		m_ledOnOff.AttachVGData(&patch->assignNC.expOnOff);
		m_preset.AttachVGData(&m_presetData);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
		m_preset.AttachVGData(NULL);
	}


	if (patch && patch->assignNC.expOnOff.getValue())
	{
		m_assignTarget.AttachVGData(&patch->exp.expTarget);

		m_assignMin1.AttachVGData(&patch->exp.expMin);
		m_assignMax1.AttachVGData(&patch->exp.expMax);
		m_assignMin2.AttachVGData(&patch->exp.expMin);
		m_assignMax2.AttachVGData(&patch->exp.expMax);
		m_assignMin3.AttachVGData(&patch->exp.expMin);
		m_assignMax3.AttachVGData(&patch->exp.expMax);
		m_assignMin4.AttachVGData(&patch->exp.expMin);
		m_assignMax4.AttachVGData(&patch->exp.expMax);
		m_assignMin5.AttachVGData(&patch->exp.expMin);
		m_assignMax5.AttachVGData(&patch->exp.expMax);
		m_assignMin6.AttachVGData(&patch->exp.expMin);
		m_assignMax6.AttachVGData(&patch->exp.expMax);
	}
	else
	{
		m_assignTarget.AttachVGData(NULL);
		m_assignMin1.AttachVGData(NULL);
		m_assignMax1.AttachVGData(NULL);
		m_assignMin2.AttachVGData(NULL);
		m_assignMax2.AttachVGData(NULL);
		m_assignMin3.AttachVGData(NULL);
		m_assignMax3.AttachVGData(NULL);
		m_assignMin4.AttachVGData(NULL);
		m_assignMax4.AttachVGData(NULL);
		m_assignMin5.AttachVGData(NULL);
		m_assignMax5.AttachVGData(NULL);
		m_assignMin6.AttachVGData(NULL);
		m_assignMax6.AttachVGData(NULL);
	}

	if (patch)
		ShowRightKnob(patch->exp.expTarget.getValue());
	else
	{
		m_assignMax1.ShowWindow(SW_HIDE);
		m_assignMin1.ShowWindow(SW_HIDE);
		m_assignMax2.ShowWindow(SW_HIDE);
		m_assignMin2.ShowWindow(SW_HIDE);
		m_assignMax3.ShowWindow(SW_HIDE);
		m_assignMin3.ShowWindow(SW_HIDE);
		m_assignMax4.ShowWindow(SW_HIDE);
		m_assignMin4.ShowWindow(SW_HIDE);
		m_assignMax5.ShowWindow(SW_HIDE);
		m_assignMin5.ShowWindow(SW_HIDE);
		m_assignMax6.ShowWindow(SW_HIDE);
		m_assignMin6.ShowWindow(SW_HIDE);
	}
}


//////////////// CPanelAssignCtl ///////////////

BEGIN_MESSAGE_MAP(CPanelAssignCtl, CPanelAssign)
	//{{AFX_MSG_MAP(CPanelAssignCtl)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString	CPanelAssignCtl::getPresetDir()
{
	return "preset\\Assign\\";
}

int CPanelAssignCtl::setAllPanelData(char *buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
	{
		count += g_currentPatch->assign[i].setVGData(&buffer);
	}

	count += g_currentPatch->exp.setVGData(&buffer);
	count += g_currentPatch->ctl.setVGData(&buffer);
	count += g_currentPatch->gkVol.setVGData(&buffer);
	count += g_currentPatch->gkS1S2.setVGData(&buffer);
	
	count += g_currentPatch->assignNC.expOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.ctlOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.gkVolOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.gkS1S2OnOff.setVGData(&buffer);

	for (i = 0; i < 8; i++)
		count +=  g_currentPatch->assignNC.assignOnOff[i].setVGData(&buffer);

	return count;
}


int CPanelAssignCtl::getAllPanelData(char *buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
	{
		count += g_currentPatch->assign[i].getVGData(&buffer);
	}

	count += g_currentPatch->exp.getVGData(&buffer);
	count += g_currentPatch->ctl.getVGData(&buffer);
	count += g_currentPatch->gkVol.getVGData(&buffer);
	count += g_currentPatch->gkS1S2.getVGData(&buffer);

	count += g_currentPatch->assignNC.expOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.ctlOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.gkVolOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.gkS1S2OnOff.getVGData(&buffer);

	for (i = 0; i < 8; i++)
		count +=  g_currentPatch->assignNC.assignOnOff[i].getVGData(&buffer);

	return count;
}

int CPanelAssignCtl::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_ASSIGN_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_ASSIGN_ONOFF))
		return -1;

	if (!m_assignTarget.CreateControl("TARGET", CTRL_EDIT1, 10, 36, this, IDC_ASSIGN_TARGET))
		return -1;

	if (!m_assignMin1.CreateControl("MIN", CTRL_VGKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax1.CreateControl("MAX", CTRL_VGKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin2.CreateControl("MIN", CTRL_AMPKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax2.CreateControl("MAX", CTRL_AMPKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin3.CreateControl("MIN", CTRL_AMPKNOB2, 8, 57, this, 0))
		return -1;

	if (!m_assignMax3.CreateControl("MAX", CTRL_AMPKNOB2, 70, 57, this, 0))
		return -1;

	if (!m_assignMin4.CreateControl("MIN", CTRL_SWITCH1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax4.CreateControl("MAX", CTRL_SWITCH1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin5.CreateControl("MIN", CTRL_GTKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax5.CreateControl("MAX", CTRL_GTKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin6.CreateControl("MIN", CTRL_SELECTOR, 8, 57, this, 0))
		return -1;

	if (!m_assignMax6.CreateControl("MAX", CTRL_SELECTOR, 69, 57, this, 0))
		return -1;

	if (!m_assignMode.CreateControl("MODE", CTRL_SWITCH1, 129, 57, this, 0))
		return -1;



	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelAssignCtl::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->assignNC.ctlOnOff);
		m_ledOnOff.AttachVGData(&patch->assignNC.ctlOnOff);
		m_preset.AttachVGData(&m_presetData);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
		m_preset.AttachVGData(NULL);
	}


	if (patch && patch->assignNC.ctlOnOff.getValue())
	{
		m_assignTarget.AttachVGData(&patch->ctl.ctlTarget);

		m_assignMin1.AttachVGData(&patch->ctl.ctlMin);
		m_assignMax1.AttachVGData(&patch->ctl.ctlMax);
		m_assignMin2.AttachVGData(&patch->ctl.ctlMin);
		m_assignMax2.AttachVGData(&patch->ctl.ctlMax);
		m_assignMin3.AttachVGData(&patch->ctl.ctlMin);
		m_assignMax3.AttachVGData(&patch->ctl.ctlMax);
		m_assignMin4.AttachVGData(&patch->ctl.ctlMin);
		m_assignMax4.AttachVGData(&patch->ctl.ctlMax);
		m_assignMin5.AttachVGData(&patch->ctl.ctlMin);
		m_assignMax5.AttachVGData(&patch->ctl.ctlMax);
		m_assignMin6.AttachVGData(&patch->ctl.ctlMin);
		m_assignMax6.AttachVGData(&patch->ctl.ctlMax);
		m_assignMode.AttachVGData(&patch->ctl.ctlmode);
	}
	else
	{
		m_assignTarget.AttachVGData(NULL);
		m_assignMin1.AttachVGData(NULL);
		m_assignMax1.AttachVGData(NULL);
		m_assignMin2.AttachVGData(NULL);
		m_assignMax2.AttachVGData(NULL);
		m_assignMin3.AttachVGData(NULL);
		m_assignMax3.AttachVGData(NULL);
		m_assignMin4.AttachVGData(NULL);
		m_assignMax4.AttachVGData(NULL);
		m_assignMin5.AttachVGData(NULL);
		m_assignMax5.AttachVGData(NULL);
		m_assignMin6.AttachVGData(NULL);
		m_assignMax6.AttachVGData(NULL);
		m_assignMode.AttachVGData(NULL);
	}

	if (patch)
		ShowRightKnob(patch->ctl.ctlTarget.getValue());
	else
	{
		m_assignMax1.ShowWindow(SW_HIDE);
		m_assignMin1.ShowWindow(SW_HIDE);
		m_assignMax2.ShowWindow(SW_HIDE);
		m_assignMin2.ShowWindow(SW_HIDE);
		m_assignMax3.ShowWindow(SW_HIDE);
		m_assignMin3.ShowWindow(SW_HIDE);
		m_assignMax4.ShowWindow(SW_HIDE);
		m_assignMin4.ShowWindow(SW_HIDE);
		m_assignMax5.ShowWindow(SW_HIDE);
		m_assignMin5.ShowWindow(SW_HIDE);
		m_assignMax6.ShowWindow(SW_HIDE);
		m_assignMin6.ShowWindow(SW_HIDE);
	}
}



//////////////// CPanelAssignGkVol ///////////////

BEGIN_MESSAGE_MAP(CPanelAssignGkVol, CPanelAssign)
	//{{AFX_MSG_MAP(CPanelAssignGkVol)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CString	CPanelAssignGkVol::getPresetDir()
{
	return "preset\\Assign\\";
}

int CPanelAssignGkVol::setAllPanelData(char *buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
	{
		count += g_currentPatch->assign[i].setVGData(&buffer);
	}

	count += g_currentPatch->exp.setVGData(&buffer);
	count += g_currentPatch->ctl.setVGData(&buffer);
	count += g_currentPatch->gkVol.setVGData(&buffer);
	count += g_currentPatch->gkS1S2.setVGData(&buffer);
	
	count += g_currentPatch->assignNC.expOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.ctlOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.gkVolOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.gkS1S2OnOff.setVGData(&buffer);

	for (i = 0; i < 8; i++)
		count +=  g_currentPatch->assignNC.assignOnOff[i].setVGData(&buffer);

	return count;
}


int CPanelAssignGkVol::getAllPanelData(char *buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
	{
		count += g_currentPatch->assign[i].getVGData(&buffer);
	}

	count += g_currentPatch->exp.getVGData(&buffer);
	count += g_currentPatch->ctl.getVGData(&buffer);
	count += g_currentPatch->gkVol.getVGData(&buffer);
	count += g_currentPatch->gkS1S2.getVGData(&buffer);

	count += g_currentPatch->assignNC.expOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.ctlOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.gkVolOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.gkS1S2OnOff.getVGData(&buffer);

	for (i = 0; i < 8; i++)
		count +=  g_currentPatch->assignNC.assignOnOff[i].getVGData(&buffer);

	return count;
}

int CPanelAssignGkVol::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_ASSIGN_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_ASSIGN_ONOFF))
		return -1;

	if (!m_assignTarget.CreateControl("TARGET", CTRL_EDIT1, 10, 36, this, IDC_ASSIGN_TARGET))
		return -1;

	if (!m_assignMin1.CreateControl("MIN", CTRL_VGKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax1.CreateControl("MAX", CTRL_VGKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin2.CreateControl("MIN", CTRL_AMPKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax2.CreateControl("MAX", CTRL_AMPKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin3.CreateControl("MIN", CTRL_AMPKNOB2, 8, 57, this, 0))
		return -1;

	if (!m_assignMax3.CreateControl("MAX", CTRL_AMPKNOB2, 70, 57, this, 0))
		return -1;

	if (!m_assignMin4.CreateControl("MIN", CTRL_SWITCH1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax4.CreateControl("MAX", CTRL_SWITCH1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin5.CreateControl("MIN", CTRL_GTKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax5.CreateControl("MAX", CTRL_GTKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin6.CreateControl("MIN", CTRL_SELECTOR, 8, 57, this, 0))
		return -1;

	if (!m_assignMax6.CreateControl("MAX", CTRL_SELECTOR, 69, 57, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelAssignGkVol::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->assignNC.gkVolOnOff);
		m_ledOnOff.AttachVGData(&patch->assignNC.gkVolOnOff);
		m_preset.AttachVGData(&m_presetData);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
		m_preset.AttachVGData(NULL);
	}


	if (patch && patch->assignNC.gkVolOnOff.getValue())
	{
		m_assignTarget.AttachVGData(&patch->gkVol.gkVolTarget);

		m_assignMin1.AttachVGData(&patch->gkVol.gkVolMin);
		m_assignMax1.AttachVGData(&patch->gkVol.gkVolMax);
		m_assignMin2.AttachVGData(&patch->gkVol.gkVolMin);
		m_assignMax2.AttachVGData(&patch->gkVol.gkVolMax);
		m_assignMin3.AttachVGData(&patch->gkVol.gkVolMin);
		m_assignMax3.AttachVGData(&patch->gkVol.gkVolMax);
		m_assignMin4.AttachVGData(&patch->gkVol.gkVolMin);
		m_assignMax4.AttachVGData(&patch->gkVol.gkVolMax);
		m_assignMin5.AttachVGData(&patch->gkVol.gkVolMin);
		m_assignMax5.AttachVGData(&patch->gkVol.gkVolMax);
		m_assignMin6.AttachVGData(&patch->gkVol.gkVolMin);
		m_assignMax6.AttachVGData(&patch->gkVol.gkVolMax);
	}
	else
	{
		m_assignTarget.AttachVGData(NULL);
		m_assignMin1.AttachVGData(NULL);
		m_assignMax1.AttachVGData(NULL);
		m_assignMin2.AttachVGData(NULL);
		m_assignMax2.AttachVGData(NULL);
		m_assignMin3.AttachVGData(NULL);
		m_assignMax3.AttachVGData(NULL);
		m_assignMin4.AttachVGData(NULL);
		m_assignMax4.AttachVGData(NULL);
		m_assignMin5.AttachVGData(NULL);
		m_assignMax5.AttachVGData(NULL);
		m_assignMin6.AttachVGData(NULL);
		m_assignMax6.AttachVGData(NULL);
	}

	if (patch)
		ShowRightKnob(patch->gkVol.gkVolTarget.getValue());
	else
	{
		m_assignMax1.ShowWindow(SW_HIDE);
		m_assignMin1.ShowWindow(SW_HIDE);
		m_assignMax2.ShowWindow(SW_HIDE);
		m_assignMin2.ShowWindow(SW_HIDE);
		m_assignMax3.ShowWindow(SW_HIDE);
		m_assignMin3.ShowWindow(SW_HIDE);
		m_assignMax4.ShowWindow(SW_HIDE);
		m_assignMin4.ShowWindow(SW_HIDE);
		m_assignMax5.ShowWindow(SW_HIDE);
		m_assignMin5.ShowWindow(SW_HIDE);
		m_assignMax6.ShowWindow(SW_HIDE);
		m_assignMin6.ShowWindow(SW_HIDE);
	}
}



//////////////// CPanelAssignGkS1S2 ///////////////

BEGIN_MESSAGE_MAP(CPanelAssignGkS1S2, CPanelAssign)
	//{{AFX_MSG_MAP(CPanelAssignGkS1S2)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CString	CPanelAssignGkS1S2::getPresetDir()
{
	return "preset\\Assign\\";
}

int CPanelAssignGkS1S2::setAllPanelData(char *buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
	{
		count += g_currentPatch->assign[i].setVGData(&buffer);
	}

	count += g_currentPatch->exp.setVGData(&buffer);
	count += g_currentPatch->ctl.setVGData(&buffer);
	count += g_currentPatch->gkVol.setVGData(&buffer);
	count += g_currentPatch->gkS1S2.setVGData(&buffer);
	
	count += g_currentPatch->assignNC.expOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.ctlOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.gkVolOnOff.setVGData(&buffer);
	count += g_currentPatch->assignNC.gkS1S2OnOff.setVGData(&buffer);

	for (i = 0; i < 8; i++)
		count +=  g_currentPatch->assignNC.assignOnOff[i].setVGData(&buffer);

	return count;
}


int CPanelAssignGkS1S2::getAllPanelData(char *buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
	{
		count += g_currentPatch->assign[i].getVGData(&buffer);
	}

	count += g_currentPatch->exp.getVGData(&buffer);
	count += g_currentPatch->ctl.getVGData(&buffer);
	count += g_currentPatch->gkVol.getVGData(&buffer);
	count += g_currentPatch->gkS1S2.getVGData(&buffer);

	count += g_currentPatch->assignNC.expOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.ctlOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.gkVolOnOff.getVGData(&buffer);
	count += g_currentPatch->assignNC.gkS1S2OnOff.getVGData(&buffer);

	for (i = 0; i < 8; i++)
		count +=  g_currentPatch->assignNC.assignOnOff[i].getVGData(&buffer);

	return count;
}

int CPanelAssignGkS1S2::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_ASSIGN_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_ASSIGN_ONOFF))
		return -1;

	if (!m_assignTarget.CreateControl("TARGET", CTRL_EDIT1, 10, 36, this, IDC_ASSIGN_TARGET))
		return -1;

	if (!m_assignMin1.CreateControl("MIN", CTRL_VGKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax1.CreateControl("MAX", CTRL_VGKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin2.CreateControl("MIN", CTRL_AMPKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax2.CreateControl("MAX", CTRL_AMPKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin3.CreateControl("MIN", CTRL_AMPKNOB2, 8, 57, this, 0))
		return -1;

	if (!m_assignMax3.CreateControl("MAX", CTRL_AMPKNOB2, 70, 57, this, 0))
		return -1;

	if (!m_assignMin4.CreateControl("MIN", CTRL_SWITCH1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax4.CreateControl("MAX", CTRL_SWITCH1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin5.CreateControl("MIN", CTRL_GTKNOB1, 8, 57, this, 0))
		return -1;

	if (!m_assignMax5.CreateControl("MAX", CTRL_GTKNOB1, 70, 57, this, 0))
		return -1;

	if (!m_assignMin6.CreateControl("MIN", CTRL_SELECTOR, 8, 57, this, 0))
		return -1;

	if (!m_assignMax6.CreateControl("MAX", CTRL_SELECTOR, 69, 57, this, 0))
		return -1;

	if (!m_assignMode.CreateControl("MODE", CTRL_SWITCH1, 129, 57, this, 0))
		return -1;



	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelAssignGkS1S2::AttachVGData(CPatch *patch)
{
	if (patch)
	{
		m_onOff.AttachVGData(&patch->assignNC.gkS1S2OnOff);
		m_ledOnOff.AttachVGData(&patch->assignNC.gkS1S2OnOff);
		m_preset.AttachVGData(&m_presetData);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
		m_preset.AttachVGData(NULL);
	}


	if (patch && patch->assignNC.gkS1S2OnOff.getValue())
	{
		m_assignTarget.AttachVGData(&patch->gkS1S2.gkS1S2Target);

		m_assignMin1.AttachVGData(&patch->gkS1S2.gkS1S2Min);
		m_assignMax1.AttachVGData(&patch->gkS1S2.gkS1S2Max);
		m_assignMin2.AttachVGData(&patch->gkS1S2.gkS1S2Min);
		m_assignMax2.AttachVGData(&patch->gkS1S2.gkS1S2Max);
		m_assignMin3.AttachVGData(&patch->gkS1S2.gkS1S2Min);
		m_assignMax3.AttachVGData(&patch->gkS1S2.gkS1S2Max);
		m_assignMin4.AttachVGData(&patch->gkS1S2.gkS1S2Min);
		m_assignMax4.AttachVGData(&patch->gkS1S2.gkS1S2Max);
		m_assignMin5.AttachVGData(&patch->gkS1S2.gkS1S2Min);
		m_assignMax5.AttachVGData(&patch->gkS1S2.gkS1S2Max);
		m_assignMin6.AttachVGData(&patch->gkS1S2.gkS1S2Min);
		m_assignMax6.AttachVGData(&patch->gkS1S2.gkS1S2Max);
		m_assignMode.AttachVGData(&patch->gkS1S2.gkS1S2mode);
	}
	else
	{
		m_assignTarget.AttachVGData(NULL);
		m_assignMin1.AttachVGData(NULL);
		m_assignMax1.AttachVGData(NULL);
		m_assignMin2.AttachVGData(NULL);
		m_assignMax2.AttachVGData(NULL);
		m_assignMin3.AttachVGData(NULL);
		m_assignMax3.AttachVGData(NULL);
		m_assignMin4.AttachVGData(NULL);
		m_assignMax4.AttachVGData(NULL);
		m_assignMin5.AttachVGData(NULL);
		m_assignMax5.AttachVGData(NULL);
		m_assignMin6.AttachVGData(NULL);
		m_assignMax6.AttachVGData(NULL);
		m_assignMode.AttachVGData(NULL);
	}

	if (patch)
		ShowRightKnob(patch->gkS1S2.gkS1S2Target.getValue());
	else
	{
		m_assignMax1.ShowWindow(SW_HIDE);
		m_assignMin1.ShowWindow(SW_HIDE);
		m_assignMax2.ShowWindow(SW_HIDE);
		m_assignMin2.ShowWindow(SW_HIDE);
		m_assignMax3.ShowWindow(SW_HIDE);
		m_assignMin3.ShowWindow(SW_HIDE);
		m_assignMax4.ShowWindow(SW_HIDE);
		m_assignMin4.ShowWindow(SW_HIDE);
		m_assignMax5.ShowWindow(SW_HIDE);
		m_assignMin5.ShowWindow(SW_HIDE);
		m_assignMax6.ShowWindow(SW_HIDE);
		m_assignMin6.ShowWindow(SW_HIDE);
	}
}




//////////////// CPanelOpenTune ///////////////

BEGIN_MESSAGE_MAP(CPanelOpenTune, CPanel)
	//{{AFX_MSG_MAP(CPanelOpenTune)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelOpenTune::OnCreate(LPCREATESTRUCT lpcs)
{
	int i;
	char caption[50];

	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_PTSHIFT_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_PTSHIFT_ONOFF))
		return -1;

	if (!m_pedalImage.CreateImageControl("", 9, 40, &g_sEffPedShift, 0, this, 0))
		return -1;

	if (!m_type.CreateControl("TYPE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

	for (i = 0; i < 6; i++)
	{
		sprintf(caption, "ST-%d", 6 - i);

		if (!m_shift[5 - i].CreateControl(caption, CTRL_VFADER1, 11 + i * 27, 80, this, 1033))
			return -1;
	}

	return 0;
}


void CPanelOpenTune::AttachVGData(CPatch *patch)
{
	CTune	*pOpenTune;
	int i;

	if (patch)
	{
		pOpenTune = &(((COpenTune *) patch->instrument)->tune);

		if (patch->cosmGT.guitarOnOff.getValue())
		{
			m_onOff.AttachVGData(&((COpenTune *) patch->instrument)->openTuneOnOff);
			m_ledOnOff.AttachVGData(&((COpenTune *) patch->instrument)->openTuneOnOff);
			m_preset.AttachVGData(&m_presetData);
		}
		else
		{
			m_preset.AttachVGData(NULL);
			m_onOff.AttachVGData(NULL);
			m_ledOnOff.AttachVGData(NULL);
		}
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
		m_preset.AttachVGData(&m_presetData);
	}


	if (patch && ((COpenTune *) patch->instrument)->openTuneOnOff.getValue() && patch->cosmGT.guitarOnOff.getValue())
	{
		m_type.AttachVGData(&pOpenTune->type);

		if (pOpenTune->type.getValue() == TUNE_USER)
		{
			for (i = 0; i < 6; i++)
			{
				m_shift[i].AttachVGData(&pOpenTune->shift[i]);
				pOpenTune->shift[i].setStringNum(i);
			}
		}
		else
		{
			for (i = 0; i < 6; i++)
				m_shiftPreset[i].m_needSaving = FALSE;

			switch(pOpenTune->type.getValue())
			{
				case TUNE_OPEN_D:
					m_shiftPreset[0].setValue(22); 
					m_shiftPreset[1].setValue(22); 
					m_shiftPreset[2].setValue(23); 
					m_shiftPreset[3].setValue(24); 
					m_shiftPreset[4].setValue(24); 
					m_shiftPreset[5].setValue(22); 
					break;


				case TUNE_OPEN_E:
					m_shiftPreset[0].setValue(24); 
					m_shiftPreset[1].setValue(24); 
					m_shiftPreset[2].setValue(25); 
					m_shiftPreset[3].setValue(26); 
					m_shiftPreset[4].setValue(26); 
					m_shiftPreset[5].setValue(24); 
					break;

				case TUNE_OPEN_G:
					m_shiftPreset[0].setValue(22); 
					m_shiftPreset[1].setValue(24); 
					m_shiftPreset[2].setValue(24); 
					m_shiftPreset[3].setValue(24); 
					m_shiftPreset[4].setValue(22); 
					m_shiftPreset[5].setValue(22); 
					break;

				case TUNE_OPEN_A:
					m_shiftPreset[0].setValue(24); 
					m_shiftPreset[1].setValue(26); 
					m_shiftPreset[2].setValue(26); 
					m_shiftPreset[3].setValue(26); 
					m_shiftPreset[4].setValue(24); 
					m_shiftPreset[5].setValue(24); 
					break;

				case TUNE_DROP_D:
					m_shiftPreset[0].setValue(24); 
					m_shiftPreset[1].setValue(24); 
					m_shiftPreset[2].setValue(24); 
					m_shiftPreset[3].setValue(24); 
					m_shiftPreset[4].setValue(24); 
					m_shiftPreset[5].setValue(22); 
					break;

				case TUNE_NASH_VILLE:
					m_shiftPreset[0].setValue(24); 
					m_shiftPreset[1].setValue(24); 
					m_shiftPreset[2].setValue(36); 
					m_shiftPreset[3].setValue(36); 
					m_shiftPreset[4].setValue(36); 
					m_shiftPreset[5].setValue(36); 
					break;
			}

			for (i = 0; i < 6; i++)
			{
				m_shiftPreset[i].m_needSaving = TRUE;
				m_shiftPreset[i].setStringNum(i);
				m_shift[i].AttachVGData(&m_shiftPreset[i]);
				
			}
		}
	}
	else
	{
		m_type.AttachVGData(NULL);

		for (i = 0; i < 6; i++)
			m_shift[i].AttachVGData(NULL);
	}
}


BOOL CPanelOpenTune::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	int i;

	if (wParam == IDC_TUNE)
	{
		if (m_type.m_vgData->getValue() != TUNE_USER)
		{
			m_type.m_vgData->setValue(TUNE_USER);

			for (i = 0; i < 6; i++)
			{
				((COpenTune *) g_currentPatch->instrument)->tune.shift[i].setValue(m_shiftPreset[i].getValue());
				((COpenTune *) g_currentPatch->instrument)->tune.shift[i].setStringNum(i);
				m_shift[i].AttachVGData(&((COpenTune *) g_currentPatch->instrument)->tune.shift[i]);
			}
			
			m_type.Invalidate(FALSE);
		}
	}
	else
	{
		// Notify the parent window that a refresh of the panel is needed
		GetParent()->PostMessage(WM_COMMAND, wParam, (long) this);
	}

	return CPanel ::OnCommand(wParam, lParam);
}

CString	CPanelOpenTune::getPresetDir()
{
	return "preset\\Instrument\\OpenTune\\";
}


int CPanelOpenTune::setAllPanelData(char *buffer)
{
	CTune *pOpenTune = &(((COpenTune *) g_currentPatch->instrument)->tune);

	return pOpenTune->setVGData(&buffer);
}


int CPanelOpenTune::getAllPanelData(char *buffer)
{
	CTune *pOpenTune = &(((COpenTune *) g_currentPatch->instrument)->tune);

	return pOpenTune->getVGData(&buffer);
}

//////////////// CPanelDetune ///////////////

BEGIN_MESSAGE_MAP(CPanelDetune, CPanel)
	//{{AFX_MSG_MAP(CPanelDetune)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelDetune::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_PTSHIFT_ONOFF))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_PTSHIFT_ONOFF))
		return -1;

	if (!m_pedalImage.CreateImageControl("", 9, 40, &g_sEffPedShift, 0, this, 0))
		return -1;

	if (!m_detune.CreateControl("DETUNE", CTRL_VGKNOB1, 69, 35, this, 0))
		return -1;

	return 0;
}


void CPanelDetune::AttachVGData(CPatch *patch)
{
	CDetune	*pDetune;

	if (patch)
	{
		pDetune = &(((CStrings12 *) patch->instrument)->detune);

		if (patch->cosmGT.guitarOnOff.getValue())
		{
			m_onOff.AttachVGData(&((CStrings12 *) patch->instrument)->detuneOnOff);
			m_ledOnOff.AttachVGData(&((CStrings12 *) patch->instrument)->detuneOnOff);
		}
		else
		{
			m_onOff.AttachVGData(NULL);
			m_ledOnOff.AttachVGData(NULL);
		}
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}


	if (patch && ((CStrings12 *) patch->instrument)->detuneOnOff.getValue() && patch->cosmGT.guitarOnOff.getValue())
		m_detune.AttachVGData(&pDetune->detune);
	else
		m_detune.AttachVGData(NULL);
}


//////////////// CPanelPDShift ///////////////

BEGIN_MESSAGE_MAP(CPanelPDShift, CPanel)
	//{{AFX_MSG_MAP(CPanelPDShift)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelPDShift::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_PTSHIFT_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_PTSHIFT_ONOFF))
		return -1;

	if (!m_pedalImage.CreateImageControl("", 9, 40, &g_sEffPedShift, 0, this, 0))
		return -1;

	if (!m_pitch.CreateControl("PITCH", CTRL_VGKNOB1, 69, 35, this, 0))
		return -1;

	if (!m_string[0].CreateControl("STRING-1", CTRL_SWITCH1, 10, 100, this, 0))
		return -1;

	if (!m_string[1].CreateControl("STRING-2", CTRL_SWITCH1, 69, 100, this, 0))
		return -1;

	if (!m_string[2].CreateControl("STRING-3", CTRL_SWITCH1, 125, 100, this, 0))
		return -1;

	if (!m_string[3].CreateControl("STRING-4", CTRL_SWITCH1, 10, 156, this, 0))
		return -1;

	if (!m_string[4].CreateControl("STRING-5", CTRL_SWITCH1, 69, 156, this, 0))
		return -1;

	if (!m_string[5].CreateControl("STRING-6", CTRL_SWITCH1, 125, 156, this, 0))
		return -1;


	return 0;
}


void CPanelPDShift::AttachVGData(CPatch *patch)
{
	CShift	*pShift;
	int i;

	if (patch)
	{
		pShift = &(((CPdShift *) patch->instrument)->pdShift);

		if (patch->cosmGT.guitarOnOff.getValue())
		{
			m_onOff.AttachVGData(&((CPdShift *) patch->instrument)->detuneOnOff);
			m_ledOnOff.AttachVGData(&((CPdShift *) patch->instrument)->detuneOnOff);
		}
		else
		{
			m_onOff.AttachVGData(NULL);
			m_ledOnOff.AttachVGData(NULL);
		}
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}


	if (patch && ((CPdShift *) patch->instrument)->detuneOnOff.getValue() && patch->cosmGT.guitarOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_pitch.AttachVGData(&pShift->pitch);

		for (i = 0; i < 6; i++)
			m_string[i].AttachVGData(&pShift->string[i]);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_pitch.AttachVGData(NULL);

		for (i = 0; i < 6; i++)
			m_string[i].AttachVGData(NULL);
	}
}

CString	CPanelPDShift::getPresetDir()
{
	return "preset\\Instrument\\PDShift\\";
}


int CPanelPDShift::setAllPanelData(char *buffer)
{
	CShift	*pShift;

	pShift = &(((CPdShift *) g_currentPatch->instrument)->pdShift);

	return pShift->setVGData(&buffer);
}


int CPanelPDShift::getAllPanelData(char *buffer)
{
	CShift	*pShift;

	pShift = &(((CPdShift *) g_currentPatch->instrument)->pdShift);

	return pShift->getVGData(&buffer);
}

//////////////// CPanelOrgan ///////////////

BEGIN_MESSAGE_MAP(CPanelOrgan, CPanel)
	//{{AFX_MSG_MAP(CPanelOrgan)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelOrgan::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_organImage.CreateImageControl("", 33, 50, &g_organS, 0, this, 0))
		return -1;

	if (!m_feet16.CreateControl("FEET-16", CTRL_VFADERORGAN, 40, 120, this, 0))
		return -1;


	if (!m_feet8.CreateControl("FEET-8", CTRL_VFADERORGAN, 77, 120, this, 0))
		return -1;


	if (!m_feet4.CreateControl("FEET-4", CTRL_VFADERORGAN, 114, 120, this, 0))
		return -1;


	if (!m_sustain.CreateControl("SUSTAIN", CTRL_VGKNOB1, 10, 320, this, 0))
		return -1;

	return 0;
}


void CPanelOrgan::AttachVGData(CPatch *patch)
{
	if (patch->cosmGT.guitarOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_feet4.AttachVGData(&(((COrgan *) patch->instrument)->drawBar.feet4));
		m_feet8.AttachVGData(&(((COrgan *) patch->instrument)->drawBar.feet8));
		m_feet16.AttachVGData(&(((COrgan *) patch->instrument)->drawBar.feet16));
		m_sustain.AttachVGData(&(((COrgan *) patch->instrument)->sustain));
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_feet4.AttachVGData(NULL);
		m_feet8.AttachVGData(NULL);
		m_feet16.AttachVGData(NULL);
		m_sustain.AttachVGData(NULL);
	}
}


CString	CPanelOrgan::getPresetDir()
{
	return "preset\\Instrument\\Organ\\";
}


int CPanelOrgan::setAllPanelData(char *buffer)
{
	COrgan *organ = (COrgan *) g_currentPatch->instrument;

	return organ->drawBar.setVGData(&buffer);
}


int CPanelOrgan::getAllPanelData(char *buffer)
{
	COrgan *organ = (COrgan *) g_currentPatch->instrument;

	return organ->drawBar.getVGData(&buffer);
}


//////////////// CPanelDist ///////////////

BEGIN_MESSAGE_MAP(CPanelDist, CPanel)
	//{{AFX_MSG_MAP(CPanelDist)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelDist::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);


	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_DIST_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_DIST_ONOFF))
		return -1;

	if (!m_pedalImage.CreateImageControl("", 9, 40, &g_effDist, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("MODE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

	if (!m_drive.CreateControl("DRIVE", CTRL_VGKNOB1, 69, 78, this, 0))
			return -1;

	if (!m_highCut.CreateControl("HIGH CUT", CTRL_VGKNOB1, 125, 78, this, 0))
			return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 10, 135, this, 0))
		return -1;

	if (!m_polyBal.CreateControl("POLY BAL", CTRL_VGKNOB1, 69, 135, this, 0))
		return -1;

	if (!m_drvBal.CreateControl("DRV BAL", CTRL_VGKNOB1, 125, 135, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelDist::AttachVGData(CPatch *patch)
{
	CDist *dist;

	if (patch)
	{
		m_onOff.AttachVGData(&(((CPolyDist *) patch->instrument)->distOnOff));
		m_ledOnOff.AttachVGData(&(((CPolyDist *) patch->instrument)->distOnOff));
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && (((CPolyDist *) patch->instrument)->distOnOff).getValue() && patch->cosmGT.guitarOnOff.getValue())
	{
		dist = &((CPolyDist *) patch->instrument)->dist;

		m_preset.AttachVGData(&m_presetData);
		m_drive.AttachVGData(&dist->drive);
		m_drvBal.AttachVGData(&dist->drvBal);
		m_highCut.AttachVGData(&dist->highCut);
		m_level.AttachVGData(&dist->level);
		m_mode.AttachVGData(&dist->mode);
		m_polyBal.AttachVGData(&dist->polyBal);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_drive.AttachVGData(NULL);
		m_drvBal.AttachVGData(NULL);
		m_highCut.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_polyBal.AttachVGData(NULL);
	}
}

CString	CPanelDist::getPresetDir()
{
	return "preset\\Instrument\\PolyDist\\";
}


int CPanelDist::setAllPanelData(char *buffer)
{
	CDist *dist = &((CPolyDist *) g_currentPatch->instrument)->dist;

	return dist->setVGData(&buffer);
}


int CPanelDist::getAllPanelData(char *buffer)
{
	CDist *dist = &((CPolyDist *) g_currentPatch->instrument)->dist;

	return dist->getVGData(&buffer);
}


//////////////// CPanelPolyComp ///////////////

BEGIN_MESSAGE_MAP(CPanelPolyComp, CPanel)
	//{{AFX_MSG_MAP(CPanelPolyComp)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelPolyComp::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);


	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_DIST_ONOFF))
		return -1;

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_DIST_ONOFF))
		return -1;

	if (!m_pedalImage.CreateImageControl("", 9, 40, &g_sEffComp, 0, this, 0))
		return -1;

	if (!m_mode.CreateControl("MODE", CTRL_EDIT2, 65, 44, this, 0))
		return -1;

	if (!m_sustain.CreateControl("SUSTAIN", CTRL_VGKNOB1, 69, 78, this, 0))
			return -1;

	if (!m_threshold.CreateControl("TRESHOLD", CTRL_VGKNOB1, 69, 78, this, 0))
			return -1;

	if (!m_attack.CreateControl("ATTACK", CTRL_VGKNOB1, 125, 78, this, 0))
			return -1;

	if (!m_release.CreateControl("RELEASE", CTRL_VGKNOB1, 125, 78, this, 0))
			return -1;

	if (!m_tone.CreateControl("TONE", CTRL_VGKNOB1, 10, 135, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 69, 135, this, 0))
		return -1;

	if (!m_cmpBal.CreateControl("CMP BAL", CTRL_VGKNOB1, 125, 135, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPolyComp::AttachVGData(CPatch *patch)
{
	CIComp *comp;

	if (patch)
	{
		m_onOff.AttachVGData(&(((CPolyComp *) patch->instrument)->compOnOff));
		m_ledOnOff.AttachVGData(&(((CPolyComp *) patch->instrument)->compOnOff));
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && (((CPolyComp *) patch->instrument)->compOnOff).getValue() && patch->cosmGT.guitarOnOff.getValue())
	{
		comp = &((CPolyComp *) patch->instrument)->comp;

		m_preset.AttachVGData(&m_presetData);
		m_mode.AttachVGData(&comp->mode);
		m_sustain.AttachVGData(&comp->sustain);
		m_attack.AttachVGData(&comp->attack);
		m_tone.AttachVGData(&comp->tone);
		m_level.AttachVGData(&comp->level);
		m_cmpBal.AttachVGData(&comp->cmpBal);
		m_threshold.AttachVGData(&comp->threshold);
		m_release.AttachVGData(&comp->release);

		if (comp->mode.getValue() == POLYCOMP_COMP)
		{
			m_sustain.ShowWindow(SW_SHOWNA);
			m_attack.ShowWindow(SW_SHOWNA);
			m_threshold.ShowWindow(SW_HIDE);
			m_release.ShowWindow(SW_HIDE);
		}
		else
		{
			m_sustain.ShowWindow(SW_HIDE);
			m_attack.ShowWindow(SW_HIDE);
			m_threshold.ShowWindow(SW_SHOWNA);
			m_release.ShowWindow(SW_SHOWNA);
		}
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_mode.AttachVGData(NULL);
		m_sustain.AttachVGData(NULL);
		m_attack.AttachVGData(NULL);
		m_tone.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_cmpBal.AttachVGData(NULL);
		m_threshold.AttachVGData(NULL);
		m_release.AttachVGData(NULL);
	}
}

CString	CPanelPolyComp::getPresetDir()
{
	return "preset\\Instrument\\PolyComp\\";
}


int CPanelPolyComp::setAllPanelData(char *buffer)
{
	CIComp *comp = &((CPolyComp *) g_currentPatch->instrument)->comp;

	return comp->setVGData(&buffer);
}


int CPanelPolyComp::getAllPanelData(char *buffer)
{
	CIComp *comp = &((CPolyComp *) g_currentPatch->instrument)->comp;

	return comp->getVGData(&buffer);
}

//////////////// CPanelPolySG ///////////////

BEGIN_MESSAGE_MAP(CPanelPolySG, CPanel)
	//{{AFX_MSG_MAP(CPanelPolySG)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelPolySG::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_DIST_ONOFF))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_DIST_ONOFF))
		return -1;

	if (!m_pedalImage.CreateImageControl("", 9, 40, &g_sEffVibrato, 0, this, 0))
		return -1;

	if (!m_riseTime.CreateControl("RISE TIME", CTRL_VGKNOB1, 69, 35, this, 0))
			return -1;

	if (!m_sens.CreateControl("SENS", CTRL_VGKNOB1, 125, 35, this, 0))
			return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPolySG::AttachVGData(CPatch *patch)
{
	CSG *sg;

	if (patch)
	{
		m_onOff.AttachVGData(&(((CPolySG *) patch->instrument)->sgOnOff));
		m_ledOnOff.AttachVGData(&(((CPolySG *) patch->instrument)->sgOnOff));
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (patch && (((CPolySG *) patch->instrument)->sgOnOff).getValue() && patch->cosmGT.guitarOnOff.getValue())
	{
		sg = &((CPolySG *) patch->instrument)->sg;

		m_preset.AttachVGData(&m_presetData);
		m_riseTime.AttachVGData(&sg->riseTime);
		m_sens.AttachVGData(&sg->sens);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_riseTime.AttachVGData(NULL);
		m_sens.AttachVGData(NULL);
	}
}


CString	CPanelPolySG::getPresetDir()
{
	return "preset\\Instrument\\PolySG\\";
}


int CPanelPolySG::setAllPanelData(char *buffer)
{
	return  ((CPolySG *) g_currentPatch->instrument)->sg.setVGData(&buffer);
}


int CPanelPolySG::getAllPanelData(char *buffer)
{
	return  ((CPolySG *) g_currentPatch->instrument)->sg.getVGData(&buffer);
}

//////////////// CPanelFilter ///////////////

BEGIN_MESSAGE_MAP(CPanelFilter, CPanel)
	//{{AFX_MSG_MAP(CPanelFilter)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelFilter::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	// Cutoff
	if (!m_cutOff.CreateControl("CUTOFF", CTRL_VGKNOB1, 10, 35, this, 0))
		return -1;

	// Reso
	if (!m_reso.CreateControl("RESO", CTRL_VGKNOB1, 69, 35, this, 0))
		return -1;

	// Touch-S
	if (!m_touchS.CreateControl("TOUCH-S", CTRL_VGKNOB1, 125, 35, this, 0))
		return -1;

	// Decay
	if (!m_decay.CreateControl("DECAY", CTRL_VGKNOB1, 125, 93, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelFilter::AttachVGData(CPatch *patch)
{
	CFilter	*filter;
	
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		switch (patch->cosmGT.guitarType.getValue())
		{
			case COSMGT_BOWED:
				filter = &((CBowed *) patch->instrument)->filter;
				m_decay.ShowWindow(SW_HIDE);
			break;

			case COSMGT_DUAL:
				filter = &((CDual *) patch->instrument)->filter;
				m_decay.ShowWindow(SW_HIDE);
			break;

			case COSMGT_FILTER_BASS:
				filter = &((CFilterBass *) patch->instrument)->filter;
				m_decay.ShowWindow(SW_SHOWNA);
			break;

			case COSMGT_PIPE:
				filter = &((CPipe *) patch->instrument)->filter;
				m_decay.ShowWindow(SW_HIDE);
			break;

			case COSMGT_SOLO:
				filter = &((CSolo *) patch->instrument)->filter;
				m_decay.ShowWindow(SW_HIDE);
			break;

			case COSMGT_PWM:
				filter = &((CPWM *) patch->instrument)->filter;
				m_decay.ShowWindow(SW_HIDE);
			break;

			case COSMGT_BRASS:
				filter = &((CBrass *) patch->instrument)->filter;
				m_decay.ShowWindow(SW_HIDE);
			break;

			default:
				return;
		}
	
		m_preset.AttachVGData(&m_presetData);
		m_cutOff.AttachVGData(&filter->cutOff);
		m_reso.AttachVGData(&filter->reso);
		m_touchS.AttachVGData(&filter->touchS);
		m_decay.AttachVGData(&filter->decay);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_cutOff.AttachVGData(NULL);
		m_reso.AttachVGData(NULL);
		m_touchS.AttachVGData(NULL);
		m_decay.AttachVGData(NULL);

		m_decay.ShowWindow(SW_HIDE);
	}
}


CString	CPanelFilter::getPresetDir()
{
	switch (g_currentPatch->cosmGT.guitarType.getValue())
	{
		case COSMGT_FILTER_BASS:
			return "preset\\Instrument\\filterBass\\";
			break;

		default:
			return "preset\\Instrument\\filter\\";
			break;
	}
	
}


int CPanelFilter::setAllPanelData(char *buffer)
{
	CFilter	*filter;
	
	switch (g_currentPatch->cosmGT.guitarType.getValue())
	{
		case COSMGT_BOWED:
			filter = &((CBowed *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_DUAL:
			filter = &((CDual *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_FILTER_BASS:
			filter = &((CFilterBass *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_PIPE:
			filter = &((CPipe *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_SOLO:
			filter = &((CSolo *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_PWM:
			filter = &((CPWM *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_BRASS:
			filter = &((CBrass *) g_currentPatch->instrument)->filter;
		break;
	}

	return filter->setVGData(&buffer);
}


int CPanelFilter::getAllPanelData(char *buffer)
{
	CFilter	*filter;
	
	switch (g_currentPatch->cosmGT.guitarType.getValue())
	{
		case COSMGT_BOWED:
			filter = &((CBowed *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_DUAL:
			filter = &((CDual *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_FILTER_BASS:
			filter = &((CFilterBass *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_PIPE:
			filter = &((CPipe *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_SOLO:
			filter = &((CSolo *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_PWM:
			filter = &((CPWM *) g_currentPatch->instrument)->filter;
		break;

		case COSMGT_BRASS:
			filter = &((CBrass *) g_currentPatch->instrument)->filter;
		break;
	}

	return filter->getVGData(&buffer);
}


//////////////// CPanelBowed ///////////////

BEGIN_MESSAGE_MAP(CPanelBowed, CPanel)
	//{{AFX_MSG_MAP(CPanelBowed)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelBowed::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_image.CreateImageControl("", 33, 50, &g_violon2, 0, this, 0))
		return -1;

	if (!m_pBend.CreateControl("P-BEND", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;

	if (!m_pBendQ.CreateControl("P-BEND-Q", CTRL_VGKNOB1, 69, 160, this, 0))
		return -1;

	if (!m_sustain.CreateControl("SUSTAIN", CTRL_VGKNOB1, 10, 219, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelBowed::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_pBend.AttachVGData(&((CBowed *) patch->instrument)->pBend.pBend);
		m_pBendQ.AttachVGData(&((CBowed *) patch->instrument)->pBend.pBendQ);
		m_sustain.AttachVGData(&((CBowed *) patch->instrument)->sustain);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_pBend.AttachVGData(NULL);
		m_pBendQ.AttachVGData(NULL);
		m_sustain.AttachVGData(NULL);
	}
}

CString	CPanelBowed::getPresetDir()
{
	return "preset\\Instrument\\PBend\\";
}


int CPanelBowed::setAllPanelData(char *buffer)
{
	int count;

	count = ((CBowed *) g_currentPatch->instrument)->pBend.setVGData(&buffer);
	//count += ((CBowed *) g_currentPatch->instrument)->sustain.setVGData(&buffer);

	return count;
}


int CPanelBowed::getAllPanelData(char *buffer)
{
	int count;

	count = ((CBowed *) g_currentPatch->instrument)->pBend.getVGData(&buffer);
	//count += ((CBowed *) g_currentPatch->instrument)->sustain.getVGData(&buffer);

	return count;
}


//////////////// CPanelDual ///////////////

BEGIN_MESSAGE_MAP(CPanelDual, CPanel)
	//{{AFX_MSG_MAP(CPanelDual)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelDual::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_image.CreateImageControl("", 27, 50, &g_dualS, 0, this, 0))
		return -1;

	if (!m_gldSens.CreateControl("GLD-SENS", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;

	if (!m_gldTime.CreateControl("GLD-TIME", CTRL_VGKNOB1, 69, 160, this, 0))
		return -1;

	if (!m_sustain.CreateControl("SUSTAIN", CTRL_VGKNOB1, 10, 219, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelDual::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_gldSens.AttachVGData(&((CDual *) patch->instrument)->gLide.gldSens);
		m_gldTime.AttachVGData(&((CDual *) patch->instrument)->gLide.gldTime);
		m_sustain.AttachVGData(&((CDual *) patch->instrument)->sustain);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_gldSens.AttachVGData(NULL);
		m_gldTime.AttachVGData(NULL);
		m_sustain.AttachVGData(NULL);
	}
}


CString	CPanelDual::getPresetDir()
{
	return "preset\\Instrument\\GLide\\";
}


int CPanelDual::setAllPanelData(char *buffer)
{
	return  ((CDual *) g_currentPatch->instrument)->gLide.setVGData(&buffer);
}


int CPanelDual::getAllPanelData(char *buffer)
{
	return  ((CDual *) g_currentPatch->instrument)->gLide.getVGData(&buffer);
}


//////////////// CPanelFilterBass ///////////////

BEGIN_MESSAGE_MAP(CPanelFilterBass, CPanel)
	//{{AFX_MSG_MAP(CPanelFilterBass)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelFilterBass::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_image.CreateImageControl("", 43, 50, &g_filterBassS, 0, this, 0))
		return -1;

	if (!m_color.CreateControl("COLOR", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelFilterBass::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_color.AttachVGData(&((CFilterBass *) patch->instrument)->color);
	}
	else
	{
		m_color.AttachVGData(NULL);
	}
}


//////////////// CPanelPipe ///////////////

BEGIN_MESSAGE_MAP(CPanelPipe, CPanel)
	//{{AFX_MSG_MAP(CPanelPipe)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelPipe::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_image.CreateImageControl("", 43, 60, &g_flute2, 0, this, 0))
		return -1;

	if (!m_pBend.CreateControl("P-BEND", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;

	if (!m_pBendQ.CreateControl("P-BEND-Q", CTRL_VGKNOB1, 69, 160, this, 0))
		return -1;

	if (!m_sustain.CreateControl("SUSTAIN", CTRL_VGKNOB1, 10, 219, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPipe::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_pBend.AttachVGData(&((CPipe *) patch->instrument)->pBend.pBend);
		m_pBendQ.AttachVGData(&((CPipe *) patch->instrument)->pBend.pBendQ);
		m_sustain.AttachVGData(&((CPipe *) patch->instrument)->sustain);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_pBend.AttachVGData(NULL);
		m_pBendQ.AttachVGData(NULL);
		m_sustain.AttachVGData(NULL);
	}
}

CString	CPanelPipe::getPresetDir()
{
	return "preset\\Instrument\\PBend\\";
}


int CPanelPipe::setAllPanelData(char *buffer)
{
	return  ((CPipe *) g_currentPatch->instrument)->pBend.setVGData(&buffer);
}


int CPanelPipe::getAllPanelData(char *buffer)
{
	return  ((CPipe *) g_currentPatch->instrument)->pBend.getVGData(&buffer);
}


//////////////// CPanelSolo ///////////////

BEGIN_MESSAGE_MAP(CPanelSolo, CPanel)
	//{{AFX_MSG_MAP(CPanelSolo)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelSolo::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_image.CreateImageControl("", 43, 50, &g_trumpet2, 0, this, 0))
		return -1;

	if (!m_color.CreateControl("COLOR", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;

	if (!m_sustain.CreateControl("SUSTAIN", CTRL_VGKNOB1, 69, 160, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelSolo::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_color.AttachVGData(&((CSolo *) patch->instrument)->color);
		m_sustain.AttachVGData(&((CSolo *) patch->instrument)->sustain);
	}
	else
	{
		m_color.AttachVGData(NULL);
		m_sustain.AttachVGData(NULL);
	}
}


//////////////// CPanelPWM ///////////////

BEGIN_MESSAGE_MAP(CPanelPWM, CPanel)
	//{{AFX_MSG_MAP(CPanelPWM)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelPWM::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_image.CreateImageControl("", 27, 50, &g_ppwmS, 0, this, 0))
		return -1;

	if (!m_depth.CreateControl("DEPTH", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;

	if (!m_rate.CreateControl("RATE", CTRL_VGKNOB1, 69, 160, this, 0))
		return -1;

	if (!m_sustain.CreateControl("SUSTAIN", CTRL_VGKNOB1, 125, 160, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelPWM::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_depth.AttachVGData(&((CPWM *) patch->instrument)->mod.depth);
		m_rate.AttachVGData(&((CPWM *) patch->instrument)->mod.rate);
		m_sustain.AttachVGData(&((CPWM *) patch->instrument)->sustain);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_depth.AttachVGData(NULL);
		m_rate.AttachVGData(NULL);
		m_sustain.AttachVGData(NULL);
	}
}


CString	CPanelPWM::getPresetDir()
{
	return "preset\\Instrument\\mod\\";
}


int CPanelPWM::setAllPanelData(char *buffer)
{
	return  ((CPWM *) g_currentPatch->instrument)->mod.setVGData(&buffer);
}


int CPanelPWM::getAllPanelData(char *buffer)
{
	return  ((CPWM *) g_currentPatch->instrument)->mod.getVGData(&buffer);
}
//////////////// CPanelCrystal ///////////////

BEGIN_MESSAGE_MAP(CPanelCrystal, CPanel)
	//{{AFX_MSG_MAP(CPanelCrystal)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelCrystal::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_preset.CreateControl("ON / OFF", 5, 130, 8, this, IDC_PRESET))
		return -1;

	if (!m_image.CreateImageControl("", 63, 50, &g_crystal2, 0, this, 0))
		return -1;

	if (!m_length.CreateControl("LENGTH", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;

	if (!m_modTune.CreateControl("MOD-TUNE", CTRL_VGKNOB1, 69, 160, this, 0))
		return -1;

	if (!m_level.CreateControl("LEVEL", CTRL_VGKNOB1, 125, 160, this, 0))
		return -1;

	if (!m_modeDep.CreateControl("MOD-DEP", CTRL_VGKNOB1, 69, 219, this, 0))
		return -1;

	if (!m_bodyLev.CreateControl("BODY LEV", CTRL_VGKNOB1, 10, 275, this, 0))
		return -1;

	if (!m_sustain.CreateControl("SUSTAIN", CTRL_VGKNOB1, 69, 275, this, 0))
		return -1;

	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelCrystal::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_preset.AttachVGData(&m_presetData);
		m_length.AttachVGData(&((CCrystal *) patch->instrument)->mod.length);
		m_level.AttachVGData(&((CCrystal *) patch->instrument)->mod.level);
		m_modeDep.AttachVGData(&((CCrystal *) patch->instrument)->mod.modeDep);
		m_modTune.AttachVGData(&((CCrystal *) patch->instrument)->mod.modTune);
		m_bodyLev.AttachVGData(&((CCrystal *) patch->instrument)->bodyLevel);
		m_sustain.AttachVGData(&((CCrystal *) patch->instrument)->sustain);
	}
	else
	{
		m_preset.AttachVGData(NULL);
		m_length.AttachVGData(NULL);
		m_level.AttachVGData(NULL);
		m_modeDep.AttachVGData(NULL);
		m_modTune.AttachVGData(NULL);
		m_bodyLev.AttachVGData(NULL);
		m_sustain.AttachVGData(NULL);
	}
}

CString	CPanelCrystal::getPresetDir()
{
	return "preset\\Instrument\\Attack\\";
}


int CPanelCrystal::setAllPanelData(char *buffer)
{
	return  ((CCrystal *) g_currentPatch->instrument)->mod.setVGData(&buffer);
}


int CPanelCrystal::getAllPanelData(char *buffer)
{
	return  ((CCrystal *) g_currentPatch->instrument)->mod.getVGData(&buffer);
}


//////////////// CPanelBrass ///////////////

BEGIN_MESSAGE_MAP(CPanelBrass, CPanel)
	//{{AFX_MSG_MAP(CPanelBrass)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelBrass::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_image.CreateImageControl("", 33, 50, &g_brass, 0, this, 0))
		return -1;

	if (!m_sustain.CreateControl("SUSTAIN", CTRL_VGKNOB1, 10, 160, this, 0))
		return -1;


	AttachVGData(g_currentPatch);

	return 0;
}


void CPanelBrass::AttachVGData(CPatch *patch)
{
	if (patch && patch->cosmGT.guitarOnOff.getValue())
	{
		m_sustain.AttachVGData(&((CBrass *) patch->instrument)->sustain);
	}
	else
	{
		m_sustain.AttachVGData(NULL);
	}
}



//////////////// CPanelContrast ///////////////

BEGIN_MESSAGE_MAP(CPanelContrast, CPanel)
	//{{AFX_MSG_MAP(CPanelContrast)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelContrast::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_image.CreateImageControl("", 75, 45, &g_lcd, 0, this, 0))
		return -1;

	if (!m_contrast.CreateControl("CONTRAST", CTRL_VGKNOB1, 20, 45, this, 0))
		return -1;


	AttachVGData(g_currentSystem);

	return 0;
}


void CPanelContrast::AttachVGData(CSystem *system)
{
	if (system)
		m_contrast.AttachVGData(&system->display);
	else
		m_contrast.AttachVGData(NULL);
}




//////////////// CPanelGkFunction ///////////////

BEGIN_MESSAGE_MAP(CPanelGkFunction, CPanel)
	//{{AFX_MSG_MAP(CPanelGkFunction)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelGkFunction::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_image.CreateImageControl("", 30, 58, &g_gkFunc, 0, this, 0))
		return -1;

	if (!m_downS1S2.CreateControl("S1  /  S2", CTRL_EDIT1, 10, 44, this, 0))
		return -1;

	if (!m_synthVol.CreateControl("S. VOL", CTRL_EDIT1, 10, 139, this, 0))
		return -1;

	AttachVGData(g_currentSystem);

	return 0;
}


void CPanelGkFunction::AttachVGData(CSystem *system)
{
	if (system)
	{
		m_downS1S2.AttachVGData(&system->gkFunc.downS1S2);
		m_synthVol.AttachVGData(&system->gkFunc.synthVol);
	}
	else
	{
		m_downS1S2.AttachVGData(NULL);
		m_synthVol.AttachVGData(NULL);
	}
}



//////////////// CPanelGlobal ///////////////

BEGIN_MESSAGE_MAP(CPanelGlobal, CPanel)
	//{{AFX_MSG_MAP(CPanelGlobal)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelGlobal::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_onOff.CreateControl("ON / OFF", 1, 15, 8, this, IDC_GLOBAL_ONOFF))
		return -1;

	if (!m_ledOnOff.CreateControl("ON / OFF", 2, 150, 8, this, IDC_GLOBAL_ONOFF))
		return -1;

	if (!m_lowG.CreateControl("LOW G", CTRL_VGKNOB1, 10, 35, this, 0))
		return -1;

	if (!m_highG.CreateControl("HIGH G", CTRL_VGKNOB1, 69, 35, this, 0))
		return -1;

	if (!m_NS.CreateControl("NS", CTRL_VGKNOB1, 125, 35, this, 0))
		return -1;

	if (!m_reverb.CreateControl("REVERB", CTRL_VGKNOB1, 10, 93, this, 0))
		return -1;

	AttachVGData(g_currentSystem);

	return 0;
}


void CPanelGlobal::AttachVGData(CSystem *system)
{
	if (system)
	{
		m_onOff.AttachVGData(&system->global.OnOff);
		m_ledOnOff.AttachVGData(&system->global.OnOff);
	}
	else
	{
		m_onOff.AttachVGData(NULL);
		m_ledOnOff.AttachVGData(NULL);
	}

	if (system	&& system->global.OnOff.getValue())
	{
		m_lowG.AttachVGData(&system->global.lowG);
		m_highG.AttachVGData(&system->global.highG);
		m_NS.AttachVGData(&system->global.NS);
		m_reverb.AttachVGData(&system->global.reverb);
	}
	else
	{
		m_lowG.AttachVGData(NULL);
		m_highG.AttachVGData(NULL);
		m_NS.AttachVGData(NULL);
		m_reverb.AttachVGData(NULL);

	}
}


//////////////// CPanelTuner ///////////////

BEGIN_MESSAGE_MAP(CPanelTuner, CPanel)
	//{{AFX_MSG_MAP(CPanelTuner)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelTuner::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_image.CreateImageControl("", 104, 55, &g_tuner, 0, this, 0))
		return -1;

	if (!m_pitch.CreateControl("PITCH", CTRL_VGKNOB1, 10, 45, this, 0))
		return -1;

	if (!m_mute.CreateControl("MUTE", CTRL_SWITCH1, 58, 45, this, 0))
		return -1;

	AttachVGData(g_currentSystem);

	return 0;
}


void CPanelTuner::AttachVGData(CSystem *system)
{
	if (system)
	{
		m_pitch.AttachVGData(&system->tuner.pitch);
		m_mute.AttachVGData(&system->tuner.mute);
	}
	else
	{
		m_pitch.AttachVGData(NULL);
		m_mute.AttachVGData(NULL);
	}
}



//////////////// CPanelDial ///////////////

BEGIN_MESSAGE_MAP(CPanelDial, CPanel)
	//{{AFX_MSG_MAP(CPanelDial)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelDial::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_image.CreateImageControl("", 60, 80, &g_dial, 0, this, 0))
		return -1;

	if (!m_function.CreateControl("FUNC.", CTRL_EDIT1, 10, 44, this, 0))
		return -1;

	AttachVGData(g_currentSystem);

	return 0;
}


void CPanelDial::AttachVGData(CSystem *system)
{
	if (system)
		m_function.AttachVGData(&system->dial);
	else
		m_function.AttachVGData(NULL);
}



//////////////// CPanelOutputSelect ///////////////

BEGIN_MESSAGE_MAP(CPanelOutputSelect, CPanel)
	//{{AFX_MSG_MAP(CPanelOutputSelect)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelOutputSelect::OnCreate(LPCREATESTRUCT lpcs)
{
	CPanel::OnCreate(lpcs);

	if (!m_outputImage.CreateImageControl("OUTPUT", 15, 70, &g_outputSelect, 5, this, IDC_OUTPUT_SELECT))
		return -1;

	if (!m_output.CreateControl("OUTPUT", CTRL_EDIT1, 10, 44, this, 0))
		return -1;

	AttachVGData(g_currentSystem);

	return 0;
}


void CPanelOutputSelect::AttachVGData(CSystem *system)
{
	if (system)
	{
		m_output.AttachVGData(&system->outputSelect);
		m_outputImage.AttachVGData(&system->outputSelect);
	}
	else
	{
		m_output.AttachVGData(NULL);
		m_outputImage.AttachVGData(NULL);
	}
}




//////////////// CPanelDriverSetting ///////////////

BEGIN_MESSAGE_MAP(CPanelDriverSetting, CPanel)
	//{{AFX_MSG_MAP(CPanelDriverSetting)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPanelDriverSetting::OnCreate(LPCREATESTRUCT lpcs)
{
	int i;
	char caption[50];

	CPanel::OnCreate(lpcs);

	if (!m_gkConnection.CreateControl("CONNEC.", CTRL_EDIT1, 10, 40, this, 0))
		return -1;

	if (!m_setting.CreateControl("SETTING", CTRL_EDIT1, 10, 60, this, 0))
		return -1;

	if (!m_outputImage.CreateImageControl("", 60, 85, &g_gk2ab, 0, this, 0))
		return -1;

	if (!m_misc.CreateControl("", 130, this, 0))
		return -1;

	if (!m_type.CreateControl("TYPE", CTRL_EDIT1, 10, 150, this, 0))
		return -1;

	if (!m_direction.CreateControl("DIRECTION", CTRL_SWITCH1, 10, 185, this, 0))
		return -1;

	if (!m_gtPuPhase.CreateControl("PU PHASE", CTRL_SWITCH1, 69, 185, this, 0))
		return -1;

	if (!m_s1S2Pos.CreateControl("S1 / S2 POS", CTRL_SWITCH1, 125, 185, this, 0))
		return -1;

	if (!m_scale.CreateControl("SCALE", CTRL_VGKNOB1, 10, 244, this, 0))
			return -1;

	if (!m_puBridgeSec.CreateControl("PICKUP <-> BRIDGE", 300, this, 0))
		return -1;

	for (i = 0; i < 6; i++)
	{
		sprintf(caption, "ST-%d", 6 - i);

		if (!m_puBridge[5 - i].CreateControl(caption, CTRL_VGKNOB2, 10 + i * 27, 327, this, 0))
			return -1;
	}


	if (!m_sensitivitySec.CreateControl("SENSITIVITY", 390, this, 0))
		return -1;

	for (i = 0; i < 6; i++)
	{
		sprintf(caption, "ST-%d", 6 - i);

		if (!m_sensitivity[5 - i].CreateControl(caption, CTRL_VGKNOB2, 10 + i * 27, 418, this, 0))
			return -1;
	}

	AttachVGData(g_currentSystem);

	return 0;
}


void CPanelDriverSetting::AttachVGData(CSystem *system)
{
	int i;

	if (system)
	{
		m_gkConnection.AttachVGData(&system->driver.settings[system->driver.setting.getValue()].gkConnect);
		m_setting.AttachVGData(&system->driver.setting);
		m_type.AttachVGData(&system->driver.settings[system->driver.setting.getValue()].type);
		m_direction.AttachVGData(&system->driver.settings[system->driver.setting.getValue()].direction);
		m_gtPuPhase.AttachVGData(&system->driver.settings[system->driver.setting.getValue()].GtPuPhase);
		m_s1S2Pos.AttachVGData(&system->driver.settings[system->driver.setting.getValue()].S1S2Pos);
		m_scale.AttachVGData(&system->driver.settings[system->driver.setting.getValue()].scale);

		for (i = 0; i < 6; i++)
			m_sensitivity[i].AttachVGData(&system->driver.settings[system->driver.setting.getValue()].sensitivity[i]);

		for (i = 0; i < 6; i++)
			m_puBridge[i].AttachVGData(&system->driver.settings[system->driver.setting.getValue()].PUBrige[i]);
	}
	else
	{
		m_gkConnection.AttachVGData(NULL);
		m_setting.AttachVGData(NULL);
		m_type.AttachVGData(NULL);
		m_direction.AttachVGData(NULL);
		m_gtPuPhase.AttachVGData(NULL);
		m_s1S2Pos.AttachVGData(NULL);
		m_scale.AttachVGData(NULL);

		for (i = 0; i < 6; i++)
			m_sensitivity[i].AttachVGData(NULL);

		for (i = 0; i < 6; i++)
			m_puBridge[i].AttachVGData(NULL);
	}
}

void CPanel::OnKillFocus(CWnd* pNewWnd) 
{
}
