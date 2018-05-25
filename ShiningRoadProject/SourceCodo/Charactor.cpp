#include"Charactor.h"

void clsCharactor::SetMoveAcceleSpeed(float fMoveSpeedMax, int iTopSpeedFrame)//����.
{
	m_fMoveSpeedMax = fMoveSpeedMax;
	m_iTopSpeedFrame = iTopSpeedFrame;

	m_fMoveAccele = m_fMoveSpeedMax / m_iTopSpeedFrame;

	SetMoveDecelerationSpeed(m_iTopSpeedFrame);
}

void clsCharactor::SetMoveDecelerationSpeed(const int iStopFrame)//����.
{
	m_iStopFrame = iStopFrame;

	m_fMoveDecele = abs(m_fMoveSpeed) / m_iStopFrame;
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
	vForward = GetVec3Dir(m_Trans.fYaw, vDirForward);

	//�s����������.

	D3DXVECTOR3 vAcceleDir = GetVec3Dir(fAngle, vForward);

	m_vMoveDir += (vAcceleDir - m_vMoveDir) / (m_iStopFrame / 2);
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

	SetMoveDecelerationSpeed(m_iStopFrame);
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
		m_vMoveDir = GetVec3Dir(m_Trans.fYaw, vDirForward);
	}
}

//��].
void clsCharactor::SetRotationSpeed(const float fSpd)
{
	m_fRotSpd = fSpd;
}

bool clsCharactor::IsRotate()
{
	return m_bRotation;
}

bool clsCharactor::IsRotControl()
{
	if (abs(m_fRotSpd) > m_fRotSpdMax)
	{
		return false;
	}

	return true;
}
void clsCharactor::RotAccele(const float fPower)
{
	m_fRotSpd += m_fRotAccele * fPower;

	if (abs(m_fRotSpd) > m_fRotSpdMax)
	{
		m_fRotSpd = m_fRotSpdMax * (m_fRotSpd / abs(m_fRotSpd));
	}
}

void clsCharactor::RotDecele()
{
	m_fRotSpd -= m_fRotDecele;
}

void SetRotationSpeed(const float fRotSpeedMax, const int iTopRotSpdFrame);
void SetRotationSpeed(const int iRotStopFrame);

void clsCharactor::Rotate(const float fAngle, const float fPush)
{
	Spin(m_Trans.fYaw, fAngle, m_fRotSpd, m_fRotSpd);
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
	m_fMoveSpeed( 0.0f ),
	m_fMoveSpeedMax( 0.0f ),
	m_iTopSpeedFrame( 0 ),
	m_fMoveAccele( 0.0f ),
	m_iStopFrame( 0 ),
	m_fMoveDecele( 0.0f ),
	m_vMoveDir( { 0.0f, 0.0f, 0.0f } ),
	m_fRotSpd( 0.0f ),
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
