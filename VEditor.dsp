# Microsoft Developer Studio Project File - Name="VEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VEditor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VEditor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VEditor.mak" CFG="VEditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VEditor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VEditor - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX"VEditor.pch" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 comctl32.lib winmm.lib dsound.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "VEditor - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 comctl32.lib winmm.lib dsound.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "VEditor - Win32 Release"
# Name "VEditor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\chainWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\controls.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DragDrop.cpp
# End Source File
# Begin Source File

SOURCE=.\Input.cpp
# End Source File
# Begin Source File

SOURCE=.\LibProp.cpp
# End Source File
# Begin Source File

SOURCE=.\libTreeWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\midi.cpp
# End Source File
# Begin Source File

SOURCE=.\panel.cpp
# End Source File
# Begin Source File

SOURCE=.\patchWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\preset.cpp
# End Source File
# Begin Source File

SOURCE=.\SendPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\SendPatchForm.cpp
# End Source File
# Begin Source File

SOURCE=.\Settings.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\tools.cpp
# End Source File
# Begin Source File

SOURCE=.\VEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\VEditor.rc
# End Source File
# Begin Source File

SOURCE=".\vg-88.cpp"
# End Source File
# Begin Source File

SOURCE=.\vg88Common.cpp
# End Source File
# Begin Source File

SOURCE=.\VGWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkspaceView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\chainWnd.h
# End Source File
# Begin Source File

SOURCE=.\controls.h
# End Source File
# Begin Source File

SOURCE=.\DeviceSetting.h
# End Source File
# Begin Source File

SOURCE=.\DragDrop.h
# End Source File
# Begin Source File

SOURCE=.\Input.h
# End Source File
# Begin Source File

SOURCE=.\LibProp.h
# End Source File
# Begin Source File

SOURCE=.\libTreeWnd.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\midi.h
# End Source File
# Begin Source File

SOURCE=.\panel.h
# End Source File
# Begin Source File

SOURCE=.\patchWnd.h
# End Source File
# Begin Source File

SOURCE=.\preset.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SendPatch.h
# End Source File
# Begin Source File

SOURCE=.\SendPatchForm.h
# End Source File
# Begin Source File

SOURCE=.\Settings.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\tools.h
# End Source File
# Begin Source File

SOURCE=.\VEditor.h
# End Source File
# Begin Source File

SOURCE=".\VG-88.h"
# End Source File
# Begin Source File

SOURCE=.\VG88Common.h
# End Source File
# Begin Source File

SOURCE=.\VGWindow.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\2x2 Chorus.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\about.bmp
# End Source File
# Begin Source File

SOURCE=".\res\ac guitar.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Acous-mic.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Acous-Piezo.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\acousg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\amplifers.bmp
# End Source File
# Begin Source File

SOURCE=".\res\assign gk vol.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\AssignCtl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\assignGkS1S2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\assignMidi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\assignPedal.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Auto wah.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BG drive.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BG lead.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BG rythm.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Blues.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bodytype.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bowed.bmp
# End Source File
# Begin Source File

SOURCE=.\res\brass.bmp
# End Source File
# Begin Source File

SOURCE=.\res\brassB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ButtonCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ButtonDelete.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ButtonRename.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ButtonSave.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cable1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cable2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cablecorner.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cableinter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chain.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Chet.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Chorus.bmp
# End Source File
# Begin Source File

SOURCE=".\res\CLA-ST.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Clean twin.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Compressor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Crunch.bmp
# End Source File
# Begin Source File

SOURCE=.\res\crystal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\crystal2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\crystalB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursorg1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursorm.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursormp.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursormps.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursorms.cur
# End Source File
# Begin Source File

SOURCE=.\res\Defretter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Delay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelaySmall.bmp
# End Source File
# Begin Source File

SOURCE=.\res\detune.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Dial.bmp
# End Source File
# Begin Source File

SOURCE=.\res\digitled.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Dist Cla od.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Dist DS1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Dist DS2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Dist Fuzz.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Dist turbo od.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Down.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Drive stack.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\dual.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dualB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffAutoWah.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffChorus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffComp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffDefretter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffDelay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffDist.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffEq.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffFlanger.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffHarmo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffNS.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffPan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\effPedShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\effPedWah.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffPhaser.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffReverb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\effUniV.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EffVibrato.bmp
# End Source File
# Begin Source File

SOURCE=.\res\empty.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EqLabel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Equalizer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\faderH1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\faderV1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\filterBassB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\filterBassS.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Flanger.bmp
# End Source File
# Begin Source File

SOURCE=.\res\flute.bmp
# End Source File
# Begin Source File

