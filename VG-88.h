#if !defined(AFX_VG88_H__023EDBDF_837E_400B_BF3B_CF6432A6FCAB__INCLUDED_)
#define AFX_VG88_H__023EDBDF_837E_400B_BF3B_CF6432A6FCAB__INCLUDED_

#include <Afxcoll.h>
#include <Mmsystem.h>
#include "vg88Common.h"

#define USERPATCH	0
#define PRESETPATCH	1
#define VG88_PATCHSIZE	776

class CPickup
{
public:
	CPickupPosition		rearPickupPosition;
	CPickupAngle		rearPickupAngle;
	CPickupPosition		frontPickupPosition;
	CPickupAngle		frontPickupAngle;
	CPickupModel		model;
	CPickupPickup		pickup;
	CNumN50To50			tone;
	CNum0To100			level;
	CPickupPhase		phase;
	CPickupType			rearPickuType;
	CPickupType			frontPickuType;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CAPickup
{
public:
	CNumN50To50			tone;
	CNum0To100			level;
	CAPickupType		type;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CPitchShift
{
public:
	CPitchShiftMode		mode;
	CShiftString		shift[6];
	CNumN50To50			fine[6];
	CNum0To100			eLevel[6];
	CNum0To100			dLevel[6];
	CVariGtHarm			harmo[6];

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CBody
{
public:
	CNum0To100			attack;
	CNum0To100			body;
	CLowCut2			lowCut;
	CNum0To100			level;
	CBodyType			bodyType;
	CNum0To100			reso;
	CNumN50To50			size;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CNBody
{
public:
	CNum0To100			level;
	CNum0To10			bottom;
	CNum0To10			reso;
	CNumN50To50			size;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CNIIBody
{
public:
	CNum0To100			level;
	CNum0To100			attack;
	CNum0To100			body;
	CNumN50To50			tone;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};

class CTune
{
public:
	CTuneType			type;
	CShiftString		shift[6];

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CDetune
{
public:
	CNum0To100			detune;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



class CShift
{
public:
	CPitch				pitch;
	COnOff				string[6];

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CDist
{
public:
	CDistMode			mode;
	CNum0To100			drive;
	CHighCut			highCut;
	CNum0To100			level;
	CNum0To100			polyBal;
	CNum0To100			drvBal;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



class CIComp
{
public:
	CCompMode			mode;
	CNum0To100			sustain;
	CNum0To100			attack;
	CNumN50To50			tone;
	CNum0To100			level;
	CNum0To100			cmpBal;
	CNum0To100			threshold;
	CNum0To100			release;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class COctave
{
public:
	CNum0To100			Oct1[6];
	CNum0To100			Oct2[6];
	CNum0To100			dir[6];

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CSG
{
public:
	CNum0To100			riseTime;
	CNum0To100			sens;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CFilter
{
public:
	CNum0To100			cutOff;
	CNum0To100			reso;
	CNum0To100			touchS;
	CNum0To100			decay;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CPBend
{
public:
	CNum0To100			pBend;
	CNum0To100			pBendQ;
	
	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CGlide
{
public:
	CNum0To100			gldSens;
	CNum0To100			gldTime;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};




class CIMod
{
public:
	CNum0To100			depth;
	CNum0To100			rate;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



class CModC
{
public:
	CNum0To100			length;
	CNum0To100			modTune;
	CNum0To100			level;
	CNum0To100			modeDep;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



class CDrawBar
{
public:
	CNum0To100			feet4;
	CNum0To100			feet8;
	CNum0To100			feet16;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


//===== COSM =====

class CInstrument
{
public:
	virtual int getVGData(char **buffer) = 0;
	virtual int setVGData(char **buffer) = 0;
	virtual void setDefaultValues() = 0;
};


class CVariGuitar:public CInstrument
{
public:
	CPickup				pickup;
	CPitchShift			pitchShift;
	CBody				body;
	COnOff				ptShiftOnOff;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CAcoustic:public CInstrument
{
public:
	CAPickup			pickup;
	CBody				body;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CNylonStrings:public CInstrument
{
public:
	CNBody				body;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};

class CNylonII:public CInstrument
{
public:
	CNIIBody			body;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};

class COpenTune:public CInstrument
{
public:
	CPickup				pickup;
	CTune				tune;
	CBody				body;
	COnOff				openTuneOnOff;
	
	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CStrings12:public CInstrument
{
public:
	CPickup		pickup;
	CDetune		detune;
	CBody		body;
	COnOff		detuneOnOff;
	
	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CPdShift:public CInstrument
{
public:
	CPickup		pickup;
	CShift		pdShift;
	CBody		body;
	COnOff		detuneOnOff;
	
	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CPolyDist:public CInstrument
{
public:
	CPickup		pickup;
	CDist		dist;
	COnOff		distOnOff;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CPolyComp:public CInstrument
{
public:
	CPickup		pickup;
	CIComp		comp;
	COnOff		compOnOff;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CPolyOct:public CInstrument
{
public:

	CPickup		pickup;
	COctave		octave;
	COnOff		ocataveOnOff;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};



class CPolySG:public CInstrument
{
public:

	CPickup		pickup;
	CSG			sg;
	COnOff		sgOnOff;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};



class CBowed:public CInstrument
{
public:

	CFilter		filter;
	CPBend		pBend;
	CNum0To100	sustain;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CDual:public CInstrument
{
public:

	CFilter		filter;
	CGlide		gLide;
	CNum0To100	sustain;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CFilterBass:public CInstrument
{
public:

	CFilter		filter;
	CNum0To100	color;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CPipe:public CInstrument
{
public:

	CFilter		filter;
	CPBend		pBend;
	CNum0To100	sustain;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CSolo:public CInstrument
{
public:

	CFilter		filter;
	CNum0To100	color;
	CNum0To100	sustain;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CPWM:public CInstrument
{
public:

	CFilter		filter;
	CIMod		mod;
	CNum0To100	sustain;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CCrystal:public CInstrument
{
public:

	CModC		mod;
	CNum0To100	bodyLevel;
	CNum0To100	sustain;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};

class COrgan:public CInstrument
{
public:

	CDrawBar	drawBar;
	CNum0To100	sustain;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};

class CBrass:public CInstrument
{
public:

	CFilter		filter;
	CNum0To100	sustain;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};

class CSitar:public CInstrument
{
public:
	CNum0To100			body;
	CNum0To100			color;
	CNum0To100			decay;
	CNum0To100			buzz;
	CNum0To100			AttackLevel;
	CSPickupPosition	pickup;
	CNum0To100			sens;
	CNum0To100			level;
	CNumN50To50			tone;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CWave:public CInstrument
{
public:
	CShape		shape;
	CNum0To100	sens;
	CNum0To100	attack;
	CNum0To100	decay;
	CNum0To100	level;
	CNum0To100	cutoff;
	CNum0To100	reso;
	CFtype		ftype;
	CNum0To100	fattack;
	CNum0To100	fdecay;
	CNumN50To50	fdepth;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


//===== COSM EQ =====

class CEq
{
public:
	CEqValue	level;
	CEqValue	lMidG;		
	CEqValue	lowG;
	CEqValue	highG;
	CEqValue	hMidG;
	CEqMidF		lMidF;
	CEqMidQ		lMidQ;
	CEqMidF		hMidF;
	CEqMidQ		hMidQ;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== COSM Pan =====

class CCosmPan
{
public:
	CPanBalance	string[6];

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== COSM Mixer =====

class CCosmMixer
{
public:
	CMixerBalance	balance;
	CPola			puPola;
	CNum0To100		level;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== COSM GT =====

class CCosmGT
{
public:
	CGuitarType	guitarType;
	COnOff		guitarOnOff;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


//===== COSM Amp =====

class CCosmAmp
{
public:
	COnOff		ampOnOff;
	CAmpType	ampType;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


//===== Amp =====

class CAmp
{
public:
	CNum0To100		volume;
	CNum0To100		presenceHighCut;
	CNum0To100		master;
	CNum0To100		bass;
	CNum0To100		middle;
	CNum0To100		trebble;
	CGain			gain;
	COnOff			bright;
	CMAmpBalance	balance;
	CSpeaker		speaker;
	CMicset			micSet;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};




//===== CComp =====

#define COMP_COMP	 0
#define COMP_LIMITER 1

class CComp
{
public:
	virtual int getVGData(char **buffer) = 0;
	virtual int setVGData(char **buffer) = 0;
};

class CCompComp:public CComp
{
public:
	CNum0To100	sustain;
	CNum0To100	attack;
	CNumN50To50	tone;
	CNum0To100	level;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CCompLim:public CComp
{
public:
	CNum0To100	threshold;
	CNum0To100	release;
	CNumN50To50	tone;
	CNum0To100	level;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CCompE
{
public:
	CCompMode	compType;
	CComp		*comp;

	CCompE();
	~CCompE();

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== CWah =====

class CWah
{
public:
	virtual int getVGData(char **buffer) = 0;
	virtual int setVGData(char **buffer) = 0;
};


class CPedalWah:public CWah
{
public:
	CNum0To100	freq;
	CNum0To100	level;
	CWahModel	model;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CAutoWah: public CWah
{
public:
	CAutoWahMode	autoWahMode;
	CPolarity		polarity;
	CNum0To100		sens;
	CNum0To100		freq;
	CNum0To100		peak;
	CRate			rate;
	CNum0To100		depth;
	CNum0To100		level;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};

class CWahE
{
public:
	CWahType	wahType;
	CWah		*wah;

	CWahE();
	~CWahE();
	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


#define MOD_HARMONIST	0
#define MOD_PSHIFTER	1
#define MOD_FLANGER		2
#define MOD_PHASER		3
#define MOD_SUBEQ		4
#define MOD_2X2CHORUS	5
#define MOD_TREMOLO		6
#define MOD_PAN			7
#define MOD_PDSHIFT		8
#define MOD_VIBRATO		9
#define MOD_DEFRETTER	10
#define MOD_UNIV		11

//===== CMod =====

class CMod
{
public:
	virtual int getVGData(char **buffer) = 0;
	virtual int setVGData(char **buffer) = 0;
};


class CHarmonist:public CMod
{
public:
	COnOff			hr1OnOff;
	CHr1Harmony		hr1Harmony;
	CPanBalanceST	hr1Pan;
	CNum0To100		hr1Level;
	CNum0To100		dirLevel;
	CNumN24To24		hr1UserScale[12];
	COnOff			hr2OnOff;
	CHr1Harmony		hr2Harmony;
	CPanBalanceST	hr2Pan;
	CNum0To100		hr2Level;
	CNumN24To24		hr2UserScale[12];

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CPitchShifter:public CMod
{
public:
	CPSPredly	ps1PreDly;
	CPSPredly	ps2PreDly;
	COnOff		ps1OnOff;
	CPSMode		ps1Mode;
	CNumN24To24	ps1Shift;
	CNumN50To50	ps1Fine;
	CNum0To100	ps1Feedback;
	CPanBalanceST	ps1Pan;
	CNum0To100	ps1Level;
	CNum0To100	dirLevel;
	COnOff		ps2OnOff;
	CPSMode		ps2Mode;
	CNumN24To24	ps2Shift;
	CNumN50To50	ps2Fine;
	CPanBalanceST	ps2Pan;
	CNum0To100	ps2Level;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CFlanger:public CMod
{
public:	
	CRate			rate;
	CNum0To100		depth;
	CNum0To100		manual;
	CNum0To100		reso;
	CNum0To100		level;
	CNum0To100		separate;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CPhaser:public CMod
{
public:	
	CRate			rate;
	CNum0To100		depth;
	CNum0To100		manual;
	CNum0To100		reso;
	CNum0To100		level;
	CStage			stage;
	CStep			step;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CSubEq:public CMod
{
public:
	CEqValue	level;
	CEqValue	lMidG;		
	CEqValue	lowG;
	CEqValue	highG;
	CEqValue	hMidG;
	CEqMidF		lMidF;
	CEqMidQ		lMidQ;
	CEqMidF		hMidF;
	CEqMidQ		hMidQ;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};



class CChorus2x2:public CMod
{
public:	
	CXoverF			xOverf;
	CRate			lowRate;
	CNum0To100		lowDepth;
	CCHPredly		lowPreDly;
	CNum0To100		lowLevel;
	CRate			highRate;
	CNum0To100		highDepth;
	CCHPredly		highPreDly;
	CNum0To100		highLevel;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CTremolo:public CMod
{
public:	
	CNum0To100		wave;
	CRate			rate;
	CNum0To100		depth;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CUniV:public CMod
{
public:	
	CNum0To100		level;
	CRate			rate;
	CNum0To100		depth;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CDefretter:public CMod
{
public:	
	CNum0To100		sens;
	CNum0To100		attack;
	CNum0To100		depth;
	CNum0To100		reso;
	CNumN50To50		tone;
	CNum0To100		elevel;
	CNum0To100		dlevel;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};


class CPan:public CMod
{
public:	
	CNum0To100		wave;
	CRate			rate;
	CNum0To100		depth;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};



class CModPDShift:public CMod
{
public:	
	CPitch			pitch;
	CPSMode			mode;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};



class CVibrato:public CMod
{
public:	
	COnOff			trigger;
	CRate			rate;
	CNum0To100		depth;
	CNum0To100		riseTime;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
	void setDefaultValues();
};



class CModE
{
public:
	CModType		modeType;
	CMod			*mod;

	CModE();
	~CModE();
	int getVGData(char **buffer);
	int setVGData(char **buffer);
};




//===== CDelay =====

class CDelay
{
public:
	CDlyTime	dlyTime;
	CTapeTime	tapeTime;
	CNum0To100	feedback;
	CHighCut	highCut;
	CNum0To120	dlyLev;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== CChorus =====

class CChorus
{
public:
	CChorusMode		mode;
	CRate			rate;
	CNum0To100		depth;
	CCHPredly		preDly;
	CHighCut		highCut;
	CNum0To100		cLevel;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== CReverb =====

class CReverb
{
public:
	CReverbMode		reverbMode;
	CReverbTime		reverbTime;
	CLowCut			lowCut;
	CHighCut		highCut;
	CRVBPreDly		preDly;
	CNum0To100		revLev;
	CNum0To10		density;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== CNS =====

class CNS
{
public:
	CNum0To100	threshold;
	CNum0To100	release;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== CFV =====

class CFV
{
public:
	CNum0To100	level;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


//===== CAssign =====

class CAssign
{
public:
	CAssignTarget	assignTarget;
	CAssignMinMax	assignMin;
	CAssignMinMax	assignMax;
	CAssignSource	assignSource;
	CAssignMode		assignMode;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


//===== CExp =====

class CExp
{
public:
	CAssignTarget	expTarget;
	CAssignMinMax	expMin;
	CAssignMinMax	expMax;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== CCTL =====

class CCTL
{
public:
	CAssignTarget	ctlTarget;
	CAssignMinMax	ctlMin;
	CAssignMinMax	ctlMax;
	CAssignMode		ctlmode;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};




//===== CGKVol =====

class CGKVol
{
public:
	CAssignTarget	gkVolTarget;
	CAssignMinMax	gkVolMin;
	CAssignMinMax	gkVolMax;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== CGKS1S2 =====

class CGKS1S2
{
public:
	CAssignTarget	gkS1S2Target;
	CAssignMinMax	gkS1S2Min;
	CAssignMinMax	gkS1S2Max;
	CAssignMode		gkS1S2mode;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



//===== CAssignNC =====

class CAssignNC
{
public:
	CNum0To126	assignActiveRangeLo[8];
	CNum1To127	assignActiveRangeHi[8];
	COnOff		expOnOff;
	COnOff		ctlOnOff;
	COnOff		gkVolOnOff;
	COnOff		gkS1S2OnOff;
	COnOff		assignOnOff[8];
	CBPM		bpm;
	CLevel		level;
	CKey		key;
	CName		name;
	CNum0To10	chainMix;
	CChain		chain[10];

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CVG88_GKFunc
{
public:
	CVG88_DownS1S2	downS1S2;
	CVG88_SynthVol	synthVol;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};



class CVG88_Global
{
public:
	COnOffS			OnOff;
	CVG88_GlobalVol	lowG;
	CVG88_GlobalVol highG;
	CVG88_GlobalVol	NS;
	CVG88_GlobalRev	reverb;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CVG88_Tuner
{
public:
	CPitchTuner	pitch;
	COnOffS		mute;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};

class CVG88_DriverSettings
{
public:
	CVG88_DriverType		type;
	CVG88_DriverDirection	direction;
	CVG88_DriverScale		scale;
	CVG88_DriverGtPuPhase	GtPuPhase;
	CVG88_DriverS1S2Pos		S1S2Pos;
	CVG88_DriverSettingName	name;
	CVG88_DriverPuBridge	PUBrige[6];
	CNum0To100S				sensitivity[6];
	CVG88_GkConnect			gkConnect;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CVG88_Driver
{
public:
	CVG88_DriverSetting		setting;
	CVG88_DriverSettings	settings[5];

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};


class CVG88_Pedal
{
public:
	CVG88_BankSwMode	bankSwMode;
	CNum1To65S			bankAreaMin;
	CNum1To65S			bankAreaMax;
	CVG88_SubCtl		subCtl1;
	CVG88_SubCtl		subCtl2;
	COnOffS				ExpGkVolHold;
	CNum0To127S			expPedalCalibrationRelease;
	CNum0To127S			expPedalCalibrationPress;

	int getVGData(char **buffer);
	int setVGData(char **buffer);
};

class CPatch
{
public:
	// ===== COSM =====

	CInstrument			*instrument;

	CEq			cosmEq;			// ===== COSM EQ =====
	CCosmPan	cosmPan;		// ===== COSM PAN =====
	CCosmMixer	cosmMixer;		// ===== COSM MIXER =====

	COnOff		cosmEqOnOff;
	CCosmGT		cosmGT;			// ===== COSM GT =====
	CCosmAmp	cosmAmp;		// ===== COSM AMP =====
	CAmp		amp;			// ===== AMP =====
	COnOff		compOnOff;
	COnOff		wahOnOff;
	COnOff		eqOnOff;
	COnOff		modOnOff;
	COnOff		delayOnOff;
	COnOff		chorusOnOff;
	COnOff		reverbOnOff;
	COnOff		nsOnOff;
	CCompE		comp;			// ===== COMP =====
	CWahE		wah;			// ===== WAH =====
	CEq			eq;				// ===== EQ =====
	CModE		mod;			// ===== MOD =====
	CDelay		delay;			// ===== DELAY =====
	CChorus		chorus;			// ===== CHORUS =====
	CReverb		reverb;			// ===== REVERB =====
	CNS			ns;				// ===== NS =====
	CFV			fv;				// ===== FV =====
	CAssign		assign[8];		// ===== ASSIGN =====
	CExp		exp;			// ===== EXP =====
	CCTL		ctl;			// ===== CTL =====
	CGKVol		gkVol;			// ===== GK VOL =====
	CGKS1S2		gkS1S2;			// ===== GK S1/S2 =====

	CAssignNC	assignNC;		// ===== ASSIGN/NAME/CHAIN =====

	bool		modified;
	char		*bufferCompare;

	CPatch();
	~CPatch();
	int	 patchNum;				// Index of the patch in the library
	int  getVGData(char **buffer);
	int  setVGData(char **buffer);
	void checkPatch();
	void initializePatchObjects();
};



class CSystem
{
public:
	CVG88_Display		display;
	CVG88_GKFunc		gkFunc;
	CVG88_Global		global;
	CVG88_Tuner			tuner;
	CVG88_OutputSelect	outputSelect;
	CVG88_Driver		driver;
	CVG88_Pedal			pedal;
	CVG88_Dial			dial;
/*	CVG88_Midi			midi;
	CVG88_ProgamMapBank	programMapBank0;
	CVG88_ProgamMapBank	programMapBank1;
	CVG88_ProgamMapBank	programMapBank2;
*/

	int  getVGData(char **buffer);
	int  setVGData(char **buffer);
};

#define	LIB_PRESET	0
#define	LIB_USER	1
#define	LIB_FILE	2

class CVG88SysEx
{
public:
	CString		file;
	CSystem		*vgSystem;
	CPtrList	patchList;
	int			firstPatchNumber;
	int			deviceId;
	bool		modified;
	void		*data1;
	char		libraryType;
	bool		newLibrary;

	CVG88SysEx();
	~CVG88SysEx();

	void emptyPatchList();
	int  getVGData(char **buffer);
	int  getVGData(char **buffer, CPatch *, int patchNum);
	int  setVGData(char **buffer);
	CString CVG88SysEx::GetLibraryName();
	int  save();
	int  SendPatch(HMIDIOUT hMidiOut, int firstPatch, int lastPatch, int targetPatch, bool onlyModified = FALSE);
	int  SendAuditionPatch(HMIDIOUT hMidiOut);
	void SetModifiedFlag();
	HTREEITEM GetTreeItem();
	HTREEITEM GetTreePatchItem(CPatch *patch);
	BOOL getPatchLabel(int patchNumber, char *label);
};



#endif