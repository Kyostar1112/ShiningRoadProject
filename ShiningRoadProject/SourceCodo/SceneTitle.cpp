#include "SceneTitle.h"
#include "WindowBox.h"

using namespace std;

const float fROBO_SCALE = 0.5f;
const float fBACK_SCALE = 1.0f;

//���S.
const char* sFILE_PATH_LOGO = "Data\\Image\\TitleUi\\TitleLogo.png";
const WHSIZE_FLOAT INIT_LOGO_SIZE = { 512.0f, 128.0f };
const D3DXVECTOR3 vINIT_LOGO_POS = { 128.0f, 75.0f, 0.0f };


//�t���b�V��.
const char* sFLASH_PATH = "Data\\Image\\TitleUi\\Flash.png";
const float fFLASH_DOWN = -0.05f;


//���{��UI.
const char* sFONT_TEXT_PATH_TITLE = "Data\\Font\\Text\\TextTitle.csv";


//================================//
//========== �^�C�g���N���X ==========//
//================================//
clsSCENE_TITLE::clsSCENE_TITLE( clsPOINTER_GROUP* const ptrGroup ) : clsSCENE_BASE( ptrGroup )
	,m_pRoboModel( nullptr )
{
}

clsSCENE_TITLE::~clsSCENE_TITLE()
{
	SAFE_DELETE( m_pRoboModel );
}


void clsSCENE_TITLE::CreateProduct()
{
	m_wpFont->Create( sFONT_TEXT_PATH_TITLE );

	//���f������쐬.
	assert( !m_pRoboModel );
	m_pRoboModel = new clsASSEMBLE_MODEL;
	m_pRoboModel->Create( m_wpResource, m_wpRoboStatus );
	m_pRoboModel->SetScale( fROBO_SCALE );

	//���S.
	assert( !m_upLogo );
	m_upLogo = make_unique< clsSprite2D >();
	SPRITE_STATE ss;
	ss.Disp = INIT_LOGO_SIZE;
	m_upLogo->Create( m_wpDevice, m_wpContext, sFILE_PATH_LOGO, ss );
	m_upLogo->SetPos( vINIT_LOGO_POS );
	m_upLogo->SetAlpha( 0.0f );

	//�w�i.
	assert( !m_upBack );
	m_upBack  = make_unique< clsCharaStatic >();
	m_upBack->AttachModel( 
		m_wpResource->GetStaticModels( clsResource::enStaticModel_StageBase ) );
	m_upBack->SetPosition( m_pRoboModel->GetPos() );
	m_upBack->SetScale( fBACK_SCALE );

	//���܂����t���b�V��.
	assert( !m_upFlash );
	ss.Disp = { WND_W, WND_H };
	m_upFlash = make_unique< clsSprite2D >();
	m_upFlash->Create( m_wpDevice, m_wpContext, sFLASH_PATH, ss );
	m_upFlash->SetAlpha( 0.0f );


	//��.
	assert( !m_upBox );
	m_upBox = make_unique< clsWINDOW_BOX >( m_wpDevice, m_wpContext );
	m_upBox->SetSize( 0.0f );
	m_upBox->SetAlpha( 0.5f );

//	//�J����.
//	assert( m_wpCamera );
//	m_wpCamera->SetPos( { 0.0f, 100.0f, -80.0f } );
//	m_wpCamera->SetLookPos( { 0.0f, 45.0f, 0.0f } );

}

