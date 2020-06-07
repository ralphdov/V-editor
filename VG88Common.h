#if !defined(AFX_VG88COMMON_H__023EDBDF_837E_400B_BF3B_CF6432A6FCAB__INCLUDED_)
#define AFX_VG88COMMON_H__023EDBDF_837E_400B_BF3B_CF6432A6FCAB__INCLUDED_

#define COSMGT_TYPE_COUNT		22


// Guitar type values

#define COSMGT_VARI_GT			0
#define COSMGT_ACOUSTIC			1
#define COSMGT_NYLON_STRINGS	2
#define COSMGT_OPEN_TUNE		3
#define COSMGT_12STRINGS		4
#define COSMGT_PD_SHIFT			5
#define COSMGT_POLY_DIST		6
#define COSMGT_POLY_COMP		7
#define COSMGT_POLY_OCT			8
#define COSMGT_POLY_SG			9
#define COSMGT_BOWED			10
#define COSMGT_DUAL				11
#define COSMGT_FILTER_BASS		12
#define COSMGT_PIPE				13
#define COSMGT_SOLO				14
#define COSMGT_PWM				15
#define COSMGT_CRYSTAL			16
#define COSMGT_ORGAN			17
#define COSMGT_BRASS			18
#define COSMGT_NYLONII_STRINGS	19
#define COSMGT_SITAR			20
#define COSMGT_WAVE_SYNTH		21


// Guitar Pickup Type

#define	PICKUP_LP		0
#define	PICKUP_CLA_ST	1
#define	PICKUP_MOD_ST	2
#define	PICKUP_TEL		3
#define	PICKUP_P_90		4
#define	PICKUP_LIPS		5
#define	PICKUP_PAF		6
#define	PICKUP_RICK		7
#define	PICKUP_CHET		8
#define	PICKUP_SSH		9
#define	PICKUP_VARI		10

// Pickup Type

#define	TPICKUP_SINGLE		0
#define	TPICKUP_DOUBLE		1
#define	TPICKUP_PIEZO		2
#define	TPICKUP_ACOUSTIC	3

#define TAPICKUP_PIEZO		0
#define TAPICKUP_MIC		1

#define	HARMONY_USER			29

// Sitar Pickup Type

#define	SPICKUP_FRONT		0
#define	SPICKUP_FRONT_REAR	1
#define	SPICKUP_REAR		2
#define	SPICKUP_PIEZO		3


// WAH VALUES
#define WAH_PEDAL	0
#define WAH_AUTO	1

#define WAHMODE_LPF	0
#define WAHMODE_BPF	1

#define WAHPOL_DOWN	0
#define WAHPOL_UP	1

// P.SHIFTER
#define PSMODE_POLY	0
#define PSMODE_MONO	1


// Phaser
#define PHASER_4STAGE	0
#define PHASER_8STAGE	1
#define PHASER_12STAGE	2
#define PHASER_BIPHASE	3

// PD Shift
#define PDSHIFT_MONO	0
#define PDSHIFT_POLY	1


// Amp type

#define AMP_JC_120			0
#define AMP_CLEAN_TWIN		1
#define AMP_CRUNCH			2
#define AMP_MATCH_DRIVE		3
#define AMP_VO_DRIVE		4
#define AMP_BLUES			5
#define AMP_BG_LEAD			6
#define AMP_MS1959_I		7
#define AMP_MS1959_II		8
#define AMP_MS1959_I_II		9
#define AMP_SLDN_LEAD		10	
#define AMP_METAL5150		11
#define AMP_METAL_DRIVE		12
#define AMP_AC_GUITAR		13
#define AMP_JAZZ_COMBO		14
#define AMP_PRO_CRUNCH		15
#define AMP_TWEED			16
#define AMP_STACK_CRUNCH	17
#define AMP_MATCH_LEAD		18
#define AMP_FAT_MATCH		19
#define AMP_VO_CLEAN		20
#define AMP_VO_LEAD			21
#define AMP_BG_RYTHM		22
#define AMP_BG_DRIVE		23
#define AMP_MS_HIGH_GAIN	24
#define AMP_R_FIER_RED		25
#define AMP_R_FIER_ORANGE	26
#define AMP_R_FIER_VINT		27
#define AMP_DRIVE_STACK		28
#define AMP_LEAD_STACK		29
#define AMP_METAL_STACK		30
#define AMP_METAL_LEAD		31


