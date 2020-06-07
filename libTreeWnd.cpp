// LibTreeWnd.cpp : implementation of the CLibTreeWnd class
//

#include <stdio.h>
#include <io.h>
#include <time.h>
#include "stdafx.h"
#include "LibTreeWnd.h"
#include "VEditor.h"
#include "MainFrm.h"
#include "tools.h"
#include "VG-88.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CLibTreeWnd

CLibTreeWnd::~CLibTreeWnd()
{
	delete (m_font);
}


BEGIN_MESSAGE_MAP(CLibTreeWnd,CWnd )
	//{{AFX_MSG_MAP(CLibTreeWnd)
	ON_WM_CREATE ()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_LIBRARYTREE, OnNotify)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_LIBRARYTREE, BeginLabelEdit)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_LIBRARYTREE, EndLabelEdit)
	ON_NOTIFY(NM_RCLICK, IDC_LIBRARYTREE, RClick)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLibTreeWnd message handlers

BOOL CLibTreeWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	//cs.dwExStyle |= WS_EX_CLIENTEDGE;
	//cs.style &= ~WS_BORDER;

	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS, 
		AfxGetApp()->LoadCursor(IDC_CURSOR), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

int CLibTreeWnd::OnCreate (LPCREATESTRUCT lpcs)
{
	RECT			rect;

	rect.top = 38;
	rect.left = 15;
	rect.bottom = 0;
	rect.right = 0;

	m_libraryTree.Create(WS_VISIBLE | TVS_HASLINES | TVS_EDITLABELS | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS, rect, this, IDC_LIBRARYTREE);

	m_libraryTree.SetFont(&g_font4);
	m_libraryTree.SetImageList(g_ImageList, TVSIL_NORMAL);
	m_libraryTree.SetBkColor(RGB(255,255,255));
	//CoLockObjectExternal(&m_libraryTree, TRUE, FALSE);
	switch (RegisterDragDrop(m_libraryTree.GetSafeHwnd(), &m_libraryTree))
	{
		case DRAGDROP_E_INVALIDHWND:
			MessageBox("Invalid Hwnd");
			break;

		case DRAGDROP_E_ALREADYREGISTERED :
			break;

		case S_OK:
			break;

		case E_OUTOFMEMORY:
			MessageBox("E_OUTOFMEMORY");
			break;

		default:
			MessageBox("Unknown error");
			break;
	}
	
		
	//RegisterDragDrop(this->GetSafeHwnd(), &m_libraryTree);

	return 0;
}


void CLibTreeWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	PaintLibTreeWnd(&dc);
	// Do not call CWnd::OnPaint() for painting messages
}


void CLibTreeWnd::PaintLibTreeWnd(CDC *dc) 
{
	BITMAP	bmBot, bmSide, bmTop;
	RECT	rect;
	int		sideCount, i;

	GetClientRect(&rect);

	g_pFileTop.GetObject (sizeof (BITMAP), &bmTop);
	g_pFileBot.GetObject (sizeof (BITMAP), &bmBot);
	g_pFileLeft.GetObject (sizeof (BITMAP), &bmSide);

	g_pFileTop.Draw(dc, 0, 0);

	// côtés
	
	sideCount = (rect.bottom - bmBot.bmHeight - bmTop.bmHeight);

	if (sideCount < 0)
		sideCount = 0;

	sideCount = sideCount / bmSide.bmHeight;

	if (sideCount > 0)
	{
		for (i = 0; i <= sideCount; i++)
			g_pFileLeft.Draw(dc, 0, bmTop.bmHeight + (i * bmSide.bmHeight));

		for (i = 0; i <= sideCount; i++)
			g_pFileRight.Draw(dc, bmTop.bmWidth - bmSide.bmWidth, bmTop.bmHeight + (i * bmSide.bmHeight));
	}
	

	// Bas
	
	g_pFileBot.Draw(dc, 0, rect.bottom - bmBot.bmHeight);

}


void CLibTreeWnd::OnSize(UINT nType, int cx, int cy) 
{
	CClientDC dc(this);

	PaintLibTreeWnd(&dc);

	// Resize the TreeCtrl
	m_libraryTree.SetWindowPos(NULL, 0, 0, LIBTREEWND_WIDTH - 29, cy - 53, SWP_NOMOVE | SWP_NOOWNERZORDER);
}


