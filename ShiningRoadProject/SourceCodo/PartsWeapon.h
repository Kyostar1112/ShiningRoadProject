#pragma once

#include "PartsBase.h"


class clsPARTS_WEAPON : public clsPARTS_BASE
{
public:
	clsPARTS_WEAPON();
	~clsPARTS_WEAPON();

	//�X�e�[�^�X�ϐ��̓Y����.
	enum enSTATUS : PARTS_STATUS_TYPE
	{
		ATK = 0,			//�U����.
		BULLET_SPD,			//�e��.
		RANGE,				//�˒�����.
		COST,				//����G�l���M�[.
		LOAD_TIME,			//���U����.
		LOCK_SPD,			//���b�N���x.
		LOCK_RANGE,			//���b�N����.

		REACTION,			//�ˌ�����.
		ACCURACY,			//�ˌ����x.
		MAGAZINE_LOAD_TIME,	//�}�K�W�����U����.
		BULLETS_NUM,		//���e��.
						
		MAX
	};



private:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	void CreateProduct() final;//�e�V�[����Create.
	void UpdateProduct() final;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.


};