// Speaker type

#define SPEAKER_SMALL			0
#define SPEAKER_MIDDLE			1
#define SPEAKER_JC_120			2
#define SPEAKER_TWIN_ON			3
#define SPEAKER_TWIN_OFF		4
#define SPEAKER_MATCH_ON		5
#define SPEAKER_MATCH_OFF		6
#define SPEAKER_VO_ON			7
#define SPEAKER_VO_OFF			8
#define SPEAKER_BG_STACK_ON		9
#define SPEAKER_BG_STACK_OFF	10
#define SPEAKER_MS_STACK_ON		11
#define SPEAKER_MS_STACK_OFF	12
#define SPEAKER_METAL_STACK		13
#define SPEAKER_ACOUSTIC		14
#define SPEAKER_PRO_RVB			15
#define SPEAKER_TWEED			16
#define SPEAKER_R_FIER			17


// Open tune type
#define TUNE_OPEN_D		0
#define TUNE_OPEN_E		1
#define TUNE_OPEN_G		2
#define TUNE_OPEN_A		3
#define TUNE_DROP_D		4
#define TUNE_NASH_VILLE	5
#define TUNE_USER		6


// DIST Mode

#define DIST_CLA_OD		0
#define DIST_TURBO_OD	1
#define DIST_DS1		2
#define DIST_DS2		3
#define DIST_FUZZ		4

// Poly comp mode

#define POLYCOMP_COMP		0
#define POLYCOMP_LIMITER	1


// Pitch Shifter mode
#define PS_SHIFT	0
#define PS_HARMO	1

// Wave Type
#define WAVE_SAW		0
#define WAVE_SQUARE		1

// Classe CVGData


class CVGData
{
public:
	int	m_data;
	bool m_needSaving;

				 CVGData();
	virtual int	 getValue();
	virtual void setValue(int value);
	virtual void getString(char *dest);
	virtual int  getRange();
	virtual int  getFirstValue();
	virtual int	 getVGData(char **buffer);
	virtual int	 setVGData(char **buffer);
	virtual char **getTabString();
	virtual void freeTabString(char **tabString);
};


class CVGDataLong: public CVGData
{
public:
	int getVGData(char **buffer);
	int	setVGData(char **buffer);
};


class CVGDataShort: public CVGData
{
public:
	int getVGData(char **buffer);
	int	setVGData(char **buffer);
};


class CNumN24To24:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CNumN50To50:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CNum0To100:public CVGData
{
public:
	void setValue(int value);
	int  getRange();
};


class CNum0To10:public CVGData
{
public:
	void setValue(int value);
	int getRange();
};


class CNum0To120:public CVGData
{
public:
	void setValue(int value);
	int getRange();
};


class CNum0To126:public CVGData
{
public:
	void setValue(int value);
	int getRange();
};



class CNum1To127:public CVGData
{
public:
	void setValue(int value);
	int getRange();
	int getFirstValue();
};



class CNum0To200:public CVGData
{
public:
	void setValue(int value);
	int getRange();
};


class CNum0To100S:public CVGDataShort
{
public:
	void setValue(int value);
	int  getRange();
};


class CNum1To65S:public CVGDataShort
{
public:
	void setValue(int value);
	int  getRange();
};


class CNum0To127S:public CVGDataShort
{
public:
	void setValue(int value);
	int  getRange();
};


class CPickupModel:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	void setPickupType(char *dest);

	int getRange();
};



class CPickupPosition:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int getRange();
};


class CSPickupPosition:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int getRange();
};


class CPickupType:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int	 getRange();
};


#define PICKUP_3POS	0
#define PICKUP_5POS	1

#define PICKUPPOS_REAR		0
#define PICKUPPOS_C_R		1
#define PICKUPPOS_CENTER	2
#define PICKUPPOS_F_R		2
#define PICKUPPOS_F_C		3
#define PICKUPPOS_FRONT		4


class CPickupPickup:public CVGData
{
public:
	char type;
	CPickupPickup();
	void setPickupType(int);
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CPitchShiftMode:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CVariGtHarm:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};



class CLowCut:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CLowCut2:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CHighCut:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CBodyType:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};



class COnOff:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class COnOffS:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CPickupPhase:public COnOff
{
public:
	void getString(char *dest);
};


class CPickupAngle:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CAPickupType:public COnOff
{
public:
	void getString(char *dest);
};


