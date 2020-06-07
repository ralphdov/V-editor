// MainFrm.cpp : implementation of the CMainFrame class
//

#include <stdio.h>
#include <io.h>
#include "stdafx.h"
#include "midi.h"
#include "VEditor.h"
#include "tools.h"
#include "MainFrm.h"
#include "Splash.h"
#include "LibProp.h"
#include "SendPatchForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_LIBTREE, OnLibtree)
	ON_COMMAND(ID_CHAIN, OnChain)
	ON_COMMAND(ID_PATCHEDIT, OnPatchedit)
	ON_COMMAND(ID_CASCAD, Cascade)
	ON_COMMAND(ID_TILEH, TileH)
	ON_COMMAND(ID_TILEV, TileV)
	ON_COMMAND(ID_SAVE, Save)
	ON_COMMAND(ID_SAVEAS, SaveAs)
	ON_COMMAND(ID_SAVE_ALL, SaveAll)
	ON_COMMAND(ID_OPEN, Open)
	ON_COMMAND(ID_EDIT_COPY, Copy)
	ON_COMMAND(ID_ORDER, Order)
	ON_COMMAND(ID_EDIT_CUT, Cut)
	ON_COMMAND(ID_EDIT_PASTE, Paste)
	ON_COMMAND(ID_NEW, New)
	ON_COMMAND(ID_SEND, Send)
	ON_COMMAND(ID_CLOSE, Close)
	ON_COMMAND(ID_SEND_ONE_PATCH, SendOnePatch)
	ON_COMMAND(ID_RECEIVE, Receive)
	ON_COMMAND(ID_SYNCHRONIZE, Synchronize)
	ON_COMMAND(ID_PROPERTIES, Properties)
	ON_COMMAND(ID_OPENVGWINDOW, OpenVgWindow)
	ON_WM_CHAR()
	ON_MESSAGE(WM_MIDI_PATCH_CHANGE, OnMidiPatchChange)
	ON_MESSAGE(WM_MIDI_PATCH_RECEIVED, OnMidiPatchReceived)
	ON_MESSAGE(WM_CHECK_LIBRARY_WINDOW, OnCheckLibraryWindows)
	ON_MESSAGE(WM_FIRSTRUN, OnFirstRun)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CMainFrame::Properties()
{
	CLibProp prop;

	if (!g_currentLibrary)
		return;

	prop.m_file = g_currentLibrary->file;
	prop.m_firstPatch = g_currentLibrary->firstPatchNumber;
	prop.m_libraryName = g_currentLibrary->GetLibraryName();

	if (prop.DoModal() == IDOK && g_currentLibrary->libraryType != LIB_PRESET && g_currentLibrary->libraryType != LIB_USER)
	{
		HTREEITEM item;

		if (prop.m_firstPatch != g_currentLibrary->firstPatchNumber)
		{
			char label[256];
			int i = 0;

			g_currentLibrary->firstPatchNumber = prop.m_firstPatch;

			item = g_currentLibrary->GetTreeItem();

			item = m_libTreeWnd.m_libraryTree.GetChildItem(item);

			while (item)
			{
				g_currentLibrary->getPatchLabel(i++, label);
				m_libTreeWnd.m_libraryTree.SetItemText(item, label);

				item = m_libTreeWnd.m_libraryTree.GetNextItem(item, TVGN_NEXT);
			}
		}

		char newName[_MAX_PATH];
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];

		_splitpath(g_currentLibrary->file, drive, dir, fname, ext);
		_makepath(newName, drive, dir, prop.m_libraryName, "syx" );
		item = g_currentLibrary->GetTreeItem();

		if (rename(g_currentLibrary->file, newName) == 0)
		{
			m_libTreeWnd.m_libraryTree.SetItemText(item, prop.m_libraryName);
			g_currentLibrary->file = newName;
		}
		else
			MessageBox("Unable to rename the library");
	}
}


void CMainFrame::Synchronize()
{
	HTREEITEM item, lastItem;
	CTreeCtrl *tree;
	CVG88SysEx *library;
	CVGWindow *vgWindow;

	Receive();

	if (!m_sendPatchCanceled)
	{
		tree = &m_libTreeWnd.m_libraryTree;
		item = tree->GetRootItem();
		lastItem = NULL;

		while (item)
		{
			lastItem = item;
			item = tree->GetNextItem(item, TVGN_NEXT);
		}

		if (lastItem)
		{
			library = (CVG88SysEx *) tree->GetItemData(lastItem);

			UpdateUserLibrary(0, library->patchList.GetCount() - 1, library->firstPatchNumber, library);
			tree->DeleteItem(lastItem);

			vgWindow = (CVGWindow *) library->data1;
			vgWindow->PostMessage(WM_CLOSE);
			PostMessage(WM_CHECK_LIBRARY_WINDOW);

			delete library;
		}

		MessageBox("VEditor is now synchronized with your VG-88", "VEditor", MB_ICONINFORMATION);
	}
	else
	{
		m_wndVGWindow->PostMessage(WM_CLOSE);
		PostMessage(WM_CHECK_LIBRARY_WINDOW);
	}
}


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	KillTimer(123);
	midiInUnprepareHeader(m_hmi[0], &m_midiHdr, sizeof(MIDIHDR));
	
	if (!m_sendPatchDlg.m_cancel)
		m_sendPatchDlg.Close();

	InsertLibrary(m_wndVGWindow->m_library);

	CFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::OnMidiPatchReceived(WPARAM wParam, LPARAM lParam)
{
	char *buffer;
	KillTimer(123);

	m_sendPatchDlg.SetWindowText("Receiving...");
	m_midiInSize += m_midiHdr.dwBytesRecorded;

	midiInUnprepareHeader(m_hmi[0], &m_midiHdr, sizeof(MIDIHDR));

	buffer = m_midiHdr.lpData;

	char addressMSBHigh = buffer[6];
	char addressMSBLow  = buffer[7];
	char addressLSBHigh = buffer[8];
	char addressLSBLow  = buffer[9];

	//if (m_midiInCount % 6 == 0)
	if (buffer[0] == '\xF0' && addressMSBHigh == '\x0C' && addressLSBHigh == 5)
	{
		POSITION	position;
		int			numPatch;
		int			patchCount;
		CPatch		*patch;
		CString		file;
		int			i;
		char *buffer = m_midiInBuffer;
		m_midiInBuffer[m_midiInSize] = 0;
		m_midiInCount++;

		m_sendPatchDlg.SetInfo("", m_midiInCount, 100);

		file = m_wndVGWindow->m_library->file;
		delete m_wndVGWindow->m_library;
		CVG88SysEx *library = new CVG88SysEx;
		library->file = file;
		library->data1 = m_wndVGWindow;
		m_wndVGWindow->m_library = library;
		library->setVGData(&buffer);

		patchCount = library->patchList.GetCount();
		position = library->patchList.GetHeadPosition();
		numPatch = library->firstPatchNumber;

		for (i = 0; i < patchCount; i++)
		{
			patch = (CPatch *) library->patchList.GetNext(position);

			if (i == patchCount - 1)
				m_wndVGWindow->InsertItem(patch, i, numPatch + i);
		}
	}

	SetTimer(123, 1000, NULL);

	if (m_sendPatchDlg.m_cancel)
		return;

	m_midiHdr.lpData = &m_midiInBuffer[m_midiInSize];
	m_midiHdr.dwBufferLength = 175000 - m_midiInSize;
	m_midiHdr.dwFlags  = 0;
	midiInPrepareHeader(m_hmi[0], &m_midiHdr, sizeof(MIDIHDR));

	midiInAddBuffer(m_hmi[0], &m_midiHdr, sizeof(MIDIHDR));
}


void CMainFrame::Receive()
{
	m_midiHdr.lpData = m_midiInBuffer;
	m_midiHdr.dwBufferLength = 175000;
	m_midiHdr.dwFlags  = 0;
	midiInPrepareHeader(m_hmi[0], &m_midiHdr, sizeof(MIDIHDR));
	m_midiInCount = 0;
	m_midiInSize = 0;

	CVG88SysEx *library = new CVG88SysEx;
	library->data1 = m_wndVGWindow;
	m_newLibraryCounter++;
	library->file.Format("patch\\Library%d.syx", m_newLibraryCounter);
	m_wndVGWindow = OpenLibraryWindow(library);

	midiInAddBuffer(m_hmi[0], &m_midiHdr, sizeof(MIDIHDR));

	m_sendPatchDlg.m_modeReceive = TRUE;
	m_sendPatchDlg.DoModal();

	if (m_sendPatchCanceled && m_wndVGWindow->m_library->patchList.GetCount() == 0)
	{
		m_wndVGWindow->PostMessage(WM_CLOSE);
		PostMessage(WM_CHECK_LIBRARY_WINDOW);
	}
}


