#include "SceneTitle.h"


const float fROBO_SCALE = 0.5f;

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

	//���f������쐬.
	m_pRoboModel = new clsASSEMBLE_MODEL;
	m_pRoboModel->Create( m_wpResource, m_wpRoboStatus );
	m_pRoboModel->SetScale( fROBO_SCALE );

	//�J����.
	m_wpCamera->SetPos( { 0.0f, 0.0f, -100.0f } );
	m_wpCamera->SetLookPos( { 0.0f, 0.0f, 0.0f } );
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
	if( GetAsyncKeyState( VK_RETURN ) & 0x1 ){
		enNextScene = enSCENE::ASSEMBLE;
		//			Excel�̍s�ԍ�.
		m_wpSound->StopBGM( 0 );
		m_wpSound->PlaySE( 0 );
	}
}

void clsSCENE_TITLE::RenderProduct( const D3DXVECTOR3 &vCamPos )
{
	m_pRoboModel->Render( m_mView, m_mProj, m_vLight, vCamPos );

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
