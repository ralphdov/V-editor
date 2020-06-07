#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <typeinfo>
#include <Afx.h>
#include "MainFrm.h"
#include "stdafx.h"
#include "vg88Common.h"
#include "vg-88.h"

extern CPatch		*g_currentPatch;
extern int			g_currentPatchNumber;
extern CVG88SysEx	*g_currentLibrary;


//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
//                              Tables definition                               //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

char *T_pickupModel[]		= {"LP", "CLA-ST", "MOD-ST", "TEL", "P-90", "LIPS", "P.A.F.", "RICK", "CHET", "S-S-H", "VARI"};
char *T_pickupPickup3[]		= {"REAR", "", "R+F", "", "FRONT"};
char *T_pickupPickup5[]		= {"REAR", "C+R", "CENTER", "F+C", "FRONT"};
char *T_pickupType[]		= {"SINGLE", "DOUBLE", "PIEZO", "ACOUSTIC"};
char *T_bodyType[]			= {"FLAT", "ROUND", "f HOLE", "METAL", "BANJO"};
char *T_variGtHarm_hrHarm[]	= {"-2oct", "-14th", "-13th", "-12th", "-11th", "-10th", "-9th", "-1oct", "-7th", "-6th", "-5th", "-4th", "-3rd", "-2nd", "Tonic", "+2nd", "+3rd", "+4th", "+5th", "+6th", "+7th", "+1oct", "+9th", "+10th", "+11th", "+12th", "+13th", "+14th", "+2oct", "USER"};
char *T_lowCut[]			= {"55.0Hz", "110Hz", "165Hz", "200Hz", "280Hz", "340Hz", "400Hz", "500Hz", "630Hz", "800Hz"};
char *T_lowCut2[]			= {"THRU", "55.0Hz", "110Hz", "165Hz", "200Hz", "280Hz", "340Hz", "400Hz", "500Hz", "630Hz", "800Hz"};
char *T_highCut[]			= {"700Hz", "1.00kHz", "1.40kHz", "2.00kHz", "3.00kHz", "4.00kHz", "6.00kHz", "8.00kHz", "11.0kHz", "FLAT"};
char *T_tuneType[]			= {"OPEN-D", "OPEN-E", "OPEN-G", "OPEN-A", "DROP-D", "NASH-VILLE", "USER"};
char *T_distMode[]			= {"CLA OD", "TURBO OD", "DS1", "DS2", "FUZZ"};
char *T_eqMidF[]			= {"100\nHz", "125\nHz", "160\nHz", "200\nHz", "250\nHz", "315\nHz", "400\nHz", "500\nHz", "630\nHz", "800\nHz", "1.00\nkHz", "1.25\nkHz", "1.60\nkHz", "2.00\nkHz", "2.50\nkHz", "3.15\nkHz", "4.00\nkHz", "5.00\nkHz", "6.30\nkHz", "8.00\nkHz", "10.0\nkHz"};
char *T_eqMidQ[]			= {"0.5", "1", "2", "4", "8", "16"};
char *T_key[]				= {"C (Am)", "Db (Bbm)", "D (Bm)", "Eb (Cm)", "E (C#m)", "F (Dm)", "F# (Ebm)", "G (Em)", "Ab (Fm)", "A (F#m)", "Bb (Gm)", "B (G#m)"};
char *T_chain[]				= {"COMP", "WAH", "AMP", "EQ", "FV", "NS", "MOD", "DLY", "CHO", "REV"};
char *T_guitarType[]		= {"VARI GT", "ACOUSTIC", "NYLON STRINGS", "OPEN TUNE", "12STRINGS", "PD SHIFT", "POLY DIST", "POLY COMP", "POLY OCT", "POLY SG", "BOWED", "DUAL", "FILTER BASS", "PIPE", "SOLO", "PWM", "CRYSTAL", "ORGAN","BRASS", "NYLON II", "SITAR", "WAVE SYNTH"};
char *T_ampType[]			= {"JC-120", "CLEAN TWIN", "CRUNCH", "MATCH DRIVE", "VO DRIVE", "BLUES", "BG LEAD", "MS1959 (I)", "MS1959 (II)", "MS1959 (I + II)", "SLDN LEAD", "METAL 5150", "METAL DRIVE", "AC.GUITAR", "JAZZ COMBO", "PRO CRUNCH", "TWEED", "STACK CRUNCH", "VO LEAD", "VO CLEAN", "MATCH LEAD", "FAT MATCH", "BG DRIVE", "BG RYTHM", "MS HIGH GAIN", "R-FIER RED", "R-FIER ORANGE", "R-FIER VINT", "DRIVE STACK", "LEAD STACK", "METAL STACK", "METAL LEAD"};
char *T_speakerType[]		= {"SMALL", "MIDDLE", "JC-120", "TWIN ON", "TWIN OFF", "MATCH ON", "MATCH OFF", "VO ON", "VO OFF", "BG STACK ON", "BG STACK OFF", "MS STACK ON", "MS STACK OFF", "METAL STACK", "ACOUSTIC", "PRO RVB", "TWEED", "R-FIER"};
char *T_rate[]				= {"4.0", "3.0", "8/3", "2.0", "1.5", "4/3", "1.0", "3/4", "2/3", "1/2", "3/8", "1/3", "1/4"};
char *T_modType[]			= {"HARMONIST", "P.SHIFTER", "FLANGER", "PHASER", "SUB EQ", "2x2CHORUS", "TREMOLO", "PAN", "PD SHIFT", "VIBRATO", "DEFRETTER", "UNI-V"};
char *T_delay[]				= {"1/4", "1/3", "3/8", "1/2", "2/3", "3/4", "1.0", "4/3", "1.5", "2.0", "8/3", "3.0", "4.0"};
char *T_xOverF[]			= {"100Hz", "125Hz", "160Hz", "200Hz", "250Hz", "315Hz", "400Hz", "500Hz", "630Hz", "800Hz", "1.00kHz", "1.25kHz", "1.60kHz", "2.00kHz", "2.50kHz", "3.15kHz", "4.00kHz"};
char *T_source[]			= {"EXP PEDAL", "CTL PEDAL", "SUB EXP", "SUB CTL1", "SUB CTL2", "GK VOL", "GK S1/S2"};
char *T_downS1S2[]			= {"ASSIGNABLE", "MASTER LEVEL", "PEDAL FUNC", "PATCH SELECT", "PU SELECT", "TUNER/BPM"};
char *T_synthVol[]			= {"ASSIGNABLE", "PICKUP LEVEL", "MIXER LEVEL", "MASTER LEVEL"};
char *T_outputSelect[]		= {"GUITAR AMP COMBO", "GUITAR AMP STACK", "PA + SP/RETURN COMBO", "PA + SP/RETURN STACK", "LINE / PHONES"};
char *T_driverType[]		= {"GK-2A", "GK-2", "PIEZO"};
char *T_bankSwMode[]		= {"WAIT NUM", "NUMBER 1", "SAME NUM"};
char *T_subCtl[]			= {"ASSIGNABLE", "TUNER", "BMP(TAP)", "PU to FRONT", "PU to REAR"};
char *T_wahModel[]			= {"ORIGINAL", "CRY WAH", "VO WAH", "FAT WAH", "LIGHT WAH", "7STR WAH"};
char *T_spickupPosition[]	= {"FRONT", "F+R", "REAR", "PIEZO"};
char *T_target[]			= { "COSM GT     ON/OFF",
								"F-BASS       COLOR",
								"BODY        ATTACK",
								"BODY          BODY",
								"BODY       LOW CUT",
								"BODY         LEVEL",
								"COSM EQ     ON/OFF",
								"COSM EQ      LEVEL",
								"COSM EQ    L-MID G",
								"COSM EQ      LOW G",
								"COSM EQ     HIGH G",
								"COSM EQ    H-MID G",
								"PICKUP      PICKUP",
								"PICKUP        TONE",
								"PICKUP       LEVEL",
								"PT SHIFT    ON/OFF",
								"PT SHIFT    SHIFT1",
								"PT SHIFT    SHIFT2",
								"PT SHIFT    SHIFT3",
								"PT SHIFT    SHIFT4",
								"PT SHIFT    SHIFT5",
								"PT SHIFT    SHIFT6",
								"PT SHIFT     FINE1",
								"PT SHIFT     FINE2",
								"PT SHIFT     FINE3",
								"PT SHIFT     FINE4",
								"PT SHIFT     FINE5",
								"PT SHIFT     FINE6",
								"PT SHIFT  E.LEVEL1",
								"PT SHIFT  E.LEVEL2",
								"PT SHIFT  E.LEVEL3",
								"PT SHIFT  E.LEVEL4",
								"PT SHIFT  E.LEVEL5",
								"PT SHIFT  E.LEVEL6",
								"PT SHIFT  D.LEVEL1",
								"PT SHIFT  D.LEVEL2",
								"PT SHIFT  D.LEVEL3",
								"PT SHIFT  D.LEVEL4",
								"PT SHIFT  D.LEVEL5",
								"PT SHIFT  D.LEVEL6",
								"PT SHIFT    HARMO1",
								"PT SHIFT    HARMO2",
								"PT SHIFT    HARMO3",
								"PT SHIFT    HARMO4",
								"PT SHIFT    HARMO5",
								"PT SHIFT    HARMO6",
								"TUNE        ON/OFF",
								"TUNE     TUNE TYPE",
								"TUNE        SHIFT1",
								"TUNE        SHIFT2",
								"TUNE        SHIFT3",
								"TUNE        SHIFT4",
								"TUNE        SHIFT5",
								"TUNE        SHIFT6",
								"DETUNE      ON/OFF",
								"DETUNE      DETUNE",
								"COSM PAN  STRING-1",
								"COSM PAN  STRING-2",
								"COSM PAN  STRING-3",
								"COSM PAN  STRING-4",
								"COSM PAN  STRING-5",
								"COSM PAN  STRING-6",
								"PD SHIFT    ON/OFF",
								"PD SHIFT     PITCH",
								"PD SHIFT  STRING-1",
								"PD SHIFT  STRING-2",
								"PD SHIFT  STRING-3",
								"PD SHIFT  STRING-4",
								"PD SHIFT  STRING-5",
								"PD SHIFT  STRING-6",
								"DIST        ON/OFF",
								"DIST         DRIVE",
								"DIST         LEVEL",
								"DIST     POLY RATE",
								"DIST       DRV BAL",
								"COSM COMP   ON/OFF",
								"COSM COMP  SUSTAIN",
								"COSM COMP     TONE",
								"COSM COMP    LEVEL",
								"COSM COMPTHRESHOLD",
								"OCTAVE      ON/OFF",
								"OCTAVE      -1OCT1",
								"OCTAVE      -1OCT2",
								"OCTAVE      -1OCT3",
								"OCTAVE      -1OCT4",
								"OCTAVE      -1OCT5",
								"OCTAVE      -1OCT6",
								"OCTAVE      -2OCT1",
								"OCTAVE      -2OCT2",
								"OCTAVE      -2OCT3",
								"OCTAVE      -2OCT4",
								"OCTAVE      -2OCT5",
								"OCTAVE      -2OCT6",
								"OCTAVE        DIR1",
								"OCTAVE        DIR2",
								"OCTAVE        DIR3",
								"OCTAVE        DIR4",
								"OCTAVE        DIR5",
								"OCTAVE        DIR6",
								"SG          ON/OFF",
								"MIXER      BALANCE",
								"MIXER        LEVEL",
								"FILTER      CUTOFF",
								"FILTER       DECAY",
								"ATTACK      LENGTH",
								"ATTACK    MOD-TUNE",
								"ATTACK     MOD-DEP",
								"ATTACK       LEVEL",
								"ORGAN       FEET-4",
								"ORGAN       FEET-8",
								"ORGAN      FEET-16",
								"P-BEND    P-BEND Q",
								"GLIDE     GLD-SENS",
								"COSM MOD     DEPTH",
								"COSM MOD      RATE",
								"COSM AMP    ON/OFF",
								"COSM AMP    VOLUME",
								"COSM AMP  PRESENCE",
								"COSM AMP  HIGH CUT",
								"COSM AMP    MASTER",
								"COSM AMP      BASS",
								"COSM AMP    MIDDLE",
								"COSM AMP    TREBLE",
								"COSM AMP      GAIN",
								"COSM AMP    BRIGHT",
								"FX:COMP     ON/OFF",
								"FX:COMP    SUSTAIN",
								"FX:COMP       TONE",
								"FX:COMP      LEVEL",
								"FX:LM    THRESHOLD",
								"FX:LM         TONE",
								"FX:LM        LEVEL",
								"FX:WAH      ON/OFF",
								"FX:PD WAH     FREQ",
								"FX:PD WAH    LEVEL",
								"FX:AT WAH     FREQ",
								"FX:AT WAH     PEAK",
								"FX:AT WAH     RATE",
								"FX:AT WAH    DEPTH",
								"FX:AT WAH    LEVEL",
								"FX:EQ       ON/OFF",
								"FX:EQ        LEVEL",
								"FX:EQ      L-MID G",
								"FX:EQ        LOW G",
								"FX:EQ       HIGH G",
								"FX:EQ      H-MID G",
								"FX:MOD      ON/OFF",
								"FX:HARMO  1:ON/OFF",
								"FX:HARMO 1:HARMONY",
								"FX:HARMO     1:PAN",
								"FX:HARMO   1:LEVEL",
								"FX:HARMO   DIR LEV",
								"FX:HARMO  2:ON/OFF",
								"FX:HARMO 2:HARMONY",
								"FX:HARMO     2:PAN",
								"FX:HARMO   2:LEVEL",
								"FX:P.SFT  1:ON/OFF",
								"FX:P.SFT   1:SHIFT",
								"FX:P.SFT    1:FINE",
								"FX:P.SFT  1:F.BACK",
								"FX:P.SFT     1:PAN",
								"FX:P.SFT   1:LEVEL",
								"FX:P.SFT DIR LEVEL",
								"FX:P.SFT  2:ON/OFF",
								"FX:P.SFT   2:SHIFT",
								"FX:P.SFT    2:FINE",
								"FX:P.SFT     2:PAN",
								"FX:P.SFT   2:LEVEL",
								"FX:FL         RATE",
								"FX:FL        DEPTH",
								"FX:FL       MANUAL",
								"FX:FL    RESONANCE",
								"FX:FL        LEVEL",
								"FX:PH         RATE",
								"FX:PH        DEPTH",
								"FX:PH       MANUAL",
								"FX:PH    RESONANCE",
								"FX:PH        LEVEL",
								"FX:PH         STEP",
								"FX:SUB EQ    LEVEL",
								"FX:SUB EQ  L-MID G",
								"FX:SUB EQ    LOW G",
								"FX:SUB EQ   HIGH G",
								"FX:SUB EQ  H-MID G",
								"FX:2x2CE    L-RATE",
								"FX:2x2CE   L-DEPTH",
								"FX:2x2CE   L-LEVEL",
								"FX:2x2CE    H-RATE",
								"FX:2x2CE   H-DEPTH",
								"FX:2x2CE   H-LEVEL",
								"FX:TR         RATE",
								"FX:TR        DEPTH",
								"FX:PAN        RATE",
								"FX:PAN       DEPTH",
								"FX:PD SFT    PITCH",
								"FX:VB      TRIGGER",
								"FX:VB         RATE",
								"FX:VB        DEPTH",
								"FX:DELAY    ON/OFF",
								"FX:DELAY  DLY TIME",
								"FX:DELAY  FEEDBACK",
								"FX:DELAY DLY LEVEL",
								"FX:CHORUS   ON/OFF",
								"FX:CHORUS     RATE",
								"FX:CHORUS    DEPTH",
								"FX:CHORUS CE LEVEL",
								"FX:REVERB   ON/OFF",
								"FX:REVERB REV TIME",
								"FX:REVERB  REV LEV",
								"FX:NS       ON/OFF",
								"FX:FV        LEVEL",
								"MASTER       LEVEL",
								"MASTER    BPM(TAP)",
								"MASTER         KEY",
								"TUNER       ON/OFF",
								"NYLON2      ATTACK",
								"NYLON2        BODY",
								"NYLON2        TONE",
								"NYLON2       LEVEL",
								"SITAR       PICKUP",
								"SITAR         BODY",
								"SITAR         SENS",
								"SITAR         TONE",
								"SITAR        LEVEL",
								"SITAR        COLOR",
								"SITAR        DECAY",
								"SITAR         BUZZ",
								"SITAR      ATK LEV",
								"WAVE         SHAPE",
								"WAVE          SENS",
								"WAVE        ATTACK",
								"WAVE         DECAY",
								"WAVE         LEVEL",
								"WAVE        CUTOFF",
								"WAVE          RESO",
								"WAVE    FLT ATTACK",
								"WAVE     FLT DECAY",
								"WAVE     FLT DEPTH",
								"FX:DEFRET     TONE",
								"FX:DEFRET     SENS",
								"FX:DEFRET   ATTACK",
								"FX:DEFRET    DEPTH",
								"FX:DEFRET     RESO",
								"FX:DEFRET    E.LEV",
								"FX:DEFRET    D.LEV",
								"FX:UNI-V      RATE",
								"FX:UNI-V     DEPTH",
								"FX:UNI-V     LEVEL"
								};
								


