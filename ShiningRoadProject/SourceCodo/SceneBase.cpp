#include "SceneBase.h"
#include <Windows.h>

using namespace std;

namespace{

	//���C�g����.
	const D3DXVECTOR3 vLIGHT_DIR = { 0.005f, 0.01f, -2.0f };
	//�J�����̂��.
	const float fZOOM = static_cast<float>( D3DX_PI / 4.0 );
	//�`����E����.
	const float fRENDER_LIMIT = 640.0f;//150.0f.


	#define XINPUT_ENTER  ( XINPUT_START | XINPUT_B )
	#define XINPUT_EXIT  ( XINPUT_A )

	//�{�^���̃z�[���h�t���[��.
	const int iHOLD_FREAM = 30;
	const int iHOLD_FREAM_FIRST = 6;
	const int iHOLD_FREAM_FIRST_STEP = 1;

#if _DEBUG
	const D3DXVECTOR4 vDEBUG_TEXT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	const float fDEBUG_TEXT_SIZE = 50.0f;
#endif//#if _DEBUG
}


//================================//
//========== ���N���X ==========//
//================================//
clsSCENE_BASE::clsSCENE_BASE( clsPOINTER_GROUP* const ptrGroup )
	:m_wpPtrGroup(		ptrGroup )
	,m_wpDevice(		m_wpPtrGroup->GetDevice() )
	,m_wpContext(		m_wpPtrGroup->GetContext() )
	,m_wpViewPort10(	m_wpPtrGroup->GetViewPort10() )
	,m_wpViewPort11(	m_wpPtrGroup->GetViewPort11() )
	,m_wpDxInput(		m_wpPtrGroup->GetDxInput() )
	,m_wpXInput(		m_wpPtrGroup->GetXInput() )
	,m_wpResource(		m_wpPtrGroup->GetResource() )
	,m_wpEffects(		m_wpPtrGroup->GetEffects() )
	,m_wpSound(			m_wpPtrGroup->GetSound() )
	,m_wpCamera(		m_wpPtrGroup->GetCamera() )
	,m_wpRoboStatus(	m_wpPtrGroup->GetRoboStatus() )
	,m_wpBlackScreen(	m_wpPtrGroup->GetBlackScreen() )
	,m_wpFont(			m_wpPtrGroup->GetFont() )
	,m_enNextScene(		enSCENE::NOTHING )
	,m_wpViewPortUsing(	m_wpViewPort11 )
	,m_pDepthStencilStateOn( nullptr )
	,m_pDepthStencilStateOff(nullptr )
#ifdef RENDER_SCREEN_TEXTURE_	
	,m_pScreenTex( nullptr )
	,m_pScreenRTV( nullptr )
	,m_pScreenSRV( nullptr )
	,m_pScreenSmp( nullptr )
	,m_pScreenVS( nullptr )
	,m_pScreenPS( nullptr )
#endif//#ifdef RENDER_SCREEN_TEXTURE_
{
}

clsSCENE_BASE::~clsSCENE_BASE()
{
#if _DEBUG
//	SAFE_DELETE( m_upText );
	if( m_upText ){
		m_upText.reset();
	}
#endif//#if _DEBUG

#ifdef RENDER_SCREEN_TEXTURE_	
	SAFE_RELEASE( m_pScreenPS );
	SAFE_RELEASE( m_pScreenVS );
	SAFE_RELEASE( m_pScreenSmp );
	SAFE_RELEASE( m_pScreenSRV );
	SAFE_RELEASE( m_pScreenRTV );
	SAFE_RELEASE( m_pScreenTex );
#endif//#ifdef RENDER_SCREEN_TEXTURE_

	m_wpFont->Release();

//	//�����~�߂�.
//	m_wpSound->StopAllSound();
	//���̃V�[���ɗ]�v�ȃG�t�F�N�g���������܂Ȃ�.
	m_wpEffects->StopAll();

	SAFE_RELEASE( m_pDepthStencilStateOff );
	SAFE_RELEASE( m_pDepthStencilStateOn );


	m_enNextScene = enSCENE::NOTHING;

	m_wpFont = nullptr;
	m_wpBlackScreen = nullptr;
	m_wpRoboStatus = nullptr;
	m_wpCamera = nullptr;
	m_wpSound = nullptr;
	m_wpEffects = nullptr;
	m_wpResource = nullptr;
	m_wpDxInput = nullptr;
	m_wpPtrGroup = nullptr;
	m_wpViewPortUsing = nullptr;
	m_wpViewPort11 = nullptr;
	m_wpViewPort10 = nullptr;
	m_wpContext = nullptr;
	m_wpDevice = nullptr;
}


