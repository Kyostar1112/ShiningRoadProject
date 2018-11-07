#pragma once

#include"Enemy.h"
#include"RoboCommand.h"

#define sShot

class clsEnemyRobo : public clsEnemyBase
{
public:
	clsEnemyRobo();
	virtual ~clsEnemyRobo();

	void Init(
		LPSTR strEnemyFolderName,
		clsRobo* pRobo);

	clsRoboCommand* MoveOperation(float& fPower, float& fAngle);
	clsRoboCommand* MoveSwitchOperation();
	clsRoboCommand* RotateOperation(float& fPower, float& fAngle);
	clsRoboCommand* LookOperation(float& fPower, float& fAngle);

	clsRoboCommand* QuickTurnOperation(float& fPower, float& fAngle);
	clsRoboCommand* QuickBoostOperation(float& fPower, float& fAngle);
	clsRoboCommand* BoostOperation();

	clsRoboCommand* LShotOperation();
	clsRoboCommand* RShotOperation();
	
private:
	struct Boost
	{
		int iRisingENParcent;//�㏸�J�n���Ă���EN�c�ʗ�.
		int iENLimitParcent;//�㏸����߂�EN�c�ʗ�.
	};

	enum enBoostFileOrder
	{
		enBoostRisingENParcent = 0,
		enBoostENLimitParcent,

		enBoostSize
	};

	struct QuickBoostApproach
	{
		int iUpdateTime;
		int iDis;
		int iENLimit;
	};

	enum enQuickBoostApproachFileOrder
	{
		enQuickBoostAppUpdateTime = 0,
		enQuickBoostAppDis,
		enQuickBoostAppENLimit,

		enQuickBoostAppSize
	};

	struct QuickTrun
	{
		int iUpdateTime;
		int iDir;
		int iENLimit;
	};

	enum enQuickTrunFileOrder
	{
		enQuickTrunUpdateTime = 0,
		enQuickTrunDir,
		enQuickTrunENLimit,

		enQuickTrunSize
	};

	enum enAvoidCategory
	{
		enAvoidUpdateTime = 0,
		enAvoidLockTime,
		enAvoidDamage,

		enAvoidSize
	};

	struct QuickBoostAvoid
	{
		int iUpdateTime;
		int iAvoidNum;//��������J�e�S���i���o�[.
		int iLockTimeorDamage;
		int iAvoidDir;
		int iENLimit;

		//�ȉ��A���t���[���X�V�̂��߂̕ϐ�.
		int iAvoidDamageUpdateTime;
		int iDamage;
		int iLockTime;
	};

	enum enQuickBoostAvoidFileOrder
	{
		QuickBoostAvoidUpdateTime = 0,
		QuickBoostAvoidAvoidNum,
		QuickBoostAvoidLockTimeorDamage,
		enQuickBoostAvoidDir,
		enQuickBoostAvoidENLimit,

		enQuickBoostAvoidSize
	};

	clsRobo* m_pBody;

	clsRoboCommand* m_pComMove;
	clsRoboCommand* m_pComMoveSwitch;
	clsRoboCommand* m_pComRotate;
	clsRoboCommand* m_pComLook;

	clsRoboCommand* m_pComQuickBoost;
	clsRoboCommand* m_pComQuickTrun;
	clsRoboCommand* m_pComBoost;

	clsRoboCommand* m_pComLShot;
	clsRoboCommand* m_pComRShot;

	void IsENSaving();//�u�[�X�g�㏸���s���Ă����ق�EN���񕜂������𔻒�.
	bool IsBoostRising();

	bool IsBoostOn();
	bool IsBoostOff();

	bool IsQuickTurn(float& fPush, float& fAngle);//�^�[�Q�b�g�ʒu�̕��������ʂ�����ȏ㗣��Ă��ꍇ�A�N�C�b�N�^�[�����g�p.
	bool IsQuickBoostApproach(float& fPush, float& fAngle);//�N�C�b�N�u�[�X�g���g�p���A�^�[�Q�b�g�Ƃ̋������l�߂�.

	bool IsQuickBoostAvoid(float& fPush, float& fAngle);//�N�C�b�N�u�[�X�g�ɂ����.

	bool IsQuickBoostAvoidtoLockTime(QuickBoostAvoid& AvoidState, float& fPush, float& fAngle);
	bool IsQuickBoostAvoidtoDamage(QuickBoostAvoid& AvoidState, float& fPush, float& fAngle);
	void ResetAvoidtoDamage();

	bool IsShotR();
	bool IsShotL();

	virtual void SetDataProduct();
	virtual void SetShotData();

	void SetBoostData();

	void SetQuickBoostAppData();
	void SetQuickTrunData();
	void SetQuickBoostAvoidData();

	std::vector<ShotState> m_v_LShotState;
	std::vector<ShotState> m_v_RShotState;

	Boost m_BoostState;

	std::vector<QuickBoostApproach> m_v_QuickAppState;
	std::vector<QuickTrun> m_v_QuickTrunState;
	std::vector<QuickBoostAvoid> m_v_QuickBoostAvoidState;

	bool m_bENSaving;
};