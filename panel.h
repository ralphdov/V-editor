#ifndef __PANEL_H__
#define __PANEL_H__


#include "tools.h"
#include "controls.h"
#include "preset.h"

#define PANEL_WIDTH		180
#define PANEL1_HEIGTH	353
#define PANEL2_HEIGTH	486
#define PANEL3_HEIGTH	184
#define PANELPAN_HEIGTH	184
#define PANELMIXER_HEIGTH 118
#define PANEL5_HEIGTH	118
#define PANEL6_HEIGTH	250
#define PANELEFFECT_HEIGTH	243
#define PANELEFFECT2_HEIGTH	275
#define PANELEFFECT3_HEIGTH	211
#define PANELEFFECT4_HEIGTH	122
#define PANELEFFECT5_HEIGTH	121
#define PANEL7_HEIGTH 133
#define PANEL8_HEIGTH 353


class CPanel :  public CWnd
{
public:
	CFont	    *m_font;
	CVGButton	m_onOff;
	CVGButton	m_preset;
	COnOff		m_presetData;
	CPreset		*m_presetWnd;
	CControl	*m_parent;

	CPanel();

	void			PaintPanel(CDC *dc);
	CMaskedBitmap	*m_background;
	CMaskedBitmap	*m_bottom;
	int				m_panelHeight;

	// preset management
	CString copy();
	virtual CString getPresetDir();
	virtual int setAllPanelData(char *buffer);
	virtual int getAllPanelData(char *buffer);

	virtual void AttachVGData(CPatch *patch);

	//CPtrList	vgControl;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanel)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPanel();


	// Generated message map functions
protected:
	//{{AFX_MSG(CPanel)
	afx_msg int OnCreate (LPCREATESTRUCT);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelEmpty :  public CPanel
{
public:
		
	CPanelEmpty();

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelEmpty)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelAmp :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGSection	m_sectionPreamp;
	CVGSection	m_sectionSpeaker;
	CVGEdit		m_ampType;
	CVGKnob		m_ampTypeImage;
	CVGKnob		m_volume;
	CVGKnob		m_presence;
	CVGKnob		m_master;
	CVGKnob		m_bass;
	CVGKnob		m_middle;
	CVGKnob		m_trebble;
	CVGKnob		m_gain;
	CVGKnob		m_bright;
	CVGEdit		m_speaker;
	CVGKnob		m_speakerImage;
	CVGKnob		m_balance;
	CVGKnob		m_micSet;
	CVGKnob		m_mic1;
	CVGKnob		m_mic2;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelAmp)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	CPanelAmp();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelAmp)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelEqualizer :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_labels;
	CVGKnob		m_level;
	CVGKnob		m_lowG;
	CVGKnob		m_hMidG;
	CVGKnob		m_lMidG;
	CVGKnob		m_highG;
	CVGKnob		m_lMidQ;
	CVGKnob		m_hMidQ;
	CVGKnob		m_hMidF;
	CVGKnob		m_lMidF;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelEqualizer();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelEqualizer)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




class CPanelEqualizerEff :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_eqImage;
	CVGKnob		m_labels;
	CVGKnob		m_level;
	CVGKnob		m_lowG;
	CVGKnob		m_hMidG;
	CVGKnob		m_lMidG;
	CVGKnob		m_highG;
	CVGKnob		m_lMidQ;
	CVGKnob		m_hMidQ;
	CVGKnob		m_hMidF;
	CVGKnob		m_lMidF;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelEqualizerEff();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelEqualizer)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




