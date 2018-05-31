#include"Charactor.h"

void clsCharactor::SetMoveAcceleSpeed(float fMoveSpeedMax, int iTopSpeedFrame)//����.
{
	m_fMoveSpeedMax = fMoveSpeedMax;
	m_iTopMoveSpeedFrame = iTopSpeedFrame;

	m_fMoveAccele = m_fMoveSpeedMax / m_iTopMoveSpeedFrame;

	SetMoveDeceleSpeed(m_iTopMoveSpeedFrame);
}

void clsCharactor::SetMoveDeceleSpeed(const int iMoveStopFrame)//����.
{
	m_iMoveStopFrame = iMoveStopFrame;

	m_fMoveDecele = abs(m_fMoveSpeed) / m_iMoveStopFrame;
}

void clsCharactor::Move(const float fAngle, const float fPush)
{
	fPushMin = 0.5f;
	float fPushPower = abs(fPush);

	if (!IsMoveControl())
	{
		MoveControl();
		MoveDecele();
		return;
	}

	else
	{
		if (fPushPower < fPushMin)
		{
			MoveDecele();
		}

		else
		{
			SetMoveDir(fAngle);
			MoveAccele(fPush);
		}

		MoveControl();
	}

	
	//�ǂƂ̓����蔻��.


}

bool clsCharactor::IsMoveing()
{
	if (m_fMoveSpeed == 0.00f)
	{
		return false;
	}

	return true;
}

bool clsCharactor::IsMoveControl()
{
	if (m_fMoveSpeed > m_fMoveSpeedMax || m_fMoveSpeed <= -m_fMoveSpeedMax)
	{
		return false;
	}

	return true;
}

