// ChainWnd.cpp : implementation of the CChainWnd class
//

#include <stdio.h>
#include <io.h>
#include <time.h>
#include "stdafx.h"
#include "VG-88.h"
#include "controls.h"
#include "VEditor.h"
#include "MainFrm.h"
#include "tools.h"
#include "ChainWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CChainWnd

CChainWnd::CChainWnd()
{
	m_panelEdit = NULL;
	m_bTracking = FALSE;
	m_moveFrom = -1;
	m_moveTo = -1;
}


CChainWnd::~CChainWnd()
{
}


BEGIN_MESSAGE_MAP(CChainWnd,CWnd )
	//{{AFX_MSG_MAP(CChainWnd)
	ON_WM_CREATE ()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChainWnd message handlers

BOOL CChainWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	//cs.dwExStyle |= WS_EX_CLIENTEDGE;
	//cs.style &= ~WS_BORDER;

	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS, 
		AfxGetApp()->LoadCursor(IDC_CURSOR), HBRUSH(COLOR_APPWORKSPACE + 1) /*HBRUSH(COLOR_WINDOW+1)*/, NULL);

	return TRUE;
}


int CChainWnd::OnCreate (LPCREATESTRUCT lpcs)
{
	if (!m_compareButtonOnOff.CreateControl("OnOff", 3, 690, 57, this, IDC_COMPARE))
		return -1;

	if (!m_compareLedOnOff.CreateControl("OnOff", 2, 720, 60, this, IDC_COMPARE))
		return -1;

	m_compareOnOffData.m_needSaving = FALSE;
	m_compareOnOffData.setValue(0);
	m_compareButtonOnOff.AttachVGData(&m_compareOnOffData);
	m_compareLedOnOff.AttachVGData(&m_compareOnOffData);

	if (!m_AmpOnOff.CreateControl("OnOff", 3, 410, 57, this, IDC_PANEL_AMP))
		return -1;

	if (!m_ledOnOff.CreateControl("OnOff", 2, 440, 60, this, IDC_PANEL_AMP))
		return -1;

	m_AmpOnOffData.m_needSaving = FALSE;
	m_AmpOnOffData.setValue(1);
	
	m_AmpOnOff.AttachVGData(&m_AmpOnOffData);
	m_ledOnOff.AttachVGData(&m_AmpOnOffData);


	if (!m_effectButtonOnOff.CreateControl("OnOff", 3, 495, 57, this, IDC_PANEL_EFFECTS))
		return -1;

	if (!m_effectsLedOnOff.CreateControl("OnOff", 2, 525, 60, this, IDC_PANEL_EFFECTS))
		return -1;

	m_effectsOnOffData.m_needSaving = FALSE;
	m_effectsOnOffData.setValue(0);

	m_effectButtonOnOff.AttachVGData(&m_effectsOnOffData);
	m_effectsLedOnOff.AttachVGData(&m_effectsOnOffData);

	if (!m_assignButtonOnOff.CreateControl("OnOff", 3, 580, 57, this, IDC_PANEL_ASSIGN))
		return -1;

	if (!m_assignLedOnOff.CreateControl("OnOff", 2, 610, 60, this, IDC_PANEL_ASSIGN))
		return -1;

	m_assignOnOffData.m_needSaving = FALSE;
	m_assignOnOffData.setValue(0);

	m_assignButtonOnOff.AttachVGData(&m_assignOnOffData);
	m_assignLedOnOff.AttachVGData(&m_assignOnOffData);


	if (!m_sendMidiButtonOnOff.CreateControl("OnOff", 3, 300, 57, this, IDC_SEND_MIDI))
		return -1;

	if (!m_assignMidiLedOnOff.CreateControl("OnOff", 2, 325, 60, this, IDC_SEND_MIDI))
		return -1;

	if (!m_assignMidiLed.CreateControl("OnOff", 4, 340, 60, this, IDC_SEND_MIDI))
		return -1;

	m_sendMidiOnOffData.m_needSaving = FALSE;
	m_sendMidiData.m_needSaving = FALSE;
	m_sendMidiOnOffData.setValue(1);
	m_sendMidiData.setValue(0);

	m_sendMidiButtonOnOff.AttachVGData(&m_sendMidiOnOffData);
	m_assignMidiLedOnOff.AttachVGData(&m_sendMidiOnOffData);
	m_assignMidiLed.AttachVGData(&m_sendMidiData);

	if (!m_preset.CreateControl("ON / OFF", 5, 770, 60, this, IDC_PRESET))
		return -1;

	return 0;
}


