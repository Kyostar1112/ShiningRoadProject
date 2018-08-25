#include "SceneMission.h"


//================================//
//========== �~�b�V�������N���X ==========//
//================================//
clsSCENE_MISSION::clsSCENE_MISSION(clsPOINTER_GROUP* const ptrGroup) : clsSCENE_BASE(ptrGroup),
m_pPlayer(nullptr)
, m_bEnemyStop(false)
, m_bCamTarChange(false)
{
}

clsSCENE_MISSION::~clsSCENE_MISSION()
{
	//SAFE_DELETE( m_pTestChara );
	SAFE_DELETE(m_pPlayer);
}

//�������Ɉ�x�����ʂ鏈��.
void clsSCENE_MISSION::CreateProduct()
{
	CreateFriends();
	CreateEnemys();

	CreateUI();

	m_pCamTar = m_pPlayer;

	//�e�X�g���f���̏�����.

	m_pStage = new clsStage(m_wpResource);

	m_fCamMoveSpeed = 0.01f;
}

void clsSCENE_MISSION::CreateUI()
{
	assert(!m_pLimitTime);
	char pText[STR_BUFF_MAX];
	D3DXVECTOR2 vPos = { 0.0f, 0.0f };

	m_pLimitTime = new clsUiText;
	m_pLimitTime->Create(m_wpPtrGroup->GetContext(), WND_W, WND_H, 3.0f);
	m_pLimitTime->SetPos(vPos);

	sprintf_s(pText,"");

	m_pLimitTime->SetText(pText);

	assert(!m_pLBulletNum);
	vPos = { 250.0f, 0.0f };

	m_pLBulletNum = new clsUiText;
	m_pLBulletNum->Create(m_wpPtrGroup->GetContext(), WND_W, WND_H, 3.0f);
	m_pLBulletNum->SetPos(vPos);

	sprintf_s(pText, "");

	m_pLBulletNum->SetText(pText);

	assert(!m_pRBulletNum);
	vPos = { WND_W / 2 + 250.0f, 0.0f };

	m_pRBulletNum = new clsUiText;
	m_pRBulletNum->Create(m_wpPtrGroup->GetContext(), WND_W, WND_H, 3.0f);
	m_pRBulletNum->SetPos(vPos);

	sprintf_s(pText, "");

	m_pRBulletNum->SetText(pText);

	assert(!m_pHP);
	vPos = { WND_W / 2, 0.0f };

	m_pHP = new clsUiText;
	m_pHP->Create(m_wpPtrGroup->GetContext(), WND_W, WND_H, 3.0f);
	m_pHP->SetPos(vPos);

	sprintf_s(pText, "");

	m_pHP->SetText(pText);
}

//���t���[���ʂ鏈��.
void clsSCENE_MISSION::UpdateProduct( enSCENE &enNextScene )
{
	//null�Ȃ�assert.
	assert(m_pPlayer);
	//m_pPlayer->Action(m_pStage);

	if (GetAsyncKeyState('C') & 0x1)
	{
		if (!m_bCamTarChange)
		{
			m_bCamTarChange = true;
			m_pCamTar = m_pTestObj;
		}

		else
		{
			m_bCamTarChange = false;
			m_pCamTar = m_pPlayer;
		}
	}
	
	if (GetAsyncKeyState('S') & 0x1)
	{
		if (!m_bEnemyStop)
		{
			m_bEnemyStop = true;
		}

		else
		{
			m_bEnemyStop = false;
		}
	}

	for (int i = 0; i < m_v_pFriends.size(); i++)
	{
		m_v_pFriends[i]->Action(m_pStage);
	}

	if (!m_bEnemyStop)
	{
		for (int i = 0; i < m_v_pEnemys.size(); i++)
		{
			m_v_pEnemys[i]->Action(m_pStage);
		}
	}

	//D3DXVECTOR3 vCamPosTmp = m_pPlayer->GetCamTargetPos();
	//D3DXVECTOR3 vLookPosTmp = m_pPlayer->GetLookTargetPos();

	UpdateCamTargetPos(m_pCamTar);

	m_wpCamera->SetPos(m_vCamTargetPos, false);
	m_wpCamera->SetLookPos(m_vLookTargetPos);

	//�G���f�B���O�ɍs���ꍇ�͈ȉ��̂悤�ɂ���.
	if (AllEnemyDead()){
		enNextScene = enSCENE::ENDING;
	}

	if (m_pPlayer->m_bDeadFlg){
		enNextScene = enSCENE::ENDING;
	}
}