void CLibTreeWnd::OnNotify(LPNMHDR pnmhdr, LRESULT *pResult)
{
	HTREEITEM item, parentItem;

	item = m_libraryTree.GetSelectedItem();

	if ((parentItem = m_libraryTree.GetParentItem(item)))
	{
		((CMainFrame *) AfxGetMainWnd())->SetCurrentLibrary((CVG88SysEx *) m_libraryTree.GetItemData(parentItem));

		if (g_currentLibrary->vgSystem == (CSystem *) m_libraryTree.GetItemData(m_libraryTree.GetSelectedItem()))
		{
			((CMainFrame *) AfxGetMainWnd())->SetCurrentSystem((CSystem *) m_libraryTree.GetItemData(m_libraryTree.GetSelectedItem()));
			((CMainFrame *) AfxGetMainWnd())->SetCurrentPatch(NULL);
		}
		else
		{
			((CMainFrame *) AfxGetMainWnd())->SetCurrentPatch((CPatch *) m_libraryTree.GetItemData(m_libraryTree.GetSelectedItem()));
			((CMainFrame *) AfxGetMainWnd())->SetCurrentSystem(NULL);
		}
	}
	else
	{
		((CMainFrame *) AfxGetMainWnd())->SetCurrentLibrary((CVG88SysEx *) m_libraryTree.GetItemData(m_libraryTree.GetSelectedItem()));
		((CMainFrame *) AfxGetMainWnd())->SetCurrentPatch(NULL);
		((CMainFrame *) AfxGetMainWnd())->SetCurrentSystem(NULL);
	}

	((CMainFrame *) AfxGetMainWnd())->onPatchChange();
	((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();
}



void CLibTreeWnd::BeginLabelEdit(LPNMHDR pnmhdr, LRESULT *pResult)
{
	if (g_currentPatch)
		PostMessage(WM_COMMAND, 162, 0);
}

void CLibTreeWnd::EndLabelEdit(LPNMHDR pnmhdr, LRESULT *pResult)
{
	if (m_libraryTree.GetParentItem(m_libraryTree.GetSelectedItem()) == NULL)
	{
		LPNMTVDISPINFO ptvdi = (LPNMTVDISPINFO) pnmhdr;

		CVG88SysEx  *library = (CVG88SysEx  *) m_libraryTree.GetItemData(ptvdi->item.hItem);

		char newName[_MAX_PATH];
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];

		_splitpath(library->file, drive, dir, fname, ext);
		_makepath(newName, drive, dir, ptvdi->item.pszText, "syx" );

		if (rename(library->file, newName) == 0)
		{
			m_libraryTree.SetItemText(ptvdi->item.hItem, ptvdi->item.pszText);
			library->file = newName;
		}
		else
			MessageBox("Unable to rename the library");
	}
}

void CLibTreeWnd::RClick(LPNMHDR pnmhdr, LRESULT *pResult)
{
/*	HTREEITEM item, parentItem;

	item = m_libraryTree.GetSelectedItem();

	m_libraryTree.Select(item, TVGN_CARET);
	//RECT rect;

	//GetWindowRect(&rect);
	//menu.TrackPopupMenu(TPM_LEFTALIGN, point.x + rect.left, point.y + rect.top, this);
	MessageBox("coucou");*/
	*pResult = 0;
}



BOOL CLibTreeWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	HTREEITEM item;
	RECT	rect, rect2;
	CPatch *patch[1];
	CString name;
	CString str;

	switch (wParam)
	{
		case ID_EDIT_RENAME:
		case 162:
			item = m_libraryTree.GetSelectedItem();
			m_libraryTree.GetItemRect(item, &rect, 1);
			m_libraryTree.GetWindowRect(&rect2);

			rect.top    += rect2.top;
			rect.bottom += rect2.top;
			rect.left   += rect2.left;
			rect.right  += rect2.left;

			m_nameEditor = new CNameEditor;
			m_nameEditor->Create(&rect, this);
			m_nameEditor->m_parent = this;

			break;

		case 666:
			char label[255];

			item = m_libraryTree.GetSelectedItem();
			m_nameEditor->m_edit.GetWindowText(name);
			g_currentPatch->assignNC.name.setString(name.GetBuffer(255));
		
			g_currentLibrary->getPatchLabel(g_currentPatchNumber, label);
			m_libraryTree.SetItemText(item, label);

			if (g_currentLibrary->data1)
			{
				((CVGWindow *) g_currentLibrary->data1)->m_listView.SetItemText(g_currentPatchNumber, 0, label);
			}


			delete m_nameEditor;
			m_libraryTree.SetFocus();
			((CMainFrame *) AfxGetMainWnd())->onPatchChange();
			((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();

			break;

		case 555:
			delete m_nameEditor;
			m_libraryTree.SetFocus();
			break;

		case ID_EDIT_CUT:
			item = m_libraryTree.GetSelectedItem();

			if (((CVG88SysEx *) m_libraryTree.GetItemData(m_libraryTree.GetParentItem(item)))->libraryType  != LIB_PRESET 
				&& ((CVG88SysEx *) m_libraryTree.GetItemData(m_libraryTree.GetParentItem(item)))->libraryType != LIB_USER)
			{
				patch[0] = (CPatch *) m_libraryTree.GetItemData(item);

				((CMainFrame *) AfxGetMainWnd())->CutToClipboard((CVG88SysEx *) m_libraryTree.GetItemData(m_libraryTree.GetParentItem(item)), patch, 1);
				CVGWindow *vgWindow = (CVGWindow *) ((CVG88SysEx *) m_libraryTree.GetItemData(m_libraryTree.GetParentItem(item)))->data1;

				/*if (vgWindow)
				{
					vgWindow->AttachLibrary((CVG88SysEx *) m_libraryTree.GetItemData(m_libraryTree.GetParentItem(item)));
				}*/
			}
			else
			{
				patch[0] = (CPatch *) m_libraryTree.GetItemData(item);

				((CMainFrame *) AfxGetMainWnd())->CopyToClipboard(patch, 1);
			}
			break;

		case ID_EDIT_COPY:
			item = m_libraryTree.GetSelectedItem();
			patch[0] = (CPatch *) m_libraryTree.GetItemData(item);

			((CMainFrame *) AfxGetMainWnd())->CopyToClipboard(patch, 1);
			break;

		case ID_EDIT_PASTE:
			int pos;

			item = m_libraryTree.GetSelectedItem();

			if (m_libraryTree.GetParentItem(item))
			{
				HTREEITEM item2, itemsvg;

				itemsvg = item;
				item = m_libraryTree.GetParentItem(item);

				item2 = m_libraryTree.GetNextItem(item, TVGN_CHILD);
				pos = 0;

				while (item2 != itemsvg)
				{
					pos++;
					item2 = m_libraryTree.GetNextItem(item2, TVGN_NEXT);
				}
			}
			else
				pos = -1;

			if (((CVG88SysEx *) m_libraryTree.GetItemData(item))->libraryType  == LIB_PRESET 
				|| ((CVG88SysEx *) m_libraryTree.GetItemData(item))->libraryType == LIB_USER)
			{
				MessageBox("Paste not allowed");
			}
				break;

			((CMainFrame *) AfxGetMainWnd())->PasteFromClipboard((CVG88SysEx *) m_libraryTree.GetItemData(item), pos);
			break;


		default:
			AfxGetMainWnd()->PostMessage(WM_COMMAND, wParam, lParam);
			break;
	}

	return CWnd ::OnCommand(wParam, lParam);
}


BEGIN_MESSAGE_MAP(CTreeCtrlCustom,CTreeCtrl )
	//{{AFX_MSG_MAP(CTreeCtrlCustom)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CTreeCtrlCustom::CTreeCtrlCustom()
{
}

void CTreeCtrlCustom::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging)
	{
		if (((CMainFrame *) AfxGetMainWnd())->m_DropFound)
		{
			if (::GetKeyState(VK_CONTROL) < 0)
				::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORGP));
			else
				::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORG));
		}
		else
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));
	}
	else
	{
		switch(nChar)
		{
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

			case VK_F2:
				EditLabel(GetSelectedItem());
				break;

			default:
				CWnd ::OnKeyDown(nChar, nRepCnt, nFlags);
		}
	}
}