void CMainFrame::OnMidiPatchChange(WPARAM wParam, LPARAM lParam)
{
	int i;
	int offset = 0;
	CVG88SysEx *ptrLibrary;
	HTREEITEM item;
	WORD bank = LOWORD(lParam);
	WORD patchNumber = HIWORD(lParam);

	if (bank >= 1)
	{
		patchNumber = (100 * (bank - 1)) + patchNumber;
		offset = 100;

		item = m_libTreeWnd.m_libraryTree.GetRootItem();
		item = m_libTreeWnd.m_libraryTree.GetNextSiblingItem(item);
		item = m_libTreeWnd.m_libraryTree.GetChildItem(item);
	}
	else
	{
		item = m_libTreeWnd.m_libraryTree.GetRootItem();
		item = m_libTreeWnd.m_libraryTree.GetChildItem(item);

	}

	ptrLibrary = (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData(m_libTreeWnd.m_libraryTree.GetParentItem(item));

	if (ptrLibrary->vgSystem)
		patchNumber++;

	for (i = ptrLibrary->firstPatchNumber - offset; i < patchNumber; i++)
			item = m_libTreeWnd.m_libraryTree.GetNextSiblingItem(item);

	m_libTreeWnd.m_libraryTree.SelectItem(item);
}



/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_tileType = MDITILE_VERTICAL;
	m_newLibraryCounter = 0;
	m_copyBuffer[0] = 0;
	m_copyCount = 0;
	g_currentPatch = NULL;
	g_currentLibrary = NULL;
	g_currentSystem = NULL;
}


