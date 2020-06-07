// controls.cpp : implementation of the CControl class
//

#include <stdio.h>
#include <io.h>
#include <time.h>
#include <typeinfo>
#include "stdafx.h"
#include "VEditor.h"
#include "MainFrm.h"
#include "tools.h"
#include "VG-88.h"
#include "controls.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CControl

CControl::CControl()
{
	m_font = &g_font2;
}

CControl::~CControl()
{
}


BEGIN_MESSAGE_MAP(CControl, CWnd)
	//{{AFX_MSG_MAP(CControl)
	ON_WM_CREATE ()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CControl message handlers

BOOL CControl::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.lpszClass = AfxRegisterWndClass(0, 
		AfxGetApp()->LoadCursor(IDC_CURSOR), NULL, NULL);
//HBRUSH(COLOR_WINDOW + 1)
	return TRUE;
}


int CControl::OnCreate (LPCREATESTRUCT lpcs)
{
	m_vgData = NULL;
	m_listValue = NULL;

	return 0;
}


BOOL CControl::CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
							 const RECT& rect, CWnd* pParentWnd, UINT nID, unsigned long cwndStyle)
{
	if (!Create(NULL, lpszCaption, WS_CHILD | WS_VISIBLE | cwndStyle,
		rect, pParentWnd, nID, NULL))
		return -1;

	m_dwStyle = dwStyle;
	EnableWindow(FALSE);

	return 1;
}



void CControl::AttachVGData(CVGData *vgData)
{
	int oldValue = -1;
	int newValue = -1;

	m_vgData = vgData;

	if (m_vgData)
		EnableWindow(TRUE);
	else
		EnableWindow(FALSE);

	Invalidate(FALSE);
}


void CControl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();
	
	CWnd::OnLButtonDown(nFlags, point);
}


void CControl::OnRButtonDown(UINT nFlags, CPoint point)
{
	char **tabString;
	char caption[50];
	RECT	rect, desktopRect;
	int max, len, width, height, posx, posy;
	int i;

	if (!m_vgData)
		return;

	if (m_listValue)
		delete m_listValue;

	m_listValue = new CVGList;
	
	GetWindowText(caption, 50);
	GetWindowRect(&rect);

	SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID) &desktopRect, 0);
	tabString = m_vgData->getTabString();

	max = 0;

	// estimate the width
	for (i = 0; i < m_vgData->getRange(); i++)
	{
		len = strlen(tabString[i]);

		if (len > max)
			max = len;
	}

	width = 12 + max * 7;
	if (width < 100)
		width = 100;

	// estimate the height
	posy = rect.top;
	height = 22 + m_vgData->getRange() * 12;

	if (height > desktopRect.bottom - desktopRect.top)
		height = desktopRect.bottom - desktopRect.top;

	if (height + posy > desktopRect.bottom)
		posy = desktopRect.bottom - height;

	if (rect.right + width < desktopRect.right)
		posx = rect.right;
	else
		posx = rect.left - width;

	m_listValue->CreateControl(caption, 0, posx, posy, width, height, this, 0);

	// Disable the redraw
	m_listValue->m_listBox.SendMessage(WM_SETREDRAW, FALSE, 0);

	for (i = 0; i < m_vgData->getRange(); i++)
		m_listValue->m_listBox.AddString(tabString[i]);

	// Reactivate the redraw
	m_listValue->m_listBox.SendMessage(WM_SETREDRAW, TRUE, 0);

	m_listValue->AttachVGData(m_vgData);
	m_listValue->m_listBox.SetCurSel(m_vgData->getValue());
	m_listValue->m_listBox.SetFocus();

	m_vgData->freeTabString(tabString);
	

	//CWnd::OnRButtonDown(nFlags, point);
}


void CControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CWnd *pCnwd, *pCnwd2;
	BOOL changePanel = FALSE;

	switch (nChar)
	{
		case VK_TAB:
			if (::GetKeyState(VK_CONTROL) < 0)
				changePanel = TRUE;
			else
			{
				CWnd *first, *last;

				first = GetParent()->GetNextDlgTabItem(NULL, FALSE);
				last  = GetParent()->GetNextDlgTabItem(first, TRUE);

				if (::GetKeyState(VK_SHIFT) < 0)
				{
					pCnwd2 = GetParent()->GetNextDlgTabItem(this, TRUE);

					if (pCnwd2 == last)
						changePanel = TRUE;
				}
				else
				{
					pCnwd2 = GetParent()->GetNextDlgTabItem(this, FALSE);

					if (pCnwd2 == first)
						changePanel = TRUE;
				}
			}

			if (changePanel)
			{
				int i = 50;

				pCnwd2 = NULL;
				pCnwd = GetParent();

				while (!pCnwd2 && i)
				{
					if (::GetKeyState(VK_SHIFT) < 0)
						pCnwd = GetParent()->GetParent()->GetNextDlgTabItem(pCnwd, TRUE);
					else
						pCnwd = GetParent()->GetParent()->GetNextDlgTabItem(pCnwd, FALSE);

					if (pCnwd)
					{
						pCnwd2 = pCnwd->GetNextDlgTabItem(NULL, FALSE);

						if (pCnwd2 && ::GetKeyState(VK_SHIFT) < 0)
							pCnwd2 = pCnwd->GetNextDlgTabItem(pCnwd2, TRUE);
					}

					if (!pCnwd2->IsWindowEnabled() || pCnwd2 == pCnwd)
						pCnwd2 = NULL;

					i--;
				}
			}

			if (pCnwd2)
				pCnwd2->SetFocus();


			break;

		case VK_INSERT:
			GetParent()->PostMessage(WM_KEYDOWN, VK_INSERT);
			break;

		case VK_HOME:
		case VK_END:
		case VK_DOWN:
		case VK_RIGHT:
		case VK_UP:
		case VK_LEFT:
		case VK_NEXT:
		case VK_PRIOR:
		case VK_DELETE:
		case VK_ADD:
		case VK_SUBTRACT:
			if (!m_vgData)
				return;

			switch (nChar)
			{
				int step;

				case VK_HOME:
					m_vgData->setValue(m_vgData->getFirstValue());
					break;

				case VK_END:
					m_vgData->setValue(m_vgData->getFirstValue() + m_vgData->getRange() - 1);
					break;

				case VK_DELETE:
					m_vgData->setValue(m_vgData->getFirstValue() + (m_vgData->getRange() - 1) / 2);
					break;

				case VK_UP:
				case VK_RIGHT:
				case VK_ADD:
					if (::GetKeyState(VK_CONTROL) < 0)
						step = 10;
					else
						step = 1;

					m_vgData->setValue(m_vgData->getValue() + step);
					break;

				case VK_DOWN:
				case VK_LEFT:
				case VK_SUBTRACT:
					if (::GetKeyState(VK_CONTROL) < 0)
						step = 10;
					else
						step = 1;

					m_vgData->setValue(m_vgData->getValue() - step);
					break;

				case VK_NEXT:
					m_vgData->setValue(m_vgData->getValue() + 10);
					break;

				case VK_PRIOR:
					m_vgData->setValue(m_vgData->getValue() - 10);
					break;
			}

			if (g_currentPatch)
			{
				g_currentPatch->checkPatch();
				g_currentPatch->initializePatchObjects();
			}

			//m_parent->SendMessage(WM_COMMAND, (int) LOWORD(IDC_SEL_CHANGE), (long) this);

			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.OnPatchChange();
			((CMainFrame *) AfxGetMainWnd())->m_patchWnd.m_patchWindowLayer.OnPatchChange();

			//Invalidate(FALSE);

			break;
	
		default:
			CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

void CControl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CPoint point(0, 0);

	switch(nChar)
	{
		case VK_RETURN:
			OnRButtonDown(0, point);
			return;
			break;
	}

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}


