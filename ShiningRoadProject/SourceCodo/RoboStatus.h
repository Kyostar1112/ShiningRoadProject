#pragma once 

#include "Global.h"

#include <vector>



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
	void ReceiveLeg( const std::vector<int> &LegDatas );
	void ReceiveCore( const std::vector<int> &CoreDatas );
	void ReceiveHead( const std::vector<int> &HeadDatas );
	void ReceiveArms( const std::vector<int> &ArmsDatas );
	void ReceiveWeaponL( const std::vector<int> &WeaponLDatas );
	void ReceiveWeaponR( const std::vector<int> &WeaponRDatas );
	 
	//���{�̃X�e�[�^�X�z��̈���.
	enum enROBO_STATE : UCHAR
	{
		HP = 0,		//�̗�.
		WALK_SPD,	//���s���x.
		STABILITY,	//���萫�\.
		TURN,		//���񐫔\.
		JUMP_POWER,	//�W�����v��.

		EN_CAPA,		//�G�l���M�[�e�� �G�l���M�[ : energy  �e�� : capacity.
		EN_OUTPUT,		//�G�l���M�[�o��( �񕜗� ).
		BOOST_THRUST,	//�u�[�X�^�[����.
		BOOST_COST,		//�u�[�X�^�[����G�l���M�[.
		QUICK_THRUST,	//�N�C�b�N����.
		QUICK_COST,		//�N�C�b�N����G�l���M�[.
		ACT_TIME,		//��������(ActivityTime).
		QUIC_KTIME,		//�N�C�b�N���ˎ���.

		SEARCH,	//���G���\.

		AIMING,	//�Ə����x( �G�C�� ).

		enROBO_STATE_SIZE
	};

	//����̃X�e�[�^�X�z��̈���.
	enum enWEAPON_STATE : UCHAR
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

		enWEAPON_STATE_SIZE
	};

	//����̃X�e�[�^�X���E�̈���.
	enum enWEAPON_NUM : UCHAR
	{
		LEFT = 0,
		RIGHT= 1,

		enWEAPON_NUM_SIZE
	};


	//���{�̏���f���o��.
	int GetRoboState( const enROBO_STATE enStateNum );
	//����̏���f���o��.
	int GetWeaponState( const enWEAPON_NUM enArmLR, const enWEAPON_STATE enStateNum ) const;


private:

	//HP�����p�[�c.
	enum enHAVE_HP_PARTS
	{
		LEG = 0,
		CORE,
		HEAD,
		ARMS,

		enHAVE_HP_PARTS_SIZE
	};

	//���{�b�g�{�̂̃p�����[�^.
	int m_iRoboState[enROBO_STATE_SIZE];

	//����̃p�����[�^.
	int m_iWeaponState[enWEAPON_NUM_SIZE][enWEAPON_STATE_SIZE];

	int m_iRoboHp[enHAVE_HP_PARTS_SIZE];

};