//�V�[���쐬����ɁuSceneManager.cpp�v�́uSwitchScene�v�֐����Ŏg�p����Ă���.
void clsSCENE_BASE::Create()
{
	if( FAILED( CreateDepthStencilState() ) ){
		assert( !"�f�v�X�X�e���V���쐬���s" );
		return;
	}

	D3DXMatrixIdentity( &m_mView );
	D3DXMatrixIdentity( &m_mProj );	
	m_vLight = vLIGHT_DIR;

	m_wpBlackScreen->SetChangeSpd( fBLACK_SCREEN_DEFAULT_SPD );
	m_wpBlackScreen->GetBright();

#ifdef RENDER_SCREEN_TEXTURE_	
	//�`���e�N�X�`���쐬.
	if( FAILED( CreateScreenTexture() ) ){
		ERR_MSG( "�`���e�N�X�`���쐬���s", "" );
	}
#endif//#ifdef RENDER_SCREEN_TEXTURE_


#if _DEBUG
	//�f�o�b�O�e�L�X�g�̏�����.
	m_upText = make_unique< clsDebugText >();
	if( FAILED( m_upText->Init(
		m_wpContext,
		WND_W, WND_H, fDEBUG_TEXT_SIZE,
		vDEBUG_TEXT_COLOR ) ) )
	{
		assert( !"�f�o�b�O�e�L�X�g�쐬���s" );
	}
#endif//#if _DEBUG

	//�e�V�[����Create.
	CreateProduct();

}

//���[�v���̏���( �������֐����ŕύX����ƍ��̃V�[�����j������A.
//				  �w�肵���V�[������������� ).
void clsSCENE_BASE::Update( enSCENE &enNextScene )
{
//	m_upKey->Update();

	//�T�E���h���[�v.
	m_wpSound->UpdateLoop();

	//enNextScene�͊e�V�[���ɒ��ڂ͓��������Ȃ�.
	enSCENE tmpScene = enNextScene;

	//�Ó]�X�V.
	m_wpBlackScreen->Update();

#if _DEBUG
	//BGM�̃`�F�b�N.
	DebugBgm();
#endif//#if _DEBUG

	//�e�V�[����Update.
	UpdateProduct( tmpScene );

//	//UpdateProduct���ł̎󂯎��( �X�V )�Y��h�~.
	m_wpBlackScreen->isBrightEnd();

	//�V�[���ύX�����߂��ꂽ��.
	if( tmpScene != enSCENE::NOTHING ){
		//�Ó]�J�n.
		m_wpBlackScreen->GetDark();
		m_enNextScene = tmpScene;//���ɕύX����V�[�����o��������.
	}

	//�Ó]���������炲�����̃V�[���ɐ؂�ւ���.
	if( m_wpBlackScreen->isDarkEnd() ){
		enNextScene = m_enNextScene;//�o���Ă����V�[����������.
		m_enNextScene = enSCENE::NOTHING;//������.//�o���Ă����Y���.
	}

	//�f�o�b�O�p�V�[���؂�ւ�.
	DebugChangeScene( enNextScene );
}

//�V�[�����̃I�u�W�F�N�g�̕`��֐��̂܂Ƃ�.
void clsSCENE_BASE::Render( 
	ID3D11RenderTargetView* const pBackBuffer_TexRTV,
	ID3D11DepthStencilView* const pDepthStencilView )
{
	//�J�����֐�.
	Camera();
	//�v���W�F�N�V�����֐�.
	Proj();	


#ifdef RENDER_SCREEN_TEXTURE_	
	//Rendertarget���e�N�X�`���ɂ���.
	SetRenderTargetTexture( pDepthStencilView );
#endif//#ifdef RENDER_SCREEN_TEXTURE_


	//�e�V�[���̕`��.
	RenderProduct( m_wpCamera->GetPos() );
	
	//�G�t�F�N�g�`��.
	m_wpEffects->Render( m_mView, m_mProj, m_wpCamera->GetPos() );

	//���ʂ�̃r���[�|�[�g.
	SetViewPort( m_wpViewPort11, m_wpCamera->GetPos(), m_wpCamera->GetLookPos(), WND_W, WND_H );

	//�e�V�[����UI�̕`��.
	SetDepth( false );
	RenderUi();

	//���ʂ�̃r���[�|�[�g.
	if( m_wpViewPortUsing != m_wpViewPort11 ){
		m_wpViewPortUsing = m_wpViewPort11;
		m_wpContext->RSSetViewports( 1, m_wpViewPort11 );
	}

	//�Ó]�`��.
	m_wpBlackScreen->Render();

#if _DEBUG
	RenderDebugText();
#endif//#if _DEBUG

	SetDepth( true );	//Z�e�X�g:ON.


#ifdef RENDER_SCREEN_TEXTURE_	
	//�e�N�X�`���̓��e����ʂɕ`��.
	RenderWindowFromTexture( pBackBuffer_TexRTV, pDepthStencilView );
#endif//#ifdef RENDER_SCREEN_TEXTURE_


}