BOOL CControl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch (wParam)
	{
		case IDC_POPUP_CANCEL:
			delete m_listValue;
			m_listValue = NULL;
			//SetFocus();
			break;

		case IDC_POPUP_VALIDATE:
			delete m_listValue;
			m_listValue = NULL;
			SetFocus();
			break;

		case IDC_SEL_CHANGE:
			GetParent()->SendMessage(WM_COMMAND, (int) LOWORD(GetDlgCtrlID()), (long) this);
	}
	
	return CWnd::OnCommand(wParam, lParam);
}



void CControl::OnSetFocus(CWnd* pOldWnd) 
{
	Invalidate(FALSE);
}

void CControl::OnKillFocus(CWnd* pNewWnd)
{
	Invalidate(FALSE);
}


BOOL CControl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	int step;

	if (::GetKeyState(VK_CONTROL) < 0)
		step = 10;
	else
		step = 1;

	m_vgData->setValue(m_vgData->getValue() + ((zDelta / WHEEL_DELTA) * step));

	if (g_currentPatch)
	{
		g_currentPatch->checkPatch();
		g_currentPatch->initializePatchObjects();
	}

	((CMainFrame *) AfxGetMainWnd())->m_chainWnd.OnPatchChange();
	((CMainFrame *) AfxGetMainWnd())->m_patchWnd.m_patchWindowLayer.OnPatchChange();
	((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

BEGIN_MESSAGE_MAP(CVGKnob, CControl)
	//{{AFX_MSG_MAP(CVGKnob)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CVGKnob::CVGKnob()
{
	m_bTracking = FALSE;
}


BOOL CVGKnob::CreateImageControl(LPCTSTR lpszCaption, int x, int y, CMaskedBitmap *bitmap, int imageCount, CWnd* pParentWnd, UINT nID)
{
	BITMAP bm;
	int ret;

	m_knob = bitmap;
	m_bitmapImageCount = imageCount;
	m_sens = 0;
	m_emptyImage = TRUE;
	m_dataPosition = DATA_NONE;
	

	bitmap->GetObject (sizeof (BITMAP), &bm);

	m_imageWidth = bm.bmWidth;
	m_imageHeight = bm.bmHeight / (imageCount + 1);

	ret = CreateControl(lpszCaption, 0, x, y, pParentWnd, nID);
	m_labelPosition = DATA_NONE;

	return ret;
}


BOOL CVGKnob::CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
							 int x, int y, CWnd* pParentWnd, UINT nID)
{
	m_labelPosition = DATA_BOTTOM;

	switch (dwStyle)
	{
		case CTRL_AMPKNOB1:
			m_knob = &g_knob1;
			m_bitmapImageCount = 19;
			m_sens = 0;
			m_imageWidth = 42;
			m_imageHeight = 43;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOP;

			break;

		case CTRL_AMPKNOB2:
			m_knob = &g_knob2;
			m_bitmapImageCount = 3;
			m_sens = 0;
			m_imageWidth = 50;
			m_imageHeight = 48;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOP;

			break;

		case CTRL_SWITCH1:
			m_knob = &g_switch1;
			m_bitmapImageCount = 2;
			m_sens = 0;
			m_imageWidth = 43;
			m_imageHeight = 43;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOP;

			break;

		case CTRL_VFADER1:
			m_knob = &g_faderv1;
			m_bitmapImageCount = 50;
			m_sens = 1;
			m_imageWidth = 18;
			m_imageHeight = 98;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOP;

			break;

		case CTRL_VFADERORGAN:
			m_knob = &g_organSlider;
			m_bitmapImageCount = 100;
			m_sens = 1;
			m_imageWidth = 37;
			m_imageHeight = 160;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOP;

			break;

		case CTRL_HFADER1:
			m_knob = &g_faderh1;
			m_bitmapImageCount = 100;
			m_sens = 0;
			m_imageWidth = 119;
			m_imageHeight = 24;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOPLEFT;

			break;

		case CTRL_VGKNOB1:
			m_knob = &g_knob3;
			m_bitmapImageCount = 19;
			m_sens = 0;
			m_imageWidth = 42;
			m_imageHeight = 43;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOP;

			break;

		case CTRL_VGKNOB2:
			m_knob = &g_knob4;
			m_bitmapImageCount = 19;
			m_sens = 0;
			m_imageWidth = 27;
			m_imageHeight = 35;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOP;

			break;

		case CTRL_VGKNOB3:
			m_knob = &g_knob6;
			m_bitmapImageCount = 19;
			m_sens = 0;
			m_imageWidth = 11;
			m_imageHeight = 23;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOP;

			break;

		case CTRL_GTKNOB1:
			m_knob = &g_knob7;
			m_bitmapImageCount = 19;
			m_sens = 0;
			m_imageWidth = 42;
			m_imageHeight = 43;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOP;

			break;

		case CTRL_SELECTOR:
			m_knob = &g_selector;
			m_bitmapImageCount = 5;
			m_sens = 0;
			m_imageWidth = 62;
			m_imageHeight = 43;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_TOP;

			break;

		case CTRL_MIC1:
			m_knob = &g_mic1;
			m_bitmapImageCount = 11;
			m_sens = 1;
			m_imageWidth = 30;
			m_imageHeight = 60;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_NONE;

			break;

		case CTRL_MIC2:
			m_knob = &g_mic2;
			m_bitmapImageCount = 11;
			m_sens = 1;
			m_imageWidth = 30;
			m_imageHeight = 60;
			m_emptyImage = FALSE;
			m_dataPosition = DATA_NONE;

			break;
	}

	if (m_dataPosition == DATA_NONE)
	{
		if (!CControl::CreateControl(lpszCaption, dwStyle, 
							 CRect(x, y, x + m_imageWidth, y + m_imageHeight + LABEL_HEIGHT), pParentWnd, nID))
			return -1;
	}
	else
	{
		if (!CControl::CreateControl(lpszCaption, dwStyle, 
							 CRect(x, y, x + m_imageWidth, y + m_imageHeight + LABEL_HEIGHT), pParentWnd, nID, WS_TABSTOP))
			return -1;
	}

	

	return 1;
}

void CVGKnob::OnPaint() 
{
	CFont *pOldFont;
	CPaintDC dc(this); // device context for painting
	CDC dcTemp;
	CBitmap	bitmpap;
	CBitmap *pBitmapOld;
	char	 caption[50];
	int heigthLabel = 0;

	GetWindowText(caption, 50);

	if (caption[0] != '\0' && m_labelPosition != DATA_NONE)
		heigthLabel = 10;

	// All painting are done on the memory device context to avoid flicker
	dcTemp.CreateCompatibleDC (&dc);
	dcTemp.SetMapMode (dc.GetMapMode());
	dcTemp.SetBkMode(TRANSPARENT);
	bitmpap.CreateCompatibleBitmap(&dc, m_imageWidth, m_imageHeight + heigthLabel);
	pBitmapOld = dcTemp.SelectObject(&bitmpap);
	pOldFont = dcTemp.SelectObject(m_font);

	Paint(&dcTemp);

	// Once all painting are done, copy the result to the display
	dc.BitBlt (0, 0, m_imageWidth, m_imageHeight + heigthLabel, &dcTemp, 0, 0, SRCCOPY);

	dcTemp.SelectObject(pOldFont);
	dcTemp.SelectObject(pBitmapOld);
}


void CVGKnob::Paint(CDC *pDc)
{
	CDC		 dcMem;
	CBitmap* pOldBitmap;
	BITMAP	 bm;
	char	 value[50];
	char	 caption[50];
	int		 pos;

	dcMem.CreateCompatibleDC (pDc);
	dcMem.SetMapMode (pDc->GetMapMode ());

	pOldBitmap = dcMem.SelectObject (m_knob);
	m_knob->GetObject (sizeof (BITMAP), &bm);

	if (m_sens)
	{
		if (m_vgData == NULL)
		{
			pos = 0;
			strcpy(value, "-");
		}
		else
		{
			pos = ((m_bitmapImageCount * m_vgData->getValue()) / m_vgData->getRange()) * m_imageWidth;
			pos += (((m_bitmapImageCount / m_vgData->getRange()) - 1) * ((m_vgData->getValue() + 1 - m_vgData->getFirstValue()) / m_vgData->getRange())) * m_imageWidth;

			m_vgData->getString(value);
		}
	
		pDc->BitBlt (0, 0 , m_imageWidth, m_imageHeight, &dcMem, pos, 0, SRCCOPY);

		if (m_dataPosition != DATA_NONE)
		{
			if (GetFocus() == this)
				pDc->SetTextColor(RGB(216, 247, 45));
			else
				pDc->SetTextColor(RGB(238, 142, 27));

			pDc->DrawText(value, -1, CRect(0, 0 , m_imageWidth, 30), DT_CENTER | DT_EXPANDTABS);
		}

		GetWindowText(caption, 50);

		if (caption[0] != '\0' && m_labelPosition != DATA_NONE)
		{
			if (GetFocus() == this)
			{
				pDc->SetTextColor(RGB(255, 255, 255));
				pDc->SelectObject(&g_font3);
			}
			else
			{
				pDc->SetTextColor(RGB(228, 228, 228));
				pDc->SelectObject(&g_font1);
			}

			dcMem.SelectObject (&g_empty);
			pDc->BitBlt (0, m_imageHeight , m_imageWidth, 8, &dcMem, 0, 0, SRCCOPY);
			pDc->DrawText(caption, -1, CRect(0, m_imageHeight, m_imageWidth, m_imageHeight + 10), DT_CENTER);
		}
	}
	else
	{
		if (m_vgData == NULL)
		{
			pos = 0;
			strcpy(value, "-");

			if (!m_emptyImage)
				pDc->BitBlt (0, 0 , m_imageWidth, m_imageHeight, &dcMem, 0, pos, SRCCOPY);
			else
			{
				pos = m_bitmapImageCount * m_imageHeight;
				pDc->BitBlt (0, 0 , m_imageWidth, m_imageHeight, &dcMem, 0, pos, SRCCOPY);
			}
		}
		else
		{
			pos = ((m_bitmapImageCount * (m_vgData->getValue() - m_vgData->getFirstValue())) / m_vgData->getRange()) * m_imageHeight;

			m_vgData->getString(value);

			pDc->BitBlt (0, 0 , m_imageWidth, m_imageHeight, &dcMem, 0, pos, SRCCOPY);
		}
	

		if (GetFocus() == this)
			pDc->SetTextColor(RGB(216, 247, 45));
		else
			pDc->SetTextColor(RGB(238, 142, 27));
	
		if (m_dwStyle == DATA_TOPLEFT)
				pDc->DrawText(value, -1, CRect(0, 0 , m_imageWidth, 15), DT_LEFT  | DT_EXPANDTABS);
		else if (m_dataPosition != DATA_NONE)
		{
			if (m_dwStyle == 11)
			{
				if (GetFocus() == this)
					pDc->SetTextColor(RGB(216, 247, 45));
				else
					pDc->SetTextColor(RGB(238, 142, 27));

				pDc->SelectObject(&g_font1);
			}


			pDc->DrawText(value, -1, CRect(0, 0 , m_imageWidth, 15), DT_CENTER  | DT_EXPANDTABS);
		}

		GetWindowText(caption, 50);

		if (caption[0] != '\0' && m_labelPosition != DATA_NONE)
		{
			if (GetFocus() == this)
			{
				pDc->SetTextColor(RGB(255, 255, 255));
				pDc->SelectObject(&g_font3);
			}
			else
			{
				pDc->SetTextColor(RGB(228, 228, 228));
				pDc->SelectObject(&g_font1);
			}

			dcMem.SelectObject (&g_empty);
			pDc->BitBlt (0, m_imageHeight , m_imageWidth, 8, &dcMem, 0, 0, SRCCOPY);
			pDc->DrawText(caption, -1, CRect(0, m_imageHeight, m_imageWidth, m_imageHeight + 10), DT_CENTER);
		}
		
	}

}


void CVGKnob::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CControl::OnLButtonDown(nFlags, point);

	if (m_vgData)
	{
		m_bTracking = TRUE;
		SetCapture();

		OnMouseAction(point);
	}
}


