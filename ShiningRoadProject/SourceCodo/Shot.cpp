#define _CRT_SECURE_NO_WARNINGS
#include"Shot.h"

const int g_iColNum = 1;

clsShot::clsShot(clsPOINTER_GROUP* pPtrGroup)
{
	ZeroMemory(this, sizeof(clsShot));

	m_wpEffect = pPtrGroup->GetEffects();
}

clsShot::~clsShot()
{
}

HRESULT clsShot::Init(BulletState BState)
{
	//strWeaponFileName��������󂯎��.
	//���̑傫��.
	//����.
	//�G�t�F�N�g.
	m_ShotState = BState;

	//�����蔻��̑傫�������߂�.
	m_ppColSpheres = new clsObject::SPHERE * [g_iColNum];

	for (int i = 0; i < g_iColNum; i++)
	{
		m_ppColSpheres[i]->vCenter = &m_Trans.vPos;
		m_ppColSpheres[i]->fRadius = 1.0f;
	}
	
	//�m�F�p�̨̽��������ݸނ���.
	//�����蔻��Ƃ��ẮA�����ȍ~�͕s�v.

#ifdef _DEBUG
	//m_pBodySphere = clsResource::GetInstance()->GetStaticModels(clsResource::enStaticModel_Shpere);
#endif

	return S_OK;
}

bool clsShot::Hit(SPHERE* ppTargetSphere,int iSphereMax)
{
	if (m_bShotExistFlg)
	{
		for (int i = 0; i < g_iColNum; i++)
		{
			for (int j = 0; j < iSphereMax; i++)
			{
				if (Collision(*m_ppColSpheres[i], ppTargetSphere[j]))
				{
					m_ShotEfcHandles[enEfcHit] = m_wpEffect->Play(m_ShotState.iHitEfcNum, m_Trans.vPos);
					m_wpEffect->Stop(m_ShotEfcHandles[enEfcShot]);
					m_bShotExistFlg = false;
					return true;
				}
			}
		}
	}

	return false;
}

bool clsShot::Form(D3DXVECTOR3 vShotPos, D3DXVECTOR3 vTarget)
{
	if (m_bExistFlg)
	{
		return false;
	}

	D3DXMATRIX mInv;

	D3DXMatrixTranslation(
		&mInv,
		vTarget.x,
		vTarget.y,
		vTarget.z
		);

	D3DXMatrixInverse(&mInv, NULL, &mInv);

	D3DXVECTOR3 vStart,vTar;

	D3DXVec3TransformCoord(&vStart, &vShotPos, &mInv);
	D3DXVec3TransformCoord(&vTar, &vTarget, &mInv);

	m_vMoveDir = vTar - vStart;
	D3DXVec3Normalize(&m_vMoveDir, &m_vMoveDir);

	m_Trans.vPos = m_vStartPos = vShotPos - m_vMoveDir * m_fMoveSpeed;

	m_bShotExistFlg = true;
	m_bExistFlg = true;

	//Excel�̍s�ԍ�	���W.
	m_ShotEfcHandles[enEfcShot] = m_wpEffect->Play(m_ShotState.iShotEfcNum, m_Trans.vPos);
	m_ShotEfcHandles[enEfcLine] = m_wpEffect->Play(m_ShotState.iLineEfcNum, m_Trans.vPos);

	return true;
}

void clsShot::Move()
{
	if (!m_bShotExistFlg)
	{
		if (!m_wpEffect->isPlay(m_ShotEfcHandles[enEfcLine]) && !m_wpEffect->isPlay(m_ShotEfcHandles[enEfcHit]))
		{
			m_bExistFlg = false;
		}
		return;
	}

	if (D3DXVec3Length(&(m_Trans.vPos - m_vStartPos)) > 50.0f)
	{
		m_wpEffect->Stop(m_ShotEfcHandles[enEfcShot]);
		m_bShotExistFlg = false;
	}

	if (!m_bShotExistFlg)
	{
		m_Trans.vPos += m_vMoveDir  * m_fMoveSpeed;
	}

	//���W.
	m_wpEffect->SetPosition(m_ShotEfcHandles[enEfcShot], m_Trans.vPos);
	m_wpEffect->SetPosition(m_ShotEfcHandles[enEfcLine], m_Trans.vPos);

}

void clsShot::ReStart()
{
	m_bShotExistFlg = false;//�e�̑��݊m�F(false�Ȃ�e�����݂��Ȃ����).
	m_bExistFlg = false;//�e,����,�O�Ղ̑��݊m�F(false�Ȃ炻���S�Ă����݂��Ȃ����)
}

