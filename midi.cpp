#include "stdafx.h"
#include "midi.h"

void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	static WORD bank;

	switch (wMsg)	
	{
		case MIM_DATA:
			int status;
			int data1;
			int data2;

			status = LOBYTE(LOWORD(dwParam1));
			data1  = HIBYTE(LOWORD(dwParam1));
			data2  = LOBYTE(HIWORD(dwParam1));

			if (status >= 176 && status < 192)
			{
				// Control change
				if (data1 == 0)
					bank = data2;

			}
			else if (status >= 192 && status < 208)
			{
				// Patch change
				AfxGetMainWnd()->PostMessage(WM_MIDI_PATCH_CHANGE, dwInstance, MAKELONG(bank, data1));
			}

		break;

		case MIM_LONGDATA:
			// Patch change
			AfxGetMainWnd()->PostMessage(WM_MIDI_PATCH_RECEIVED, dwInstance, MAKELONG(dwParam1, dwParam2));
			break;
	}
}