void CChainWnd::OnPaint() 
{
	CPaintDC dc(this);	// device context for painting
	CDC dcTemp;
	CBitmap	bitmpap;
	CBitmap *pBitmapOld;

	// All painting are done on the memory device context to avoid flicker
	dcTemp.CreateCompatibleDC (&dc);
	dcTemp.SetMapMode (dc.GetMapMode());
	bitmpap.CreateCompatibleBitmap(&dc, 900, 313);
	pBitmapOld = dcTemp.SelectObject(&bitmpap);

	PaintChainWnd(&dcTemp);

	// Once all painting are done, copy the result to the display
	dc.BitBlt (0, 0, 900, 313, &dcTemp, 0, 0, SRCCOPY);

	dcTemp.SelectObject(pBitmapOld);
}


void CChainWnd::OnPatchChange() 
{
	Invalidate(FALSE);

	if (g_currentPatch)
		m_preset.AttachVGData(&m_presetData);
	else
		m_preset.AttachVGData(NULL);
}


void CChainWnd::PaintChainWnd(CDC *dc) 
{
	g_chain.Draw(dc, 0, 0);
	g_chainSkin.Draw(dc, 0, 82);

	PaintLCD(dc);
	PaintChain(dc);
	/*m_AmpOnOff.Invalidate(FALSE);
	m_ledOnOff.Invalidate(FALSE);
	m_effectButtonOnOff.Invalidate(FALSE);
	m_effectsLedOnOff.Invalidate(FALSE);
	m_assignButtonOnOff.Invalidate(FALSE);
	m_assignLedOnOff.Invalidate(FALSE);*/
}


void CChainWnd::OnSize(UINT nType, int cx, int cy)
{
	//CClientDC dc(this);

	//PaintChainWnd(&dc);

	// Resize the TreeCtrl
	//m_libraryTree.SetWindowPos(NULL, 0, 0, 155, cy - 53, SWP_NOMOVE | SWP_NOOWNERZORDER);
}



void CChainWnd::PaintLCD(CDC *pDc)
{
	CDC dcMem;
	CBitmap* pOldBitmap;
	BITMAP bm;
	char name[32];
	char bank1;
	char bank2;
	char patch;
	int i, x, y;
	CFont *pOldfont;
	CString libName;

	if (!g_currentPatch)
		return;

	pDc->SetBkMode(TRANSPARENT);
	pDc->SetTextColor(RGB(216, 247, 45));
	pOldfont = pDc->SelectObject(&g_font4);
	pDc->DrawText(g_currentLibrary->GetLibraryName(), &CRect(20, 22, 160, 34), DT_LEFT);	

	if (g_currentPatch && g_currentPatch->modified)
	{
		pDc->SetTextColor(RGB(225, 10, 10));
		pDc->DrawText("Modified", &CRect(236, 19, 364, 31), DT_LEFT);

		if (m_compareOnOffData.getValue())
		{
			pDc->DrawText("Compare", &CRect(180, 19, 308, 31), DT_LEFT);
		}
	}

	g_currentPatch->assignNC.name.getString(name);

	dcMem.CreateCompatibleDC (pDc);
	dcMem.SetMapMode (pDc->GetMapMode ());

	pOldBitmap = dcMem.SelectObject (&g_vg88Font);
	g_vg88Font.GetObject (sizeof (BITMAP), &bm);


	for (i = 0; i < 8; i++)
	{
		x = (name[i] - ((name[i] / 16) * 16)) * 19;
		y = (name[i] / 16) * 27;

		pDc->BitBlt (14 + i * 19, 40, 19, 27, &dcMem, x, y, SRCCOPY);

	}

	i = g_currentPatchNumber + g_currentLibrary->firstPatchNumber + 1;

	dcMem.SelectObject (&g_digit);

	patch = i % 4;

	if (patch == 0)
	{
		patch = 4;
		bank1 = ((i / 4)) / 10;
		bank2 = ((i / 4)) % 10;
	}
	else
	{
		bank1 = ((i / 4) + 1) / 10;
		bank2 = ((i / 4) + 1) % 10;
	}

	if(bank1 > 0)
		pDc->BitBlt (176, 37, 25, 34, &dcMem, 25 * bank1 , 0, SRCCOPY);

	pDc->BitBlt (176 + 25 , 37, 25, 34, &dcMem, 25 * bank2 , 0, SRCCOPY);
	pDc->BitBlt (176 + (25 * 2), 37, 25, 34, &dcMem, 25 * 10 , 0, SRCCOPY);
	pDc->BitBlt (176 + (25 * 3), 37, 25, 34, &dcMem, 25 * patch , 0, SRCCOPY);


	dcMem.SelectObject (pOldBitmap);
	pDc->SelectObject(pOldfont);
}



