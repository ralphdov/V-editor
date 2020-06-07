// Settings.cpp : implementation file
//

#include "stdafx.h"
#include "mainfrm.h"
#include "Settings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettings

CSettings::CSettings()
{
	devicesCount = 0;
	memset(devices, 0, MAXDEVICES * sizeof(SDevice));
}


int CSettings::Read()
{
	CFileException		e;
	CFile				fileParam;
	int					i;
	
	// Open the file
	if (!fileParam.Open("VEditor.cfg", CFile::modeRead, &e))
		return 0;

	fileParam.Read(devices, MAXDEVICES * sizeof(SDevice));

	for (i = 0; i < MAXDEVICES; i++)
		if (devices[i].type != DEVICE_NODEVICE)
			devicesCount++;
	
	fileParam.Read(&generalSetting, sizeof(SGeneralSetting));

	fileParam.Close();
		
	return 1;
}


int CSettings::Write()
{
	CFileException		e;
	CFile				fileParam;
	
	// Open the file
	if (!fileParam.Open(((CMainFrame *) AfxGetMainWnd())->m_editorPath + "\\VEditor.cfg", CFile::modeWrite | CFile::modeCreate, &e))
		return 0;

	fileParam.Write(devices, MAXDEVICES * sizeof(SDevice));
	fileParam.Write(&generalSetting, sizeof(SGeneralSetting));

	fileParam.Close();

	return 1;
}