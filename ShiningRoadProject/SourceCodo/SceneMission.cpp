#include "SceneMission.h"


//================================//
//========== �~�b�V�������N���X ==========//
//================================//
clsMISSION::clsMISSION( clsPOINTER_GROUP* const ptrGroup ) : clsSCENE_BASE( ptrGroup ),
	m_pTestRobo( nullptr ),
	m_pTestChara( nullptr )
{
}

clsMISSION::~clsMISSION()
{
	SAFE_DELETE( m_pTestChara );
	SAFE_DELETE( m_pTestRobo );
}

//�������Ɉ�x�����ʂ鏈��.
void clsMISSION::CreateProduct()
{
	m_pTestRobo = new clsRobo;
	m_pTestRobo->RoboInit( nullptr, nullptr, nullptr, m_wpPtrGroup );//4�ڂ̈����͌��ʉ���G�t�F�N�g���o�����߂ɒǉ����܂���.

	D3DXVECTOR3 tmpVec3 = { 0.0f, -2.0f, 0.0f };
	m_pTestRobo->SetPosition( tmpVec3 );
	m_pTestRobo->SetScale( 0.25f );

	//�e�X�g���f���̏�����.
	m_pTestChara = new clsCharaStatic;
	m_pTestChara->AttachModel( 
		m_wpResource->GetStaticModels( 
			clsResource::enSTATIC_MODEL::enStaticModel_Enemy ) );
	m_pTestChara->Init();
	m_pTestChara->SetPosition( D3DXVECTOR3( -2.0f, 0.0f, 0.0f ) );
	m_pTestChara->SetRotation( D3DXVECTOR3( 0.0f, 0.0f, D3DX_PI*0.5 ) );

}

//���t���[���ʂ鏈��.
void clsMISSION::UpdateProduct( enSCENE &nextScene )
{
	//null�Ȃ�assert.
	ASSERT_IF_NULL( m_pTestRobo );
	m_pTestRobo->Update();



	//�G���f�B���O�ɍs���ꍇ�͈ȉ��̂悤�ɂ���.
	if( !"�N���A�����𖞂����Ƃ�����ʂ�" ){
		nextScene = enSCENE::ENDING;
	}

	//�f�o�b�O�p�V�[���ύX( �L�[�{�[�h��F9�`12���Ή����Ă��� )���ׂẴV�[����Update�̈�ԉ��ɒu��.
	DebugChangeScene( nextScene );
}

//�`��.
void clsMISSION::RenderProduct()
{
	//Render�֐��̈����������₷�����邽�߂̕ϐ�.
	D3DXVECTOR3 vCamPos = m_wpCamera->GetPos();

	m_pTestChara->Render( m_mView, m_mProj, m_vLight, vCamPos );
	m_pTestRobo->Render( m_mView, m_mProj, m_vLight, vCamPos );
}