//////////// CVGData //////////////

CVGData::CVGData()
{
	m_needSaving = TRUE;
}


int CVGData::getValue()
{
	return m_data;
}


void CVGData::setValue(int value)
{
	if (g_currentLibrary && m_needSaving && m_data != value)
		g_currentLibrary->SetModifiedFlag();

	m_data = value;
}


void CVGData::getString(char *dest)
{
	sprintf(dest, "%d", getValue());
}


int CVGData::getRange()
{
	return 101;
}


int CVGData::getFirstValue()
{
	return 0;
}

int CVGData::setVGData(char **buffer)
{
	m_data = **buffer * 16;
	*buffer += 1;
		
	m_data += **buffer;
	*buffer += 1;

	return 2;
}


int CVGData::getVGData(char **buffer)
{
	**buffer = m_data / 16;
	*buffer += 1;
	**buffer = m_data % 16;
	*buffer += 1;

	return 2;
}

char ** CVGData::getTabString()
{
	int range;
	int firstValue;
	int i, j, len;
	char buffer[255];
	char **tabString;
	int dataBackup;
	bool needSaving;

	range = getRange();
	firstValue = getFirstValue();
	dataBackup = getValue();
	needSaving = m_needSaving;
	m_needSaving = FALSE;

	tabString = (char **) malloc(sizeof (char **) * range);

	for (i = 0; i < range; i++)
	{
		setValue(i + getFirstValue());

		if (getValue() == i + getFirstValue())
			getString(buffer);
		else
			buffer[0] = '\0';

		len = strlen(buffer);
		tabString[i] = (char *) malloc(len + 1);

		for (j = 0; j < len; j++)
			if (buffer[j] == '\n')
				buffer[j] = '\t';

		strcpy(tabString[i], buffer);
	}

	setValue(dataBackup);
	m_needSaving = needSaving;

	return tabString;
}


