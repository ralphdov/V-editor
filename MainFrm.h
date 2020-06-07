// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__023EDBDF_837E_400B_BF3B_CF6432A6FCAB__INCLUDED_)
#define AFX_MAINFRM_H__023EDBDF_837E_400B_BF3B_CF6432A6FCAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Mmsystem.h>
#include "LibTreeWnd.h"
#include "tools.h"
#include "VGWindow.h"
#include "chainWnd.h"
#include "patchWnd.h"
#include "libTreeWnd.h"
#include "WorkspaceView.h"
#include "SendPatch.h"

#define WM_CHECK_LIBRARY_WINDOW	WM_USER + 2
#define WM_FIRSTRUN				WM_USER + 3

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:
	CPtrList	m_VG88Lib;

	HMIDIOUT		m_hmo[MAXDEVICES];
	HMIDIIN			m_hmi[MAXDEVICES];

	// Drag and drop management
	BOOL        m_bDragging;
	HTREEITEM   m_hitemDrag;
	CListCtrlCustom *pLastListviewDrag;
	int			lastItemDrag;
	int			m_DropFound;

	CString		m_editorPath;

	CVG88SysEx* CMainFrame::LoadLibrary(LPCTSTR lpFileName, CVG88SysEx *VG88Old = NULL);
	int CMainFrame::InsertLibrary(CVG88SysEx *library, CVG88SysEx *oldLibrary = NULL);
	void onPatchChange();
	int OpenMidiPort(int device);
	int CloseMidiPort(int device);
	void SendAuditionPatch();
	int CMainFrame::UpdateUserLibrary(int firstPatch, int lastPatch, int targetPatch, CVG88SysEx *library = NULL);
	void CopyToClipboard(CPatch **patches, int count);
	void PasteFromClipboard(CVG88SysEx *library, int pos);
	void CMainFrame::CutToClipboard(CVG88SysEx *library, CPatch **patches, int patchCount);
	void CheckLibraryWindows();
	void CMainFrame::SetCurrentPatch(CPatch *patch);
	void CMainFrame::SetCurrentLibrary(CVG88SysEx * library);
	void CMainFrame::SetCurrentSystem(CSystem *system);
	void DragMove(UINT nFlags, CPoint point);
	void DragLButtonUp(UINT nFlags, CPoint point);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CToolBar			m_wndToolBar;
	CLibTreeWnd			m_libTreeWnd;
	CChainWnd			m_chainWnd;
	CPatchWnd			m_patchWnd;
	CWorkspaceView		m_wksView;
	CVGWindow			*m_wndVGWindow;
	int					m_newLibraryCounter;

	bool				m_libTreeWndVisible;
	bool				m_chainWndVisible;
	bool				m_patchWndVisible;

	bool				m_chainWndVisibleBefore;
	bool				m_patchWndVisibleBefore;

	UINT				m_tileType;
	int					m_midiPatchNumber;
	MIDIHDR				m_midiHdr;
	char				m_midiInBuffer[175000];
	long				m_midiInCount;
	long				m_midiInSize;
	char				m_copyBuffer[175000];
	int					m_copyCount;
	bool				m_sendPatchCanceled;

	CSendPatch			m_sendPatchDlg;

	CVGWindow *OpenLibraryWindow(CVG88SysEx *library);

// Generated message map functions
public:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLibtree();
	afx_msg void OnChain();
	afx_msg void OnPatchedit();
	afx_msg void Cascade();
	afx_msg void TileH();
	afx_msg void TileV();
	afx_msg void Save();
	afx_msg void SaveAs();
	afx_msg void SaveAll();
	afx_msg void Open();
	afx_msg void Copy();
	afx_msg void Cut();
	afx_msg void Paste();
	afx_msg void New();
	afx_msg void Send();
	afx_msg void Close();
	afx_msg void Order();
	afx_msg void SendOnePatch();
	afx_msg void Receive();
	afx_msg void Synchronize();
	afx_msg void Properties();
	afx_msg void OpenVgWindow();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMidiPatchChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMidiPatchReceived(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCheckLibraryWindows(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFirstRun(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__023EDBDF_837E_400B_BF3B_CF6432A6FCAB__INCLUDED_)