void CVGKnob::OnMouseMove(UINT nFlags, CPoint point)
{
	OnMouseAction(point);
}


void CVGKnob::OnMouseAction(CPoint point)
{
	double	value;

	if (m_bTracking && m_vgData)
	{
		if (m_dwStyle == 3)
		{
			point.x -= 25;
			point.y -= 25;

			if (point.y < 0)
				m_vgData->setValue(1);
			else
				m_vgData->setValue(0);

			Invalidate(FALSE);
		}
		else if (m_dwStyle == 1 || m_dwStyle == 2 || m_dwStyle == 6 || m_dwStyle == 7 || m_dwStyle == 11 || m_dwStyle == 12)
		{
			if (m_dwStyle == 7)
			{
				point.x -= 14;
				point.y -= 22;
			}
			else if (m_dwStyle == 2)
			{
				point.x -= 24;
				point.y -= 24;
			}
			else if (m_dwStyle == 11)
			{
				point.x -= 5;
				point.y -= 16;
			}
			else
			{
				point.x -= 20;
				point.y -= 24;
			}


			value = point.x / sqrt(point.x * point.x + point.y * point.y);
			value = acos(value) / 3.14159265358979;

			if (point.x < 0 && point.y >= 0)
				value = (value - 0.5) / 2;
			else if (point.x < 0 && point.y <= 0)
				value = 0.25 + ((1 - value) / 2);
			else if (point.x >= 0 && point.y <= 0)
				value = 0.5 + (((1 - value) - 0.5) / 2);
			else
				value = 0.75 + value / 2;

			if (m_dwStyle == 1 || m_dwStyle == 6 || m_dwStyle == 7 || m_dwStyle == 11 || m_dwStyle == 12)
			{
				if (value < 0.125)
					value = 0.125;

				if (value > 0.875)
					value = 0.875;

				m_vgData->setValue((int) (m_vgData->getFirstValue() + ((m_vgData->getRange() - 1) * (value - 0.125) / 0.75)));
			}
			else if (m_dwStyle == 2)
			{
				if (value < 0.375)
					value = 0.375;

				if (value > 0.625)
					value = 0.625;

				m_vgData->setValue((int) (m_vgData->getFirstValue() +  ((m_vgData->getRange() - 1) * (value - 0.375) / 0.25)));
			}

			Invalidate(FALSE);
		}
		else if (m_dwStyle == 4)
		{
			value = 85 - point.y;

			if (value < 0)
				value = 0;

			if (value > 50)
				value = 50;

			value = value / 50;
			m_vgData->setValue((int) (m_vgData->getFirstValue() + ((m_vgData->getRange() - 1) * value)));

			Invalidate(FALSE);
		}
		else if (m_dwStyle == CTRL_VFADERORGAN)
		{
			value = point.y - 32 ;

			if (value < 0)
				value = 0;

			if (value > 100)
				value = 100;

			value = value / 100;

			m_vgData->setValue((int) (m_vgData->getFirstValue() + ((m_vgData->getRange() - 1) * value)));
			Invalidate(FALSE);
		}
		else if (m_dwStyle == CTRL_MIC1 || m_dwStyle == CTRL_MIC2)
		{
			value = point.y -5 ;

			if (value < 0)
				value = 0;

			if (value > 33)
				value = 33;

			value = value / 33;
			m_vgData->setValue((int) (m_vgData->getFirstValue() + ((m_vgData->getRange() - 1) * value)));

			Invalidate(FALSE);
		}
		else if (m_dwStyle == 5)
		{
			value = point.x - 9;

			if (value < 0)
				value = 0;

			if (value > 100)
				value = 100;

			value = value / 100;
			m_vgData->setValue((int) (m_vgData->getFirstValue() + ((m_vgData->getRange() - 1) * value)));

			Invalidate(FALSE);
		}
		else if (m_dwStyle == 13)
		{
			value = point.x - 10;

			if (value < 0)
				value = 0;

			if (value > 30)
				value = 30;

			value = value / 30;
			m_vgData->setValue((int) (m_vgData->getFirstValue() + ((m_vgData->getRange() - 1) * value)));

			Invalidate(FALSE);
		}

		if (g_currentPatch)
		{
			g_currentPatch->checkPatch();
			g_currentPatch->initializePatchObjects();
		}

		/*DWORD message;
		message = MAKELONG(MAKEWORD(176, 1), MAKEWORD(m_vgData->getValue(), 0));
		midiOutShortMsg(((CMainFrame *) AfxGetMainWnd())->m_hmo, message);
		*/
		// Notify the parent window that a refresh of the panel is needed
		GetParent()->PostMessage(WM_COMMAND, (int) LOWORD(GetDlgCtrlID()), (long) this);
	}
}