class CPanelPan :  public CPanel
{
public:
	CVGKnob	m_labels;
	CVGKnob	m_string[6];

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);


	CPanelPan();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPan)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelMixer :  public CPanel
{
public:
	CVGKnob	m_balance;
	CVGKnob	m_puPola;
	CVGKnob	m_level;

	CPanelMixer();
	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelMixer)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelPitchShift :  public CPanel
{
public:

	CVGButton	m_ledOnOff;
	CVGKnob		m_pedalImage;
	CVGSection	m_sectionShift;
	CVGSection	m_sectionHarmo;
	CVGEdit		m_key;
	CVGKnob		m_keyImage;
	CVGSection	m_sectionKey;
	CVGSection	m_sectionFine;
	CVGSection	m_sectionELevel;
	CVGSection	m_sectionDLevel;
	CVGEdit		m_mode;
	CVGKnob		m_shift[6];
	CVGKnob		m_harmo[6];
	CVGKnob		m_fine[6];
	CVGKnob		m_eLevel[6];
	CVGKnob		m_dLevel[6];

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelPitchShift();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPitchShift)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelFV :  public CPanel
{
public:
	CVGKnob	m_volumeKnob;
	CVGKnob	m_volume;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelFV)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	CPanelFV();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelFV)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelNS :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_nsImage;
	CVGKnob		m_threshold;
	CVGKnob		m_release;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelNS();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelNS)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelReverb :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_reverbImage;
	CVGEdit		m_mode;
	CVGKnob		m_density;
	CVGKnob		m_highCut;
	CVGKnob		m_lowCut;
	CVGKnob		m_preDly;
	CVGKnob		m_reverbTime;
	CVGKnob		m_revLev;
	
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelReverb();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelReverb)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelDelay :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_dlyImage;
	CVGKnob		m_dlyLev;
	CVGKnob		m_tapeTime;
	CVGKnob		m_feedback;
	CVGKnob		m_highCut;
	CVGKnob		m_dlyTime;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelDelay();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelDelay)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelChorus :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_chorusImage;
	CVGKnob		m_mode;
	CVGKnob		m_rate;
	CVGKnob		m_depth;
	CVGKnob		m_preDly;
	CVGKnob		m_highCut;
	CVGKnob		m_cLevel;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelChorus();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelChorus)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelCompressor :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_compImage;
	CVGEdit		m_mode;
	CVGKnob		m_sustain;
	CVGKnob		m_attack;
	CVGKnob		m_tone;
	CVGKnob		m_level;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelCompressor();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelCompressor)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelLimiter :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_limiterImage;
	CVGEdit		m_mode;
	CVGKnob		m_threshold;
	CVGKnob		m_release;
	CVGKnob		m_tone;
	CVGKnob		m_level;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelLimiter();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelLimiter)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