void CVGData::freeTabString(char **tabString)
{
	int range;
	int i;

	range = getRange();

	for (i = 0; i < range; i++)
		free(tabString[i]);

	free(tabString);
}


//////////// CVGDataLong //////////////

int CVGDataLong::setVGData(char **buffer)
{
	int m_dataTemp;

	m_dataTemp = **buffer * 16;
	*buffer += 1;
		
	m_dataTemp += **buffer;
	*buffer += 1;

	m_data = **buffer * 16;
	*buffer += 1;
		
	m_data += **buffer;
	*buffer += 1;

	m_data = m_dataTemp + (m_data * 256);

	return 4;
}


int CVGDataLong::getVGData(char **buffer)
{
	**buffer = (m_data % 256) / 16;
	*buffer += 1;
	**buffer = (m_data % 256) % 16;
	*buffer += 1;

	**buffer = (m_data / 256) / 16;
	*buffer += 1;
	**buffer = (m_data / 256) % 16;
	*buffer += 1;

	return 4;
}


//////////// CVGDataShort //////////////

int CVGDataShort::setVGData(char **buffer)
{
	m_data = **buffer;
	*buffer += 1;

	return 1;
}


int CVGDataShort::getVGData(char **buffer)
{
	**buffer = m_data;
	*buffer += 1;

	return 1;
}

//////////// CNumN24To24 //////////////

void CNumN24To24::setValue(int value)
{
	if (value >= 0 && value <= 48)
		CVGData::setValue(value);
}

void CNumN24To24::getString(char *dest)
{
	if (getValue() == 24)
		sprintf(dest, "%d", getValue() - 24);
	else
		sprintf(dest, "%+d", getValue() - 24);
}

int CNumN24To24::getRange()
{
	return 49;
}



//////////// CNum0To120 //////////////

void CNum0To120::setValue(int value)
{
	if (value >= 0 && value <= 120)
		CVGData::setValue(value);
}


int CNum0To120::getRange()
{
	return 121;
}


//////////// CNum0To126 //////////////

void CNum0To126::setValue(int value)
{
	if (value >= 0 && value <= 126)
		CVGData::setValue(value);
}


int CNum0To126::getRange()
{
	return 127;
}


//////////// CNum1To127 //////////////

void CNum1To127::setValue(int value)
{
	if (value >= 1 && value <= 127)
		CVGData::setValue(value);
}


int CNum1To127::getRange()
{
	return 127;
}



int CNum1To127::getFirstValue()
{
	return 1;
}


//////////// CNum0To200 //////////////

void CNum0To200::setValue(int value)
{
	if (value >= 0 && value <= 200)
		CVGData::setValue(value);
}


int CNum0To200::getRange()
{
	return 201;
}



//////////// CNumN50To50 //////////////

void CNumN50To50::setValue(int value)
{
	if (value >= 0 && value <= 100)
		CVGData::setValue(value);
}

void CNumN50To50::getString(char *dest)
{
	if (getValue() == 50)
		sprintf(dest, "%d", getValue() - 50);
	else
		sprintf(dest, "%+d", getValue() - 50);
}

int CNumN50To50::getRange()
{
	return 101;
}

//////////// CNum0To100 //////////////

void CNum0To100::setValue(int value)
{
	if (value >= 0 && value <= 100)
		CVGData::setValue(value);
}


int CNum0To100::getRange()
{
	return 101;
}


//////////// CNum0To100S //////////////

void CNum0To100S::setValue(int value)
{
	if (value >= 0 && value <= 100)
		CVGData::setValue(value);
}


int CNum0To100S::getRange()
{
	return 101;
}



//////////// CNum1To65S //////////////

void CNum1To65S::setValue(int value)
{
	if (value >= 1 && value <= 65)
		CVGData::setValue(value);
}


int CNum1To65S::getRange()
{
	return 65;
}



//////////// CNum0To127S //////////////

void CNum0To127S::setValue(int value)
{
	if (value >= 0 && value <= 127)
		CVGData::setValue(value);
}


int CNum0To127S::getRange()
{
	return 128;
}


//////////// CNum0To10 //////////////
void CNum0To10::setValue(int value)
{
	if (value >= 0 && value <= 10)
		CVGData::setValue(value);
}


int CNum0To10::getRange()
{
	return 11;
}



//////////// CPickupModel //////////////

void CPickupModel::setValue(int value)
{
	if (value >= 0 && value <= 10)
		CVGData::setValue(value);
}


void CPickupModel::getString(char *dest)
{
	strcpy(dest, T_pickupModel[getValue()]);
}


int CPickupModel::getRange()
{
	return 11;
}



//////////// CAPickupType //////////////

void CAPickupType::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "PIEZO");
	else
		strcpy(dest, "MIC");
}


//////////// CPickupPosition //////////////

void CPickupPosition::setValue(int value)
{
	if (value >= 0 && value <= 63)
		CVGData::setValue((value));
}


void CPickupPosition::getString(char *dest)
{
	sprintf(dest, "%d mm", (getValue() * 5) + 5);
}


int CPickupPosition::getRange()
{
	return 64;
}



//////////// CSPickupPosition //////////////

void CSPickupPosition::setValue(int value)
{
	if (value >= 0 && value <= 4)
		CVGData::setValue(value);
}


void CSPickupPosition::getString(char *dest)
{
	strcpy(dest, T_spickupPosition[getValue()]);
}


int CSPickupPosition::getRange()
{
	return 4;
}

//////////// CEqValue //////////////

void CEqValue::setValue(int value)
{
	if (value >= 0 && value <= 40)
		CVGData::setValue((value));
}


void CEqValue::getString(char *dest)
{
	sprintf(dest, "%+d\ndb", getValue() - 20);
}


int CEqValue::getRange()
{
	return 41;
}



//////////// CEqMidF //////////////

void CEqMidF::setValue(int value)
{
	if (value >= 0 && value <= 20)
		CVGData::setValue((value));
}


void CEqMidF::getString(char *dest)
{
	strcpy(dest, T_eqMidF[getValue()]);
}


int CEqMidF::getRange()
{
	return 21;
}



//////////// CEqMidQ //////////////

void CEqMidQ::setValue(int value)
{
	if (value >= 0 && value <= 5)
		CVGData::setValue((value));
}


void CEqMidQ::getString(char *dest)
{
	strcpy(dest, T_eqMidQ[getValue()]);
}


int CEqMidQ::getRange()
{
	return 6;
}



//////////// CPickupAngle //////////////

void CPickupAngle::setValue(int value)
{
	if (value >= 0 && value <= 126)
		CVGData::setValue((value));
}


void CPickupAngle::getString(char *dest)
{
	sprintf(dest, "%d mm", (getValue() * 5) - 315);
}


int CPickupAngle::getRange()
{
	return 127;
}


//////////// CPickupAngle //////////////


void CPickupPhase::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "IN");
	else
		strcpy(dest, "OUT");
}


//////////// CPickupType //////////////

void CPickupType::setValue(int value)
{
	if (value >=0 && value <= 3)
		CVGData::setValue(value);
}


void CPickupType::getString(char *dest)
{
	strcpy(dest, T_pickupType[getValue()]);
}


int CPickupType::getRange()
{
	return 4;
}



//////////// CPickupPickup //////////////

CPickupPickup::CPickupPickup()
{
	type = PICKUP_5POS;
}

void CPickupPickup::setValue(int value)
{
	if ((value >=0 && value <= 4 && type == PICKUP_5POS) ||
		 ((value ==0 || value == 2 || value == 4) && type == PICKUP_3POS))
		CVGData::setValue(value);
}


void CPickupPickup::getString(char *dest)
{
	if (type == PICKUP_3POS)
		strcpy(dest, T_pickupPickup3[getValue()]);
	else
		strcpy(dest, T_pickupPickup5[getValue()]);
}


int CPickupPickup::getRange()
{
	return 5;
}


void CPickupPickup::setPickupType(int pickup)
{
	switch (pickup)
	{
		case PICKUP_LP:
		case PICKUP_TEL:
		case PICKUP_P_90:
		case PICKUP_LIPS:
		case PICKUP_PAF:
		case PICKUP_RICK:
		case PICKUP_CHET:
		case PICKUP_VARI:

			if (getValue() == PICKUPPOS_C_R || getValue() == PICKUPPOS_F_C
				|| (getValue() == PICKUPPOS_CENTER && type == PICKUP_5POS))
				setValue(PICKUPPOS_F_R);

			type = PICKUP_3POS;

			break;

		case PICKUP_CLA_ST:
		case PICKUP_MOD_ST:
		case PICKUP_SSH:
			type = PICKUP_5POS;
			break;
	}
}


