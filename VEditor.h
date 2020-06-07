// VEditor.h : main header file for the VEDITOR application
//

#if !defined(AFX_VEDITOR_H__4DFB9A34_943A_4256_9C68_3856E925731A__INCLUDED_)
#define AFX_VEDITOR_H__4DFB9A34_943A_4256_9C68_3856E925731A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "vg-88.h"
#include "tools.h"       // main symbols
#include "settings.h"
#include <Mmsystem.h>

extern bool g_firstRun;

extern CMaskedBitmap g_down;
extern CMaskedBitmap g_up;
extern CMaskedBitmap g_pFileTop;
extern CMaskedBitmap g_pFileBot;
extern CMaskedBitmap g_pFileLeft;
extern CMaskedBitmap g_pFileRight;
extern CMaskedBitmap g_vg88Font;
extern CMaskedBitmap g_vg88FontBW;
extern CMaskedBitmap g_chain;
extern CMaskedBitmap g_chainSkin;
extern CMaskedBitmap g_digit;
extern CMaskedBitmap g_guitar[11];
extern CMaskedBitmap g_acoustic;
extern CMaskedBitmap g_acousticMic;
extern CMaskedBitmap g_nylon;
extern CMaskedBitmap g_nylonii;
extern CMaskedBitmap g_sitar;
extern CMaskedBitmap g_sitarp;
extern CMaskedBitmap g_solo;
extern CMaskedBitmap g_organ;
extern CMaskedBitmap g_pipe;
extern CMaskedBitmap g_crystal;
extern CMaskedBitmap g_bowed;
extern CMaskedBitmap g_comp[2];
extern CMaskedBitmap g_wah[2];
extern CMaskedBitmap g_amp[32];
extern CMaskedBitmap g_eq;
extern CMaskedBitmap g_fv;
extern CMaskedBitmap g_ns;
extern CMaskedBitmap g_mod[12];
extern CMaskedBitmap g_delay;
extern CMaskedBitmap g_chorus; 
extern CMaskedBitmap g_reverb;
extern CMaskedBitmap g_cable;
extern CMaskedBitmap g_cable2;
extern CMaskedBitmap g_cableCorner;
extern CMaskedBitmap g_cableInter;
extern CMaskedBitmap g_pickup;
extern CMaskedBitmap g_tune;
extern CMaskedBitmap g_detune;
extern CMaskedBitmap g_polySlowGear;
extern CMaskedBitmap g_polyOctave;
extern CMaskedBitmap g_polyDist[5];
extern CMaskedBitmap g_section;
extern CMaskedBitmap g_sEffAutoWah;
extern CMaskedBitmap g_sEffChorus;
extern CMaskedBitmap g_sEffComp;
extern CMaskedBitmap g_sEffDelay;
extern CMaskedBitmap g_sEffEq;
extern CMaskedBitmap g_sEffFlanger;
extern CMaskedBitmap g_sEffHarmo;
extern CMaskedBitmap g_sEffPan;
extern CMaskedBitmap g_sEffPedShift;
extern CMaskedBitmap g_sEffPedWah;
extern CMaskedBitmap g_sEffPhaser;
extern CMaskedBitmap g_sEffReverb;
extern CMaskedBitmap g_sEffVibrato;
extern CMaskedBitmap g_sEffUniV;
extern CMaskedBitmap g_sEffDefretter;
extern CMaskedBitmap g_sEffNS;
extern CMaskedBitmap g_eqLabel;
extern CMaskedBitmap g_guitarNylon;
extern CMaskedBitmap g_guitarNylonII;
extern CMaskedBitmap g_brassB;
extern CMaskedBitmap g_brass;
extern CMaskedBitmap g_wave;
extern CMaskedBitmap g_waveSaw;
extern CMaskedBitmap g_waveSquare;
extern CMaskedBitmap g_filterBassS;
extern CMaskedBitmap g_filterBassB;

