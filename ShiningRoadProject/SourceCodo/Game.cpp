#include "Game.h"

using namespace std;

const char* cBLACK_FILE_NAME = "Data\\Image\\BlackScreen.png";


//�N�����̏����V�[��.
#define START_UP_SCENE enSCENE::TITLE
//�V�[�����������̏���BGM�ԍ�.
const int iINIT_SCENE_BGM_NO = 0;

const unsigned char cSTART_UP_MUSIC_NO = 0;

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
		,m_spPtrGroup( nullptr )
		,m_spDxInput( nullptr )
		,m_spXInput( nullptr )
		,m_spResource( nullptr )
		,m_spEffect( nullptr )
		,m_spSound( nullptr )
		,m_upScene( nullptr )
		,m_upSceneFactory( nullptr )
		,m_spCamera( nullptr )
		,m_upCameraFactory( nullptr )
		,m_spRoboStatus( nullptr )
		,m_spBlackScreen( nullptr )
{

}

clsGAME::~clsGAME()
{
	SAFE_DELETE( m_upScene );
	SAFE_DELETE( m_spCamera );
//	SAFE_DELETE( m_upCameraFactory );
	if( m_upCameraFactory ){
		m_upCameraFactory.reset( nullptr );
	}
//	SAFE_DELETE( m_upSceneFactory );
	if( m_upSceneFactory ){
		m_upSceneFactory.reset( nullptr );
	}
	SAFE_DELETE( m_spPtrGroup );
	SAFE_DELETE( m_spBlackScreen );
	SAFE_DELETE( m_spRoboStatus );
	SAFE_DELETE( m_spEffect );
	SAFE_DELETE( m_spResource );
	SAFE_DELETE( m_spSound );
	m_upSoundFactory.reset();
	SAFE_DELETE( m_spXInput );
//	if( m_spXInput != nullptr ){
//		m_spXInput->EndProc();
//		XInputEnable( false );
//		delete m_spXInput;
//		m_spXInput = nullptr;
//	}
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
	assert( !m_spDxInput );
	m_spDxInput = new clsDxInput;
	m_spDxInput->initDI(m_hWnd);

	assert( !m_spXInput );
	m_spXInput = new clsXInput;

	assert( !m_upSoundFactory );
	m_upSoundFactory = make_unique<clsFACTORY_SOUND_MANAGER>();

	assert( !m_spSound );
	m_spSound = m_upSoundFactory->Create( START_UP_SCENE, m_hWnd );
	m_spSound->Create();
	m_spSound->PlayBGM( cSTART_UP_MUSIC_NO );//�N�����Đ�.

	assert( !m_spResource );
	m_spResource = new clsResource;
	m_spResource->Create( m_hWnd, m_wpDevice, m_wpContext );

	assert( !m_spEffect );
	m_spEffect = new clsEffects;
	m_spEffect->Create( m_wpDevice, m_wpContext );

	assert( !m_spRoboStatus );
	m_spRoboStatus = new clsROBO_STATUS;

	//�Ó].
	SPRITE_STATE ss;
	assert( !m_spBlackScreen );
	m_spBlackScreen = new clsBLACK_SCREEN;
	m_spBlackScreen->Create( m_wpDevice, m_wpContext,
		cBLACK_FILE_NAME, ss );

	//�����̃|�C���^�̏W����.
	assert( !m_spPtrGroup );
	m_spPtrGroup = new clsPOINTER_GROUP( 
		m_wpDevice, m_wpContext, 
		m_wpViewPort, m_wpDepthStencilState,
		m_spDxInput, m_spXInput,
		m_spResource, m_spEffect, m_spSound,
		m_spRoboStatus, m_spBlackScreen );


	//�t�@�N�g���̍쐬.
	assert( !m_upSceneFactory );
//	m_pSceneFactory = new clsSCENE_FACTORY( m_spPtrGroup );
	m_upSceneFactory = make_unique< clsSCENE_FACTORY >( m_spPtrGroup );
	assert( !m_upCameraFactory );
//	m_pCameraFactory = new clsFACTORY_CAMERA;
	m_upCameraFactory = make_unique< clsFACTORY_CAMERA >();

	//�ŏ��̃V�[���̓^�C�g�����w�肷��.
	SwitchScene( START_UP_SCENE, true );

}

//���t���[���g��.
void clsGAME::Update()
{ 
	//�R���g���[�����͏��X�V.
	assert( m_spDxInput );
	m_spDxInput->UpdataInputState();

	assert( m_spXInput );
	m_spXInput->UpdateStatus();

	//�V�[��������Ă���Ȃ�.
	assert( m_upScene );

	//���̃V�[���͉�?�t���O.
	enSCENE enNextScene = enSCENE::NOTHING;

	m_upScene->Update( enNextScene );

	//�t���O�ɕύX������΃V�[���ύX.
	if( enNextScene != enSCENE::NOTHING ){
		SwitchScene( enNextScene );
	}
}

//���t���[���g��.
void clsGAME::Render(		
	ID3D11RenderTargetView *pBackBuffer_TexRTV,
	ID3D11DepthStencilView *pBackBuffer_DSTexDSV )
{ 
	//��ʂ̃N���A.
	float ClearColor[4] = { 0.5f, 0.25f, 2.0f, 1.0f };//�N���A�F(RGBA��)(0.0f~1.0f).
	assert( m_wpContext );
	//�J���[�o�b�N�o�b�t�@.
	m_wpContext->ClearRenderTargetView(
		pBackBuffer_TexRTV, ClearColor );
	//�f�v�X�X�e���V���r���[�o�b�N�o�b�t�@.
	m_wpContext->ClearDepthStencilView(
		pBackBuffer_DSTexDSV,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 0 );

	//�V�[���̕`��.
	assert( m_upScene );
	m_upScene->Render(); 
}


//�V�[���؂�ւ�.
void clsGAME::SwitchScene( const enSCENE enNextScene, const bool bStartUp )
{
	//�������Ȃ��Ȃ炻�̂܂�( �V�[���ύX���s��Ȃ� ).
	if( enNextScene == enSCENE::NOTHING ){
		return;
	}

	//���̃V�[����������.
	SAFE_DELETE( m_upScene );
	SAFE_DELETE( m_spCamera );

	//�N�����͖���.
	if( !bStartUp ){
		SAFE_DELETE( m_spSound );
		//�w���ǂ���̃V�[�������.
		//�T�E���h.
		m_spSound = m_upSoundFactory->Create( enNextScene, m_hWnd );
		m_spSound->Create();
		m_spPtrGroup->UpdateSoundPtr( m_spSound );
	}

	//�J����.
	m_spCamera = m_upCameraFactory->Create( enNextScene );
	m_spPtrGroup->UpdateCameraPtr( m_spCamera );

	//���҂����˂̃V�[���{��.
	m_upScene = m_upSceneFactory->Create( enNextScene );

	//�N�����͖���.
	if( !bStartUp ){
		m_spSound->PlayBGM( iINIT_SCENE_BGM_NO );//BGM�Đ�.
	}

	m_upScene->Create();//�V�[��������.

	//���]�J�n.
	m_spBlackScreen->GetBright();
}




//���b�v�֐�.
D3DXVECTOR3 clsGAME::GetCameraPos() const
{
	return m_upScene->GetCameraPos();
}
D3DXVECTOR3 clsGAME::GetCameraLookPos() const
{
	return m_upScene->GetCameraLookPos();
}