void clsSCENE_TITLE::UpdateProduct( enSCENE &enNextScene )
{
	//�G�t�F�N�g�̎g����.
	if( GetAsyncKeyState( VK_SPACE ) & 0x1 ){
		//						Excel�̍s�ԍ�	���W.
		m_ehHibana = m_wpEffects->Play( 2, { 0.0f, 20.0f, 0.0f } );

		//�傫������.
		m_wpEffects->SetScale( m_ehHibana, 50.0f );
		//���W.
		m_wpEffects->SetPosition( m_ehHibana, { 0.0f, 10.0f, 0.0f } );
		//��].
		static float fff = 0.0f;
		m_wpEffects->SetRotation( m_ehHibana, { 0.0f, 0.0f, fff } );
		fff += 0.1f;
	}

	//�����ƃV�[���ړ�.
	if( isPressEnter() ){
		enNextScene = enSCENE::ASSEMBLE;
		//			Excel�̍s�ԍ�.
		assert( m_wpSound );
		m_wpSound->StopBGM( 0 );
		m_wpSound->PlaySE( 0 );
	}

//	if( m_upKey->isEnter( 'Z' ) ){
//		m_upBox->SetSizeTarget( { 200.0f, 200.0f, 0.0f } );
//	}
//	if( m_upKey->isEnter( 'X' ) ){
//		m_upBox->SetSizeTarget( { 100.0f, 40.0f, 0.0f } );
//	}
//	if( m_upKey->isEnter( 'C' ) ){
//		m_upBox->SetSizeTarget( { 40.0f, 200.0f, 0.0f } );
//	}
//	if( m_upKey->isEnter( 'V' ) ){
//		m_upBox->SetSizeTarget( { 0.0f, 0.0f, 0.0f } );
//	}
//
//	if( m_upKey->isEnter( 'A' ) ){
//		m_upBox->AddChangeData( 
//			10.0f, 10.0f, clsLINE_BOX::encBEFOR_CHANGE::WIDTH );
//	}
//	if( m_upKey->isEnter( 'S' ) ){
//		m_upBox->AddChangeData( 
//			10.0f, 10.0f, clsLINE_BOX::encBEFOR_CHANGE::HEIGHT );
//	}
//	if( m_upKey->isEnter( 'D' ) ){
//		m_upBox->AddChangeData( 
//			10.0f, 10.0f, clsLINE_BOX::encBEFOR_CHANGE::BOTH );
//	}
//	if( m_upKey->isEnter( 'F' ) ){
//		m_upBox->AddChangeData( 
//			100.0f, 100.0f, clsLINE_BOX::encBEFOR_CHANGE::BOTH );
//	}

	m_upFlash->AddAlpha( fFLASH_DOWN );



	m_wpCamera->Update();
	m_upBox->Update();


	clsCAMERA_TITLE* pCam = (clsCAMERA_TITLE*)m_wpCamera;//�S�������ł��߂�Ȃ���.
	if( pCam->isFlash() ){
		m_upFlash->SetAlpha( 1.0f );
		m_upLogo->SetAlpha( 1.0f );
	}

}

void clsSCENE_TITLE::RenderProduct( const D3DXVECTOR3 &vCamPos )
{
	assert( m_pRoboModel );
	m_pRoboModel->Render( m_mView, m_mProj, m_vLight, vCamPos );

	assert( m_upBack );
	m_upBack->Render( m_mView, m_mProj, m_vLight, vCamPos );


	SetDepth( false );

	assert( m_upLogo );
	m_upLogo->Render();

	assert( m_upBox );
	m_upBox->Render();



	SetDepth( true );
}
void clsSCENE_TITLE::RenderUi()
{
	m_wpFont->Render( 0, 100 );

	assert( m_upFlash );
	m_upFlash->Render();
}


//============================ �f�o�b�O�e�L�X�g ===========================//
#if _DEBUG
void clsSCENE_TITLE::RenderDebugText()
{
	//NULL�`�F�b�N.
	assert( m_upText );

	char strDbgTxt[256];
	int iTxtY = 0;
	const int iOFFSET = 10;//��s���ɂǂꂾ�����ɂ��炷��.

	sprintf_s( strDbgTxt, 
		"CameraPos : x[%f], y[%f], z[%f]",
		GetCameraPos().x, GetCameraPos().y, GetCameraPos().z );
	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

	sprintf_s( strDbgTxt, 
		"CamLokPos : x[%f], y[%f], z[%f]",
		GetCameraLookPos().x, GetCameraLookPos().y, GetCameraLookPos().z );
	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

	sprintf_s( strDbgTxt, 
		"CamRot : x[%f], y[%f], z[%f]",
		m_wpCamera->GetRot().x, m_wpCamera->GetRot().y, m_wpCamera->GetRot().z );
	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

	//�ړ���.
	clsCAMERA_TITLE* pct;
	pct = (clsCAMERA_TITLE*)m_wpCamera;
	sprintf_s( strDbgTxt, 
		"CamSpd : x[%f], y[%f], z[%f]",
		pct->GetSpd().x, pct->GetSpd().y, pct->GetSpd().z );
	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

	sprintf_s( strDbgTxt, 
		"CamAcc : x[%f], y[%f], z[%f]",
		pct->GetAcc().x, pct->GetAcc().y, pct->GetAcc().z );
	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

	pct = nullptr;

	//dbgtxty += 10;
	//if( m_pBgm[0]->IsStopped() ){
	//	sprintf_s( strDbgTxt, "Stopped" );
	//	m_pText->Render( strDbgTxt, 0, dbgtxty );
	//}
	//if( m_pBgm[0]->IsPlaying() ){
	//	sprintf_s( strDbgTxt, "Playingn" );
	//	m_pText->Render( strDbgTxt, 0, dbgtxty );
	//}
}
#endif //#if _DEBUG