class CPanelPedalWah :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_pedalWahImage;
	CVGEdit		m_mode;
	CVGEdit		m_model;
	CVGKnob		m_freq;
	CVGKnob		m_level;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelPedalWah();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPedalWah)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelAutoWah :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_autoWahImage;
	CVGEdit		m_mode;
	CVGKnob		m_autoWahMode;
	CVGKnob		m_polarity;
	CVGKnob		m_sens;
	CVGKnob		m_freq;
	CVGKnob		m_peak;
	CVGKnob		m_rate;
	CVGKnob		m_depth;
	CVGKnob		m_level;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelAutoWah();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelAutoWah)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelVolBmpKey :  public CPanel
{
public:
	CVGKnob		m_level;
	CVGKnob		m_bmp;
	CVGEdit		m_key;
	CVGKnob		m_keyImage;

	CPanelVolBmpKey();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelVolBmpKey)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelVibrato :  public CPanel
{
public:
		CVGButton	m_ledOnOff;
		CVGKnob		m_vibratoImage;
		CVGEdit	m_mode;
		CVGKnob	m_trigger;
		CVGKnob	m_rate;
		CVGKnob	m_depth;
		CVGKnob	m_riseTime;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelVibrato();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelVibrato)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelTremolo :  public CPanel
{
public:
		CVGButton	m_ledOnOff;
		CVGKnob		m_tremoloImage;
		CVGEdit	m_mode;
		CVGKnob	m_wave;
		CVGKnob	m_rate;
		CVGKnob	m_depth;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelTremolo();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelTremolo)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelUniV :  public CPanel
{
public:
		CVGButton	m_ledOnOff;
		CVGKnob		m_univImage;
		CVGEdit	m_mode;
		CVGKnob	m_level;
		CVGKnob	m_rate;
		CVGKnob	m_depth;

	CPanelUniV();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelUniV)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelPdShift :  public CPanel
{
public:
		CVGButton	m_ledOnOff;
		CVGKnob		m_pdShiftImage;
		CVGEdit		m_modeType;
		CVGKnob		m_pitch;
		CVGKnob		m_mode;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelPdShift();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPdShift)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelPanEff :  public CPanel
{
public:
		CVGButton	m_ledOnOff;
		CVGKnob		m_panImage;
		CVGEdit	m_mode;
		CVGKnob	m_wave;
		CVGKnob	m_rate;
		CVGKnob	m_depth;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelPanEff();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPanEff)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelSubEq :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_eqImage;
	CVGKnob		m_labels;
	CVGEdit		m_mode;
	CVGKnob		m_level;
	CVGKnob		m_lowG;
	CVGKnob		m_hMidG;
	CVGKnob		m_lMidG;
	CVGKnob		m_highG;
	CVGKnob		m_lMidQ;
	CVGKnob		m_hMidQ;
	CVGKnob		m_hMidF;
	CVGKnob		m_lMidF;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelSubEq();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelSubEq)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanel2x2Chorus :  public CPanel
{
public:
		CVGButton	m_ledOnOff;
		CVGKnob		m_chorusImage;
		CVGSection	m_sectionLow;
		CVGSection	m_sectionHigh;
		CVGEdit		m_mode;
		CVGKnob		m_highDepth;
		CVGKnob		m_highLevel;
		CVGKnob		m_highPreDly;
		CVGKnob		m_highRate;
		CVGKnob		m_lowDepth;
		CVGKnob		m_lowLevel;
		CVGKnob		m_lowPreDly;
		CVGKnob		m_lowRate;
		CVGKnob		m_xOverf;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanel2x2Chorus();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanel2x2Chorus)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPanelPhaser :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_phaserImage;
	CVGEdit		m_mode;
	CVGKnob		m_rate;
	CVGKnob		m_depth;
	CVGKnob		m_manual;
	CVGKnob		m_reso;
	CVGKnob		m_level;
	CVGKnob		m_stage;
	CVGKnob		m_step;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelPhaser();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPhaser)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelDefretter :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_defretterImage;
	CVGEdit		m_mode;
	CVGKnob		m_sens;
	CVGKnob		m_attack;
	CVGKnob		m_depth;
	CVGKnob		m_reso;
	CVGKnob		m_tone;
	CVGKnob		m_elevel;
	CVGKnob		m_dlevel;

	CPanelPhaser();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPhaser)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelFlanger :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_flangerImage;
	CVGEdit		m_mode;
	CVGKnob		m_rate;
	CVGKnob		m_depth;
	CVGKnob		m_manual;
	CVGKnob		m_reso;
	CVGKnob		m_level;
	CVGKnob		m_separate;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelFlanger();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelFlanger)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelHarmonist :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_harmoImage;
	CVGEdit		m_mode;
	CVGSection	m_sectionHr1;
	CVGSection	m_sectionHr2;
	CVGKnob	    m_dirLevel;
	CVGKnob		m_hr1OnOff;
	CVGKnob		m_hr1UserScale[12];
	CVGKnob		m_hr1Harmony;
	CVGKnob		m_hr1Pan;
	CVGKnob		m_hr1Level;
	CVGKnob		m_hr2OnOff;
	CVGKnob		m_hr2UserScale[12];
	CVGKnob		m_hr2Harmony;
	CVGKnob		m_hr2Pan;
	CVGKnob		m_hr2Level;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelHarmonist();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelHarmonist)
	afx_msg int OnCreate (LPCREATESTRUCT);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPanelPickup :  public CPanel
{
public:
	CVGEdit		m_model;
	CVGKnob		m_modelImage;
	CVGKnob		m_level;
	CVGKnob		m_tone;
	CVGKnob		m_pickup;


	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelPickup();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPickup)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelSitar :  public CPanel
{
public:
	CVGEdit		m_pickup;
	CVGKnob		m_modelImage;
	CVGKnob		m_sens;
	CVGKnob		m_level;
	CVGKnob		m_tone;
	CVGKnob		m_body;
	CVGKnob		m_color;
	CVGKnob		m_decay;
	CVGKnob		m_buzz;
	CVGKnob		m_attackLevel;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelSitar();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelSitar)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelWave :  public CPanel
{
public:
	CVGEdit		m_shape;
	CVGKnob		m_modelImage;
	CVGKnob		m_sens;
	CVGKnob		m_attack;
	CVGKnob		m_decay;
	CVGKnob		m_level;
	CVGKnob		m_cutoff;
	CVGKnob		m_reso;
	CVGKnob		m_ftype;
	CVGKnob		m_fattack;
	CVGKnob		m_fdecay;
	CVGKnob		m_fdepth;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelWave();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelWave)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelPickupAcous :  public CPanel
{
public:
	CVGEdit		m_type;
	CVGKnob		m_typeImage;
	CVGKnob		m_level;
	CVGKnob		m_tone;

	CPanelPickupAcous();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPickupAcous)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelPickupNylon :  public CPanel
{
public:
	CVGKnob	m_nylonImage;
	CVGKnob	m_nylonImageII;

	CPanelPickupNylon();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPickupNylon)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelPickupVari :  public CPanel
{
public:
	CVGEdit		m_model;
	CVGPickupPos m_pickupPos;
	CVGSection	m_sectionRearPickup;
	CVGSection	m_sectionFrontPickup;
	CVGKnob		m_level;
	CVGKnob		m_tone;
	CVGKnob		m_pickup;
	CVGKnob		m_phase;
	CVGEdit		m_frontPickuType;
	CVGKnob		m_frontPickuTypeImage;
	CVGKnob		m_frontPickupPosition;
	CVGKnob		m_frontPickupAngle;
	CVGEdit		m_rearPickuType;
	CVGKnob		m_rearPickuTypeImage;
	CVGKnob		m_rearPickupPosition;
	CVGKnob		m_rearPickupAngle;

	CPanelPickupVari();
	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPickupVari)
	afx_msg int OnCreate (LPCREATESTRUCT);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelBody :  public CPanel
{
public:
	CVGKnob		m_attack;
	CVGKnob		m_body;
	CVGKnob		m_lowCut;
	CVGKnob		m_level;
	CVGEdit		m_bodyType;
	CVGKnob		m_bodyTypeImage;
	CVGKnob		m_size;
	CVGKnob		m_reso;
	
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);


	CPanelBody();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelBody)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelBodyNylon :  public CPanel
{
public:
	CVGKnob		m_size;
	CVGKnob		m_bottom;
	CVGKnob		m_reso;
	CVGKnob		m_level;
	
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelBodyNylon();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelBodyNylon)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelBodyNylonII :  public CPanel
{
public:
	CVGKnob		m_attack;
	CVGKnob		m_body;
	CVGKnob		m_tone;
	CVGKnob		m_level;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	CPanelBodyNylonII();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelBodyNylonII)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelCosmGT :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGEdit		m_cosmGtType;
	CVGKnob		m_cosmGtTypeImage;
		
	CPanelCosmGT();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelCosmGT)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelPShifter :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGSection	m_sectionPS1;
	CVGSection	m_sectionPS2;
	CVGKnob		m_pShifterImage;
	CVGEdit		m_mode;
	CVGKnob		m_dirLevel;
	CVGKnob		m_ps1Feedback;
	CVGKnob		m_ps1Fine;
	CVGKnob		m_ps1Level;
	CVGKnob		m_ps1Mode;
	CVGKnob		m_ps1OnOff;
	CVGKnob		m_ps1Pan;
	CVGKnob		m_ps1PreDly;
	CVGKnob		m_ps1Shift;
	CVGKnob		m_ps2Fine;
	CVGKnob		m_ps2Level;
	CVGKnob		m_ps2Mode;
	CVGKnob		m_ps2OnOff;
	CVGKnob		m_ps2Pan;
	CVGKnob		m_ps2PreDly;
	CVGKnob		m_ps2Shift;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	CPanelPShifter();
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPShifter)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelPolyOct :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGSection	m_section1Oct;
	CVGSection	m_section2Oct;
	CVGSection	m_sectionDir;
	CVGKnob		m_pedalImage;
	CVGKnob		m_1Oct[6];
	CVGKnob		m_2Oct[6];
	CVGKnob		m_dir[6];

	CPanelPolyOct();
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPolyOct)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelAssign :  public CPanel
{
public:
	int			m_assignNum;
	CVGButton	m_ledOnOff;
	CVGEdit		m_assignTarget;
	CVGKnob		m_assignMin1;
	CVGKnob		m_assignMax1;
	CVGKnob		m_assignMin2;
	CVGKnob		m_assignMax2;
	CVGKnob		m_assignMin3;
	CVGKnob		m_assignMax3;
	CVGKnob		m_assignMin4;
	CVGKnob		m_assignMax4;
	CVGKnob		m_assignMin5;
	CVGKnob		m_assignMax5;
	CVGKnob		m_assignMin6;
	CVGKnob		m_assignMax6;
	CVGEdit		m_assignSource;
	CVGKnob		m_assignSourceImagePedal;
	CVGKnob		m_assignSourceImageCtl;
	CVGKnob		m_assignSourceImageKGVol;
	CVGKnob		m_assignSourceImageGKS1S2;
	CVGKnob		m_assignSourceImageMidi;
	CVGKnob		m_assignMode;
	CVGSection	m_activeRange;
	CVGKnob		m_assignActiveRangeLo;
	CVGKnob		m_assignActiveRangeHi;

	CPanelAssign();
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	void SetAssignNum(int num);
	void ShowRightKnob(int value);
	void AttachVGData(CPatch *patch);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelAssign)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL


		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelAssign)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelAssignExp :  public CPanelAssign
{
public:
	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelAssignExp)
	protected:
	//}}AFX_VIRTUAL

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelAssignExp)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelAssignCtl :  public CPanelAssign
{
public:
	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelAssignCtl)
	protected:
	//}}AFX_VIRTUAL

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelAssignCtl)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelAssignGkVol :  public CPanelAssign
{
public:
	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelAssignGkVol)
	protected:
	//}}AFX_VIRTUAL

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelAssignGkVol)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPanelAssignGkS1S2 :  public CPanelAssign
{
public:
	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelAssignGkS1S2)
	protected:
	//}}AFX_VIRTUAL

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelAssignGkS1S2)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPanelOpenTune :  public CPanel
{
public:
	CVGButton		m_ledOnOff;
	CVGKnob			m_pedalImage;
	CVGEdit			m_type;
	CVGKnob			m_shift[6];
	CShiftString	m_shiftPreset[6];

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	void AttachVGData(CPatch *patch);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelOpenTune)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelOpenTune)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelDetune :  public CPanel
{
public:
	CVGButton		m_ledOnOff;
	CVGKnob			m_pedalImage;
	CVGKnob			m_detune;

	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelDetune)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPanelPDShift :  public CPanel
{
public:
	CVGButton		m_ledOnOff;
	CVGKnob			m_pedalImage;
	CVGKnob			m_pitch;
	CVGKnob			m_string[6];

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPDShift)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelOrgan :  public CPanel
{
public:
	CVGKnob	m_organImage;
	CVGKnob	m_feet4;
	CVGKnob	m_feet8;
	CVGKnob	m_feet16;
	CVGKnob	m_sustain;

	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);


		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelOrgan)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelDist :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGEdit		m_mode;
	CVGKnob		m_pedalImage;
	CVGKnob		m_drive;
	CVGKnob		m_highCut;
	CVGKnob		m_level;
	CVGKnob		m_polyBal;
	CVGKnob		m_drvBal;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelDist)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelPolyComp :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGEdit		m_mode;
	CVGKnob		m_pedalImage;
	CVGKnob		m_sustain;
	CVGKnob		m_attack;
	CVGKnob		m_tone;
	CVGKnob		m_level;
	CVGKnob		m_cmpBal;
	CVGKnob		m_threshold;
	CVGKnob		m_release;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPolyComp)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPanelPolySG :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_pedalImage;
	CVGKnob		m_riseTime;
	CVGKnob		m_sens;

	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);


		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPolySG)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelFilter :  public CPanel
{
public:
	CVGKnob	m_cutOff;
	CVGKnob	m_reso;
	CVGKnob	m_touchS;
	CVGKnob	m_decay;

	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelFilter)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelBowed :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGKnob	m_pBend;
	CVGKnob	m_pBendQ;
	CVGKnob	m_sustain;

	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);
	void AttachVGData(CPatch *patch);


		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelBowed)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelDual :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGKnob	m_gldSens;
	CVGKnob	m_gldTime;
	CVGKnob	m_sustain;

	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelDual)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPanelFilterBass :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGKnob	m_color;

	void AttachVGData(CPatch *patch);


		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelFilterBass)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelPipe :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGKnob	m_pBend;
	CVGKnob	m_pBendQ;
	CVGKnob	m_sustain;

	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPipe)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelSolo :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGKnob	m_color;
	CVGKnob	m_sustain;

	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelSolo)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelPWM :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGKnob	m_depth;
	CVGKnob	m_rate;
	CVGKnob	m_sustain;

	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelPWM)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelCrystal :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGKnob	m_length;
	CVGKnob	m_modTune;
	CVGKnob	m_level;
	CVGKnob	m_modeDep;
	CVGKnob	m_bodyLev;
	CVGKnob	m_sustain;

	void AttachVGData(CPatch *patch);
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelCrystal)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPanelBrass :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGKnob	m_sustain;

	void AttachVGData(CPatch *patch);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelBrass)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CPanelContrast :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGKnob	m_contrast;

	void AttachVGData(CSystem *system);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelContrast)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelGkFunction :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGEdit	m_downS1S2;
	CVGEdit	m_synthVol;

	void AttachVGData(CSystem *system);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelGkFunction)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelGlobal :  public CPanel
{
public:
	CVGButton	m_ledOnOff;
	CVGKnob		m_lowG;
	CVGKnob		m_highG;
	CVGKnob		m_NS;
	CVGKnob		m_reverb;

	void AttachVGData(CSystem *system);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelGlobal)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelTuner :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGKnob	m_pitch;
	CVGKnob	m_mute;

	void AttachVGData(CSystem *system);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelTuner)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelDial :  public CPanel
{
public:
	CVGKnob	m_image;
	CVGEdit	m_function;

	void AttachVGData(CSystem *system);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelDial)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelOutputSelect :  public CPanel
{
public:
	CVGKnob	m_outputImage;
	CVGEdit	m_output;

	void AttachVGData(CSystem *system);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelOutputSelect)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPanelDriverSetting :  public CPanel
{
public:
	CVGKnob		m_outputImage;
	CVGEdit		m_setting;
	CVGEdit		m_gkConnection;
	CVGSection	m_misc;
	CVGEdit		m_type;
	CVGKnob		m_direction;
	CVGKnob		m_gtPuPhase;
	CVGKnob		m_s1S2Pos;
	CVGKnob		m_scale;
	CVGSection	m_sensitivitySec;
	CVGSection	m_puBridgeSec;
	CVGKnob		m_sensitivity[6];
	CVGKnob		m_puBridge[6];

	void AttachVGData(CSystem *system);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPanelDriverSetting)
	afx_msg int OnCreate (LPCREATESTRUCT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