//���j���[����Ɏg���Ă�.
bool clsSCENE_BASE::isPressRight()
{
	if( m_wpXInput->isPressEnter( XINPUT_RIGHT ) ){
		return true;
	}
	else if( m_wpXInput->isSlopeEnter( XINPUT_RIGHT ) ){
		return true;
	}
	else if( m_wpDxInput->IsLSRightEnter() ){
		return true;
	}
	else if( GetAsyncKeyState( VK_RIGHT ) & 0x1 ){
		return true;
	}
	return false;
}

bool clsSCENE_BASE::isPressLeft()
{
	if( m_wpXInput->isPressEnter( XINPUT_LEFT ) ){
		return true;
	}
	else if( m_wpXInput->isSlopeEnter( XINPUT_LEFT ) ){
		return true;
	}
	else if( m_wpDxInput->IsLSLeftEnter() ){
		return true;
	}
	else if( GetAsyncKeyState( VK_LEFT ) & 0x1 ){
		return true;
	}
	return false;
}

bool clsSCENE_BASE::isPressUp()
{
	if( m_wpXInput->isPressEnter( XINPUT_UP ) ){
		return true;
	}
	else if( m_wpXInput->isSlopeEnter( XINPUT_UP ) ){
		return true;
	}
	else if( m_wpDxInput->IsLSUpEnter() ){
		return true;
	}
	else if( GetAsyncKeyState( VK_UP ) & 0x1 ){
		return true;
	}
	return false;
}

bool clsSCENE_BASE::isPressDown()
{
	if( m_wpXInput->isPressEnter( XINPUT_DOWN ) ){
		return true;
	}
	else if( m_wpXInput->isSlopeEnter( XINPUT_DOWN ) ){
		return true;
	}
	else if( m_wpDxInput->IsLSDownEnter() ){
		return true;
	}
	else if( GetAsyncKeyState( VK_DOWN ) & 0x1 ){
		return true;
	}
	return false;
}

bool clsSCENE_BASE::isPressEnter()
{
	if( m_wpXInput->isPressEnter( XINPUT_ENTER ) ){
		return true;
	}
//	else if( m_wpDxInput->IsPressKey( enPKey_00 ) ){
//		return true;
//	}
	else if( GetAsyncKeyState( VK_RETURN ) & 0x1 ){
		return true;
	}
	return false;
}

bool clsSCENE_BASE::isPressExit()
{
	if( m_wpXInput->isPressEnter( XINPUT_EXIT ) ){
		return true;
	}
	else if( GetAsyncKeyState( VK_BACK ) & 0x1 ){
		return true;
	}
	return false;
}

//���j���[����Ɏg���Ă�.
bool clsSCENE_BASE::isPressHoldRight( bool isWithStick )
{
	bool isPush = false;
	if( m_wpXInput->isPressStay( XINPUT_RIGHT ) ){
		isPush = true;
	}
	else if( m_wpXInput->isSlopeStay( XINPUT_RIGHT ) && isWithStick ){
		isPush = true;
	}
	else if( m_wpDxInput->IsLSRightStay() && isWithStick ){
		isPush = true;
	}
	else if( GetAsyncKeyState( VK_RIGHT ) & 0x8000 ){
		isPush = true;
	}

	if( isPush ){
		m_HoldRight.iHoldFream ++;
		//�ŏ�.
		if(!m_HoldRight.iFirstPush ){
			m_HoldRight.iFirstPush ++;
			m_HoldRight.iHoldFream = 0;
			return true;
		}
		//��Ԗ�.
		else if(m_HoldRight.iFirstPush == iHOLD_FREAM_FIRST_STEP ){
			if( m_HoldRight.iHoldFream >= iHOLD_FREAM ){
				m_HoldRight.iFirstPush ++;
				m_HoldRight.iHoldFream = 0;
				return true;
			}
		}
		else{
			if( m_HoldRight.iHoldFream >= iHOLD_FREAM_FIRST ){
				m_HoldRight.iHoldFream = 0;
				return true;
			}
		}
	}
	else{
		m_HoldRight.iHoldFream = iHOLD_FREAM;
		m_HoldRight.iFirstPush = 0;
	}

	return false;
}