extern CMaskedBitmap g_assignCtl;
extern CMaskedBitmap g_assignGKS1S2;
extern CMaskedBitmap g_assignGKVol;
extern CMaskedBitmap g_assignMidi;
extern CMaskedBitmap g_assignPedal;
extern CMaskedBitmap g_speaker;
extern CMaskedBitmap g_mic1;
extern CMaskedBitmap g_mic2;
extern CMaskedBitmap g_organSlider;
extern CMaskedBitmap g_organS;
extern CMaskedBitmap g_effDist;
extern CMaskedBitmap  g_violon2;
extern CMaskedBitmap  g_trumpet2;
extern CMaskedBitmap  g_crystal2;
extern CMaskedBitmap  g_flute2;

extern CFont		 g_font1, g_font2, g_font3, g_font4, g_font5;
extern CImageList	*g_ImageList;


// Bitmap for panels and customs controls
extern CMaskedBitmap g_panel1;
extern CMaskedBitmap g_panelEmpty;
extern CMaskedBitmap g_panelBottom;

// Bitmap for controls
extern CMaskedBitmap  g_knob1;
extern CMaskedBitmap  g_knob2;
extern CMaskedBitmap  g_switch1;
extern CMaskedBitmap  g_faderv1;
extern CMaskedBitmap  g_faderh1;
extern CMaskedBitmap  g_knob3;
extern CMaskedBitmap  g_knob4;
extern CMaskedBitmap  g_wah2;
extern CMaskedBitmap  g_amplifers;
extern CMaskedBitmap  g_key;
extern CMaskedBitmap  g_knob6;
extern CMaskedBitmap  g_knob7;
extern CMaskedBitmap  g_selector;
extern CMaskedBitmap  g_guitars;
extern CMaskedBitmap  g_bodytype;
extern CMaskedBitmap  g_guitarsacous;
extern CMaskedBitmap  g_pickuptype1;
extern CMaskedBitmap  g_pickuptype2;
extern CMaskedBitmap  g_button1;
extern CMaskedBitmap  g_button2;
extern CMaskedBitmap  g_button3;
extern CMaskedBitmap  g_led1;
extern CMaskedBitmap  g_led2;
extern CMaskedBitmap  g_empty;
extern CMaskedBitmap  g_popup;
extern CMaskedBitmap  g_labelPan;
extern CMaskedBitmap  g_dualS;
extern CMaskedBitmap  g_dualB;
extern CMaskedBitmap  g_ppwmS;
extern CMaskedBitmap  g_ppwmB;
extern CMaskedBitmap  g_lcd;
extern CMaskedBitmap  g_gkFunc;
extern CMaskedBitmap  g_dial;
extern CMaskedBitmap  g_tuner;
extern CMaskedBitmap  g_outputSelect;
extern CMaskedBitmap  g_gk2ab;
extern CMaskedBitmap  g_buttonSave;
extern CMaskedBitmap  g_buttonDelete;
extern CMaskedBitmap  g_buttonCopy;
extern CMaskedBitmap  g_buttonRename;

extern CPatch		*g_currentPatch;
extern int			g_currentPatchNumber;
extern CVG88SysEx	*g_currentLibrary;
extern CSystem		*g_currentSystem;

extern CSettings	g_settings;

#define ON_WM_APP() \
	{ WM_APP, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(void (AFX_MSG_CALL CWnd::*)(void))&OnRefreshNeeded },


/////////////////////////////////////////////////////////////////////////////
// CVEditorApp:
// See VEditor.cpp for the implementation of this class
//

class CVEditorApp : public CWinApp
{
public:
	CVEditorApp();
	~CVEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//{{AFX_MSG(CVEditorApp)
	afx_msg void OnAppAbout();
	afx_msg void OnAppSettings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEDITOR_H__4DFB9A34_943A_4256_9C68_3856E925731A__INCLUDED_)