void CTreeCtrlCustom::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging)
	{
		if (nChar == VK_ESCAPE)
		{
			ReleaseCapture();
			((CMainFrame *) AfxGetMainWnd())->pLastListviewDrag = NULL;
			((CMainFrame *) AfxGetMainWnd())->m_bDragging = FALSE;
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));
		}
		else if (((CMainFrame *) AfxGetMainWnd())->m_DropFound)
		{
			if (::GetKeyState(VK_CONTROL) < 0)
				::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORGP));
			else
				::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORG));
		}
		else
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));

	}
	
	CTreeCtrl ::OnKeyUp(nChar, nRepCnt, nFlags);
}



BEGIN_MESSAGE_MAP(CNameEditor,CWnd )
	//{{AFX_MSG_MAP(CNameEditor)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_CREATE ()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CNameEditor::CNameEditor()
{
	m_currentCar = 1;
	m_patch = g_currentPatch;
}

CNameEditor::CNameEditor(CPatch *patch)
{
	m_currentCar = 1;
	m_patch = patch;
}

BOOL CNameEditor::PreCreateWindow(CREATESTRUCT& cs) 
{
if (!CWnd::PreCreateWindow(cs))
		return FALSE;	

	//cs.dwExStyle |= WS_EX_CLIENTEDGE;
	//cs.style &= ~WS_BORDER;

	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS, 
		AfxGetApp()->LoadCursor(IDC_CURSOR), HBRUSH(COLOR_WINDOW+1), NULL);


	return TRUE;
}


