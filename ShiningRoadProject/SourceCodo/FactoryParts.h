#pragma once


#include "PartsLeg.h"
#include "PartsCore.h"
#include "PartsHead.h"
//#include "PartsArms.h"
#include "PartsArmL.h"
#include "PartsArmR.h"
#include "PartsWeapon.h"

//�t���O�ɉ����ăp�[�c��f���o���N���X.
class clsFACTORY_PARTS
{
public:
//	clsFACTORY_PARTS();
//	~clsFACTORY_PARTS();

	//�p�[�c��f���o��.
	clsPARTS_BASE* Create( const enPARTS enParts );

};