//////////// CPitchShiftMode //////////////

void CPitchShiftMode::setValue(int value)
{
	if (value == 0 || value == 1)
		CVGData::setValue(value);
}


void CPitchShiftMode::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "SHIFT");
	else
		strcpy(dest, "HARMO");
}


int CPitchShiftMode::getRange()
{
	return 2;
}



//////////// CPitch //////////////

int CPitch::setVGData(char **buffer)
{
	int count;

	count = CVGDataLong::setVGData(buffer);

	m_data = m_data / 100;

	return count;
}


int CPitch::getVGData(char **buffer)
{
	int count;

	m_data = m_data * 100;
	count = CVGDataLong::getVGData(buffer);
	m_data = m_data / 100;

	return count;
}

void CPitch::setValue(int value)
{
	if (value >= 0 && value <= 48)
		CVGDataLong::setValue(value);
}


void CPitch::getString(char *dest)
{
	if (getValue() == 24)
		sprintf(dest, "%d", getValue() - 24);
	else
		sprintf(dest, "%+d", getValue() - 24);
}


int CPitch::getRange()
{
	return 49;
}


//////////// CCompMode //////////////

void CCompMode::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "COMP");
	else
		strcpy(dest, "LIMITER");
}



//////////// CVariGtHarm //////////////

void CVariGtHarm::setValue(int value)
{
	if (value >=0 && value <= 28)
		CVGData::setValue(value);
}


void CVariGtHarm::getString(char *dest)
{
	strcpy(dest, T_variGtHarm_hrHarm[getValue()]);
}


int CVariGtHarm::getRange()
{
	return 29;
}


//////////// CLowCut //////////////

void CLowCut::setValue(int value)
{
	if (value >=0 && value <= 9)
		CVGData::setValue(value);
}


void CLowCut::getString(char *dest)
{
	strcpy(dest, T_lowCut[getValue()]);
}

int CLowCut::getRange()
{
	return 10;
}




//////////// CLowCut2 //////////////

void CLowCut2::setValue(int value)
{
	if (value >=0 && value <= 10)
		CVGData::setValue(value);
}


void CLowCut2::getString(char *dest)
{
	strcpy(dest, T_lowCut2[getValue()]);
}

int CLowCut2::getRange()
{
	return 11;
}



//////////// CHighCut //////////////

void CHighCut::setValue(int value)
{
	if (value >=0 && value <= 9)
		CVGData::setValue(value);
}


void CHighCut::getString(char *dest)
{
	strcpy(dest, T_highCut[getValue()]);
}


int CHighCut::getRange()
{
	return 10;
}



//////////// CBodyType //////////////

void CBodyType::setValue(int value)
{
	if (value >=0 && value <= 4)
		CVGData::setValue(value);
}


void CBodyType::getString(char *dest)
{
	strcpy(dest, T_bodyType[getValue()]);
}


int CBodyType::getRange()
{
	return 5;
}



//////////// COnOff //////////////

void COnOff::setValue(int value)
{
	if (value == 0 || value == 1)
		CVGData::setValue(value);
}


void COnOff::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "OFF");
	else
		strcpy(dest, "ON");
}


int COnOff::getRange()
{
	return 2;
}



//////////// COnOffS //////////////

void COnOffS::setValue(int value)
{
	if (value == 0 || value == 1)
		CVGData::setValue(value);
}


void COnOffS::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "OFF");
	else
		strcpy(dest, "ON");
}


int COnOffS::getRange()
{
	return 2;
}


//////////// CTuneType //////////////

void CTuneType::setValue(int value)
{
	if (value >=0 && value <= 6)
		CVGData::setValue(value);
}


void CTuneType::getString(char *dest)
{
	strcpy(dest, T_tuneType[getValue()]);
}


int CTuneType::getRange()
{
	return 7;
}



//////////// CDistMode //////////////

void CDistMode::setValue(int value)
{
	if (value >=0 && value <= 4)
		CVGData::setValue(value);
}


void CDistMode::getString(char *dest)
{
	strcpy(dest, T_distMode[getValue()]);
}


int CDistMode::getRange()
{
	return 5;
}




//////////// CBPM //////////////

void CBPM::setValue(int value)
{
	if (value >= 40 && value <= 251)
		CVGData::setValue(value);
}


void CBPM::getString(char *dest)
{
	int value = getValue();

	if (value == 251)
		strcpy(dest, "MIDI");
	else
		CVGData::getString(dest);
}


int CBPM::getRange()
{
	return 212;
}


int CBPM::getFirstValue()
{
	return 40;
}


//////////// CKey //////////////

void CKey::setValue(int value)
{
	if (value >=0 && value <= 11)
		CVGData::setValue(value);
}


void CKey::getString(char *dest)
{
	strcpy(dest, T_key[getValue()]);
}


int CKey::getRange()
{
	return 12;
}



//////////// CName //////////////

void CName::setString(char *name)
{
	int i, j;
	
	for (i = 0; i < 8; i++)
	{
		if (name[i] == 0)
		{
			for (j = i; j < 8; j++)
				car[j].setValue(' ');

			return;
		}
		else
			car[i].setValue(name[i]);
	}
}


void CName::getString(char *name)
{
	int i;
	char value;
	
	for (i = 0; i < 8; i++)
	{
		value = car[i].getValue();

		if (value == 0 || value > 127)
			name[i] = ' ';
		else
			name[i] = value;
	}

	for (i = 7; i >= 0; i--)
	{
		if (name[i] != ' ')
		{
			name[i + 1] = 0;

			return;
		}
	}

	name[0] = 0;
}


int CName::setVGData(char **buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
		count += car[i].setVGData(buffer);

	return count;
}



int CName::getVGData(char **buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
		count += car[i].getVGData(buffer);

	return count;
}



//////////// CChain //////////////

void CChain::setValue(int value)
{
	if (value >= 0 && value <= 9)
		CVGData::setValue(value);
}


void CChain::getString(char *dest)
{
	strcpy(dest, T_chain[getValue()]);
}


int CChain::getRange()
{
	return 10;
}




//////////// CPanBalance //////////////

void CPanBalance::setValue(int value)
{
	if (value >= 0 && value <= 100)
		CVGData::setValue(value);
}


void CPanBalance::getString(char *dest)
{
	int value = getValue();

	sprintf(dest, "   %d\t\t\t  %d", 100 - value, value);
}


int CPanBalance::getRange()
{
	return 101;
}



//////////// CPanBalanceST //////////////

void CPanBalanceST::getString(char *dest)
{
	int value = getValue();

	sprintf(dest, "%d - %d", 100 - value, value);
}


//////////// CMixerBalance //////////////

void CMixerBalance::setValue(int value)
{
	if (value >= 0 && value <= 100)
		CVGData::setValue(value);
}


void CMixerBalance::getString(char *dest)
{
	int value = getValue();

	sprintf(dest, "%d - %d", 100 - value, value);
}


int CMixerBalance::getRange()
{
	return 101;
}



//////////// CMAmpBalance //////////////

void CMAmpBalance::setValue(int value)
{
	if (value >= 0 && value <= 100)
		CVGData::setValue(value);
}


void CMAmpBalance::getString(char *dest)
{
	int value = getValue();

	sprintf(dest, "%d - %d", 100 - value, value);
}


int CMAmpBalance::getRange()
{
	return 101;
}



//////////// CPola //////////////

void CPola::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "NORMAL");
	else
		strcpy(dest, "INVERT");
}



//////////// CGuitarType //////////////

void CGuitarType::setValue(int value)
{
	if (value >= 0 && value <= 21)
		CVGData::setValue(value);
}


void CGuitarType::getString(char *dest)
{
	strcpy(dest, T_guitarType[getValue()]);
}


int CGuitarType::getRange()
{
	return 22;
}




//////////// CAmpType //////////////

void CAmpType::setValue(int value)
{
	if (value >= 0 && value <= 31)
		CVGData::setValue(value);
}


void CAmpType::getString(char *dest)
{
	strcpy(dest, T_ampType[getValue()]);
}


int CAmpType::getRange()
{
	return 32;
}




//////////// CGain //////////////

void CGain::setValue(int value)
{
	if (value >= 0 && value <= 2)
		CVGData::setValue(value);
}


void CGain::getString(char *dest)
{
	switch (getValue())
	{
		case 0:
			strcpy(dest, "LOW");
			break;

		case 1:
			strcpy(dest, "NORMAL");
			break;

		case 2:
			strcpy(dest, "HIGH");
			break;
	}
}


int CGain::getRange()
{
	return 3;
}




//////////// CSpeaker //////////////

void CSpeaker::setValue(int value)
{
	if (value >= 0 && value <= 17)
		CVGData::setValue(value);
}


void CSpeaker::getString(char *dest)
{
	strcpy(dest, T_speakerType[getValue()]);
}


int CSpeaker::getRange()
{
	return 18;
}




//////////// CMicset //////////////

void CMicset::setValue(int value)
{
	if (value >= 0 && value <= 10)
		CVGData::setValue(value);
}


void CMicset::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "CENTER");
	else
		sprintf(dest, "%d cm", getValue());
	
}