BOOL CNameEditor::Create(RECT *rect, CWnd *pParentWnd)
{
	int ret;
	RECT rect2;
	char name[255];

	rect2.left   = rect->left;
	rect2.top    = rect->top;
	rect2.right  = rect->left + 120;
	rect2.bottom = rect->bottom + 2;

	rect->right = rect->left + 314;

	if (rect2.top < 600)
	{
		rect->top = rect2.bottom - 1;
		rect->bottom = rect2.bottom + 226;
		m_wndCarIsOnBottom = TRUE;
		m_currentCar = 1;
	}
	else
	{
		rect->top = rect2.top - 226;
		rect->bottom = rect2.top + 1;
		m_wndCarIsOnBottom = FALSE;
		m_currentCar = 112;
	}

	ret = CWnd::CreateEx(0, NULL, "", WS_POPUP | WS_VISIBLE, *rect, pParentWnd, 0, NULL);

	m_edit.Create(WS_VISIBLE | WS_POPUP | WS_BORDER, rect2, this, 0);
	m_edit.m_parent = this;

	m_patch->assignNC.name.getString(name);
	m_edit.SetFont(&g_font4);
	m_edit.SetWindowText(name);
	
	m_edit.SetLimitText(8);
	m_edit.SetSel(0, 8, FALSE);
	m_edit.SetFocus();

	return ret;
}

void CNameEditor::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	Paint(&dc);
	// Do not call CWnd::OnPaint() for painting messages
}


void CNameEditor::Paint(CDC *dc) 
{
	g_vg88FontBW.Draw(dc, 0, 0);
}


void CNameEditor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (((point.y - 5) / 27) * 16 + ((point.x - 5) / 19) > 0)
		m_currentCar = ((point.y - 5) / 27) * 16 + ((point.x - 5) / 19);

	point.x = 5 + (m_currentCar % 16) * 19;
	point.y = 5 + (m_currentCar / 16) * 27;
	SetCaretPos(point);

	CWnd ::OnLButtonDown(nFlags, point);
}


void CNameEditor::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_edit.SetFocus();

	if (m_currentCar < 32)
		m_edit.PostMessage(WM_CHAR, (TCHAR) m_currentCar + 128, 0);
	else
		m_edit.PostMessage(WM_CHAR, (TCHAR) m_currentCar, 0);

	CWnd ::OnLButtonUp(nFlags, point);
}


void CNameEditor::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd ::OnKillFocus(pNewWnd);

	HideCaret();
	::DestroyCaret();

	PostMessage(WM_COMMAND, 777, 0);
}


