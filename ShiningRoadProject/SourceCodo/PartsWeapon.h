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
		STABILITY,			//�ˌ�����.
		MAGAZINE_LOAD_TIME,	//�}�K�W�����U����.
		BULLETS_NUM,		//���e��.

		COL_SIZE,	//�e�̓����蔻��T�C�Y.
		EFC_BULLET,	//�e�{�̂̃G�t�F�N�g.
		EFC_LOCUS,	//�e�̋O�Ղ̃G�t�F�N�g.
		EFC_HIT,	//���e�̃G�t�F�N�g.
		SE_FIER,	//����SE.
		SE_HIT,		//���e��SE.

		size
	};



private:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	void CreateProduct() final;//�e�V�[����Create.
	void UpdateProduct() final;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.


};

