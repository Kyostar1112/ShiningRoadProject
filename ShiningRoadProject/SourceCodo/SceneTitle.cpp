#include "SceneTitle.h"


//================================//
//========== �^�C�g���N���X ==========//
//================================//
clsTITLE::clsTITLE( clsPOINTER_GROUP* const ptrGroup ) : clsSCENE_BASE( ptrGroup ),
	m_pTestChara( nullptr )
{
}

clsTITLE::~clsTITLE()
{
	//new�����|�C���^�̔j��.
	SAFE_DELETE( m_pTestChara );
}


void clsTITLE::Create()
{
	//�e�X�g���f���̏�����.
	m_pTestChara = new clsCharaStatic;
	m_pTestChara->AttachModel( 
		m_wpResource->GetStaticModels( 
			clsResource::enSTATIC_MODEL::enStaticModel_Ground ) );
	m_pTestChara->Init();
	m_pTestChara->SetPosition( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );

}

void clsTITLE::Update( enSCENE &nextScene )
{
	//Update�֐����@�\���Ă��邩�̃e�X�g�p��].
	m_pTestChara->AddRotation( D3DXVECTOR3( 0.0f, 0.00f, 0.025f ) );


	DebugChangeScene( nextScene );
}

void clsTITLE::Render(
	const D3DXMATRIX &mView, 
	const D3DXMATRIX &mProj,
	const D3DXVECTOR3 &vLight ) const
{
	//Render�֐��̈����������₷�����邽�߂̕ϐ�.
	D3DXVECTOR3 vCamPos = m_wpCamera->GetPos();

	m_pTestChara->Render( mView, mProj, vLight, vCamPos );

}