void CNameEditor::OnSetFocus(CWnd* pOldWnd) 
{
	POINT point;
	CWnd ::OnSetFocus(pOldWnd);
	
	CreateGrayCaret(19, 27);

	point.x = 5 + (m_currentCar % 16) * 19;
	point.y = 5 + (m_currentCar / 16) * 27;
	SetCaretPos(point);
	ShowCaret();
}


BOOL CNameEditor::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == 777)
		if (GetFocus()->m_hWnd != m_hWnd && GetFocus()->m_hWnd != m_edit.m_hWnd)
			m_parent->PostMessage(WM_COMMAND, 666, 0);

	if (wParam == 666)
		m_parent->PostMessage(WM_COMMAND, 666, 0);

	if (wParam == 555)
		m_parent->PostMessage(WM_COMMAND, 555, 0);

	return CWnd ::OnCommand(wParam, lParam);
}


void CNameEditor::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_RETURN:
			m_edit.SetFocus();

			if (m_currentCar < 32)
				m_edit.PostMessage(WM_CHAR, (TCHAR) m_currentCar + 128, 0);
			else
				m_edit.PostMessage(WM_CHAR, (TCHAR) m_currentCar, 0);

			break;

		case VK_ESCAPE:
			m_parent->PostMessage(WM_COMMAND, 555, 0);
			break;

		default:
				CWnd ::OnChar(nChar, nRepCnt, nFlags);
	}
}

void CNameEditor::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	POINT point;

	switch(nChar)
	{
		case VK_LEFT:
			m_currentCar--;
			break;

		case VK_RIGHT:
			m_currentCar++;

			if (m_currentCar > 127)
				m_currentCar = 127;
			break;

		case VK_DOWN:
			if (m_currentCar < 112)
				m_currentCar += 16;	
			else
			{
				if (!m_wndCarIsOnBottom)
				{
					m_edit.SetFocus();
					return;
				}
			}

			break;

		case VK_UP:
			if (m_currentCar < 16)
			{
				if (m_wndCarIsOnBottom)
				{
					m_edit.SetFocus();
					return;
				}
			}
			else
				m_currentCar -= 16;

			break;
	}

	if (m_currentCar < 1)
		m_currentCar = 1;

	point.x = 5 + (m_currentCar % 16) * 19;
	point.y = 5 + (m_currentCar / 16) * 27;
	SetCaretPos(point);

	CWnd ::OnKeyDown(nChar, nRepCnt, nFlags);
}


BEGIN_MESSAGE_MAP(CEditCustom,CEdit )
	//{{AFX_MSG_MAP(CEditCustom)
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEditCustom::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_RETURN)
		m_parent->PostMessage(WM_COMMAND, 666, 0);

	if (nChar == VK_ESCAPE)
		m_parent->PostMessage(WM_COMMAND, 555, 0);

	if (nChar > 0 && nChar <= 127)
		CEdit :: OnChar(nChar, nRepCnt, nFlags);
	else if (nChar > 127 && nChar < 160)
	{
		char buffer[2] = "";

		buffer[0] = (char) nChar - 128;
		ReplaceSel(buffer);
	}
}


void CEditCustom::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit ::OnKillFocus(pNewWnd);

	m_parent->PostMessage(WM_COMMAND, 777, 0);
}

void CEditCustom::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_DOWN:
			if (m_parent->m_wndCarIsOnBottom)
				m_parent->SetFocus();
			break;

		case VK_UP:
			if (!m_parent->m_wndCarIsOnBottom)
				m_parent->SetFocus();
			break;

		default:
			CEdit ::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

