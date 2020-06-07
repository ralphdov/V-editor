// preset.cpp
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
#include "preset.h"
#include "Input.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define TOOLBARHEIGHT	22


BEGIN_MESSAGE_MAP(CPreset, CControl)
	//{{AFX_MSG_MAP(CPreset)
	ON_WM_PAINT()
	ON_LBN_SELCHANGE(IDC_POPUP, OnSelChange)
	ON_LBN_KILLFOCUS(IDC_POPUP, OnKillFocus)
	ON_LBN_DBLCLK(IDC_POPUP, OnDblClk)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CPreset::CPreset()
{
	m_bTracking = FALSE;
	m_brush.CreateSolidBrush(RGB(43, 48, 51));
}


BOOL CPreset::CreateControl(LPCTSTR lpszCaption, DWORD dwStyle, 
							 int x, int y, int width, int height, CPanel* pParentWnd, UINT nID)
{
	m_dwStyle = dwStyle;
	m_parent  = pParentWnd;

	if (!CWnd::CreateEx(0, NULL, lpszCaption, WS_POPUP | WS_VISIBLE,
		CRect(x, y, x + width, y + height), pParentWnd, nID, NULL))
		return -1;

	if (!m_buttonSave.CreateControl("ON / OFF", 6, 10, 17, this, IDC_PRESETSAVE))
		return -1;

	m_buttonSaveData.setValue(0);
	m_buttonSave.AttachVGData(&m_buttonSaveData);

	if (!m_buttonCopy.CreateControl("ON / OFF", 7, 35, 17, this, IDC_PRESETCOPY))
		return -1;

	m_buttonCopyData.setValue(0);
	m_buttonCopy.AttachVGData(&m_buttonCopyData);

	if (!m_buttonDelete.CreateControl("ON / OFF", 8, 10, 17, this, IDC_PRESETDELETE))
		return -1;

	m_buttonDeleteData.setValue(0);
	m_buttonDelete.AttachVGData(&m_buttonDeleteData);

	if (!m_buttonRename.CreateControl("ON / OFF", 9, 35, 17, this, IDC_PRESETRENAME))
		return -1;

	m_buttonRenameData.setValue(0);
	m_buttonRename.AttachVGData(&m_buttonRenameData);

	m_listBox.Create(LBS_NOINTEGRALHEIGHT | LBS_USETABSTOPS | LBS_NOTIFY | WS_VISIBLE | WS_VSCROLL, 
			CRect(6, 16 + TOOLBARHEIGHT, width - 6, height - 6), this, IDC_POPUP);
	m_listBox.SetFont(&g_font2, TRUE);

	m_buttonDelete.ShowWindow(SW_HIDE);
	m_buttonRename.ShowWindow(SW_HIDE);


	// Load all the libraries in the library directorie

	int loop;
	struct _finddata_t c_file;
    long hFile;

	m_listBox.AddString(">> CURRENT PATCH");

	   // Find first .c file in current directory 
    hFile = _findfirst(pParentWnd->getPresetDir() + "*", &c_file );

	if (hFile != -1L)
		loop = 0;
	else
		loop = 1;

	while(loop == 0)
	{
		if (strcmp(c_file.name, ".") != 0 && strcmp(c_file.name, "..") != 0)
			m_listBox.AddString(c_file.name);

		loop = _findnext( hFile, &c_file );
	}

	_findclose( hFile );

	m_currentCount = m_parent->getAllPanelData(m_current);

	m_listBox.SetCurSel(0);

	return 1;
}


void CPreset::OnPaint() 
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


void CPreset::Paint(CDC *pDc)
{
	CDC		 dcMem;
	CBitmap* pOldBitmap;
	RECT	 rectW;
	char	 caption[50];
	int		 i;


	GetWindowRect(&rectW);

	dcMem.CreateCompatibleDC (pDc);
	dcMem.SetMapMode (pDc->GetMapMode ());

	pDc->FillRect(CRect(0, 0, rectW.right - rectW.left, 100), &m_brush);

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


HBRUSH CPreset::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	pDC->SetTextColor(RGB(238, 142, 27));	
	pDC->SetBkColor(RGB(43, 48, 51));
	
	return (HBRUSH) m_brush;
}


void CPreset::saveCurrentToPreset(CString name)
{
	CFileException	e;
	CFile file;
	
	// Open the file
	if (!file.Open(m_parent->getPresetDir() + name, CFile::modeWrite | CFile::modeCreate, &e))
	{
		MessageBox((char *) e.m_cause);

		return;
	}

	// Read the entire content of the file
	file.Write(m_current, m_currentCount);
	file.Close();

}


