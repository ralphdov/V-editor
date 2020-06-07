#ifndef __CONTROLS_H__
#define __CONTROLS_H__


#include "tools.h"
#include "VG88Common.h"

#define LABEL_HEIGHT	8
#define LABEL_WIDTH		85

#define CTRL_AMPKNOB1		1
#define CTRL_AMPKNOB2		2
#define CTRL_SWITCH1		3
#define CTRL_VFADER1		4
#define CTRL_HFADER1		5
#define CTRL_VGKNOB1		6
#define CTRL_VGKNOB2		7
#define CTRL_VGKNOB3		11
#define CTRL_GTKNOB1		12
#define CTRL_SELECTOR		13
#define CTRL_MIC1			14
#define CTRL_MIC2			15
#define CTRL_VFADERORGAN	16

#define CTRL_EDIT1		1
#define CTRL_EDIT2		2

class CVGList;

class CControl : public CWnd
{
public:
	CControl();
	virtual ~CControl();
	BOOL CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
			const RECT& rect, CWnd* pParentWnd, UINT nID, unsigned long cwndStyle = 0);

	void AttachVGData(CVGData *vgData);
	virtual void Paint(CDC *pDc) = 0;

	CFont	*m_font;
	CVGData	*m_vgData;
	DWORD	m_dwStyle;
	CVGList *m_listValue;

	char	m_sens;
	int		m_bitmapImageCount;
	int		m_imageWidth;
	int		m_imageHeight;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControl)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

		// Generated message map functions
protected:
	//{{AFX_MSG(CControl)
	afx_msg int OnCreate (LPCREATESTRUCT);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




#define DATA_NONE		0
#define DATA_BOTTOM		1
#define DATA_TOP		2
#define DATA_RIGHT		3
#define DATA_TOPLEFT	4

class CVGKnob: public CControl
{
	public:
	CVGKnob();
	BOOL CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
			int x, int y, CWnd* pParentWnd, UINT nID);

	BOOL CreateImageControl(LPCTSTR lpszCaption, int x, int y, CMaskedBitmap *bitmap, int imageCount, CWnd* pParentWnd, UINT nID);

	void OnMouseAction(CPoint);
	void Paint(CDC *pDc);
	
	CMaskedBitmap	*m_knob;		// Contain images for all possibles values
	BOOL			m_emptyImage;	// True if the image contain one supplementary position for NULL
	char			m_labelPosition;
	char			m_dataPosition;
	BOOL			m_bTracking;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVGKnob)
	protected:
	//}}AFX_VIRTUAL

		// Generated message map functions
protected:
	//{{AFX_MSG(CVGKnob)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CVGButton: public CControl
{
	public:
	CVGButton();
	BOOL CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
			int x, int y, CWnd* pParentWnd, UINT nID);
	void Paint(CDC *pDc);
	
	CMaskedBitmap	*m_button;
	char m_dataPosition;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVGButton)
	protected:
	//}}AFX_VIRTUAL

		// Generated message map functions
protected:
	//{{AFX_MSG(CVGButton)
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CVGEdit: public CControl
{
	public:
	CVGEdit();
	BOOL CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
			int x, int y, CWnd* pParentWnd, UINT nID);

	BOOL CreateControl(LPCTSTR lpszCaption, int labelEdit, DWORD dwStyle, 
			int x, int y, CWnd* pParentWnd, UINT nID);
	void Paint(CDC *pDc);
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVGEdit)
	//}}AFX_VIRTUAL

		// Generated message map functions
protected:
	//{{AFX_MSG(CVGEdit)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CVGPickupPos: public CControl
{
	public:

	CVGData	*m_pickup;
	CVGData	*m_frontPickuType;
	CVGData	*m_frontPickupPosition;
	CVGData	*m_frontPickupAngle;
	CVGData	*m_rearPickuType;
	CVGData	*m_rearPickupPosition;
	CVGData	*m_rearPickupAngle;
	CRgn	m_rearTop, m_rearMid, m_rearBot;
	CRgn	m_frontTop, m_frontMid, m_frontBot;
	BOOL	m_bTracking;

	CVGPickupPos();
	void AttachVGData(CVGData *, CVGData *, CVGData *, CVGData *, CVGData *, CVGData *, CVGData *);
	BOOL CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
			int x, int y, CWnd* pParentWnd, UINT nID);
	void OnMouseAction(CPoint);
	void Paint(CDC *pDc);
	
	CMaskedBitmap	m_backImage;
	CMaskedBitmap	m_pickupSingle1;
	CMaskedBitmap	m_pickupDouble1;
	CMaskedBitmap	m_pickupSingle2;
	CMaskedBitmap	m_pickupDouble2;

		// Generated message map functions
protected:
	//{{AFX_MSG(CVGPickupPos)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
};


class CVGSection: public CControl
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


class CListBoxCustom : public CListBox
{
public:
	//{{AFX_MSG(CListBoxCustom)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CVGList: public CControl
{
	public:
	CVGList();
	BOOL CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
			int x, int y, int width, int height, CControl* pParentWnd, UINT nID);

	//void OnMouseAction(CPoint);
	void Paint(CDC *pDc);
	
	CBrush			m_brush;
	BOOL			m_bTracking;
	CListBoxCustom	m_listBox;
	CControl	*m_parent;
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVGList)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
		// Generated message map functions
protected:
	//{{AFX_MSG(CVGList)
	afx_msg void OnPaint();
	afx_msg void OnSelChange();
	afx_msg void OnKillFocus();
	afx_msg void OnDblClk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