void CVGKnob::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bTracking && m_vgData)
	{
		m_bTracking = FALSE;
		ReleaseCapture();

		((CMainFrame *) AfxGetMainWnd())->m_chainWnd.OnPatchChange();
		((CMainFrame *) AfxGetMainWnd())->m_patchWnd.m_patchWindowLayer.OnPatchChange();

		if (m_vgData->m_needSaving)
			((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();
	}
}




///////////////




BEGIN_MESSAGE_MAP(CVGButton, CControl)
	//{{AFX_MSG_MAP(CVGButton)
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CVGButton::CVGButton()
{
}



BOOL CVGButton::CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
							 int x, int y, CWnd* pParentWnd, UINT nID)
{
	switch (dwStyle)
	{
		case 1:
			m_button = &g_button1;
			m_bitmapImageCount = 2;
			m_sens = 0;
			m_imageWidth = 22;
			m_imageHeight = 18;
			m_dataPosition = DATA_BOTTOM;

			if (!CControl::CreateControl(lpszCaption, dwStyle, 
							 CRect(x, y, x + m_imageWidth, y + m_imageHeight), pParentWnd, nID, WS_TABSTOP))
				return -1;

			break;

		case 2:
			m_button = &g_led1;
			m_bitmapImageCount = 2;
			m_sens = 0;
			m_imageWidth = 22;
			m_imageHeight = 18;
			m_dataPosition = DATA_NONE;

			if (!CControl::CreateControl(lpszCaption, dwStyle, 
							 CRect(x, y, x + m_imageWidth, y + m_imageHeight), pParentWnd, nID))
				return -1;

			break;


		case 3:
			m_button = &g_button2;
			m_bitmapImageCount = 2;
			m_sens = 0;
			m_imageWidth = 27;
			m_imageHeight = 25;
			m_dataPosition = DATA_BOTTOM;

			if (!CControl::CreateControl(lpszCaption, dwStyle, 
							 CRect(x, y, x + m_imageWidth, y + m_imageHeight), pParentWnd, nID, WS_TABSTOP))
				return -1;

			break;

		case 4:
			m_button = &g_led2;
			m_bitmapImageCount = 2;
			m_sens = 0;
			m_imageWidth = 22;
			m_imageHeight = 18;
			m_dataPosition = DATA_NONE;

			if (!CControl::CreateControl(lpszCaption, dwStyle, 
							 CRect(x, y, x + m_imageWidth, y + m_imageHeight), pParentWnd, nID))
				return -1;

			break;

		case 5:
			m_button = &g_button3;
			m_bitmapImageCount = 2;
			m_sens = 0;
			m_imageWidth = 22;
			m_imageHeight = 18;
			m_dataPosition = DATA_NONE;

			if (!CControl::CreateControl(lpszCaption, dwStyle, 
							 CRect(x, y, x + m_imageWidth, y + m_imageHeight), pParentWnd, nID, WS_TABSTOP))
				return -1;

			break;

		case 6:
		case 7:
		case 8:
		case 9:
			switch (dwStyle)
			{
			case 6:
				m_button = &g_buttonSave;
				break;

			case 7:
				m_button = &g_buttonCopy;
				break;

			case 8:
				m_button = &g_buttonDelete;
				break;

			case 9:
				m_button = &g_buttonRename;
				break;
			}

			
			m_bitmapImageCount = 2;
			m_sens = 0;
			m_imageWidth = 18;
			m_imageHeight = 19;
			m_dataPosition = DATA_NONE;

			if (!CControl::CreateControl(lpszCaption, dwStyle, 
							 CRect(x, y, x + m_imageWidth, y + m_imageHeight), pParentWnd, nID, WS_TABSTOP))
				return -1;

			break;

	}

	return 1;
}


