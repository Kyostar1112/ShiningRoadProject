#pragma once 

#include "Global.h"

#include <vector>

//�A�Z���u���V�[���ł̑I�����̌^.
//#define ASSEMBLE_SCENE_SELECT_TYPE short 
using ASSEMBLE_SCENE_SELECT_TYPE = short;


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
	//������ : �U���͂Ȃǂ̃p�����[�^�Q.
	//������ : ���f���ԍ�.
	void ReceiveLeg( const std::vector<int> &LegDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum );
	void ReceiveCore( const std::vector<int> &CoreDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum );
	void ReceiveHead( const std::vector<int> &HeadDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum );
	void ReceiveArms( const std::vector<int> &ArmsDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum );
	void ReceiveWeaponL( const std::vector<int> &WeaponLDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum );
	void ReceiveWeaponR( const std::vector<int> &WeaponRDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum );
	 
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
		BOOST_THRUST_H,	//�u�[�X�^�[����( ���� ).
		BOOST_COST_H,	//�u�[�X�^�[����G�l���M�[( ���� ).
		BOOST_THRUST_V,	//�u�[�X�^�[����( ���� ).
		BOOST_COST_V,	//�u�[�X�^�[����G�l���M�[( ���� ).
		QUICK_THRUST,	//�N�C�b�N����.
		QUICK_COST,		//�N�C�b�N����G�l���M�[.
		QUICK_TIME,		//�N�C�b�N���ˎ���.
		ACT_TIME,		//��������(ActivityTime).

		SEARCH,	//���G���\.

		AIMING,	//�Ə����x( �G�C�� ).

		COL_SIZE_LEG,	//�r�����蔻��T�C�Y.
		COL_SIZE_CORE,	//�R�A�����蔻��T�C�Y.
		COL_SIZE_HEAD,	//�������蔻��T�C�Y.
		COL_SIZE_ARMS,	//�r�����蔻��T�C�Y.

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
		SHOT_STABILITY,		//�ˌ�����.
		MAGAZINE_LOAD_TIME,	//�}�K�W�����U����.
		BULLETS_NUM,		//���e��.

		COL_SIZE,	//�e�̓����蔻��T�C�Y.
		EFC_BULLET,	//�e�{�̂̃G�t�F�N�g.
		EFC_LOCUS,	//�e�̋O�Ղ̃G�t�F�N�g.
		EFC_HIT,	//���e�̃G�t�F�N�g.
		SE_FIER,	//����SE.
		SE_HIT,		//���e��SE.

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

	//�p�[�c�ԍ���Ԃ�( ���ܑ������Ă���p�[�c�����Ԃ� ).//#define SKIN_ENUM_TYPE UCHAR.
	UCHAR GetPartsNum( const enPARTS PartsType );

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

	//���{��HP����ō��Z���邽�߂̕ϐ�.
	int m_iRoboHp[enHAVE_HP_PARTS_SIZE];

	//�p�[�c�ԍ��̔z��.//#define SKIN_ENUM_TYPE UCHAR.
	UCHAR m_ucPartsModelNum[ static_cast<int>( enPARTS::MAX ) ];
};
