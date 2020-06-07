// PatchWnd.cpp : implementation of the CPatchWndLayer class
//

#include <stdio.h>
#include <io.h>
#include <time.h>
#include "stdafx.h"
#include "VEditor.h"
#include "MainFrm.h"
#include "tools.h"
#include "PatchWnd.h"
#include "VG-88.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CPatchWndLayer

CPatchWndLayer::CPatchWndLayer()
{
	m_guitarAmp		= TRUE;
	m_effects		= FALSE;
	m_levelBmpKey	= FALSE;
	m_pedalAssign	= FALSE;
}


CPatchWndLayer::~CPatchWndLayer()
{
}


BEGIN_MESSAGE_MAP(CPatchWndLayer,CWnd )
	//{{AFX_MSG_MAP(CPatchWndLayer)
	ON_WM_CREATE ()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPatchWndLayer message handlers

BOOL CPatchWndLayer::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL /*HBRUSH(COLOR_APPWORKSPACE + 1)*/ , NULL);

	return TRUE;
}

int CPatchWndLayer::OnCreate (LPCREATESTRUCT lpcs)
{
	int i;
	char buffer[255];

	// Empty panels

	if (!m_panelEmpty1.Create(NULL, "", WS_CHILD | WS_TABSTOP,
		CRect(0, PANEL7_HEIGTH, PANEL_WIDTH, PANEL8_HEIGTH + PANEL7_HEIGTH), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelEmpty2.Create(NULL, "", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelEmpty3.Create(NULL, "", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * (2 + 1), PANEL2_HEIGTH), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelEmpty4.Create(NULL, "", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * (3 + 1), PANEL2_HEIGTH), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelEmpty5.Create(NULL, "", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 4, 0, PANEL_WIDTH * (4 + 1), PANEL2_HEIGTH), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	//////////////////
	// GUITAR & AMP //
	//////////////////

	if (!m_panelCosmGT.Create(NULL, "COSM GT", WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		CRect(0, 0, PANEL_WIDTH, PANEL7_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelBody.Create(NULL, "BODY", WS_CHILD | WS_TABSTOP,
		CRect(0, PANEL7_HEIGTH, PANEL_WIDTH, PANEL7_HEIGTH + PANEL8_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelFilter.Create(NULL, "FILTER", WS_CHILD | WS_TABSTOP,
		CRect(0, PANEL7_HEIGTH, PANEL_WIDTH, PANEL7_HEIGTH + PANEL8_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelBodyNylon.Create(NULL, "BODY", WS_CHILD | WS_TABSTOP,
		CRect(0, PANEL7_HEIGTH, PANEL_WIDTH, PANEL7_HEIGTH + PANEL8_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelBodyNylonII.Create(NULL, "BODY", WS_CHILD | WS_TABSTOP,
		CRect(0, PANEL7_HEIGTH, PANEL_WIDTH, PANEL7_HEIGTH + PANEL8_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelPickup.Create(NULL, "PICKUP", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelPickupNylon.Create(NULL, "PICKUP", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelSitar.Create(NULL, "SITAR", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelWave.Create(NULL, "WAVE", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelPickupVari.Create(NULL, "PICKUP", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelPickupAcous.Create(NULL, "PICKUP", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelOrgan.Create(NULL, "ORGAN", WS_CHILD | WS_TABSTOP ,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	if (!m_panelBowed.Create(NULL, "P-BEND", WS_CHILD | WS_TABSTOP ,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	if (!m_panelDual.Create(NULL, "GLIDE", WS_CHILD | WS_TABSTOP ,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	if (!m_panelFilterBass.Create(NULL, "COLOR", WS_CHILD | WS_TABSTOP ,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	if (!m_panelPipe.Create(NULL, "P-BEND", WS_CHILD | WS_TABSTOP ,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelSolo.Create(NULL, "COLOR", WS_CHILD | WS_TABSTOP ,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelPWM.Create(NULL, "MOD", WS_CHILD | WS_TABSTOP ,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelCrystal.Create(NULL, "ATTACK", WS_CHILD | WS_TABSTOP ,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelBrass.Create(NULL, "SUSTAIN", WS_CHILD | WS_TABSTOP ,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Panel pitch shift
	if (!m_pitchShift.Create(NULL, "PT SHIFT", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * 3, PANEL2_HEIGTH), this, IDW_PATCHWND + 3, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Panel Open Tune
	if (!m_panelOpenTune.Create(NULL, "TUNE", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * 3, PANEL2_HEIGTH), this, IDW_PATCHWND + 3, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

		// Panel DeTune
	if (!m_panelDetune.Create(NULL, "DETUNE", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * 3, PANEL2_HEIGTH), this, IDW_PATCHWND + 3, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Panel PD shift
	if (!m_panelPDShift.Create(NULL, "PD SHIFT", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * 3, PANEL2_HEIGTH), this, IDW_PATCHWND + 3, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Panel Dist
	if (!m_panelDist.Create(NULL, "DIST", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * 3, PANEL2_HEIGTH), this, IDW_PATCHWND + 3, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

		// Panel Poly comp
	if (!m_panelPolyComp.Create(NULL, "COMP  /  LIM", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * 3, PANEL2_HEIGTH), this, IDW_PATCHWND + 3, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Panel SG
	if (!m_panelPolySG.Create(NULL, "SG", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * 3, PANEL2_HEIGTH), this, IDW_PATCHWND + 3, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Panel pitch shift
	if (!m_panelPolyOct.Create(NULL, "POLY OCT", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * 3, PANEL2_HEIGTH), this, IDW_PATCHWND + 3, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// COSM Equalizer
	if (!m_cosmEqualizer.Create(NULL, "COSM EQ", WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL3_HEIGTH), this, IDW_PATCHWND + 4, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Cosm pan
	if (!m_cosmPan.Create(NULL, "PAN", WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, PANEL3_HEIGTH, PANEL_WIDTH * 4, PANEL3_HEIGTH + PANELPAN_HEIGTH), this, IDW_PATCHWND + 8, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_mixer.Create(NULL, "MIXER", WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, PANEL3_HEIGTH + PANELPAN_HEIGTH, PANEL_WIDTH * 4, PANEL3_HEIGTH + PANELPAN_HEIGTH + PANELMIXER_HEIGTH), this, IDW_PATCHWND + 3, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// COSM AMP
	if (!m_panelAmp.Create(NULL, "COSM AMP", WS_CHILD | WS_TABSTOP | WS_VISIBLE,
		CRect(PANEL_WIDTH * 4, 0, PANEL_WIDTH * 5, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	/////////////
	// EFFECTS //
	/////////////

	// Compressor
	if (!m_compressor.Create(NULL, "COMPRESSOR", WS_CHILD | WS_TABSTOP, //| WS_VISIBLE,
		CRect(0, 0, PANEL_WIDTH, PANELEFFECT_HEIGTH), this, IDW_PATCHWND + 4, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Limiter
	if (!m_limiter.Create(NULL, "LIMITER", WS_CHILD | WS_TABSTOP, //| WS_VISIBLE,
		CRect(0, 0, PANEL_WIDTH, PANELEFFECT_HEIGTH), this, IDW_PATCHWND + 4, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Pedal Wah
	if (!m_pedalWah.Create(NULL, "PEDAL WAH", WS_CHILD | WS_TABSTOP, //| WS_VISIBLE,
		CRect(0, PANELEFFECT_HEIGTH, PANEL_WIDTH, PANELEFFECT_HEIGTH * 2), this, IDW_PATCHWND + 4, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	if (!m_autoWah.Create(NULL, "AUTO WAH", WS_CHILD | WS_TABSTOP, //| WS_VISIBLE,
		CRect(0, PANELEFFECT_HEIGTH, PANEL_WIDTH, PANELEFFECT_HEIGTH * 2), this, IDW_PATCHWND + 4, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}



	// Equalizer
	if (!m_equalizerEff.Create(NULL, "EQUALIZER", WS_CHILD | WS_TABSTOP, //| WS_VISIBLE,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, PANELEFFECT_HEIGTH), this, IDW_PATCHWND + 4, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Reverb
	if (!m_panelReverb.Create(NULL, "REVERB", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH, PANELEFFECT_HEIGTH, PANEL_WIDTH * 2, PANELEFFECT_HEIGTH * 2), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Delay
	if (!m_panelDelay.Create(NULL, "DELAY", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * 3, PANELEFFECT_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Chorus
	if (!m_panelChorus.Create(NULL, "CHORUS", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 2, PANELEFFECT_HEIGTH, PANEL_WIDTH * 3, PANELEFFECT_HEIGTH * 2), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// MODULATION PANELS //

	// harmonist
	if (!m_harmonist.Create(NULL, "HARMONIST", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelPShifter.Create(NULL, "P.SHIFTER", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// flanger
	if (!m_panelFlanger.Create(NULL, "FLANGER", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// phaser
	if (!m_panelPhaser.Create(NULL, "PHASER", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// 2x2 chorus
	if (!m_panel2x2Chorus.Create(NULL, "2x2 CHORUS", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	// Sub eq
	if (!m_panelSubEq.Create(NULL, "SUB EQ", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Vibrato
	if (!m_panelVibrato.Create(NULL, "VIBRATO", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Tremolo
	if (!m_panelTremolo.Create(NULL, "TREMOLO", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelDefretter.Create(NULL, "DEFRETTER", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelUniV.Create(NULL, "UNI-V", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Effect pan
	if (!m_panelPanEff.Create(NULL, "PAN", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Pedal shift
	if (!m_panelPdShift.Create(NULL, "PD SHIFT", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 3, 0, PANEL_WIDTH * 4, PANEL2_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Foot Volume
	if (!m_panelFV.Create(NULL, "FOOT VOLUME", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 4, 0, PANEL_WIDTH * 5, PANELEFFECT4_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Noise suppressor
	if (!m_panelNS.Create(NULL, "NOISE SUPPRESSOR", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 4, PANELEFFECT4_HEIGTH, PANEL_WIDTH * 5, PANELEFFECT4_HEIGTH + PANELEFFECT5_HEIGTH), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Level / BPM / KEY
	if (!m_panelVolBmpKey.Create(NULL, "LEVEL / BPM / KEY", WS_CHILD | WS_TABSTOP, // | WS_VISIBLE,
		CRect(PANEL_WIDTH * 4, PANELEFFECT4_HEIGTH + PANELEFFECT5_HEIGTH, PANEL_WIDTH * 5, PANELEFFECT_HEIGTH + PANELEFFECT4_HEIGTH + PANELEFFECT5_HEIGTH), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Panel Assign
	for (i = 0;  i < 8; i++)
	{
		sprintf(buffer, "ASSIGN %d", i + 1);

		if (!m_panelAssign[i].Create(NULL, buffer, WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH + PANEL_WIDTH * (i / 2), 
		PANELEFFECT_HEIGTH * (i % 2), 
		PANEL_WIDTH * 2 + (PANEL_WIDTH * (i / 2)), 
		PANELEFFECT_HEIGTH + (PANELEFFECT_HEIGTH * (i % 2)))
		, this, 0, NULL))
		{
			TRACE0("Failed to create view window\n");
			return -1;
		}

		m_panelAssign[i].SetAssignNum(i);
	}

	if (!m_panelAssignExp.Create(NULL, "EXP PEDAL", WS_CHILD | WS_TABSTOP,
		CRect(0, 0, PANEL_WIDTH, PANELEFFECT5_HEIGTH), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelAssignCtl.Create(NULL, "CTL PEDAL", WS_CHILD | WS_TABSTOP,
		CRect(0, PANELEFFECT5_HEIGTH, PANEL_WIDTH, PANELEFFECT5_HEIGTH * 2), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelAssignGkVol.Create(NULL, "GK VOL", WS_CHILD | WS_TABSTOP,
		CRect(0, PANELEFFECT5_HEIGTH * 2, PANEL_WIDTH, PANELEFFECT5_HEIGTH * 3), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelAssignGkS1S2.Create(NULL, "GK  DOWN / S1  UP / S2", WS_CHILD | WS_TABSTOP,
		CRect(0, PANELEFFECT5_HEIGTH * 3, PANEL_WIDTH, PANELEFFECT5_HEIGTH * 4), this, IDW_PATCHWND + 5, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	

	////////////
	// SYSTEM //
	////////////

	if (!m_panelContrast.Create(NULL, "CONTRAST", WS_CHILD | WS_TABSTOP,
		CRect(0, 0, PANEL_WIDTH, 120), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelGkFunction.Create(NULL, "GK FUNC", WS_CHILD | WS_TABSTOP,
		CRect(0, 120, PANEL_WIDTH, 120 + 176), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelGlobal.Create(NULL, "GLOBAL", WS_CHILD | WS_TABSTOP,
		CRect(0, 120 + 176, PANEL_WIDTH, 120 + 176 + 190), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelTuner.Create(NULL, "TUNER", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH, 0, PANEL_WIDTH * 2, 120), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelDial.Create(NULL, "DIAL", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH, 120, PANEL_WIDTH * 2, 120 + 176), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelOutputSelect.Create(NULL, "OUTPUT SELECT", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH, 120 + 176, PANEL_WIDTH * 2, 120 + 176 + 190), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_panelDriverSetting.Create(NULL, "DRIVER SETTING", WS_CHILD | WS_TABSTOP,
		CRect(PANEL_WIDTH * 2, 0, PANEL_WIDTH * 3, PANEL2_HEIGTH), this, 0, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	return 0;
}


void CPatchWndLayer::OnPaint() 
{
	CPaintDC dc(this);
}


void CPatchWndLayer::PaintPatchWnd(CDC *dc) 
{

}


void CPatchWndLayer::OnPatchChange()
{
	int guitarType;
	int i;

	int m_panelEmpty1_flag		 = SW_HIDE;
	int m_panelEmpty2_flag		 = SW_HIDE;
	int m_panelEmpty3_flag		 = SW_HIDE;
	int m_panelEmpty4_flag		 = SW_HIDE;
	int m_panelEmpty5_flag		 = SW_HIDE;

	int m_panelCosmGT_flag		 = SW_HIDE;

	int m_panelBody_flag		 = SW_HIDE;
	int m_panelBodyNylon_flag	 = SW_HIDE;
	int m_panelBodyNylonII_flag	 = SW_HIDE;
	int m_panelFilter_flag		 = SW_HIDE;

	int m_panelPickupVari_flag	 = SW_HIDE;
	int m_panelPickup_flag		 = SW_HIDE;
	int m_panelPickupNylon_flag	 = SW_HIDE;
	int m_panelPickupAcous_flag	 = SW_HIDE;
	int m_panelSitar_flag		 = SW_HIDE;
	int m_panelWave_flag		 = SW_HIDE;
	int m_panelBowed_flag		 = SW_HIDE;
	int m_panelDual_flag		 = SW_HIDE;
	int m_panelFilterBass_flag	 = SW_HIDE;
	int m_panelPipe_flag		 = SW_HIDE;
	int m_panelSolo_flag		 = SW_HIDE;
	int m_panelPWM_flag			 = SW_HIDE;
	int m_panelCrystal_flag		 = SW_HIDE;
	int m_panelOrgan_flag		 = SW_HIDE;
	int m_panelBrass_flag		 = SW_HIDE;

	int m_pitchShift_flag		 = SW_HIDE;
	int m_panelOpenTune_flag	 = SW_HIDE;
	int m_panelDetune_flag		 = SW_HIDE;
	int m_panelPDShift_flag		 = SW_HIDE;
	int m_panelDist_flag		 = SW_HIDE;
	int m_panelPolyComp_flag	 = SW_HIDE;
	int m_panelPolyOct_flag		 = SW_HIDE;
	int m_panelPolySG_flag		 = SW_HIDE;
	
	int m_cosmEqualizer_flag	 = SW_HIDE;
	int m_cosmPan_flag			 = SW_HIDE;
	int m_mixer_flag			 = SW_HIDE;
	int m_panelAmp_flag			 = SW_HIDE;


	if (m_guitarAmp && !g_currentSystem)
	{
		// Panels that always appear
		m_panelCosmGT_flag	 = SW_SHOWNA;
		m_cosmPan_flag		 = SW_SHOWNA;
		m_cosmEqualizer_flag = SW_SHOWNA;
		m_mixer_flag		 = SW_SHOWNA;
		m_panelAmp_flag		 = SW_SHOWNA;
	
		
		m_panelCosmGT.AttachVGData(g_currentPatch);
		m_cosmPan.AttachVGData(g_currentPatch);
		m_cosmEqualizer.AttachVGData(g_currentPatch);
		m_mixer.AttachVGData(g_currentPatch);
		m_panelAmp.AttachVGData(g_currentPatch);

		// Panels that appear depending on some values in the patch

		if (g_currentPatch)
		{
			guitarType = g_currentPatch->cosmGT.guitarType.getValue();

			switch (guitarType)
			{
				case COSMGT_VARI_GT:
					m_pitchShift_flag = SW_SHOWNA;
					m_pitchShift.AttachVGData(g_currentPatch);
					m_panelBody_flag = SW_SHOWNA;
					m_panelBody.AttachVGData(g_currentPatch);
					break;

				case COSMGT_ACOUSTIC:
					m_panelPickupAcous_flag = SW_SHOWNA;
					m_panelPickupAcous.AttachVGData(g_currentPatch);
					m_panelBody_flag = SW_SHOWNA;
					m_panelBody.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_NYLON_STRINGS:
					m_panelPickupNylon_flag = SW_SHOWNA;
					m_panelPickupNylon.AttachVGData(g_currentPatch);
					m_panelBodyNylon_flag = SW_SHOWNA;
					m_panelBodyNylon.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_OPEN_TUNE:
					m_panelOpenTune_flag = SW_SHOWNA;
					m_panelOpenTune.AttachVGData(g_currentPatch);
					m_panelBody_flag = SW_SHOWNA;
					m_panelBody.AttachVGData(g_currentPatch);
					break;

				case COSMGT_12STRINGS:
					m_panelDetune_flag = SW_SHOWNA;
					m_panelDetune.AttachVGData(g_currentPatch);
					m_panelBody_flag = SW_SHOWNA;
					m_panelBody.AttachVGData(g_currentPatch);
					break;

				case COSMGT_PD_SHIFT:
					m_panelPDShift_flag = SW_SHOWNA;
					m_panelPDShift.AttachVGData(g_currentPatch);
					m_panelBody_flag = SW_SHOWNA;
					m_panelBody.AttachVGData(g_currentPatch);
					break;

				case COSMGT_POLY_DIST:
					m_panelDist_flag = SW_SHOWNA;
					m_panelDist.AttachVGData(g_currentPatch);
					m_panelEmpty1_flag = SW_SHOWNA;
					break;

				case COSMGT_POLY_COMP:
					m_panelPolyComp_flag = SW_SHOWNA;
					m_panelPolyComp.AttachVGData(g_currentPatch);
					m_panelEmpty1_flag = SW_SHOWNA;
					break;

				case COSMGT_POLY_OCT:
					m_panelPolyOct_flag = SW_SHOWNA;
					m_panelPolyOct.AttachVGData(g_currentPatch);
					m_panelEmpty1_flag = SW_SHOWNA;
					break;
				
				case COSMGT_POLY_SG:
					m_panelPolySG_flag = SW_SHOWNA;
					m_panelPolySG.AttachVGData(g_currentPatch);
					m_panelEmpty1_flag = SW_SHOWNA;
					break;

				case COSMGT_BOWED:
					m_panelFilter_flag =  SW_SHOWNA;
					m_panelFilter.AttachVGData(g_currentPatch);
					m_panelBowed_flag = SW_SHOWNA;
					m_panelBowed.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_DUAL:
					m_panelFilter_flag =  SW_SHOWNA;
					m_panelFilter.AttachVGData(g_currentPatch);
					m_panelDual_flag = SW_SHOWNA;
					m_panelDual.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_FILTER_BASS:
					m_panelFilter_flag =  SW_SHOWNA;
					m_panelFilter.AttachVGData(g_currentPatch);
					m_panelFilterBass_flag = SW_SHOWNA;
					m_panelFilterBass.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_PIPE:
					m_panelFilter_flag =  SW_SHOWNA;
					m_panelFilter.AttachVGData(g_currentPatch);
					m_panelPipe_flag = SW_SHOWNA;
					m_panelPipe.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_SOLO:
					m_panelFilter_flag =  SW_SHOWNA;
					m_panelFilter.AttachVGData(g_currentPatch);
					m_panelSolo_flag = SW_SHOWNA;
					m_panelSolo.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_PWM:
					m_panelFilter_flag =  SW_SHOWNA;
					m_panelFilter.AttachVGData(g_currentPatch);
					m_panelPWM_flag = SW_SHOWNA;
					m_panelPWM.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_CRYSTAL:
					m_panelCrystal_flag = SW_SHOWNA;
					m_panelCrystal.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					m_panelEmpty1_flag = SW_SHOWNA;
					break;

				case COSMGT_ORGAN:
					m_panelOrgan_flag = SW_SHOWNA;
					m_panelOrgan.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					m_panelEmpty1_flag = SW_SHOWNA;
					break;

				case COSMGT_BRASS:
					m_panelFilter_flag =  SW_SHOWNA;
					m_panelFilter.AttachVGData(g_currentPatch);
					m_panelBrass_flag = SW_SHOWNA;
					m_panelBrass.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_NYLONII_STRINGS:
					m_panelPickupNylon_flag = SW_SHOWNA;
					m_panelPickupNylon.AttachVGData(g_currentPatch);
					m_panelBodyNylonII_flag = SW_SHOWNA;
					m_panelBodyNylonII.AttachVGData(g_currentPatch);
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_SITAR:
					m_panelSitar_flag = SW_SHOWNA;
					m_panelSitar.AttachVGData(g_currentPatch);
					m_panelEmpty1_flag = SW_SHOWNA;
					m_panelEmpty3_flag = SW_SHOWNA;
					break;

				case COSMGT_WAVE_SYNTH:
					m_panelWave_flag = SW_SHOWNA;
					m_panelWave.AttachVGData(g_currentPatch);
					m_panelEmpty1_flag = SW_SHOWNA;
					m_panelEmpty3_flag = SW_SHOWNA;
					break;
			}


			switch (guitarType)
			{
				case COSMGT_VARI_GT:
				case COSMGT_OPEN_TUNE:
				case COSMGT_12STRINGS:
				case COSMGT_PD_SHIFT:
				case COSMGT_POLY_DIST:
				case COSMGT_POLY_COMP:
				case COSMGT_POLY_OCT:
				case COSMGT_POLY_SG:
					if (((CVariGuitar *) g_currentPatch->instrument)->pickup.model.getValue() == PICKUP_VARI)
					{
						m_panelPickupVari_flag = SW_SHOWNA;
						m_panelPickupVari.AttachVGData(g_currentPatch);
					}
					else
					{
						m_panelPickup_flag = SW_SHOWNA;
						m_panelPickup.AttachVGData(g_currentPatch);
					}
			}

		}
		else
		{
			m_panelEmpty1_flag = SW_SHOWNA;
			m_panelEmpty2_flag = SW_SHOWNA;
			m_panelEmpty3_flag = SW_SHOWNA;
		}
	}
	
	m_panelEmpty1.ShowWindow(m_panelEmpty1_flag);
	m_panelEmpty2.ShowWindow(m_panelEmpty2_flag);
	m_panelEmpty3.ShowWindow(m_panelEmpty3_flag);
	m_panelEmpty4.ShowWindow(m_panelEmpty4_flag);
	m_panelEmpty5.ShowWindow(m_panelEmpty5_flag);

	m_panelCosmGT.ShowWindow(m_panelCosmGT_flag);

	m_panelBody.ShowWindow(m_panelBody_flag);
	m_panelBodyNylon.ShowWindow(m_panelBodyNylon_flag);
	m_panelBodyNylonII.ShowWindow(m_panelBodyNylonII_flag);
	m_panelFilter.ShowWindow(m_panelFilter_flag);

	m_panelPickupVari.ShowWindow(m_panelPickupVari_flag);
	m_panelPickup.ShowWindow(m_panelPickup_flag);
	m_panelPickupNylon.ShowWindow(m_panelPickupNylon_flag);
	m_panelSitar.ShowWindow(m_panelSitar_flag);
	m_panelWave.ShowWindow(m_panelWave_flag);
	m_panelPickupAcous.ShowWindow(m_panelPickupAcous_flag);
	m_panelBowed.ShowWindow(m_panelBowed_flag);
	m_panelDual.ShowWindow(m_panelDual_flag);
	m_panelFilterBass.ShowWindow(m_panelFilterBass_flag);
	m_panelPipe.ShowWindow(m_panelPipe_flag);
	m_panelSolo.ShowWindow(m_panelSolo_flag);
	m_panelPWM.ShowWindow(m_panelPWM_flag);
	m_panelCrystal.ShowWindow(m_panelCrystal_flag);
	m_panelOrgan.ShowWindow(m_panelOrgan_flag);
	m_panelBrass.ShowWindow(m_panelBrass_flag);
	
	m_pitchShift.ShowWindow(m_pitchShift_flag);
	m_panelOpenTune.ShowWindow(m_panelOpenTune_flag);
	m_panelDetune.ShowWindow(m_panelDetune_flag);
	m_panelPDShift.ShowWindow(m_panelPDShift_flag);
	m_panelDist.ShowWindow(m_panelDist_flag);
	m_panelPolyComp.ShowWindow(m_panelPolyComp_flag);
	m_panelPolyOct.ShowWindow(m_panelPolyOct_flag);
	m_panelPolySG.ShowWindow(m_panelPolySG_flag);
	
	m_cosmEqualizer.ShowWindow(m_cosmEqualizer_flag);
	m_cosmPan.ShowWindow(m_cosmPan_flag);
	m_mixer.ShowWindow(m_mixer_flag);
	m_panelAmp.ShowWindow(m_panelAmp_flag);


	if (m_effects && !g_currentSystem)
	{
		// Panels that always appear
		m_panelFV.ShowWindow(SW_SHOWNA);
		m_panelNS.ShowWindow(SW_SHOWNA);
		m_panelReverb.ShowWindow(SW_SHOWNA);
		m_panelDelay.ShowWindow(SW_SHOWNA);
		m_panelChorus.ShowWindow(SW_SHOWNA);
		m_equalizerEff.ShowWindow(SW_SHOWNA);
		m_panelVolBmpKey.ShowWindow(SW_SHOWNA);

		m_panelFV.AttachVGData(g_currentPatch);
		m_panelNS.AttachVGData(g_currentPatch);
		m_panelReverb.AttachVGData(g_currentPatch);
		m_panelDelay.AttachVGData(g_currentPatch);
		m_panelChorus.AttachVGData(g_currentPatch);
		m_equalizerEff.AttachVGData(g_currentPatch);
		m_panelVolBmpKey.AttachVGData(g_currentPatch);

		// Panels that appear depending on some values in the patch

		if (g_currentPatch && g_currentPatch->comp.compType.getValue() == COMP_COMP)
		{
			m_compressor.ShowWindow(SW_SHOWNA);
			m_limiter.ShowWindow(SW_HIDE);
			m_compressor.AttachVGData(g_currentPatch);
		}
		else
		{
			m_limiter.ShowWindow(SW_SHOWNA);
			m_compressor.ShowWindow(SW_HIDE);
			m_limiter.AttachVGData(g_currentPatch);
		}

		if (g_currentPatch && g_currentPatch->wah.wahType.getValue() == WAH_PEDAL)
		{
			m_pedalWah.ShowWindow(SW_SHOWNA);
			m_autoWah.ShowWindow(SW_HIDE);
			m_pedalWah.AttachVGData(g_currentPatch);
		}
		else
		{
			m_pedalWah.ShowWindow(SW_HIDE);
			m_autoWah.ShowWindow(SW_SHOWNA);
			m_autoWah.AttachVGData(g_currentPatch);
		}

		if (g_currentPatch && !g_currentSystem)
		{
			switch(g_currentPatch->mod.modeType.getValue())
			{
				case MOD_HARMONIST:
					m_harmonist.ShowWindow(SW_SHOWNA);
					m_harmonist.AttachVGData(g_currentPatch);

					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);
					break;

				case MOD_PSHIFTER:
					m_panelPShifter.ShowWindow(SW_SHOWNA);
					m_panelPShifter.AttachVGData(g_currentPatch);

					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);
					break;

				case MOD_VIBRATO:
					m_panelVibrato.ShowWindow(SW_SHOWNA);
					m_panelVibrato.AttachVGData(g_currentPatch);

					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);

					break;

				case MOD_PAN:
					m_panelPanEff.ShowWindow(SW_SHOWNA);
					m_panelPanEff.AttachVGData(g_currentPatch);

					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);
					break;

				case MOD_PDSHIFT:
					m_panelPdShift.ShowWindow(SW_SHOWNA);
					m_panelPdShift.AttachVGData(g_currentPatch);

					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);
					break;

				case MOD_TREMOLO:
					m_panelTremolo.ShowWindow(SW_SHOWNA);
					m_panelTremolo.AttachVGData(g_currentPatch);

					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);
					break;

				case MOD_SUBEQ:
					m_panelSubEq.ShowWindow(SW_SHOWNA);
					m_panelSubEq.AttachVGData(g_currentPatch);

					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);

					break;

				case MOD_2X2CHORUS:
					m_panel2x2Chorus.ShowWindow(SW_SHOWNA);
					m_panel2x2Chorus.AttachVGData(g_currentPatch);

					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);

					break;

				case MOD_FLANGER:
					m_panelFlanger.ShowWindow(SW_SHOWNA);
					m_panelFlanger.AttachVGData(g_currentPatch);

					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);
					
					break;

				case MOD_PHASER:
					m_panelPhaser.ShowWindow(SW_SHOWNA);
					m_panelPhaser.AttachVGData(g_currentPatch);

					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);

					break;

				case MOD_DEFRETTER:
					m_panelDefretter.ShowWindow(SW_SHOWNA);
					m_panelDefretter.AttachVGData(g_currentPatch);

					m_panelUniV.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);

					break;

				case MOD_UNIV:
					m_panelUniV.ShowWindow(SW_SHOWNA);
					m_panelUniV.AttachVGData(g_currentPatch);

					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);

					break;

				default:
					m_harmonist.ShowWindow(SW_HIDE);
					m_panelPShifter.ShowWindow(SW_HIDE);
					m_panelFlanger.ShowWindow(SW_HIDE);
					m_panelPhaser.ShowWindow(SW_HIDE);
					m_panelVibrato.ShowWindow(SW_HIDE);
					m_panelPdShift.ShowWindow(SW_HIDE);
					m_panelPanEff.ShowWindow(SW_HIDE);
					m_panelTremolo.ShowWindow(SW_HIDE);
					m_panelDefretter.ShowWindow(SW_HIDE);
					m_panelUniV.ShowWindow(SW_HIDE);
					m_panel2x2Chorus.ShowWindow(SW_HIDE);
					m_panelSubEq.ShowWindow(SW_HIDE);
			}
		}
		else
		{
			m_harmonist.ShowWindow(SW_HIDE);
			m_panelPShifter.ShowWindow(SW_HIDE);
			m_panelFlanger.ShowWindow(SW_HIDE);
			m_panelPhaser.ShowWindow(SW_HIDE);
			m_panelVibrato.ShowWindow(SW_SHOWNA);
			m_panelVibrato.AttachVGData(g_currentPatch);
			m_panelTremolo.ShowWindow(SW_HIDE);
			m_panelDefretter.ShowWindow(SW_HIDE);
			m_panelUniV.ShowWindow(SW_HIDE);
			m_panelPdShift.ShowWindow(SW_HIDE);
			m_panelPanEff.ShowWindow(SW_HIDE);
			m_panel2x2Chorus.ShowWindow(SW_HIDE);
			m_panelSubEq.ShowWindow(SW_HIDE);
		}
	}
	else
	{
		m_harmonist.ShowWindow(SW_HIDE);
		m_panelPShifter.ShowWindow(SW_HIDE);
		m_compressor.ShowWindow(SW_HIDE);
		m_limiter.ShowWindow(SW_HIDE);
		m_pedalWah.ShowWindow(SW_HIDE);
		m_autoWah.ShowWindow(SW_HIDE);
		m_panelFV.ShowWindow(SW_HIDE);
		m_panelNS.ShowWindow(SW_HIDE);
		m_panelReverb.ShowWindow(SW_HIDE);
		m_panelDelay.ShowWindow(SW_HIDE);
		m_panelFlanger.ShowWindow(SW_HIDE);
		m_panelPhaser.ShowWindow(SW_HIDE);
		m_panelChorus.ShowWindow(SW_HIDE);
		m_panelSubEq.ShowWindow(SW_HIDE);
		m_panel2x2Chorus.ShowWindow(SW_HIDE);
		m_panelVibrato.ShowWindow(SW_HIDE);
		m_panelTremolo.ShowWindow(SW_HIDE);
		m_panelDefretter.ShowWindow(SW_HIDE);
		m_panelUniV.ShowWindow(SW_HIDE);
		m_panelPdShift.ShowWindow(SW_HIDE);
		m_panelPanEff.ShowWindow(SW_HIDE);
		m_equalizerEff.ShowWindow(SW_HIDE);
		m_panelVolBmpKey.ShowWindow(SW_HIDE);
	}
	

	if (m_pedalAssign && !g_currentSystem)
	{
		m_panelAssignExp.ShowWindow(SW_SHOWNA);
		m_panelAssignCtl.ShowWindow(SW_SHOWNA);
		m_panelAssignGkVol.ShowWindow(SW_SHOWNA);
		m_panelAssignGkS1S2.ShowWindow(SW_SHOWNA);
	
		m_panelAssignExp.AttachVGData(g_currentPatch);
		m_panelAssignCtl.AttachVGData(g_currentPatch);
		m_panelAssignGkVol.AttachVGData(g_currentPatch);
		m_panelAssignGkS1S2.AttachVGData(g_currentPatch);

		for (i = 0; i < 8; i++)
		{
			m_panelAssign[i].ShowWindow(SW_SHOWNA);
			m_panelAssign[i].AttachVGData(g_currentPatch);
		}
	}
	else
	{
		for (i = 0; i < 8; i++)
			m_panelAssign[i].ShowWindow(SW_HIDE);

		m_panelAssignExp.ShowWindow(SW_HIDE);
		m_panelAssignCtl.ShowWindow(SW_HIDE);
		m_panelAssignGkVol.ShowWindow(SW_HIDE);
		m_panelAssignGkS1S2.ShowWindow(SW_HIDE);
	}

	if (g_currentSystem)
	{
		m_panelContrast.ShowWindow(SW_SHOWNA);
		m_panelGkFunction.ShowWindow(SW_SHOWNA);
		m_panelGlobal.ShowWindow(SW_SHOWNA);

		m_panelTuner.ShowWindow(SW_SHOWNA);
		m_panelDial.ShowWindow(SW_SHOWNA);
		m_panelOutputSelect.ShowWindow(SW_SHOWNA);

		m_panelDriverSetting.ShowWindow(SW_SHOWNA);

		m_panelEmpty4.ShowWindow(SW_SHOWNA);
		m_panelEmpty5.ShowWindow(SW_SHOWNA);

		m_panelContrast.AttachVGData(g_currentSystem);
		m_panelGkFunction.AttachVGData(g_currentSystem);
		m_panelGlobal.AttachVGData(g_currentSystem);
		
		m_panelTuner.AttachVGData(g_currentSystem);
		m_panelDial.AttachVGData(g_currentSystem);
		m_panelOutputSelect.AttachVGData(g_currentSystem);
		m_panelDriverSetting.AttachVGData(g_currentSystem);
	}
	else
	{
		m_panelContrast.ShowWindow(SW_HIDE);
		m_panelGkFunction.ShowWindow(SW_HIDE);
		m_panelGlobal.ShowWindow(SW_HIDE);
		m_panelEmpty4.ShowWindow(SW_HIDE);
		m_panelEmpty5.ShowWindow(SW_HIDE);

		m_panelTuner.ShowWindow(SW_HIDE);
		m_panelDial.ShowWindow(SW_HIDE);
		m_panelOutputSelect.ShowWindow(SW_HIDE);
		m_panelDriverSetting.ShowWindow(SW_HIDE);
	}
}


BOOL CPatchWndLayer::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// Notify the parent window that a refresh of the panel is needed
	GetParent()->PostMessage(WM_COMMAND, wParam, (long) this);
	
	return CWnd ::OnCommand(wParam, lParam);
}



BEGIN_MESSAGE_MAP(CPatchWnd,CWnd )
	//{{AFX_MSG_MAP(CPatchWnd)
	ON_WM_CREATE ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CPatchWnd::OnCreate (LPCREATESTRUCT lpcs)
{
	// create the patchLayer Window
	if (!m_patchWindowLayer.Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
		CRect(0, 0, 900, 486), this, IDW_PATCHWND, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	return 0;
}


BOOL CPatchWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL /*HBRUSH(COLOR_APPWORKSPACE + 1)*/ , NULL);

	return TRUE;
}


BOOL CPatchWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// Notify the parent window that a refresh of the panel is needed
	GetParent()->PostMessage(WM_COMMAND, wParam, (long) this);
	
	return CWnd ::OnCommand(wParam, lParam);
}