#ifndef PLAYER_ROBO_STATUS_H_
#define PLAYER_ROBO_STATUS_H_

#include "RoboStatus.h"

class clsPLAYER_ROBO_STATUS : public clsROBO_STATUS
{
public:
	clsPLAYER_ROBO_STATUS();
	~clsPLAYER_ROBO_STATUS();


	//�N���A��ʂŎg�� : �^�C�g���p�̏������p�̃f�[�^��p�ӂ��� : �N���A�������{���o���Ă���.
	void SaveHeroData();

	//�^�C�g����ʂł̏�������AssembleModel��new�̑O�Ɏg��.
	void LodeHeroData();

private:
	ROBO_STATE_DATA m_RoboStateDataHero;
//	//�^�C�g���p.
//	UCHAR m_ucPartsModelNumHero[ static_cast<int>( enPARTS::MAX ) ];
//	int m_iColorRankHero[ enCOLOR_GAGE_size ];

};




#endif//#ifndef PLAYER_ROBO_STATUS_H_