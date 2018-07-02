#define _CRT_SECURE_NO_WARNINGS
#include"Shot.h"

const int g_iColNum = 1;

clsShot::clsShot(clsPOINTER_GROUP* pPtrGroup)
{
	ZeroMemory(this, sizeof(clsShot));
}

clsShot::~clsShot()
{
}

HRESULT clsShot::Init(LPSTR strWeaponFolderName)
{
	//strWeaponFileName��������󂯎��.
	//���̑傫��.
	//����.
	//�G�t�F�N�g.


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
					//m_pEffect->SetLocation(m_HitEfcH, m_Trans.vPos);
					m_HitEfcH = //m_pEffect->Play(clsEffects::enEFFECTS_ARBIA_ATK,m_Trans.vPos);

					//m_pEffect->SetScale(m_HitEfcH, D3DXVECTOR3(1.0f,1.0f,1.0f));

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

	m_vMoveAxis = vTar - vStart;
	D3DXVec3Normalize(&m_vMoveAxis, &m_vMoveAxis);

	m_Trans.vPos = m_vStartPos = vShotPos - m_vMoveAxis * m_fMoveSpeed;

	m_bShotExistFlg = true;
	m_bExistFlg = true;

	return true;
}

void clsShot::Move()
{
	if (!m_bShotExistFlg)
	{
		/*if (!//m_pEffect->PlayCheck(m_LineEfcH) && !//m_pEffect->PlayCheck(m_HitEfcH))
		{
			m_bExistFlg = false;
		}

		//m_pEffect->Stop(m_ShotEfcH);*/
		return;
	}

	if (D3DXVec3Length(&(m_Trans.vPos - m_vStartPos)) > 50.0f)
	{
		//m_pEffect->Stop(m_ShotEfcH);
		m_bShotExistFlg = false;
	}

	/*if (!//m_pEffect->PlayCheck(m_ShotEfcH))
	{
		/*m_ShotEfcH = //m_pEffect->Play(m_Trans.vPos, ShotEfcTypes.ShotEfcType, m_UseChar);
		//m_pEffect->SetScale(m_ShotEfcH, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
		m_LineEfcH = //m_pEffect->Play(m_Trans.vPos, ShotEfcTypes.LineEfcType, m_UseChar);
		//m_pEffect->SetScale(m_LineEfcH, D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	}

	else
	{
		m_Trans.vPos += m_vMoveAxis  * m_fMoveSpeed;
	}

	//m_pEffect->SetLocation(m_ShotEfcH, m_Trans.vPos);
	//m_pEffect->SetLocation(m_LineEfcH, m_Trans.vPos);*/

}

void clsShot::ReStart()
{
	m_bShotExistFlg = false;//�e�̑��݊m�F(false�Ȃ�e�����݂��Ȃ����).
	m_bExistFlg = false;//�e,����,�O�Ղ̑��݊m�F(false�Ȃ炻���S�Ă����݂��Ȃ����)
}
