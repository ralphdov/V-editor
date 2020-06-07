// LibProp.cpp : implementation file
//

#include "stdafx.h"
#include "veditor.h"
#include "LibProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibProp dialog


CLibProp::CLibProp(CWnd* pParent /*=NULL*/)
	: CDialog(CLibProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLibProp)
	m_firstPatch = -1;
	m_file = _T("");
	m_libraryName = _T("");
	//}}AFX_DATA_INIT
}


void CLibProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLibProp)
	DDX_CBIndex(pDX, IDC_FIRSTPATCH, m_firstPatch);
	DDX_Text(pDX, IDC_FILE, m_file);
	DDX_Text(pDX, IDC_LIBNAME, m_libraryName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLibProp, CDialog)
	//{{AFX_MSG_MAP(CLibProp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibProp message handlers
