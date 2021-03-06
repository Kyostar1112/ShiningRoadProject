#define _CRT_SECURE_NO_WARNINGS
#include"Shot.h"

const int g_iColNum = 1;

clsShot::clsShot(clsPOINTER_GROUP* pPtrGroup)
	: m_fRangeMax(0.0f)
{
	m_wpEffect = pPtrGroup->GetEffects();
}

clsShot::~clsShot()
{
}

HRESULT clsShot::Init(BulletState BState)
{
	//strWeaponFileNameから情報を受け取る.
	//球の大きさ.
	//音量.
	//エフェクト.
	m_ShotState = BState;

	//当たり判定の大きさを決める.

	//m_v_Spheres.resize(g_iColNum);

	clsObject::SPHERE Tmp;
	Tmp.vCenter = &m_Trans.vPos;
	Tmp.fRadius = m_ShotState.fScale;

	m_v_Spheres.push_back(Tmp);
	m_v_Spheres.shrink_to_fit();
	
	//確認用のｽﾌｨｱをﾚﾝﾀﾞﾘﾝｸﾞする.
	//当たり判定としては、ここ以降は不要.

#ifdef _DEBUG
	//m_pBodySphere = clsResource::GetInstance()->GetStaticModels(clsResource::enStaticModel_Shpere);
#endif

	return S_OK;
}

bool clsShot::Hit(std::vector<clsObject::SPHERE> v_TargetSphere)
{
	if (m_bShotExistFlg)
	{
		for (unsigned int i = 0; i < g_iColNum; i++)
		{
			for (unsigned int j = 0; j < v_TargetSphere.size(); j++)
			{
				float fLenght = D3DXVec3Length(&(*m_v_Spheres[i].vCenter - *v_TargetSphere[j].vCenter));
				
				//ショットの速度が速すぎて当たらない問題を解消.
				D3DXVECTOR3 vTmpPos = *m_v_Spheres[i].vCenter;
				if ((fLenght + m_v_Spheres[i].fRadius) < m_ShotState.fSpeed)
				{
					*m_v_Spheres[i].vCenter += m_vMoveDir * fLenght;
				}

				if (Collision(m_v_Spheres[i], v_TargetSphere[j]))
				{
					m_ShotEfcHandles[enEfcHit] = m_wpEffect->Play(m_ShotState.iHitEfcNum, m_Trans.vPos);
					m_wpEffect->Stop(m_ShotEfcHandles[enEfcShot]);
					m_wpEffect->Stop(m_ShotEfcHandles[enEfcLine]);
					m_bShotExistFlg = false;
					return true;
				}

				*m_v_Spheres[i].vCenter = vTmpPos;
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

	//Excelの行番号	座標.
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

	if (D3DXVec3Length(&(m_Trans.vPos - m_vStartPos)) > m_ShotState.fRangeMax)
	{
		m_wpEffect->Stop(m_ShotEfcHandles[enEfcShot]);
		m_wpEffect->Stop(m_ShotEfcHandles[enEfcLine]);
		m_bShotExistFlg = false;
		return;
	}

	m_Trans.vPos += m_vMoveDir * m_ShotState.fSpeed;
	
	//座標.
	m_wpEffect->SetPosition(m_ShotEfcHandles[enEfcShot], m_Trans.vPos);
	m_wpEffect->SetPosition(m_ShotEfcHandles[enEfcLine], m_Trans.vPos);
}

void clsShot::ReStart()
{
	m_bShotExistFlg = false;//弾の存在確認(falseなら弾が存在しない状態).
	m_bExistFlg = false;//弾,爆発,軌跡の存在確認(falseならそれら全てが存在しない状態)
}

