        VEditor 0.5 - Librarian / Editor for the Roland VG-88
                    04/2003 by Ralph Benchetrit



VEditor Release Notes
---------------------

This is the Beta 0.5 of VEditor.

What is present in this version :
- full midi implementation
- patch editing / saving / sending to VG-88 / Receiving from VG-88 / renaming
- preset management (ie for pickup, amp, effects ...)
- system parameters (read only)
- open libraries in independant window
- libraries management (copy, delete, from one library to another)
- drag and drop

What is not present in this version (yet) :
- search option
- Undo

Requirements
------------

- Windows WMe, WNT4, WXP (W98 ? , W2000 ?)
- Minimum resolution 1152x864.
- 64 Mo Ram


Installation
------------


Just unzip the zip file in the directory you want
Note : If you have already installed a previous version of VEditor, choose a different directory 

Once files are extracted, copy manually all your .syx file to the directory VEditor\patch

you now can start VEditor.exe

The first time you start VEditor, Veditor display the configuration window :

Device ID : Set the same ID as the one in your VG-88 
		(on your  VG-88 from the display mode press F6 (System) than F5 (midi))

Input port / Output Port : Choose the port that are connected to your VG-88

Audition patch : Since VG-88 do not manage real time Midi message, you have to choose one user patch
			that will be used by VEditor to hear the patch you are editing. Each time you change
			a parameter, the whole patch is sent to the VG-88 (in the audition patch)

Important : If you want VEditor to jump to a patch in VEditor when you switch the patch on the VG-88,
you have first to configure the VG-88 to send midi Programme change. To do this, on your VG-88
press SYSTEM then press MIDI and set the parameter "F4:PROGRAM CHANGE OUT" to "ON"


Quick start
-----------
VEditor screen is divided into 4 parts

- The left side show you all your libraries (sysex) file. You can view the content 
  of a library by expanding the tree (as in the explorer). The library "VG-88 USER" and 
  "VG-88 PRESET" are the reflect of your VG-88. All other libraries are sysexfile. When
  VEditor start, it automatically open all syx files it found in the VEditor\patch directory.
  You can rename your patches as in the explorer (select the patch to rename and press the F2
  key or click one time on it). When the patch is in edit name mode, a window with all the VG-88
  charset appear. By this way, you can use special char (as the amp and guitar char). You can use
  the mouse to pick up the char you want, or you can use arrows keys to position the cursor on 
  the char you want, and hit the return key to get it (try it, it is easier than explan it).

- The top right side show you a graphical representation of the patch currently selected. The LCD
  screen show you the name of the patch, its number and the name of the library.
  you also have 3 buttons that are used to switch between different part of the editing screens.

- The main area of the screen is used for editing. All the names used are the same as in the VG-88
  so you will not be lost. This area is divided into panels, each panel is a VG-88 setting as it
  appear in the VG-88 (ie body, pickup, ...).
  To modify the value of a parameter, you can use use the left mouse button as in any other graphical
  application (such as cubase). You can either right click on the control, you will get a popup with
  all possible values for this control. This works with any control including some image (such as the
  amp or the guitar image). For the Variguitar intrument you can modify pickup position directly by
  manipulating the pickup on the image (not the angle for the moment), same for the mic setting in 
  the Cosm amp panel.
  Some panels include an ON/OFF button. When the panel is off, all the controls are desabled.

- You can use the buttons at the top to switch between Guitar & Amps, Effects/Level/Bmp Key and
  Pedal/assign.


Keyboard
--------
Tab         : move to next control
Shift + TAB : move to previous control

Up Arrow    
Right Arrow : Increment the value for the control that has the focus
"+"	      Hold Control key to go faster

down Arrow    
left Arrow  : Decrement the value for the control that has the focus
"-"	      Hold Control key to go faster

Enter	    : open a popup whith all possible values for the control (same as right click)
	      then in the popup, enter again to validate

Suppr key   : Set the control to its middle value (ie for a control from 0 to 100 the value is set to 50)

End key     : Set the control to its higher value

Home key    : Set the control to its lower value

Insert key  : Set the current panel On/Off (if there is an On/off button)

F5          : Switch to Guitare & Amp scren
F6          : Switch to Effect & Level/BMP/Key screen
F7          : Switch to Pedal/Assign screen