bool clsSCENE_BASE::isPressHoldLeft( bool isWithStick )
{
	bool isPush = false;
	if( m_wpXInput->isPressStay( XINPUT_LEFT ) ){
		isPush = true;
	}
	else if( m_wpXInput->isSlopeStay( XINPUT_LEFT ) && isWithStick ){
		isPush = true;
	}
	else if( m_wpDxInput->IsLSLeftStay() && isWithStick ){
		isPush = true;
	}
	else if( GetAsyncKeyState( VK_LEFT ) & 0x8000 ){
		isPush = true;
	}

	if( isPush ){
		m_HoldLeft.iHoldFream ++;
		//�ŏ�.
		if(!m_HoldLeft.iFirstPush ){
			m_HoldLeft.iFirstPush ++;
			m_HoldLeft.iHoldFream = 0;
			return true;
		}
		//��Ԗ�.
		else if(m_HoldLeft.iFirstPush == iHOLD_FREAM_FIRST_STEP ){
			if( m_HoldLeft.iHoldFream >= iHOLD_FREAM ){
				m_HoldLeft.iFirstPush ++;
				m_HoldLeft.iHoldFream = 0;
				return true;
			}
		}
		else{
			if( m_HoldLeft.iHoldFream >= iHOLD_FREAM_FIRST ){
				m_HoldLeft.iHoldFream = 0;
				return true;
			}
		}
	}
	else{
		m_HoldLeft.iHoldFream = iHOLD_FREAM;
		m_HoldLeft.iFirstPush = 0;
	}

	return false;
}

bool clsSCENE_BASE::isPressHoldUp( bool isWithStick )
{
	bool isPush = false;
	if( m_wpXInput->isPressStay( XINPUT_UP ) ){
		isPush = true;
	}
	else if( m_wpXInput->isSlopeStay( XINPUT_UP ) && isWithStick ){
		isPush = true;
	}
	else if( m_wpDxInput->IsLSUpStay() && isWithStick ){
		isPush = true;
	}
	else if( GetAsyncKeyState( VK_UP ) & 0x8000 ){
		isPush = true;
	}

	if( isPush ){
		m_HoldUp.iHoldFream ++;
		//�ŏ�.
		if(!m_HoldUp.iFirstPush ){
			m_HoldUp.iFirstPush ++;
			m_HoldUp.iHoldFream = 0;
			return true;
		}
		//��Ԗ�.
		else if(m_HoldUp.iFirstPush == iHOLD_FREAM_FIRST_STEP ){
			if( m_HoldUp.iHoldFream >= iHOLD_FREAM ){
				m_HoldUp.iFirstPush ++;
				m_HoldUp.iHoldFream = 0;
				return true;
			}
		}
		else{
			if( m_HoldUp.iHoldFream >= iHOLD_FREAM_FIRST ){
				m_HoldUp.iHoldFream = 0;
				return true;
			}
		}
	}
	else{
		m_HoldUp.iHoldFream = iHOLD_FREAM;
		m_HoldUp.iFirstPush = 0;
	}

	return false;
}

bool clsSCENE_BASE::isPressHoldDown( bool isWithStick )
{
	bool isPush = false;
	if( m_wpXInput->isPressStay( XINPUT_DOWN ) ){
		isPush = true;
	}
	else if( m_wpXInput->isSlopeStay( XINPUT_DOWN ) && isWithStick ){
		isPush = true;
	}
	else if( m_wpDxInput->IsLSDownStay() && isWithStick ){
		isPush = true;
	}
	else if( GetAsyncKeyState( VK_DOWN ) & 0x8000 ){
		isPush = true;
	}

	if( isPush ){
		m_HoldDown.iHoldFream ++;
		//�ŏ�.
		if( !m_HoldDown.iFirstPush ){
			m_HoldDown.iFirstPush ++;
			m_HoldDown.iHoldFream = 0;
			return true;
		}
		//��Ԗ�.
		else if( m_HoldDown.iFirstPush == iHOLD_FREAM_FIRST_STEP ){
			if( m_HoldDown.iHoldFream >= iHOLD_FREAM ){
				m_HoldDown.iFirstPush ++;
				m_HoldDown.iHoldFream = 0;
				return true;
			}
		}
		else{
			if( m_HoldDown.iHoldFream >= iHOLD_FREAM_FIRST ){
				m_HoldDown.iHoldFream = 0;
				return true;
			}
		}
	}
	else{
		m_HoldDown.iHoldFream = iHOLD_FREAM;
		m_HoldDown.iFirstPush = 0;
	}

	return false;
}


//3D���W���X�N���[��( 2D )���W�ւƕϊ����� conversion(�ϊ�) dimensions(����).
D3DXVECTOR3 clsSCENE_BASE::ConvDimPos( const D3DXVECTOR3 &v3DPos )
{
	D3DXVECTOR3 v2DPos;
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity( &mWorld );
	D3DXVec3Project( &v2DPos, &v3DPos, m_wpViewPort10, &m_mProj, &m_mView, &mWorld );
	return v2DPos;
}


