//#pragma once

#ifndef CHARACTOR
#define CHARACTOR

#include"Global.h"
#include"DX9Mesh.h"
#include"Object.h"

class clsCharactor : public clsObject
{

public:
	//���ʃX�e�[�^�X.
	int HP;//�̗�.
	int m_MaxHP;//�ő�̗�.

	bool m_bDeadFlg;//���S�t���O.

	//���͊֌W.

	float fPushMin;

	//�ړ��֌W.
	bool m_bMoving;

	float m_fMoveSpeed;//�ŏI�I�ɉ��Z�����X�s�[�h.
	float m_fMoveSpeedMax;//�X�s�[�h�̍ő�l.

	int m_iTopSpeedFrame;//���ɒB����܂ł̃t���[���l.
	float m_fMoveAccele;// = m_fMoveSpeedMax / m_fTopSpeedFrame;
	
	int m_iStopFrame;//���S�ɒ�~����܂ł̃t���[���l.
	float m_fMoveDecele;// = m_fMoveSpeed / m_iStopFrame;

	D3DXVECTOR3 m_vMoveDir;

	void Shot();

	//�ړ��֌W.
	void Move(const float fAngle, const float fPush);
	bool IsMoveing();
	bool IsMoveControl();
	void SetMoveDir(const float fAngle);
	void MoveControl();
	void Accele(const float fPower);
	void Decele();

	void SetMoveAcceleSpeed(
		float fMoveSpeedMax, 
		int iTopSpeedFrame)//����.
	{
		m_fMoveSpeedMax = fMoveSpeedMax;
		m_iTopSpeedFrame = iTopSpeedFrame;

		m_fMoveAccele = m_fMoveSpeedMax / m_iTopSpeedFrame;

		SetMoveDecelerationSpeed(m_iTopSpeedFrame);
	}

	void SetMoveDecelerationSpeed(const int iStopFrame)//����.
	{
		m_iStopFrame = iStopFrame;

		m_fMoveDecele = abs(m_fMoveSpeed) / m_iStopFrame;
	}

	//��].
	float m_fRotSpd;

	void SetRotationSpeed(const float fSpd);
	void Rotate(const float fAngle, const float fPush);

	void Spin(
		float& fNowYaw,
		const float fTargetYaw,
		const float fTurnSpd,
		const float fTurnStop);

	//�󒆊֌W.
	float m_fJumpPower;

	void SetJumpPower(const float fPower)
	{
		m_fJumpPower = fPower;
	}

	void Jump();

	float fJumpPower;

	//�����蔻��֌W.

	//�X�t�B�A.

	//�X�t�B�A�\����.
	struct SPHERE
	{
		D3DXVECTOR3 vCenter;//���S.
		float fRadius;	//���a.
	};

	bool PointIntersect(
		const D3DXVECTOR3 StartPos,	//��̈ʒu.
		const D3DXVECTOR3 EndPos,		//�W�I�̈ʒu.
		const clsDX9Mesh* pTarget		//��Q���̕���.
		);
	
	//ڲ��˯Ĕ���̒���.
	float RaySpece;

	clsCharactor();
	virtual ~clsCharactor();

	bool RecoLange(
		const D3DXVECTOR3 CenterPos, 
		const D3DXVECTOR3 TargetPos, 
		const float Range);//�~�͈͔̔���.

private:
	LPD3DXMESH m_pMeshForRay;//ڲ�̂��߂�ү���p.
};

#endif