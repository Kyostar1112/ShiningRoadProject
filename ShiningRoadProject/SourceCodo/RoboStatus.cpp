#include "RoboStatus.h"

#include "PartsLeg.h"
#include "PartsCore.h"
#include "PartsHead.h"
#include "PartsArmL.h"
#include "PartsArmR.h"
#include "PartsWeapon.h"


using namespace std;


clsROBO_STATUS::clsROBO_STATUS()
{
	Clear();
}

clsROBO_STATUS::~clsROBO_STATUS()
{
	Clear();
}




//�܂�����ɂ���.
void clsROBO_STATUS::Clear()
{
	for( UCHAR i=0; i<enROBO_STATE_SIZE; i++ ){
		m_iRoboState[i] = 0;
	}

	for( UCHAR i=0; i<enWEAPON_STATE_SIZE; i++ ){
		m_iWeaponState[enWEAPON_NUM::LEFT][i] = 0;
		m_iWeaponState[enWEAPON_NUM::RIGHT][i] = 0;
	}
	for( UCHAR i=0; i<enHAVE_HP_PARTS_SIZE; i++ ){
		m_iRoboHp[i] = 0;
	}
}


//�f�[�^�̎󂯎��.
void clsROBO_STATUS::ReceiveLeg( const vector<int> &LegDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum )
{
	if( LegDatas.size() > clsPARTS_LEG::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_iRoboHp[enHAVE_HP_PARTS::LEG]		  = LegDatas[clsPARTS_LEG::HP];			//�l�̃p�[�c�ɉe�������.
	m_iRoboState[enROBO_STATE::WALK_SPD]  = LegDatas[clsPARTS_LEG::WALK_SPD];	//���s���x.
	m_iRoboState[enROBO_STATE::STABILITY] = LegDatas[clsPARTS_LEG::STABILITY];	//���萫�\.
	m_iRoboState[enROBO_STATE::TURN]	  = LegDatas[clsPARTS_LEG::TURN];		//���񐫔\.
	m_iRoboState[enROBO_STATE::JUMP_POWER]= LegDatas[clsPARTS_LEG::JUMP_POWER];	//�W�����v��.

	m_ucPartsModelNum[ static_cast<int>( enPARTS::LEG ) ] = PartsNum;
}

void clsROBO_STATUS::ReceiveCore( const vector<int> &CoreDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum )
{
	if( CoreDatas.size() > clsPARTS_CORE::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_iRoboHp[enHAVE_HP_PARTS::CORE]	    = CoreDatas[clsPARTS_CORE::HP];				//�l�̃p�[�c�ɉe�������.
	m_iRoboState[enROBO_STATE::EN_CAPA]		= CoreDatas[clsPARTS_CORE::EN_CAPA];		//�G�l���M�[�e�� �G�l���M�[ : energy  �e�� : capacity.
	m_iRoboState[enROBO_STATE::EN_OUTPUT]	= CoreDatas[clsPARTS_CORE::EN_OUTPUT];		//�G�l���M�[�o��( �񕜗� ).
	m_iRoboState[enROBO_STATE::BOOST_THRUST]= CoreDatas[clsPARTS_CORE::BOOST_THRUST];	//�u�[�X�^�[����.
	m_iRoboState[enROBO_STATE::BOOST_COST]	= CoreDatas[clsPARTS_CORE::BOOST_COST];		//�u�[�X�^�[����G�l���M�[.
	m_iRoboState[enROBO_STATE::QUICK_THRUST]= CoreDatas[clsPARTS_CORE::QUICK_THRUST];	//�N�C�b�N����.
	m_iRoboState[enROBO_STATE::QUICK_COST]  = CoreDatas[clsPARTS_CORE::QUICK_COST];		//�N�C�b�N����G�l���M�[.
	m_iRoboState[enROBO_STATE::ACT_TIME]	= CoreDatas[clsPARTS_CORE::ACT_TIME];		//��������(ActivityTime).
	m_iRoboState[enROBO_STATE::QUICK_TIME]	= CoreDatas[clsPARTS_CORE::QUICK_TIME];		//�N�C�b�N���ˎ���.

	m_ucPartsModelNum[ static_cast<int>( enPARTS::CORE ) ] = PartsNum;
}

void clsROBO_STATUS::ReceiveHead( const vector<int> &HeadDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum )
{
	if( HeadDatas.size() > clsPARTS_HEAD::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_iRoboHp[enHAVE_HP_PARTS::HEAD]  = HeadDatas[clsPARTS_HEAD::HP];		//�l�̃p�[�c�ɉe�������.
	m_iRoboState[enROBO_STATE::SEARCH]= HeadDatas[clsPARTS_HEAD::SEARCH];	//���G���\.

	m_ucPartsModelNum[ static_cast<int>( enPARTS::HEAD ) ] = PartsNum;
}

void clsROBO_STATUS::ReceiveArms( const vector<int> &ArmsDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum )
{
	if( ArmsDatas.size() > clsPARTS_ARM_BASE::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_iRoboHp[enHAVE_HP_PARTS::ARMS]  = ArmsDatas[clsPARTS_ARM_BASE::HP];		//�l�̃p�[�c�ɉe�������.
	m_iRoboState[enROBO_STATE::AIMING]= ArmsDatas[clsPARTS_ARM_BASE::AIMING]; //�Ə����x( �G�C�� ).

	m_ucPartsModelNum[ static_cast<int>( enPARTS::ARM_L ) ] = PartsNum;
	m_ucPartsModelNum[ static_cast<int>( enPARTS::ARM_R ) ] = PartsNum;
}

void clsROBO_STATUS::ReceiveWeaponL( const vector<int> &WeaponLDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum )
{
	if( WeaponLDatas.size() > clsPARTS_WEAPON::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::ATK]			= WeaponLDatas[clsPARTS_WEAPON::ATK];		//�U����.
	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::BULLET_SPD]	= WeaponLDatas[clsPARTS_WEAPON::BULLET_SPD];//�e��.
	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::RANGE]		= WeaponLDatas[clsPARTS_WEAPON::RANGE];		//�˒�����.
	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::COST]		= WeaponLDatas[clsPARTS_WEAPON::COST];		//����G�l���M�[.
	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::LOAD_TIME]	= WeaponLDatas[clsPARTS_WEAPON::LOAD_TIME];	//���U����.
	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::LOCK_SPD]	= WeaponLDatas[clsPARTS_WEAPON::LOCK_SPD];	//���b�N���x.
	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::LOCK_RANGE]	= WeaponLDatas[clsPARTS_WEAPON::LOCK_RANGE];//���b�N����.

	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::REACTION]	= WeaponLDatas[clsPARTS_WEAPON::REACTION];						//�ˌ�����.
	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::ACCURACY]	= WeaponLDatas[clsPARTS_WEAPON::ACCURACY];						//�ˌ����x.
	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::MAGAZINE_LOAD_TIME]	= WeaponLDatas[clsPARTS_WEAPON::MAGAZINE_LOAD_TIME];	//�}�K�W�����U����.
	m_iWeaponState[enWEAPON_NUM::LEFT][enWEAPON_STATE::BULLETS_NUM]	= WeaponLDatas[clsPARTS_WEAPON::BULLETS_NUM];					//���e��.

	m_ucPartsModelNum[ static_cast<int>( enPARTS::WEAPON_L ) ] = PartsNum;
}

