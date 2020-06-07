#include <string.h>
#include <typeinfo>
#include <Afx.h>
#include "stdafx.h"
#include "VEditor.h"
#include "tools.h"
#include "MainFrm.h"
#include "VG-88.h"
#include "SendPatch.h"

CPatch::CPatch()
{
	instrument = NULL;
	patchNum = 0;
	modified = FALSE;
	bufferCompare = NULL;
}


CPatch::~CPatch()
{
	if (instrument)
		delete (instrument);
}


int CPatch::getVGData(char **buffer)
{
	int count;
	int i;

	count =  instrument->getVGData(buffer);
	count += cosmEq.getVGData(buffer);
	count += cosmPan.getVGData(buffer);
	count += cosmMixer.getVGData(buffer);
	count += cosmEqOnOff.getVGData(buffer);
	count += cosmGT.getVGData(buffer);
	count += cosmAmp.getVGData(buffer);
	count += amp.getVGData(buffer);
	count += compOnOff.getVGData(buffer);
	count += wahOnOff.getVGData(buffer);
	count += eqOnOff.getVGData(buffer);
	count += modOnOff.getVGData(buffer);
	count += delayOnOff.getVGData(buffer);
	count += chorusOnOff.getVGData(buffer);
	count += reverbOnOff.getVGData(buffer);
	count += nsOnOff.getVGData(buffer);
	count += comp.getVGData(buffer);
	count += wah.getVGData(buffer);
	count += eq.getVGData(buffer);
	count += mod.getVGData(buffer);
	count += delay.getVGData(buffer);
	count += chorus.getVGData(buffer);
	count += reverb.getVGData(buffer);
	count += ns.getVGData(buffer);
	count += fv.getVGData(buffer);

	for (i = 0; i < 8; i++)
		count += assign[i].getVGData(buffer);

	count += exp.getVGData(buffer);
	count += ctl.getVGData(buffer);
	count += gkVol.getVGData(buffer);
	count += gkS1S2.getVGData(buffer);
	count += assignNC.getVGData(buffer);

	return count;
}



int CPatch::setVGData(char **buffer)
{
	int count;
	int guitareType;
	int i;

	guitareType = cosmGT.guitarType.getValue();

	switch (guitareType)
	{
		case COSMGT_VARI_GT:
			instrument = new CVariGuitar;
			break;

		case COSMGT_ACOUSTIC:
			instrument = new CAcoustic;
			break;

		case COSMGT_NYLON_STRINGS:
			instrument = new CNylonStrings;
			break;

		case COSMGT_OPEN_TUNE:
			instrument = new COpenTune;
			break;

		case COSMGT_12STRINGS:
			instrument = new CStrings12;
			break;

		case COSMGT_PD_SHIFT:
			instrument = new CPdShift;
			break;

		case COSMGT_POLY_DIST:
			instrument = new CPolyDist;
			break;

		case COSMGT_POLY_COMP:
			instrument = new CPolyComp;
			break;

		case COSMGT_POLY_OCT:
			instrument = new CPolyOct;
			break;

		case COSMGT_POLY_SG:
			instrument = new CPolySG;
			break;

		case COSMGT_BOWED:
			instrument = new CBowed;
			break;

		case COSMGT_DUAL:
			instrument = new CDual;
			break;

		case COSMGT_FILTER_BASS:
			instrument = new CFilterBass;
			break;

		case COSMGT_PIPE:
			instrument = new CPipe;
			break;

		case COSMGT_SOLO:
			instrument = new CSolo;
			break;

		case COSMGT_PWM:
			instrument = new CPWM;
			break;

		case COSMGT_CRYSTAL:
			instrument = new CCrystal;
			break;

		case COSMGT_ORGAN:
			instrument = new COrgan;
			break;

		case COSMGT_BRASS:
			instrument = new CBrass;
			break;

		case COSMGT_NYLONII_STRINGS:
			instrument = new CNylonII;
			break;

		case COSMGT_SITAR:
			instrument = new CSitar;
			break;

		case COSMGT_WAVE_SYNTH:
			instrument = new CWave;
			break;
	}

	count =  instrument->setVGData(buffer);

	count += cosmEq.setVGData(buffer);
	count += cosmPan.setVGData(buffer);
	count += cosmMixer.setVGData(buffer);
	count += cosmEqOnOff.setVGData(buffer);
	count += cosmGT.setVGData(buffer);
	count += cosmAmp.setVGData(buffer);
	count += amp.setVGData(buffer);
	count += compOnOff.setVGData(buffer);
	count += wahOnOff.setVGData(buffer);
	count += eqOnOff.setVGData(buffer);
	count += modOnOff.setVGData(buffer);
	count += delayOnOff.setVGData(buffer);
	count += chorusOnOff.setVGData(buffer);
	count += reverbOnOff.setVGData(buffer);
	count += nsOnOff.setVGData(buffer);
	count += comp.setVGData(buffer);
	count += wah.setVGData(buffer);
	count += eq.setVGData(buffer);
	count += mod.setVGData(buffer);
	count += delay.setVGData(buffer);
	count += chorus.setVGData(buffer);
	count += reverb.setVGData(buffer);
	count += ns.setVGData(buffer);
	count += fv.setVGData(buffer);

	for (i = 0; i < 8; i++)
		count += assign[i].setVGData(buffer);

	count += exp.setVGData(buffer);
	count += ctl.setVGData(buffer);
	count += gkVol.setVGData(buffer);
	count += gkS1S2.setVGData(buffer);
	count += assignNC.setVGData(buffer);

	initializePatchObjects();

	return count;
}


