#ifndef FACTORY_PARTS_H_
#define FACTORY_PARTS_H_



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

	//�p�[�c��f���o��.
	clsPARTS_BASE* Create( const enPARTS enParts );

};

#endif//#ifndef FACTORY_PARTS_H_