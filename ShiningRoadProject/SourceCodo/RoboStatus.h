#pragma once 

#include "Global.h"

#include <vector>

//������( ���E�ʁX�Ȃ̂Ŗʓ|�Ȃ̂ł܂Ƃ߂� ).
struct WERPON_STATUS
{
	int iAtk;			//�U����.
	int iBulletSpd;		//�e��.
	int iRange;			//�˒�����.
	int iCost;			//����G�l���M�[.
	int iLoadTIme;		//���U����.
	int iLockSpd;		//���b�N���x.
	int iLockRange;		//���b�N����.
		
	int iReaction;		//�ˌ�����.
	int iAccuracy;		//�ˌ����x.
	int iMagazineLoadTime;//�}�K�W�����U����.
	int iBulletNum;		//���e��.

	void Clear(){
		iAtk = 0;
		iBulletSpd = 0;
		iRange = 0;
		iCost = 0;
		iLoadTIme = 0;
		iLockSpd = 0;
		iLockRange = 0;
		
		iReaction = 0;
		iAccuracy = 0;
		iMagazineLoadTime = 0;
		iBulletNum = 0;
	}
};


//�Q�[���N���X�ō쐬�A.
//�A�Z���u���V�[���Œl��ݒ�A.
//�~�b�V���V�[���ŏ������̒i�K�Ń��{�ɓn��.
class clsROBO_STATUS
{
public:
	clsROBO_STATUS();
	~clsROBO_STATUS();

	//�܂�����ɂ���.
	void Clear();

	//�f�[�^�̎󂯎��.
	//�����̊֐��Ńf�[�^���󂯎��O��Clear()���Ă�������.
	void ReceiveLeg( std::vector<int> LegDatas );
	void ReceiveCore( std::vector<int> CoreDatas );
	void ReceiveHead( std::vector<int> HeadDatas );
	void ReceiveArms( std::vector<int> ArmsDatas );
	void ReceiveWeaponL( std::vector<int> WeaponLDatas );
	void ReceiveWeaponR( std::vector<int> WeaponRDatas );

private:
	
	int m_iHp;			//�l�̃p�[�c�ɉe�������.
	int m_iWalkSpd;		//���s���x.
	int m_iStability;	//���萫�\.
	int m_iSpn;			//���񐫔\.
	int m_iJumpPower;	//�W�����v��.
	int m_iSearch;		//���G���\.
	int m_iEnCapa;		//�G�l���M�[�e�� �G�l���M�[ : energy  �e�� : capacity.
	int m_iEnOutPut;	//�G�l���M�[�o��( �񕜗� ).
	int m_iBoostThrust;	//�u�[�X�^�[����.
	int m_iBoostCost;	//�u�[�X�^�[����G�l���M�[.
	int m_iQuickThrust;	//�N�C�b�N����.
	int m_iQuickCost;	//�N�C�b�N����G�l���M�[.
	int m_iActTime;		//��������(ActivityTime).
	int m_iQuickTime;	//�N�C�b�N���ˎ���.
	int m_iAiming;		//�Ə����x( �G�C�� ).

	WERPON_STATUS m_WeaponL;
	WERPON_STATUS m_WeaponR;

};
