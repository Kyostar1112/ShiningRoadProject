#ifndef ASSEMBLE_MODEL_BONE_POSITIONS_H_
#define ASSEMBLE_MODEL_BONE_POSITIONS_H_

#include "Global.h"


//----- �� -----//.
//��_�̃{�[����.
#define sBONE_NAME_LEG_POSITION_BASE "PositionBase"
//�A�������̃{�[����.
#define sBONE_NAME_LEG_TO_CORE		"JunctionCore"
//���̗�( 0 �` x ).
#define sBONE_NAME_LEG_SOLE			"Sole"
//�A�������̃{�[����.
#define sBONE_NAME_LEG_TO_CORE		"JunctionCore"

//----- �R�A -----//.
//���f���̒��S.
#define sBONE_NAME_CORE_JENERATOR	"Jenerator"
//�A�������̃{�[����.
#define sBONE_NAME_CORE_TO_HEAD		"JunctionHead"
#define sBONE_NAME_CORE_TO_ARM_L	"JunctionArmL"
#define sBONE_NAME_CORE_TO_ARM_R	"JunctionArmR"

//----- �� -----//.
#define sBONE_NAME_HEAD_CENTER		"Center"

//----- �r -----//.
//�u�[�X�^�[( 00 �` xx ).
#define sBONE_NAME_FRONT_ROOT		"BoosterFrontRoot"
#define sBONE_NAME_FRONT_END		"BoosterFrontEnd"
#define sBONE_NAME_BACK_ROOT		"BoosterBackRoot"
#define sBONE_NAME_BACK_END			"BoosterBackEnd"
#define sBONE_NAME_SIDE_ROOT		"BoosterSideRoot"
#define sBONE_NAME_SIDE_END			"BoosterSideEnd"
//�A�������̃{�[����.
#define sBONE_NAME_ARM_TO_WEAPON	"JunctionWeapon"
//����̉�]���m��Ɏg��.
#define sBONE_NAME_ARM_WEAPON_VEC_ROOT	 sBONE_NAME_ARM_TO_WEAPON	
#define sBONE_NAME_ARM_WEAPON_VEC_END	 "WeaponVec"		

//----- ���� -----//.
#define sBONE_NAME_WEAPON_MUZZLE_ROOT	"MuzzleRoot"
#define sBONE_NAME_WEAPON_MUZZLE_END	"MuzzleEnd"
#define sBONE_NAME_WEAPON_CARTRIDGE_INJECTION "CartridgeInjection"



//----- �S�p�[�c���� -----//.
#define sBONE_NAME_NULL			"null"


//----- �r�ƃR�A���� -----//.
//�u�[�X�^�[( 00 �` xx ).
#define sBONE_NAME_BOOSTER_ROOT	"BoosterRoot"
#define sBONE_NAME_BOOSTER_END	"BoosterEnd"

//----- �r�Ƙr���� -----//.
//�֐�( 00 �` xx ).
#define sBONE_NAME_JOINT		"Joint"


class clsASSEMBLE_MODEL_BONE_POSITIONS
{
public:
	clsASSEMBLE_MODEL_BONE_POSITIONS();
	~clsASSEMBLE_MODEL_BONE_POSITIONS();

	enum enPARTS_INDEX : int
	{
		enPARTS_INDEX_LEG = 0,
		enPARTS_INDEX_CORE,
		enPARTS_INDEX_HEAD,
		enPARTS_INDEX_ARM_L,
		enPARTS_INDEX_ARM_R,
		enPARTS_INDEX_WEAPON_L,
		enPARTS_INDEX_WEAPON_R,

		enPARTS_INDEX_size
	};


private:

};

#endif//#ifndef ASSEMBLE_MODEL_BONE_POSITIONS_H_