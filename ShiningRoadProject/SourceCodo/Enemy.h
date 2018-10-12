#pragma once

#include<random>
#include<vector>
#include<string>

#include"Global.h"
#include"Charactor.h"

class clsEnemyBase
{
public:
	clsEnemyBase(std::vector<clsCharactor*>& v_Enemys);
	virtual ~clsEnemyBase();

	virtual void Update();
	void SearchTarget(std::vector<clsCharactor*>);

protected:
	TRANSFORM* m_pTrans;

	clsCharactor* m_pChara;
	clsCharactor* m_pTarget;

	std::vector<clsCharactor*>* m_vp_pEnemys;

	virtual void UpdateProduct();
	
	void SearchNear();

	bool SetMoveDir(float& fPush, float& fAngle);
	bool SetRotate(float& fPush, float& fAngle);
	bool SetLook(float& fPush, float& fAngle);

	bool IsJump();
	bool IsShot();

	struct BaseState
	{
		char strName[STR_BUFF_MAX];
		
		int iMoveCategoryVisType;//�ړ��X�e�[�^�X��؂�ւ�����@.
		
		int iProcFrame;//���_�������X�V���鎞��.
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

	struct ShotState
	{
		int iShotDisMin;
		int iShotDisMax;
		int iShotENLimitParcent;
	};

	struct VisibilityAreaState
	{
		int iVisType;
		int iVisDistance;
		int iVisAngle;
	};

	struct MoveData
	{
		int iCategory;
		std::vector<MoveState> v_MoveState;
	};

	struct ShotData
	{
		int iCategory;
		std::vector<ShotState> v_ShotState;
	};

	struct VisibilityAreaData
	{
		int iCategory;
		std::vector<VisibilityAreaState> v_VisAreaState;
	};

	BaseState m_BaseData;

	MoveData m_MoveData;
	ShotData m_ShotData;
	VisibilityAreaData m_visAreaData;

protected:
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