//�`��.
void clsSCENE_MISSION::RenderProduct( const D3DXVECTOR3 &vCamPos )
{

	//m_pTestChara->Render(m_mView, m_mProj, m_vLight, vCamPos);

	for (int i = 0; i < m_v_pFriends.size(); i++)
	{
		m_v_pFriends[i]->Render(m_mView, m_mProj, m_vLight, vCamPos);
	}

	for (int i = 0; i < m_v_pEnemys.size(); i++)
	{
		m_v_pEnemys[i]->Render(m_mView, m_mProj, m_vLight, vCamPos);
	}

	Collison();

	m_pStage->Render(m_mView, m_mProj, m_vLight, vCamPos);
}

void clsSCENE_MISSION::RenderUi()
{
	int iTmp = m_pPlayer->m_iActivityLimitTime;
	int iMin = iTmp / 3600;
	int iSecond = (iTmp - (iMin * 3600)) / 60;
	int iN = iTmp % 100;

	char pText[STR_BUFF_MAX];

	sprintf_s(pText, "%d:%d:%d", iMin, iSecond, iN);
	m_pLimitTime->SetText(pText);
	m_pLimitTime->Render();

	int iNowNum = m_pPlayer->m_v_pWeapons[clsRobo::enWeaponLHand]->GetNowBulletNum();
	int iMaxNum = m_pPlayer->m_v_pWeapons[clsRobo::enWeaponLHand]->GetMaxBulletNum();

	sprintf_s(pText, "%d/%d", iNowNum, iMaxNum);
	m_pLBulletNum->SetText(pText);
	m_pLBulletNum->Render();

	iNowNum = m_pPlayer->m_v_pWeapons[clsRobo::enWeaponRHand]->GetNowBulletNum();
	iMaxNum = m_pPlayer->m_v_pWeapons[clsRobo::enWeaponRHand]->GetMaxBulletNum();

	sprintf_s(pText, "%d/%d", iNowNum, iMaxNum);
	m_pRBulletNum->SetText(pText);
	m_pRBulletNum->Render();

	int iHP = m_pPlayer->m_HP;

	sprintf_s(pText, "%d", iHP);
	m_pHP->SetText(pText);
	m_pHP->Render(clsUiText::enPOS::MIDDLE);
}

bool clsSCENE_MISSION::AllEnemyDead()
{
	for (int i = 0; i < m_v_pEnemys.size(); i++)
	{
		if (!m_v_pEnemys[i]->m_bDeadFlg)
		{
			return false;
		}
	}

	return true;
}

void clsSCENE_MISSION::CreateFriends()
{
	m_pPlayer = CreatePlayer();
	m_v_pFriends.push_back(m_pPlayer);

	m_v_pFriends.shrink_to_fit();
}

void clsSCENE_MISSION::CreateEnemys()
{
	clsCharactor* pChara;

	for (int i = 0; i < 1; i++)
	{
		pChara = CreateEnemy();

		m_v_pEnemys.push_back(pChara);
	}

	m_v_pEnemys.shrink_to_fit();
}

void clsSCENE_MISSION::Collison()
{
	ColFShottoEBody();
	ColEShottoFBody();
}

//���L������Shot�����L������Body�ɓ����锻������邩�͏����̌��ˍ����œ����.
void clsSCENE_MISSION::ColFShottoFBody()
{
	for (int i = 0; i < m_v_pFriends.size(); i++)
	{
		for (int j = 0; j < m_v_pFriends.size(); j++)
		{
			HitState Tmp = m_v_pFriends[i]->BulletHit(m_v_pFriends[j]->m_v_Spheres);
			Tmp.iDamage = 0;
			m_v_pFriends[j]->Damage(Tmp);
		}
	}
}

void clsSCENE_MISSION::ColFShottoEBody()
{
	for (int i = 0; i < m_v_pFriends.size(); i++)
	{
		for (int j = 0; j < m_v_pEnemys.size(); j++)
		{
			HitState Tmp = m_v_pFriends[i]->BulletHit(m_v_pEnemys[j]->m_v_Spheres);
			m_v_pEnemys[j]->Damage(Tmp);
		}
	}
}

void clsSCENE_MISSION::ColEShottoFBody()
{
	for (int i = 0; i < m_v_pEnemys.size(); i++)
	{
		for (int j = 0; j < m_v_pFriends.size(); j++)
		{
			HitState Tmp = m_v_pEnemys[i]->BulletHit(m_v_pFriends[j]->m_v_Spheres);
			m_v_pFriends[j]->Damage(Tmp);
		}
	}
}

void clsSCENE_MISSION::ColEShottoEBody()
{
	for (int i = 0; i < m_v_pEnemys.size(); i++)
	{
		for (int j = 0; j < m_v_pEnemys.size(); j++)
		{
			HitState Tmp = m_v_pEnemys[i]->BulletHit(m_v_pEnemys[j]->m_v_Spheres);
			Tmp.iDamage = 0;
			m_v_pEnemys[j]->Damage(Tmp);
		}
	}
}

