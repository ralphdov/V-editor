// ChildView.cpp : implementation of the VGWindow class
//

#include <stdio.h>
#include <io.h>
#include <time.h>
#include "stdafx.h"
#include "VEditor.h"
#include "MainFrm.h"
#include "tools.h"
#include "VGWindow.h"
#include "VG-88.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// VGWindow

CVGWindow::CVGWindow()
{
	m_LTVGWin1.LoadBitmap (IDB_LTVGWin1);
	m_MTVGWin1.LoadBitmap (IDB_MTVGWin1);
	m_RTVGWin1.LoadBitmap (IDB_RTVGWin1);
	m_LVGWin1.LoadBitmap  (IDB_LVGWin1);
	m_RVGWin1.LoadBitmap  (IDB_RVGWin1);
	m_LBVGWin1.LoadBitmap (IDB_LBVGWin1);
	m_MBVGWin1.LoadBitmap (IDB_MBVGWin1);
	m_RBVGWin1.LoadBitmap (IDB_RBVGWin1);
	m_icon.LoadBitmap (IDB_VLIB2);

	m_widget = 0;
	m_capture = 0;
}


CVGWindow::~CVGWindow()
{
}


BEGIN_MESSAGE_MAP(CVGWindow,CWnd )
	//{{AFX_MSG_MAP(CVGWindow)
	ON_WM_NCPAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PATCHLIST, OnNotify)
	ON_WM_NCCALCSIZE()
	ON_WM_SETFOCUS()
	ON_WM_NCACTIVATE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCRBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_PATCHLIST, BeginLabelEdit)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_PATCHLIST, ItemActivate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VGWindow message handlers

BOOL CVGWindow::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_LEFT | WS_EX_LTRREADING;


	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS, 
		AfxGetApp()->LoadCursor(IDC_CURSOR), HBRUSH(COLOR_WINDOW + 1), NULL);

	return TRUE;
}


void CVGWindow::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	lpncsp->rgrc[0].left   = lpncsp->rgrc[0].left   + 16;
	lpncsp->rgrc[0].top	   = lpncsp->rgrc[0].top    + 39;
	lpncsp->rgrc[0].bottom = lpncsp->rgrc[0].bottom - 16;
	lpncsp->rgrc[0].right  = lpncsp->rgrc[0].right  - 16;
}



BOOL CVGWindow::OnNcActivate(BOOL bActive) 
{
	return CWnd ::OnNcActivate(bActive);
}