void CPatch::checkPatch()
{
	int i;

	// Check if the instrument object is the right one
	switch (cosmGT.guitarType.getValue())
	{
		case COSMGT_VARI_GT:
			if (strcmp(typeid(*instrument).name(), "class CVariGuitar") != 0)
			{
				delete instrument;
				instrument = new CVariGuitar;

				// Default values for this intrument
				((CVariGuitar *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_ACOUSTIC:
			if (strcmp(typeid(*instrument).name(), "class CAcoustic") != 0)
			{
				delete instrument;
				instrument = new CAcoustic;

				// Default values for this intrument
				((CAcoustic *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_NYLON_STRINGS:
			if (strcmp(typeid(*instrument).name(), "class CNylonStrings") != 0)
			{
				delete instrument;
				instrument = new CNylonStrings;

				// Default values for this intrument
				((CNylonStrings *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_OPEN_TUNE:
			if (strcmp(typeid(*instrument).name(), "class COpenTune") != 0)
			{
				delete instrument;
				instrument = new COpenTune;

				// Default values for this intrument
				((COpenTune *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_12STRINGS:
			if (strcmp(typeid(*instrument).name(), "class CStrings12") != 0)
			{
				delete instrument;
				instrument = new CStrings12;

				// Default values for this intrument
				((CStrings12 *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_PD_SHIFT:
			if (strcmp(typeid(*instrument).name(), "class CPdShift") != 0)
			{
				delete instrument;
				instrument = new CPdShift;

				// Default values for this intrument
				((CPdShift *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_POLY_DIST:
			if (strcmp(typeid(*instrument).name(), "class CPolyDist") != 0)
			{
				delete instrument;
				instrument = new CPolyDist;

				// Default values for this intrument
				((CPolyDist *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_POLY_COMP:
			if (strcmp(typeid(*instrument).name(), "class CPolyComp") != 0)
			{
				delete instrument;
				instrument = new CPolyComp;

				// Default values for this intrument
				((CPolyComp *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_POLY_OCT:
			if (strcmp(typeid(*instrument).name(), "class CPolyOct") != 0)
			{
				delete instrument;
				instrument = new CPolyOct;

				// Default values for this intrument
				((CPolyOct *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_POLY_SG:
			if (strcmp(typeid(*instrument).name(), "class CPolySG") != 0)
			{
				delete instrument;
				instrument = new CPolySG;

				// Default values for this intrument
				((CPolySG *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_BOWED:
			if (strcmp(typeid(*instrument).name(), "class CBowed") != 0)
			{
				delete instrument;
				instrument = new CBowed;

				// Default values for this intrument
				((CBowed *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_DUAL:
			if (strcmp(typeid(*instrument).name(), "class CDual") != 0)
			{
				delete instrument;
				instrument = new CDual;

				// Default values for this intrument
				((CDual *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_FILTER_BASS:
			if (strcmp(typeid(*instrument).name(), "class CFilterBass") != 0)
			{
				delete instrument;
				instrument = new CFilterBass;

				// Default values for this intrument
				((CFilterBass *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_PIPE:
			if (strcmp(typeid(*instrument).name(), "class CPipe") != 0)
			{
				delete instrument;
				instrument = new CPipe;

				// Default values for this intrument
				((CPipe *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_SOLO:
			if (strcmp(typeid(*instrument).name(), "class CSolo") != 0)
			{
				delete instrument;
				instrument = new CSolo;

				// Default values for this intrument
				((CSolo *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_PWM:
			if (strcmp(typeid(*instrument).name(), "class CPWM") != 0)
			{
				delete instrument;
				instrument = new CPWM;

				// Default values for this intrument
				((CPWM *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_CRYSTAL:
			if (strcmp(typeid(*instrument).name(), "class CCrystal") != 0)
			{
				delete instrument;
				instrument = new CCrystal;

				// Default values for this intrument
				((CCrystal *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_ORGAN:
			if (strcmp(typeid(*instrument).name(), "class COrgan") != 0)
			{
				delete instrument;
				instrument = new COrgan;

				// Default values for this intrument
				((COrgan *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_BRASS:
			if (strcmp(typeid(*instrument).name(), "class CBrass") != 0)
			{
				delete instrument;
				instrument = new CBrass;

				// Default values for this intrument
				((CBrass *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_NYLONII_STRINGS:
			if (strcmp(typeid(*instrument).name(), "class CNylonII") != 0)
			{
				delete instrument;
				instrument = new CNylonII;

				// Default values for this intrument
				((CNylonII *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_SITAR:
			if (strcmp(typeid(*instrument).name(), "class CSitar") != 0)
			{
				delete instrument;
				instrument = new CSitar;

				// Default values for this intrument
				((CSitar *) instrument)->setDefaultValues();
			}

			break;

		case COSMGT_WAVE_SYNTH:
			if (strcmp(typeid(*instrument).name(), "class CWave") != 0)
			{
				delete instrument;
				instrument = new CWave;

				// Default values for this intrument
				((CWave *) instrument)->setDefaultValues();
			}

			break;
	}


	// Check if the wah object is the right one (pedal wah or auto wah)
	switch (wah.wahType.getValue())
	{
		case WAH_PEDAL:
			if (strcmp(typeid(*wah.wah).name(), "class CPedalWah") != 0)
			{
				delete wah.wah;
				wah.wah = new CPedalWah;
				
				// Default values for this intrument
				((CPedalWah *) wah.wah)->setDefaultValues();
			}

			break;

		case WAH_AUTO:
			if (strcmp(typeid(*wah.wah).name(), "class CAutoWah") != 0)
			{
				delete wah.wah;
				wah.wah = new CAutoWah;

				// Default values for this intrument
				((CAutoWah *) wah.wah)->setDefaultValues();
			}
			break;
	}


	// Check if the modulation object is the right one
	switch (mod.modeType.getValue())
	{
		case MOD_HARMONIST:
			if (strcmp(typeid(*mod.mod).name(), "class CHarmonist") != 0)
			{
				delete mod.mod;
				mod.mod = new CHarmonist;

				// Default values for this modulation effect
				((CHarmonist *) mod.mod)->setDefaultValues();
			}
			break;


		case MOD_PSHIFTER:
			if (strcmp(typeid(*mod.mod).name(), "class CPitchShifter") != 0)
			{
				delete mod.mod;
				mod.mod = new CPitchShifter;

				// Default values for this modulation effect
				((CPitchShifter *) mod.mod)->setDefaultValues();
			}
			break;

		case MOD_FLANGER:
			if (strcmp(typeid(*mod.mod).name(), "class CFlanger") != 0)
			{
				delete mod.mod;
				mod.mod = new CFlanger;

				// Default values for this modulation effect
				((CFlanger *) mod.mod)->setDefaultValues();
			}

			break;

		case MOD_PHASER:
			if (strcmp(typeid(*mod.mod).name(), "class CPhaser") != 0)
			{
				delete mod.mod;
				mod.mod = new CPhaser;

				// Default values for this modulation effect
				((CPhaser *) mod.mod)->setDefaultValues();
			}
			break;

		case MOD_SUBEQ:
			if (strcmp(typeid(*mod.mod).name(), "class CSubEq") != 0)
			{
				delete mod.mod;
				mod.mod = new CSubEq;

				// Default values for this modulation effect
				((CSubEq *) mod.mod)->setDefaultValues();
			}
			break;

		case MOD_2X2CHORUS:
			if (strcmp(typeid(*mod.mod).name(), "class CChorus2x2") != 0)
			{
				delete mod.mod;
				mod.mod = new CChorus2x2;

				// Default values for this modulation effect
				((CChorus2x2 *) mod.mod)->setDefaultValues();
			}
			break;

		case MOD_TREMOLO:
			if (strcmp(typeid(*mod.mod).name(), "class CTremolo") != 0)
			{
				delete mod.mod;
				mod.mod = new CTremolo;

				// Default values for this modulation effect
				((CTremolo *) mod.mod)->setDefaultValues();
			}
			break;

		case MOD_PAN:
			if (strcmp(typeid(*mod.mod).name(), "class CPan") != 0)
			{
				delete mod.mod;
				mod.mod = new CPan;

				// Default values for this modulation effect
				((CPan *) mod.mod)->setDefaultValues();
			}
			break;

		case MOD_PDSHIFT:
			if (strcmp(typeid(*mod.mod).name(), "class CModPDShift") != 0)
			{
				delete mod.mod;
				mod.mod = new CModPDShift;

				// Default values for this modulation effect
				((CModPDShift *) mod.mod)->setDefaultValues();
			}
			break;

		case MOD_VIBRATO:
			if (strcmp(typeid(*mod.mod).name(), "class CVibrato") != 0)
			{
				delete mod.mod;
				mod.mod = new CVibrato;

				// Default values for this modulation effect
				((CVibrato *) mod.mod)->setDefaultValues();
			}
			break;

		case MOD_DEFRETTER:
			if (strcmp(typeid(*mod.mod).name(), "class CDefretter") != 0)
			{
				delete mod.mod;
				mod.mod = new CDefretter;

				// Default values for this modulation effect
				((CDefretter *) mod.mod)->setDefaultValues();
			}
			break;

		case MOD_UNIV:
			if (strcmp(typeid(*mod.mod).name(), "class CUniV") != 0)
			{
				delete mod.mod;
				mod.mod = new CUniV;

				// Default values for this modulation effect
				((CUniV *) mod.mod)->setDefaultValues();
			}
			break;

	}

	// Check that Assign active range "Hi" is greater then the "Low" one

	for (i = 0; i < 8; i++)
	{
		if (assignNC.assignActiveRangeLo[i].getValue() >= assignNC.assignActiveRangeHi[i].getValue())
		{
			assignNC.assignActiveRangeLo[i].setValue(assignNC.assignActiveRangeHi[i].getValue() - 1);
		}
	}
}

void CPatch::initializePatchObjects()
{
	int guitarType;
	int pickupModel;
	int i;


	// Initialize assign objects

	for (i = 0; i < 8; i++)
	{
		assign[i].assignMin.setVgDataType(assign[i].assignTarget.getValue());
		assign[i].assignMax.setVgDataType(assign[i].assignTarget.getValue());

		switch (assign[i].assignSource.getValue())
		{
			case ASSIGN_GK_S1_S2:
				assign[i].assignMode.setType(ASSIGNMODE_DEC_IN);
				break;

			default:
				assign[i].assignMode.setType(ASSIGNMODE_NORMAL);
		}
	}


	// Initialize Expression pedal assign object
	exp.expMin.setVgDataType(exp.expTarget.getValue());
	exp.expMax.setVgDataType(exp.expTarget.getValue());


	// Initialize control pedal assign object
	ctl.ctlMin.setVgDataType(ctl.ctlTarget.getValue());
	ctl.ctlMax.setVgDataType(ctl.ctlTarget.getValue());
	ctl.ctlmode.setType(ASSIGNMODE_NORMAL);


	// Initialize gk2a volume assign object
	gkVol.gkVolMin.setVgDataType(gkVol.gkVolTarget.getValue());
	gkVol.gkVolMax.setVgDataType(gkVol.gkVolTarget.getValue());


	// Initialize gk2a S1/S2 assign object
	gkS1S2.gkS1S2Min.setVgDataType(gkS1S2.gkS1S2Target.getValue());
	gkS1S2.gkS1S2Max.setVgDataType(gkS1S2.gkS1S2Target.getValue());
	gkS1S2.gkS1S2mode.setType(ASSIGNMODE_DEC_IN);


	// Initialize pickup selector (3 or 5 position)
	guitarType = cosmGT.guitarType.getValue();

	switch (guitarType)
	{
		case COSMGT_VARI_GT:
			pickupModel = ((CVariGuitar *) instrument)->pickup.model.getValue();
			((CVariGuitar *) instrument)->pickup.pickup.setPickupType(pickupModel);
			break;

		case COSMGT_OPEN_TUNE:
			pickupModel = ((COpenTune *) instrument)->pickup.model.getValue();
			((COpenTune *) instrument)->pickup.pickup.setPickupType(pickupModel);
			break;

		case COSMGT_12STRINGS:
			pickupModel = ((CStrings12 *) instrument)->pickup.model.getValue();
			((CStrings12 *) instrument)->pickup.pickup.setPickupType(pickupModel);
			break;

		case COSMGT_PD_SHIFT:
			pickupModel = ((CPdShift *) instrument)->pickup.model.getValue();
			((CPdShift *) instrument)->pickup.pickup.setPickupType(pickupModel);
			break;

		case COSMGT_POLY_DIST:
			pickupModel = ((CPolyDist *) instrument)->pickup.model.getValue();
			((CPolyDist *) instrument)->pickup.pickup.setPickupType(pickupModel);
			break;

		case COSMGT_POLY_COMP:
			pickupModel = ((CPolyComp *) instrument)->pickup.model.getValue();
			((CPolyComp *) instrument)->pickup.pickup.setPickupType(pickupModel);
			break;

		case COSMGT_POLY_OCT:
			pickupModel = ((CPolyOct *) instrument)->pickup.model.getValue();
			((CPolyOct *) instrument)->pickup.pickup.setPickupType(pickupModel);
			break;

		case COSMGT_POLY_SG:
			pickupModel = ((CPolySG *) instrument)->pickup.model.getValue();
			((CPolySG *) instrument)->pickup.pickup.setPickupType(pickupModel);
			break;

		default:
			pickupModel = -1;
	}


	for (i = 0; i < 8; i++)
	{
		if (assign[i].assignTarget.getValue() == 12)
		{
			if (pickupModel != -1)
			{
				((CPickupPickup *) assign[i].assignMin.vgData)->setPickupType(pickupModel);
				((CPickupPickup *) assign[i].assignMax.vgData)->setPickupType(pickupModel);
			}
			else
			{
				((CPickupPickup *) assign[i].assignMin.vgData)->setPickupType(0);
				((CPickupPickup *) assign[i].assignMax.vgData)->setPickupType(0);
			}
		}
	}
}



////////// CPickup  //////////

int CPickup::getVGData(char **buffer)
{
	int count;

	count =  rearPickupPosition.getVGData(buffer);
	count += rearPickupAngle.getVGData(buffer);
	count += frontPickupPosition.getVGData(buffer);
	count += frontPickupAngle.getVGData(buffer);
	count += model.getVGData(buffer);
	count += pickup.getVGData(buffer);
	count += tone.getVGData(buffer);
	count += level.getVGData(buffer);
	count += phase.getVGData(buffer);
	count += rearPickuType.getVGData(buffer);
	count += frontPickuType.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	return count;
}



int CPickup::setVGData(char **buffer)
{
	int count;

	count =  rearPickupPosition.setVGData(buffer);
	count += rearPickupAngle.setVGData(buffer);
	count += frontPickupPosition.setVGData(buffer);
	count += frontPickupAngle.setVGData(buffer);
	count += model.setVGData(buffer);
	count += pickup.setVGData(buffer);
	count += tone.setVGData(buffer);
	count += level.setVGData(buffer);
	count += phase.setVGData(buffer);
	count += rearPickuType.setVGData(buffer);
	count += frontPickuType.setVGData(buffer);

	*buffer += 2;
	count += 2;

	return count;
}


void CPickup::setDefaultValues()
{
	model.setValue(PICKUP_CLA_ST);
	pickup.setValue(PICKUPPOS_REAR);
	tone.setValue(50);					// 50 = 0
	level.setValue(100);
	
	rearPickuType.setValue(TPICKUP_SINGLE);
	rearPickupPosition.setValue(7);		// 7 = 40 mm
	rearPickupAngle.setValue(63);		// 63 = 0 mm

	frontPickuType.setValue(TPICKUP_SINGLE);
	frontPickupPosition.setValue(31);	// 31 = 160 mm
	frontPickupAngle.setValue(63);		// 63 = 0 mm

	phase.setValue(0);					// 0 = IN
}



////////// CSitar  //////////

int CSitar::getVGData(char **buffer)
{
	int count;

	count =  pickup.getVGData(buffer);
	count += body.getVGData(buffer);
	count += sens.getVGData(buffer);
	count += tone.getVGData(buffer);
	count += level.getVGData(buffer);
	count += color.getVGData(buffer);
	count += decay.getVGData(buffer);
	count += buzz.getVGData(buffer);
	count += AttackLevel.getVGData(buffer);

	memset(*buffer, 0, 94);
	*buffer += 94;
	count += 94;


	return count;
}



int CSitar::setVGData(char **buffer)
{
	int count;

	count =  pickup.setVGData(buffer);
	count += body.setVGData(buffer);
	count += sens.setVGData(buffer);
	count += tone.setVGData(buffer);
	count += level.setVGData(buffer);
	count += color.setVGData(buffer);
	count += decay.setVGData(buffer);
	count += buzz.setVGData(buffer);
	count += AttackLevel.setVGData(buffer);

	*buffer += 94;
	count += 94;

	return count;
}


void CSitar::setDefaultValues()
{
	pickup.setValue(SPICKUP_FRONT_REAR);
	tone.setValue(58);					// 50 = 0
	level.setValue(68);
	sens.setValue(50);
	body.setValue(33);
	color.setValue(72);
	decay.setValue(68);
	buzz.setValue(43);
	AttackLevel.setValue(92);
}


//////////  CWave //////////

int CWave::getVGData(char **buffer)
{
	int count;

	count = shape.getVGData(buffer);
	count += sens.getVGData(buffer);
	count += attack.getVGData(buffer);
	count += decay.getVGData(buffer);
	count += level.getVGData(buffer);
	count += cutoff.getVGData(buffer);
	count += reso.getVGData(buffer);
	count += ftype.getVGData(buffer);
	count += fattack.getVGData(buffer);
	count += fdecay.getVGData(buffer);
	count += fdepth.getVGData(buffer);

	memset(*buffer, 0, 90);
	*buffer += 90;
	count += 90;

	return count;
}


int CWave::setVGData(char **buffer)
{
	int count;

	count = shape.setVGData(buffer);
	count += sens.setVGData(buffer);
	count += attack.setVGData(buffer);
	count += decay.setVGData(buffer);
	count += level.setVGData(buffer);
	count += cutoff.setVGData(buffer);
	count += reso.setVGData(buffer);
	count += ftype.setVGData(buffer);
	count += fattack.setVGData(buffer);
	count += fdecay.setVGData(buffer);
	count += fdepth.setVGData(buffer);

	*buffer += 90;
	count += 90;

	return count;
}


void CWave::setDefaultValues()
{
	shape.setValue(0);
	sens.setValue(80);
	attack.setValue(0);
	decay.setValue(100);
	level.setValue(100);
	cutoff.setValue(50);
	reso.setValue(30);
	ftype.setValue(1);
	fattack.setValue(50);
	fdecay.setValue(50);
	fdepth.setValue(70);
}


//////////  CAPickup //////////

int CAPickup::getVGData(char **buffer)
{
	int count;

	count =  tone.getVGData(buffer);
	count += level.getVGData(buffer);
	count += type.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	return count;
}



int CAPickup::setVGData(char **buffer)
{
	int count;

	count =  tone.setVGData(buffer);
	count += level.setVGData(buffer);
	count += type.setVGData(buffer);

	*buffer += 2;
	count += 2;

	return count;
}


void CAPickup::setDefaultValues()
{
	level.setValue(100);
	tone.setValue(50);
	type.setValue(TAPICKUP_PIEZO);
}

//////////  CPitchShift //////////

int CPitchShift::getVGData(char **buffer)
{
	int count;
	int i;

	count =  mode.getVGData(buffer);

	for (i = 0; i < 6; i++)
		count += shift[i].getVGData(buffer);

	for (i = 0; i < 6; i++)
		count += fine[i].getVGData(buffer);

	for (i = 0; i < 6; i++)
		count += eLevel[i].getVGData(buffer);

	for (i = 0; i < 6; i++)
		count += dLevel[i].getVGData(buffer);

	for (i = 0; i < 6; i++)
		count += harmo[i].getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	return count;
}



int CPitchShift::setVGData(char **buffer)
{
	int count;
	int i;

	count =  mode.setVGData(buffer);

	for (i = 0; i < 6; i++)
		count += shift[i].setVGData(buffer);

	for (i = 0; i < 6; i++)
		count += fine[i].setVGData(buffer);

	for (i = 0; i < 6; i++)
		count += eLevel[i].setVGData(buffer);

	for (i = 0; i < 6; i++)
		count += dLevel[i].setVGData(buffer);

	for (i = 0; i < 6; i++)
		count += harmo[i].setVGData(buffer);

	*buffer += 2;
	count += 2;

	return count;
}


void CPitchShift::setDefaultValues()
{
	int i;

	mode.setValue(0);	// mode shift

	for (i = 0; i < 6; i++)
	{
		shift[i].setValue(24);		// 24 = 0
		fine[i].setValue(50);
		eLevel[i].setValue(100);
		dLevel[i].setValue(100);
		harmo[i].setValue(12);
	}
}


//////////  CBody //////////

int CBody::getVGData(char **buffer)
{
	int count;

	count =  attack.getVGData(buffer);
	count += body.getVGData(buffer);
	count += lowCut.getVGData(buffer);
	count += level.getVGData(buffer);
	count += bodyType.getVGData(buffer);
	count += reso.getVGData(buffer);
	count += size.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	return count;
}



int CBody::setVGData(char **buffer)
{
	int count;

	count =  attack.setVGData(buffer);
	count += body.setVGData(buffer);
	count += lowCut.setVGData(buffer);
	count += level.setVGData(buffer);
	count += bodyType.setVGData(buffer);
	count += reso.setVGData(buffer);
	count += size.setVGData(buffer);

		*buffer += 2;
	count += 2;

	return count;
}

void CBody::setDefaultValues()
{
	attack.setValue(0);
	body.setValue(0);
	level.setValue(100);
	lowCut.setValue(0);
	bodyType.setValue(0);
	reso.setValue(50);
	size.setValue(50);
}


//////////  CNBody //////////

int CNBody::getVGData(char **buffer)
{
	int count;

	count =  level.getVGData(buffer);
	count += bottom.getVGData(buffer);
	count += reso.getVGData(buffer);
	count += size.getVGData(buffer);

	return count;
}



int CNBody::setVGData(char **buffer)
{
	int count;

	count =  level.setVGData(buffer);
	count += bottom.setVGData(buffer);
	count += reso.setVGData(buffer);
	count += size.setVGData(buffer);

	return count;
}


//////////  CNIIBody //////////

int CNIIBody::getVGData(char **buffer)
{
	int count;

	count = body.getVGData(buffer);
	count += attack.getVGData(buffer);
	count += tone.getVGData(buffer);
	count +=  level.getVGData(buffer);

	return count;
}



int CNIIBody::setVGData(char **buffer)
{
	int count;

	count = body.setVGData(buffer);
	count += tone.setVGData(buffer);
	count += attack.setVGData(buffer);
	count +=  level.setVGData(buffer);

	return count;
}

////////// CTune  //////////

int CTune::getVGData(char **buffer)
{
	int count;
	int i;

	count =  type.getVGData(buffer);

	for (i = 0; i < 6; i++)
		count += shift[i].getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;


	return count;
}



int CTune::setVGData(char **buffer)
{
	int count;
	int i;

	count =  type.setVGData(buffer);

	for (i = 0; i < 6; i++)
		count += shift[i].setVGData(buffer);

	*buffer += 2;
	count += 2;

	return count;
}



////////// CDetune  //////////

int CDetune::getVGData(char **buffer)
{
	int count;

	count =  detune.getVGData(buffer);

	memset(*buffer, 0, 6);
	*buffer += 6;
	count += 6;

	return count;
}



int CDetune::setVGData(char **buffer)
{
	int count;

	count =  detune.setVGData(buffer);

	*buffer += 6;
	count += 6;

	return count;
}



////////// CShift  //////////

int CShift::getVGData(char **buffer)
{
	int count;
	int i;

	count =  pitch.getVGData(buffer);

	for (i = 0; i < 6; i++)
		count += string[i].getVGData(buffer);

	return count;
}



int CShift::setVGData(char **buffer)
{
	int count;
	int i;

	count =  pitch.setVGData(buffer);

	for (i = 0; i < 6; i++)
		count += string[i].setVGData(buffer);

	return count;
}



////////// CDist  //////////

int CDist::getVGData(char **buffer)
{
	int count;

	count =  mode.getVGData(buffer);
	count += drive.getVGData(buffer);
	count += highCut.getVGData(buffer);
	count += level.getVGData(buffer);
	count += polyBal.getVGData(buffer);
	count += drvBal.getVGData(buffer);

	memset(*buffer, 0, 4);
	*buffer += 4;
	count += 4;

	return count;
}



int CDist::setVGData(char **buffer)
{
	int count;

	count =  mode.setVGData(buffer);
	count += drive.setVGData(buffer);
	count += highCut.setVGData(buffer);
	count += level.setVGData(buffer);
	count += polyBal.setVGData(buffer);
	count += drvBal.setVGData(buffer);

	*buffer += 4;
	count += 4;

	return count;
}



////////// CIComp  //////////

int CIComp::getVGData(char **buffer)
{
	int count;

	count =  mode.getVGData(buffer);
	count += sustain.getVGData(buffer);
	count += attack.getVGData(buffer);
	count += tone.getVGData(buffer);
	count += level.getVGData(buffer);
	count += cmpBal.getVGData(buffer);
	count += threshold.getVGData(buffer);
	count += release.getVGData(buffer);

	return count;
}



int CIComp::setVGData(char **buffer)
{
	int count;

	count =  mode.setVGData(buffer);
	count += sustain.setVGData(buffer);
	count += attack.setVGData(buffer);
	count += tone.setVGData(buffer);
	count += level.setVGData(buffer);
	count += cmpBal.setVGData(buffer);
	count += threshold.setVGData(buffer);
	count += release.setVGData(buffer);

	return count;
}



//////////  COctave //////////

int COctave::getVGData(char **buffer)
{
	int count = 0;
	int i;

	for (i = 0; i < 6; i++)
		count += Oct1[i].getVGData(buffer);

	for (i = 0; i < 6; i++)
		count += Oct2[i].getVGData(buffer);

	for (i = 0; i < 6; i++)
		count += dir[i].getVGData(buffer);


	memset(*buffer, 0, 4);
	*buffer += 4;
	count += 4;

	return count;
}



int COctave::setVGData(char **buffer)
{
	int count = 0;
	int i;

	for (i = 0; i < 6; i++)
		count += Oct1[i].setVGData(buffer);

	for (i = 0; i < 6; i++)
		count += Oct2[i].setVGData(buffer);

	for (i = 0; i < 6; i++)
		count += dir[i].setVGData(buffer);


	*buffer += 4;
	count += 4;

	return count;
}



//////////  CSG //////////

int CSG::getVGData(char **buffer)
{
	int count;

	count =  riseTime.getVGData(buffer);
	count += sens.getVGData(buffer);

	return count;
}



int CSG::setVGData(char **buffer)
{
	int count;

	count =  riseTime.setVGData(buffer);
	count += sens.setVGData(buffer);

	return count;
}



//////////  CFilter //////////

int CFilter::getVGData(char **buffer)
{
	int count;

	count =  cutOff.getVGData(buffer);
	count += reso.getVGData(buffer);
	count += touchS.getVGData(buffer);
	count += decay.getVGData(buffer);

	return count;
}



int CFilter::setVGData(char **buffer)
{
	int count;

	count =  cutOff.setVGData(buffer);
	count += reso.setVGData(buffer);
	count += touchS.setVGData(buffer);
	count += decay.setVGData(buffer);

	return count;
}


//////////  CPBend //////////

int CPBend::getVGData(char **buffer)
{
	int count;

	count =  pBend.getVGData(buffer);
	count += pBendQ.getVGData(buffer);

	return count;
}



int CPBend::setVGData(char **buffer)
{
	int count;

	count =  pBend.setVGData(buffer);
	count += pBendQ.setVGData(buffer);

	return count;
}



////////// CGlide  //////////

int CGlide::getVGData(char **buffer)
{
	int count;

	count =  gldSens.getVGData(buffer);
	count += gldTime.getVGData(buffer);

	return count;
}



int CGlide::setVGData(char **buffer)
{
	int count;

	count =  gldSens.setVGData(buffer);
	count += gldTime.setVGData(buffer);

	return count;
}



////////// CIMod  //////////

int CIMod::getVGData(char **buffer)
{
	int count;

	count =  depth.getVGData(buffer);
	count += rate.getVGData(buffer);

	return count;
}



int CIMod::setVGData(char **buffer)
{
	int count;

	count =  depth.setVGData(buffer);
	count += rate.setVGData(buffer);

	return count;
}



////////// CModC  //////////

int CModC::getVGData(char **buffer)
{
	int count;

	count =  length.getVGData(buffer);
	count += modTune.getVGData(buffer);
	count += level.getVGData(buffer);
	count += modeDep.getVGData(buffer);

	return count;
}



int CModC::setVGData(char **buffer)
{
	int count;

	count =  length.setVGData(buffer);
	count += modTune.setVGData(buffer);
	count += level.setVGData(buffer);
	count += modeDep.setVGData(buffer);


	return count;
}



////////// CDrawBar  //////////

int CDrawBar::getVGData(char **buffer)
{
	int count;

	count =  feet4.getVGData(buffer);
	count += feet8.getVGData(buffer);
	count += feet16.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	return count;
}



int CDrawBar::setVGData(char **buffer)
{
	int count;

	count =  feet4.setVGData(buffer);
	count += feet8.setVGData(buffer);
	count += feet16.setVGData(buffer);

	*buffer += 2;
	count += 2;

	return count;
}

//////////////////////////////////
//			INSTRUMENT			//
//////////////////////////////////


//////////  CVariGuitar //////////

int CVariGuitar::getVGData(char **buffer)
{
	int count;

	count =  pickup.getVGData(buffer);
	count += pitchShift.getVGData(buffer);
	count += body.getVGData(buffer);
	count += ptShiftOnOff.getVGData(buffer);

	memset(*buffer, 0, 6);
	*buffer += 6;
	count += 6;

	return count;
}



int CVariGuitar::setVGData(char **buffer)
{
	int count;

	count =  pickup.setVGData(buffer);
	count += pitchShift.setVGData(buffer);
	count += body.setVGData(buffer);
	count += ptShiftOnOff.setVGData(buffer);

	*buffer += 6;
	count += 6;

	return count;
}


void CVariGuitar::setDefaultValues()
{
	body.setDefaultValues();
	pickup.setDefaultValues();
	pitchShift.setDefaultValues();

	ptShiftOnOff.setValue(0);
}


//////////  CAcoustic //////////

int CAcoustic::getVGData(char **buffer)
{
	int count;

	count =  pickup.getVGData(buffer);
	count += body.getVGData(buffer);

	memset(*buffer, 0, 88);
	*buffer += 88;
	count += 88;

	return count;
}



int CAcoustic::setVGData(char **buffer)
{
	int count;

	count =  pickup.setVGData(buffer);
	count += body.setVGData(buffer);

	*buffer += 88;
	count += 88;

	return count;
}


void CAcoustic::setDefaultValues()
{
	pickup.setDefaultValues();
	body.setDefaultValues();
}


//////////  CNylonStrings //////////

int CNylonStrings::getVGData(char **buffer)
{
	int count;

	count =  body.getVGData(buffer);

	memset(*buffer, 0, 104);
	*buffer += 104;
	count += 104;

	return count;
}



int CNylonStrings::setVGData(char **buffer)
{
	int count;

	count =  body.setVGData(buffer);

	*buffer += 104;
	count += 104;

	return count;
}


void CNylonStrings::setDefaultValues()
{
	body.level.setValue(80);
	body.bottom.setValue(8);
	body.reso.setValue(8);
	body.size.setValue(50);
}


////////// COpenTune  //////////

int COpenTune::getVGData(char **buffer)
{
	int count;

	count =  pickup.getVGData(buffer);
	count += tune.getVGData(buffer);
	count += body.getVGData(buffer);
	count += openTuneOnOff.getVGData(buffer);

	memset(*buffer, 0, 54);
	*buffer += 54;
	count += 54;

	return count;
}



int COpenTune::setVGData(char **buffer)
{
	int count;

	count =  pickup.setVGData(buffer);
	count += tune.setVGData(buffer);
	count += body.setVGData(buffer);
	count += openTuneOnOff.setVGData(buffer);

	*buffer += 54;
	count += 54;

	return count;
}


void COpenTune::setDefaultValues()
{
	int i;

	pickup.setDefaultValues();
	body.setDefaultValues();
	tune.type.setValue(0);

	for (i = 0; i < 6; i++)
		tune.shift[i].setValue(24);
	
	openTuneOnOff.setValue(1);		// 1 = ON
}


//////////  CStrings12 //////////

int CStrings12::getVGData(char **buffer)
{
	int count;

	count =  pickup.getVGData(buffer);
	count += detune.getVGData(buffer);
	count += body.getVGData(buffer);
	count += detuneOnOff.getVGData(buffer);

	memset(*buffer, 0, 62);
	*buffer += 62;
	count += 62;

	return count;
}



int CStrings12::setVGData(char **buffer)
{
	int count;

	count =  pickup.setVGData(buffer);
	count += detune.setVGData(buffer);
	count += body.setVGData(buffer);
	count += detuneOnOff.setVGData(buffer);

	*buffer += 62;
	count += 62;

	return count;
}


void CStrings12::setDefaultValues()
{
	pickup.setDefaultValues();
	body.setDefaultValues();
	detune.detune.setValue(50);

	detuneOnOff.setValue(1);		// 1 = ON
}


////////// CPdShift  //////////

int CPdShift::getVGData(char **buffer)
{
	int count;

	count =  pickup.getVGData(buffer);
	count += pdShift.getVGData(buffer);
	count += body.getVGData(buffer);
	count += detuneOnOff.getVGData(buffer);

	memset(*buffer, 0, 54);
	*buffer += 54;
	count += 54;

	return count;
}



int CPdShift::setVGData(char **buffer)
{
	int count;

	count =  pickup.setVGData(buffer);
	count += pdShift.setVGData(buffer);
	count += body.setVGData(buffer);
	count += detuneOnOff.setVGData(buffer);

	*buffer += 54;
	count += 54;

	return count;
}


void CPdShift::setDefaultValues()
{
	int i;

	pickup.setDefaultValues();
	body.setDefaultValues();
	pdShift.pitch.setValue(36);		// 36 = +12

	for (i = 0; i < 6; i++)
		pdShift.string[i].setValue(1);	// 1 = ON

	detuneOnOff.setValue(1);		// 1 = ON
}


//////////  CPolyDist //////////

int CPolyDist::getVGData(char **buffer)
{
	int count;

	count =  pickup.getVGData(buffer);
	count += dist.getVGData(buffer);
	count += distOnOff.getVGData(buffer);

	memset(*buffer, 0, 70);
	*buffer += 70;
	count += 70;

	return count;
}



int CPolyDist::setVGData(char **buffer)
{
	int count;

	count =  pickup.setVGData(buffer);
	count += dist.setVGData(buffer);
	count += distOnOff.setVGData(buffer);

	*buffer += 70;
	count += 70;

	return count;
}


void CPolyDist::setDefaultValues()
{
	pickup.setDefaultValues();
	distOnOff.setValue(1);			// 1 = ON

	dist.mode.setValue(DIST_DS2);
	dist.drive.setValue(70);
	dist.drvBal.setValue(70);
	dist.highCut.setValue(5);		// 5 = 4.00 Hz
	dist.level.setValue(50);
	dist.polyBal.setValue(100);
}


////////// CPolyComp  //////////

int CPolyComp::getVGData(char **buffer)
{
	int count;

	count =  pickup.getVGData(buffer);
	count += comp.getVGData(buffer);
	count += compOnOff.getVGData(buffer);

	memset(*buffer, 0, 70);
	*buffer += 70;
	count += 70;

	return count;
}



int CPolyComp::setVGData(char **buffer)
{
	int count;

	count =  pickup.setVGData(buffer);
	count += comp.setVGData(buffer);
	count += compOnOff.setVGData(buffer);

	*buffer += 70;
	count += 70;

	return count;
}


void CPolyComp::setDefaultValues()
{
	pickup.setDefaultValues();
	compOnOff.setValue(1);			// 1 = ON
	comp.attack.setValue(40);
	comp.cmpBal.setValue(100);
	comp.level.setValue(50);
	comp.mode.setValue(POLYCOMP_COMP);
	comp.sustain.setValue(50);
	comp.tone.setValue(50);

	comp.release.setValue(20);
	comp.threshold.setValue(60);
}


////////// CPolyOct  //////////

int CPolyOct::getVGData(char **buffer)
{
	int count;

	count =  pickup.getVGData(buffer);
	count += octave.getVGData(buffer);
	count += ocataveOnOff.getVGData(buffer);

	memset(*buffer, 0, 46);
	*buffer += 46;
	count += 46;

	return count;
}



int CPolyOct::setVGData(char **buffer)
{
	int count;

	count =  pickup.setVGData(buffer);
	count += octave.setVGData(buffer);
	count += ocataveOnOff.setVGData(buffer);

	*buffer += 46;
	count += 46;


	return count;
}


void CPolyOct::setDefaultValues()
{
	int i;

	pickup.setDefaultValues();

	for (i = 0; i < 6; i++)
	{
		octave.Oct1[i].setValue(100);
		octave.Oct2[i].setValue(0);
		octave.dir[i].setValue(100);
	}

	ocataveOnOff.setValue(1);		// 1 = ON
}


////////// CPolySG  //////////

int CPolySG::getVGData(char **buffer)
{
	int count;

	count =  pickup.getVGData(buffer);
	count += sg.getVGData(buffer);
	count += sgOnOff.getVGData(buffer);

	memset(*buffer, 0, 82);
	*buffer += 82;
	count += 82;

	return count;
}



int CPolySG::setVGData(char **buffer)
{
	int count;

	count =  pickup.setVGData(buffer);
	count += sg.setVGData(buffer);
	count += sgOnOff.setVGData(buffer);

	*buffer += 82;
	count += 82;

	return count;
}


void CPolySG::setDefaultValues()
{
	pickup.setDefaultValues();
	sgOnOff.setValue(1);			// 1 = ON
	sg.riseTime.setValue(50);
	sg.sens.setValue(100);
}


////////// CBowed  //////////

int CBowed::getVGData(char **buffer)
{
	int count;

	count =  filter.getVGData(buffer);
	count += pBend.getVGData(buffer);
	count += sustain.getVGData(buffer);

	memset(*buffer, 0, 98);
	*buffer += 98;
	count += 98;

	return count;
}



int CBowed::setVGData(char **buffer)
{
	int count;

	count =  filter.setVGData(buffer);
	count += pBend.setVGData(buffer);
	count += sustain.setVGData(buffer);

	*buffer += 98;
	count += 98;

	return count;
}


void CBowed::setDefaultValues()
{
	filter.cutOff.setValue(80);
	filter.reso.setValue(0);
	filter.touchS.setValue(30);
	filter.decay.setValue(0);

	pBend.pBend.setValue(20);
	pBend.pBendQ.setValue(20);

	sustain.setValue(50);
}


////////// CDual  //////////

int CDual::getVGData(char **buffer)
{
	int count;

	count =  filter.getVGData(buffer);
	count += gLide.getVGData(buffer);
	count += sustain.getVGData(buffer);

	memset(*buffer, 0, 98);
	*buffer += 98;
	count += 98;

	return count;
}



int CDual::setVGData(char **buffer)
{
	int count;

	count =  filter.setVGData(buffer);
	count += gLide.setVGData(buffer);
	count += sustain.setVGData(buffer);

	*buffer += 98;
	count += 98;

	return count;
}


void CDual::setDefaultValues()
{
	filter.cutOff.setValue(60);
	filter.reso.setValue(30);
	filter.touchS.setValue(30);
	filter.decay.setValue(0);

	gLide.gldSens.setValue(50);
	gLide.gldTime.setValue(50);

	sustain.setValue(50);
}


//////////  CFilterBass //////////

int CFilterBass::getVGData(char **buffer)
{
	int count;

	count =  filter.getVGData(buffer);
	count += color.getVGData(buffer);

	memset(*buffer, 0, 102);
	*buffer += 102;
	count += 102;

	return count;
}



int CFilterBass::setVGData(char **buffer)
{
	int count;

	count =  filter.setVGData(buffer);
	count += color.setVGData(buffer);

	*buffer += 102;
	count += 102;

	return count;
}


void CFilterBass::setDefaultValues()
{
	filter.cutOff.setValue(40);
	filter.reso.setValue(50);
	filter.touchS.setValue(100);
	filter.decay.setValue(50);

	color.setValue(50);
}


//////////  CPipe //////////

int CPipe::getVGData(char **buffer)
{
	int count;

	count =  filter.getVGData(buffer);
	count += pBend.getVGData(buffer);
	count += sustain.getVGData(buffer);

	memset(*buffer, 0, 98);
	*buffer += 98;
	count += 98;

	return count;
}



int CPipe::setVGData(char **buffer)
{
	int count;

	count =  filter.setVGData(buffer);
	count += pBend.setVGData(buffer);
	count += sustain.setVGData(buffer);

	*buffer += 98;
	count += 98;

	return count;
}


void CPipe::setDefaultValues()
{
	filter.cutOff.setValue(60);
	filter.reso.setValue(50);
	filter.touchS.setValue(0);
	filter.decay.setValue(0);

	pBend.pBend.setValue(50);
	pBend.pBendQ.setValue(20);

	sustain.setValue(50);
}


////////// CSolo  //////////

int CSolo::getVGData(char **buffer)
{
	int count;

	count =  filter.getVGData(buffer);
	count += color.getVGData(buffer);
	count += sustain.getVGData(buffer);

	memset(*buffer, 0, 100);
	*buffer += 100;
	count += 100;

	return count;
}



int CSolo::setVGData(char **buffer)
{
	int count;

	count =  filter.setVGData(buffer);
	count += color.setVGData(buffer);
	count += sustain.setVGData(buffer);

	*buffer += 100;
	count += 100;


	return count;
}


void CSolo::setDefaultValues()
{
	filter.cutOff.setValue(60);
	filter.reso.setValue(5);
	filter.touchS.setValue(50);
	filter.decay.setValue(0);

	sustain.setValue(50);
	color.setValue(50);
}


////////// CPWM  //////////

int CPWM::getVGData(char **buffer)
{
	int count;

	count =  filter.getVGData(buffer);
	count += mod.getVGData(buffer);
	count += sustain.getVGData(buffer);

	memset(*buffer, 0, 98);
	*buffer += 98;
	count += 98;

	return count;
}



int CPWM::setVGData(char **buffer)
{
	int count;

	count =  filter.setVGData(buffer);
	count += mod.setVGData(buffer);
	count += sustain.setVGData(buffer);

	*buffer += 98;
	count += 98;


	return count;
}


void CPWM::setDefaultValues()
{
	filter.cutOff.setValue(80);
	filter.reso.setValue(40);
	filter.touchS.setValue(50);
	filter.decay.setValue(0);

	mod.depth.setValue(70);
	mod.rate.setValue(30);

	sustain.setValue(50);
}


//////////  CCrystal //////////

int CCrystal::getVGData(char **buffer)
{
	int count;

	count =  mod.getVGData(buffer);
	count += bodyLevel.getVGData(buffer);
	count += sustain.getVGData(buffer);

	memset(*buffer, 0, 100);
	*buffer += 100;
	count += 100;

	return count;
}



int CCrystal::setVGData(char **buffer)
{
	int count;

	count =  mod.setVGData(buffer);
	count += bodyLevel.setVGData(buffer);
	count += sustain.setVGData(buffer);

	*buffer += 100;
	count += 100;

	return count;
}



void CCrystal::setDefaultValues()
{
	mod.length.setValue(50);
	mod.modTune.setValue(100);
	mod.level.setValue(40);
	mod.modeDep.setValue(30);
	
	bodyLevel.setValue(60);
	sustain.setValue(50);
}


//////////  COrgan //////////

int COrgan::getVGData(char **buffer)
{
	int count;

	count =  drawBar.getVGData(buffer);
	count += sustain.getVGData(buffer);

	memset(*buffer, 0, 102);
	*buffer += 102;
	count += 102;

	return count;
}



int COrgan::setVGData(char **buffer)
{
	int count;

	count =  drawBar.setVGData(buffer);
	count += sustain.setVGData(buffer);

	*buffer += 102;
	count += 102;

	return count;
}



void COrgan::setDefaultValues()
{
	drawBar.feet4.setValue(70);
	drawBar.feet8.setValue(20);
	drawBar.feet16.setValue(50);

	sustain.setValue(100);
}


//////////  CBrass //////////

int CBrass::getVGData(char **buffer)
{
	int count;

	count =  filter.getVGData(buffer);
	count += sustain.getVGData(buffer);

	memset(*buffer, 0, 102);
	*buffer += 102;
	count += 102;

	return count;
}



int CBrass::setVGData(char **buffer)
{
	int count;

	count =  filter.setVGData(buffer);
	count += sustain.setVGData(buffer);

	*buffer += 102;
	count += 102;

	return count;
}



void CBrass::setDefaultValues()
{
	filter.cutOff.setValue(60);
	filter.reso.setValue(40);
	filter.touchS.setValue(50);
	filter.decay.setValue(50);

	sustain.setValue(50);
}


//////////  CNylonII //////////

int CNylonII::getVGData(char **buffer)
{
	int count;

	count =  body.getVGData(buffer);

	memset(*buffer, 0, 104);
	*buffer += 104;
	count += 104;

	return count;
}



int CNylonII::setVGData(char **buffer)
{
	int count;

	count =  body.setVGData(buffer);

	*buffer += 104;
	count += 104;

	return count;
}


void CNylonII::setDefaultValues()
{
	body.level.setValue(80);
	body.attack.setValue(8);
	body.tone.setValue(50);
	body.body.setValue(60);
}

//////////  CAssignNC //////////

int CAssignNC::getVGData(char **buffer)
{
	int count = 0;
	int i;

	for (i = 0; i < 8; i++)
		count += assignActiveRangeLo[i].getVGData(buffer);

	for (i = 0; i < 8; i++)
		count += assignActiveRangeHi[i].getVGData(buffer);

	count += expOnOff.getVGData(buffer);
	count += ctlOnOff.getVGData(buffer);
	count += gkVolOnOff.getVGData(buffer);
	count += gkS1S2OnOff.getVGData(buffer);

	for (i = 0; i < 8; i++)
		count +=  assignOnOff[i].getVGData(buffer);

	count += bpm.getVGData(buffer);
	count += level.getVGData(buffer);
	count += key.getVGData(buffer);
	count += name.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;
	
	count += chainMix.getVGData(buffer);

	for (i = 0; i < 10; i++)
		count += chain[i].getVGData(buffer);

	return count;
}



int CAssignNC::setVGData(char **buffer)
{
	int count = 0;
	int i;

	for (i = 0; i < 8; i++)
		count += assignActiveRangeLo[i].setVGData(buffer);

	for (i = 0; i < 8; i++)
		count += assignActiveRangeHi[i].setVGData(buffer);

	count += expOnOff.setVGData(buffer);
	count += ctlOnOff.setVGData(buffer);
	count += gkVolOnOff.setVGData(buffer);
	count += gkS1S2OnOff.setVGData(buffer);

	for (i = 0; i < 8; i++)
		count +=  assignOnOff[i].setVGData(buffer);

	count += bpm.setVGData(buffer);
	count += level.setVGData(buffer);
	count += key.setVGData(buffer);
	count += name.setVGData(buffer);

	*buffer += 2;
	count += 2;
	
	count += chainMix.setVGData(buffer);

	for (i = 0; i < 10; i++)
		count += chain[i].setVGData(buffer);;

	return count;
}

//////////  CEq //////////

int CEq::getVGData(char **buffer)
{
	int count;

	count =  level.getVGData(buffer);
	count += lMidG.getVGData(buffer);
	count += lowG.getVGData(buffer);
	count += highG.getVGData(buffer);
	count += hMidG.getVGData(buffer);
	count += lMidF.getVGData(buffer);
	count += lMidQ.getVGData(buffer);
	count += hMidF.getVGData(buffer);
	count += hMidQ.getVGData(buffer);

	memset(*buffer, 0, 6);
	*buffer += 6;
	count += 6;

	return count;
}


int CEq::setVGData(char **buffer)
{
	int count;

	count =  level.setVGData(buffer);
	count += lMidG.setVGData(buffer);
	count += lowG.setVGData(buffer);
	count += highG.setVGData(buffer);
	count += hMidG.setVGData(buffer);
	count += lMidF.setVGData(buffer);
	count += lMidQ.setVGData(buffer);
	count += hMidF.setVGData(buffer);
	count += hMidQ.setVGData(buffer);

	*buffer += 6;
	count += 6;

	return count;
}




//////////  CCosmPan //////////

int CCosmPan::getVGData(char **buffer)
{
	int count = 0;
	int i;

	for (i = 0; i < 6; i++)
		count +=  string[i].getVGData(buffer);

	memset(*buffer, 0, 4);
	*buffer += 4;
	count += 4;

	return count;
}


int CCosmPan::setVGData(char **buffer)
{
	int count = 0;
	int i;

	for (i = 0; i < 6; i++)
		count +=  string[i].setVGData(buffer);

	*buffer += 4;
	count += 4;

	return count;
}




//////////  CCosmMixer //////////

int CCosmMixer::getVGData(char **buffer)
{
	int count;

	count =  balance.getVGData(buffer);
	count += puPola.getVGData(buffer);
	count += level.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	return count;
}


int CCosmMixer::setVGData(char **buffer)
{
	int count;

	count =  balance.setVGData(buffer);
	count += puPola.setVGData(buffer);
	count += level.setVGData(buffer);

	*buffer += 2;
	count += 2;

	return count;
}



//////////  CCompComp //////////

int CCompComp::getVGData(char **buffer)
{
	int count;

	count =  sustain.getVGData(buffer);
	count += attack.getVGData(buffer);
	count += tone.getVGData(buffer);
	count += level.getVGData(buffer);
	
	return count;
}


int CCompComp::setVGData(char **buffer)
{
	int count;

	count =  sustain.setVGData(buffer);
	count += attack.setVGData(buffer);
	count += tone.setVGData(buffer);
	count += level.setVGData(buffer);
	
	return count;
}


//////////  CCompLim //////////

int CCompLim::getVGData(char **buffer)
{
	int count;

	count =  threshold.getVGData(buffer);
	count += release.getVGData(buffer);
	count += tone.getVGData(buffer);
	count += level.getVGData(buffer);
	
	return count;
}


int CCompLim::setVGData(char **buffer)
{
	int count;

	count =  threshold.setVGData(buffer);
	count += release.setVGData(buffer);
	count += tone.setVGData(buffer);
	count += level.setVGData(buffer);
	
	return count;
}



////////// CCompE  //////////


CCompE::CCompE()
{
	comp = NULL;
}



CCompE::~CCompE()
{
	if (comp)
		delete(comp);
}


int CCompE::getVGData(char **buffer)
{
	int count;

	count =  compType.getVGData(buffer);

	memset(*buffer, 0, 6);
	*buffer += 6;
	count += 6;

	count += comp->getVGData(buffer);

	return count;
}


int CCompE::setVGData(char **buffer)
{
	int count;

	count =  compType.setVGData(buffer);

	*buffer += 6;
	count += 6;

	if (compType.getValue() == COMP_COMP)
		comp = new CCompComp;
	else
		comp = new CCompLim;

	count += comp->setVGData(buffer);

	return count;
}



////////// CWahE  //////////

CWahE::CWahE()
{
	wah = NULL;
}


CWahE::~CWahE()
{
	if (wah)
		delete (wah);
}

int CWahE::getVGData(char **buffer)
{
	int count;

	count =  wahType.getVGData(buffer);

	memset(*buffer, 0, 6);
	*buffer += 6;
	count += 6;

	count += wah->getVGData(buffer);

	return count;
}


int CWahE::setVGData(char **buffer)
{
	int count;

	count =  wahType.setVGData(buffer);

	*buffer += 6;
	count += 6;

	if (wahType.getValue() == WAH_PEDAL)
		wah = new CPedalWah;
	else
		wah = new CAutoWah;

	count += wah->setVGData(buffer);

	return count;
}



//////////  CPedalWah //////////

int CPedalWah::getVGData(char **buffer)
{
	int count;

	count =  freq.getVGData(buffer);
	count += level.getVGData(buffer);
	count += model.getVGData(buffer);

	memset(*buffer, 0, 10);
	*buffer += 10;
	count += 10;

	return count;
}


int CPedalWah::setVGData(char **buffer)
{
	int count;

	count =  freq.setVGData(buffer);
	count += level.setVGData(buffer);
	count += model.setVGData(buffer);

	*buffer += 10;
	count += 10;

	return count;
}


void CPedalWah::setDefaultValues()
{
	freq.setValue(42);
	level.setValue(100);
	model.setValue(0);
}


//////////  CAutoWah //////////

int CAutoWah::getVGData(char **buffer)
{
	int count;

	count =  autoWahMode.getVGData(buffer);
	count += polarity.getVGData(buffer);
	count += sens.getVGData(buffer);
	count += freq.getVGData(buffer);
	count += peak.getVGData(buffer);
	count += rate.getVGData(buffer);
	count += depth.getVGData(buffer);
	count += level.getVGData(buffer);

	return count;
}

int CAutoWah::setVGData(char **buffer)
{
	int count;

	count =  autoWahMode.setVGData(buffer);
	count += polarity.setVGData(buffer);
	count += sens.setVGData(buffer);
	count += freq.setVGData(buffer);
	count += peak.setVGData(buffer);
	count += rate.setVGData(buffer);
	count += depth.setVGData(buffer);
	count += level.setVGData(buffer);

	return count;
}

void CAutoWah::setDefaultValues()
{
	autoWahMode.setValue(WAHMODE_BPF);
	polarity.setValue(WAHPOL_UP);
	sens.setValue(50);
	freq.setValue(15);
	peak.setValue(50);
	rate.setValue(50);
	depth.setValue(0);
	level.setValue(100);
}

//////////  CCosmGT //////////

int CCosmGT::getVGData(char **buffer)
{
	int count;

	count =  guitarType.getVGData(buffer);
	count += guitarOnOff.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	return count;
}


int CCosmGT::setVGData(char **buffer)
{
	int count;

	count =  guitarType.setVGData(buffer);
	count += guitarOnOff.setVGData(buffer);

	*buffer += 2;
	count += 2;

	return count;
}



//////////  CCosmAmp //////////

int CCosmAmp::getVGData(char **buffer)
{
	int count;

	count =  ampOnOff.getVGData(buffer);
	count += ampType.getVGData(buffer);

	memset(*buffer, 0, 4);
	*buffer += 4;
	count += 4;

	return count;
}


int CCosmAmp::setVGData(char **buffer)
{
	int count;

	count =  ampOnOff.setVGData(buffer);
	count += ampType.setVGData(buffer);

	*buffer += 4;
	count += 4;

	return count;
}


//////////  CAmp //////////

int CAmp::getVGData(char **buffer)
{
	int count;

	count =  volume.getVGData(buffer);
	count += presenceHighCut.getVGData(buffer);
	count += master.getVGData(buffer);
	count += bass.getVGData(buffer);
	count += middle.getVGData(buffer);
	count += trebble.getVGData(buffer);
	count += gain.getVGData(buffer);
	count += bright.getVGData(buffer);
	count += balance.getVGData(buffer);
	count += speaker.getVGData(buffer);
	count += micSet.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	return count;
}

int CAmp::setVGData(char **buffer)
{
	int count;

	count =  volume.setVGData(buffer);
	count += presenceHighCut.setVGData(buffer);
	count += master.setVGData(buffer);
	count += bass.setVGData(buffer);
	count += middle.setVGData(buffer);
	count += trebble.setVGData(buffer);
	count += gain.setVGData(buffer);
	count += bright.setVGData(buffer);
	count += balance.setVGData(buffer);
	count += speaker.setVGData(buffer);
	count += micSet.setVGData(buffer);

	*buffer += 2;
	count += 2;

	return count;
}



//////////  CHarmonist //////////

int CHarmonist::getVGData(char **buffer)
{
	int count;
	int i;

	count =  hr1OnOff.getVGData(buffer);
	count += hr1Harmony.getVGData(buffer);
	count += hr1Pan.getVGData(buffer);
	count += hr1Level.getVGData(buffer);
	count += dirLevel.getVGData(buffer);

	for (i = 0; i < 12; i++)
		count +=  hr1UserScale[i].getVGData(buffer);

	count += hr2OnOff.getVGData(buffer);
	count += hr2Harmony.getVGData(buffer);
	count += hr2Pan.getVGData(buffer);
	count += hr2Level.getVGData(buffer);

	for (i = 0; i < 12; i++)
		count +=  hr2UserScale[i].getVGData(buffer);


	memset(*buffer, 0, 6);
	*buffer += 6;
	count += 6;

	return count;
}



int CHarmonist::setVGData(char **buffer)
{
	int count;
	int i;

	count =  hr1OnOff.setVGData(buffer);
	count += hr1Harmony.setVGData(buffer);
	count += hr1Pan.setVGData(buffer);
	count += hr1Level.setVGData(buffer);
	count += dirLevel.setVGData(buffer);

	for (i = 0; i < 12; i++)
		count +=  hr1UserScale[i].setVGData(buffer);

	count += hr2OnOff.setVGData(buffer);
	count += hr2Harmony.setVGData(buffer);
	count += hr2Pan.setVGData(buffer);
	count += hr2Level.setVGData(buffer);

	for (i = 0; i < 12; i++)
		count +=  hr2UserScale[i].setVGData(buffer);


	*buffer += 6;
	count += 6;

	return count;
}


void CHarmonist::setDefaultValues()
{
	int i;

	hr1OnOff.setValue(1);				// 1 = ON
	hr1Harmony.setValue(12);			// 12 = -3rd
	hr1Pan.setValue(50);				// 50 =  50 <> 50
	hr1Level.setValue(100);
	dirLevel.setValue(100);

	for (i = 0; i < 12; i++)
		hr1UserScale[i].setValue(24);	// 24 = 0

	hr2OnOff.setValue(0);				// 0 = OFF
	hr2Harmony.setValue(16);			// 16 = +3rd
	hr2Pan.setValue(50);
	hr2Level.setValue(100);
	
	for (i = 0; i < 12; i++)
		hr2UserScale[i].setValue(24);
}


//// CPitchShifter /////////

int CPitchShifter::getVGData(char **buffer)
{
	int count;

	count =  ps1PreDly.getVGData(buffer);
	count += ps2PreDly.getVGData(buffer);
	count += ps1OnOff.getVGData(buffer);
	count += ps1Mode.getVGData(buffer);
	count += ps1Shift.getVGData(buffer);
	count += ps1Fine.getVGData(buffer);
	count += ps1Feedback.getVGData(buffer);
	count += ps1Pan.getVGData(buffer);
	count += ps1Level.getVGData(buffer);
	count += dirLevel.getVGData(buffer);
	count += ps2OnOff.getVGData(buffer);
	count += ps2Mode.getVGData(buffer);
	count += ps2Shift.getVGData(buffer);
	count += ps2Fine.getVGData(buffer);
	count += ps2Pan.getVGData(buffer);
	count += ps2Level.getVGData(buffer);
	
	memset(*buffer, 0, 36);
	*buffer += 36;
	count += 36;

	return count;
}

int CPitchShifter::setVGData(char **buffer)
{
	int count;

	count =  ps1PreDly.setVGData(buffer);
	count += ps2PreDly.setVGData(buffer);
	count += ps1OnOff.setVGData(buffer);
	count += ps1Mode.setVGData(buffer);
	count += ps1Shift.setVGData(buffer);
	count += ps1Fine.setVGData(buffer);
	count += ps1Feedback.setVGData(buffer);
	count += ps1Pan.setVGData(buffer);
	count += ps1Level.setVGData(buffer);
	count += dirLevel.setVGData(buffer);
	count += ps2OnOff.setVGData(buffer);
	count += ps2Mode.setVGData(buffer);
	count += ps2Shift.setVGData(buffer);
	count += ps2Fine.setVGData(buffer);
	count += ps2Pan.setVGData(buffer);
	count += ps2Level.setVGData(buffer);
	
	*buffer += 36;
	count += 36;

	return count;
}


void CPitchShifter::setDefaultValues()
{
	ps1OnOff.setValue(1);		// 1 = ON
	ps1Mode.setValue(PSMODE_POLY);
	ps1Shift.setValue(24);
	ps1Fine.setValue(66);
	ps1Feedback.setValue(0);
	ps1PreDly.setValue(0);
	ps1Pan.setValue(50);
	ps1Level.setValue(100);

	dirLevel.setValue(100);
	
	ps2OnOff.setValue(0);		// 0 = OFF
	ps2Mode.setValue(PSMODE_POLY);
	ps2Shift.setValue(24);
	ps2Fine.setValue(50);
	ps2PreDly.setValue(0);
	ps2Pan.setValue(50);
	ps2Level.setValue(100);
}


//////////  CFlanger //////////

int CFlanger::getVGData(char **buffer)
{
	int count;

	count =  rate.getVGData(buffer);
	count += depth.getVGData(buffer);
	count += manual.getVGData(buffer);
	count += reso.getVGData(buffer);
	count += level.getVGData(buffer);
	count += separate.getVGData(buffer);

	memset(*buffer, 0, 60);
	*buffer += 60;
	count += 60;

	return count;
}


int CFlanger::setVGData(char **buffer)
{
	int count;

	count =  rate.setVGData(buffer);
	count += depth.setVGData(buffer);
	count += manual.setVGData(buffer);
	count += reso.setVGData(buffer);
	count += level.setVGData(buffer);
	count += separate.setVGData(buffer);

	*buffer += 60;
	count += 60;

	return count;
}


void CFlanger::setDefaultValues()
{
	rate.setValue(25);
	depth.setValue(50);
	manual.setValue(75);
	reso.setValue(80);
	level.setValue(70);
	separate.setValue(0);
}

//////////  CPhaser //////////

int CPhaser::getVGData(char **buffer)
{
	int count;

	count =  rate.getVGData(buffer);
	count += depth.getVGData(buffer);
	count += manual.getVGData(buffer);
	count += reso.getVGData(buffer);
	count += level.getVGData(buffer);
	count += stage.getVGData(buffer);
	count += step.getVGData(buffer);

	memset(*buffer, 0, 58);
	*buffer += 58;
	count += 58;

	return count;
}

int CPhaser::setVGData(char **buffer)
{
	int count;

	count =  rate.setVGData(buffer);
	count += depth.setVGData(buffer);
	count += manual.setVGData(buffer);
	count += reso.setVGData(buffer);
	count += level.setVGData(buffer);
	count += stage.setVGData(buffer);
	count += step.setVGData(buffer);

	*buffer += 58;
	count += 58;

	return count;
}

void CPhaser::setDefaultValues()
{
	rate.setValue(70);
	depth.setValue(50);
	manual.setValue(55);
	reso.setValue(0);
	level.setValue(70);
	step.setValue(0);		// 0 =OFF
	stage.setValue(PHASER_4STAGE);
}


//////////  CSubEq //////////

int CSubEq::getVGData(char **buffer)
{
	int count;

	count =  level.getVGData(buffer);
	count += lMidG.getVGData(buffer);
	count += lowG.getVGData(buffer);
	count += highG.getVGData(buffer);
	count += hMidG.getVGData(buffer);
	count += lMidF.getVGData(buffer);
	count += lMidQ.getVGData(buffer);
	count += hMidF.getVGData(buffer);
	count += hMidQ.getVGData(buffer);

	memset(*buffer, 0, 54);
	*buffer += 54;
	count += 54;

	return count;
}


int CSubEq::setVGData(char **buffer)
{
	int count;

	count =  level.setVGData(buffer);
	count += lMidG.setVGData(buffer);
	count += lowG.setVGData(buffer);
	count += highG.setVGData(buffer);
	count += hMidG.setVGData(buffer);
	count += lMidF.setVGData(buffer);
	count += lMidQ.setVGData(buffer);
	count += hMidF.setVGData(buffer);
	count += hMidQ.setVGData(buffer);

	*buffer += 54;
	count += 54;

	return count;
}

void CSubEq::setDefaultValues()
{
	level.setValue(20);		// 20 = 0
	lMidG.setValue(20);
	lowG.setValue(20);
	highG.setValue(20);
	hMidG.setValue(20);
	lMidF.setValue(7);		// 7 == 550 Hz
	lMidQ.setValue(1);
	hMidF.setValue(16);		// 10 = 4 kz
	hMidQ.setValue(1);		// 0 = -20db
}


//////////  CChorus2x2 //////////

int CChorus2x2::getVGData(char **buffer)
{
	int count;

	count =  xOverf.getVGData(buffer);
	count += lowRate.getVGData(buffer);
	count += lowDepth.getVGData(buffer);
	count += lowPreDly.getVGData(buffer);
	count += lowLevel.getVGData(buffer);
	count += highRate.getVGData(buffer);
	count += highDepth.getVGData(buffer);
	count += highPreDly.getVGData(buffer);
	count += highLevel.getVGData(buffer);


	memset(*buffer, 0, 54);
	*buffer += 54;
	count += 54;

	return count;
}


int CChorus2x2::setVGData(char **buffer)
{
	int count;

	count =  xOverf.setVGData(buffer);
	count += lowRate.setVGData(buffer);
	count += lowDepth.setVGData(buffer);
	count += lowPreDly.setVGData(buffer);
	count += lowLevel.setVGData(buffer);
	count += highRate.setVGData(buffer);
	count += highDepth.setVGData(buffer);
	count += highPreDly.setVGData(buffer);
	count += highLevel.setVGData(buffer);

	*buffer += 54;
	count += 54;

	return count;
}

void CChorus2x2::setDefaultValues()
{
	xOverf.setValue(9);		// 9 = 800Hz
	lowRate.setValue(20);
	lowDepth.setValue(20);
	lowPreDly.setValue(16);	// 16 = 8.0 msec
	lowLevel.setValue(50);
	highRate.setValue(40);
	highDepth.setValue(50);
	highPreDly.setValue(8);
	highLevel.setValue(100);
}


//////////  CTremolo //////////

int CTremolo::getVGData(char **buffer)
{
	int count;

	count =  wave.getVGData(buffer);
	count += rate.getVGData(buffer);
	count += depth.getVGData(buffer);

	memset(*buffer, 0, 66);
	*buffer += 66;
	count += 66;

	return count;
}


int CTremolo::setVGData(char **buffer)
{
	int count;

	count =  wave.setVGData(buffer);
	count += rate.setVGData(buffer);
	count += depth.setVGData(buffer);

	*buffer += 66;
	count += 66;

	return count;
}


void CTremolo::setDefaultValues()
{
	wave.setValue(75);
	rate.setValue(85);
	depth.setValue(70);
}


//////////  CUniV //////////

int CUniV::getVGData(char **buffer)
{
	int count;

	
	count = rate.getVGData(buffer);
	count += depth.getVGData(buffer);
	count += level.getVGData(buffer);

	memset(*buffer, 0, 66);
	*buffer += 66;
	count += 66;

	return count;
}


int CUniV::setVGData(char **buffer)
{
	int count;

	
	count = rate.setVGData(buffer);
	count += depth.setVGData(buffer);
	count += level.setVGData(buffer);

	*buffer += 66;
	count += 66;

	return count;
}


void CUniV::setDefaultValues()
{
	level.setValue(100);
	rate.setValue(48);
	depth.setValue(82);
}


//////////  CDefretter //////////

int CDefretter::getVGData(char **buffer)
{
	int count;

	count = tone.getVGData(buffer);
	count += attack.getVGData(buffer);
	count += sens.getVGData(buffer);
	count += depth.getVGData(buffer);
	count += reso.getVGData(buffer);
	count += elevel.getVGData(buffer);
	count += dlevel.getVGData(buffer);

	memset(*buffer, 0, 58);
	*buffer += 58;
	count += 58;

	return count;
}


int CDefretter::setVGData(char **buffer)
{
	int count;

	count = tone.setVGData(buffer);
	count += sens.setVGData(buffer);
	count += attack.setVGData(buffer);
	count += depth.setVGData(buffer);
	count += reso.setVGData(buffer);
	count += elevel.setVGData(buffer);
	count += dlevel.setVGData(buffer);

	*buffer += 58;
	count += 58;

	return count;
}


void CDefretter::setDefaultValues()
{
	sens.setValue(25);
	attack.setValue(21);
	depth.setValue(40);
	reso.setValue(13);
	tone.setValue(0);
	elevel.setValue(100);
	dlevel.setValue(0);
}


//////////  CPan //////////

int CPan::getVGData(char **buffer)
{
	int count;

	count =  wave.getVGData(buffer);
	count += rate.getVGData(buffer);
	count += depth.getVGData(buffer);

	memset(*buffer, 0, 66);
	*buffer += 66;
	count += 66;

	return count;
}


int CPan::setVGData(char **buffer)
{
	int count;

	count =  wave.setVGData(buffer);
	count += rate.setVGData(buffer);
	count += depth.setVGData(buffer);

	*buffer += 66;
	count += 66;

	return count;
}


void CPan::setDefaultValues()
{
	wave.setValue(0);
	rate.setValue(85);
	depth.setValue(100);
}


//////////  CModPDShift //////////

int CModPDShift::getVGData(char **buffer)
{
	int count;

	count =  pitch.getVGData(buffer);
	count += mode.getVGData(buffer);

	memset(*buffer, 0, 66);
	*buffer += 66;
	count += 66;

	return count;
}



int CModPDShift::setVGData(char **buffer)
{
	int count;

	count =  pitch.setVGData(buffer);
	count += mode.setVGData(buffer);

	*buffer += 66;
	count += 66;

	return count;
}


void CModPDShift::setDefaultValues()
{
	pitch.setValue(36);		// 36 = +12
	mode.setValue(PDSHIFT_POLY);
}


//////////  CVibrato //////////

int CVibrato::getVGData(char **buffer)
{
	int count;

	count =  trigger.getVGData(buffer);
	count += rate.getVGData(buffer);
	count += depth.getVGData(buffer);
	count += riseTime.getVGData(buffer);


	memset(*buffer, 0, 64);
	*buffer += 64;
	count += 64;

	return count;
}


int CVibrato::setVGData(char **buffer)
{
	int count;

	count =  trigger.setVGData(buffer);
	count += rate.setVGData(buffer);
	count += depth.setVGData(buffer);
	count += riseTime.setVGData(buffer);

	*buffer += 64;
	count += 64;

	return count;
}


void CVibrato::setDefaultValues()
{
	trigger.setValue(1);	// 1 = ON
	rate.setValue(80);
	depth.setValue(15);
	riseTime.setValue(80);
}



//////////  CModE //////////

CModE::CModE()
{
	mod = NULL;
}


CModE::~CModE()
{
	if (mod)
		delete (mod);
}

int CModE::getVGData(char **buffer)
{
	int count;

	count = modeType.getVGData(buffer);

	memset(*buffer, 0, 6);
	*buffer += 6;
	count += 6;

	count += mod->getVGData(buffer);

	return count;
}



int CModE::setVGData(char **buffer)
{
	int count;

	count = modeType.setVGData(buffer);

	*buffer += 6;
	count += 6;

	switch (modeType.getValue())
	{
		case MOD_HARMONIST:
			mod = new CHarmonist;
			break;

		case MOD_PSHIFTER:
			mod = new CPitchShifter;
			break;

		case MOD_FLANGER:
			mod = new CFlanger;
			break;

		case MOD_PHASER:
			mod = new CPhaser;
			break;

		case MOD_SUBEQ:
			mod = new CSubEq;
			break;

		case MOD_2X2CHORUS:
			mod = new CChorus2x2;
			break;

		case MOD_TREMOLO:
			mod = new CTremolo;
			break;

		case MOD_PAN:
			mod = new CPan;
			break;

		case MOD_PDSHIFT:
			mod = new CModPDShift;
			break;

		case MOD_VIBRATO:
			mod = new CVibrato;
			break;

		case MOD_DEFRETTER:
			mod = new CDefretter;
			break;

		case MOD_UNIV:
			mod = new CUniV;
			break;

		default:
			mod = NULL;
	}

	if (mod)
		count += mod->setVGData(buffer);
	else
	{
		*buffer += 80 - 8;
		count = 80;
	}

	return count;
}



//////////  CDelay //////////

int CDelay::getVGData(char **buffer)
{
	int count;

	count =  dlyTime.getVGData(buffer);
	count += tapeTime.getVGData(buffer);
	count += feedback.getVGData(buffer);
	count += highCut.getVGData(buffer);
	count += dlyLev.getVGData(buffer);

	memset(*buffer, 0, 4);
	*buffer += 4;
	count += 4;

	return count;
}


int CDelay::setVGData(char **buffer)
{
	int count;

	count =  dlyTime.setVGData(buffer);
	count += tapeTime.setVGData(buffer);
	count += feedback.setVGData(buffer);
	count += highCut.setVGData(buffer);
	count += dlyLev.setVGData(buffer);

	*buffer += 4;
	count += 4;

	return count;
}



//////////  CChorus //////////

int CChorus::getVGData(char **buffer)
{
	int count;

	count =  mode.getVGData(buffer);
	count += rate.getVGData(buffer);
	count += depth.getVGData(buffer);
	count += preDly.getVGData(buffer);
	count += highCut.getVGData(buffer);
	count += cLevel.getVGData(buffer);

	memset(*buffer, 0, 4);
	*buffer += 4;
	count += 4;

	return count;
}


int CChorus::setVGData(char **buffer)
{
	int count;

	count =  mode.setVGData(buffer);
	count += rate.setVGData(buffer);
	count += depth.setVGData(buffer);
	count += preDly.setVGData(buffer);
	count += highCut.setVGData(buffer);
	count += cLevel.setVGData(buffer);

	*buffer += 4;
	count += 4;

	return count;
}



//////////  CReverb //////////

int CReverb::getVGData(char **buffer)
{
	int count;

	count =  reverbMode.getVGData(buffer);
	count += reverbTime.getVGData(buffer);
	count += lowCut.getVGData(buffer);
	count += highCut.getVGData(buffer);
	count += preDly.getVGData(buffer);
	count += revLev.getVGData(buffer);
	count += density.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	return count;
}


int CReverb::setVGData(char **buffer)
{
	int count;

	count =  reverbMode.setVGData(buffer);
	count += reverbTime.setVGData(buffer);
	count += lowCut.setVGData(buffer);
	count += highCut.setVGData(buffer);
	count += preDly.setVGData(buffer);
	count += revLev.setVGData(buffer);
	count += density.setVGData(buffer);

	*buffer += 2;
	count += 2;

	return count;
}


//////////  CNS //////////

int CNS::getVGData(char **buffer)
{
	int count;

	count =  threshold.getVGData(buffer);
	count += release.getVGData(buffer);

	return count;
}


int CNS::setVGData(char **buffer)
{
	int count;

	count =  threshold.setVGData(buffer);
	count += release.setVGData(buffer);

	return count;
}


//////////  CFV //////////

int CFV::getVGData(char **buffer)
{
	int count;

	count =  level.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;


	return count;
}


int CFV::setVGData(char **buffer)
{
	int count;

	count =  level.setVGData(buffer);

	*buffer += 2;
	count += 2;


	return count;
}



//////////  CAssign //////////

int CAssign::getVGData(char **buffer)
{
	int count;

	count =  assignTarget.getVGData(buffer);
	count += assignMin.getVGData(buffer);
	count += assignMax.getVGData(buffer);
	count += assignSource.getVGData(buffer);
	count += assignMode.getVGData(buffer);

	return count;
}


int CAssign::setVGData(char **buffer)
{
	int count;

	count =  assignTarget.setVGData(buffer);
	count += assignMin.setVGData(buffer);
	count += assignMax.setVGData(buffer);
	count += assignSource.setVGData(buffer);
	count += assignMode.setVGData(buffer);

	return count;
}



//////////  CExp //////////

int CExp::getVGData(char **buffer)
{
	int count;

	count =  expTarget.getVGData(buffer);
	count += expMin.getVGData(buffer);
	count += expMax.getVGData(buffer);

	return count;
}


int CExp::setVGData(char **buffer)
{
	int count;

	count =  expTarget.setVGData(buffer);
	count += expMin.setVGData(buffer);
	count += expMax.setVGData(buffer);

	return count;
}



//////////  CCTL //////////

int CCTL::getVGData(char **buffer)
{
	int count;

	count =  ctlTarget.getVGData(buffer);
	count += ctlMin.getVGData(buffer);
	count += ctlMax.getVGData(buffer);
	count += ctlmode.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	
	return count;
}


int CCTL::setVGData(char **buffer)
{
	int count;

	count =  ctlTarget.setVGData(buffer);
	count += ctlMin.setVGData(buffer);
	count += ctlMax.setVGData(buffer);
	count += ctlmode.setVGData(buffer);

		*buffer += 2;
	count += 2;


	return count;
}


//////////  CGKVol //////////

int CGKVol::getVGData(char **buffer)
{
	int count;

	count =  gkVolTarget.getVGData(buffer);
	count += gkVolMin.getVGData(buffer);
	count += gkVolMax.getVGData(buffer);

	return count;
}


int CGKVol::setVGData(char **buffer)
{
	int count;

	count =  gkVolTarget.setVGData(buffer);
	count += gkVolMin.setVGData(buffer);
	count += gkVolMax.setVGData(buffer);

	return count;
}

//////////  CGKS1S2 //////////

int CGKS1S2::getVGData(char **buffer)
{
	int count;

	count =  gkS1S2Target.getVGData(buffer);
	count += gkS1S2Min.getVGData(buffer);
	count += gkS1S2Max.getVGData(buffer);
	count += gkS1S2mode.getVGData(buffer);

	memset(*buffer, 0, 2);
	*buffer += 2;
	count += 2;

	return count;
}


int CGKS1S2::setVGData(char **buffer)
{
	int count;

	count =  gkS1S2Target.setVGData(buffer);
	count += gkS1S2Min.setVGData(buffer);
	count += gkS1S2Max.setVGData(buffer);
	count += gkS1S2mode.setVGData(buffer);

	*buffer += 2;
	count += 2;

	return count;
}




//////////  SYSTEM //////////

//////////  CSystem //////////

int CSystem::getVGData(char **buffer)
{
	int count;

	count =  display.getVGData(buffer);
	count += gkFunc.getVGData(buffer);
	count += global.getVGData(buffer);
	count += tuner.getVGData(buffer);
	count += outputSelect.getVGData(buffer);
	count += driver.getVGData(buffer);
	count += pedal.getVGData(buffer);
	count += dial.getVGData(buffer);
	
	return count;
}


int CSystem::setVGData(char **buffer)
{
	int count;

	count =  display.setVGData(buffer);
	count += gkFunc.setVGData(buffer);
	count += global.setVGData(buffer);
	count += tuner.setVGData(buffer);
	count += outputSelect.setVGData(buffer);
	count += driver.setVGData(buffer);
	count += pedal.setVGData(buffer);
	count += dial.setVGData(buffer);
	
	return count;
}


//////////  CVG88_GKFunc //////////

int CVG88_GKFunc::getVGData(char **buffer)
{
	int count;

	count =  downS1S2.getVGData(buffer);
	count +=  synthVol.getVGData(buffer);

	return count;
}


int CVG88_GKFunc::setVGData(char **buffer)
{
	int count;

	count =  downS1S2.setVGData(buffer);
	count +=  synthVol.setVGData(buffer);

	return count;
}


//////////  CVG88_Global //////////

int CVG88_Global::getVGData(char **buffer)
{
	int count;

	count =  OnOff.getVGData(buffer);
	count +=  lowG.getVGData(buffer);
	count +=  highG.getVGData(buffer);
	count +=  NS.getVGData(buffer);
	count +=  reverb.getVGData(buffer);

	memset(*buffer, 0, 3);
	*buffer += 3;
	count += 3;

	return count;
}


int CVG88_Global::setVGData(char **buffer)
{
	int count;

	count =  OnOff.setVGData(buffer);
	count +=  lowG.setVGData(buffer);
	count +=  highG.setVGData(buffer);
	count +=  NS.setVGData(buffer);
	count +=  reverb.setVGData(buffer);

	*buffer += 3;
	count += 3;

	return count;
}


//////////  CVG88_Tuner //////////

int CVG88_Tuner::getVGData(char **buffer)
{
	int count;

	count =  pitch.getVGData(buffer);
	count +=  mute.getVGData(buffer);

	return count;
}


int CVG88_Tuner::setVGData(char **buffer)
{
	int count;

	count =  pitch.setVGData(buffer);
	count +=  mute.setVGData(buffer);

	return count;
}


//////////  CVG88_DriverSettings //////////

int CVG88_DriverSettings::getVGData(char **buffer)
{
	int count;
	int i;

	count =  type.getVGData(buffer);
	count += direction.getVGData(buffer);
	count += scale.getVGData(buffer);
	count += GtPuPhase.getVGData(buffer);
	count += S1S2Pos.getVGData(buffer);
	count += name.getVGData(buffer);

	memset(*buffer, 0, 1);
	*buffer += 1;
	count += 1;
	
	for (i = 0; i < 6; i++)
		count += PUBrige[i].getVGData(buffer);

	for (i = 0; i < 6; i++)
		count += sensitivity[i].getVGData(buffer);

	count += gkConnect.getVGData(buffer);

	memset(*buffer, 0, 1);
	*buffer += 1;
	count += 1;

	return count;
}

int CVG88_DriverSettings::setVGData(char **buffer)
{
	int count;
	int i;

	count =  type.setVGData(buffer);
	count += direction.setVGData(buffer);
	count += scale.setVGData(buffer);
	count += GtPuPhase.setVGData(buffer);
	count += S1S2Pos.setVGData(buffer);
	count += name.setVGData(buffer);

	*buffer += 1;
	count += 1;

	for (i = 0; i < 6; i++)
		count += PUBrige[i].setVGData(buffer);

	for (i = 0; i < 6; i++)
		count += sensitivity[i].setVGData(buffer);

	count += gkConnect.getVGData(buffer);

	*buffer += 1;
	count += 1;

	return count;
}


//////////  CVG88_Driver //////////

int CVG88_Driver::getVGData(char **buffer)
{
	int count;
	int i;

	count =  setting.getVGData(buffer);

	memset(*buffer, 0, 3);
	*buffer += 3;
	count += 3;

	for (i = 0; i < 5; i++)
		count += settings[i].getVGData(buffer);

	return count;
}


int CVG88_Driver::setVGData(char **buffer)
{
	int count;
	int i;

	count =  setting.setVGData(buffer);

	*buffer += 3;
	count += 3;

	for (i = 0; i < 5; i++)
		count += settings[i].setVGData(buffer);

	return count;
}


//////////  CVG88_SettingPedal //////////

int CVG88_Pedal::getVGData(char **buffer)
{
	int count;

	count = bankSwMode.getVGData(buffer);
	count += bankAreaMin.getVGData(buffer);
	count += bankAreaMax.getVGData(buffer);
	count += subCtl1.getVGData(buffer);
	count += subCtl2.getVGData(buffer);
	count += ExpGkVolHold.getVGData(buffer);
	count += expPedalCalibrationRelease.getVGData(buffer);
	count += expPedalCalibrationPress.getVGData(buffer);

	return count;
}


int CVG88_Pedal::setVGData(char **buffer)
{
	int count;

	count = bankSwMode.setVGData(buffer);
	count += bankAreaMin.setVGData(buffer);
	count += bankAreaMax.setVGData(buffer);
	count += subCtl1.setVGData(buffer);
	count += subCtl2.setVGData(buffer);
	count += ExpGkVolHold.setVGData(buffer);
	count += expPedalCalibrationRelease.setVGData(buffer);
	count += expPedalCalibrationPress.setVGData(buffer);

	return count;
}

//// CVG88SysEx /////////

CVG88SysEx::CVG88SysEx()
{
	vgSystem = NULL;
	firstPatchNumber = 0;
	deviceId = 1;
	data1 = NULL;
	modified = true;
	newLibrary = TRUE;
}

BOOL CVG88SysEx::getPatchLabel(int patchNumber, char *label)
{
	int bank;
	int num;
	CPatch *patch;
	POSITION pos;
	char name[9];

	pos = patchList.FindIndex(patchNumber);

	patchNumber += firstPatchNumber;
	
	if (!pos)
	{
		return FALSE;
	}

	patch = (CPatch *) patchList.GetAt(pos);

	bank = patchNumber / 4;
	num = patchNumber % 4;
	patch->assignNC.name.getString(name);

	sprintf(label, "%2d - %d    %s", bank + 1, num + 1, name);

	if (patch->modified)
		strcat(label, "   (M)");

	return TRUE;
}


CVG88SysEx::~CVG88SysEx()
{
	if (vgSystem != NULL)
		delete vgSystem;

	emptyPatchList();
}


void CVG88SysEx::emptyPatchList()
{
	CPatch		*patch;

	if (patchList.GetCount() > 0)
	{
		int i;
		int count = patchList.GetCount();

		for (i = 0; i < count; i++)
		{
			patch = (CPatch *) patchList.RemoveHead();

			delete patch;
		}
	}
}

int CVG88SysEx::getVGData(char **buffer)
{
	int			count;
	int			patchCount;
	int			i;
	CPatch		*patch;
	POSITION	position;


	// Get system data
	//if (vgSystem)
	//	count += vgSystem->getVGData(buffer);

	// Get Patch Data

	count = 0;

	patchCount = patchList.GetCount();
	
	position = patchList.GetHeadPosition();

	for (i = 0; i < patchCount; i++)
	{
		patch = (CPatch *) patchList.GetNext(position);
		count += getVGData(buffer, patch, i + firstPatchNumber);
	}

	return count;
}


int CVG88SysEx::getVGData(char **buffer, CPatch *patch, int patchNum)
{
	int			count;
	int			j, k;
	char		patchBuffer[1024];
	char		*pBuffer;
	int			length;
	int			blocLength;
	int			blocCount;
	int			checksum;

	// Get Patch Data

	count = 0;

	pBuffer = patchBuffer;
	length = patch->getVGData(&pBuffer);
	blocCount = length / 128;

	for (j = 0; j <= blocCount; j++)
	{
		if (j < blocCount)
			blocLength = 128;
		else
			blocLength = length - (blocCount * 128);

		(*buffer)[0] = '\xF0';
		(*buffer)[1] = '\x41';
		(*buffer)[2] = g_settings.devices[0].deviceID - 1;
		(*buffer)[3] = '\x00';
		(*buffer)[4] = '\x27';
		(*buffer)[5] = '\x12';
		(*buffer)[6] = '\x0C';
		(*buffer)[7] = patchNum;
		(*buffer)[8] = j;
		(*buffer)[9] = '\x00';

		*buffer += 10;

		memcpy(*buffer, &patchBuffer[j * 128], blocLength);
		*buffer += blocLength;

		checksum = 12 + patchNum + j;

		for (k = 0; k < blocLength; k++)
				checksum += patchBuffer[(j *128) + k];

		checksum = 128 - (checksum % 128);

		(*buffer)[0] = checksum;
		(*buffer)[1] = '\xF7';

		*buffer += 2;
			count += 10 + blocLength + 2;
	}

	return count;
}


/*
int CVG88SysEx::getVGData(char **buffer)
{
	CPatch		*patch;
	int			count;
	int			patchCount;
	int			i, j, k;
	char		patchBuffer[1024];
	char		*pBuffer;
	int			length;
	int			blocLength;
	int			blocCount;
	int		checksum;
	POSITION	position;
	
	// Get system data

	// Get Patch Data

	patchCount = patchList.GetCount();
	count = 0;

	position = patchList.GetHeadPosition();

	
	patch = (CPatch *) patchList.GetNext(position);

	pBuffer = patchBuffer;
	length = patch->getVGData(&pBuffer);

	for (i = 193; i < 255; i++)
	{
		blocCount = length / 128;

		for (j = 0; j <= blocCount; j++)
		{
			if (j < blocCount)
				blocLength = 128;
			else
				blocLength = length - (blocCount * 128);

			(*buffer)[0] = '\xF0';
			(*buffer)[1] = '\x41';
			(*buffer)[2] = 0; //deviceId;
			(*buffer)[3] = '\x00';
			(*buffer)[4] = '\x27';
			(*buffer)[5] = '\x12';
			(*buffer)[6] = '\x0D';
			(*buffer)[7] = i;
			(*buffer)[8] = j;
			(*buffer)[9] = '\x00';

			*buffer += 10;

			memcpy(*buffer, &patchBuffer[j * 128], blocLength);
			*buffer += blocLength;

			checksum = 12 + i + firstPatchNumber + j;

			for (k = 0; k < blocLength; k++)
					checksum += patchBuffer[(j *128) + k];

			checksum = 128 - (checksum % 128);

			(*buffer)[0] = checksum;
			(*buffer)[1] = '\xF7';

			*buffer += 2;

			count += 10 + blocLength + 2;
		}
	}

	return count;
}
*/


int CVG88SysEx::setVGData(char **buffer)
{
	char	addressMSBHigh;
	char	addressMSBLow;
	char	addressLSBHigh;
	char	addressLSBLow;
	int		previousPatchNumber = -1;
	char	bloc[256];
	char	message[1204];
	int		posBloc, posMessage;
	CPatch	*patch;
	char	*posBuffer;

	emptyPatchList();
	posMessage = 0;
	
	while (*buffer[0] == '\xF0')
	{
		addressMSBHigh = (*buffer)[6];
		addressMSBLow  = (*buffer)[7];
		addressLSBHigh = (*buffer)[8];
		addressLSBLow  = (*buffer)[9];

		*buffer += 10;
		posBloc = 0;

		while ((*buffer)[posBloc + 1] != '\xF7' && posBloc < 1024)
		{
			bloc[posBloc] = (*buffer)[posBloc];
			posBloc++;
		}
	
		if (posBloc == 1024)
			return -1;

		*buffer += posBloc + 2;

		memcpy(&message[posMessage], bloc, posBloc);

		switch (addressMSBHigh)
		{
			// DISPLAY
			case '\x00':
				break;

			// GK FUNK
			case '\x01':
				break;

			// GLOBAL
			case '\x02':
				break;

			// TUNER
			case '\x03':
				break;

			// OUTPUT SELECT
			case '\x04':
				break;

			// SYSTEM
			case '\x09':
				if (addressLSBHigh == 7)
				{
					vgSystem = new CSystem;

					posBuffer = message;
					vgSystem->setVGData(&posBuffer);
					
					posMessage = 0;
					posBloc = 0;
				}

				break;

			// USER PATCH
			case '\x0C':
				if (previousPatchNumber == -1)
					firstPatchNumber = addressMSBLow;

				if (addressLSBHigh == 5)
				{
					// Insert a new patch
					patch = new CPatch;

					if (message[162] * 16 + message[163] > 18)
					{
						posBloc = posBloc;
					}

					patch->cosmGT.guitarType.m_needSaving = FALSE;
					patch->cosmGT.guitarType.setValue(message[162] * 16 + message[163]);
					patch->cosmGT.guitarType.m_needSaving = TRUE;
					patch->patchNum = addressMSBLow;

				
					posBuffer = message;
					patch->setVGData(&posBuffer);

					patchList.AddTail(patch);

					posMessage = 0;
					posBloc = 0;
				}
				
				previousPatchNumber = addressMSBLow;

				break;
		}

		posMessage += posBloc;
	}
	
	return 0;
}


int CVG88SysEx::SendPatch(HMIDIOUT hMidiOut, int firstPatch, int lastPatch, int targetPatch, bool onlyModified)
{
	MIDIHDR midiHdr;
	char buffer[175000];
	char *ptrBuf;
	int patchCount;
	int i, led = 0;
	CSendPatch sendPatchDlg;
	POSITION	position;
	CPatch		*patch;	

	midiHdr.lpData = (LPSTR) buffer;
	
	midiHdr.dwUser = 0;
	midiHdr.dwFlags = 0;
	char name[255];

	patchCount = patchList.GetCount();

	if (patchCount < 1)
		return 0;

	sendPatchDlg.m_modeReceive = FALSE;	
	sendPatchDlg.Create(CSendPatch::IDD);

	position = patchList.GetHeadPosition();

	for (i = 1; i <= firstPatch; i++)
		patch = (CPatch *) patchList.GetNext(position);

	for (i = firstPatch; i <= lastPatch; i++)
	{
		if (sendPatchDlg.IsCanceled())
			break;

		patch = (CPatch *) patchList.GetNext(position);

//	patch->assignNC.name.getString(name);
//	MessageBox(NULL, name, name, MB_OK);
		
		if (!onlyModified || patch->modified)
		{
			ptrBuf = buffer;
			led = 1 - led;
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_sendMidiData.setValue(led);
			((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_assignMidiLed.RedrawWindow();
		
			midiHdr.dwBytesRecorded = getVGData(&ptrBuf, patch, i + targetPatch);
			midiHdr.dwBufferLength = midiHdr.dwBytesRecorded;
			midiOutPrepareHeader(hMidiOut, &midiHdr, sizeof(MIDIHDR));

			patch->assignNC.name.getString(name);
			sendPatchDlg.SetInfo(CString(name), i + 1, patchCount);
	
			midiOutLongMsg(hMidiOut, &midiHdr, sizeof(MIDIHDR));

			midiOutUnprepareHeader(hMidiOut, &midiHdr, sizeof(MIDIHDR));

			Sleep(100);
		}		
	}

	((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_sendMidiData.setValue(0);
	((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_assignMidiLed.RedrawWindow();

	return 0;
}


int CVG88SysEx::SendAuditionPatch(HMIDIOUT hMidiOut)
{
	MIDIHDR midiHdr;
	char buffer[175000];
	char *ptrBuf;
	CPatch		*patch;
	DWORD message;
	int midiPatchNumber;
	int midiPatchOffset;

	if (!g_currentPatch)
		return 0;

	if ((libraryType == LIB_PRESET || libraryType == LIB_USER) && !g_currentPatch->modified)
	{
		midiPatchNumber = (g_currentPatchNumber + g_currentLibrary->firstPatchNumber) % 100;
		midiPatchOffset = (g_currentPatchNumber + g_currentLibrary->firstPatchNumber) / 100;

		message = MAKELONG(MAKEWORD(176, 0), MAKEWORD(midiPatchOffset, 0));
		midiOutShortMsg(((CMainFrame *) AfxGetMainWnd())->m_hmo[0], message);

		message = MAKELONG(MAKEWORD(192, midiPatchNumber), MAKEWORD(0, 0));
		midiOutShortMsg(((CMainFrame *) AfxGetMainWnd())->m_hmo[0], message);

		return 0;
	}

	midiHdr.dwUser = 0;
	midiHdr.dwFlags = 0;

	if (!g_currentPatch)
		return 0;

	ptrBuf = buffer;
	patch = g_currentPatch;

	if (((CMainFrame *) AfxGetMainWnd())->m_chainWnd.m_compareOnOffData.getValue() && g_currentPatch->bufferCompare != NULL)
	{
		midiHdr.lpData = g_currentPatch->bufferCompare;
		midiHdr.dwBytesRecorded = VG88_PATCHSIZE;
	}
	else
	{
		midiHdr.lpData = (LPSTR) buffer;
		midiHdr.dwBytesRecorded = getVGData(&ptrBuf, g_currentPatch, g_settings.devices[0].auditionPatch);
	}

	midiHdr.dwBufferLength = midiHdr.dwBytesRecorded;
	midiHdr.dwFlags = 0;
	midiOutPrepareHeader(hMidiOut, &midiHdr, sizeof(MIDIHDR));

	midiOutLongMsg(hMidiOut, &midiHdr, sizeof(MIDIHDR));
	midiOutUnprepareHeader(hMidiOut, &midiHdr, sizeof(MIDIHDR));

	Sleep(100);

	return 0;
}


int CVG88SysEx::save()
{
	char buffer[175000];
	char *ptrBuf;
	int count;
	POSITION	position;
	CPatch		*patch;	
	int		i;
	int patchCount;

	if (!modified)
	{
		MessageBox(AfxGetMainWnd()->m_hWnd, "Nothing to save", "VEditor", MB_OK);

		return 0;
	}

	ptrBuf = buffer;
	count = getVGData(&ptrBuf);

	CFileException		e;
	CFile				fileParam;
	
	// Open the file
	if (!fileParam.Open(file, CFile::modeWrite | CFile::modeCreate, &e))
		return 0;

	fileParam.Write(buffer, count);

	fileParam.Close();
	modified = false;
	newLibrary = FALSE;

	HTREEITEM item;
	CTreeCtrl *tree = &((CMainFrame *) AfxGetMainWnd())->m_libTreeWnd.m_libraryTree;

	item = GetTreeItem();

	if (item)
		tree->SetItemText(item, GetLibraryName());

	// Reset modified flag for each patch
	patchCount = patchList.GetCount();
	position = patchList.GetHeadPosition();

	for (i = 0; i < patchCount; i++)
	{
		patch = (CPatch *) patchList.GetNext(position);
		patch->modified = false;
		if (patch->bufferCompare)
		{
			free(patch->bufferCompare);
			patch->bufferCompare = NULL;
		}
	}

	char label[256];
	i = 0;

	item = GetTreeItem();
	item = tree->GetChildItem(item);

	while (item)
	{
		getPatchLabel(i++, label);
		tree->SetItemText(item, label);

		item = tree->GetNextItem(item, TVGN_NEXT);
	}

	if (data1)
	{
		((CVGWindow *) data1)->OnNcPaint();
		((CVGWindow *) data1)->AttachLibrary(this);
	}

	return 0;
}


HTREEITEM CVG88SysEx::GetTreeItem()
{
	HTREEITEM item;
	CTreeCtrl *tree;

	tree = &(((CMainFrame *) AfxGetMainWnd())->m_libTreeWnd.m_libraryTree);
	item = tree->GetRootItem();

	while (item)
	{
		if ((CVG88SysEx *) (tree->GetItemData(item)) == this)
			return item;

		item = tree->GetNextItem(item, TVGN_NEXT);
	}

	return NULL;
}


HTREEITEM CVG88SysEx::GetTreePatchItem(CPatch *patch)
{
	HTREEITEM item;
	CTreeCtrl *tree;

	tree = &(((CMainFrame *) AfxGetMainWnd())->m_libTreeWnd.m_libraryTree);
	item = GetTreeItem();

	item = tree->GetChildItem(item);

	while (item)
	{
		if ((CPatch *) (tree->GetItemData(item)) == patch)
			return item;

		item = tree->GetNextItem(item, TVGN_NEXT);
	}

	return NULL;
}


void CVG88SysEx::SetModifiedFlag()
{
	HTREEITEM item;
	CTreeCtrl *tree;

	if (!modified)
	{
		tree = &((CMainFrame *) AfxGetMainWnd())->m_libTreeWnd.m_libraryTree;

		modified = true;
		item = GetTreeItem();

		if (item)
			tree->SetItemText(item, tree->GetItemText(item) + "  ( Modified )");

		if (data1)
		{
			((CVGWindow *) data1)->OnNcPaint();
		}

	}

	if (g_currentPatch && !g_currentPatch->modified)
	{
		char *buffer;

		g_currentPatch->bufferCompare = (char *) malloc(sizeof(char) * VG88_PATCHSIZE);
		buffer = g_currentPatch->bufferCompare;
		int count = g_currentLibrary->getVGData(&buffer, g_currentPatch, g_settings.devices[0].auditionPatch);
		g_currentPatch->modified = true;

		tree = &((CMainFrame *) AfxGetMainWnd())->m_libTreeWnd.m_libraryTree;
		item = GetTreePatchItem(g_currentPatch);

		if (item)
		{
			char name[20];

			getPatchLabel(g_currentPatchNumber, name);
			tree->SetItemText(item, name);
		}
	}
}

CString CVG88SysEx::GetLibraryName()
{
	char buffer[1024];
	char *libraryName;

	if (libraryType == LIB_USER)
		return CString("VG-88 USER");
	else if (libraryType == LIB_PRESET)
		return CString("VG-88 PRESET");

	// Remove the path and the .syx extension from the name
	strcpy(buffer, file);
	buffer[strlen(buffer) - 4] = 0;
	libraryName = strrchr(buffer, '\\');

	if (libraryName)
		libraryName = libraryName + 1;
	else
		libraryName = buffer;

	return CString(libraryName);
}