void clsROBO_STATUS::ReceiveWeaponR( const vector<int> &WeaponRDatas, const ASSEMBLE_SCENE_SELECT_TYPE PartsNum )
{
	if( WeaponRDatas.size() > clsPARTS_WEAPON::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::ATK]		= WeaponRDatas[clsPARTS_WEAPON::ATK];		//�U����.
	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::BULLET_SPD]	= WeaponRDatas[clsPARTS_WEAPON::BULLET_SPD];//�e��.
	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::RANGE]		= WeaponRDatas[clsPARTS_WEAPON::RANGE];		//�˒�����.
	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::COST]		= WeaponRDatas[clsPARTS_WEAPON::COST];		//����G�l���M�[.
	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::LOAD_TIME]	= WeaponRDatas[clsPARTS_WEAPON::LOAD_TIME];	//���U����.
	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::LOCK_SPD]	= WeaponRDatas[clsPARTS_WEAPON::LOCK_SPD];	//���b�N���x.
	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::LOCK_RANGE]	= WeaponRDatas[clsPARTS_WEAPON::LOCK_RANGE];//���b�N����.
								 
	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::REACTION]	= WeaponRDatas[clsPARTS_WEAPON::REACTION];						//�ˌ�����.
	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::ACCURACY]	= WeaponRDatas[clsPARTS_WEAPON::ACCURACY];						//�ˌ����x.
	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::MAGAZINE_LOAD_TIME]	= WeaponRDatas[clsPARTS_WEAPON::MAGAZINE_LOAD_TIME];	//�}�K�W�����U����.
	m_iWeaponState[enWEAPON_NUM::RIGHT][enWEAPON_STATE::BULLETS_NUM]	= WeaponRDatas[clsPARTS_WEAPON::BULLETS_NUM];				//���e��.

	m_ucPartsModelNum[ static_cast<int>( enPARTS::WEAPON_R ) ] = PartsNum;
}


//���{�̏���f���o��.
int clsROBO_STATUS::GetRoboState( const enROBO_STATE enStateNum )
{
	if( enStateNum >= enROBO_STATE_SIZE ){
		assert( !"�s���ȏ����擾���悤�Ƃ���܂���" );
		return 0;
	}
	//HP���Z.
	if( enStateNum == enROBO_STATE::HP ){
		m_iRoboState[enStateNum] = 0;
		for( UCHAR i=0; i<enHAVE_HP_PARTS_SIZE; i++ ){
			m_iRoboState[enStateNum] += m_iRoboHp[i];
		}
	}

	return m_iRoboState[enStateNum];
}
//����̏���f���o��.
int clsROBO_STATUS::GetWeaponState( 
	const enWEAPON_NUM enArmLR, const enWEAPON_STATE enStateNum ) const
{
	if( enArmLR >= enWEAPON_NUM_SIZE ){
		assert( !"�s���Ȑ��̕��킪�w�肳��܂���" );
		return 0;
	}

	if( enStateNum >= enWEAPON_STATE_SIZE ){
		assert( !"�s���ȕ�������擾���悤�Ƃ���܂���" );
		return 0;
	}

	return m_iWeaponState[enArmLR][enStateNum];
}


//�p�[�c�ԍ���Ԃ�.
UCHAR clsROBO_STATUS::GetPartsNum( const enPARTS PartsType )
{
	return m_ucPartsModelNum[ static_cast<int>( PartsType ) ];
}
