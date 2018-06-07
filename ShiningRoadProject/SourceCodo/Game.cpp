#include "Game.h"

//�N�����̏����V�[��.
#define START_UP_SCENE enSCENE::TITLE


clsGAME::clsGAME( 
	const HWND hWnd, 
	ID3D11Device* const pDevice, 
	ID3D11DeviceContext* const pContext,
	D3D10_VIEWPORT* const pViewPort,
	ID3D11DepthStencilState* const pDepthState  )
		:m_hWnd( hWnd )
		,m_wpDevice( pDevice )
		,m_wpContext( pContext )
		,m_wpViewPort( pViewPort )
		,m_wpDepthStencilState( pDepthState )
		,m_pPtrGroup( nullptr )
		,m_spDxInput( nullptr )
		,m_pResource( nullptr )
		,m_pEffect( nullptr )
		,m_pSound( nullptr )
		,m_pScene( nullptr )
		,m_pSceneFactory( nullptr )
		,m_spCamera( nullptr )
		,m_pCameraFactory( nullptr )
		,m_spRoboStatus( nullptr )
{

}

clsGAME::~clsGAME()
{
	SAFE_DELETE( m_pScene );
	SAFE_DELETE( m_spCamera );
	SAFE_DELETE( m_pCameraFactory );
	SAFE_DELETE( m_pSceneFactory );
	SAFE_DELETE( m_pPtrGroup );
	SAFE_DELETE( m_spRoboStatus );
	SAFE_DELETE( m_pSound );
	SAFE_DELETE( m_pEffect );
	SAFE_DELETE( m_pResource );
	SAFE_DELETE( m_spDxInput );

	m_wpDepthStencilState = nullptr;
	m_wpViewPort = nullptr;
	m_wpContext = nullptr;
	m_wpDevice = nullptr;
	m_hWnd = nullptr;
}

//new����Ɏg��.
void clsGAME::Create()
{ 
	ASSERT_IF_NOT_NULL( m_spDxInput );
	m_spDxInput = new clsDxInput;
	m_spDxInput->initDI(m_hWnd);

	m_pResource = new clsResource;
	m_pResource->Create( m_hWnd, m_wpDevice, m_wpContext );

	m_pEffect = new clsEffects;
	m_pEffect->Create( m_wpDevice, m_wpContext );

	m_pSound = new clsSOUND_MANAGER( m_hWnd );

	m_spRoboStatus = new clsROBO_STATUS;

	//�����̃|�C���^�̏W����.
	m_pPtrGroup = new clsPOINTER_GROUP( 
		m_wpDevice, m_wpContext, 
		m_wpViewPort, m_wpDepthStencilState,
		m_spDxInput, m_pResource, 
		m_pEffect, m_pSound,
		m_spRoboStatus );


	//�t�@�N�g���̍쐬.
	ASSERT_IF_NOT_NULL( m_pSceneFactory );
	m_pSceneFactory = new clsSCENE_FACTORY( m_pPtrGroup );
	ASSERT_IF_NOT_NULL( m_pCameraFactory );
	m_pCameraFactory = new clsFACTORY_CAMERA;

	//�ŏ��̃V�[���̓^�C�g�����w�肷��.
	SwitchScene( START_UP_SCENE );

//	//�V�[��.
//	ASSERT_IF_NOT_NULL( m_pSceneManager );
//	m_pSceneManager = new clsSCENE_MANAGER( m_pPtrGroup );
//	m_pSceneManager->Create(); 

	//�N�����Đ�.
	m_pSound->PlayBGM( enBGM_TITLE );


}

//���t���[���g��.
void clsGAME::Update()
{ 
	//�R���g���[�����͏��X�V.
	ASSERT_IF_NULL( m_spDxInput );
	m_spDxInput->UpdataInputState();

	//�V�[��������Ă���Ȃ�.
	ASSERT_IF_NULL( m_pScene );

	//���̃V�[���͉�?�t���O.
	enSCENE enNextScene = enSCENE::NOTHING;

	m_pScene->Update( enNextScene );

	//�t���O�ɕύX������΃V�[���ύX.
	if( enNextScene != enSCENE::NOTHING ){
		SwitchScene( enNextScene );
	}
}

//���t���[���g��.
void clsGAME::Render()
{ 

	ASSERT_IF_NULL( m_pScene );
	m_pScene->Render(); 
}


//�V�[���؂�ւ�.
void clsGAME::SwitchScene( const enSCENE enNextScene )
{
	//�������Ȃ��Ȃ炻�̂܂�( �V�[���ύX���s��Ȃ� ).
	if( enNextScene == enSCENE::NOTHING ){
		return;
	}

	//���̃V�[����������.
	SAFE_DELETE( m_pScene );
	SAFE_DELETE( m_spCamera );

	//�w���ǂ���̃V�[�������.
	//�܂��̓J����.
	m_spCamera = m_pCameraFactory->Create( enNextScene );
	m_pPtrGroup->UpdateCameraPtr( m_spCamera );

	//���҂����˂̃V�[���{��.
	m_pScene = m_pSceneFactory->Create( enNextScene );
	m_pScene->Create();
}





//���b�v�֐�.
D3DXVECTOR3 clsGAME::GetCameraPos() const
{
	return m_pScene->GetCameraPos();
}
D3DXVECTOR3 clsGAME::GetCameraLookPos() const
{
	return m_pScene->GetCameraLookPos();
}