//�[�x�e�X�g(Z�e�X�g)ON/OFF�ؑ�.
void clsSCENE_BASE::SetDepth( const bool isOn )
{
	if( isOn ){
		m_wpContext->OMSetDepthStencilState(
			m_pDepthStencilStateOn, 1 );
	}
	else{
		m_wpContext->OMSetDepthStencilState(
			m_pDepthStencilStateOff, 1 );
	}
}



D3DXVECTOR3 clsSCENE_BASE::GetCameraPos() const
{
	assert( m_wpCamera );
	return m_wpCamera->GetPos();
}
D3DXVECTOR3 clsSCENE_BASE::GetCameraLookPos() const
{
	assert( m_wpCamera );
	return m_wpCamera->GetLookPos();
}




#if _DEBUG

void clsSCENE_BASE::RenderDebugText()
{
	//NULL�`�F�b�N.
	assert( m_upText );

	char strDbgTxt[256];
	int iTxtY = 0;
	const int iOFFSET = 10;//��s���ɂ������ɂ��炷��.

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


//BGM�̃`�F�b�N.
void clsSCENE_BASE::DebugBgm()
{
	if( !m_wpSound ) return;
	static int iBGM_DEBUG_NUMBER = 0;

	if( GetAsyncKeyState( 'N' ) & 0x1 ){
		if( iBGM_DEBUG_NUMBER > 0 )	iBGM_DEBUG_NUMBER --;
		m_wpSound->StopAllSound();
		m_wpSound->PlayBGM( iBGM_DEBUG_NUMBER );
	}
	if( GetAsyncKeyState( 'M' ) & 0x1 ){
		iBGM_DEBUG_NUMBER ++;
		m_wpSound->StopAllSound();
		m_wpSound->PlayBGM( iBGM_DEBUG_NUMBER );
	}

}


#endif //#if _DEBUG



HRESULT clsSCENE_BASE::CreateDepthStencilState()
{
	assert( !m_pDepthStencilStateOn );
	assert( !m_pDepthStencilStateOff );

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc,
		sizeof( D3D11_DEPTH_STENCIL_DESC ) );

	//ON.
	depthStencilDesc.DepthEnable = true;
	m_wpDevice->CreateDepthStencilState(
		&depthStencilDesc, &m_pDepthStencilStateOn );

	//OFF.
	depthStencilDesc.DepthEnable = false;
	m_wpDevice->CreateDepthStencilState(
		&depthStencilDesc, &m_pDepthStencilStateOff );

	return S_OK;
}



//�J�����֐�.
void clsSCENE_BASE::Camera()
{
	//�r���[(�J����)�ϊ�.
	D3DXVECTOR3 vUpVec	( 0.0f, 1.0f, 0.0f );	//����ʒu.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)�r���[�v�Z����.
		&GetCameraPos(), &GetCameraLookPos(), &vUpVec );

}
//�v���W�F�N�V�����֐�.
void clsSCENE_BASE::Proj()
{
	//�v���W�F�N�V����(�ˉe�s��)�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,			//(out)�v���W�F�N�V�����v�Z����.
		fZOOM,	//y�����̎���(���W�A���w��)������傫�������王�삪�����Ȃ�.
		static_cast<FLOAT>( WND_W ) / static_cast<FLOAT>( WND_H ),//�A�X�y�N�g��(��/����).
		0.1f,				//�߂��r���[���ʂ�z�l.
		fRENDER_LIMIT );	//�����r���[���ʂ�z�l.
}


//�f�o�b�O�p�V�[���؂�ւ�.
void clsSCENE_BASE::DebugChangeScene( enSCENE &enNextScene ) const
{
	if( GetAsyncKeyState( 'Y' ) & 0x1 ){
		enNextScene = enSCENE::TITLE;
	}
	else if( GetAsyncKeyState( 'U' ) & 0x1 ){
		enNextScene = enSCENE::ASSEMBLE;
	}
	else if( GetAsyncKeyState( 'I' ) & 0x1 ){
		enNextScene = enSCENE::MISSION;
	}
	else if( GetAsyncKeyState( 'O' ) & 0x1 ){
		enNextScene = enSCENE::ENDING;
	}
	else if( GetAsyncKeyState( 'P' ) & 0x1 ){
		enNextScene = enSCENE::GAMEOVER;
	}
}