void CChainWnd::PaintChain(CDC *pDc)
{
	CDC dcMem;
	CMaskedBitmap *bitmap;
	int guitarType;
	int pos, i, j, posMix, offset, posy, height;
		
	if (!g_currentPatch)
		return;

	pos = 146;

	// Draw the pickup at the beginning of the chain
	g_pickup.Draw(pDc, pos, 147);
	g_pickup.DrawTransparent(pDc, pos, 147, RGB(255, 255, 255));

	// Draw the cable
	pos += 20;

	if (g_currentPatch->assignNC.chainMix.getValue() == 0)
	{
		if (!g_currentPatch->cosmGT.guitarOnOff.getValue())
			bitmap = &g_cable;
		else
			bitmap = &g_cableInter;

		posMix = pos;
	}
	else
		bitmap = &g_cable;

	//bitmap->Draw(pDc, pos , 159);
	bitmap->DrawTransparent(pDc, pos , 159, RGB(255, 255, 255));

	pos += 15;
	offset = 0;

	for (i = 0; i < 10; i++)
	{
		bitmap = NULL;
		posy = 130;
		height = 90;

		switch(g_currentPatch->assignNC.chain[i].getValue())
		{ 
			case 0:	// COMP
				if (g_currentPatch->compOnOff.getValue())
				{
					bitmap = &g_comp[g_currentPatch->comp.compType.getValue()];
					offset = 47;
				}

				break;

			case 1:	// WAH
				if (g_currentPatch->wahOnOff.getValue())
				{
					bitmap = &g_wah[g_currentPatch->wah.wahType.getValue()];
					
					if (g_currentPatch->wah.wahType.getValue() == 0)
						offset = 42;
					else
						offset = 47;
				}

				break;
				
			case  2:	// AMP
				if (g_currentPatch->cosmAmp.ampOnOff.getValue())
				{
					bitmap = &g_amp[g_currentPatch->cosmAmp.ampType.getValue()];
					offset = 130;
					posy = 100;
					height = 129;
				}

				break;
					
			case  3:	// EQ
				if (g_currentPatch->eqOnOff.getValue())
				{
					bitmap = &g_eq;
					offset = 47;
				}

				break;
					
			case  4:	// FV
				if (g_currentPatch->assignNC.expOnOff.getValue())
				{
					bitmap = &g_fv;
					offset = 42;
				}

				break;
				
			case  5:	// NS
				if (g_currentPatch->nsOnOff.getValue())
				{
					bitmap = &g_ns;
					offset = 47;
				}
				break;
					
			case  6:	// MOD
				if (g_currentPatch->modOnOff.getValue())
				{
					bitmap = &g_mod[g_currentPatch->mod.modeType.getValue()];
					offset = 47;
				}

				break;
					
			case  7:	// DLY
				if (g_currentPatch->delayOnOff.getValue())
				{
					bitmap = &g_delay;
					offset = 47;
				}
				break;
					
			case  8:	// CHO
				if (g_currentPatch->chorusOnOff.getValue())
				{
					bitmap = &g_chorus;
					offset = 47;
				}

				break;
				
			case  9:	// REV
				if (g_currentPatch->reverbOnOff.getValue())
				{
					bitmap = &g_reverb;
					offset = 47;
				}

				break;
		}


		if (bitmap)
		{
			//bitmap->Draw(pDc, pos, posy);
			bitmap->DrawTransparent(pDc, pos, posy, RGB(255, 255, 255));

			m_pedalPos[i].left = pos - 3;
			m_pedalPos[i].right = pos + offset + 3;
			m_pedalPos[i].top = posy - 3;
			m_pedalPos[i].bottom = posy + height + 3;

			pos += offset;

			if (g_currentPatch->assignNC.chainMix.getValue() == i + 1)
			{
				bitmap = &g_cableInter;
				posMix = pos;
			}
			else
				bitmap = &g_cable;

			if (!g_currentPatch->cosmGT.guitarOnOff.getValue())
				bitmap = &g_cable;

			//bitmap->Draw(pDc, pos, 159);
			bitmap->DrawTransparent(pDc, pos , 159, RGB(255, 255, 255));
			
			pos += 15;
		}
		else
		{
			if (g_currentPatch->assignNC.chainMix.getValue() == i + 1)
			{
				bitmap = &g_cableInter;
				posMix = pos - 15;

				if (!g_currentPatch->cosmGT.guitarOnOff.getValue())
					bitmap = &g_cable;

				//bitmap->Draw(pDc, pos - 15, 159);
				bitmap->DrawTransparent(pDc, pos - 15, 159, RGB(255, 255, 255));
			}
		}
	}


	m_CosmGMix.left = posMix;
	m_CosmGMix.right = posMix + 16;
	m_CosmGMix.top = 154;
	m_CosmGMix.bottom = 178;

	// Draw indicators for drag and drop
	if (m_moveTo != -1)
	{
		if (m_moveFrom < m_moveTo)
			g_down.DrawTransparent(pDc, m_pedalPos[m_moveTo].right - 3, 100, RGB(255, 255, 255));
		else
			g_down.DrawTransparent(pDc, m_pedalPos[m_moveTo].left + 3 - 15, 100, RGB(255, 255, 255));
	}

	if (m_moveFrom != -1 && m_moveFrom != -2)
		//g_up.Draw(pDc, m_pedalPos[m_moveFrom].left + ((m_pedalPos[m_moveFrom].right - m_pedalPos[m_moveFrom].left) / 2) - 6, 240);
		g_up.DrawTransparent(pDc, m_pedalPos[m_moveFrom].left + ((m_pedalPos[m_moveFrom].right - m_pedalPos[m_moveFrom].left) / 2) - 6, 240, RGB(255, 255, 255));

	// If the Cosm guitar is OFF don't draw it
	if (!g_currentPatch->cosmGT.guitarOnOff.getValue())
		return;

	for (j = 56; j < posMix - 15; j += 15)
		//g_cable.Draw(pDc, j , 157 + 14 + (3 * 20));
		  g_cable.DrawTransparent(pDc, j , 157 + 14 + (3 * 20), RGB(255, 255, 255));

	//g_cable.Draw(pDc, posMix - 15 , 157 + 14 + (3 * 20));
	g_cable.DrawTransparent(pDc, posMix - 15 , 157 + 14 + (3 * 20), RGB(255, 255, 255));

	for (i = 0; i < 3; i++)
		//g_cable2.Draw(pDc, posMix , 159 + 14 + (i * 20));
		g_cable2.DrawTransparent(pDc, posMix , 159 + 14 + (i * 20), RGB(255, 255, 255));
	
	g_cableCorner.DrawTransparent(pDc, posMix , 159 + 14 + (i * 20), RGB(255, 255, 255));

	// Draw the instrument

	guitarType = g_currentPatch->cosmGT.guitarType.getValue();
	bitmap= NULL;

	switch(guitarType)
	{
		case COSMGT_VARI_GT:
		case COSMGT_OPEN_TUNE:
		case COSMGT_12STRINGS:
		case COSMGT_PD_SHIFT:
		case COSMGT_POLY_DIST:
		case COSMGT_POLY_COMP:
		case COSMGT_POLY_OCT:
		case COSMGT_POLY_SG:
			CVariGuitar *variGuitar;

			variGuitar = (CVariGuitar *) g_currentPatch->instrument;
			bitmap = (CMaskedBitmap *) &g_guitar[variGuitar->pickup.model.getValue()];

			break;

		case COSMGT_ACOUSTIC:
			CAcoustic *acoustic;

			acoustic = (CAcoustic *) g_currentPatch->instrument;

			if(acoustic->pickup.type.getValue() == 0)
				bitmap = (CMaskedBitmap *) &g_acoustic;
			else
				bitmap = (CMaskedBitmap *) &g_acousticMic;

				break;

		case COSMGT_NYLON_STRINGS:
			bitmap = (CMaskedBitmap *) &g_nylon;

			break;

		case COSMGT_NYLONII_STRINGS:
			bitmap = (CMaskedBitmap *) &g_nylonii;

			break;

		case COSMGT_SITAR:
			bitmap = (CMaskedBitmap *) &g_sitar;

			break;

		case COSMGT_BOWED:
			bitmap =  (CMaskedBitmap *) &g_bowed;
			break;

		case COSMGT_DUAL:
			bitmap =  (CMaskedBitmap *) &g_dualB;
			break;

		case COSMGT_FILTER_BASS:
			bitmap = (CMaskedBitmap *) &g_filterBassB;
			break;

		case COSMGT_PIPE:
			bitmap = (CMaskedBitmap *) &g_pipe;
			break;

		case COSMGT_SOLO:
			bitmap = (CMaskedBitmap *) &g_solo;
			break;

		case COSMGT_PWM:
			bitmap = (CMaskedBitmap *) &g_ppwmB;
			break;

		case COSMGT_CRYSTAL:
			bitmap = (CMaskedBitmap *) &g_crystal;
			break;

		case COSMGT_ORGAN:
			bitmap = (CMaskedBitmap *) &g_organ;
			break;

		case COSMGT_BRASS:
			bitmap = (CMaskedBitmap *) &g_brassB;
			break;

		case COSMGT_WAVE_SYNTH:
			if (((CWave *) g_currentPatch->instrument)->shape.getValue() == WAVE_SAW)
				bitmap = (CMaskedBitmap *) &g_waveSaw;
			else
				bitmap = (CMaskedBitmap *) &g_waveSquare;
			break;
	}		

	if (bitmap)
		bitmap->DrawTransparent (pDc, 16, 100, RGB (255, 255, 255));

	bitmap = NULL;
	CVariGuitar *variGuitar;
	COpenTune	*openTune;
	CStrings12	*strings12;
	CPdShift	*pdShift;
	CPolyDist	*polyDist;
	CPolyComp	*polyComp;
	CPolyOct	*polyOct;
	CPolySG		*polySG;

	switch(guitarType)
	{
		case 0:
			variGuitar = (CVariGuitar *) g_currentPatch->instrument;

			if (variGuitar->ptShiftOnOff.getValue())
				bitmap = &g_mod[1];
			break;

		case 3:
			openTune = (COpenTune *) g_currentPatch->instrument;

			if (openTune->openTuneOnOff.getValue())
				bitmap = &g_tune;
			break;

		case 4:
			strings12 = (CStrings12 *) g_currentPatch->instrument;

			if (strings12->detuneOnOff.getValue())
				bitmap = &g_detune;
			break;

		case 5:
			pdShift = (CPdShift *) g_currentPatch->instrument;

			if (pdShift->detuneOnOff.getValue())
				bitmap = &g_mod[8];
			break;

	
		case 6:
			polyDist = (CPolyDist *) g_currentPatch->instrument;

			if (polyDist->distOnOff.getValue())
				bitmap = &g_polyDist[polyDist->dist.mode.getValue()];
			break;

		case 7:
			polyComp = (CPolyComp *) g_currentPatch->instrument;

			if (polyComp->compOnOff.getValue())
				bitmap = &g_comp[polyComp->comp.mode.getValue()];
			break;

		case 8:
			polyOct = (CPolyOct *) g_currentPatch->instrument;

			if (polyOct->ocataveOnOff.getValue())
				bitmap = &g_polyOctave;
			break;

		case 9:
			polySG = (CPolySG *) g_currentPatch->instrument;

			if (polySG->sgOnOff.getValue())
				bitmap = &g_polySlowGear;
			break;
				
	}

	if (bitmap)
		//bitmap->Draw(pDc, 106, 201);
		bitmap->DrawTransparent(pDc, 106, 201, RGB(255, 255, 255));
}