int CMicset::getRange()
{
	return 11;
}



//////////// CWahType //////////////

void CWahType::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "PEDAL WAH");
	else
		strcpy(dest, "AUTO WAH");
}


//////////// CAutoWahMode //////////////

void CAutoWahMode::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "LPF");
	else
		strcpy(dest, "BPF");
}




//////////// CPolarity //////////////

void CPolarity::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "DOWN");
	else
		strcpy(dest, "UP");
}



//////////// CRate //////////////

void CRate::setValue(int value)
{
	if (value >= 0 && value <= 113)
		CVGData::setValue(value);
}


void CRate::getString(char *dest)
{
	int value = getValue();

	if (value <= 100)
		sprintf(dest, "%d", value);
	else
		sprintf(dest, "%s*BPM", T_rate[value - 101]);
}


int CRate::getRange()
{
	return 114;
}




//////////// CModType //////////////

void CModType::setValue(int value)
{
	if (value >= 0 && value <= 11)
		CVGData::setValue(value);
}


void CModType::getString(char *dest)
{
	strcpy(dest, T_modType[getValue()]);
}


int CModType::getRange()
{
	return 12;
}



//////////// CHr1Harmony //////////////

void CHr1Harmony::setValue(int value)
{
	if (value >= 0 && value <= 29)
		CVGData::setValue(value);
}


void CHr1Harmony::getString(char *dest)
{
	strcpy(dest, T_variGtHarm_hrHarm[getValue()]);
}


int CHr1Harmony::getRange()
{
	return 30;
}



//////////// CPSPredly //////////////

void CPSPredly::setValue(int value)
{
	if (value >= 0 && value <= 313)
		CVGData::setValue(value);
}


void CPSPredly::getString(char *dest)
{
	int value = getValue();

	if (value <= 300)
		sprintf(dest, "%d ms", value);
	else
		strcpy(dest, T_delay[value - 301]);
}


int CPSPredly::getRange()
{
	return 314;
}



//////////// CDlyTime //////////////

void CDlyTime::setValue(int value)
{
	if (value >= 0 && value <= 1813)
		CVGData::setValue(value);
}


void CDlyTime::getString(char *dest)
{
	int value = getValue();

	if (value <= 1800)
		sprintf(dest, "%d ms", value);
	else
		strcpy(dest, T_delay[value - 1801]);
}


int CDlyTime::getRange()
{
	return 1814;
}


//////////// CPSMode //////////////

void CPSMode::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "POLY");
	else
		strcpy(dest, "MONO");
}



//////////// CStage //////////////

void CStage::setValue(int value)
{
	if (value >= 0 && value <= 3)
		CVGData::setValue(value);
}


void CStage::getString(char *dest)
{
	switch (getValue())
	{
		case 0:
			strcpy(dest, "4STAGE");
			break;

		case 1:
			strcpy(dest, "8STAGE");
			break;

		case 2:
			strcpy(dest, "12STAGE");
			break;

		case 3:
			strcpy(dest, "BI-PHASE");
			break;
	}
}


int CStage::getRange()
{
	return 4;
}


//////////// CStep //////////////

void CStep::setValue(int value)
{
	if (value >= 0 && value <= 114)
		CVGData::setValue(value);
}


void CStep::getString(char *dest)
{
	int value = getValue();

	if (value == 0)
		strcpy(dest, "OFF");
	else
	{
		if (value > 0 && value <= 101)
			sprintf(dest, "%d", value - 1);
		else
			sprintf(dest, "%s*BPM", T_rate[value - 102]);
	}
}


int CStep::getRange()
{
	return 115;
}



//////////// CXoverF //////////////

void CXoverF::setValue(int value)
{
	if (value >= 0 && value <= 16)
		CVGData::setValue(value);
}


void CXoverF::getString(char *dest)
{
	strcpy(dest, T_xOverF[getValue()]);
}


int CXoverF::getRange()
{
	return 17;
}




//////////// CCHPredly //////////////

void CCHPredly::setValue(int value)
{
	if (value >= 0 && value <= 80)
		CVGData::setValue(value);
}


void CCHPredly::getString(char *dest)
{
	sprintf(dest, "%.1f msec", (float) (getValue() * 0.5));
}


int CCHPredly::getRange()
{
	return 81;
}



//////////// CChorusMode //////////////

void CChorusMode::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "MONO");
	else
		strcpy(dest, "STEREO");
}



//////////// CReverbMode //////////////

void CReverbMode::setValue(int value)
{
	if (value >= 0 && value <= 4)
		CVGData::setValue(value);
}


void CReverbMode::getString(char *dest)
{
	switch(getValue())
	{
		case 0:
			strcpy(dest, "ROOM1");
			break;

		case 1:
			strcpy(dest, "ROOM2");
			break;

		case 2:
			strcpy(dest, "HALL1");
			break;

		case 3:
			strcpy(dest, "HALL2");
			break;

		case 4:
			strcpy(dest, "PLATE");
			break;
	}
	
}


int CReverbMode::getRange()
{
	return 5;
}




//////////// CReverbTime //////////////

void CReverbTime::setValue(int value)
{
	if (value >= 1 && value <= 100)
		CVGData::setValue(value);
}


void CReverbTime::getString(char *dest)
{
	sprintf(dest, "%.1f sec",  (((float) getValue()) / 10));
}


int CReverbTime::getRange()
{
	return 100;
}


int CReverbTime::getFirstValue()
{
	return 1;
}


//////////// CRVBPreDly //////////////

void CRVBPreDly::setValue(int value)
{
	if (value >= 0 && value <= 100)
		CVGData::setValue(value);
}


void CRVBPreDly::getString(char *dest)
{
	sprintf(dest, "%d msec", getValue());
}


int CRVBPreDly::getRange()
{
	return 101;
}



//////////// CTapeTime //////////////

void CTapeTime::setValue(int value)
{
	if (value >= 0 && value <= 101)
		CVGData::setValue(value);
}


void CTapeTime::getString(char *dest)
{
	int value = getValue();

	if (value == 0)
		strcpy(dest, "OFF");
	else
		sprintf(dest, "%d%%", value - 1);
}


int CTapeTime::getRange()
{
	return 102;
}



//////////// CAssignTarget //////////////

void CAssignTarget::setValue(int value)
{
	if (value >= 0 && value <= 246)
		CVGData::setValue(value);
}


void CAssignTarget::getString(char *dest)
{
	strcpy(dest, T_target[getValue()]);
}


int CAssignTarget::getRange()
{
	return 247;
}


//////////// CAssignMinMax //////////////

CAssignMinMax::CAssignMinMax()
{
	vgData = NULL;
	m_mul = 1;
}


CAssignMinMax::~CAssignMinMax()
{
	if (vgData)
		delete vgData;
}


void CAssignMinMax::setValue(int value)
{
	if (vgData)
	{
		vgData->setValue(value);
		CVGDataLong::setValue(vgData->getValue() * m_mul);
	}
}


int CAssignMinMax::getValue()
{
	return (m_data / m_mul);
}


void CAssignMinMax::getString(char *dest)
{
	if (vgData)
		vgData->getString(dest);
}


int CAssignMinMax::getFirstValue()
{
	if (vgData)
		return vgData->getFirstValue();
	else
		return 0;
}


int CAssignMinMax::getRange()
{
	if (vgData)
		return vgData->getRange();
	else
		return 1;
}