CMainFrame::~CMainFrame()
{
	CVG88SysEx	*VG88Lib;
	int i;
	int count = m_VG88Lib.GetCount();

	for (i = 0; i < count; i++)
	{
		VG88Lib = (CVG88SysEx *) m_VG88Lib.RemoveHead();

		delete VG88Lib;
	}

	for (i = 0; i < g_settings.devicesCount; i++)
		CloseMidiPort(i);
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int i;
	CVG88SysEx* VG88User;

	// Create the toolbar
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetButtonStyle(13, TBBS_CHECKBOX);
	m_wndToolBar.SetButtonStyle(14, TBBS_CHECKBOX);
	m_wndToolBar.SetButtonStyle(15, TBBS_CHECKBOX);

	if (m_libTreeWndVisible)
		m_wndToolBar.GetToolBarCtrl().CheckButton(ID_LIBTREE, TRUE);

	if (m_chainWndVisible)
		m_wndToolBar.GetToolBarCtrl().CheckButton(ID_CHAIN, TRUE);

	if (m_patchWndVisible)
		m_wndToolBar.GetToolBarCtrl().CheckButton(ID_PATCHEDIT, TRUE);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	g_down.LoadBitmap (IDB_DOWN);
	g_up.LoadBitmap (IDB_UP);
	g_pFileTop.LoadBitmap (IDB_PFILETOP);
	g_pFileBot.LoadBitmap (IDB_PFILEBOT);
	g_pFileLeft.LoadBitmap (IDB_PFILELEFT);
	g_pFileRight.LoadBitmap (IDB_PFILERIGHT);
	g_vg88Font.LoadBitmap (IDB_VG88FONT);
	g_vg88FontBW.LoadBitmap (IDB_VGFONTBW);
	g_chain.LoadBitmap (IDB_CHAIN);
	g_chainSkin.Attach(::LoadImage(AfxGetInstanceHandle(), "skin\\chain_woo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));

	for (i = IDB_LP; i <= IDB_VARIGUITAR; i++)
		g_guitar[i - IDB_LP].LoadBitmap(i);

	g_acoustic.LoadBitmap (IDB_ACOUSPIEZO);
	g_acousticMic.LoadBitmap (IDB_ACOUSMIC);
	g_nylon.LoadBitmap (IDB_NYLONB);

	g_nylonii.LoadBitmap (IDB_NYLONIIB);
	g_sitar.LoadBitmap (IDB_SITARB);
	g_sitarp.LoadBitmap (IDB_SITARP);

	g_bowed.LoadBitmap (IDB_BOWED);
	g_crystal.LoadBitmap (IDB_CRYSTALB);
	g_solo.LoadBitmap (IDB_SOLO);
	g_organ.LoadBitmap (IDB_ORGANB);
	g_pipe.LoadBitmap (IDB_PIPE);
	g_brassB.LoadBitmap (IDB_BRASSB);
	g_brass.LoadBitmap (IDB_BRASS);
	g_wave.LoadBitmap (IDB_WAVE);
	g_waveSaw.LoadBitmap (IDB_WAVESAW);
	g_waveSquare.LoadBitmap (IDB_WAVESQUARE);
	g_filterBassS.LoadBitmap (IDB_FILTERBASSS);
	g_filterBassB.LoadBitmap (IDB_FILTERBASSB);


	for (i = IDB_AMPJC120; i <= IDB_AMPMETALLEAD; i++)
		g_amp[i - IDB_AMPJC120].LoadBitmap(i);

	g_digit.LoadBitmap (IDB_DIGIT);

	g_comp[0].LoadBitmap(IDB_EFFCOMPRESSOR);
	g_comp[1].LoadBitmap(IDB_EFFLIMITER);
	g_wah[0].LoadBitmap(IDB_EFFWAH);
	g_wah[1].LoadBitmap(IDB_EFFAUTOWAH);

	g_eq.LoadBitmap(IDB_EFFEQ);
	g_fv.LoadBitmap(IDB_EFFFV);
	g_ns.LoadBitmap(IDB_EFFNS);

	for (i = IDB_EFFHARMONIST; i <= IDB_EFFUNIV; i++)
		g_mod[i - IDB_EFFHARMONIST].LoadBitmap(i);

	g_delay.LoadBitmap(IDB_EFFDELAY);
	g_chorus.LoadBitmap(IDB_EFFCHORUS); 
	g_reverb.LoadBitmap(IDB_EFFREVERB);

	g_tune.LoadBitmap(IDB_TUNE);
	g_detune.LoadBitmap(IDB_DETUNE);
	g_polySlowGear.LoadBitmap(IDB_SLOWGEAR);
	g_polyOctave.LoadBitmap(IDB_POLYOCTAVE);

	for (i = IDB_DISTCLAOD; i <= IDB_DISTFUZZ; i++)
		g_polyDist[i - IDB_DISTCLAOD].LoadBitmap(i);

	g_cable.LoadBitmap(IDB_CABLE);
	g_cable2.LoadBitmap(IDB_CABLE2);
	g_cableCorner.LoadBitmap(IDB_CABLECORNER);
	g_cableInter.LoadBitmap(IDB_CABLEINTER);



	// Load bitmaps for controls
	g_knob1.LoadBitmap(IDB_KNOB1);
	g_knob2.LoadBitmap(IDB_KNOB2);
	g_switch1.LoadBitmap(IDB_SWITCH1);
	g_faderv1.LoadBitmap(IDB_FADERV1);
	g_faderh1.LoadBitmap(IDB_FADERH1);
	g_knob3.LoadBitmap(IDB_KNOB3);
	g_knob4.LoadBitmap(IDB_KNOB4);
	g_wah2.LoadBitmap(IDB_WAH2);
	g_amplifers.LoadBitmap(IDB_AMPLIFERS);
	g_key.LoadBitmap(IDB_KEY);
	g_knob6.LoadBitmap(IDB_KNOB6);
	g_knob7.LoadBitmap(IDB_KNOB7);
	g_selector.LoadBitmap(IDB_SELECTOR);
	g_guitars.LoadBitmap(IDB_GUITARS);
	g_bodytype.LoadBitmap(IDB_BODYTYPE);
	g_guitarsacous.LoadBitmap(IDB_GUITARSACOUS);
	g_pickuptype1.LoadBitmap(IDB_PICKUPTYPE1);
	g_pickuptype2.LoadBitmap(IDB_PICKUPTYPE2);
	g_button1.LoadBitmap(IDB_BUTTON1);
	g_button2.LoadBitmap(IDB_BUTTON2);
	g_button3.LoadBitmap(IDB_BUTTON3);
	g_led1.LoadBitmap(IDB_LED1);
	g_led2.LoadBitmap(IDB_LED2);
	g_section.LoadBitmap(IDB_SECTION);

	g_sEffAutoWah.LoadBitmap(IDB_SEFFAUTOWAH);
	g_sEffChorus.LoadBitmap(IDB_SEFFCHORUS);
	g_sEffComp.LoadBitmap(IDB_SEFFCOMP);
	g_sEffDelay.LoadBitmap(IDB_SEFFDELAY);
	g_sEffEq.LoadBitmap(IDB_SEFFEQ);
	g_sEffFlanger.LoadBitmap(IDB_SEFFFLANGER);
	g_sEffHarmo.LoadBitmap(IDB_SEFFHARMO);
	g_sEffPan.LoadBitmap(IDB_SEFFPAN);
	g_sEffPedShift.LoadBitmap(IDB_SEFFPEDSHIFT);
	g_sEffPedWah.LoadBitmap(IDB_SEFFPEDWAH);
	g_sEffPhaser.LoadBitmap(IDB_SEFFPHASER);
	g_sEffReverb.LoadBitmap(IDB_SEFFREVERB);
	g_sEffVibrato.LoadBitmap(IDB_SEFFVIBRATO);
	g_sEffUniV.LoadBitmap(IDB_SEFFUNIV);
	g_sEffDefretter.LoadBitmap(IDB_SEFFDEFRETTER);
	g_sEffNS.LoadBitmap(IDB_SEFFNS);
	g_eqLabel.LoadBitmap(IDB_EQLABEL);
	g_guitarNylon.LoadBitmap(IDB_GUITARNYLON);
	g_guitarNylonII.LoadBitmap(IDB_GUITARNYLONII);

	g_assignCtl.LoadBitmap(IDB_ASSIGNCTL);
	g_assignGKS1S2.LoadBitmap(IDB_ASSIGNGKS1S2);
	g_assignGKVol.LoadBitmap(IDB_ASSIGNGKVOL);
	g_assignMidi.LoadBitmap(IDB_ASSIGNMIDI);
	g_assignPedal.LoadBitmap(IDB_ASSIGNPEDAL);

	g_pickup.LoadBitmap(IDB_PICKUP);
	g_panel1.LoadBitmap(IDB_PANEL1);
	g_panelEmpty.LoadBitmap(IDB_PANELEMPTY);
	g_panelBottom.LoadBitmap(IDB_PANELBOTTOM);
	g_empty.LoadBitmap(IDB_EMPTY);
	g_popup.LoadBitmap(IDB_POPUP);
	g_speaker.LoadBitmap(IDB_SPEAKER);

	g_mic1.LoadBitmap(IDB_MIC1);
	g_mic2.LoadBitmap(IDB_MIC2);

	g_organSlider.LoadBitmap(IDB_ORGANSLIDER);
	g_organS.LoadBitmap(IDB_ORGANS);
	g_effDist.LoadBitmap(IDB_EFFDIST);

	g_violon2.LoadBitmap(IDB_VIOLON2);
	g_trumpet2.LoadBitmap(IDB_TRUMPET2);
	g_crystal2.LoadBitmap(IDB_CRYSTAL2);
	g_flute2.LoadBitmap(IDB_FLUTE2);

	g_labelPan.LoadBitmap(IDB_LABELPAN);

	g_dualS.LoadBitmap(IDB_DUALS);
	g_dualB.LoadBitmap(IDB_DUALB);
	g_ppwmS.LoadBitmap(IDB_PPWM);
	g_ppwmB.LoadBitmap(IDB_PPWMB);
	g_lcd.LoadBitmap(IDB_LCD);
	g_gkFunc.LoadBitmap(IDB_GKFUNC);
	g_dial.LoadBitmap(IDB_DIAL);
	g_tuner.LoadBitmap(IDB_TUNER);
	g_outputSelect.LoadBitmap(IDB_OUTPUTSELECT);
	g_gk2ab.LoadBitmap(IDB_GK2AB);
	g_buttonSave.LoadBitmap(IDB_BUTTONSAVE);
	g_buttonDelete.LoadBitmap(IDB_BUTTONDELETE);
	g_buttonRename.LoadBitmap(IDB_BUTTONRENAME);
	g_buttonCopy.LoadBitmap(IDB_BUTTONCOPY);

	UINT			nID;
	CMaskedBitmap	bitmap;


	// Create the Image List of the treeCtrl
	g_ImageList = new CImageList();
	
	g_ImageList->Create(16, 16, ILC_COLOR24, 6, 4);


	for (nID = IDB_GUITAR; nID <= IDB_GK2A; nID++)
	{
		if (nID == IDB_OPENTUNE || nID == IDB_12STRINGS || nID == IDB_PDSHIFT || nID == IDB_POLYDIST || nID == IDB_POLYCOMP || nID == IDB_POLYOCT || nID == IDB_POLYSG) 
			bitmap.LoadBitmap(IDB_GUITAR);
		else if (nID == IDB_BRASS || nID == IDB_PWM || nID == IDB_DUAL || nID == IDB_WAVESYNTH || nID == IDB_FILTEBASS)
			bitmap.LoadBitmap(IDB_ORGAN);
		else
			bitmap.LoadBitmap(nID);

		g_ImageList->Add(&bitmap, (CMaskedBitmap *) NULL);
		bitmap.DeleteObject();
	}


	// Load fonts
/*	g_font1.CreateFont (12, 0, 0, 0, FW_HEAVY,
            0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
            FF_DONTCARE, "Arial");
*/
	g_font1.CreateFont (10, 0, 0, 0, FW_NORMAL,
            0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
            FF_DONTCARE, "Arial");

	g_font2.CreateFont (12, 0, 0, 0, FW_MEDIUM,
            0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
            FF_DONTCARE, "Arial");

	g_font3.CreateFont (10, 0, 0, 0, FW_EXTRABOLD,
            0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
            FF_DONTCARE, "Arial");

	g_font4.CreateFont (14, 0, 0, 0, FW_MEDIUM,
            0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
            FF_DONTCARE, "Arial");

	g_font5.CreateFont (14, 0, 0, 0, FW_EXTRABOLD,
            0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH |
            FF_DONTCARE, "Arial");

	// create the Library Tree Window
	if (!m_libTreeWnd.Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS    | (WS_VISIBLE * m_libTreeWndVisible),
		CRect(0, 50, 0, 0), this, IDW_LIBTREEWND, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Load all the libraries in the library directorie

	int loop;
	char fileName[100];
	struct _finddata_t c_file;
    long hFile;

	VG88User = LoadLibrary("sys\\VG88U.syx");
	LoadLibrary("sys\\VG88P.syx");

    // Find first .c file in current directory 
    hFile = _findfirst( "Patch\\*.syx", &c_file );

	if (hFile != -1L)
		loop = 0;
	else
		loop = 1;

	while(loop == 0)
	{
		sprintf(fileName, "Patch\\%s", c_file.name);
		LoadLibrary(fileName);

		loop = _findnext( hFile, &c_file );
	}

	_findclose( hFile );


	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create the Chain Window
	if (!m_chainWnd.Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS | (WS_VISIBLE * m_chainWndVisible),
		CRect(0, 50, 0, 0), this, IDW_CHAINWND, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// create the patch Window
	if (!m_patchWnd.Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS  | (WS_VISIBLE * m_patchWndVisible),
		CRect(400, 400, 450, 450), this, IDW_PATCHWND, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	// Create the workspace
	if (!m_wksView.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED,
		CRect(0, 50, 0, 0), this, IDW_WKSVIEW, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}


	// Open Midi ports
	for (i = 0; i < g_settings.devicesCount; i++)
		OpenMidiPort(i);

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);

	if (m_libTreeWndVisible)
		GetMenu()->CheckMenuItem(ID_LIBTREE, MF_CHECKED);
	else
		GetMenu()->CheckMenuItem(ID_LIBTREE, MF_UNCHECKED);

	if (m_chainWndVisible)
		GetMenu()->CheckMenuItem(ID_CHAIN, MF_CHECKED);
	else
		GetMenu()->CheckMenuItem(ID_CHAIN, MF_UNCHECKED);

	if (m_patchWndVisible)
		GetMenu()->CheckMenuItem(ID_PATCHEDIT, MF_CHECKED);
	else
		GetMenu()->CheckMenuItem(ID_PATCHEDIT, MF_UNCHECKED);

	PostMessage(WM_FIRSTRUN);


	_fullpath(c_file.name, "", _MAX_PATH ) ;
	m_editorPath = CString(c_file.name);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0, AfxGetApp()->LoadCursor(IDC_CURSOR), HBRUSH(COLOR_APPWORKSPACE + 1), AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	return TRUE;
}


int CMainFrame::InsertLibrary(CVG88SysEx *library, CVG88SysEx *oldLibrary)
{
	CFileException		e;
	CFile				file;
	TV_INSERTSTRUCT		curTreeItem;
	POSITION			position;
	CString				str;
	HTREEITEM			hTreeItem, hTreeItemOld;
	CPatch				*patch;
	int					i;
	int					numPatch;
	int					patchCount;
	char				patchName[32];
	bool				expand = false;

	// Add the library at the end of the TreeCtrl


	m_libTreeWnd.m_libraryTree.SendMessage(WM_SETREDRAW, FALSE, 0);

	if (oldLibrary)
	{
		hTreeItemOld = m_libTreeWnd.m_libraryTree.GetRootItem();

		while (hTreeItemOld && m_libTreeWnd.m_libraryTree.GetItemData(hTreeItemOld) != (unsigned long) oldLibrary)
			hTreeItemOld = m_libTreeWnd.m_libraryTree.GetNextItem(hTreeItemOld, TVGN_NEXT);

		expand = (bool) (m_libTreeWnd.m_libraryTree.GetItemState(hTreeItemOld, TVIF_STATE) & TVIS_EXPANDED);
	}

	// Parent Item 
	curTreeItem.hParent = NULL;

	if (hTreeItemOld)
		curTreeItem.hInsertAfter = hTreeItemOld;
	else
		curTreeItem.hInsertAfter = TVI_LAST;

	if (strcmp(library->file, "sys\\VG88P.syx") == 0)
	{
		char buffer[255];

		library->libraryType = LIB_PRESET;
		curTreeItem.item.iImage = COSMGT_TYPE_COUNT;
		curTreeItem.item.iSelectedImage = COSMGT_TYPE_COUNT;

		sprintf(buffer, "%s PRESET", g_settings.devices[0].name);
		curTreeItem.item.pszText = buffer;
		library->firstPatchNumber = 100;
	}
	else if (strcmp(library->file, "sys\\VG88U.syx") == 0)
	{
		char buffer[255];

		library->libraryType = LIB_USER;
		curTreeItem.item.iImage = COSMGT_TYPE_COUNT;
		curTreeItem.item.iSelectedImage = COSMGT_TYPE_COUNT;

		sprintf(buffer, "%s USER", g_settings.devices[0].name);
		curTreeItem.item.pszText = buffer;
	}
	else
	{
		library->libraryType = LIB_FILE;
		curTreeItem.item.iImage = COSMGT_TYPE_COUNT + 1;
		curTreeItem.item.iSelectedImage = COSMGT_TYPE_COUNT + 1;
		curTreeItem.item.pszText = (library->GetLibraryName()).GetBuffer(1);
	}

	if (library->modified)
		strcat(curTreeItem.item.pszText, "  ( Modified )");


	curTreeItem.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	curTreeItem.item.lParam = (LPARAM) library;

	hTreeItem = m_libTreeWnd.m_libraryTree.InsertItem(&curTreeItem);

	if (hTreeItemOld)
		m_libTreeWnd.m_libraryTree.DeleteItem(hTreeItemOld);


	// add an item for system data if present
	if (library->vgSystem)
	{
		curTreeItem.hParent = hTreeItem;
		curTreeItem.hInsertAfter = TVI_LAST;
		curTreeItem.item.iImage = COSMGT_TYPE_COUNT + 2;
		curTreeItem.item.iSelectedImage = COSMGT_TYPE_COUNT + 2;
		curTreeItem.item.pszText = "SYSTEM";
		curTreeItem.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM ;
		curTreeItem.item.lParam = (LPARAM) library->vgSystem;

		m_libTreeWnd.m_libraryTree.InsertItem(&curTreeItem);
	}

	// add an item for each patch
	patchCount = library->patchList.GetCount();
	position = library->patchList.GetHeadPosition();

	numPatch = library->firstPatchNumber;

	for (i = 0; i < patchCount; i++)
	{
		patch = (CPatch *) library->patchList.GetNext(position);
		patch->assignNC.name.getString(patchName);

		str.Format("%2d - %d    %s", (char)((numPatch + i) / 4) + 1, (char)((numPatch + i) % 4) + 1, patchName);
		curTreeItem.hParent = hTreeItem;
		curTreeItem.hInsertAfter = TVI_LAST;
		curTreeItem.item.iImage = patch->cosmGT.guitarType.getValue();
		curTreeItem.item.iSelectedImage = patch->cosmGT.guitarType.getValue();
		curTreeItem.item.pszText = str.GetBuffer(str.GetLength()); 
		curTreeItem.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM ;
		curTreeItem.item.state = TVIS_DROPHILITED ;
		curTreeItem.item.stateMask = TVIS_DROPHILITED ;
		curTreeItem.item.lParam = (LPARAM) patch;

		m_libTreeWnd.m_libraryTree.InsertItem(&curTreeItem);
	}

	if (expand)
		m_libTreeWnd.m_libraryTree.Expand(hTreeItem, TVE_EXPAND);

	m_libTreeWnd.m_libraryTree.SendMessage(WM_SETREDRAW, TRUE, 0);

	return 0;
}



CVG88SysEx* CMainFrame::LoadLibrary(LPCTSTR lpFileName, CVG88SysEx *VG88Old)
{
	CFileException		e;
	CFile				file;
	CVG88SysEx			*VG88;
	POSITION			position;
	CString				str;
	char				buffer[175000];
	char				*posBuffer;
	int					ret;
	
	
	// If the library is aleady loaded, we have to reload it
	// Find in the list the old library
	if (VG88Old)
	{
		position = m_VG88Lib.Find(VG88Old);

		if (!position)
			return NULL;
	}
	else
		position = NULL;


	// Open the file
	if (!file.Open(lpFileName, CFile::modeRead, &e))
	{
		MessageBox((char *) e.m_cause);

		return NULL;
	}

	// Read the entire content of the file
	ret = file.Read(buffer, 175000);
	buffer[ret] = 0;
	file.Close();


	// Create a new library object and add it to library list
    VG88 = new CVG88SysEx;

	VG88->newLibrary = FALSE;
	VG88->modified = FALSE;

	if (VG88Old)
		m_VG88Lib.SetAt(position, VG88);
	else
		m_VG88Lib.AddTail(VG88);

	VG88->file = lpFileName;

	// Extract VG data from the buffer
	posBuffer = buffer;
	VG88->setVGData(&posBuffer);

	InsertLibrary(VG88, VG88Old);

	if (VG88Old)
		delete VG88Old;

	return VG88;
}



/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_libTreeWnd.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	//if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	//	return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	RECT rect, rect2;
	int width;
	int chainwnd_height;
	

	CFrameWnd::OnSize(nType, cx, cy);

	if (m_libTreeWndVisible)
		m_libTreeWnd.ShowWindow(SW_SHOWNA);
	else
		m_libTreeWnd.ShowWindow(SW_HIDE);

	if (m_chainWndVisible)
	{
		chainwnd_height = 313;
		m_chainWnd.ShowWindow(SW_SHOWNA);
	}
	else
	{
		chainwnd_height = 86;
		m_chainWnd.ShowWindow(SW_SHOWNA);
	}

	if (m_patchWndVisible)
		m_patchWnd.ShowWindow(SW_SHOWNA);
	else
		m_patchWnd.ShowWindow(SW_HIDE);

	
	GetClientRect(&rect2);
	cx = rect2.right;
	cy = rect2.bottom;

	m_wndToolBar.GetWindowRect(&rect);
	width = cx - (LIBTREEWND_WIDTH * m_libTreeWndVisible) - (rect.right - rect.left);

	/*
	m_libTreeWnd.SetWindowPos(NULL, 0, 0, LIBTREEWND_WIDTH, cy, SWP_NOOWNERZORDER);
	m_chainWnd.SetWindowPos(NULL, LIBTREEWND_WIDTH * m_libTreeWndVisible, 0, width, chainwnd_height, SWP_NOOWNERZORDER);
	m_patchWnd.SetWindowPos(NULL, LIBTREEWND_WIDTH * m_libTreeWndVisible, chainwnd_height * m_chainWndVisible, width, PATCHWND_HEIGHT, SWP_NOOWNERZORDER);
	m_wksView.SetWindowPos(NULL, LIBTREEWND_WIDTH * m_libTreeWndVisible, (chainwnd_height * m_chainWndVisible) +  (PATCHWND_HEIGHT * m_patchWndVisible), width,  cy - (chainwnd_height * m_chainWndVisible) - (PATCHWND_HEIGHT * m_patchWndVisible), SWP_NOOWNERZORDER);
	*/

	m_libTreeWnd.SetWindowPos(NULL, 0, 0, LIBTREEWND_WIDTH, cy, SWP_NOOWNERZORDER);
	m_chainWnd.SetWindowPos(NULL, LIBTREEWND_WIDTH * m_libTreeWndVisible, 0, width, chainwnd_height, SWP_NOOWNERZORDER);
	m_patchWnd.SetWindowPos(NULL, LIBTREEWND_WIDTH * m_libTreeWndVisible, chainwnd_height, width, PATCHWND_HEIGHT, SWP_NOOWNERZORDER);
	m_wksView.SetWindowPos(NULL, LIBTREEWND_WIDTH * m_libTreeWndVisible, chainwnd_height +  (PATCHWND_HEIGHT * m_patchWndVisible), width,  cy - chainwnd_height - (PATCHWND_HEIGHT * m_patchWndVisible), SWP_NOOWNERZORDER);
}



void CMainFrame::onPatchChange()
{
	POSITION position;
	int i;


	if (g_currentPatch)
	{
		// Determine the patch number
		position = g_currentLibrary->patchList.GetHeadPosition();

		i = 0;

		while (g_currentLibrary->patchList.GetAt(position) != g_currentPatch)
		{
			i++;
			g_currentLibrary->patchList.GetNext(position);
		}
	
		g_currentPatchNumber = i;
	}

	m_chainWnd.OnPatchChange();
	m_patchWnd.m_patchWindowLayer.OnPatchChange();
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	//RECT rect;
	CPatchWndLayer *pPatchWndLayer;

	pPatchWndLayer = &m_patchWnd.m_patchWindowLayer;

	switch (wParam)
	{
		case 0:
		break;

		case IDC_FV_VOLUME:
		case IDC_COSMEQ_ONOFF:
			pPatchWndLayer->OnPatchChange();
			break;

		case IDC_EQ_ONOFF:
		case IDC_AMP_ONOFF:
		case IDC_PTSHIFT_ONOFF:
		case IDC_NS_ONOFF:
		case IDC_REVERB_ONOFF:
		case IDC_DELAY_ONOFF:
		case IDC_CHORUS_ONOFF:
		case IDC_COMP_ONOFF:
		case IDC_WAH_ONOFF:
		case IDC_MOD_ONOFF:
		case IDC_GT_ONOFF:
		case IDC_POCT_ONOFF:
			m_chainWnd.OnPatchChange();
			pPatchWndLayer->OnPatchChange();
			break;

		case IDC_PANEL_AMP:
		case IDC_PANEL_EFFECTS:
		case IDC_PANEL_ASSIGN:
			pPatchWndLayer->m_guitarAmp		= m_chainWnd.m_AmpOnOffData.getValue();
			pPatchWndLayer->m_effects		= m_chainWnd.m_effectsOnOffData.getValue();
			pPatchWndLayer->m_pedalAssign	= m_chainWnd.m_assignOnOffData.getValue();
			pPatchWndLayer->m_levelBmpKey	= FALSE;

		/*	if (!m_patchWnd.m_patchWindowLayer.m_guitarAmp
				&& !pPatchWndLayer->m_effects 
				&& !pPatchWndLayer->m_levelBmpKey 
				&& !pPatchWndLayer->m_pedalAssign)
				m_patchWndVisible = 0;
			else
				m_patchWndVisible = 1;
*/
			//GetWindowRect(&rect);
			//OnSize(0, rect.right - rect.left, rect.bottom - rect.top);
			onPatchChange();
			break;

		case IDC_COMPARE:
			onPatchChange();
			break;

		case IDC_COSM_GT:
			HTREEITEM hTreeItem;

			hTreeItem = m_libTreeWnd.m_libraryTree.GetSelectedItem();
			m_libTreeWnd.m_libraryTree.SetItemImage(hTreeItem, 
			g_currentPatch->cosmGT.guitarType.getValue(), 
			g_currentPatch->cosmGT.guitarType.getValue());
					
			break;

		default:
			onPatchChange();
	}
	
	return CFrameWnd::OnCommand(wParam, lParam);
}

void CMainFrame::OnLibtree() 
{
	m_libTreeWndVisible = !m_libTreeWndVisible;

	OnSize(0, 0, 0);

	m_wksView.TileWindows(m_tileType);
	m_wndToolBar.GetToolBarCtrl().CheckButton(ID_LIBTREE, m_libTreeWndVisible);

	if (m_libTreeWndVisible)
		GetMenu()->CheckMenuItem(ID_LIBTREE, MF_CHECKED);
	else
		GetMenu()->CheckMenuItem(ID_LIBTREE, MF_UNCHECKED);
}

void CMainFrame::OnChain() 
{
	m_chainWndVisible = !m_chainWndVisible;
	OnSize(0, 0, 0);

	m_wksView.TileWindows(m_tileType);
	m_wndToolBar.GetToolBarCtrl().CheckButton(ID_CHAIN, m_chainWndVisible);

	if (m_chainWndVisible)
		GetMenu()->CheckMenuItem(ID_CHAIN, MF_CHECKED);
	else
		GetMenu()->CheckMenuItem(ID_CHAIN, MF_UNCHECKED);
}

void CMainFrame::OnPatchedit() 
{
	m_patchWndVisible = !m_patchWndVisible;
	OnSize(0, 0, 0);

	m_wksView.TileWindows(m_tileType);
	m_wndToolBar.GetToolBarCtrl().CheckButton(ID_PATCHEDIT, m_patchWndVisible);

	if (m_patchWndVisible)
		GetMenu()->CheckMenuItem(ID_PATCHEDIT, MF_CHECKED);
	else
		GetMenu()->CheckMenuItem(ID_PATCHEDIT, MF_UNCHECKED);
}

void CMainFrame::Cascade() 
{
	//m_wksView.TileWindows();
}

void CMainFrame::TileH()
{
	m_wksView.TileWindows(MDITILE_HORIZONTAL);

	m_tileType = MDITILE_HORIZONTAL;
}

void CMainFrame::TileV() 
{
	m_wksView.TileWindows(MDITILE_VERTICAL);

	m_tileType = MDITILE_VERTICAL;
}

void CMainFrame::Save()
{
	char buffer[4096];
	int ret;

	if (g_currentLibrary && g_currentLibrary->modified)
	{
		if (g_currentLibrary->libraryType == LIB_PRESET)
		{
			MessageBox("The preset library can not be saved.", "VEditor", MB_ICONINFORMATION);
			return;
		}
		else if (g_currentLibrary->libraryType == LIB_USER)
		{
			sprintf(buffer, "Send changes to VG-88 User ?", g_currentLibrary->file);
			ret = MessageBox(buffer, "VEditor", MB_YESNO | MB_ICONQUESTION);

			switch (ret)
			{
				case IDYES:
					g_currentLibrary->SendPatch(((CMainFrame *) AfxGetMainWnd())->m_hmo[0], 0, 99, 0, TRUE);
					g_currentLibrary->save();
					break;

				case IDNO:
					break;
			}
		}
		else
		{
			if (g_currentLibrary->newLibrary)
			{
				int ret;
				CFileDialog dlg(FALSE, "syx", g_currentLibrary->file, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, "System Exclusive Library (*.syx)|*.syx", this);

				ret = dlg.DoModal();

				if (ret == IDCANCEL)
					return;

				g_currentLibrary->file = dlg.GetPathName();
				g_currentLibrary->save();
			}
			else
				g_currentLibrary->save();
		}
	}
}


void CMainFrame::SaveAs()
{
	if (!g_currentLibrary)
		return;
	
	int ret;
	CVG88SysEx *library;

	CFileDialog dlg(FALSE, "syx", g_currentLibrary->file, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, "System Exclusive Library (*.syx)|*.syx", this);

	ret = dlg.DoModal();
	
	if (ret == IDCANCEL)
		return;
	library = LoadLibrary(m_editorPath + "\\" + g_currentLibrary->file);
	library->file = dlg.GetPathName();
	library->modified = true;
	library->save();
}


void CMainFrame::SaveAll()
{
	HTREEITEM hTreeItem;
	CVG88SysEx *library;
	char buffer[4096];
	int ret;


	hTreeItem = m_libTreeWnd.m_libraryTree.GetRootItem();

	while (hTreeItem)
	{
		library =  (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData(hTreeItem);

		if (library->modified)
		{
			if (library->libraryType == LIB_PRESET)
			{
				if (MessageBox("You have modified some patches in the preset library.\nThese patches can not be saved. Continue ?", "VEditor", MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
					return;

				hTreeItem = m_libTreeWnd.m_libraryTree.GetNextItem(hTreeItem, TVGN_NEXT);
				continue;
			}

			if (library->libraryType == LIB_USER)
			{
				sprintf(buffer, "Send changes to VG-88 User ?", library->file);
				ret = MessageBox(buffer, "VEditor", MB_YESNO | MB_ICONQUESTION);

				switch (ret)
				{
					case IDYES:
						library->SendPatch(((CMainFrame *) AfxGetMainWnd())->m_hmo[0], 0, 99, 0, TRUE);
						library->save();
						break;

					case IDNO:
						break;
				}
			}
			else
			{
				if (library->newLibrary)
				{
					int ret;

					CFileDialog dlg(FALSE, "syx", library->file, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, "System Exclusive Library (*.syx)|*.syx", this);

					ret = dlg.DoModal();

					if (ret == IDCANCEL)
						return;

					library->file = dlg.GetPathName();
					library->save();
				}
				else
					library->save();
			}
		}

		hTreeItem = m_libTreeWnd.m_libraryTree.GetNextItem(hTreeItem, TVGN_NEXT);
	}
}


void CMainFrame::Open()
{
	CVG88SysEx *library;
	char fileNames[100 * 1024];
	fileNames[0] = 0;

	CFileDialog dlg(TRUE, "syx", "*.syx", OFN_ALLOWMULTISELECT  | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, "System Exclusive Library (*.syx)|*.syx");

	dlg.m_ofn.nMaxFile = 100 * 1024;
	dlg.m_ofn.lpstrFile = fileNames;

	if (dlg.DoModal() == IDOK)
	{
		POSITION position;
		int count = 0;

		position = dlg.GetStartPosition();

		while (position)
		{
			count++;
			library = LoadLibrary(dlg.GetNextPathName(position));
		}


		if (count == 1)
		{
			HTREEITEM item;
			OpenLibraryWindow(library);
			CTreeCtrl *tree = &((CMainFrame *) AfxGetMainWnd())->m_libTreeWnd.m_libraryTree;

			item = library->GetTreeItem();
			item = tree->GetChildItem(item);

			if (item)
			{
				tree->SelectItem(item);
				tree->EnsureVisible(item);
			}
		}
	}
}


void CMainFrame::Order()
{
	MessageBox("If you want to send a donation :\n\nGo to www.paypal.com and send money to ralph.benchetrit1@libertysurf.fr\n\nIf you do not want to use paypal, send me an e-mail at ralph.benchetrit1@libertysurf.fr");
}

void CMainFrame::Copy()
{
	if (GetFocus()->m_hWnd == m_libTreeWnd.m_libraryTree.m_hWnd)
		m_libTreeWnd.PostMessage(WM_COMMAND, ID_EDIT_COPY, 0);
	else
	{
		HTREEITEM hItem;
		CVG88SysEx *library;

		hItem = m_libTreeWnd.m_libraryTree.GetRootItem();

		while (hItem)
		{
			library = (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData(hItem);

			if (library->data1 != NULL)
			{
				if (GetFocus()->m_hWnd == ((CVGWindow *) library->data1)->m_listView.m_hWnd)
					((CVGWindow *) library->data1)->PostMessage(WM_COMMAND, ID_EDIT_COPY, 0);
			}

			hItem = m_libTreeWnd.m_libraryTree.GetNextItem(hItem, TVGN_NEXT);
		}
	}
}

void CMainFrame::Cut()
{
	if (GetFocus()->m_hWnd == m_libTreeWnd.m_libraryTree.m_hWnd)
		m_libTreeWnd.PostMessage(WM_COMMAND, ID_EDIT_CUT, 0);
	else
	{
		HTREEITEM hItem;
		CVG88SysEx *library;

		hItem = m_libTreeWnd.m_libraryTree.GetRootItem();

		while (hItem)
		{
			library = (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData(hItem);

			if (library->data1 != NULL)
			{
				if (GetFocus()->m_hWnd == ((CVGWindow *) library->data1)->m_listView.m_hWnd)
					((CVGWindow *) library->data1)->PostMessage(WM_COMMAND, ID_EDIT_CUT, 0);
			}

			hItem = m_libTreeWnd.m_libraryTree.GetNextItem(hItem, TVGN_NEXT);
		}
	}
}


void CMainFrame::Paste()
{
	if (GetFocus()->m_hWnd == m_libTreeWnd.m_libraryTree.m_hWnd)
		m_libTreeWnd.PostMessage(WM_COMMAND, ID_EDIT_PASTE, 0);
	else
	{
		HTREEITEM hItem;
		CVG88SysEx *library;

		hItem = m_libTreeWnd.m_libraryTree.GetRootItem();

		while (hItem)
		{
			library = (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData(hItem);

			if (library->data1 != NULL)
			{
				if (GetFocus()->m_hWnd == ((CVGWindow *) library->data1)->m_listView.m_hWnd)
					((CVGWindow *) library->data1)->PostMessage(WM_COMMAND, ID_EDIT_PASTE, 0);
			}

			hItem = m_libTreeWnd.m_libraryTree.GetNextItem(hItem, TVGN_NEXT);
		}
	}
}


void CMainFrame::Close()
{
	HTREEITEM item;
	POSITION position;

	if (g_currentLibrary && g_currentLibrary->libraryType != LIB_PRESET && g_currentLibrary->libraryType != LIB_USER)
	{
		item = g_currentLibrary->GetTreeItem();

		if (g_currentLibrary->data1)
		{
			CVGWindow *vgWindow = (CVGWindow *) g_currentLibrary->data1;
			vgWindow->PostMessage(WM_CLOSE);
			PostMessage(WM_CHECK_LIBRARY_WINDOW);
		}

		position = m_VG88Lib.Find(g_currentLibrary);
		m_VG88Lib.RemoveAt(position);
		delete g_currentLibrary;
		g_currentLibrary = NULL;

		m_libTreeWnd.m_libraryTree.DeleteItem(item);
	}
}


void CMainFrame::New()
{
	CVG88SysEx *library = new CVG88SysEx;
	m_newLibraryCounter++;
	library->file.Format("patch\\Library%d.syx", m_newLibraryCounter);
	OpenLibraryWindow(library);
	InsertLibrary(library);
}

void CMainFrame::Send()
{
	CSendPatchForm	sendPatchFormDlg;

	if (!g_currentLibrary)
		return;

	sendPatchFormDlg.m_library = g_currentLibrary;
	sendPatchFormDlg.m_system = (g_currentLibrary->vgSystem != NULL);
	sendPatchFormDlg.m_patchToSend = -1;

	if (sendPatchFormDlg.DoModal() == IDOK)
	{
		g_currentLibrary->SendPatch(((CMainFrame *) AfxGetMainWnd())->m_hmo[0], sendPatchFormDlg.m_startPatch, sendPatchFormDlg.m_toPach, sendPatchFormDlg.m_toProgram);
		UpdateUserLibrary(sendPatchFormDlg.m_startPatch, sendPatchFormDlg.m_toPach, sendPatchFormDlg.m_toProgram);
		SendAuditionPatch();
	}
}


void CMainFrame::SendOnePatch()
{
	CSendPatchForm	sendPatchFormDlg;

	if (!g_currentLibrary)
		return;

	sendPatchFormDlg.m_library = g_currentLibrary;
	sendPatchFormDlg.m_system = (g_currentLibrary->vgSystem != NULL);

	HTREEITEM item;
	CTreeCtrl *tree;

	tree = &(((CMainFrame *) AfxGetMainWnd())->m_libTreeWnd.m_libraryTree);
	item = g_currentLibrary->GetTreeItem();

	item = tree->GetChildItem(item);
	int pos = 0;

	while (item)
	{
		if ((CPatch *) (tree->GetItemData(item)) == g_currentPatch)
			break;

		pos++;
		item = tree->GetNextItem(item, TVGN_NEXT);
	}


	sendPatchFormDlg.m_patchToSend = pos;

	if (sendPatchFormDlg.DoModal() == IDOK)
	{
		g_currentLibrary->SendPatch(((CMainFrame *) AfxGetMainWnd())->m_hmo[0], sendPatchFormDlg.m_startPatch, sendPatchFormDlg.m_toPach, sendPatchFormDlg.m_toProgram);
		UpdateUserLibrary(sendPatchFormDlg.m_startPatch, sendPatchFormDlg.m_toPach, sendPatchFormDlg.m_toProgram);
		SendAuditionPatch();
	}
}


void CMainFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}



int CMainFrame::OpenMidiPort(int device)
{
	CloseMidiPort(device);

	// Open Midi device

	if (midiOutOpen(&m_hmo[device], g_settings.devices[device].midiOutputPort, NULL, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		MessageBox("Failed opening midi output port");

	if (midiInOpen(&m_hmi[device], g_settings.devices[device].midiInputPort , (DWORD) MidiInProc, 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
		MessageBox("Failed opening midi input port");
	else
	{
		if (midiInStart(m_hmi[device]) != MMSYSERR_NOERROR)
			MessageBox("Failed initializing midi");
	}

	return 1;
}



int CMainFrame::CloseMidiPort(int device)
{
	midiOutClose(m_hmo[device]);
	midiInClose(m_hmi[device]);

	return 1;
}

void CMainFrame::OpenVgWindow()
{
	if (g_currentLibrary && g_currentLibrary->data1 == NULL)
		OpenLibraryWindow(g_currentLibrary);
}


CVGWindow *CMainFrame::OpenLibraryWindow(CVG88SysEx *library)
{
	CVGWindow	*vgWindow;
	RECT rect;
	HTREEITEM hItem;
	bool noWindowLeft = true;
	CVG88SysEx *libraryTmp;

	hItem = m_libTreeWnd.m_libraryTree.GetRootItem();

	while (hItem)
	{
		libraryTmp = (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData(hItem);

		if (libraryTmp->data1 != NULL)
			noWindowLeft = FALSE;

		hItem = m_libTreeWnd.m_libraryTree.GetNextItem(hItem, TVGN_NEXT);
	}

	if (noWindowLeft)
	{
		m_chainWndVisibleBefore = m_chainWndVisible;
		m_patchWndVisibleBefore = m_patchWndVisible;
	}

	vgWindow = new CVGWindow;
			
	library->data1 = vgWindow;

	vgWindow->Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CAPTION | WS_THICKFRAME, // | WS_SYSMENU,  | WS_MAXIMIZEBOX
			CRect(0, 0, 900, 200), &m_wksView, 0, NULL);

	vgWindow->AttachLibrary(library);

	m_patchWndVisible = 0;
	m_chainWndVisible = 0;
	m_wndToolBar.GetToolBarCtrl().CheckButton(ID_PATCHEDIT, FALSE);
	m_wndToolBar.GetToolBarCtrl().CheckButton(ID_CHAIN, FALSE);
	GetMenu()->CheckMenuItem(ID_CHAIN, MF_UNCHECKED);
	GetMenu()->CheckMenuItem(ID_PATCHEDIT, MF_UNCHECKED);

	GetWindowRect(&rect);
	OnSize(0, rect.right - rect.left, rect.bottom - rect.top);

	m_wksView.TileWindows(m_tileType);
	vgWindow->ShowWindow(SW_SHOW);
	vgWindow->BringWindowToTop();

	return vgWindow;
}


int CMainFrame::UpdateUserLibrary(int firstPatch, int lastPatch, int targetPatch, CVG88SysEx *library)
{
	CVG88SysEx *userLibrary;
	char buffer[175000];
	char *ptrBuf;
	int count;
	int patchcountUser, patchcount;
	CPatch		*patch;
	int i;
	POSITION	position, positionUser;
	CFileException	e;
	CFile			fileParam;

	if (!library)
		library = g_currentLibrary;

	if (!library)
		return 0;

	// Open the file
	if (!fileParam.Open("sys\\VG88U.syx", CFile::modeWrite | CFile::modeCreate, &e))
		return 0;

	userLibrary = (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData((m_libTreeWnd.m_libraryTree.GetRootItem()));

	patchcountUser = userLibrary->patchList.GetCount();
	patchcount = lastPatch - firstPatch + 1;
	positionUser = userLibrary->patchList.GetHeadPosition();
	position = library->patchList.GetHeadPosition();

	for (i = 0; i < firstPatch; i++)
		patch = (CPatch *) library->patchList.GetNext(position);

	for (i = 0; i < patchcountUser; i++)
	{
		ptrBuf = buffer;

		if (i < targetPatch || i >= targetPatch + patchcount)
		{
			patch = (CPatch *) userLibrary->patchList.GetNext(positionUser);

			count = userLibrary->getVGData(&ptrBuf, patch, i);
		}
		else
		{
			patch = (CPatch *) userLibrary->patchList.GetNext(positionUser);
			patch = (CPatch *) library->patchList.GetNext(position);
			count = library->getVGData(&ptrBuf, patch, firstPatch + i - targetPatch);
		}

		fileParam.Write(buffer, count);
	}

	fileParam.Close();

	((CMainFrame *) AfxGetMainWnd())->LoadLibrary("sys\\VG88U.syx", userLibrary);

	return 0;
}



void CMainFrame::SendAuditionPatch()
{
	if (g_currentLibrary && m_chainWnd.m_sendMidiOnOffData.getValue() == 1)
	{
		/*if (strcmp(g_currentLibrary->file, "sys\\VG88U.syx") == 0 
			|| strcmp(g_currentLibrary->file, "sys\\VG88P.syx") == 0)
			return;*/
		m_chainWnd.m_sendMidiData.setValue(1);
		m_chainWnd.m_assignMidiLed.RedrawWindow();
		g_currentLibrary->SendAuditionPatch(m_hmo[0]);
		m_chainWnd.m_sendMidiData.setValue(0);
		m_chainWnd.m_assignMidiLed.RedrawWindow();
	}
}

void CMainFrame::OnClose() 
{
	HTREEITEM hItem;
	CVG88SysEx *library;
	char buffer[4096];
	int ret;

	// Check if a library have been modified and need saving

	hItem = m_libTreeWnd.m_libraryTree.GetRootItem();

	while (hItem)
	{
		library = (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData(hItem);

		if (library->modified)
		{
			if (library->libraryType == LIB_PRESET)
			{
				if (MessageBox("You have modified some patches in the preset library.\nThese patches can not be saved. Continue ?", "VEditor", MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
					return;
			}
			else if (library->libraryType == LIB_USER)
			{
				sprintf(buffer, "Send changes to VG-88 User ?", library->file);
				ret = MessageBox(buffer, "VEditor", MB_YESNOCANCEL | MB_ICONQUESTION);

				switch (ret)
				{
					case IDYES:
						library->SendPatch(((CMainFrame *) AfxGetMainWnd())->m_hmo[0], 0, 99, 0, TRUE);
						library->save();
						break;

					case IDNO:
						break;

					case IDCANCEL:
						return;
						break;
				}
			}
			else
			{
				sprintf(buffer, "Save changes to library %s ?", library->file);
				ret = MessageBox(buffer, "VEditor", MB_YESNOCANCEL | MB_ICONQUESTION);

				switch (ret)
				{
					case IDYES:
					{
						if (library->newLibrary)
						{
							int ret;

							CFileDialog dlg(FALSE, "syx", library->file, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, "System Exclusive Library (*.syx)|*.syx", this);

							ret = dlg.DoModal();

							if (ret == IDCANCEL)
								return;

							library->file = dlg.GetPathName();
							library->save();
						}
					}
					break;

					case IDNO:
						break;

					case IDCANCEL:
						return;
						break;
				}
			}
		}

		hItem = m_libTreeWnd.m_libraryTree.GetNextItem(hItem, TVGN_NEXT);
	}

	if (IsZoomed())
		g_settings.generalSetting.isZoomed = TRUE;
	else
	{
		CRect rect;

		g_settings.generalSetting.isZoomed = FALSE;
		GetWindowRect(rect);

		g_settings.generalSetting.x = rect.left;
		g_settings.generalSetting.y = rect.top;
		g_settings.generalSetting.cx = rect.right - rect.left;
		g_settings.generalSetting.cy = rect.bottom - rect.top;
	}

	g_settings.generalSetting.chainWndVisible = m_chainWndVisible;
	g_settings.generalSetting.libTreeWndVisible = m_libTreeWndVisible;
	g_settings.generalSetting.patchWndVisible = m_patchWndVisible;

	g_settings.Write();
	
	CFrameWnd::OnClose();
}


void CMainFrame::CopyToClipboard(CPatch **patches, int patchCount)
{
	char *buffer;
	int i;
	int count;
	count = 0;

	for (i = 0; i < patchCount; i++)
	{
		buffer = &m_copyBuffer[count];
		count += patches[i]->getVGData(&buffer);
	}

	m_copyCount = patchCount;
}



void CMainFrame::CutToClipboard(CVG88SysEx *library, CPatch **patches, int patchCount)
{
	int i;
	POSITION pos;

	CopyToClipboard(patches, patchCount);

	for (i = 0; i < patchCount; i++)
	{
		pos = library->patchList.Find(patches[i]);

		if (pos)
			library->patchList.RemoveAt(pos);
	}

	InsertLibrary(library, library);
	library->SetModifiedFlag();
}


void CMainFrame::PasteFromClipboard(CVG88SysEx *library, int pos)
{
	char *buffer;
	int count = 0;
	CPatch *patch;
	int posNum = pos;
	int i;
	POSITION position;

	position = library->patchList.GetHeadPosition();

	for (i = 0; i < pos; i++)
		library->patchList.GetNext(position);

	buffer = &m_copyBuffer[count];

	for (i = 0; i < m_copyCount; i++)
	{
		patch = new CPatch;

		patch->cosmGT.guitarType.m_needSaving = FALSE;
		patch->cosmGT.guitarType.setValue(buffer[162] * 16 + buffer[163]);
		patch->cosmGT.guitarType.m_needSaving = TRUE;
		patch->patchNum = posNum++;

		count += patch->setVGData(&buffer);

		if (pos >= 0)
			library->patchList.InsertBefore(position, patch);
		else
			library->patchList.AddTail(patch);

		buffer = &m_copyBuffer[count];
	}

	InsertLibrary(library, library);
	library->SetModifiedFlag();
}


void CMainFrame::OnCheckLibraryWindows(WPARAM wParam, LPARAM lParam)
{
	CheckLibraryWindows();
}


void CMainFrame::OnFirstRun(WPARAM wParam, LPARAM lParam)
{
	onPatchChange();

	if (g_firstRun && MessageBox("This is the first time you run VEditor.\n\nDo you want to synchronize VEditor's User library whith your VG-88 ?", "VEditor", MB_YESNO | MB_ICONQUESTION) == IDYES)
		Synchronize();
}


void CMainFrame::CheckLibraryWindows()
{
	HTREEITEM hItem;
	CVG88SysEx *library;
	bool noWindowLeft = TRUE;

	if (m_chainWndVisible || m_patchWndVisible)
		return;

	// Check if a library have been modified and need saving

	hItem = m_libTreeWnd.m_libraryTree.GetRootItem();

	while (hItem)
	{
		library = (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData(hItem);

		if (library->data1 != NULL)
			noWindowLeft = FALSE;

		hItem = m_libTreeWnd.m_libraryTree.GetNextItem(hItem, TVGN_NEXT);
	}


	if (noWindowLeft)
	{
		m_chainWndVisible = m_chainWndVisibleBefore;
		m_patchWndVisible = m_patchWndVisibleBefore;
		m_wndToolBar.GetToolBarCtrl().CheckButton(ID_CHAIN, m_chainWndVisibleBefore);
		m_wndToolBar.GetToolBarCtrl().CheckButton(ID_PATCHEDIT, m_patchWndVisibleBefore);

		OnSize(0, 0, 0);
	}
	else
		m_wksView.TileWindows(m_tileType);
}


void CMainFrame::SetCurrentLibrary(CVG88SysEx * library)
{
	g_currentLibrary = library;

	/*if (library)
	{
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_SEND, FALSE);

		if (library->modified)
			m_wndToolBar.GetToolBarCtrl().EnableButton(ID_SEND, TRUE);
		else
			m_wndToolBar.GetToolBarCtrl().EnableButton(ID_SEND, FALSE);
	}
	else
	{
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_SEND, FALSE);
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_SAVE, FALSE);
	}*/
}

void CMainFrame::SetCurrentPatch(CPatch *patch)
{
	g_currentPatch = patch;
}

void CMainFrame::SetCurrentSystem(CSystem *system)
{
	g_currentSystem = system;
}


void CMainFrame::DragMove(UINT nFlags, CPoint point)
{
	if (!m_bDragging)
		return;

	CRect	rect, rect2;
	CWnd *pWnd = GetCapture();

	m_DropFound = false;

	if (pWnd)
	{
		pWnd->GetWindowRect(rect);
		int posX = point.x + rect.left;
		int posY = point.y + rect.top;

		HTREEITEM hItem;
		CVG88SysEx *library;
		bool noWindowLeft = TRUE;

		hItem = m_libTreeWnd.m_libraryTree.GetRootItem();

		while (hItem)
		{
			library = (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData(hItem);

			if (library->data1 != NULL)
			{
				((CVGWindow *) library->data1)->GetWindowRect(rect);

				if (posX > rect.left && posX < rect.right && posY > rect.top && posY < rect.bottom)
				{
					m_DropFound = true;

					int itemSel;
					RECT recSel;
					CListCtrlCustom *pListview = &((CVGWindow *) library->data1)->m_listView;

					pListview->GetWindowRect(rect2);

					itemSel = pListview->HitTest(CPoint(posX - rect2.left, posY - rect2.top));
					pListview->SetSelectionMark(itemSel);

					if (itemSel != -1)
					{
						if (pListview != pLastListviewDrag || lastItemDrag != itemSel)
						{
							if (pLastListviewDrag)
							{
								pLastListviewDrag->GetItemRect(lastItemDrag, &recSel, LVIR_LABEL);
								recSel.bottom = recSel.top + 2;
								recSel.top = recSel.top;
								pLastListviewDrag->GetDC()->DrawFocusRect(&recSel);
							}

							pListview->GetItemRect(itemSel, &recSel, LVIR_LABEL);
							recSel.bottom = recSel.top + 2;
							recSel.top = recSel.top;

							pListview->GetDC()->DrawFocusRect(&recSel);
							pLastListviewDrag = pListview;
							lastItemDrag = itemSel;
						}
					}
					else if (pLastListviewDrag)
					{
						pLastListviewDrag->GetItemRect(lastItemDrag, &recSel, LVIR_LABEL);
						recSel.bottom = recSel.top + 2;
						recSel.top = recSel.top;
						pLastListviewDrag->GetDC()->DrawFocusRect(&recSel);

						pLastListviewDrag = NULL;
					}
				}
			}

			hItem = m_libTreeWnd.m_libraryTree.GetNextItem(hItem, TVGN_NEXT);
		}

		if (m_DropFound)
		{
			if (::GetKeyState(VK_CONTROL) < 0)
				::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORGP));
			else 
				::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORG));
		}
		else
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));
	}
}

void CMainFrame::DragLButtonUp(UINT nFlags, CPoint point) 
{
	if (!m_bDragging)
		return;

	CRect	rect;
	CWnd *pWnd = GetCapture();

	if (::GetKeyState(VK_CONTROL) < 0)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORGP));
	else 
		::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORG));

	if (pWnd)
	{
		pWnd->GetWindowRect(rect);
		int posX = point.x + rect.left;
		int posY = point.y + rect.top;

		HTREEITEM hItem;
		CVG88SysEx *library;
		bool noWindowLeft = TRUE;

		hItem = m_libTreeWnd.m_libraryTree.GetRootItem();

		while (hItem)
		{
			library = (CVG88SysEx *) m_libTreeWnd.m_libraryTree.GetItemData(hItem);

			if (library->data1 != NULL)
			{
				if (pLastListviewDrag)
					pLastListviewDrag->SetSelectionMark(lastItemDrag);

				((CVGWindow *) library->data1)->GetWindowRect(rect);

				if (posX > rect.left && posX < rect.right && posY > rect.top && posY < rect.bottom)
				{
					((CVGWindow *) library->data1)->SendMessage(WM_COMMAND, ID_EDIT_PASTE, 0);
					break;
				}
			}

			hItem = m_libTreeWnd.m_libraryTree.GetNextItem(hItem, TVGN_NEXT);
		}

		if (pLastListviewDrag)
		{
			RECT recSel;

			pLastListviewDrag->GetItemRect(lastItemDrag, &recSel, LVIR_LABEL);
			recSel.bottom = recSel.top + 2;
			recSel.top = recSel.top;
			pLastListviewDrag->GetDC()->DrawFocusRect(&recSel);
		}

	}

	pLastListviewDrag = NULL;
	ReleaseCapture();
	m_bDragging = FALSE;
}