void CVGWindow::OnNcPaint() 
{

	CFont *pOldFont;
	RECT	rectW; //, rectU;
	int i, count;
	CDC	 *pDc;
//	CRgn *pRgn;
//	CRgn  Rgn;

	GetWindowRect(&rectW);

	MSG& msg = AfxGetThreadState()->m_lastSentMsg;

	pDc = GetWindowDC();

/*	if (msg.wParam > 1)
	{
		pRgn = CRgn::FromHandle((HRGN) msg.wParam);

		pRgn->GetRgnBox(&rectU);

		Rgn.CreateRectRgn(rectU.left - rectW.left, rectU.top - rectW.top, rectU.right - rectW.left, rectU.bottom - rectW.top);
		pDc->SelectClipRgn(&Rgn);
	}
*/
	// Draw top Edge and bottom edge

	count =  ((rectW.right - rectW.left) / 16) - 1;

	for (i = 0; i < count; i++)
	{
		m_MTVGWin1.Draw(pDc, (i * 16) + 16, 0);
		m_MBVGWin1.Draw(pDc, (i * 16) + 16, rectW.bottom - rectW.top - 16);
	}


	// Draw left Edge and right edge

	count = (((rectW.bottom - rectW.top) - 39) / 16);

	for (i = 0; i < count; i++)
	{
		m_LVGWin1.Draw(pDc, 0, (i * 16) + 39);
		m_RVGWin1.Draw(pDc, rectW.right - rectW.left - 16, (i * 16) + 39);
	}


	// Draw corners

	m_LTVGWin1.Draw(pDc, 0, 0);
	m_RTVGWin1.Draw(pDc, rectW.right - rectW.left - 16, 0);
	m_LBVGWin1.Draw(pDc, 0, rectW.bottom - rectW.top - 16);
	m_RBVGWin1.Draw(pDc, rectW.right - rectW.left - 16, rectW.bottom - rectW.top - 16);

	// Draw the title

	CString str;
	CWnd *hWndFocus = GetFocus();
	str = m_library->GetLibraryName();
	//GetWindowText(str);

	if (m_library->modified)
		str = str + "   ( Modified )";

	if (hWndFocus && hWndFocus->m_hWnd == m_listView.m_hWnd)
	{
		pDc->SetTextColor(RGB(216, 247, 45));
		pOldFont = pDc->SelectObject(&g_font5);
	}
	else
	{
		pDc->SetTextColor(RGB(238, 142, 27));
		pOldFont = pDc->SelectObject(&g_font5);
	}

	pDc->SetBkMode(TRANSPARENT);
	

	pDc->DrawText(str.GetBuffer(255), -1, CRect(30, 8 , 1000, 30), DT_LEFT);
	
	// Draw the close button if any
	{
	CDC		 dcMem;
	CBitmap* pOldBitmap;
	BITMAP	 bm;
	int		 pos;
	int		 offset = 0;

	dcMem.CreateCompatibleDC (pDc);
	dcMem.SetMapMode (pDc->GetMapMode ());

	pOldBitmap = dcMem.SelectObject (&g_button1);
	g_button1.GetObject (sizeof (BITMAP), &bm);

	pos = ((2 * m_widget) / 2) * 18;

	if (m_widget == 0)
		offset = 1;
	else
		offset = 0;

	pDc->BitBlt (rectW.right - rectW.left - 30, 10 , 22, 18, &dcMem, 0, pos, SRCCOPY);

	pDc->SetTextColor(RGB(238, 142, 27));
	pDc->SelectObject(&g_font2);
	pDc->DrawText("x", -1, CRect(rectW.right - rectW.left - 30, 11 - offset, rectW.right - rectW.left - 30 + 22 - 3, 9 - offset + 20), DT_CENTER);

	dcMem.SelectObject(pOldBitmap);

	}

	m_icon.Draw(pDc, 10, 8);

	pDc->SelectObject(pOldFont);
	ReleaseDC(pDc);
}



int CVGWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	RECT			rect;
	CMaskedBitmap	bitmap;
	
	rect.top = 0;
	rect.left = 0;
	rect.bottom = 400;
	rect.right = 800;

	m_listView.Create(WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SHAREIMAGELISTS | LVS_EDITLABELS,
		rect, this, IDC_PATCHLIST);
	m_listView.SetFont(&g_font4);
	m_listView.SetImageList(g_ImageList, LVSIL_SMALL);
	m_listView.SetBkColor(RGB(255,255,255));

	m_listView.InsertColumn(0,  "Patch",	LVCFMT_LEFT, 170);
	m_listView.InsertColumn(1,  "Cosm Amp",	LVCFMT_LEFT, 90);
	m_listView.InsertColumn(2,  "Cosm GT",	LVCFMT_LEFT, 96);
	m_listView.InsertColumn(3,  "Pickup",	LVCFMT_LEFT, 96);
	m_listView.InsertColumn(4,  "Comp",		LVCFMT_CENTER, 50);
	m_listView.InsertColumn(5,  "Wah",		LVCFMT_CENTER, 50);
	m_listView.InsertColumn(6,  "Eq",		LVCFMT_CENTER, 50);
	m_listView.InsertColumn(7,  "Mod",		LVCFMT_CENTER, 50);
	m_listView.InsertColumn(8,  "Delay",	LVCFMT_CENTER, 50);
	m_listView.InsertColumn(9,  "Chorus",	LVCFMT_CENTER, 50);
	m_listView.InsertColumn(10, "Reverb",	LVCFMT_CENTER, 50);
	m_listView.InsertColumn(11, "NS",		LVCFMT_CENTER, 50);

	return 0;
}