void CAssignMinMax::setVgDataType(int type)
{
	m_mul = 1;

	if (vgData)
	{
		delete vgData;
		vgData = NULL;
	}

	switch (type)
	{
			// COSM GT     ON/OFF
			case 0:
				 vgData = new COnOff;
				break;
			// F-BASS       COLOR
			case 1:
				vgData = new CNum0To100;
				break;
			// BODY        ATTACK
			case 2:
				vgData = new CNum0To100;
				break;
			//	BODY          BODY
			case 3:
				vgData = new CNum0To100;
				break;
			//	BODY       LOW CUT
			case 4:
				vgData = new CLowCut2;
				break;
			//	BODY         LEVEL
			case 5:
				vgData = new CNum0To100;
				break;
			//	COSM EQ     ON/OFF
			case 6:
				vgData = new COnOff;
				break;
			//	COSM EQ      LEVEL
			case 7:
				vgData = new CEqValue;
				break;
			//	COSM EQ    L-MID G
			case 8:
				vgData = new CEqValue;
				break;
			//	COSM EQ      LOW G
			case 9:
				vgData = new CEqValue;
				break;
			//	COSM EQ     HIGH G
			case 10:
				vgData = new CEqValue;
				break;
			//	COSM EQ    H-MID G
			case 11:
				vgData = new CEqValue;
				break;
			//	PICKUP      PICKUP
			case 12:
				vgData = new CPickupPickup;
				break;
			//	PICKUP        TONE
			case 13:
				vgData = new CNumN50To50;
				break;
			//	PICKUP       LEVEL
			case 14:
				vgData = new CNum0To100;
				break;
			//	PT SHIFT    ON/OFF
			case 15:
				vgData = new COnOff;
				break;
			//	PT SHIFT    SHIFT1 to PT SHIFT    SHIFT6
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
				vgData = new CShiftString;
				break;
			//	PT SHIFT     FINE1 to PT SHIFT     FINE6
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:
				vgData = new CNumN50To50;
				break;
			//	PT SHIFT  E.LEVEL1 to PT SHIFT  E.LEVEL6
			case 28:
			case 29:
			case 30:
			case 31:
			case 32:
			case 33:
				vgData = new CNum0To100;
				break;
			//	PT SHIFT  D.LEVEL1 to PT SHIFT  D.LEVEL6
			case 34:
			case 35:
			case 36:
			case 37:
			case 38:
			case 39:
				vgData = new CNum0To100;
				break;
			//	PT SHIFT    HARMO1 to PT SHIFT    HARMO6
			case 40:
			case 41:
			case 42:
			case 43:
			case 44:
			case 45:
				vgData = new CVariGtHarm;
				break;
			// TUNE        ON/OFF
			case 46:
				vgData = new COnOff;
				break;
			// TUNE     TUNE TYPE
			case 47:
				vgData = new CTuneType;
				break;
			// TUNE        SHIFT1 to TUNE        SHIFT6
			case 48:
			case 49:
			case 50:
			case 51:
			case 52:
			case 53:
				vgData = new CNumN24To24;
				break;
			// DETUNE      ON/OFF
			case 54:
				vgData = new COnOff;
				break;
			// DETUNE      DETUNE
			case 55:
				vgData = new CNum0To100;
				break;
			// COSM PAN  STRING-1 to COSM PAN  STRING-6
			case 56:
			case 57:
			case 58:
			case 59:
			case 60:
			case 61:
				vgData = new CPanBalance;
				break;
			// PD SHIFT    ON/OFF
			case 62:
				vgData = new COnOff;
				break;
			// PD SHIFT     PITCH
			case 63:
				vgData = new CPitch;
				m_mul = 100;
				break;
			// PD SHIFT  STRING-1 to PD SHIFT  STRING-6
			case 64:
			case 65:
			case 66:
			case 67:
			case 68:
			case 69:
				vgData = new COnOff;
				break;
			// DIST        ON/OFF
			case 70:
				vgData = new COnOff;
				break;
			// DIST         DRIVE
			case 71:
				vgData = new CNum0To100;
				break;
			// DIST         LEVEL
			case 72:
				vgData = new CNum0To100;
				break;
			// DIST     POLY RATE
			case 73:
				vgData = new CNum0To100;
				break;
			// DIST       DRV BAL
			case 74:
				vgData = new CNum0To100;
				break;
			// COSM COMP   ON/OFF
			case 75:
				vgData = new COnOff;
				break;
			// COSM COMP  SUSTAIN
			case 76:
				vgData = new CNum0To100;
				break;
			// COSM COMP     TONE
			case 77:
				vgData = new CNumN50To50;
				break;
			// COSM COMP    LEVEL
			case 78:
				vgData = new CNum0To100;
				break;
			// COSM COMPTHRESHOLD
			case 79:
				vgData = new CNum0To100;
				break;
			// OCTAVE      ON/OFF
			case 80:
				vgData = new COnOff;
				break;
			// OCTAVE      -1OCT1 to OCTAVE      -1OCT6
			case 81:
			case 82:
			case 83:
			case 84:
			case 85:
			case 86:
				vgData = new CNum0To100;
				break;
			// OCTAVE      -2OCT2 to OCTAVE      -2OCT6
			case 87:
			case 88:
			case 89:
			case 90:
			case 91:
			case 92:
				vgData = new CNum0To100;
				break;
			// OCTAVE        DIR1 to OCTAVE        DIR6
			case 93:
			case 94:
			case 95:
			case 96:
			case 97:
			case 98:
				vgData = new CNum0To100;
				break;
			// SG          ON/OFF
			case 99:
				vgData = new COnOff;
				break;
			// MIXER      BALANCE
			case 100:
				vgData = new CMixerBalance;
				break;
			// MIXER        LEVEL
			case 101:
				vgData = new CNum0To100;
				break;
			// FILTER      CUTOFF
			case 102:
				vgData = new CNum0To100;
				break;
			// FILTER       DECAY
			case 103:
				vgData = new CNum0To100;
				break;
			// ATTACK      LENGTH
			case 104:
				vgData = new CNum0To100;
				break;
			// ATTACK    MOD-TUNE
			case 105:
				vgData = new CNum0To100;
				break;
			// ATTACK     MOD-DEP
			case 106:
				vgData = new CNum0To100;
				break;
			// ATTACK       LEVEL
			case 107:
				vgData = new CNum0To100;
				break;

			case 108:	// ORGAN       FEET-4
			case 109:	// ORGAN       FEET-8
			case 110:	// ORGAN      FEET-16
				vgData = new CNum0To100;
				break;
			case 111:	// P-BEND    P-BEND Q
				vgData = new CNum0To100;
				break;
			case 112:	// GLIDE     GLD-SENS
				vgData = new CNum0To100;
				break;
			case 113:	// COSM MOD     DEPTH
				vgData = new CNum0To100;
				break;
			case 114:	// COSM MOD      RATE
				vgData = new CNum0To100;
				break;
			case 115:	// COSM AMP    ON/OFF
				vgData = new COnOff;
				break;
			case 116:	// COSM AMP    VOLUME
				vgData = new CNum0To100;
				break;
			case 117:	// COSM AMP  PRESENCE
				vgData = new CNum0To100;
				break;
			case 118:	// COSM AMP  HIGH CUT
				vgData = new CNum0To100;
				break;
			case 119:	// COSM AMP    MASTER
				vgData = new CNum0To100;
				break;
			case 120:	// COSM AMP      BASS
				vgData = new CNum0To100;
				break;
			case 121:	// COSM AMP    MIDDLE
				vgData = new CNum0To100;
				break;
			case 122:	// COSM AMP    TREBLE
				vgData = new CNum0To100;
				break;
			case 123:	// COSM AMP      GAIN
				vgData = new CGain;
				break;
			case 124:	// COSM AMP    BRIGHT
				vgData = new COnOff;
				break;
			case 125:	// FX:COMP     ON/OFF
				vgData = new COnOff;
				break;
			case 126:	// FX:COMP    SUSTAIN
				vgData = new CNum0To100;
				break;
			case 127:	// FX:COMP       TONE
				vgData = new CNumN50To50;
				break;
			case 128:	// FX:COMP      LEVEL
				vgData = new CNum0To100;
				break;
			case 129:	// FX:LM    THRESHOLD
				vgData = new CNum0To100;
				break;
			case 130:	// FX:LM         TONE
				vgData = new CNumN50To50;
				break;
			case 131:	// FX:LM        LEVEL
				vgData = new CNum0To100;
				break;
			case 132:	// FX:WAH      ON/OFF
				vgData = new COnOff;
				break;
			case 133:	// FX:PD WAH     FREQ
				vgData = new CNum0To100;
				break;
			case 134:	// FX:PD WAH    LEVEL
				vgData = new CNum0To100;
				break;
			case 135:	// FX:AT WAH     FREQ
				vgData = new CNum0To100;
				break;
			case 136:	// FX:AT WAH     PEAK
				vgData = new CNum0To100;
				break;
			case 137:	// FX:AT WAH     RATE
				vgData = new CRate;
				break;
			case 138:	// FX:AT WAH    DEPTH
				vgData = new CNum0To100;
				break;
			case 139:	// FX:AT WAH    LEVEL
				vgData = new CNum0To100;
				break;
			case 140:	// FX:EQ       ON/OFF
				vgData = new COnOff;
				break;
			case 141:	// FX:EQ        LEVEL
				vgData = new CEqValue;
				break;
			case 142:	// FX:EQ      L-MID G
				vgData = new CEqValue;
				break;
			case 143:	// FX:EQ        LOW G
				vgData = new CEqValue;
				break;
			case 144:	// FX:EQ       HIGH G
				vgData = new CEqValue;
				break;
			case 145:	// FX:EQ      H-MID G
				vgData = new CEqValue;
				break;
			case 146:	// FX:MOD      ON/OFF
				vgData = new COnOff;
				break;
			case 147:	// FX:HARMO  1:ON/OFF
				vgData = new COnOff;
				break;
			case 148:	// FX:HARMO 1:HARMONY
				vgData = new CHr1Harmony;
				break;
			case 149:	// FX:HARMO     1:PAN
				vgData = new CPanBalanceST;
				break;
			case 150:	// FX:HARMO   1:LEVEL
				vgData = new CNum0To100;
				break;
			case 151:	// FX:HARMO   DIR LEV
				vgData = new CNum0To100;
				break;
			case 152:	// FX:HARMO  2:ON/OFF
				vgData = new COnOff;
				break;
			case 153:	// FX:HARMO 2:HARMONY
				vgData = new CHr1Harmony;
				break;
			case 154:	// FX:HARMO     2:PAN
				vgData = new CPanBalanceST;
				break;
			case 155:	// FX:HARMO   2:LEVEL
				vgData = new CNum0To100;
				break;
			case 156:	// FX:P.SFT  1:ON/OFF
				vgData = new COnOff;
				break;
			case 157:	// FX:P.SFT   1:SHIFT
				vgData = new CNumN24To24;
				break;
			case 158:	// FX:P.SFT    1:FINE
				vgData = new CNumN50To50;
				break;
			case 159:	// FX:P.SFT  1:F.BACK
				vgData = new CNum0To100;
				break;
			case 160:	// FX:P.SFT     1:PAN
				vgData = new CPanBalanceST;
				break;
			case 161:	// FX:P.SFT   1:LEVEL
				vgData = new CNum0To100;
				break;
			case 162:	// FX:P.SFT DIR LEVEL
				vgData = new CNum0To100;
				break;
			case 163:	// FX:P.SFT  2:ON/OFF
				vgData = new COnOff;
				break;
			case 164:	// FX:P.SFT   2:SHIFT
				vgData = new CNumN24To24;
				break;
			case 165:	// FX:P.SFT    2:FINE
				vgData = new CNumN50To50;
				break;
			case 166:	// FX:P.SFT     2:PAN
				vgData = new CPanBalanceST;
				break;
			case 167:	// FX:P.SFT   2:LEVEL
				vgData = new CNum0To100;
				break;
			case 168:	// FX:FL         RATE
				vgData = new CRate;
				break;
			case 169:	// FX:FL        DEPTH
				vgData = new CNum0To100;
				break;
			case 170:	// FX:FL       MANUAL
				vgData = new CNum0To100;
				break;
			case 171:	// FX:FL    RESONANCE
				vgData = new CNum0To100;
				break;
			case 172:	// FX:FL    LEVEL
				vgData = new CNum0To100;
				break;
			case 173:	// FX:PH         RATE
				vgData = new CRate;
				break;
			case 174:	// FX:PH        DEPTH
				vgData = new CNum0To100;
				break;
			case 175:	// FX:PH       MANUAL
				vgData = new CNum0To100;
				break;
			case 176:	// FX:PH    RESONANCE
				vgData = new CNum0To100;
				break;
			case 177:	// FX:PH        LEVEL
				vgData = new CNum0To100;
				break;
			case 178:	// FX:PH         STEP
				vgData = new CStage;
				break;
			case 179:	// FX:SUB EQ    LEVEL
			case 180:	// FX:SUB EQ  L-MID G
			case 181:	// FX:SUB EQ    LOW G
			case 182:	// FX:SUB EQ   HIGH G
			case 183:	// FX:SUB EQ  H-MID G
				vgData = new CEqValue;
				break;
			case 184:	// FX:2x2CE    L-RATE
				vgData = new CRate;
				break;
			case 185:	// FX:2x2CE   L-DEPTH
				vgData = new CNum0To100;
				break;
			case 186:	// FX:2x2CE   L-LEVEL
				vgData = new CNum0To100;
				break;
			case 187:	// FX:2x2CE    H-RATE
				vgData = new CRate;
				break;
			case 188:	// FX:2x2CE   H-DEPTH
				vgData = new CNum0To100;
				break;
			case 189:	// FX:2x2CE   H-LEVEL
				vgData = new CNum0To100;;
				break;
			case 190:	// FX:TR         RATE
				vgData = new CRate;
				break;
			case 191:	// FX:TR        DEPTH
				vgData = new CNum0To100;;
				break;
			case 192:	// FX:PAN        RATE
				vgData = new CRate;
				break;
			case 193:	// FX:PAN       DEPTH
				vgData = new CNum0To100;
				break;
			case 194:	// FX:PD SFT    PITCH
				vgData = new CPitch;
				break;
			case 195:	// FX:VB      TRIGGER
				vgData = new COnOff;
				break;
			case 196:	// FX:VB         RATE
				vgData = new CRate;
				break;
			case 197:	// FX:VB        DEPTH
				vgData = new CNum0To100;
				break;
			case 198:	// FX:DELAY    ON/OFF
				vgData = new COnOff;
				break;
			case 199:	// FX:DELAY  DLY TIME
				vgData = new CDlyTime;
				break;
			case 200:	// FX:DELAY  FEEDBACK
				vgData = new CNum0To100;
				break;
			case 201:	// FX:DELAY DLY LEVEL
				vgData = new CNum0To120;
				break;
			case 202:	// FX:CHORUS   ON/OFF
				vgData = new COnOff;
				break;
			case 203:	// FX:CHORUS     RATE
				vgData = new CRate;
				break;
			case 204:	// FX:CHORUS    DEPTH
				vgData = new CNum0To100;
				break;
			case 205:	// FX:CHORUS CE LEVEL
				vgData = new CNum0To100;
				break;
			case 206:	// FX:REVERB   ON/OFF
				vgData = new COnOff;
				break;
			case 207:	// FX:REVERB REV TIME
				vgData = new CReverbTime;
				break;
			case 208:	// FX:REVERB  REV LEV
				vgData = new CNum0To100;
				break;
			case 209:	// FX:NS       ON/OFF
				vgData = new COnOff;
				break;
			case 210:	// FX:FV        LEVEL
				vgData = new CNum0To100;
				break;
			case 211:	// MASTER       LEVEL
				vgData = new CLevel;
				break;
			case 212:	// MASTER    BPM(TAP)
				vgData = new CBPM;
				break;
			case 213:	// MASTER         KEY
				vgData = new CKey;
				break;
			case 214:	// TUNER       ON/OFF
				vgData = new COnOff;
				break;
			case 215:	//NYLON2      ATTACK
				vgData = new CNum0To100;
				break;
			case 216:	//NYLON2        BODY
				vgData = new CNum0To100;
				break;
			case 217:	//NYLON2        TONE
				vgData = new CNumN50To50;
				break;
			case 218:		//NYLON2       LEVEL
				vgData = new CNum0To100;
				break;
			case 219:		//SITAR       PICKUP
				vgData = new CSPickupPosition;
				break;
			case 220:		//SITAR         BODY
				vgData = new CNum0To100;
				break;
			case 221:		//SITAR         SENS
				vgData = new CNum0To100;
				break;
			case 222:		//SITAR         TONE
				vgData = new CNumN50To50;
				break;
			case 223:		//SITAR        LEVEL
				vgData = new CNum0To100;
				break;
			case 224:		//SITAR        COLOR
				vgData = new CNum0To100;
				break;
			case 225:		//SITAR        DECAY
				vgData = new CNum0To100;
				break;
			case 226:		//SITAR         BUZZ
				vgData = new CNum0To100;
				break;
			case 227:		//SITAR      ATK LEV
				vgData = new CNum0To100;
				break;
			case 228:		//WAVE         SHAPE
				vgData = new CShape;
				break;
			case 229:		//WAVE          SENS
				vgData = new CNum0To100;
				break;
			case 230:		//WAVE        ATTACK
				vgData = new CNum0To100;
				break;
			case 231:		//WAVE         DECAY
				vgData = new CNum0To100;
				break;
			case 232:		//WAVE         LEVEL
				vgData = new CNum0To100;
				break;
			case 233:		//WAVE        CUTOFF
				vgData = new CNum0To100;
				break;
			case 234:		//WAVE          RESO
				vgData = new CNum0To100;
				break;
			case 235:		//WAVE    FLT ATTACK
				vgData = new CNum0To100;
				break;
			case 236:		//WAVE    FLT DECAY
				vgData = new CNum0To100;
				break;
			case 237:		//WAVE     FLT DEPTH
				vgData = new CNumN50To50;
				break;
			case 238:		//FX:DEFRET     TONE
				vgData = new CNumN50To50;
				break;
			case 239:		//FX:DEFRET     SENS
				vgData = new CNum0To100;
				break;
			case 240:		//FX:DEFRET   ATTACK
				vgData = new CNum0To100;
				break;
			case 241:		//FX:DEFRET    DEPTH
				vgData = new CNum0To100;
				break;
			case 242:		//FX:DEFRET     RESO
				vgData = new CNum0To100;
				break;
			case 243:		//FX:DEFRET    E.LEV
				vgData = new CNum0To100;
				break;
			case 244:		//FX:DEFRET    D.LEV
				vgData = new CNum0To100;
				break;
			case 245:		//FX:UNI-V      RATE
				vgData = new CRate;
				break;
			case 246:		//FX:UNI-V     DEPTH
				vgData = new CNum0To100;
				break;
			case 247:		//FX:UNI-V     LEVEL
				vgData = new CNum0To100;
				break;
	}

	if (vgData)
	{
		vgData->m_needSaving = FALSE;

		if (getValue() < vgData->getFirstValue() || getValue() > vgData->getRange())
			setValue(vgData->getFirstValue());
		else
			vgData->setValue(getValue());

		vgData->m_needSaving = TRUE;
	}
}

