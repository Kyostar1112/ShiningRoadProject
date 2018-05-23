#include "SceneMission.h"


//================================//
//========== �~�b�V�������N���X ==========//
//================================//
clsSCENE_MISSION::clsSCENE_MISSION( clsPOINTER_GROUP* const ptrGroup ) : clsSCENE_BASE( ptrGroup ),
	m_pTestRobo( nullptr ),
	m_pTestChara( nullptr )
{
}

clsSCENE_MISSION::~clsSCENE_MISSION()
{
	SAFE_DELETE( m_pTestChara );
	SAFE_DELETE( m_pTestRobo );
}

//�������Ɉ�x�����ʂ鏈��.
void clsSCENE_MISSION::CreateProduct()
{
	m_pTestRobo = new clsTestObj;
	m_pTestRobo->Init(nullptr, nullptr, nullptr, m_wpDxInput, m_wpPtrGroup);//4�ڂ̈����͌��ʉ���G�t�F�N�g���o�����߂ɒǉ����܂���.

	D3DXVECTOR3 tmpVec3 = { 0.0f, 10.0f, 0.0f };
	m_pTestRobo->SetPosition(tmpVec3);
	m_pTestRobo->SetScale(0.01f);

	//�e�X�g���f���̏�����.
	m_pTestChara = new clsCharaStatic;
	m_pTestChara->AttachModel( 
		m_wpResource->GetStaticModels( 
			clsResource::enSTATIC_MODEL::enStaticModel_Enemy ) );
	m_pTestChara->Init();
	m_pTestChara->SetPosition( D3DXVECTOR3( -2.0f, 0.0f, 0.0f ) );
	m_pTestChara->SetRotation( D3DXVECTOR3( 0.0f, 0.0f, D3DX_PI*0.5 ) );

	m_pStage = m_wpResource->GetStaticModels(clsResource::enStaticModel_Ground);
	m_pStage->m_Trans.fScale = 10.0f;
	m_pStage->m_Trans.fYaw = 0.0f;
	m_pStage->m_Trans.fRoll = 0.0f;
	m_pStage->m_Trans.fPitch = 0.0f;
	m_pStage->m_Trans.vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//���t���[���ʂ鏈��.
void clsSCENE_MISSION::UpdateProduct( enSCENE &nextScene )
{
	//null�Ȃ�assert.
	ASSERT_IF_NULL( m_pTestRobo );
	m_pTestRobo->Action(m_pStage);

	//�G���f�B���O�ɍs���ꍇ�͈ȉ��̂悤�ɂ���.
	if( !"�N���A�����𖞂����Ƃ�����ʂ�" ){
		nextScene = enSCENE::ENDING;
	}
}

//�`��.
void clsSCENE_MISSION::RenderProduct( const D3DXVECTOR3 &vCamPos )
{
	//Render�֐��̈����������₷�����邽�߂̕ϐ�.
	D3DXVECTOR3 vTmp = m_pTestRobo->m_Trans.vPos;
	m_wpCamera->SetPos(vTmp);

	vTmp = m_pTestRobo->m_Trans.vPos - (m_pTestRobo->GetVec3Dir(m_pTestRobo->m_Trans.fYaw, vDirForward) * 2);
	vTmp.y += 0.5f;
	m_wpCamera->SetPos(vTmp, false);

	m_pTestChara->Render(m_mView, m_mProj, m_vLight, vCamPos);
	m_pTestRobo->Render(m_mView, m_mProj, m_vLight, vCamPos);
	m_pStage->Render(m_mView, m_mProj, m_vLight, vCamPos);
}