void CVGButton::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
		case VK_SPACE:
			if (m_vgData)
			{
					m_vgData->setValue(1 - m_vgData->getValue());

					Invalidate(FALSE);

					// Notify the parent window that a refresh of the panel is needed
					GetParent()->PostMessage(WM_COMMAND, (int) LOWORD(GetDlgCtrlID()), (long) this);
			}
			break;

		default:
			CControl::OnChar(nChar, nRepCnt, nFlags);
	}
}

void CVGButton::OnPaint() 
{
	CFont *pOldFont;
	CPaintDC dc(this); // device context for painting
	CDC dcTemp;
	CBitmap	bitmpap;
	CBitmap *pBitmapOld;
	

	// All painting are done on the memory device context to avoid flicker
	dcTemp.CreateCompatibleDC (&dc);
	dcTemp.SetMapMode (dc.GetMapMode());
	dcTemp.SetBkMode(TRANSPARENT);
	bitmpap.CreateCompatibleBitmap(&dc, m_imageWidth, m_imageHeight);
	pBitmapOld = dcTemp.SelectObject(&bitmpap);
	pOldFont = dcTemp.SelectObject(m_font);

	Paint(&dcTemp);

	// Once all painting are done, copy the result to the display
	dc.BitBlt (0, 0, m_imageWidth, m_imageHeight, &dcTemp, 0, 0, SRCCOPY);

	dcTemp.SelectObject(pOldFont);
	dcTemp.SelectObject(pBitmapOld);

}


void CVGButton::Paint(CDC *pDc)
{
	CDC		 dcMem;
	CBitmap* pOldBitmap;
	BITMAP	 bm;
	char	 value[50];
	int		 pos;
	int		 offset = 0;

	dcMem.CreateCompatibleDC (pDc);
	dcMem.SetMapMode (pDc->GetMapMode ());

	pOldBitmap = dcMem.SelectObject (m_button);
	m_button->GetObject (sizeof (BITMAP), &bm);


	if (m_vgData == NULL)
	{
		pos = 0;
		strcpy(value, ".");
	}
	else
	{
		pos = ((m_bitmapImageCount * m_vgData->getValue()) / m_vgData->getRange()) * m_imageHeight;

		strcpy(value, "_");

		if (m_vgData->getValue() == 0)
			offset = 1;
	}

	pDc->BitBlt (0, 0 , m_imageWidth, m_imageHeight, &dcMem, 0, pos, SRCCOPY);


	if (m_dataPosition != DATA_NONE)
	{
		if (GetFocus() == this)
			pDc->SetTextColor(RGB(216, 247, 45));
		else
			pDc->SetTextColor(RGB(238, 142, 27));

		pDc->DrawText(value, -1, CRect(0, -1 - offset, m_imageWidth - 3, 20), DT_CENTER);
	}	

	dcMem.SelectObject(pOldBitmap);
}


void CVGButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CControl::OnLButtonDown(nFlags, point);

	if (m_vgData)
	{
		m_vgData->setValue(1 - m_vgData->getValue());

		Invalidate(FALSE);

		// Notify the parent window that a refresh of the panel is needed
		GetParent()->PostMessage(WM_COMMAND, (int) LOWORD(GetDlgCtrlID()), (long) this);
	}
}



///////////////




BEGIN_MESSAGE_MAP(CVGEdit, CControl)
	//{{AFX_MSG_MAP(CVGEdit)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CVGEdit::CVGEdit()
{
}



#define ELABEL_WIDTH	38

BOOL CVGEdit::CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
							 int x, int y, CWnd* pParentWnd, UINT nID)
{
	switch (dwStyle)
	{
		case 1:
			m_sens = 0;
			m_imageWidth = 124;
			m_imageHeight = 15;

			break;


		case 2:
			m_sens = 0;
			m_imageWidth = 69;
			m_imageHeight = 15;

			break;

	}

	if (!CControl::CreateControl(lpszCaption, dwStyle, 
							 CRect(x , y, x + m_imageWidth + ELABEL_WIDTH, y + m_imageHeight), pParentWnd, nID, WS_TABSTOP))
		return -1;

	

	return 1;
}

void CVGEdit::OnPaint() 
{
	CFont *pOldFont;
	CPaintDC dc(this); // device context for painting
	/*CDC dcTemp;
	CBitmap	bitmpap;
	CBitmap *pBitmapOld;
	*/
	// All painting are done on the memory device context to avoid flicker
	//dcTemp.CreateCompatibleDC (&dc);
	//dcTemp.SetMapMode (dc.GetMapMode());
	//dcTemp.SetBkMode(TRANSPARENT);
	//bitmpap.CreateCompatibleBitmap(&dc, m_imageWidth, m_imageHeight);
	//pBitmapOld = dcTemp.SelectObject(&bitmpap);
	//pOldFont = dcTemp.SelectObject(m_font);

	dc.SetBkMode(TRANSPARENT);
	pOldFont = dc.SelectObject(m_font);

	//Paint(&dcTemp);
	Paint(&dc);

	// Once all painting are done, copy the result to the display
	//dc.BitBlt (0, 0, m_imageWidth + ELABEL_WIDTH, m_imageHeight, &dcTemp, 0, 0, SRCCOPY);

	//dcTemp.SelectObject(pOldFont);
	//dcTemp.SelectObject(pBitmapOld);
	dc.SelectObject(pOldFont);
}