void CPreset::OnSelChange()
{
	CString preset;
	CFileException	e;
	CFile file;
	char buffer[175000];
	int ret;

	m_listBox.GetText(m_listBox.GetCurSel(), preset);


	if (preset.GetAt(0) == '>')
	{
		m_buttonSave.ShowWindow(SW_SHOWNOACTIVATE);
		m_buttonCopy.ShowWindow(SW_SHOWNOACTIVATE);
		m_buttonDelete.ShowWindow(SW_HIDE);
		m_buttonRename.ShowWindow(SW_HIDE);
		m_parent->setAllPanelData(m_current);
	}
	else
	{
		m_buttonDelete.ShowWindow(SW_SHOWNOACTIVATE);
		m_buttonRename.ShowWindow(SW_SHOWNOACTIVATE);
		m_buttonSave.ShowWindow(SW_HIDE);
		m_buttonCopy.ShowWindow(SW_HIDE);

		preset = m_parent->getPresetDir() + preset;
	
		// Open the file
		if (!file.Open(preset, CFile::modeRead, &e))
		{
			MessageBox((char *) e.m_cause);

			return;
		}

		// Read the entire content of the file
		ret = file.Read(buffer, 175000);
		file.Close();

		m_parent->setAllPanelData(buffer);
	}

	
	
	if (g_currentPatch)
	{
		g_currentPatch->checkPatch();
		g_currentPatch->initializePatchObjects();
	}

	((CMainFrame *) AfxGetMainWnd())->m_chainWnd.OnPatchChange();
	((CMainFrame *) AfxGetMainWnd())->m_patchWnd.m_patchWindowLayer.OnPatchChange();
	((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();

	/*m_parent->m_vgData->setValue(m_listBox.GetCurSel());



	m_parent->SendMessage(WM_COMMAND, (int) LOWORD(IDC_SEL_CHANGE), (long) this);
	*/
}


void CPreset::OnKillFocus()
{
	CWnd *focus = GetFocus();

	if (!IsChild(focus))
		// Notify the parent window that the window must be closed
		m_parent->PostMessage(WM_COMMAND, (int) LOWORD(IDC_PRESET_CANCEL), (long) this);
}


void CPreset::OnDblClk()
{
	m_parent->PostMessage(WM_COMMAND, (int) LOWORD(IDC_PRESET_VALIDATE), (long) this);
}


BOOL CPreset::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	CString preset;
	CInput	inputDlg;

	switch (wParam)
	{
		case IDC_PRESETSAVE:
			if (inputDlg.DoModal() == IDOK)
			{
				saveCurrentToPreset(inputDlg.m_name);
				m_listBox.SetCurSel(m_listBox.AddString(inputDlg.m_name));
				m_buttonDelete.ShowWindow(SW_SHOWNOACTIVATE);
				m_buttonRename.ShowWindow(SW_SHOWNOACTIVATE);
				m_buttonSave.ShowWindow(SW_HIDE);
				m_buttonCopy.ShowWindow(SW_HIDE);
			}

			m_buttonSaveData.setValue(0);
			m_listBox.SetFocus();

			break;

		case IDC_PRESETRENAME:
			int pos;
			m_listBox.GetText(m_listBox.GetCurSel(), preset);
			inputDlg.m_name = preset;

			if (preset.Left(13) != "    CLIPBOARD" && inputDlg.DoModal() == IDOK)
			{
				CFile::Rename(m_parent->getPresetDir() + preset, m_parent->getPresetDir() + inputDlg.m_name);
				pos = m_listBox.GetCurSel();
				m_listBox.InsertString(pos, inputDlg.m_name);
				m_listBox.DeleteString(pos + 1);
				m_listBox.SetCurSel(pos);
			}

			m_buttonRenameData.setValue(0);
			m_listBox.SetFocus();

			break;

		case IDC_PRESETDELETE:
			m_listBox.GetText(m_listBox.GetCurSel(), preset);

			if (preset.Left(13) == "    CLIPBOARD" || MessageBox("Are you sure you want to delete the preset : " + preset, "VEditor", MB_ICONQUESTION | MB_YESNO) == IDYES)
			{
				preset = m_parent->getPresetDir() + preset;
				CFile::Remove(preset);
				m_listBox.DeleteString(m_listBox.GetCurSel());
			}

			m_buttonDeleteData.setValue(0);
			m_listBox.SetFocus();

			break;

		case IDC_PRESETCOPY:
			m_listBox.SetCurSel(m_listBox.InsertString(1, m_parent->copy()));
			m_buttonDelete.ShowWindow(SW_SHOWNOACTIVATE);
			m_buttonRename.ShowWindow(SW_SHOWNOACTIVATE);
			m_buttonSave.ShowWindow(SW_HIDE);
			m_buttonCopy.ShowWindow(SW_HIDE);

			m_buttonCopyData.setValue(0);
			m_listBox.SetFocus();
			break;


		case IDC_PRESET_VALIDATE:
			m_parent->PostMessage(WM_COMMAND, (int) LOWORD(IDC_PRESET_VALIDATE), (long) this);
			break;
	}
	return CControl::OnCommand(wParam, lParam);
}

void CPreset::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CControl::OnLButtonDown(nFlags, point);
}

void CPreset::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CControl::OnLButtonUp(nFlags, point);
}