int CVGWindow::InsertItem(CPatch *patch, int pos, int numPatch)
{
	char		patchName[100];
	char		buffer[1024];
	CString		str;
	LVITEM		item;

	
	m_library->getPatchLabel(numPatch - m_library->firstPatchNumber, patchName);

//	patch->assignNC.name.getString(patchName);
//	str.Format("%2d - %d    %s", (char)((numPatch) / 4) + 1, (char)((numPatch) % 4) + 1, patchName);

	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	item.iItem = pos;
	item.iSubItem = 0;
	item.state = 0;
	item.stateMask = LVIS_SELECTED ;
	item.iImage = patch->cosmGT.guitarType.getValue();
	item.pszText = patchName; // str.GetBuffer(str.GetLength());
	item.lParam = (LPARAM) patch;

	m_listView.InsertItem(&item);
	m_listView.EnsureVisible(item.iItem, FALSE);

	if (patch->cosmAmp.ampOnOff.getValue())
	{
		patch->cosmAmp.ampType.getString(buffer);
		m_listView.SetItemText(pos, 1, buffer);
	}

	if (patch->cosmGT.guitarOnOff.getValue())
	{
		patch->cosmGT.guitarType.getString(buffer);
		m_listView.SetItemText(pos, 2, buffer);
	
		buffer[0] = 0;

		switch (patch->cosmGT.guitarType.getValue())
		{
			case COSMGT_VARI_GT:
				((CVariGuitar *) patch->instrument)->pickup.model.getString(buffer);
				break;

			case COSMGT_OPEN_TUNE:
				((COpenTune *) patch->instrument)->pickup.model.getString(buffer);
				break;

			case COSMGT_PD_SHIFT:
				((CPdShift *) patch->instrument)->pickup.model.getString(buffer);
				break;

			case COSMGT_POLY_DIST:
				((CPolyDist *) patch->instrument)->pickup.model.getString(buffer);
				break;

			case COSMGT_POLY_COMP:
				((CPolyComp *) patch->instrument)->pickup.model.getString(buffer);
				break;

			case COSMGT_POLY_OCT:
				((CPolyOct *) patch->instrument)->pickup.model.getString(buffer);
				break;

			case COSMGT_POLY_SG:
				((CPolySG *) patch->instrument)->pickup.model.getString(buffer);
				break;

			case COSMGT_12STRINGS:
				((CStrings12 *) patch->instrument)->pickup.model.getString(buffer);
				break;
				

			case COSMGT_ACOUSTIC:
				((CAcoustic *) patch->instrument)->pickup.type.getString(buffer);
				break;
		}
		
		m_listView.SetItemText(pos, 3, buffer);
	}

	patch->compOnOff.getString(buffer);

	if (!strcmp(buffer, "ON"))
		m_listView.SetItemText(pos, 4, "ON");

	patch->wahOnOff.getString(buffer);

	if (!strcmp(buffer, "ON"))
		m_listView.SetItemText(pos, 5, buffer);

	patch->eqOnOff.getString(buffer);

	if (!strcmp(buffer, "ON"))
		m_listView.SetItemText(pos, 6, buffer);

	patch->modOnOff.getString(buffer);

	if (!strcmp(buffer, "ON"))
		m_listView.SetItemText(pos, 7, buffer);

	patch->delayOnOff.getString(buffer);

	if (!strcmp(buffer, "ON"))
		m_listView.SetItemText(pos, 8, buffer);

	patch->chorusOnOff.getString(buffer);

	if (!strcmp(buffer, "ON"))
		m_listView.SetItemText(pos, 9, buffer);

	patch->reverbOnOff.getString(buffer);

	if (!strcmp(buffer, "ON"))
		m_listView.SetItemText(pos, 10, buffer);

	patch->nsOnOff.getString(buffer);

	if (!strcmp(buffer, "ON"))
		m_listView.SetItemText(pos, 11, buffer);

	return 0;
}


