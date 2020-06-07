#ifndef __MIDI_H_
#define __MIDI_H_

#include <Mmsystem.h>

#define WM_MIDI_PATCH_CHANGE	WM_USER + 0
#define WM_MIDI_PATCH_RECEIVED	WM_USER + 1

void CALLBACK MidiInProc(HMIDIIN hMidiIn, 
						 UINT wMsg, 
						 DWORD dwInstance, 
						 DWORD dwParam1, 
						 DWORD dwParam2);

#endif __MIDI_H_