clsPlayer* clsSCENE_MISSION::CreatePlayer()
{
	clsPlayer* pPlayer = new clsPlayer;
	pPlayer->Init(m_wpPtrGroup);//4�ڂ̈����͌��ʉ���G�t�F�N�g���o�����߂ɒǉ����܂���.

	D3DXVECTOR3 tmpVec3 = { 0.0f, 10.0f, 0.0f };
	pPlayer->SetPosition(tmpVec3);
	pPlayer->SetScale(0.01f);

	return pPlayer;
}

clsTestObj* clsSCENE_MISSION::CreateEnemy()
{
	clsTestObj* pEnemy = new clsTestObj;
	pEnemy->Init(m_wpPtrGroup,"",m_v_pFriends);//4�ڂ̈����͌��ʉ���G�t�F�N�g���o�����߂ɒǉ����܂���.

	D3DXVECTOR3 tmpVec3 = { 0.0f, 10.0f, 0.0f };
	pEnemy->SetPosition(tmpVec3);
	pEnemy->SetScale(0.01f);

	m_pTestObj = pEnemy;

	return pEnemy;
}

//============================ �f�o�b�O�e�L�X�g ===========================//
#if _DEBUG
void clsSCENE_MISSION::RenderDebugText()
{
	//NULL�`�F�b�N.
	assert( m_upText );

	char strDbgTxt[256];
	int iTxtY = 0;
	const int iOFFSET = 10;//��s���ɂǂꂾ�����ɂ��炷��.

	/*sprintf_s( strDbgTxt, 
		"PlayerPos : x[%f], y[%f], z[%f]",
		m_pPlayer->GetPosition().x,
		m_pPlayer->GetPosition().y, 
		m_pPlayer->GetPosition().z);
	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

	sprintf_s( strDbgTxt, 
		"CamLokPos : x[%f], y[%f], z[%f]",
		GetCameraLookPos().x, GetCameraLookPos().y, GetCameraLookPos().z );
	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

	sprintf_s(strDbgTxt,
		"CamPos : x[%f], y[%f], z[%f]",
		GetCameraPos().x, GetCameraPos().y, GetCameraPos().z);
	m_upText->Render(strDbgTxt, 0, iTxtY += iOFFSET);

	sprintf_s(strDbgTxt,
		"Enelgy : [%d]",
		m_pPlayer->m_iEnelgy);
	m_upText->Render(strDbgTxt, 0, iTxtY += iOFFSET);
	
	if (m_pPlayer->m_bBoost)
	{
		sprintf_s(strDbgTxt,"ON");
		m_upText->Render(strDbgTxt, 0, iTxtY += iOFFSET);
	}

	else
	{
		sprintf_s(strDbgTxt,"OFF");
		m_upText->Render(strDbgTxt, 0, iTxtY += iOFFSET);
	}

	//dbgtxty += 10;
	//if( m_pBgm[0]->IsStopped() ){
	//	sprintf_s( strDbgTxt, "Stopped" );
	//	m_pText->Render( strDbgTxt, 0, dbgtxty );
	//}
	//if( m_pBgm[0]->IsPlaying() ){
	//	sprintf_s( strDbgTxt, "Playingn" );
	//	m_pText->Render( strDbgTxt, 0, dbgtxty );
	//}*/
}
#endif //#if _DEBUG

void clsSCENE_MISSION::UpdateCamTargetPos(clsCharactor* pChara)
{
	if (!pChara)
	{
		return;
	}

	const float fCamMoveSpeed = 0.5f;
	const float fLookPosSpace = 50.0f;
	const float fCamSpaceTmp = 2.0f;
	const float fCamPosX = 0.5f;

	D3DXMATRIX mRot;

	//�J�����ʒu�̂��߂̉�]�s��쐬.
	D3DXMatrixRotationYawPitchRoll(
		&mRot,
		pChara->m_Trans.fYaw,
		-pChara->m_fLookUpDir,
		pChara->m_Trans.fRoll);

	//���޸�ق�p��.
	float fCamAxisXTmp = 0.0f;

	/*if (m_bCamPosXSwitch)
	{
		fCamAxisXTmp = fCamPosX;
	}

	else
	{
		fCamAxisXTmp = -fCamPosX;
	}*/

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
	const D3DXVECTOR3 vCamTargetPos = pChara->m_vCenterPos - vCamAxis * fCamSpaceTmp;

	//���݈ʒu���擾���A���݈ʒu�ƖړI�̈ʒu�̍�����ړ��ʂ��v�Z����.
	vCamPosTmp = m_vCamTargetPos;//���݈ʒu���擾
	vCamPosTmp -= (vCamPosTmp - vCamTargetPos) * fCamMoveSpeed;

	m_vLookTargetPos = vCamPosTmp + vLookAxis * fLookPosSpace;

	m_vCamTargetPos = vCamPosTmp;
}