int CVGWindow::AttachLibrary(CVG88SysEx *lib)
{
	POSITION	position;
	CString		str;
	CPatch		*patch;
	int			i;
	int			numPatch;
	int			patchCount;

	SendMessage(WM_SETREDRAW, FALSE, 0);
	m_listView.SendMessage(WM_SETREDRAW, FALSE, 0);
	m_listView.DeleteAllItems();

	// Remove the path and the .syx extension from the name

	SetWindowText(lib->GetLibraryName());
	
	m_library = lib;

	// add an item for each patch
	patchCount = lib->patchList.GetCount();
	position = lib->patchList.GetHeadPosition();

	numPatch = lib->firstPatchNumber;

	for (i = 0; i < patchCount; i++)
	{
		patch = (CPatch *) lib->patchList.GetNext(position);
		InsertItem(patch, i, numPatch + i);
	}

	SendMessage(WM_SETREDRAW, TRUE, 0);
	m_listView.SendMessage(WM_SETREDRAW, TRUE, 0);
	m_listView.Invalidate();
}


void CVGWindow::OnSize(UINT nType, int cx, int cy) 
{
	CWnd ::OnSize(nType, cx, cy);
	
	m_listView.SetWindowPos(NULL, 0, 0, cx, cy, 0);
}



void CVGWindow::OnNotify(LPNMHDR pnmhdr, LRESULT *pResult)
{
	HTREEITEM item;
	CTreeCtrl *tree = &((CMainFrame *) AfxGetMainWnd())->m_libTreeWnd.m_libraryTree;

	POSITION pos = m_listView.GetFirstSelectedItemPosition();

	if (pos)
	{
		CPatch *patch = (CPatch *) m_listView.GetItemData(m_listView.GetNextSelectedItem(pos));
		item = m_library->GetTreePatchItem(patch);
		tree->SelectItem(item);
		//tree->EnsureVisible(item);
	}

//	return CWnd ::OnNotify(wParam, lParam, pResult);
}


BEGIN_MESSAGE_MAP(CListCtrlCustom,CListCtrl )
	//{{AFX_MSG_MAP(CListCtrlCustom)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBeginDrag)
	ON_WM_SETFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListCtrlCustom::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd ::OnSetFocus(pOldWnd);
	
	GetParent()->BringWindowToTop();
	((CVGWindow *) GetParent())->OnNcPaint();

	HTREEITEM item;
	CTreeCtrl *tree;

	tree = &(((CMainFrame *) AfxGetMainWnd())->m_libTreeWnd.m_libraryTree);
	
	POSITION pos = GetFirstSelectedItemPosition();

	if (pos)
	{
		CPatch *patch = (CPatch *) GetItemData(GetNextSelectedItem(pos));
		item = ((CVGWindow *) GetParent())->m_library->GetTreePatchItem(patch);
		tree->SelectItem(item);
	}
	else
		item = ((CVGWindow *) GetParent())->m_library->GetTreeItem();

	if (item)
		tree->SelectItem(item);
}


void CVGWindow::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	RECT	rectW;

	GetWindowRect(&rectW);

	if (point.x > rectW.right - 30 && point.x < rectW.right - 30 + 17
		&& point.y > rectW.top + 10 && point.y < rectW.top + 10 + 11)
	{
		SetCapture();
		m_capture = 1;
		m_widget = 1;
		OnNcPaint();
	}
	else
	{
		BringWindowToTop();
		m_listView.SetFocus();
	}

	CWnd ::OnNcLButtonDown(nHitTest, point);
}

