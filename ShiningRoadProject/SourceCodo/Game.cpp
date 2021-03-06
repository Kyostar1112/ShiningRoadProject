#include "Game.h"

using namespace std;

namespace{

	const char* cBLACK_FILE_NAME = "Data\\Image\\BlackScreen.png";


	//起動時の初期シーン.
	#define START_UP_SCENE enSCENE::TITLE
	//タイトルの前にアセンブルシーンを読み込んで、ステータスを手に入れる.
	#define GET_STATUS_DATA_INIT_SCENE enSCENE::ASSEMBLE

	const unsigned char cSTART_UP_MUSIC_NO = 0;

	//画面の初期化色.
	const float g_fClearColor[4] = { 0.5f, 0.25f, 2.0f, 1.0f };//クリア色(RGBA順)(0.0f~1.0f).

}


clsGAME::clsGAME( 
	const HWND hWnd, 
	ID3D11Device* const pDevice, 
	ID3D11DeviceContext* const pContext,
	D3D10_VIEWPORT* const pViewPort10,
	D3D11_VIEWPORT* const pViewPort11 )
		:m_hWnd( hWnd )
		,m_wpDevice( pDevice )
		,m_wpContext( pContext )
		,m_wpViewPort10( pViewPort10 )
		,m_wpViewPort11( pViewPort11 )
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
		,m_spFont( nullptr )
{
	assert( !m_spResource );
	m_spResource = new clsResource;
	m_spResource->Create( m_hWnd, m_wpDevice, m_wpContext );

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
	SAFE_DELETE( m_spFont );
	SAFE_DELETE( m_spBlackScreen );
	SAFE_DELETE( m_spRoboStatus );
	SAFE_DELETE( m_spEffect );
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
	SAFE_DELETE( m_spResource );

	m_wpViewPort11 = nullptr;
	m_wpViewPort10 = nullptr;
	m_wpContext = nullptr;
	m_wpDevice = nullptr;
	m_hWnd = nullptr;
}

//new直後に使う.
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
//	m_spSound = m_upSoundFactory->Create( START_UP_SCENE, m_hWnd );
//	m_spSound->Create();

	assert( !m_spEffect );
	m_spEffect = new clsEffects;
	m_spEffect->Create( m_wpDevice, m_wpContext );

	assert( !m_spRoboStatus );
	m_spRoboStatus = new clsROBO_STATUS_PLAYER;

	//暗転.
	SPRITE_STATE ss;
	assert( !m_spBlackScreen );
	m_spBlackScreen = new clsBLACK_SCREEN;
	m_spBlackScreen->Create( m_wpDevice, m_wpContext,
		cBLACK_FILE_NAME, ss );

	assert( !m_spFont );
	m_spFont = new clsFont ( 
		m_wpDevice, m_wpContext );

	//引数のポインタの集合体.
	assert( !m_spPtrGroup );
	m_spPtrGroup = new clsPOINTER_GROUP( 
		m_wpDevice, m_wpContext, 
		m_wpViewPort10, m_wpViewPort11,
		m_spDxInput, m_spXInput,
		m_spResource, m_spEffect, m_spSound,
		m_spRoboStatus, m_spBlackScreen,
		m_spFont );


	//ファクトリの作成.
	assert( !m_upSceneFactory );
	m_upSceneFactory = make_unique< clsSCENE_FACTORY >( m_spPtrGroup );
	assert( !m_upCameraFactory );
	m_upCameraFactory = make_unique< clsFACTORY_CAMERA >();

	//タイトルの前にアセンブルシーンを読み込んで、ステータスを手に入れる.
	SwitchScene( GET_STATUS_DATA_INIT_SCENE, true );
	//最初のシーンはタイトルを指定する.
	SwitchScene( START_UP_SCENE );

}

//毎フレーム使う.
bool clsGAME::Update()
{ 
	if( !m_upScene ){
		//閉じる.
		return false;
	}

	//コントローラ入力情報更新.
	assert( m_spDxInput );
	m_spDxInput->UpdataInputState();

	assert( m_spXInput );
	m_spXInput->UpdateStatus();

	//次のシーンは何?のフラグ.
	enSCENE enNextScene = enSCENE::NOTHING;

	//シーンが作られているなら.
	m_upScene->Update( enNextScene );

	//フラグに変更があればシーン変更.
	if( enNextScene != enSCENE::NOTHING ){
		SwitchScene( enNextScene );
	}

	return true;
}

//毎フレーム使う.
void clsGAME::Render(		
	ID3D11RenderTargetView* const pBackBuffer_TexRTV,
	ID3D11DepthStencilView* const pBackBuffer_DSTexDSV )
{ 
	assert( m_wpContext );
	//画面のクリア.
	m_wpContext->ClearRenderTargetView(
		pBackBuffer_TexRTV, g_fClearColor );
	//デプスステンシルビューバックバッファ.
	m_wpContext->ClearDepthStencilView(
		pBackBuffer_DSTexDSV,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 0 );

	//シーンの描画.
	if( m_upScene ){
		m_upScene->Render( pBackBuffer_TexRTV, pBackBuffer_DSTexDSV ); 
	}

}


//シーン切り替え.
void clsGAME::SwitchScene( const enSCENE enNextScene, const bool bStartUp )
{
	//何もしないならそのまま( シーン変更を行わない ).
	if( enNextScene == enSCENE::NOTHING ){
		return;
	}

	//今のシーンを消して.
	SAFE_DELETE( m_upScene );
	SAFE_DELETE( m_spCamera );
	SAFE_DELETE( m_spSound );

	//サウンド.

	if( !bStartUp ){
		m_spSound = m_upSoundFactory->Create( enNextScene, m_hWnd );
		if( m_spSound ){
			m_spSound->Create();
		}
	}
	m_spPtrGroup->UpdateSoundPtr( m_spSound );

	//カメラ.
	m_spCamera = m_upCameraFactory->Create( enNextScene );
	m_spPtrGroup->UpdateCameraPtr( m_spCamera );

	//お待ちかねのシーン本体.
	m_upScene = m_upSceneFactory->Create( enNextScene );

	if( m_upScene ){
		m_upScene->Create();//シーン初期化.
	}


	//明転開始.
	m_spBlackScreen->GetBright();
}




//ラップ関数.
D3DXVECTOR3 clsGAME::GetCameraPos() const
{
	return m_upScene->GetCameraPos();
}
D3DXVECTOR3 clsGAME::GetCameraLookPos() const
{
	return m_upScene->GetCameraLookPos();
}