void clsCharactor::SetMoveDir(const float fAngle)
{
	if (!IsMoveing())
	{
		m_vMoveDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	D3DXVECTOR3 vForward;

	//�������Ă������.
	vForward = GetVec3Dir(m_Trans.fYaw, g_vDirForward);

	//�s����������.
	D3DXVECTOR3 vAcceleDir = GetVec3Dir(fAngle, vForward);

	m_vMoveDir += (vAcceleDir - m_vMoveDir);// / (m_iMoveStopFrame / 2);
}

void clsCharactor::MoveControl()
{
	if (abs(m_fMoveSpeed) < 0.0f)
	{
		m_bMoving = false;
		return;
	}
	
	m_bMoving = true;
	m_Trans.vPos += m_vMoveDir * abs(m_fMoveSpeed);
}

void clsCharactor::MoveAccele(const float fPower)
{
	if (m_fMoveSpeed <= m_fMoveSpeedMax && m_fMoveSpeed > -m_fMoveSpeedMax)
	{
		m_fMoveSpeed += m_fMoveAccele * fPower;

		if (m_fMoveSpeed > m_fMoveSpeedMax || m_fMoveSpeed <= -m_fMoveSpeedMax)
		{
			m_fMoveSpeed = m_fMoveSpeedMax * (m_fMoveSpeed / abs(m_fMoveSpeed));
		}
	}

	SetMoveDeceleSpeed(m_iMoveStopFrame);
}

void clsCharactor::MoveDecele()
{
	if (m_fMoveSpeed > m_fMoveDecele)
	{
		m_fMoveSpeed -= m_fMoveDecele;
	}

	else
	{
		m_fMoveSpeed = 0.00f;
		m_vMoveDir = GetVec3Dir(m_Trans.fYaw, g_vDirForward);
	}
}

//��].
void clsCharactor::SetRotationSpeed(const float fSpd)
{
	m_fRotSpeed = fSpd;
}

bool clsCharactor::IsRotate()
{
	return m_bRotation;
}

bool clsCharactor::IsRotControl()
{
	if (abs(m_fRotSpeed) > m_fRotSpeedMax)
	{
		m_bRotation = false;
		return false;
	}

	m_bRotation = true;
	return true;
}
void clsCharactor::RotAccele(const float fPower)
{
	m_fRotSpeed += m_fRotAccele * fPower;

	if (abs(m_fRotSpeed) > m_fRotSpeedMax)
	{
		m_fRotSpeed = m_fRotSpeedMax * (m_fRotSpeed / abs(m_fRotSpeed));
	}

	SetRotDeceleSpeed(m_iMoveStopFrame);
}

void clsCharactor::RotDecele()
{
	if (m_fRotSpeed > m_fRotDecele)
	{
		m_fRotSpeed -= m_fRotDecele;
	}

	else
	{
		m_fRotSpeed = 0.00f;
		m_bRotation = false;
	}
}

void clsCharactor::SetRotAcceleSpeed(const float fRotSpeedMax, const int iTopRotSpdFrame)
{
	m_fRotSpeedMax = fRotSpeedMax;
	m_iTopRotSpeedFrame = iTopRotSpdFrame;

	m_fRotAccele = m_fRotSpeedMax / m_iTopRotSpeedFrame;

	SetRotDeceleSpeed(m_iTopRotSpeedFrame);
}

void clsCharactor::SetRotDeceleSpeed(const int iRotStopFrame)
{
	m_iRotStopFrame = iRotStopFrame;

	m_fRotDecele = abs(m_fRotSpeed) / m_iRotStopFrame;
}

void clsCharactor::SetRotDir(float fAngle)
{
	m_fRotDir = m_Trans.fYaw + fAngle;
}

void clsCharactor::Rotate(const float fAngle, const float fPush)
{
	fPushMin = 0.5f;
	float fPushPower = abs(fPush);

	if (!IsRotControl())
	{
		Spin(m_Trans.fYaw, m_fRotDir, m_fRotSpeed, m_fRotSpeed);
		RotDecele();
		return;
	}

	else
	{
		if (fPushPower < fPushMin)
		{
			RotDecele();
		}

		else
		{
			SetRotDir(fAngle);
			RotAccele(fPush);
		}

		if (IsRotate())
		{
			Spin(m_Trans.fYaw, m_fRotDir, m_fRotSpeed, m_fRotSpeed);
		}
	}
}

void clsCharactor::Jump()
{
	if (m_bGround)
	{
		m_fFollPower = m_fJumpPower;
	}
}

//���ޯĂƂ���ʒu�ɑ΂���ڲ���΂��āA�Օ������Ȃ������ׂ�.
bool clsCharactor::PointIntersect(
	const D3DXVECTOR3 StartPos,	//��̈ʒu.
	const D3DXVECTOR3 EndPos,		//�W�I�̈ʒu.
	const clsDX9Mesh* pTarget		//��Q���̕���.
	)
{
	D3DXVECTOR3 vecStart, vecEnd, vecDistance;
	//ڲ�̊J�n�I���ʒu��Attacker�ƍ��킹��.
	vecStart = StartPos;

	//�W�I�̈ʒu���I�_��.
	vecEnd = EndPos;

	//�Ώۂ������Ă��镨�̂ł��A�Ώۂ�world�s��́A
	//�t�s���p����΁A������ڲ��������.
	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(
		&matWorld,
		pTarget->m_Trans.vPos.x,
		pTarget->m_Trans.vPos.y,
		pTarget->m_Trans.vPos.z
		);

	//�t�s������߂�.
	D3DXMatrixInverse(&matWorld, NULL, &matWorld);

	D3DXVec3TransformCoord(
		&vecStart, &vecStart, &matWorld);

	D3DXVec3TransformCoord(
		&vecEnd, &vecEnd, &matWorld);

	//���������߂�.
	vecDistance = vecEnd - vecStart;

	D3DXVec3Normalize(&vecDistance, &vecDistance);

	//���������߂�.

	BOOL bHit = false;	//�����׸�.

	float fDis = 0xffffffff;//�ő�l������.

	D3DXIntersect(
		pTarget->m_pMesh,	//�Ώ�ү��.
		&vecStart,			//�J�n�ʒu.
		&vecDistance,		//ڲ�̋���.
		&bHit,				//(out)���茋��.
		NULL,	//(out)bHit��True���Aڲ�̎n�_��.
		//�ł��߂��̖ʂ̲��ޯ���l�ւ��߲��.
		NULL, NULL,				//(out)�d�S˯č��W.
		&fDis,			//���ޯĂƂ̋���.
		NULL, NULL);

	float VecLenght = D3DXVec3Length(&(vecEnd - vecStart));


	if (fDis < VecLenght)//ڲ�͈͓̔��ɉ������邩?.
	{

		return true;//����������.
	}


	return false;//�����Ȃ�.
}

bool clsCharactor::RecoLange(D3DXVECTOR3 CenterPos, D3DXVECTOR3 TargetPos, float Range)//�~�̔F���͈͔���.
{
	if (pow(TargetPos.x - CenterPos.x, 2.0f) + pow(TargetPos.z - CenterPos.z, 2.0f) <= pow(Range, 2.0f))
	{
		return true;
	}

	return false;
}

void clsCharactor::Spin(float& NowYaw, const float TargetYaw, const float TurnSpd, const float TurnStop)
{
	float fTarget = TargetYaw;

	if (fTarget - NowYaw > D3DXToRadian(180))
	{
		fTarget -= D3DXToRadian(360);
	}
	else if (fTarget - NowYaw < -D3DXToRadian(180))
	{
		fTarget += D3DXToRadian(360);
	}

	if (NowYaw > D3DXToRadian(180))
	{
		NowYaw -= D3DXToRadian(360);
	}
	else if (NowYaw < -D3DXToRadian(180))
	{
		NowYaw += D3DXToRadian(360);
	}

	//�p�x���߂Â�.
	if (abs(fTarget - NowYaw) > TurnStop)
	{
		if (NowYaw < fTarget)
		{
			NowYaw += TurnSpd;
		}
		else if (NowYaw > fTarget)
		{
			NowYaw -= TurnSpd;
		}
	}
	else
	{
		NowYaw = fTarget;
	}

	ObjRollOverGuard(&NowYaw);
}

clsCharactor::clsCharactor() :
	HP( 0 ),
	m_MaxHP( 0 ),
	m_bDeadFlg( false ),
	m_bMoving( false ),
	fPushMin( 0.0f ),
	m_fMoveSpeedMax( 0.0f ),
	m_iTopMoveSpeedFrame( 0 ),
	m_fMoveAccele( 0.0f ),
	m_iMoveStopFrame( 0 ),
	m_fMoveDecele( 0.0f ),
	m_fRotSpeed( 0.0f ),
	m_fJumpPower( 0.0f ),
	RaySpece( 0.0f ),
	m_pMeshForRay( NULL )
{
//	ZeroMemory(this, sizeof(clsCharactor));
}

clsCharactor::~clsCharactor()
{
	SAFE_RELEASE( m_pMeshForRay );
}
