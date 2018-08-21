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

	m_v_Spheres.resize(g_iColNum);

	for (int i = 0; i < g_iColNum; i++)
	{
		m_v_Spheres[i].vCenter = &m_Trans.vPos;
		m_v_Spheres[i].fRadius = m_ShotState.fScale;
	}
	
	//�m�F�p�̨̽��������ݸނ���.
	//�����蔻��Ƃ��ẮA�����ȍ~�͕s�v.

#ifdef _DEBUG
	//m_pBodySphere = clsResource::GetInstance()->GetStaticModels(clsResource::enStaticModel_Shpere);
#endif

	return S_OK;
}

bool clsShot::Hit(std::vector<clsObject::SPHERE> p_v_TargetSphere)
{
	if (m_bShotExistFlg)
	{
		for (int i = 0; i < g_iColNum; i++)
		{
			for (int j = 0; j < p_v_TargetSphere.size(); i++)
			{
				if (Collision(m_v_Spheres[i], p_v_TargetSphere[j]))
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

bool clsShot::Form(D3DXVECTOR3 vShotPos, D3DXVECTOR3 vDir)
{
	if (m_bExistFlg)
	{
		return false;
	}	

	m_vMoveDir = vDir;

	m_Trans.vPos = m_vStartPos = vShotPos;

	m_bShotExistFlg = true;
	m_bExistFlg = true;

	//Excel�̍s�ԍ�	���W.
	m_ShotEfcHandles[enEfcShot] = m_wpEffect->Play(m_ShotState.iShotEfcNum, m_Trans.vPos);
	m_ShotEfcHandles[enEfcLine] = m_wpEffect->Play(m_ShotState.iLineEfcNum, m_Trans.vPos);

	return true;
}

void clsShot::Move()
{
	if (!m_bExistFlg)
	{
		return;
	}

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
		return;
	}

	m_Trans.vPos += m_vMoveDir * m_ShotState.fSpeed;
	
	//���W.
	m_wpEffect->SetPosition(m_ShotEfcHandles[enEfcShot], m_Trans.vPos);
	m_wpEffect->SetPosition(m_ShotEfcHandles[enEfcLine], m_Trans.vPos);

}

void clsShot::ReStart()
{
	m_bShotExistFlg = false;//�e�̑��݊m�F(false�Ȃ�e�����݂��Ȃ����).
	m_bExistFlg = false;//�e,����,�O�Ղ̑��݊m�F(false�Ȃ炻���S�Ă����݂��Ȃ����)
}

