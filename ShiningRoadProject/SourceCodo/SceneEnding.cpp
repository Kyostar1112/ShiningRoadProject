#include "SceneEnding.h"

using namespace std;

//================================//
//========== �G���f�B���O�N���X ==========//
//================================//
clsSCENE_ENDING::clsSCENE_ENDING( clsPOINTER_GROUP* const ptrGroup ) : clsSCENE_BASE( ptrGroup )
{
}

clsSCENE_ENDING::~clsSCENE_ENDING()
{
}

void clsSCENE_ENDING::CreateProduct()
{
	m_upStage = make_unique< clsStage >( m_wpPtrGroup->GetResource() );

	m_wpCamera->SetPos( { 0.0f, 500.0f, -1.0f } );
	m_wpCamera->SetLookPos( { 0.0f, 0.0f, 0.0f } );
}


void clsSCENE_ENDING::UpdateProduct( enSCENE &enNextScene )
{
	float fff = 50.0f;
	if( isPressRight() ){
		m_wpCamera->AddPos( { fff, 0.0f, 0.0f } );
	}
	if( isPressLeft() ){
		m_wpCamera->AddPos( { -fff, 0.0f, 0.0f } );
	}
	if( isPressUp() ){
		m_wpCamera->AddPos( { 0.0f, 0.0f, fff } );
	}
	if( isPressDown() ){
		m_wpCamera->AddPos( { 0.0f, 0.0f, -fff } );
	}
	if( isPressEnter() ){
		m_wpCamera->AddPos( { 0.0f, fff, -0.0f } );
	}
	if( isPressExit() ){
		m_wpCamera->AddPos( { 0.0f, -fff, -0.0f } );
	}



	if( isPressEnter() ){
		enNextScene = enSCENE::TITLE;
	}
}

void clsSCENE_ENDING::RenderProduct( const D3DXVECTOR3 &vCamPos )
{
	m_upStage->Render( m_mView, m_mProj, m_vLight, vCamPos );
}


//============================ �f�o�b�O�e�L�X�g ===========================//
#if _DEBUG
void clsSCENE_ENDING::RenderDebugText()
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
