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
void clsSCENE_MISSION::UpdateProduct( enSCENE &nextScene )
{
	//null�Ȃ�assert.
	ASSERT_IF_NULL( m_pTestRobo );
	m_pTestRobo->Update();



	//�G���f�B���O�ɍs���ꍇ�͈ȉ��̂悤�ɂ���.
	if( !"�N���A�����𖞂����Ƃ�����ʂ�" ){
		nextScene = enSCENE::ENDING;
	}
}

//�`��.
void clsSCENE_MISSION::RenderProduct( const D3DXVECTOR3 &vCamPos )
{
	m_pTestChara->Render( m_mView, m_mProj, m_vLight, vCamPos );
	m_pTestRobo->Render( m_mView, m_mProj, m_vLight, vCamPos );
}

