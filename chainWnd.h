// ChainWnd.h : interface of the CChainWnd class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ChainWnd_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_)
#define AFX_ChainWnd_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

#include "controls.h"
#include "VEditor.h"
#include "panel.h"


#define CHAINWND_HEIGHT	313
#define CHAINWND_WIDTH	900

// CChainWnd window

class CChainWnd : public CPanel
{
// Construction
public:
	CChainWnd();

// Attributes
public:
	COnOff		m_AmpOnOffData;
	CVGButton	m_AmpOnOff;
	CVGButton	m_ledOnOff;

	COnOff		m_effectsOnOffData;
	CVGButton	m_effectButtonOnOff;
	CVGButton	m_effectsLedOnOff;

	COnOff		m_assignOnOffData;
	CVGButton	m_assignButtonOnOff;
	CVGButton	m_assignLedOnOff;

	COnOff		m_compareOnOffData;
	CVGButton	m_compareButtonOnOff;
	CVGButton	m_compareLedOnOff;

	
	COnOff		m_sendMidiOnOffData;
	COnOff		m_sendMidiData;
	CVGButton	m_sendMidiButtonOnOff;
	CVGButton	m_assignMidiLedOnOff;
	CVGButton	m_assignMidiLed;

	CPanel		*m_panelEdit;

	void PaintChainWnd(CDC *dc);
	void PaintLCD(CDC *dc);
	void PaintChain(CDC *dc);
	void OnPatchChange();
	CString	getPresetDir();
	int setAllPanelData(char *buffer);
	int getAllPanelData(char *buffer);

	bool CChainWnd::IsPedalOn(int i);
	CRect	m_pedalPos[10];
	CRect	m_CosmGMix;
	BOOL	m_bTracking;
	int		m_moveFrom;
	int		m_moveTo;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChainWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChainWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChainWnd)
	afx_msg int OnCreate (LPCREATESTRUCT);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ChainWnd_H__8592B4BA_42A3_4F67_AA15_481AD7605731__INCLUDED_)