//////////// CAssignSource //////////////

void CAssignSource::setValue(int value)
{
	if (value >= 0 && value <= 69)
		CVGData::setValue(value);
}


void CAssignSource::getString(char *dest)
{
	int value = getValue();

	if (value <= 6)
		strcpy(dest, T_source[getValue()]);
	else if (value > 6 && value <= 37)
		sprintf(dest, "MIDI #CC%d", getValue() - 6);
	else
		sprintf(dest, "MIDI #CC%d", getValue() + 26);
}


int CAssignSource::getRange()
{
	return 70;
}




//////////// CAssignMode //////////////

CAssignMode::CAssignMode()
{
	m_type = 0;
}


void CAssignMode::getString(char *dest)
{
	if (getValue() == 0)
	{
		if (m_type)
			strcpy(dest, "NORMAL");
		else
			strcpy(dest, "DEC/INC");
	}
	else
		strcpy(dest, "TOGGLE");
}


void CAssignMode::setType(char type)
{
	m_type = type;
}


//////////// CLevel //////////////

void CLevel::setValue(int value)
{
	if (value >= 0 && value <= 100)
		CVGData::setValue(value);
}


void CLevel::getString(char *dest)
{
	sprintf(dest, "%d", getValue() * 2);
}


int CLevel::getRange()
{
	return 101;
}