void clsSCENE_BASE::SetViewPort( 
	D3D11_VIEWPORT* const pVp, const 
	D3DXVECTOR3 &vCamPos, const D3DXVECTOR3 &vCamLookPos,
	const float fWndW, const float fWndH )
{
	if( !pVp ) return;
	if( m_wpViewPortUsing == pVp ) return;

	m_wpViewPortUsing = pVp;

	//�r���[(�J����)�ϊ�.
	D3DXVECTOR3 vUpVec	( 0.0f, 1.0f, 0.0f );	//����ʒu.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)�r���[�v�Z����.
		&vCamPos, &vCamLookPos, &vUpVec );

	//�v���W�F�N�V����(�ˉe�s��)�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,			//(out)�v���W�F�N�V�����v�Z����.
		fZOOM,	//y�����̎���(���W�A���w��)������傫�������王�삪�����Ȃ�.
		fWndW / fWndH,//�A�X�y�N�g��(��/����).
		0.1f,				//�߂��r���[���ʂ�z�l.
		fRENDER_LIMIT );	//�����r���[���ʂ�z�l.

	assert( m_wpContext );
	m_wpContext->RSSetViewports( 1, m_wpViewPortUsing );

//	//��ʂ̃N���A.
//	m_wpContext->ClearRenderTargetView(
//		pBackBuffer_TexRTV, g_fClearColor );

}


D3D11_VIEWPORT* clsSCENE_BASE::GetViewPortMainPtr()
{
	assert( m_wpViewPort11 );
	return m_wpViewPort11;
}




#ifdef RENDER_SCREEN_TEXTURE_
//�����_�����O�e�N�X�`���p.
HRESULT clsSCENE_BASE::CreateScreenTexture()
{
	//�e�N�X�`��.
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Usage				= D3D11_USAGE_DEFAULT;
	texDesc.Format				= DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags			= D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width				= WND_W;
	texDesc.Height				= WND_H;
	texDesc.CPUAccessFlags		= 0;
	texDesc.MipLevels			= 1;
	texDesc.ArraySize			= 1;
	texDesc.SampleDesc.Count	= 1;
	texDesc.SampleDesc.Quality	= 0;
	texDesc.MiscFlags			= 0;
	
	HRESULT hr = m_wpDevice->CreateTexture2D( &texDesc, nullptr, &m_pScreenTex );
	if( FAILED( hr ) ){
		ERR_MSG( "�X�N���[���e�N�X�`���쐬���s", "" );
		assert( !"�X�N���[���e�N�X�`���쐬���s" );
		return hr;
	}

	//�����_�[�^�[�Q�b�g�r���[.
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format			= DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension	= D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Buffer.ElementOffset					= 0;
	rtvDesc.Buffer.ElementWidth						= 0;
	rtvDesc.Buffer.FirstElement						= 0;
	rtvDesc.Buffer.NumElements						= 0;
	rtvDesc.Texture1D.MipSlice						= 0;
	rtvDesc.Texture1DArray.ArraySize				= 0;
	rtvDesc.Texture1DArray.FirstArraySlice			= 0;
	rtvDesc.Texture1DArray.MipSlice					= 0;
	rtvDesc.Texture2D.MipSlice						= 0;
	rtvDesc.Texture2DArray.ArraySize				= 0;
	rtvDesc.Texture2DArray.FirstArraySlice			= 0;
	rtvDesc.Texture2DArray.MipSlice					= 0;
	rtvDesc.Texture2DMS.UnusedField_NothingToDefine	= 0;
	rtvDesc.Texture2DMSArray.ArraySize				= 0;
	rtvDesc.Texture2DMSArray.FirstArraySlice		= 0;
	rtvDesc.Texture3D.FirstWSlice					= 0;
	rtvDesc.Texture3D.MipSlice						= 0;
	rtvDesc.Texture3D.WSize							= 0;
	
	hr = m_wpDevice->CreateRenderTargetView( m_pScreenTex, &rtvDesc, &m_pScreenRTV );
	if( FAILED( hr ) ){
		ERR_MSG( "�X�N���[�������_�[�^�[�Q�b�g�r���[�쐬���s", "" );
		assert( !"�X�N���[�������_�[�^�[�Q�b�g�r���[�쐬���s" );
		return hr;
	}

	//�V�F�[�_�[���\�[�X�r���[.
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory( &srvDesc, sizeof( srvDesc ) );
	srvDesc.Format				= rtvDesc.Format;
	srvDesc.ViewDimension		= D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels	= 1;

	hr = m_wpDevice->CreateShaderResourceView( m_pScreenTex, &srvDesc, &m_pScreenSRV );
	if( FAILED( hr ) ){
		ERR_MSG( "�X�N���[���V�F�[�_�[���\�[�X�r���[�쐬���s", "" );
		assert( !"�X�N���[���V�F�[�_�[���\�[�X�r���[�쐬���s" );
		return hr;
	}

	//�T���v���[�X�e�[�g.
	D3D11_SAMPLER_DESC smpDesc;
	ZeroMemory( &smpDesc, sizeof( smpDesc ) );
	smpDesc.Filter			= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU		= D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV		= D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW		= D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.ComparisonFunc	= D3D11_COMPARISON_NEVER;
	smpDesc.MinLOD			= 0;
	smpDesc.MaxLOD			= D3D11_FLOAT32_MAX;

	hr = m_wpDevice->CreateSamplerState( &smpDesc, &m_pScreenSmp );
	if( FAILED( hr ) ){
		ERR_MSG( "�X�N���[���T���v���[�X�e�[�g�쐬���s", "" );
		assert( !"�X�N���[���T���v���[�X�e�[�g�쐬���s" );
		return hr;
	}

	//�V�F�[�_�[.
	hr = this->CreateScreenShaderTexture();
	if( FAILED( hr ) ){
		ERR_MSG( "�X�N���[���V�F�[�_�[�쐬���s", "" );
		assert( !"�X�N���[���V�F�[�_�[�쐬���s" );
		return hr;
	}


	return S_OK;
}