BOOL CChainWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{

	switch (wParam)
	{
		case IDC_PANEL_AMP:
			m_AmpOnOffData.setValue(1);
			m_effectsOnOffData.setValue(0);
			m_assignOnOffData.setValue(0);
			((CMainFrame *) AfxGetMainWnd())->m_patchWndVisible = 1;
			break;

		case IDC_PANEL_EFFECTS:
			m_AmpOnOffData.setValue(0);
			m_effectsOnOffData.setValue(1);
			m_assignOnOffData.setValue(0);
			((CMainFrame *) AfxGetMainWnd())->m_patchWndVisible = 1;
			break;

		case IDC_PANEL_ASSIGN:
			m_AmpOnOffData.setValue(0);
			m_effectsOnOffData.setValue(0);
			m_assignOnOffData.setValue(1);
			((CMainFrame *) AfxGetMainWnd())->m_patchWndVisible = 1;
			break;

		case IDC_SEND_MIDI:
		case IDC_COMPARE:
			((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();
			break;

	/*	case IDC_POPUP_CANCEL:
			if (m_panelEdit)
			{
				delete m_panelEdit;
				m_panelEdit = NULL;
			}
			break;*/
	}

	switch (wParam)
	{
		case IDC_PANEL_AMP:
		case IDC_PANEL_EFFECTS:
		case IDC_PANEL_ASSIGN:
			m_ledOnOff.Invalidate(FALSE);
			m_AmpOnOff.Invalidate(FALSE);
			m_effectButtonOnOff.Invalidate(FALSE);
			m_effectsLedOnOff.Invalidate(FALSE);
			m_assignButtonOnOff.Invalidate(FALSE);
			m_assignLedOnOff.Invalidate(FALSE);
	}


	// Notify the parent window that a refresh of the panel is needed
	GetParent()->PostMessage(WM_COMMAND, wParam, (long) this);
	
	return CPanel ::OnCommand(wParam, lParam);
}

CString	CChainWnd::getPresetDir()
{
	return "preset\\chain\\";
}


int CChainWnd::setAllPanelData(char *buffer)
{
	int count;
	int i;

	CAssignNC *assign = &g_currentPatch->assignNC;

	count = assign->chainMix.setVGData(&buffer);

	for (i = 0; i < 10; i++)
		count += assign->chain[i].setVGData(&buffer);

	return count;
}


int CChainWnd::getAllPanelData(char *buffer)
{
	int count;
	int i;

	CAssignNC *assign = &g_currentPatch->assignNC;

	count = assign->chainMix.getVGData(&buffer);

	for (i = 0; i < 10; i++)
		count += assign->chain[i].getVGData(&buffer);

	return count;
}

void CChainWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	/*m_panelEdit = new CPanelReverb;

	m_panelEdit->m_parent = (CControl *) this;

	m_panelEdit->Create(NULL, "REVERB", WS_POPUP | WS_TABSTOP | WS_VISIBLE,
		CRect(600, 100, 600 + PANEL_WIDTH, 100 + PANELEFFECT_HEIGTH), this, 0, NULL);
	
	m_panelEdit->AttachVGData(g_currentPatch);
	m_panelEdit->SetFocus();*/

	CWnd ::OnRButtonDown(nFlags, point);
}


void CChainWnd::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd ::OnKillFocus(pNewWnd);
}

void CChainWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int i;

	CWnd ::OnLButtonDown(nFlags, point);

	if (!g_currentPatch)
		return;

	m_moveFrom = -1;

	for (i = 0; i < 10; i++)
	{
		if (IsPedalOn(i))
		{
			if (point.x >= m_pedalPos[i].left && point.x <= m_pedalPos[i].right
				&& point.y >= m_pedalPos[i].top && point.y <= m_pedalPos[i].bottom)
			{
				m_moveFrom = i;
			}
		}
	}

	if (m_moveFrom == -1 && point.x >= m_CosmGMix.left && point.x <= m_CosmGMix.right
				&& point.y >= m_CosmGMix.top && point.y <= m_CosmGMix.bottom)
	{
		m_moveFrom = -2;
	}

	Invalidate(FALSE);

	if (m_moveFrom == -1)
		return;

	m_moveTo = -1;
	m_bTracking = TRUE;
	SetCapture();
	::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORM));
}


void CChainWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	int i;

	if (m_bTracking && g_currentPatch)
	{
		m_moveTo = -1;

		for (i = 0; i < 10; i++)
		{
			if ((i < m_moveFrom || i > m_moveFrom || m_moveFrom == -2) && IsPedalOn(i))
			{
				int offset1, offset2;

				if (point.x > m_pedalPos[m_moveFrom].left)
				{
					offset1 = 15;
					offset2 = 0;
				}
				else
				{
					offset1 = 0;
					offset2 = 15;
				}

				if (point.x >= m_pedalPos[i].left - offset2 && point.x <= m_pedalPos[i].right + offset1
					&& point.y >= m_pedalPos[i].top && point.y <= m_pedalPos[i].bottom)
				{
					m_moveTo = i;

					if (m_moveFrom == -2)
						g_currentPatch->assignNC.chainMix.setValue(m_moveTo + 1);

					InvalidateRect(CRect(0, 85, 900, 303), FALSE);

					return;
				}
			}
		}

		if (m_moveFrom == -2 && point.x >= 146 && point.x <= 170
					&& point.y >= 130 && point.y <= 230)
		{
			g_currentPatch->assignNC.chainMix.setValue(0);
		}

		InvalidateRect(CRect(0, 85, 900, 303), FALSE);
	}
}


void CChainWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bTracking && g_currentPatch)
	{
		m_bTracking = FALSE;
		ReleaseCapture();


		if (m_moveTo != -1 && m_moveFrom != -1 && m_moveFrom != -2)
		{
			int i;
			int values[10];

			
			if (m_moveFrom < m_moveTo)
			{
				for (i = 0; i < 10; i++)
				{
					if (i < m_moveFrom || i > m_moveTo)
						values[i] = g_currentPatch->assignNC.chain[i].getValue();
					else if (i == m_moveTo)
						values[i] = g_currentPatch->assignNC.chain[m_moveFrom].getValue();
					else if (i < m_moveTo)
						values[i] = g_currentPatch->assignNC.chain[i + 1].getValue();
				}
			}
			else
			{
				for (i = 0; i < 10; i++)
				{
					if (i < m_moveTo || i > m_moveFrom)
						values[i] = g_currentPatch->assignNC.chain[i].getValue();
					else if (i == m_moveTo)
						values[i] = g_currentPatch->assignNC.chain[m_moveFrom].getValue();
					else if (i <= m_moveFrom)
						values[i] = g_currentPatch->assignNC.chain[i - 1].getValue();
				}
			}


			for (i = 0; i < 10; i++)
				g_currentPatch->assignNC.chain[i].setValue(values[i]);
		}

		m_moveTo = -1;
		m_moveFrom = -1;

		Invalidate(FALSE);

		((CMainFrame *) AfxGetMainWnd())->m_chainWnd.OnPatchChange();
		((CMainFrame *) AfxGetMainWnd())->m_patchWnd.m_patchWindowLayer.OnPatchChange();
		((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();
	}
}


bool CChainWnd::IsPedalOn(int i)
{
	bool pedalIsOn = false;

	switch(g_currentPatch->assignNC.chain[i].getValue())
	{ 
		case 0:	// COMP
			if (g_currentPatch->compOnOff.getValue())
				pedalIsOn = true;
				break;

		case 1:	// WAH
			if (g_currentPatch->wahOnOff.getValue())
				pedalIsOn = true;
				break;
			
		case  2:	// AMP
			if (g_currentPatch->cosmAmp.ampOnOff.getValue())
				pedalIsOn = true;
				break;
				
		case  3:	// EQ
			if (g_currentPatch->eqOnOff.getValue())
				pedalIsOn = true;
				break;
				
		case  4:	// FV
			if (g_currentPatch->assignNC.expOnOff.getValue())
				pedalIsOn = true;
				break;
			
		case  5:	// NS
			if (g_currentPatch->nsOnOff.getValue())
				pedalIsOn = true;
				break;
				
		case  6:	// MOD
			if (g_currentPatch->modOnOff.getValue())
				pedalIsOn = true;
				break;
				
		case  7:	// DLY
			if (g_currentPatch->delayOnOff.getValue())
				pedalIsOn = true;
				break;
				
		case  8:	// CHO
			if (g_currentPatch->chorusOnOff.getValue())
				pedalIsOn = true;
				break;
			
		case  9:	// REV
			if (g_currentPatch->reverbOnOff.getValue())
				pedalIsOn = true;
				break;
	}

	return pedalIsOn;
}
