#ifndef FACTORY_PARTS_H_
#define FACTORY_PARTS_H_



#include "PartsLeg.h"
#include "PartsCore.h"
#include "PartsHead.h"
//#include "PartsArms.h"
#include "PartsArmL.h"
#include "PartsArmR.h"
#include "PartsWeapon.h"

//フラグに応じてパーツを吐き出すクラス.
class clsFACTORY_PARTS
{
public:

	//パーツを吐き出す.
	clsPARTS_BASE* Create( const enPARTS enParts );

};

#endif//#ifndef FACTORY_PARTS_H_