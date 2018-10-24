#ifndef PARTS_HEAD_H_
#define PARTS_HEAD_H_


#include "PartsBase.h"



class clsPARTS_HEAD : public clsPARTS_BASE
{
public:
	clsPARTS_HEAD();
	~clsPARTS_HEAD();

	enum enSTATUS : PARTS_STATUS_TYPE
	{
		HP = 0,	//�̗�.

		SEARCH,		//���G���\.
		LOCK_ON_SPEED,	//���b�N���x.
		LOCK_ON_RANGE,	//���b�N����.

		COL_SIZE,	//�����蔻��T�C�Y.

		size
	};



private:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	void CreateProduct() final;//�e�V�[����Create.
	void UpdateProduct() final;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.


};

#endif//#ifndef PARTS_HEAD_H_