HRESULT clsSCENE_BASE::CreateScreenShaderTexture()
{
	const char sSHADER_NAME[] = "Shader\\Sprite2D.hlsl";
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;

	UINT uCompileFlag = 0;

#ifdef _DEBUG
	uCompileFlag
		= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION; 
#endif//#ifdef _DEBUG


	//HLSL����o�[�e�b�N�X�V�F�[�_�̃u���u���쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			sSHADER_NAME,	//�V�F�[�_�t�@�C����(HLSL�t�@�C��).
			NULL,			//�}�N����`�̔z��ւ̃|�C���^(���g�p).
			NULL,			//�C���N���[�h�t�@�C���������C���^�[�t�F�[�X�ւ̃|�C���^(���g�p).
			"VS_Main",			//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.
			"vs_5_0",		//�V�F�[�_�̃��f�����w�肷�镶����(�v���t�@�C��).
			uCompileFlag,	//�V�F�[�_�R���p�C���t���O.
			0,				//�G�t�F�N�g�R���p�C���t���O(���g�p).
			NULL,			//�X���b�h�|���v�C���^�[�t�F�[�X�ւ̃|�C���^(���g�p).
			&pCompiledShader,//�u���u���i�[���郁�����ւ̃|�C���^.
			&pErrors,		//�G���[�ƌx���ꗗ���i�[���郁�����ւ̃|�C���^.
			NULL ) ) )		//�߂�l�ւ̃|�C���^(���g�p).
	{
		MessageBox( NULL, "hlsl(vs)�ǂݍ��ݎ��s", "�G���[", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//��L�ō쐬�����u���u����u�o�[�e�b�N�X�V�F�[�_�v���쐬.
	if( FAILED(
		m_wpDevice->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			NULL,
			&m_pScreenVS ) ) )//(out)�o�[�e�b�N�X�V�F�[�_.
	{
		MessageBox( NULL, "vs�쐬���s", "�G���[", MB_OK );
		return E_FAIL;
	}

	SAFE_RELEASE( pCompiledShader );





	//HLSL����s�N�Z���V�F�[�_�̃u���u���쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			sSHADER_NAME,	//�V�F�[�_�t�@�C����(HLSL�t�@�C��).
			NULL,
			NULL,
			"PS_Main",			//�V�F�[�_�G���g���[�|�C���g�֐��̖��O.
			"ps_5_0",		//�V�F�[�_�̃��f�����w�肷�镶����(�v���t�@�C��).
			uCompileFlag,	//�V�F�[�_�R���p�C���t���O.
			0,
			NULL,
			&pCompiledShader,//�u���u���i�[���郁�����ւ̃|�C���^.
			&pErrors,
			NULL ) ) )
	{
		MessageBox( NULL, "hlsl(ps)�ǂݍ��ݎ��s", "�G���[", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//��L�ō쐬�����u���u����u�s�N�Z���V�F�[�_�v���쐬.
	if( FAILED(
		m_wpDevice->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			NULL,
			&m_pScreenPS ) ) )//(out)�s�N�Z���V�F�[�_.
	{
		MessageBox( NULL, "ps�쐬���s", "�G���[", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );//�u���u���.

	return S_OK;
}


//Rendertarget���e�N�X�`���ɂ���.
void clsSCENE_BASE::SetRenderTargetTexture( ID3D11DepthStencilView* const pDepthStencilView )
{
	//�����_�[�^�[�Q�b�g���e�N�X�`����.
	float clearcolor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	m_wpContext->OMSetRenderTargets( 1, &m_pScreenRTV, pDepthStencilView );
	m_wpContext->ClearRenderTargetView( m_pScreenRTV, clearcolor );
	m_wpContext->ClearDepthStencilView( pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
}

//�e�N�X�`���̓��e����ʂɕ`��.
void clsSCENE_BASE::RenderWindowFromTexture( 
	ID3D11RenderTargetView* const pBackBuffer_TexRTV,
	ID3D11DepthStencilView* const pDepthStencilView )
{
	float clearcolor[] = { 1.5f, 0.5f, 0.5f, 1.0f };
	m_wpContext->OMSetRenderTargets( 1, &pBackBuffer_TexRTV, pDepthStencilView );
	m_wpContext->ClearRenderTargetView( pBackBuffer_TexRTV, clearcolor );
	m_wpContext->ClearDepthStencilView( pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

	ID3D11Buffer* pBuffer;
	//�|��(�l�p�`)�̒��_���쐬.
	float tmpw = WND_W;
	float tmph = WND_H;
	SpriteVertex vertices[] = 
	{
#if 0
		//���_���W(x,y,z).					//UV���W( u, v ).
		D3DXVECTOR3( 0.0f,  tmph,  0.0f ),	D3DXVECTOR2( 0.0f, 1.0f ),//���_1(����).
		D3DXVECTOR3( 0.0f,  0.0f,  0.0f ),	D3DXVECTOR2( 0.0f, 0.0f ),//���_2(����).
		D3DXVECTOR3( tmpw,  tmph,  0.0f ),	D3DXVECTOR2( 1.0f, 1.0f ),//���_3(�E��).
		D3DXVECTOR3( tmpw,  0.0f,  0.0f ),	D3DXVECTOR2( 1.0f, 0.0f ),//���_4(�E��).
#else
		//���_���W(x,y,z).					//UV���W( u, v ).
		D3DXVECTOR3( tmpw,  0.0f,  0.0f ),	D3DXVECTOR2( 1.0f, 0.0f ),//���_4(�E��).
		D3DXVECTOR3( tmpw,  tmph,  0.0f ),	D3DXVECTOR2( 1.0f, 1.0f ),//���_3(�E��).
		D3DXVECTOR3( 0.0f,  tmph,  0.0f ),	D3DXVECTOR2( 0.0f, 1.0f ),//���_1(����).
		D3DXVECTOR3( tmpw,  0.0f,  0.0f ),	D3DXVECTOR2( 1.0f, 0.0f ),//���_4(�E��).
		D3DXVECTOR3( 0.0f,  tmph,  0.0f ),	D3DXVECTOR2( 0.0f, 1.0f ),//���_1(����).
		D3DXVECTOR3( 0.0f,  0.0f,  0.0f ),	D3DXVECTOR2( 0.0f, 0.0f ),//���_2(����).
#endif
	};
	//�ő�v�f�����Z�o����.
	UINT uVerMax = sizeof( vertices ) / sizeof( vertices[0] );

	//�o�b�t�@�\����.
	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof( bd ) );
	bd.Usage				= D3D11_USAGE_DEFAULT;				//�g�p�@(�f�t�H���g).
	bd.ByteWidth			= sizeof( SpriteVertex ) * uVerMax;	//���_�T�C�Y(���_*4).
	bd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;			//���_�o�b�t�@�Ƃ��Ĉ���.
	bd.CPUAccessFlags		= 0;								//CPU����̓A�N�Z�X���Ȃ�.
	bd.MiscFlags			= 0;								//���̑��̃t���O(���g�p).
	bd.StructureByteStride	= 0;								//�\���̃T�C�Y(���g�p).

	//�T�u���\�[�X�f�[�^�\����.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem	= vertices;	//�|���̒��_���Z�b�g.

	//���_�o�b�t�@�̍쐬.
	if( FAILED(
		m_wpDevice->CreateBuffer(
			&bd, &InitData, &pBuffer ) ) )
	{
		ERR_MSG( "�o�b�t�@�쐬���s", "" );
		assert( !"�o�b�t�@�쐬���s" );
		return ;
	}
	//���_�o�b�t�@���Z�b�g.
	UINT stride = sizeof( SpriteVertex );//�f�[�^�Ԋu.

	m_wpContext->VSSetShader( m_pScreenVS, nullptr, 0 );
	m_wpContext->PSSetShader( m_pScreenPS, nullptr, 0 );

	m_wpContext->PSSetShaderResources( 0, 1, &m_pScreenSRV );
	m_wpContext->PSSetSamplers( 0, 1, &m_pScreenSmp );
	uint32_t offset = 0;
	m_wpContext->IASetVertexBuffers( 0, 1, &pBuffer, &stride, &offset );
	m_wpContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	m_wpContext->Draw( uVerMax, 0 );

}
#endif//#ifdef RENDER_SCREEN_TEXTURE_