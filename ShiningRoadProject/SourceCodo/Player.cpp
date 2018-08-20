#include"Player.h"

clsPlayer::clsPlayer()
{
	ZeroMemory(this, sizeof(clsPlayer));
}

clsPlayer::~clsPlayer()
{

}

void clsPlayer::Init(clsPOINTER_GROUP* const pPtrGroup)
{
	RoboInit(pPtrGroup);

	m_pInput = new clsInputRobo(pPtrGroup->GetDxInput(), pPtrGroup->GetXInput());

	//m_pMesh->SetAnimSpeed(0.01);
}

void clsPlayer::Action(clsStage* const pWall)
{
	float fPush = 0.0f;
	float fAngle = 0.0f;
	clsRoboCommand* pRoboCom;

	float fPushMin = 0.5f;

	pRoboCom = m_pInput->MoveSwitch();

	if (pRoboCom)
	{
		pRoboCom->PushBotton(this);
	}

	pRoboCom = m_pInput->BoostRising();

	if (pRoboCom)
	{
		pRoboCom->PushBotton(this);
	}

	pRoboCom = m_pInput->LSInput(fPush, fAngle);

	if (pRoboCom)
	{
		pRoboCom->Trigger(this, fPush, fAngle);
	}

	pRoboCom = m_pInput->QuickBoost(fPush);//�N�C�b�N�u�[�X�g.
	if (pRoboCom)
	{
		pRoboCom->Trigger(this, fPush, fAngle);
		pRoboCom->PushBotton(this);
	}

	else
	{
		pRoboCom = m_pInput->RSHorInput(fPush, fAngle);//����.

		if (pRoboCom)
		{
			pRoboCom->Trigger(this, abs(fPush), fAngle);
		}

		pRoboCom = m_pInput->QuickTurn(fPush);

		if (pRoboCom)
		{
			pRoboCom->Trigger(this, fPush, fAngle);
			pRoboCom->PushBotton(this);
		}

		else
		{
			float fPushFull = 1.0f;
			float fPushAngle = 0.0f;

			pRoboCom = m_pInput->QuickBoost(fPushFull);//�N�C�b�N�u�[�X�g.
			if (pRoboCom)
			{
				pRoboCom->Trigger(this, fPush, fPushAngle);
				pRoboCom->PushBotton(this);
			}
		}
	}

	pRoboCom = m_pInput->RSVerInput(fPush, fAngle);

	if (pRoboCom)
	{
		pRoboCom->Trigger(this, fPush, fAngle);
	}

	pRoboCom = m_pInput->LWeaponShot();

	if (pRoboCom)
	{
		pRoboCom->PushBotton(this);
	}

	pRoboCom = m_pInput->RWeaponShot();

	if (pRoboCom)
	{
		pRoboCom->PushBotton(this);
	}

	Move();
	Rotate();

	Updata();
	UpdateCamTargetPos();

	WallJudge(pWall);
}

void clsPlayer::InhUpdate()
{
	//m_pMesh->SetAnimSpeed(0.01);
}

D3DXVECTOR3 clsPlayer::GetCamTargetPos()
{
	return m_vCamTargetPos;
}


D3DXVECTOR3 clsPlayer::GetLookTargetPos()
{
	return m_vLookTargetPos;
}


void clsPlayer::UpdateCamTargetPos()
{
	const float fCamMoveSpeed = 0.5f;
	const float fLookPosSpace = 50.0f;
	const float fCamSpaceTmp = 2.0f;
	const float fCamPosX = 0.5f;

	D3DXMATRIX mRot;

	//�J�����ʒu�̂��߂̉�]�s��쐬.
	D3DXMatrixRotationYawPitchRoll(
		&mRot,
		m_Trans.fYaw,
		m_fLookUpDir,
		m_Trans.fRoll);

	//���޸�ق�p��.
	float fCamAxisXTmp;

	if (m_bCamPosXSwitch)
	{
		fCamAxisXTmp = fCamPosX;
	}

	else
	{
		fCamAxisXTmp = -fCamPosX;
	}
	
	D3DXVECTOR3 vCamAxis =
	{
		fCamAxisXTmp,
		0.0f,
		fCamSpaceTmp
	};

	D3DXVECTOR3 vLookAxis;

	//�޸�ق��̂��̂���]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord(&vCamAxis, &vCamAxis, &mRot);
	D3DXVec3TransformCoord(&vLookAxis, &g_vDirForward, &mRot);

	D3DXVECTOR3 vCamPosTmp;

	//====================================================
	//��גǏ]���� ��������.
	//====================================================
	//�J�����������x��Ă��Ă���悤��.
	//�J���������ݖړI�Ƃ��Ă���ʒu���Z�o.
	const D3DXVECTOR3 vCamTargetPos = m_vCenterPos - vCamAxis * fCamSpaceTmp;

	//���݈ʒu���擾���A���݈ʒu�ƖړI�̈ʒu�̍�����ړ��ʂ��v�Z����.
	vCamPosTmp = m_vCamTargetPos;//���݈ʒu���擾
	vCamPosTmp -= (vCamPosTmp - vCamTargetPos) * fCamMoveSpeed;

	m_vLookTargetPos = vCamPosTmp + vLookAxis * fLookPosSpace;

	m_vCamTargetPos = vCamPosTmp;
}