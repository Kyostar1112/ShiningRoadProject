#pragma once


#include "PartsBase.h"



class clsPARTS_CORE : public clsPARTS_BASE
{
public:
	clsPARTS_CORE();
	~clsPARTS_CORE();


	//�X�e�[�^�X�ϐ��̓Y����.
	enum enSTATUS : PARTS_STATUS_TYPE
	{
		HP = 0,			//�̗�.
		EN_CAPA,		//�G�l���M�[�e�� �G�l���M�[ : energy  �e�� : capacity.
		EN_OUTPUT,		//�G�l���M�[�o��( �񕜗� ).
		BOOST_THRUST_H,	//�u�[�X�^�[����( ���� ).Horizontal
		BOOST_COST_H,	//�u�[�X�^�[����G�l���M�[( ���� ).
		BOOST_THRUST_V,	//�u�[�X�^�[����( ���� ).vertical
		BOOST_COST_V,	//�u�[�X�^�[����G�l���M�[( ���� ).
		QUICK_THRUST,	//�N�C�b�N����.
		QUICK_COST,		//�N�C�b�N����G�l���M�[.
		QUICK_TIME,		//�N�C�b�N���ˎ���.
		ACT_TIME,		//��������(ActivityTime).
						
		COL_SIZE,	//�����蔻��T�C�Y.

		size
	};


private:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	void CreateProduct() final;//�e�V�[����Create.
	void UpdateProduct() final;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.


};

