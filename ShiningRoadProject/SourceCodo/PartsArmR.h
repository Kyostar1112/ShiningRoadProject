#ifndef PARTS_ARM_R_H_
#define PARTS_ARM_R_H_


#include "PartsArmBase.h"


class clsPARTS_ARM_R : public clsPARTS_ARM_BASE
{
public:
	clsPARTS_ARM_R();
	~clsPARTS_ARM_R();

private:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	void CreateProduct() final;//�e�V�[����Create.
	void UpdateProduct() final;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.

};

#endif//#ifndef PARTS_ARM_R_H_