void CVGWindow::OnNcRButtonDown(UINT nHitTest, CPoint point) 
{
	BringWindowToTop();
	m_listView.SetFocus();
	
	CWnd ::OnNcRButtonDown(nHitTest, point);
}


void CVGWindow::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd ::OnSetFocus(pOldWnd);
	BringWindowToTop();
}


BOOL CListCtrlCustom::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));
	
	return TRUE;
}


void CListCtrlCustom::OnBeginDrag(LPNMHDR pnmhdr, LRESULT *pResult)
{
	CPoint      ptAction;

	GetCursorPos(&ptAction);
	ScreenToClient(&ptAction);

	((CMainFrame *) AfxGetMainWnd())->m_bDragging = TRUE;
	((CMainFrame *) AfxGetMainWnd())->pLastListviewDrag = NULL;

	SetCapture();
	::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORG));
	
}

void CListCtrlCustom::OnMouseMove(UINT nFlags, CPoint point)
{
	((CMainFrame *) AfxGetMainWnd())->DragMove(nFlags, point);

	CListCtrl ::OnMouseMove(nFlags, point);
}


void CListCtrlCustom::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging)
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

	CListCtrl ::OnLButtonUp(nFlags, point);
}


void CListCtrlCustom::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl ::OnKillFocus(pNewWnd);

	if (::GetActiveWindow() == AfxGetMainWnd()->m_hWnd)
		((CVGWindow *) GetParent())->OnNcPaint();
}


void CVGWindow::OnLButtonUp(UINT nFlags, CPoint point) 
{
	RECT	rectW;

	if (m_capture)
	{
		m_capture = 0;
		m_widget = 0;
		ReleaseCapture();

		GetWindowRect(&rectW);

		point.x += rectW.left + 16;
		point.y += rectW.top + 39;

		if (point.x > rectW.right - 30 && point.x < rectW.right - 30 + 17
			&& point.y > rectW.top + 10 && point.y < rectW.top + 10 + 11)
		{
			m_library->data1 = NULL;
			PostMessage(WM_CLOSE);
			AfxGetMainWnd()->PostMessage(WM_CHECK_LIBRARY_WINDOW);
		}
		else
			OnNcPaint();
	}

	CWnd ::OnLButtonUp(nFlags, point);
}


void CVGWindow::OnMouseMove(UINT nFlags, CPoint point) 
{
	RECT	rectW;

	if (m_capture)
	{
		GetWindowRect(&rectW);

		point.x += rectW.left + 16;
		point.y += rectW.top + 39;

		if (point.x > rectW.right - 30 && point.x < rectW.right - 30 + 17
			&& point.y > rectW.top + 10 && point.y < rectW.top + 10 + 11)
		{
			if (m_widget == 0)
			{
				m_widget = 1;
				OnNcPaint();
			}

		}
		else
		{
			if (m_widget == 1)
			{
				m_widget = 0;
				OnNcPaint();
			}
		}
	}
	
	
	CWnd ::OnMouseMove(nFlags, point);
}

void CVGWindow::ItemActivate(LPNMHDR pnmhdr, LRESULT *pResult)
{
}

void CVGWindow::BeginLabelEdit(LPNMHDR pnmhdr, LRESULT *pResult)
{
	PostMessage(WM_COMMAND, 162, NULL);
}

