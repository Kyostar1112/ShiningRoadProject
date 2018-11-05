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
#if _DEBUG
	,m_upText( nullptr )
#endif//#if _DEBUG
	,m_enNextScene(				enSCENE::NOTHING )
	,m_wpViewPortUsing(			m_wpViewPort11 )
	,m_pDepthStencilStateOn(	nullptr )
	,m_pDepthStencilStateOff(	nullptr )
{
//	m_wpViewPortUsing = m_wpViewPort11;
}

clsSCENE_BASE::~clsSCENE_BASE()
{
#if _DEBUG
//	SAFE_DELETE( m_upText );
	if( m_upText ){
		m_upText.reset();
	}
#endif//#if _DEBUG

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


//	m_upKey = make_unique< clsKEY_INPUT >();


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
void clsSCENE_BASE::Render()
{
	//�J�����֐�.
	Camera();
	//�v���W�F�N�V�����֐�.
	Proj();	

	//�e�V�[���̕`��.
	RenderProduct( m_wpCamera->GetPos() );
	
	//�G�t�F�N�g�`��.
	m_wpEffects->Render( m_mView, m_mProj, m_wpCamera->GetPos() );

	//���ʂ�̃r���[�|�[�g.
	SetViewPort( m_wpViewPort11, m_wpCamera->GetPos(), m_wpCamera->GetLookPos(), WND_W, WND_H );

	//�e�V�[����UI�̕`��.
	SetDepth( false );
	RenderUi();
	SetDepth( true );

	//���ʂ�̃r���[�|�[�g.
	if( m_wpViewPortUsing != m_wpViewPort11 ){
		m_wpViewPortUsing = m_wpViewPort11;
		m_wpContext->RSSetViewports( 1, m_wpViewPort11 );
	}

	//�Ó]�`��.
	m_wpBlackScreen->Render();

#if _DEBUG
	//�f�o�b�O�e�L�X�g.
	SetDepth( false );	//Z�e�X�g:OFF.
	RenderDebugText();
	SetDepth( true );	//Z�e�X�g:ON.
#endif//#if _DEBUG

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


//3D���W���X�N���[��( 2D )���W�ւƕϊ�����.dimensions(����) conversion(�ϊ�)
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