SOURCE=.\res\flute2.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Foot volume.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\gk2a.bmp
# End Source File
# Begin Source File

SOURCE=.\res\gk2aB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\gkFunc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\guitar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\guitar.ico
# End Source File
# Begin Source File

SOURCE=.\res\GuitarNylon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GuitarNylonII.bmp
# End Source File
# Begin Source File

SOURCE=.\res\guitars.bmp
# End Source File
# Begin Source File

SOURCE=.\res\guitarsAcous.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Harmonist.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Jazz combo.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\JC-120.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\key.bmp
# End Source File
# Begin Source File

SOURCE=.\res\knob1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\knob2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\knob3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\knob4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\knob6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\knob7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\labelPan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\labels.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LBVGWin1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\lcd.bmp
# End Source File
# Begin Source File

SOURCE=".\res\lead stack.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\led1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\led2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Limiter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Lips.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LP.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LTVGWin1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LVGWin1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\match drive.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\match drive2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\match fat.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\match lead.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\MBVGWin1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Metal 5150.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Metal drive.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\metal lead.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\metal stack.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\mic1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mic2.bmp
# End Source File
# Begin Source File

SOURCE=".\res\MOD-ST.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\MS 1959 I + II.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\MS 1959 I.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\MS 1959 II.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Ms High Gain.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\MTVGWin1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MTVGWin1.bmp.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Nois supressor.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\nylon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\nylonB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NylonII.bmp
# End Source File
# Begin Source File

SOURCE=.\res\nylonIIB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\organ.bmp
# End Source File
# Begin Source File

SOURCE=.\res\organB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\organS.bmp
# End Source File
# Begin Source File

SOURCE=.\res\organSlider.bmp
# End Source File
# Begin Source File

SOURCE=.\res\outputSelect.bmp
# End Source File
# Begin Source File

SOURCE=".\res\P shifter.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\P-90.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\PAF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panel1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panel2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panel2x2Chorus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panel3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelAmp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelAutoWah.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelBody.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelBodyNylon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelBottom.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelChorus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelChorus2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelCompressor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelDelay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelEqualizer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelFlanger.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelFV.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelGT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelHarmonist.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelLimiter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelMixer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelNS.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelPan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelPanEff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelPdShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelPedalWah.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelPhaser.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelPickup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelPickupAcous.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelPickupNylon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelPickupVari.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelReverb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelShift.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PanelSubEqualizer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelTremolo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelVibrato.bmp
# End Source File
# Begin Source File

SOURCE=.\res\panelVolBmpKey.bmp
# End Source File
# Begin Source File

SOURCE=".\res\PD shift.bmp"
# End Source File
# Begin Source File

SOURCE=.\bmp\pFileBot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pFileBot.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp\pFileLeft.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pFileLeft.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp\pFileRight.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pFileRight.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp\pFileTop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pFileTop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\phaser.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pickup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pickupDouble1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pickupDouble2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pickupPos.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pickupSingle1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pickupSingle2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pickupType1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pickupType2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pipe.bmp
# End Source File
# Begin Source File

SOURCE=".\res\poly octave.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\poly slowgear.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\popup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ppwm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ppwmB.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Pro reverb.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\RBVGWin1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\rectifier orange.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\rectifier red.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\rectifier.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reverb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Rick.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RTVGWin1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RVGWin1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\S Equalizer.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\S-S-H.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\section.bmp
# End Source File
# Begin Source File

SOURCE=.\res\selector.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sitar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SitarB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sitarP.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Sldn lead.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\solo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\speaker.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Stack crunch.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\switch1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TEL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tremolo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\trumpet.bmp
# End Source File
# Begin Source File

SOURCE=.\res\trumpet2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tune.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tuner.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tweed.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Univibe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Vari.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VEditor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VEditor.ico
# End Source File
# Begin Source File

SOURCE=.\res\VEditor.rc2
# End Source File
# Begin Source File

SOURCE=".\res\vg-8Font.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\vg-8FontBW.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\VGSend.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Vibrato.bmp
# End Source File
# Begin Source File

SOURCE=.\res\violin.bmp
# End Source File
# Begin Source File

SOURCE=.\res\violin2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VLib.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VLib2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VlibB.bmp
# End Source File
# Begin Source File

SOURCE=".\res\vo clean.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\vo drive.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\vo lead.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Wah.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wah2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wave.bmp
# End Source File
# Begin Source File

SOURCE=.\res\waveSaw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\waveSquare.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ff
# End Source File
# Begin Source File

SOURCE=.\patch1
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section VEditor : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:108
# 	2:21:SplashScreenInsertKey:4.0
# End Section
