#ifndef PARTS_ARM_L_H_
#define PARTS_ARM_L_H_


#include "PartsArmBase.h"



class clsPARTS_ARM_L : public clsPARTS_ARM_BASE
{
public:
	clsPARTS_ARM_L();
	~clsPARTS_ARM_L();

private:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	void CreateProduct() final;//�e�V�[����Create.
	void UpdateProduct() final;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.

};

#endif//#ifndef PARTS_ARM_L_H_