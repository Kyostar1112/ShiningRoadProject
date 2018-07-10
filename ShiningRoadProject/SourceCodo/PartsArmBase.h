#pragma once


#include "PartsBase.h"



class clsPARTS_ARM_BASE : public clsPARTS_BASE
{
public:
	clsPARTS_ARM_BASE();
	virtual ~clsPARTS_ARM_BASE();


	//�X�e�[�^�X�ϐ��̓Y����.
	enum enSTATUS : PARTS_STATUS_TYPE
	{
		HP = 0,	//�̗�.
		AIMING,	//�Ə����x( �G�C�� ).
						
		COL_SIZE,	//�����蔻��T�C�Y.

		size
	};


private:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	virtual void CreateProduct() override;//�e�V�[����Create.
	virtual void UpdateProduct() override;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.


};

