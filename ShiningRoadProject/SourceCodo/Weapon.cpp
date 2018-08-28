#include"Weapon.h"

void clsWeapon::Create(WeaponState State)
{
	m_State = State;

	m_ppBullet = new clsShot *[m_State.iBulletNumMax];

	for (int i = 0; i < m_State.iBulletNumMax; i++)
	{
		m_ppBullet[i] = new clsShot(m_pPtrGroup);
		m_ppBullet[i]->Init(m_State.BState);
	}

	Reload();
	LockOut();
}


void clsWeapon::Update()
{
	for (int i = 0; i < m_State.iBulletNumMax; i++)
	{
		m_ppBullet[i]->Move();
	}
}

int clsWeapon::Hit(std::vector<clsObject::SPHERE> v_TargetSphere)
{
	int iResult = 0;

	for (int i = 0; i < m_State.iBulletNumMax; i++)
	{
		if (m_ppBullet[i]->Hit(v_TargetSphere))
		{
			iResult += m_State.iAtk;
		}
	}
	
	return iResult;
}

bool clsWeapon::Shot()
{
	if (m_iRemainingBullet > 0 || 
		m_iReloadCnt < 0)
	{
		D3DXVECTOR3 vPos = *m_State.SState.vShotStartPos;
		D3DXVECTOR3 vDir = *m_State.SState.vShotMoveDir;

		int iRandMax = m_State.iStablity;

		if (m_pTargetObj)//�^�[�Q�b�g����Ȃ�΍��ˌ�.
		{
			int iTime;
			float fDis,fVerDevia;
			D3DXVECTOR3 vHorDevia, vPrediction;

			fDis = D3DXVec3Length(&(vPos - m_pTargetObj->m_vCenterPos));//�^�[�Q�b�g�Ƃ̌��݋���.
			iTime = (int)(fDis / m_State.BState.fSpeed);//���B�܂ł̎���(���Ǝv������)

			fVerDevia = m_pTargetObj->m_fFollPower * iTime;//���������̗\������.

			vHorDevia = (m_pTargetObj->m_vMoveDir * m_pTargetObj->m_fMoveSpeed) * iTime;//���������ړ��x�N�g�� x ���B�\�z���� = ���������̗\�z����.
			vPrediction = m_pTargetObj->m_vCenterPos;//�\���ʒu�ɂ܂��̓^�[�Q�b�g�̈ʒu������.

			vPrediction += vHorDevia;//�����̂ݗ\���ʒu.
			vPrediction.y += fVerDevia;//�\���ʒu.

			D3DXVECTOR3 vDirTmp = vPrediction - vPos;

			D3DXVec3Normalize(&vDir, &vDirTmp);
		}

		if (iRandMax != 0)//0���Ǝ~�܂�.
		{
			float fDirError;//�����덷.
			fDirError = (float)(rand() % (iRandMax * 2) - iRandMax) * g_fDistanceReference;
			vDir.x += fDirError;//x���̌덷.

			fDirError = (float)(rand() % (iRandMax * 2) - iRandMax) * g_fDistanceReference;
			vDir.y += fDirError;//y���̌덷.

			fDirError = (float)(rand() % (iRandMax * 2) - iRandMax) * g_fDistanceReference;
			vDir.z += fDirError;//z���̌덷.
		}
		
		for (int i = 0; i < m_State.iBulletNumMax; i++)
		{
			if (m_ppBullet[i]->Form(vPos, vDir))
			{
				m_iRemainingBullet--;
				m_iReloadCnt = m_State.iReloadTime;
				return true;
			}
		}
	}

	m_iReloadCnt--;

	return false;
}

bool clsWeapon::IsNeedReload()
{
	if (m_iRemainingBullet > 0)
	{
		//�ˌ��\.
		return false;
	}

	Reload();

	return true;
}

void clsWeapon::Reload()
{
	m_iRemainingBullet = m_State.iBulletNumMax;
}

int clsWeapon::GetNowBulletNum()
{
	return m_iRemainingBullet;
}

int clsWeapon::GetMaxBulletNum()
{
	return m_State.iBulletNumMax;
}

bool clsWeapon::IsLock()
{
	if (m_pTargetObj)
	{
		return true;
	}

	return false;
}

void clsWeapon::Lock(clsObject* pTargetObj)//���b�N�͈͂ɓ����Ă���.
{
	if (!pTargetObj)
	{
		return;
	}

	if (m_pTargetObj)
	{
		return;
	}

	m_iLockTime--;

	if (m_iLockTime < 0)
	{
		if (pTargetObj)
		{
			m_pTargetObj = pTargetObj;
		}
	}
}

void clsWeapon::LockOut()//���b�N�������.
{
	m_iLockTime = m_State.iLockSpeed * static_cast<int>(g_fFPS);
	m_pTargetObj = nullptr;
}

clsWeapon::clsWeapon(clsPOINTER_GROUP* pPtrGroup) 
	: m_pTargetObj(nullptr)
{
	m_pPtrGroup = pPtrGroup;
}

clsWeapon::~clsWeapon()
{
}