class CTuneType:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CPitch : public CVGDataLong
{
public:
	int	 getVGData(char **buffer);
	int	 setVGData(char **buffer);
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CDistMode:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CEqValue:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CEqMidF:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CEqMidQ:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CBPM:public CVGDataLong
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getFirstValue();
	int  getRange();
};


class CKey:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CName
{
	CVGData		car[8];

public:
	void setString(char *name);
	void getString(char *name);
	int  getVGData(char **buffer);
	int  setVGData(char **buffer);
};


class CChain:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CPanBalance:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CPanBalanceST:public CVGData
{
public:
	void getString(char *dest);
};


class CMixerBalance:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CMAmpBalance:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CPola:public COnOff
{
public:
	void getString(char *dest);
};


class CGuitarType:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CAmpType:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CGain:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CSpeaker:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};

class CMicset:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CWahModel:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};

class CWahType:public COnOff
{
public:
	void getString(char *dest);
};


class CAutoWahMode:public COnOff
{
public:
	void getString(char *dest);
};


class CPolarity:public COnOff
{
public:
	void getString(char *dest);
};


class CRate:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CCompMode:public COnOff
{
public:
	void getString(char *dest);
};


class CModType:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CHr1Harmony:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};



class CPSPredly:public CVGDataLong
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CRVBPreDly:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CPSMode:public COnOff
{
public:
	void getString(char *dest);
};


class CStage:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};



class CStep:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CXoverF:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};



class CCHPredly:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};



class CChorusMode:public COnOff
{
public:
	void getString(char *dest);
};


class CReverbMode:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};



class CReverbTime:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
	int  getFirstValue();
};


class CDlyTime:public CVGDataLong
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};



class CTapeTime:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};



class CAssignTarget:public CVGDataLong
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CShape:public COnOff
{
public:
	void getString(char *dest);
};


class CFtype:public COnOff
{
public:
	void getString(char *dest);
};


class CAssignMinMax:public CVGDataLong
{
public:
	CAssignMinMax();
	~CAssignMinMax();
	void setVgDataType(int type);

	CVGData *vgData;
	int m_mul;
	void setValue(int value);
	int getValue();
	void getString(char *dest);
	int getFirstValue();
	int  getRange();
};


#define ASSIGN_EXP_PEDAL	0
#define ASSIGN_CTL_PEDAL	1
#define ASSIGN_SUB_EXP		2
#define ASSIGN_SUB_CRL1		3
#define ASSIGN_SUB_CTL2		4
#define ASSIGN_GK_VOL		5
#define ASSIGN_GK_S1_S2		6

class CAssignSource:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


#define ASSIGNMODE_DEC_IN	0
#define ASSIGNMODE_NORMAL	1

class CAssignMode:public COnOff
{
public:
	char m_type;
	CAssignMode();
	void setType(char type);
	void getString(char *dest);
};



class CLevel:public CVGData
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CShiftString:public CNumN24To24
{
public:
	char stringNum;

	CShiftString();
	void getString(char *dest);
	void setStringNum(char stringNum);
};


// SYSTEM Objects

class CVG88_Display:public CVGDataShort
{
public:
	void setValue(int value);
	int  getRange();
	int  getFirstValue();
};


class CVG88_DownS1S2:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CVG88_SynthVol:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CVG88_GlobalVol:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CVG88_GlobalRev:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CPitchTuner:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CVG88_OutputSelect:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CVG88_DriverSetting:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CVG88_DriverType:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CVG88_DriverDirection:public COnOffS
{
public:
	void getString(char *dest);
};


class CVG88_DriverScale:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};


class CVG88_DriverGtPuPhase:public COnOffS
{
public:
	void getString(char *dest);
};


class CVG88_DriverS1S2Pos:public CVG88_DriverDirection
{
public:
};


class CVG88_DriverSettingName
{
	CVGDataShort	car[8];
public:
	void setString(char *name);
	void getString(char *dest);
	int  getVGData(char **buffer);
	int  setVGData(char **buffer);
};


class CVG88_DriverPuBridge:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};

class CVG88_GkConnect:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};

class CVG88_BankSwMode:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};

class CVG88_SubCtl:public CVGDataShort
{
public:
	void setValue(int value);
	void getString(char *dest);
	int  getRange();
};

class CVG88_Dial:public COnOffS
{
public:
	void getString(char *dest);
};

#endif