CShiftString::CShiftString()
{
	stringNum = 0;
}

void CShiftString::getString(char *dest)
{
	char *tab[] = {"C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B", 
				  "C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B",
				  "C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B",
				  "C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B",
				  "C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B"};
	char pos = 0;

	switch (stringNum)
	{
		// High E
		case 0:
			pos = 28;
			break;

		// B
		case 1:
			pos = 35;
			break;

		// G
		case 2:
			pos = 31;
			break;

		// D
		case 3:
			pos = 26;
			break;

		// A
		case 4:
			pos = 33;
			break;

		// Low E
		case 5:
			pos = 28;
			break;

		default:
			pos = 0;
	}

	if (getValue() == 24)
		sprintf(dest, "%d\n%s", getValue() - 24, tab[pos + getValue() - 24]);
	else
		sprintf(dest, "%+d\n%s", getValue() - 24, tab[pos + getValue() - 24]);
}


void CShiftString::setStringNum(char stringNumParam)
{
	stringNum = stringNumParam;
}



//////////// CVG88_Display //////////////

void CVG88_Display::setValue(int value)
{
	if (value >= 1 && value <= 16)
		CVGDataShort::setValue(value);
}


int CVG88_Display::getRange()
{
	return 16;
}


int CVG88_Display::getFirstValue()
{
	return 1;
}

//////////// CVG88_DownS1S2 //////////////

void CVG88_DownS1S2::setValue(int value)
{
	if (value >= 0 && value <= 5)
		CVGDataShort::setValue(value);
}


int CVG88_DownS1S2::getRange()
{
	return 6;
}

void CVG88_DownS1S2::getString(char *dest)
{
	strcpy(dest, T_downS1S2[getValue()]);
}




//////////// CVG88_SynthVol //////////////

void CVG88_SynthVol::setValue(int value)
{
	if (value >= 0 && value <= 3)
		CVGDataShort::setValue(value);
}


int CVG88_SynthVol::getRange()
{
	return 4;
}

void CVG88_SynthVol::getString(char *dest)
{
	strcpy(dest, T_synthVol[getValue()]);
}



//////////// CVG88_GlobalVol //////////////

void CVG88_GlobalVol::setValue(int value)
{
	if (value >= 0 && value <= 40)
		CVGData::setValue(value);
}

void CVG88_GlobalVol::getString(char *dest)
{
	if (getValue() == 20)
		sprintf(dest, "%d dB", getValue() - 20);
	else
		sprintf(dest, "%+d dB", getValue() - 20);
}

int CVG88_GlobalVol::getRange()
{
	return 41;
}



//////////// CVG88_GlobalRev //////////////

void CVG88_GlobalRev::setValue(int value)
{
	if (value >= 0 && value <= 100)
		CVGData::setValue(value);
}

void CVG88_GlobalRev::getString(char *dest)
{
	sprintf(dest, "%d%%", getValue() * 2);
}

int CVG88_GlobalRev::getRange()
{
	return 101;
}



//////////// CPitchTuner //////////////

void CPitchTuner::setValue(int value)
{
	if (value >= 0 && value <= 10)
		CVGData::setValue(value);
}

void CPitchTuner::getString(char *dest)
{
	sprintf(dest, "%dHz", getValue() + 435);
}

int CPitchTuner::getRange()
{
	return 11;
}


//////////// CVG88_OutputSelect //////////////

void CVG88_OutputSelect::setValue(int value)
{
	if (value >= 0 && value <= 4)
		CVGData::setValue(value);
}

void CVG88_OutputSelect::getString(char *dest)
{
	strcpy(dest, T_outputSelect[getValue()]);
}

int CVG88_OutputSelect::getRange()
{
	return 5;
}


//////////// CVG88_DriverSetting //////////////

void CVG88_DriverSetting::setValue(int value)
{
	if (value >= 0 && value <= 4)
		CVGData::setValue(value);
}

void CVG88_DriverSetting::getString(char *dest)
{
	sprintf(dest, "%c", getValue() + 'A');
}

int CVG88_DriverSetting::getRange()
{
	return 5;
}



//////////// CVG88_DriverType //////////////

void CVG88_DriverType::setValue(int value)
{
	if (value >= 0 && value <= 2)
		CVGData::setValue(value);
}

void CVG88_DriverType::getString(char *dest)
{
	strcpy(dest, T_driverType[getValue()]);
}

int CVG88_DriverType::getRange()
{
	return 3;
}



//////////// CVG88_DriverDirection //////////////

void CVG88_DriverDirection::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "NORMAL");
	else
		strcpy(dest, "REVERSE");
}


//////////// CVG88_DriverScale //////////////

void CVG88_DriverScale::setValue(int value)
{
	if (value >= 0 && value <= 42)
		CVGData::setValue(value);
}

void CVG88_DriverScale::getString(char *dest)
{
	if (getValue() == 41)
		strcpy(dest, "ST");
	else if (getValue() == 42)
		strcpy(dest, "LP");
	else
		sprintf(dest, "%dmm", getValue() + 620);
}

int CVG88_DriverScale::getRange()
{
	return 43;
}




//////////// CVG88_DriverGtPuPhase //////////////

void CVG88_DriverGtPuPhase::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "NORMAL");
	else
		strcpy(dest, "INVERSE");
}





//////////// CVG88_GkConnect //////////////

void CVG88_GkConnect::setValue(int value)
{
	if (value >= 0 && value <= 2)
		CVGData::setValue(value);
}

void CVG88_GkConnect::getString(char *dest)
{
	switch (getValue())
	{
	case 0:
		strcpy(dest, "AUTO");
		break;

	case 1:
		strcpy(dest, "ON");
		break;

	case 2:
		strcpy(dest, "OFF");
		break;
	}

	
}

int CVG88_GkConnect::getRange()
{
	return 3;
}



//////////// CVG88_DriverPuBridge //////////////

void CVG88_DriverPuBridge::setValue(int value)
{
	if (value >= 0 && value <= 20)
		CVGData::setValue(value);
}

void CVG88_DriverPuBridge::getString(char *dest)
{
	sprintf(dest, "%dmm", getValue() + 10);
}

int CVG88_DriverPuBridge::getRange()
{
	return 21;
}


//////////// CVG88_DriverSettingName //////////////

void CVG88_DriverSettingName::setString(char *name)
{
	int i, j;
	
	for (i = 0; i < 8; i++)
	{
		if (name[i] == 0)
		{
			for (j = i; j < 8; j++)
				car[j].setValue(' ');

			return;
		}
		else
			car[i].setValue(name[i]);
	}
}


void CVG88_DriverSettingName::getString(char *name)
{
	int i;
	char value;
	
	for (i = 0; i < 8; i++)
	{
		value = car[i].getValue();

		if (value == 0 || value > 127)
			name[i] = ' ';
		else
			name[i] = value;
	}

	for (i = 7; i >= 0; i--)
	{
		if (name[i] != ' ')
		{
			name[i + 1] = 0;

			return;
		}
	}

	name[0] = 0;
}


int CVG88_DriverSettingName::setVGData(char **buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
		count += car[i].setVGData(buffer);

	return count;
}



int CVG88_DriverSettingName::getVGData(char **buffer)
{
	int i;
	int count = 0;

	for (i = 0; i < 8; i++)
		count += car[i].getVGData(buffer);

	return count;
}




//////////// CVG88_BankSwMode //////////////

void CVG88_BankSwMode::setValue(int value)
{
	if (value >= 0 && value <= 2)
		CVGData::setValue(value);
}

void CVG88_BankSwMode::getString(char *dest)
{
	strcpy(dest, T_bankSwMode[getValue()]);
}

int CVG88_BankSwMode::getRange()
{
	return 3;
}


//////////// CVG88_SubCtl //////////////

void CVG88_SubCtl::setValue(int value)
{
	if (value >= 0 && value <= 4)
		CVGData::setValue(value);
}

void CVG88_SubCtl::getString(char *dest)
{
	strcpy(dest, T_subCtl[getValue()]);
}

int CVG88_SubCtl::getRange()
{
	return 5;
}


//////////// CVG88_Dial //////////////

void CVG88_Dial::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "P.NUMBER && VALUE");
	else
		strcpy(dest, "VALUE ONLY");
}


//////////// CWahModel //////////////

void CWahModel::setValue(int value)
{
	if (value >= 0 && value <= 5)
		CVGData::setValue(value);	
}


void CWahModel::getString(char *dest)
{
	strcpy(dest, T_wahModel[getValue()]);
}


int CWahModel::getRange()
{
	return 6;
}


//////////// CShape //////////////

void CShape::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "SAW");
	else
		strcpy(dest, "SQUARE");
}


//////////// CFtype //////////////

void CFtype::getString(char *dest)
{
	if (getValue() == 0)
		strcpy(dest, "-12dB");
	else
		strcpy(dest, "-24dB");
}