void CTreeCtrlCustom::OnRButtonUp(UINT nFlags, CPoint point) 
{
	RECT rect;

	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging)
		return;

	GetWindowRect(&rect);

	menu.CreatePopupMenu();

	if (GetParentItem(GetSelectedItem()) == NULL)
	{
		menu.AppendMenu(MF_STRING, ID_OPENVGWINDOW, "Zoom");
		menu.AppendMenu(MF_SEPARATOR, 0, "");
		menu.AppendMenu(MF_STRING, ID_SAVE, "Save");
		menu.AppendMenu(MF_STRING, ID_SAVEAS, "Save As...");
		menu.AppendMenu(MF_STRING, ID_SEND, "Send...");
		menu.AppendMenu(MF_STRING, ID_CLOSE, "Close");
		menu.AppendMenu(MF_SEPARATOR, 0, "");
		menu.AppendMenu(MF_STRING, ID_EDIT_PASTE, "Paste");
		menu.AppendMenu(MF_SEPARATOR, 0, "");
		menu.AppendMenu(MF_STRING, ID_PROPERTIES, "Properties...");
	}
	else
	{
		menu.AppendMenu(MF_STRING, ID_EDIT_CUT, "Cut");
		menu.AppendMenu(MF_STRING, ID_EDIT_COPY, "Copy");
		menu.AppendMenu(MF_STRING, ID_EDIT_PASTE, "Paste before");
		menu.AppendMenu(MF_SEPARATOR, 0, "");
		menu.AppendMenu(MF_STRING, ID_EDIT_RENAME, "Rename");
		menu.AppendMenu(MF_STRING, ID_SEND_ONE_PATCH, "Send...");
	}

	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x + rect.left, point.y + rect.top, GetParent());
	
	menu.DestroyMenu();

	// CTreeCtrl ::OnRButtonUp(nFlags, point);
}

void CTreeCtrlCustom::OnRButtonDown(UINT nFlags, CPoint point) 
{
	HTREEITEM item;
	UINT pResult;

	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging)
		return;

	item = HitTest(point, &pResult);

	if (!item)
		return;

	SelectItem(item);
	//CTreeCtrl ::OnRButtonDown(nFlags, point);
}


void CTreeCtrlCustom::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging)
	{
		if (GetParentItem(((CMainFrame *) AfxGetMainWnd())->m_hitemDrag) == NULL)
		{
			CVG88SysEx *library;
			library = (CVG88SysEx *) GetItemData(((CMainFrame *) AfxGetMainWnd())->m_hitemDrag);

			if (library->data1 == NULL)
				((CMainFrame *) AfxGetMainWnd())->OpenLibraryWindow(library);

			ReleaseCapture();
			((CMainFrame *) AfxGetMainWnd())->pLastListviewDrag = NULL;
			((CMainFrame *) AfxGetMainWnd())->m_bDragging = FALSE;
		}
		else
		{
			if (((CMainFrame *) AfxGetMainWnd())->m_DropFound)
			{
				if (::GetKeyState(VK_CONTROL) < 0)
					GetParent()->SendMessage(WM_COMMAND, (WPARAM) ID_EDIT_COPY, 0);
				else 
					GetParent()->SendMessage(WM_COMMAND, (WPARAM) ID_EDIT_CUT, 0);
			}

			((CMainFrame *) AfxGetMainWnd())->DragLButtonUp(nFlags, point);
		}
	}

	
	CTreeCtrl ::OnLButtonUp(nFlags, point);
}


void CTreeCtrlCustom::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging && GetParentItem(((CMainFrame *) AfxGetMainWnd())->m_hitemDrag) == NULL)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORF));
	else
		((CMainFrame *) AfxGetMainWnd())->DragMove(nFlags, point);

	CTreeCtrl ::OnMouseMove(nFlags, point);
}



void CTreeCtrlCustom::OnBeginDrag(LPNMHDR pnmhdr, LRESULT *pResult)
{
	CPoint      ptAction;
	UINT        nFlags;

	GetCursorPos(&ptAction);
	ScreenToClient(&ptAction);

	HTREEITEM hitem = HitTest(ptAction, &nFlags);

	((CMainFrame *) AfxGetMainWnd())->m_bDragging = TRUE;
	((CMainFrame *) AfxGetMainWnd())->m_hitemDrag = hitem;

	Select(HitTest(ptAction, &nFlags), TVGN_CARET);

	SetCapture();
	::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORG));
}


BOOL CTreeCtrlCustom::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));
	
	return TRUE;
}


void CTreeCtrlCustom::ProcessData(CString Data)
{
	MessageBox(Data, "Dropped text");

/*	CString t1(Data), t2;
	int idx = t1.Find('\n');

	while (idx !=-1)
	{
		t2 = t1.Left(idx);
		t1 = t1.Mid(idx+1);
		InsertRow(t2);
		idx = t1.Find('\n');
	}
*/
}
