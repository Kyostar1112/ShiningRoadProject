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
	m_iHp = 0;
	m_iWalkSpd = 0;
	m_iStability = 0;
	m_iSpn = 0;
	m_iJumpPower = 0;
	m_iSearch = 0;
	m_iEnCapa = 0;
	m_iEnOutPut = 0;
	m_iBoostThrust = 0;
	m_iBoostCost = 0;
	m_iQuickThrust = 0;
	m_iQuickCost = 0;
	m_iActTime = 0;
	m_iQuickTime = 0;
	m_iAiming = 0;
	m_WeaponL.Clear();
	m_WeaponR.Clear();
}


//�f�[�^�̎󂯎��.
void clsROBO_STATUS::ReceiveLeg( vector<int> LegDatas )
{
	if( LegDatas.size() > clsPARTS_LEG::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_iHp		+= LegDatas[clsPARTS_LEG::HP];			//�l�̃p�[�c�ɉe�������.
	m_iWalkSpd	 = LegDatas[clsPARTS_LEG::WALK_SPD];	//���s���x.
	m_iStability = LegDatas[clsPARTS_LEG::STABILITY];	//���萫�\.
	m_iSpn		 = LegDatas[clsPARTS_LEG::SPIN];		//���񐫔\.
	m_iJumpPower = LegDatas[clsPARTS_LEG::JUMP_POWER];	//�W�����v��.
}

void clsROBO_STATUS::ReceiveCore( vector<int> CoreDatas )
{
	if( CoreDatas.size() > clsPARTS_CORE::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_iHp			+= CoreDatas[clsPARTS_CORE::HP];			//�l�̃p�[�c�ɉe�������.
	m_iEnCapa		 = CoreDatas[clsPARTS_CORE::EN_CAPA];		//�G�l���M�[�e�� �G�l���M�[ : energy  �e�� : capacity.
	m_iEnOutPut		 = CoreDatas[clsPARTS_CORE::EN_OUTPUT];		//�G�l���M�[�o��( �񕜗� ).
	m_iBoostThrust	 = CoreDatas[clsPARTS_CORE::BOOST_THRUST];	//�u�[�X�^�[����.
	m_iBoostCost	 = CoreDatas[clsPARTS_CORE::BOOST_COST];	//�u�[�X�^�[����G�l���M�[.
	m_iQuickThrust	 = CoreDatas[clsPARTS_CORE::QUICK_THRUST];	//�N�C�b�N����.
	m_iQuickCost	 = CoreDatas[clsPARTS_CORE::QUICK_COST];	//�N�C�b�N����G�l���M�[.
	m_iActTime		 = CoreDatas[clsPARTS_CORE::ACT_TIME];		//��������(ActivityTime).
	m_iQuickTime	 = CoreDatas[clsPARTS_CORE::QUIC_KTIME];	//�N�C�b�N���ˎ���.
}

void clsROBO_STATUS::ReceiveHead( vector<int> HeadDatas )
{
	if( HeadDatas.size() > clsPARTS_HEAD::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_iHp		+= HeadDatas[clsPARTS_HEAD::HP];	//�l�̃p�[�c�ɉe�������.
	m_iSearch	 = HeadDatas[clsPARTS_HEAD::SEARCH];//���G���\.
}

void clsROBO_STATUS::ReceiveArms( vector<int> ArmsDatas )
{
	if( ArmsDatas.size() > clsPARTS_ARM_BASE::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_iHp		+= ArmsDatas[clsPARTS_ARM_BASE::HP];	//�l�̃p�[�c�ɉe�������.
	m_iAiming	 = ArmsDatas[clsPARTS_ARM_BASE::AIMING];//�Ə����x( �G�C�� ).
}

void clsROBO_STATUS::ReceiveWeaponL( vector<int> WeaponLDatas )
{
	if( WeaponLDatas.size() > clsPARTS_WEAPON::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_WeaponL.iAtk				= WeaponLDatas[clsPARTS_WEAPON::ATK];				//�U����.
	m_WeaponL.iBulletSpd		= WeaponLDatas[clsPARTS_WEAPON::BULLET_SPD];		//�e��.
	m_WeaponL.iRange			= WeaponLDatas[clsPARTS_WEAPON::RANGE];				//�˒�����.
	m_WeaponL.iCost				= WeaponLDatas[clsPARTS_WEAPON::COST];				//����G�l���M�[.
	m_WeaponL.iLoadTIme			= WeaponLDatas[clsPARTS_WEAPON::LOAD_TIME];			//���U����.
	m_WeaponL.iLockSpd			= WeaponLDatas[clsPARTS_WEAPON::LOCK_SPD];			//���b�N���x.
	m_WeaponL.iLockRange		= WeaponLDatas[clsPARTS_WEAPON::LOCK_RANGE];		//���b�N����.
	
	m_WeaponL.iReaction			= WeaponLDatas[clsPARTS_WEAPON::REACTION];			//�ˌ�����.
	m_WeaponL.iAccuracy			= WeaponLDatas[clsPARTS_WEAPON::ACCURACY];			//�ˌ����x.
	m_WeaponL.iMagazineLoadTime	= WeaponLDatas[clsPARTS_WEAPON::MAGAZINE_LOAD_TIME];//�}�K�W�����U����.
	m_WeaponL.iBulletNum		= WeaponLDatas[clsPARTS_WEAPON::BULLETS_NUM];		//���e��.
}

void clsROBO_STATUS::ReceiveWeaponR( vector<int> WeaponRDatas )
{
	if( WeaponRDatas.size() > clsPARTS_WEAPON::size ){
		assert( !"�󂯎����vector�f�[�^��size���傫�����܂�" );
	}

	m_WeaponR.iAtk				= WeaponRDatas[clsPARTS_WEAPON::ATK];				//�U����.
	m_WeaponR.iBulletSpd		= WeaponRDatas[clsPARTS_WEAPON::BULLET_SPD];		//�e��.
	m_WeaponR.iRange			= WeaponRDatas[clsPARTS_WEAPON::RANGE];				//�˒�����.
	m_WeaponR.iCost				= WeaponRDatas[clsPARTS_WEAPON::COST];				//����G�l���M�[.
	m_WeaponR.iLoadTIme			= WeaponRDatas[clsPARTS_WEAPON::LOAD_TIME];			//���U����.
	m_WeaponR.iLockSpd			= WeaponRDatas[clsPARTS_WEAPON::LOCK_SPD];			//���b�N���x.
	m_WeaponR.iLockRange		= WeaponRDatas[clsPARTS_WEAPON::LOCK_RANGE];		//���b�N����.

	m_WeaponR.iReaction			= WeaponRDatas[clsPARTS_WEAPON::REACTION];			//�ˌ�����.
	m_WeaponR.iAccuracy			= WeaponRDatas[clsPARTS_WEAPON::ACCURACY];			//�ˌ����x.
	m_WeaponR.iMagazineLoadTime	= WeaponRDatas[clsPARTS_WEAPON::MAGAZINE_LOAD_TIME];//�}�K�W�����U����.
	m_WeaponR.iBulletNum		= WeaponRDatas[clsPARTS_WEAPON::BULLETS_NUM];		//���e��.
}