void CVGEdit::Paint(CDC *pDc)
{
	CDC		 dcMem;
	CBitmap* pOldBitmap;
	char	 caption[50];

	CPen pen(PS_SOLID, 2, RGB(76, 76, 76));
	char	 value[50];

	if (m_vgData == NULL)
		strcpy(value, "-");
	else
		m_vgData->getString(value);

	pDc->FillSolidRect(ELABEL_WIDTH, 0, ELABEL_WIDTH + m_imageWidth, m_imageHeight, RGB(43, 48, 51));

	pDc->SelectObject(&pen);
	pDc->MoveTo(ELABEL_WIDTH + m_imageWidth,0);
	pDc->LineTo(ELABEL_WIDTH + m_imageWidth, m_imageHeight);
	pDc->MoveTo(ELABEL_WIDTH, m_imageHeight);
	pDc->LineTo(ELABEL_WIDTH + m_imageWidth, m_imageHeight);

	pDc->SelectStockObject(BLACK_PEN);
	pDc->MoveTo(ELABEL_WIDTH, 0);
	pDc->LineTo(ELABEL_WIDTH + m_imageWidth - 1, 0);
	pDc->MoveTo(ELABEL_WIDTH, 0);
	pDc->LineTo(ELABEL_WIDTH, m_imageHeight - 1);

	GetWindowText(caption, 50);

	if (caption[0] != '\0')
	{
		dcMem.CreateCompatibleDC (pDc);
		dcMem.SetMapMode (pDc->GetMapMode ());

		if (GetFocus() == this)
		{
			pDc->SetTextColor(RGB(255, 255, 255));
			pDc->SelectObject(&g_font3);
		}
		else
		{
			pDc->SetTextColor(RGB(228, 228, 228));
			pDc->SelectObject(&g_font1);
		}

		pOldBitmap = dcMem.SelectObject (&g_empty);
		pDc->BitBlt (0, 2 , ELABEL_WIDTH, 8, &dcMem, 0, 0, SRCCOPY);
		pDc->DrawText(caption, -1, CRect(0, 2, ELABEL_WIDTH, 13), DT_LEFT);
		dcMem.SelectObject(pOldBitmap);
	}

	// Draw the data
	pDc->SelectObject(&g_font2);

	if (GetFocus() == this)
		pDc->SetTextColor(RGB(216, 247, 45));
	else
		pDc->SetTextColor(RGB(238, 142, 27));

	pDc->DrawText(value, -1, CRect(2 + ELABEL_WIDTH, 2 , ELABEL_WIDTH + m_imageWidth, 30), DT_LEFT | DT_EXPANDTABS);
}



void CVGEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CControl::OnLButtonDown(nFlags, point);
}



void CVGEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CControl::OnKillFocus(pNewWnd);
	
	Invalidate(FALSE);
	
}

void CVGEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CControl::OnSetFocus(pOldWnd);
	
	Invalidate(FALSE);
}


BEGIN_MESSAGE_MAP(CVGPickupPos, CControl)
	//{{AFX_MSG_MAP(CVGPickupPos)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CVGPickupPos::CVGPickupPos()
{
}


BOOL CVGPickupPos::CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
							 int x, int y, CWnd* pParentWnd, UINT nID)
{
	m_backImage.LoadBitmap(IDB_PICKUPPOS);
	m_pickupSingle1.LoadBitmap(IDB_PICKUPSINGLE1);
	m_pickupDouble1.LoadBitmap(IDB_PICKUPDOUBLE1);
	m_pickupSingle2.LoadBitmap(IDB_PICKUPSINGLE2);
	m_pickupDouble2.LoadBitmap(IDB_PICKUPDOUBLE2);

	m_bitmapImageCount = 1;
	m_sens = 0;
	m_imageWidth = 180;
	m_imageHeight = 80;

	if (!CControl::CreateControl(lpszCaption, dwStyle, 
			 CRect(x, y, x + m_imageWidth, y + m_imageHeight), pParentWnd, nID))
		return -1;

	return 1;
}

void CVGPickupPos::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC dcTemp;
	CBitmap	bitmpap;
	CBitmap *pBitmapOld;


// All painting are done on the memory device context to avoid flicker
	dcTemp.CreateCompatibleDC (&dc);
	dcTemp.SetMapMode (dc.GetMapMode());
	bitmpap.CreateCompatibleBitmap(&dc, m_imageWidth, m_imageHeight);
	pBitmapOld = dcTemp.SelectObject(&bitmpap);

	Paint(&dcTemp);

	// Once all painting are done, copy the result to the display
	dc.BitBlt (0, 0, m_imageWidth, m_imageHeight, &dcTemp, 0, 0, SRCCOPY);

	dcTemp.SelectObject(pBitmapOld);
}


void CVGPickupPos::Paint(CDC *pDc)
{
	CDC				dcMem;
	CBitmap*		pOldBitmap;
	CMaskedBitmap	*pBitmap;
	BITMAP			bm;
	int				pos1, pos2;
	int				i, x, y;
	CRgn			tmpRgn;


	dcMem.CreateCompatibleDC (pDc);
	dcMem.SetMapMode (pDc->GetMapMode ());


	// Draw the back image
	pOldBitmap = dcMem.SelectObject (&m_backImage);
	m_backImage.GetObject (sizeof (BITMAP), &bm);

	pDc->BitBlt (0, 0, m_imageWidth, m_imageHeight, &dcMem, 0, 0, SRCCOPY);


	if (!m_frontPickupPosition)
		return;

	// Draw the front pickup

	if (m_pickup->getValue() == PICKUPPOS_FRONT || m_pickup->getValue() == PICKUPPOS_F_R)
	{
		if (m_frontPickuType->getValue() == TPICKUP_SINGLE)
			pBitmap = &m_pickupSingle1;
		else if (m_frontPickuType->getValue() == TPICKUP_DOUBLE)
			pBitmap = &m_pickupDouble1;
		else
			pBitmap = NULL;

		if (pBitmap)
		{
			dcMem.SelectObject (pBitmap);
			pBitmap->GetObject (sizeof (BITMAP), &bm);

			pos1 = m_frontPickupPosition->getValue();
			pos2 = (m_frontPickupPosition->getValue() + (m_frontPickupAngle->getValue() - 63));

			if (pos2 < 0)
				pos2 = 0;

			if (pos2 > 63)
				pos2 = 63;

			pos1 *= 2;
			pos2 *= 2;

			for (i = 0; i < 6; i++)
			{
				x = 30 + pos1 + ((i * (pos2 - pos1)) / 6);
				y = 25 + (bm.bmHeight * (6 - i - 1)) / 6;

				switch (i)
				{
					case 0:
						m_frontBot.CreateRectRgn(x, y, x + bm.bmWidth, y + bm.bmHeight / 6);
						break;

					case 1:
						m_frontMid.CreateRectRgn(x, y, x + bm.bmWidth, y + bm.bmHeight / 6);
						break;

					case 2:
					case 3:
					case 4:
						tmpRgn.CreateRectRgn(x, y, x + bm.bmWidth, y + bm.bmHeight / 6);
						m_frontMid.CombineRgn(&m_frontMid, &tmpRgn, RGN_OR);
						break;

					case 5:
						m_frontTop.CreateRectRgn(x, y, x + bm.bmWidth, y + bm.bmHeight / 6);
						break;
				}

				pDc->BitBlt (x, y, bm.bmWidth, bm.bmHeight / 6, &dcMem, 0, (bm.bmHeight * (6 - i - 1) / 6), SRCCOPY);
			}
		}
	}
	else
	{
		m_frontTop.CreateRectRgn(0, 0, 0, 0);
		m_frontMid.CreateRectRgn(0, 0, 0, 0);
		m_frontBot.CreateRectRgn(0, 0, 0, 0);
	}



	// Draw the rear pickup

	if (m_pickup->getValue() == PICKUPPOS_REAR || m_pickup->getValue() == PICKUPPOS_F_R)
	{
		if (m_rearPickuType->getValue() == TPICKUP_SINGLE)
			pBitmap = &m_pickupSingle2;
		else if (m_rearPickuType->getValue() == TPICKUP_DOUBLE)
			pBitmap = &m_pickupDouble2;
		else
			pBitmap = NULL;

		if (pBitmap)
		{
			dcMem.SelectObject (pBitmap);
			pBitmap->GetObject (sizeof (BITMAP), &bm);

			pos1 = m_rearPickupPosition->getValue();
			pos2 = (m_rearPickupPosition->getValue() + (m_rearPickupAngle->getValue() - 63));

			if (pos2 < 0)
				pos2 = 0;

			if (pos2 > 63)
				pos2 = 63;

			pos1 *= 2;
			pos2 *= 2;

			for (i = 0; i < 6; i++)
			{
				x = 30 + pos1 + ((i * (pos2 - pos1)) / 6);
				y = 25 + (bm.bmHeight * (6 - i - 1)) / 6;

				switch (i)
				{
					case 0:
						m_rearBot.CreateRectRgn(x, y, x + bm.bmWidth, y + bm.bmHeight / 6);
						break;

					case 1:
						m_rearMid.CreateRectRgn(x, y, x + bm.bmWidth, y + bm.bmHeight / 6);
						break;

					case 2:
					case 3:
					case 4:
						tmpRgn.CreateRectRgn(x, y, x + bm.bmWidth, y + bm.bmHeight / 6);
						m_rearMid.CombineRgn(&m_rearMid, &tmpRgn, RGN_OR);
						break;

					case 5:
						m_rearTop.CreateRectRgn(x, y, x + bm.bmWidth, y + bm.bmHeight / 6);
						break;
				}

				pDc->BitBlt (30 + pos1 + ((i * (pos2 - pos1)) / 6), 25 + (bm.bmHeight * (6 - i - 1)) / 6, bm.bmWidth, bm.bmHeight / 6, &dcMem, 0, (bm.bmHeight * (6 - i - 1) / 6), SRCCOPY);
			}
		}
	}
	else
	{
		m_rearTop.CreateRectRgn(0, 0, 0, 0);
		m_rearMid.CreateRectRgn(0, 0, 0, 0);
		m_rearBot.CreateRectRgn(0, 0, 0, 0);
	}

	dcMem.SelectObject(pOldBitmap);
}

void CVGPickupPos::AttachVGData(CVGData *frontPickuType, CVGData *frontPickupPosition, CVGData *frontPickupAngle,
				  CVGData *rearPickuType, CVGData *rearPickupPosition, CVGData *rearPickupAngle, CVGData *pickup)
{
	m_pickup				= pickup;
	m_frontPickuType		= frontPickuType;
	m_frontPickupPosition	= frontPickupPosition;
	m_frontPickupAngle		= frontPickupAngle;
	m_rearPickuType			= rearPickuType;
	m_rearPickupPosition	= rearPickupPosition;
	m_rearPickupAngle		= rearPickupAngle;

	if (m_pickup)
		EnableWindow(TRUE);
	else
		EnableWindow(FALSE);

	Invalidate(FALSE);
}



void CVGPickupPos::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CControl::OnLButtonDown(nFlags, point);

	if (m_pickup)
	{
		if (m_frontMid.PtInRegion(point))
		{
			m_bTracking = 2;
			SetCapture();

			OnMouseAction(point);
		}
		else if (m_rearMid.PtInRegion(point))
		{
			m_bTracking = 5;
			SetCapture();

			OnMouseAction(point);
		}
	}
}


void CVGPickupPos::OnMouseAction(CPoint point)
{
	int value;

	if (m_bTracking && m_pickup)
	{
		if (m_bTracking == 2 || m_bTracking == 5)
		{
			value = (point.x - 35) / 2;

			if (value < 0)
				value = 0;

			if (value > 63)
				value = 63;

			if (m_bTracking == 2)
				m_frontPickupPosition->setValue(value);
			else
				m_rearPickupPosition->setValue(value);
		}
		
		Invalidate(FALSE);

		// Notify the parent window that a refresh of the panel is needed
		GetParent()->PostMessage(WM_COMMAND, (int) LOWORD(GetDlgCtrlID()), (long) this);
	}
}

void CVGPickupPos::OnMouseMove(UINT nFlags, CPoint point)
{
	OnMouseAction(point);
}


void CVGPickupPos::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bTracking)
	{
		m_bTracking = FALSE;
		ReleaseCapture();
		((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();
	}
}




BEGIN_MESSAGE_MAP(CVGSection, CControl)
	//{{AFX_MSG_MAP(CVGSection)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CVGSection::CVGSection()
{
}


BOOL CVGSection::CreateControl(LPCTSTR lpszCaption, int y, CWnd* pParentWnd, UINT nID)
{
	m_section     = &g_section;
	m_imageWidth  = 180;
	m_imageHeight = 15;

	return (CControl::CreateControl(lpszCaption, 0, 
							 CRect(0, y, m_imageWidth, y + m_imageHeight), pParentWnd, nID));
}




void CVGSection::OnPaint() 
{
	CFont *pOldFont;
	CPaintDC dc(this); // device context for painting
	
	dc.SetBkMode(TRANSPARENT);

	pOldFont = dc.SelectObject(&g_font1);

	Paint(&dc);

	dc.SelectObject(pOldFont);
}


void CVGSection::Paint(CDC *pDc)
{
	CDC		 dcMem;
	char	 caption[50];

	GetWindowText(caption, 50);

	m_section->Draw(pDc, 0, 0);
	pDc->SetTextColor(RGB(245, 245, 245));
	pDc->DrawText(caption, -1, CRect(0, 0 , m_imageWidth, m_imageHeight), DT_CENTER);
}





BEGIN_MESSAGE_MAP(CVGList, CControl)
	//{{AFX_MSG_MAP(CVGList)
	ON_WM_PAINT()
	ON_LBN_SELCHANGE(IDC_POPUP, OnSelChange)
	ON_LBN_KILLFOCUS(IDC_POPUP, OnKillFocus)
	ON_LBN_DBLCLK(IDC_POPUP, OnDblClk)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CVGList::CVGList()
{
	m_bTracking = FALSE;
	m_brush.CreateSolidBrush(RGB(43, 48, 51));
}


BOOL CVGList::CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
							 int x, int y, int width, int height, CControl* pParentWnd, UINT nID)
{
	m_dwStyle = dwStyle;
	m_parent  = pParentWnd;

	if (!CWnd::CreateEx(0, NULL, lpszCaption, WS_POPUP | WS_VISIBLE,
		CRect(x, y, x + width, y + height), pParentWnd, nID, NULL))
		return -1;


	m_listBox.Create(LBS_NOINTEGRALHEIGHT | LBS_USETABSTOPS | LBS_NOTIFY | WS_VISIBLE | WS_VSCROLL, CRect(6, 16, width - 6, height - 6), this, IDC_POPUP);
	m_listBox.SetFont(&g_font2, TRUE);

	return 1;
}


