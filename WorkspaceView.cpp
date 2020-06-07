// WorkspaceView.cpp : implementation of the CWorkspaceView class
//

#include "stdafx.h"
#include "VEditor.h"
#include "tools.h"
#include "WorkspaceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView

CWorkspaceView::CWorkspaceView()
{
}

CWorkspaceView::~CWorkspaceView()
{
}


BEGIN_MESSAGE_MAP(CWorkspaceView,CWnd )
	//{{AFX_MSG_MAP(CWorkspaceView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView message handlers

BOOL CWorkspaceView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_LEFT | WS_EX_LTRREADING;

	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_APPWORKSPACE + 1), NULL);

	return TRUE;
}

void CWorkspaceView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}


void CWorkspaceView::TileWindows(UINT type)
{
	RECT	rect;
	CWnd	*pWnd;
	int		count;
	int		i;
	int		width;
	int		height;
	int		pos;

	GetWindowRect(&rect);
	
	pWnd = GetWindow(GW_CHILD);
	count = 0;

	while (pWnd)
	{
		count++;

		pWnd = pWnd->GetNextWindow();
	}


	if (!count)
		return;

	pWnd = GetWindow(GW_CHILD);
	pos = 0;


	switch(type)
	{
		case MDITILE_VERTICAL:
			height = rect.bottom - rect.top;
			width  = (rect.right - rect.left + 1) / count;

			for (i = 0; i < count; i++)
			{
				pWnd->SetWindowPos(NULL, pos, 0, width, height, SWP_NOZORDER);
				pos += width;

				pWnd = pWnd->GetNextWindow();
			}

			break;

		case MDITILE_HORIZONTAL:
			height = (rect.bottom - rect.top + 1) / count;
			width  = rect.right - rect.left;

			for (i = 0; i < count; i++)
			{
				pWnd->SetWindowPos(NULL, 0, pos, width, height, SWP_NOZORDER);
				pos += height;

				pWnd = pWnd->GetNextWindow();
			}

			break;
	}
}