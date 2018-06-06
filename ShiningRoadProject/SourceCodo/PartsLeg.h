#pragma once


#include "PartsBase.h"


class clsPARTS_LEG : public clsPARTS_BASE
{
public:
	clsPARTS_LEG();
	~clsPARTS_LEG();

	//�X�e�[�^�X�ϐ��̓Y����.
	enum enSTATUS : PARTS_STATUS_TYPE
	{
		HP = 0,		//�̗�.
		WALK_SPD,	//���s���x.
		STABILITY,	//���萫�\.
		JUMP_POWER,	//�W�����v��.
						
		size
	};


private:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	void CreateProduct() final;//�e�V�[����Create.
	void UpdateProduct() final;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.



};

