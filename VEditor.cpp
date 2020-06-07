// VEditor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "tools.h"
#include "VEditor.h"
#include "VG-88.h"
#include "MainFrm.h"
#include "DeviceSetting.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool g_firstRun;

CMaskedBitmap g_down;
CMaskedBitmap g_up;
CMaskedBitmap g_pFileTop;
CMaskedBitmap g_pFileBot;
CMaskedBitmap g_pFileLeft;
CMaskedBitmap g_pFileRight;
CMaskedBitmap g_vg88Font;
CMaskedBitmap g_vg88FontBW;
CMaskedBitmap g_chain;
CMaskedBitmap g_chainSkin;
CMaskedBitmap g_digit;
CMaskedBitmap g_guitar[11];
CMaskedBitmap g_acoustic;
CMaskedBitmap g_acousticMic;
CMaskedBitmap g_nylon;
CMaskedBitmap g_nylonii;
CMaskedBitmap g_sitar;
CMaskedBitmap g_sitarp;
CMaskedBitmap g_solo;
CMaskedBitmap g_organ;
CMaskedBitmap g_pipe;
CMaskedBitmap g_crystal;
CMaskedBitmap g_bowed;
CMaskedBitmap g_comp[2];
CMaskedBitmap g_wah[2];
CMaskedBitmap g_amp[32];
CMaskedBitmap g_eq;
CMaskedBitmap g_fv;
CMaskedBitmap g_ns;
CMaskedBitmap g_mod[12];
CMaskedBitmap g_delay;
CMaskedBitmap g_chorus; 
CMaskedBitmap g_reverb;
CMaskedBitmap g_cable;
CMaskedBitmap g_cable2;
CMaskedBitmap g_cableCorner;
CMaskedBitmap g_cableInter;
CMaskedBitmap g_pickup;
CMaskedBitmap g_tune;
CMaskedBitmap g_detune;
CMaskedBitmap g_polySlowGear;
CMaskedBitmap g_polyOctave;
CMaskedBitmap g_polyDist[5];
CMaskedBitmap g_section;
CMaskedBitmap g_sEffAutoWah;
CMaskedBitmap g_sEffChorus;
CMaskedBitmap g_sEffComp;
CMaskedBitmap g_sEffDelay;
CMaskedBitmap g_sEffEq;
CMaskedBitmap g_sEffFlanger;
CMaskedBitmap g_sEffHarmo;
CMaskedBitmap g_sEffPan;
CMaskedBitmap g_sEffPedShift;
CMaskedBitmap g_sEffPedWah;
CMaskedBitmap g_sEffPhaser;
CMaskedBitmap g_sEffReverb;
CMaskedBitmap g_sEffVibrato;
CMaskedBitmap g_sEffUniV;
CMaskedBitmap g_sEffDefretter;
CMaskedBitmap g_sEffNS;
CMaskedBitmap g_eqLabel;
CMaskedBitmap g_guitarNylon;
CMaskedBitmap g_guitarNylonII;
CMaskedBitmap g_brassB;
CMaskedBitmap g_brass;
CMaskedBitmap g_wave;
CMaskedBitmap g_waveSaw;
CMaskedBitmap g_waveSquare;
CMaskedBitmap g_filterBassS;
CMaskedBitmap g_filterBassB;

CMaskedBitmap g_assignCtl;
CMaskedBitmap g_assignGKS1S2;
CMaskedBitmap g_assignGKVol;
CMaskedBitmap g_assignMidi;
CMaskedBitmap g_assignPedal;

CFont		  g_font1, g_font2, g_font3, g_font4, g_font5;
CImageList	*g_ImageList;

// Bitmap for panels and customs controls
CMaskedBitmap g_panel1;
CMaskedBitmap g_panelEmpty;
CMaskedBitmap g_panelBottom;

// Bitmap for controls
CMaskedBitmap  g_knob1;
CMaskedBitmap  g_knob2;
CMaskedBitmap  g_switch1;
CMaskedBitmap  g_faderv1;
CMaskedBitmap  g_faderh1;
CMaskedBitmap  g_knob3;
CMaskedBitmap  g_knob4;
CMaskedBitmap  g_wah2;
CMaskedBitmap  g_amplifers;
CMaskedBitmap  g_key;
CMaskedBitmap  g_knob6;
CMaskedBitmap  g_knob7;
CMaskedBitmap  g_selector;
CMaskedBitmap  g_guitars;
CMaskedBitmap  g_bodytype;
CMaskedBitmap  g_guitarsacous;
CMaskedBitmap  g_pickuptype1;
CMaskedBitmap  g_pickuptype2;
CMaskedBitmap  g_button1;
CMaskedBitmap  g_button2;
CMaskedBitmap  g_button3;
CMaskedBitmap  g_led1;
CMaskedBitmap  g_led2;
CMaskedBitmap  g_empty;
CMaskedBitmap  g_popup;
CMaskedBitmap  g_speaker;
CMaskedBitmap  g_mic1;
CMaskedBitmap  g_mic2;
CMaskedBitmap  g_organSlider;
CMaskedBitmap  g_organS;
CMaskedBitmap  g_effDist;
CMaskedBitmap  g_violon2;
CMaskedBitmap  g_trumpet2;
CMaskedBitmap  g_crystal2;
CMaskedBitmap  g_flute2;
CMaskedBitmap  g_labelPan;
CMaskedBitmap  g_dualS;
CMaskedBitmap  g_dualB;
CMaskedBitmap  g_ppwmS;
CMaskedBitmap  g_ppwmB;
CMaskedBitmap  g_lcd;
CMaskedBitmap  g_gkFunc;
CMaskedBitmap  g_dial;
CMaskedBitmap  g_tuner;
CMaskedBitmap  g_outputSelect;
CMaskedBitmap  g_gk2ab;
CMaskedBitmap  g_buttonSave;
CMaskedBitmap  g_buttonDelete;
CMaskedBitmap  g_buttonCopy;
CMaskedBitmap  g_buttonRename;