void CVGList::OnPaint() 
{
	CFont *pOldFont;
	CBitmap* pOldBitmap;
	CPaintDC dc(this); // device context for painting
	
	dc.SetBkMode(TRANSPARENT);
	pOldBitmap = dc.GetCurrentBitmap();
	pOldFont = dc.SelectObject(m_font);

	Paint(&dc);

	dc.SelectObject(pOldFont);
	dc.SelectObject(pOldBitmap);
}


void CVGList::Paint(CDC *pDc)
{
	CDC		 dcMem;
	CBitmap* pOldBitmap;
	RECT	 rectW;
	char	 caption[50];
	int		 i;

	GetWindowRect(&rectW);

	dcMem.CreateCompatibleDC (pDc);
	dcMem.SetMapMode (pDc->GetMapMode ());

	pOldBitmap = dcMem.SelectObject (&g_popup);


	// Draw the top of the window
	for (i = 0; i < ((rectW.right - rectW.left) / 16) + 1; i++)
		pDc->BitBlt (i * 16, 0 , 16, 16, &dcMem, 6, 0, SRCCOPY);
	
	// Draw the bottom of the window
	for (i = 0; i < ((rectW.right - rectW.left) / 16) + 1; i++)
		pDc->BitBlt (i * 16,  rectW.bottom - rectW.top - 6, 16, 6, &dcMem, 6, 32, SRCCOPY);

	// Draw the left side of the window
	for (i = 0; i < ((rectW.bottom - rectW.top) / 16) + 1; i++)
		pDc->BitBlt (0, i * 16 , 6, 16, &dcMem, 0, 16, SRCCOPY);

	// Draw the right side of the window
	for (i = 0; i < ((rectW.bottom - rectW.top) / 16) + 1; i++)
		pDc->BitBlt (rectW.right - rectW.left - 6, i * 16 , 6, 16, &dcMem, 22, 16, SRCCOPY);

	// Draw the top left corner
	pDc->BitBlt (0, 0 , 6, 16, &dcMem, 0, 0, SRCCOPY);

	// Draw the top right corner
	pDc->BitBlt (rectW.right - rectW.left - 6, 0 , 6, 16, &dcMem, 22, 0, SRCCOPY);

	// Draw the bottom left corner
	pDc->BitBlt (0,  rectW.bottom - rectW.top - 6, 6, 6, &dcMem, 0, 32, SRCCOPY);

	// Draw the bottom right corner
	pDc->BitBlt (rectW.right - rectW.left - 6, rectW.bottom - rectW.top - 6 , 6, 6, &dcMem, 22, 32, SRCCOPY);


	GetWindowText(caption, 50);

	if (caption[0] != '\0')
	{
		pDc->SelectObject(&g_font1);
		pDc->SetTextColor(RGB(216, 247, 45));
		pDc->DrawText(caption, -1, CRect(0, 3, rectW.right - rectW.left, 13), DT_CENTER);
	}

	dcMem.SelectObject(pOldBitmap);
}


HBRUSH CVGList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	pDC->SetTextColor(RGB(238, 142, 27));	
	pDC->SetBkColor(RGB(43, 48, 51));
	
	return (HBRUSH) m_brush;
}


void CVGList::OnSelChange()
{
	m_parent->m_vgData->setValue(m_listBox.GetCurSel());

	if (g_currentPatch)
	{
		g_currentPatch->checkPatch();
		g_currentPatch->initializePatchObjects();
	}

	m_parent->SendMessage(WM_COMMAND, (int) LOWORD(IDC_SEL_CHANGE), (long) this);

	((CMainFrame *) AfxGetMainWnd())->m_chainWnd.OnPatchChange();
	((CMainFrame *) AfxGetMainWnd())->m_patchWnd.m_patchWindowLayer.OnPatchChange();
	((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();
}


void CVGList::OnKillFocus()
{
	// Notify the parent window that the window must be closed
	m_parent->PostMessage(WM_COMMAND, (int) LOWORD(IDC_POPUP_CANCEL), (long) this);
}


void CVGList::OnDblClk()
{
	m_parent->PostMessage(WM_COMMAND, (int) LOWORD(IDC_POPUP_VALIDATE), (long) this);
}


BOOL CVGList::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == IDC_POPUP_VALIDATE)
		m_parent->PostMessage(WM_COMMAND, (int) LOWORD(IDC_POPUP_VALIDATE), (long) this);
	
	return CControl::OnCommand(wParam, lParam);
}



BEGIN_MESSAGE_MAP(CListBoxCustom, CListBox)
	//{{AFX_MSG_MAP(CListBoxCustom)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListBoxCustom::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_RETURN)
		GetParent()->PostMessage(WM_COMMAND, (int) LOWORD(IDC_POPUP_VALIDATE), (long) this);
	else
		CListBox::OnChar(nChar, nRepCnt, nFlags);
}

void CControl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_vgData->m_needSaving)
		((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CControl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_TAB:
			break;

		case VK_F5:
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_AmpOnOffData.setValue(1);
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_effectsOnOffData.setValue(0);
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_assignOnOffData.setValue(0);
			AfxGetMainWnd()->PostMessage(WM_COMMAND, (int) LOWORD(IDC_PANEL_AMP), (long) this);
			break;

		case VK_F6:
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_AmpOnOffData.setValue(0);
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_effectsOnOffData.setValue(1);
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_assignOnOffData.setValue(0);
			AfxGetMainWnd()->PostMessage(WM_COMMAND, (int) LOWORD(IDC_PANEL_EFFECTS), (long) this);
			break;

		case VK_F7:
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_AmpOnOffData.setValue(0);
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_effectsOnOffData.setValue(0);
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_assignOnOffData.setValue(1);
			AfxGetMainWnd()->PostMessage(WM_COMMAND, (int) LOWORD(IDC_PANEL_ASSIGN), (long) this);
			break;

		default:
			((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();
			break;
	}

		
	
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}
