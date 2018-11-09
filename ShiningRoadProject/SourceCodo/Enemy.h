#pragma once

#include<random>
#include<vector>
#include<string>

#include"Global.h"
#include"Charactor.h"

class clsEnemyBase
{
public:
	//clsEnemyBase(std::vector<clsCharactor*>& v_Enemys);
	clsEnemyBase();
	virtual ~clsEnemyBase();

	void Update();
	void SetData(std::string strEnemyFolderName);
	void SearchTarget(std::vector<clsCharactor*>);

protected:
	TRANSFORM* m_pTrans;

	clsCharactor* m_pChara;
	clsCharactor* m_pTarget;

	std::vector<clsCharactor*>* m_vp_pEnemys;

	void SetBaseData(std::string strEnemyFolderName);
	void SetMoveData();
	void SetVisibilityData();
	virtual void SetShotData();
	virtual void SetDataProduct();

	virtual void UpdateProduct();

	void SearchNear();

	bool SetMoveDir(float& fPush, float& fAngle);
	bool SetRotate(float& fPush, float& fAngle);
	bool SetLook(float& fPush, float& fAngle);

	bool IsJump();
	bool IsShot();
	
	enum enTargetEvaluationType
	{
		enTargetEvaluationTypeNear = 0,

		enTargetEvaluationTypeSize
	};

	struct BaseState
	{
		std::string strEnemyFolderName;

		int iMoveSwichType;//�ړ��X�e�[�^�X��؂�ւ�����@.
		int iProcFrame;//���_�������X�V���鎞��.
	};

	enum enBaseStateFileOrder
	{
		enBaseStateMoveSwichType,
		enBaseStateProcFrame,

		enBaseStateSize
	};

	struct MoveState
	{
		int iMoveUpdateInterval;
		int iHorDistance;
		int iHorDisRandMax;
		int iMoveDir;
		int iMoveDirRandMax;
		int iVerDistance;
		int iVerDistRandMax;
	};

	enum enMoveStateFileOrder
	{
		enMoveStateMoveUpdateInterval,
		enMoveStateHorDistance,
		enMoveStateHorDisRandMax,
		enMoveStateMoveDir,
		enMoveStateMoveDirRandMax,
		enMoveStateVerDistance,
		enMoveStateVerDistRandMax,

		enMoveStateSize
	};

	struct ShotState
	{
		int iShotDisMin;
		int iShotDisMax;
		int iShotENLimitParcent;
	};

	enum enShotStateFileOrder
	{
		enShotStateShotDisMin,
		enShotStateShotDisMax,
		enShotStateShotENLimitParcent,
		
		enShotStateSize
	};

	struct VisibilityAreaState
	{
		int iVisType;
		int iVisDistance;
		int iVisAngle;
	};

	enum enVisibilityAreaStateFileOrder
	{
		enVisibilityAreaVisType,
		enVisibilityAreaVisDistance,
		enVisibilityAreaVisAngle,
		
		enVisibilityAreaStateSize
	};

	BaseState m_BaseState;
	std::vector<MoveState> m_v_MoveState;
	std::vector<ShotState> m_v_ShotState;
	std::vector<VisibilityAreaState> m_v_VisAreaState;

	struct UpdateState
	{
		int iHorDirResult;
		D3DXVECTOR3 vHorMovePos;
		float fMoveDir;

		float fRotDir;
		float fVerLookDir;

		float fVerDis;

		int iMoveCategoryNo;//���݂̈ړ�.

		int iProcessCnt;//�����X�V����.
		int iMoveUpdateCnt;//�ړ��X�e�[�^�X�X�V�Ԋu.
	};

	UpdateState m_UpdateState;
};