CPatch		*g_currentPatch;
int			g_currentPatchNumber;
CVG88SysEx	*g_currentLibrary;
CSystem		*g_currentSystem;

CSettings	g_settings;

/////////////////////////////////////////////////////////////////////////////
// CVEditorApp

BEGIN_MESSAGE_MAP(CVEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CVEditorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_APP_SETTINGS, OnAppSettings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVEditorApp construction

CVEditorApp::CVEditorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVEditorApp object

CVEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVEditorApp initialization

BOOL CVEditorApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("VG-Editor"));

	// Read the configuration file
	if (!g_settings.Read())
	{
		OnAppSettings();
		g_settings.generalSetting.isZoomed = TRUE;
		g_settings.generalSetting.x = 0;
		g_settings.generalSetting.y = 0;
		g_settings.generalSetting.cx = 800;
		g_settings.generalSetting.cy = 600;
		g_settings.Write();
		g_settings.generalSetting.chainWndVisible = TRUE;
		g_settings.generalSetting.libTreeWndVisible = TRUE;
		g_settings.generalSetting.patchWndVisible = TRUE;

		g_firstRun = TRUE;
	}
	else
		g_firstRun = FALSE;

	if (!g_settings.generalSetting.chainWndVisible && !g_settings.generalSetting.patchWndVisible)
	{
		g_settings.generalSetting.chainWndVisible = TRUE;
		g_settings.generalSetting.patchWndVisible = TRUE;
	}

	AfxOleInit();


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	pFrame->m_chainWndVisible = g_settings.generalSetting.chainWndVisible;
	pFrame->m_libTreeWndVisible = g_settings.generalSetting.libTreeWndVisible;
	pFrame->m_patchWndVisible = g_settings.generalSetting.patchWndVisible;

	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	pFrame->SetWindowPos(NULL, g_settings.generalSetting.x, g_settings.generalSetting.y, 
			g_settings.generalSetting.cx, g_settings.generalSetting.cy, SWP_NOOWNERZORDER);
	// The one and only window has been initialized, so show and update it.
	if (g_settings.generalSetting.isZoomed)
		pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	else
		pFrame->ShowWindow(SW_SHOWNORMAL);

	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVEditorApp message handlers


CVEditorApp::~CVEditorApp()
{
}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CVEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CVEditorApp message handlers

void CVEditorApp::OnAppSettings() 
{
	CDeviceSetting	deviceSettingDlg;

	if (g_settings.devices[0].type != DEVICE_NODEVICE)
	{
		deviceSettingDlg.m_deviceType = g_settings.devices[0].type - 1;
		deviceSettingDlg.m_deviceName = g_settings.devices[0].name;
		deviceSettingDlg.m_deviceID	  = g_settings.devices[0].deviceID;
		deviceSettingDlg.m_midiInput  = g_settings.devices[0].midiInputPort;
		deviceSettingDlg.m_midiOutput  = g_settings.devices[0].midiOutputPort;
		deviceSettingDlg.m_auditionPatch = g_settings.devices[0].auditionPatch;
	}
	else
	{
		deviceSettingDlg.m_deviceType = DEVICE_VG88 - 1;
		deviceSettingDlg.m_deviceName = "VG-88";
		deviceSettingDlg.m_deviceID	  = 1;
		deviceSettingDlg.m_midiInput  = -1;
		deviceSettingDlg.m_midiOutput  = -1;
		deviceSettingDlg.m_auditionPatch = -1;
	}

	if (deviceSettingDlg.DoModal() == IDOK)
	{
		g_settings.devices[0].type			 = deviceSettingDlg.m_deviceType + 1;
		strcpy(g_settings.devices[0].name, deviceSettingDlg.m_deviceName.GetBuffer(31));
		g_settings.devices[0].deviceID		 = deviceSettingDlg.m_deviceID;
		g_settings.devices[0].midiInputPort	 = deviceSettingDlg.m_midiInput;
		g_settings.devices[0].midiOutputPort = deviceSettingDlg.m_midiOutput;	
		g_settings.devices[0].auditionPatch = deviceSettingDlg.m_auditionPatch;	

		g_settings.devicesCount = 1;

		g_settings.Write();

		if (AfxGetMainWnd())
			((CMainFrame *) AfxGetMainWnd())->OpenMidiPort(0);
	}
}

BOOL CVEditorApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}