BOOL CVGWindow::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	POSITION pos;
	CPatch *patch[200];
	int i = 0;
	int item;
	CVG88SysEx *currentLibraryBckp;
	CPatch *currentPatchBckp;
	int currentPatchNumberBckp;
	CString name;

	switch (wParam)
	{
		case ID_EDIT_RENAME:
		case 162:
			RECT	rect, rect2;

			item = m_listView.GetSelectionMark();

			if (item == -1)
				return false;
			
			m_listView.GetItemRect(item, &rect, 1);
			m_listView.GetWindowRect(&rect2);

			rect.top    += rect2.top;
			rect.bottom += rect2.top;
			rect.left   += rect2.left;
			rect.right  += rect2.left;

			m_nameEditor = new CNameEditor((CPatch *) m_listView.GetItemData(item));
			m_nameEditor->Create(&rect, this);
			m_nameEditor->m_parent = this;

		break;

		case 666:
			item = m_listView.GetSelectionMark();
			m_nameEditor->m_edit.GetWindowText(name);

			currentLibraryBckp = g_currentLibrary;
			currentPatchBckp = g_currentPatch;
			currentPatchNumberBckp = g_currentPatchNumber;
			g_currentLibrary = m_library;
			g_currentPatch = m_nameEditor->m_patch;
			g_currentPatchNumber = item;

			m_nameEditor->m_patch->assignNC.name.setString(name.GetBuffer(255));

			if (m_nameEditor->m_patch->modified)
			{
				m_nameEditor->m_patch->modified = false;
				m_library->SetModifiedFlag();

				char name[100];
				m_library->getPatchLabel(item, name);
				m_listView.SetItemText(item, 0,name);
			}

			g_currentLibrary = currentLibraryBckp;
			g_currentPatch = currentPatchBckp;
			g_currentPatchNumber = currentPatchNumberBckp;

			delete m_nameEditor;
/*			m_libraryTree.SetFocus();
			((CMainFrame *) AfxGetMainWnd())->onPatchChange();
			((CMainFrame *) AfxGetMainWnd())->SendAuditionPatch();
*/
			break;

		case 555:
			delete m_nameEditor;
			m_listView.SetFocus();
			break;

		case ID_EDIT_CUT:
		case ID_EDIT_COPY:

			pos = m_listView.GetFirstSelectedItemPosition();
			
			while (pos)
			{
				int nItem = m_listView.GetNextSelectedItem(pos);

				patch[i++] = (CPatch *) m_listView.GetItemData(nItem);
			}

			if (wParam == ID_EDIT_COPY || m_library->libraryType == LIB_PRESET || m_library->libraryType == LIB_USER)
				((CMainFrame *) AfxGetMainWnd())->CopyToClipboard(patch, i);
			else
			{
				((CMainFrame *) AfxGetMainWnd())->CutToClipboard(m_library, patch, i);
				AttachLibrary(m_library);
			}
			
			break;

		case ID_EDIT_PASTE:
			if (m_library->libraryType != LIB_PRESET && m_library->libraryType != LIB_USER)
			{
				((CMainFrame *) AfxGetMainWnd())->PasteFromClipboard(m_library, m_listView.GetSelectionMark());
				AttachLibrary(m_library);
			}
			else
				MessageBox("Paste not allowed");

			break;

	}

	return CWnd ::OnCommand(wParam, lParam);
}


void CListCtrlCustom::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging)
		return;

	CListCtrl ::OnRButtonDown(nFlags, point);

	CMenu menu;
	RECT rect;

	GetWindowRect(&rect);

	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING, ID_EDIT_CUT, "Cut");
	menu.AppendMenu(MF_STRING, ID_EDIT_COPY, "Copy");
	menu.AppendMenu(MF_STRING, ID_EDIT_PASTE, "Paste");
	menu.AppendMenu(MF_SEPARATOR, 0, "");
	menu.AppendMenu(MF_STRING, ID_EDIT_RENAME, "Rename");

	menu.TrackPopupMenu(TPM_LEFTALIGN, point.x + rect.left, point.y + rect.top, GetParent());
	
	menu.DestroyMenu();
}


void CListCtrlCustom::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging == TRUE)
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

	switch (nChar)
	{
		case VK_F2:
				EditLabel(GetSelectionMark());
				break;
	}
	
	CListCtrl ::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CListCtrlCustom::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging == TRUE)
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

	
	CListCtrl ::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CListCtrlCustom::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	if (((CMainFrame *) AfxGetMainWnd())->m_bDragging)
		return;
	
	CListCtrl ::OnRButtonDblClk(nFlags, point);
}
