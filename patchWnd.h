// PatchWnd.h : interface of the CPatchWnd class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PatchWnd_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_)
#define AFX_PatchWnd_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

#include "panel.h"

#define PATCHWND_HEIGHT	486
#define PATCHWND_WIDTH	900


// CPatchWnd window

class CPatchWndLayer : public CWnd
{
// Construction
public:
	CPatchWndLayer();

// Attributes
public:
	BOOL m_guitarAmp;
	BOOL m_effects;
	BOOL m_levelBmpKey;
	BOOL m_pedalAssign;

	// GUITAR & AMP
	CPanelEmpty			m_panelEmpty1;
	CPanelEmpty			m_panelEmpty2;
	CPanelEmpty			m_panelEmpty3;
	CPanelEmpty			m_panelEmpty4;
	CPanelEmpty			m_panelEmpty5;
	CPanelCosmGT		m_panelCosmGT;
	CPanelBody			m_panelBody;
	CPanelBodyNylon		m_panelBodyNylon;
	CPanelBodyNylonII	m_panelBodyNylonII;
	CPanelPickup		m_panelPickup;
	CPanelPickupVari	m_panelPickupVari;
	CPanelOrgan			m_panelOrgan;
	CPanelPickupAcous	m_panelPickupAcous;
	CPanelPickupNylon	m_panelPickupNylon;
	CPanelSitar			m_panelSitar;
	CPanelWave			m_panelWave;
	CPanelAmp			m_panelInst;
	CPanelMixer			m_mixer;
	CPanelPan			m_cosmPan;
	CPanelEqualizer		m_cosmEqualizer;
	CPanelAmp			m_panelAmp;
	CPanelPitchShift	m_pitchShift;
	CPanelOpenTune		m_panelOpenTune;
	CPanelDetune		m_panelDetune;
	CPanelPDShift		m_panelPDShift;
	CPanelPolyOct		m_panelPolyOct;
	CPanelDist			m_panelDist;
	CPanelPolyComp		m_panelPolyComp;
	CPanelPolySG		m_panelPolySG;

	CPanelFilter		m_panelFilter;
	CPanelBowed			m_panelBowed;
	CPanelDual			m_panelDual;
	CPanelFilterBass	m_panelFilterBass;
	CPanelPipe			m_panelPipe;
	CPanelSolo			m_panelSolo;
	CPanelPWM			m_panelPWM;
	CPanelCrystal		m_panelCrystal;
	CPanelBrass			m_panelBrass;


	// EFFECTS
	CPanelHarmonist		m_harmonist;
	CPanelFlanger		m_panelFlanger;
	CPanelPhaser		m_panelPhaser;
	CPanelPShifter		m_panelPShifter;
	CPanelCompressor	m_compressor;
	CPanelLimiter		m_limiter;
	CPanelPedalWah		m_pedalWah;
	CPanelAutoWah		m_autoWah;
	CPanelEqualizerEff	m_equalizerEff;
	CPanelDelay			m_panelDelay;
	CPanelChorus		m_panelChorus;
	CPanelSubEq			m_panelSubEq;
	CPanel2x2Chorus		m_panel2x2Chorus;
	CPanelVibrato		m_panelVibrato;
	CPanelTremolo		m_panelTremolo;
	CPanelDefretter		m_panelDefretter;
	CPanelUniV			m_panelUniV;
	CPanelPanEff		m_panelPanEff;
	CPanelPdShift		m_panelPdShift;
	CPanelFV			m_panelFV;
	CPanelNS			m_panelNS;
	CPanelReverb		m_panelReverb;
	// LEVEL/BMP/KEY
	CPanelVolBmpKey		m_panelVolBmpKey;
	
	// ASSIGN
	CPanelAssign		m_panelAssign[8];
	CPanelAssignExp		m_panelAssignExp;
	CPanelAssignCtl		m_panelAssignCtl;
	CPanelAssignGkVol	m_panelAssignGkVol;
	CPanelAssignGkS1S2	m_panelAssignGkS1S2;
	
	// SYSTEM
	CPanelContrast		m_panelContrast;
	CPanelGkFunction	m_panelGkFunction;
	CPanelGlobal		m_panelGlobal;

	CPanelTuner			m_panelTuner;
	CPanelDial			m_panelDial;
	CPanelOutputSelect	m_panelOutputSelect;
	CPanelDriverSetting	m_panelDriverSetting;

	void PaintPatchWnd(CDC *dc);
	void OnPatchChange() ;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatchWndLayer)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPatchWndLayer();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPatchWndLayer)
	afx_msg int OnCreate (LPCREATESTRUCT);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPatchWnd : public CWnd
{
public:

	CPatchWndLayer m_patchWindowLayer;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatchWndLayer)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPatchWnd)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PatchWnd_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_)
