#if !defined(AFX_SETTINGS_H__2821D12F_685A_40A4_8AA7_BB007D905AFB__INCLUDED_)
#define AFX_SETTINGS_H__2821D12F_685A_40A4_8AA7_BB007D905AFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Settings.h : header file
//

#define	MAXDEVICES		5

#define	DEVICE_NODEVICE	0
#define	DEVICE_VG88		1
#define	DEVICE_VG8		2
#define	DEVICE_VG8EX	3
#define	DEVICE_VG8S1	4
#define	DEVICE_VGA7		5
#define	DEVICE_VGA5		6


struct SDevice
{
	int		type;			// VG-8, VG-88 ...
	char	name[32];		// Name that appear on the interface
	BYTE	deviceID;		// 1-38
	int		midiInputPort;
	int		midiOutputPort;
	int		auditionPatch;
};

struct SGeneralSetting
{
	int x;
	int y;
	int cx;
	int cy;
	bool isZoomed;
	bool chainWndVisible;
	bool libTreeWndVisible;
	bool patchWndVisible;
};

/////////////////////////////////////////////////////////////////////////////
// CSettings

class CSettings
{
public:
	int		devicesCount;
	SDevice	devices[MAXDEVICES];
	SGeneralSetting	generalSetting;

	CSettings();

	int Write();
	int Read();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGS_H__2821D12F_685A_40A4_8AA7_BB007D905AFB__INCLUDED_)
