#ifndef __PRESET_H__
#define __PRESET_H__

#include "tools.h"
#include "controls.h"
#include "panel.h"
#include "VG-88.h"

/*class CVGSection: public CControl
{
	public:
	CVGSection();
	BOOL CreateControl(LPCTSTR lpszCaption, int y, CWnd* pParentWnd, UINT nID);

	void Paint(CDC *pDc);
	
	CMaskedBitmap	*m_section;		// Contain images for all possibles values

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVGSection)
	protected:
	//}}AFX_VIRTUAL

		// Generated message map functions
protected:
	//{{AFX_MSG(CVGSection)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

*/

class CPanel;

class CPreset: public CControl
{
	public:
	CPreset();
	BOOL CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
			int x, int y, int width, int height, CPanel *pParentWnd, UINT nID);

	//void OnMouseAction(CPoint);
	void Paint(CDC *pDc);
	
	CBrush			m_brush;
	BOOL			m_bTracking;
	CListBoxCustom	m_listBox;
	CPanel			*m_parent;
	char			m_current[175000];
	int				m_currentCount;
	CVGButton		m_buttonSave;
	CVGButton		m_buttonCopy;
	CVGButton		m_buttonRename;
	CVGButton		m_buttonDelete;
	COnOff			m_buttonSaveData;
	COnOff			m_buttonCopyData;
	COnOff			m_buttonDeleteData;
	COnOff			m_buttonRenameData;

	void saveCurrentToPreset(CString name);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreset)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
		// Generated message map functions
protected:
	//{{AFX_MSG(CPreset)
	afx_msg void OnPaint();
	afx_msg void OnSelChange();
	afx_msg void OnKillFocus();
	afx_msg void OnDblClk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif