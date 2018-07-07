#include "RenderAtStartUp.h"

using namespace std;

//==============================================================.
const WHSIZE_FLOAT INIT_DISP = { 256, 256 };
const WHSIZE_FLOAT INIT_ANIM = { 3, 2 };

const D3DXVECTOR3 vINIT_POS = { WND_W * 0.5f, WND_H * 0.5f, 0.0f };
const D3DXVECTOR3 vUPDATE_ROT = { 0.0f, 0.0f, 0.0625f };

const char* cIMAGE_PATH = "Data\\Image\\StartUp\\Gear.png";

//���Ԑ�.
const char cSPRITE_MAX = 16;
//==============================================================.



//==============================================================.
//�����ʒu.
const D3DXVECTOR3 vINIT_LINE_BOX_POS = { WND_W * 0.5f, WND_H * 0.5f, 0.0f };
const D3DXVECTOR3 vINIT_GAGE_BOX_POS = { WND_W * 0.5f, WND_H * 0.75f, 0.0f };


//�ҋ@����.
const int iSTOP_TIME_SHORT = 6;
const int iSTOP_TIME_LONG = 60;

//�����傫���Ȃ�x��.
const float fLINE_BOX_ADD_SIZE = 128.0f;
const float fGAGE_BOX_ADD_SIZE = 64.0f;

//�ŏI�I�Ȕ��̑傫��.
const D3DXVECTOR3 vLINE_BOX_SIZE = { WND_W - 32.0f, WND_H - 32.0f, 0.0f };
const D3DXVECTOR3 vGAGE_BOX_SIZE = { 720.0f, 64.0f, 0.0f };


//�Q�[�W�{�̂̃p�X.
const char* cGAGE_PATH = "Data\\Image\\StartUp\\LodeGage.png";
//�Q�[�W�{�̂̐�.
const char cGAGE_MAX = 8;
//�Q�[�W�{�̂̓��ߗ�.
const float fGAGE_ALPHA_OFFSET = 0.125f;
//�Q�[�W�T�C�Y.
const WHSIZE_FLOAT INIT_DISP_GAGE = { 1.0f, 1.0f };
//�Q�[�W�͘g�̉�����?.
const float fGAGE_SIZE_RATE = 64.0f;

//==============================================================.





clsRENDER_AT_START_UP::clsRENDER_AT_START_UP(	
	ID3D11Device*			 const pDevice,
	ID3D11DeviceContext*	 const pContext,
	IDXGISwapChain*			 const pSwapChain,
	ID3D11RenderTargetView*	 const pBackBuffer_TexRTV,
	ID3D11DepthStencilView*	 const pBackBuffer_DSTexDSV,
	ID3D11DepthStencilState* const pDepthStencilState )
:m_wpDevice(pDevice)
,m_wpContext( pContext )
,m_wpSwapChain( pSwapChain )
,m_wpBackBuffer_TexRTV( pBackBuffer_TexRTV )
,m_wpBackBuffer_DSTexDSV( pBackBuffer_DSTexDSV )
,m_wpDepthStencilState( pDepthStencilState )
,m_bEnd( false )
,m_enMode( enMODE::LINE_V )
,m_iTimer( 0 )
{
	SPRITE_STATE ss;
	ss.Disp = INIT_DISP;
	ss.Anim = INIT_ANIM;

	m_vupRogo.reserve( cSPRITE_MAX );
	for( char i=0; i<cSPRITE_MAX; i++ ){
		m_vupRogo.push_back( nullptr );
		m_vupRogo[i] = make_unique< clsSPRITE2D_CENTER >();
		m_vupRogo[i]->Create( m_wpDevice, m_wpContext, cIMAGE_PATH, ss );

	//	m_upRogo->SetPos( vINIT_POS );
		float tmpY;
		if( i%2 )	tmpY = -128.0f;
		else		tmpY = WND_H * 0.5f;
		m_vupRogo[i]->SetPos( { -128.0f, tmpY, 0.0f } );//256size.
		m_vupRogo[i]->AddPos( { 96.0f*i, 32.0f*i, 0.0f } );
		m_vupRogo[i]->SetAnim( { ( i % 3 ), ( i % 2 ) } );
		float tmpAlpha;
		if( i%2 )	tmpAlpha = 0.75f;
		else		tmpAlpha = 0.5f;
		m_vupRogo[i]->SetAlpha( tmpAlpha );
	}

	m_vupGage.reserve( fGAGE_ALPHA_OFFSET );
	ss.Disp = INIT_DISP_GAGE;
	for( char i=0; i<cGAGE_MAX; i++ ){
		m_vupGage.push_back( nullptr );
		m_vupGage[i] = make_unique< clsSPRITE2D_CENTER >();
		m_vupGage[i]->Create( m_wpDevice, m_wpContext, cGAGE_PATH, ss );

		m_vupGage[i]->SetScale( 0.0f );

		float tmp = 1.0f - ( fGAGE_ALPHA_OFFSET * static_cast<float>( i ) );
		m_vupGage[i]->SetAlpha( tmp );
	}



	if( !m_upLineBox ){
		m_upLineBox = make_unique< clsLINE_BOX >();
		m_upLineBox->Create( pDevice, pContext );
		m_upLineBox->SetPos( vINIT_LINE_BOX_POS );
	}

	if( !m_upGageBox ){
		m_upGageBox = make_unique< clsLINE_BOX >();
		m_upGageBox->Create( pDevice, pContext );
		m_upGageBox->SetPos( vINIT_GAGE_BOX_POS );
	}

}

clsRENDER_AT_START_UP::~clsRENDER_AT_START_UP()
{
	End();
	for( unsigned int i=0; i<m_vupGage.size(); i++ ){
		if( m_vupGage[i] ){
			m_vupGage[i].reset( nullptr );
		}
	}
	m_vupGage.clear();
	m_vupGage.shrink_to_fit();

	for( unsigned int i=0; i<m_vupRogo.size(); i++ ){
		if( m_vupRogo[i] ){
			m_vupRogo[i].reset( nullptr );
		}
	}
	m_vupRogo.clear();
	m_vupRogo.shrink_to_fit();

	if( m_upLineBox ){
		m_upLineBox.reset( nullptr );
	}

	if( m_upGageBox ){
		m_upGageBox.reset( nullptr );
	}

	m_bEnd = false;

	m_wpDepthStencilState = nullptr;
	m_wpBackBuffer_DSTexDSV = nullptr;
	m_wpBackBuffer_TexRTV = nullptr;	
	m_wpSwapChain = nullptr;			
	m_wpContext = nullptr;		
	m_wpDevice = nullptr;
}


//���[�v����.
void clsRENDER_AT_START_UP::Loop()
{
	//----------------------------------------------------------
	//	�t���[�����[�g.
	//----------------------------------------------------------
	float fRate		= 0.0f;	//���[�g.
	float fFPS		= 60.0f;//FPS�l.
	DWORD sync_old	= timeGetTime();	//�ߋ�����.
	DWORD sync_now;
	//���ԏ����ׁ̈A�ŏ��P�ʂ�1�~���b�ɕύX.
	timeBeginPeriod( 1 );

	while( !m_bEnd )
	{
		Sleep( 1 );
		sync_now = timeGetTime();	//���ݎ��Ԃ��擾.

		fRate = 1000.0f / fFPS;	//���z���Ԃ��Z�o.

		if( sync_now - sync_old >= fRate ){
			sync_old = sync_now;	//���ݎ��Ԃɒu������.

			Update();
		}
	}
	timeEndPeriod( 1 );	//����.
}

//�I������.
void clsRENDER_AT_START_UP::End()
{
	m_bEnd = true;
}


void clsRENDER_AT_START_UP::Update()
{
	for( unsigned int i=0; i<m_vupRogo.size(); i++ ){
		m_vupRogo[i]->AddRot( vUPDATE_ROT*( (i+1) * 0.5f) );
	}


	switch( m_enMode )
	{
	case enMODE::LINE_V://�O�g���c�ɑ傫���Ȃ�.
		if( m_iTimer < iSTOP_TIME_LONG ) break;
		m_upLineBox->AddSize( { 0.0f, fLINE_BOX_ADD_SIZE, 0.0f } );

		if( m_upLineBox->GetSize().y >= vLINE_BOX_SIZE.y ){
			m_upLineBox->SetSize( { 0.0f, vLINE_BOX_SIZE.y, 1.0f } );
			m_enMode = enMODE::LINE_H;
			m_iTimer = 0;
		}
		break;
	
	case enMODE::LINE_H://�O�g�����ɑ傫���Ȃ�.
		if( m_iTimer < iSTOP_TIME_SHORT ) break;
		m_upLineBox->AddSize( { fLINE_BOX_ADD_SIZE, 0.0f, 0.0f } );


		if( m_upLineBox->GetSize().x >= vLINE_BOX_SIZE.x ){
			m_upLineBox->SetSize( { vLINE_BOX_SIZE.x, vLINE_BOX_SIZE.y, 1.0f } );
			m_enMode = enMODE::GAGE_H;
			m_iTimer = 0;
		}
		break;
	
	case enMODE::GAGE_H://�Q�[�W�̘g�����ɑ傫���Ȃ�.
		if( m_iTimer < iSTOP_TIME_LONG ) break;
		m_upGageBox->AddSize( { fGAGE_BOX_ADD_SIZE, 0.0f, 0.0f } );

		if( m_upGageBox->GetSize().x >= vGAGE_BOX_SIZE.x ){
			m_upGageBox->SetSize( { vGAGE_BOX_SIZE.x, 0.0f, 1.0f } );
			m_enMode = enMODE::GAGE_V;
			m_iTimer = 0;
		}
		break;
	
	case enMODE::GAGE_V://�Q�[�W�̘g���c�ɑ傫���Ȃ�.
		if( m_iTimer < iSTOP_TIME_SHORT ) break;
		m_upGageBox->AddSize( { 0.0f, fGAGE_BOX_ADD_SIZE, 0.0f } );

		if( m_upGageBox->GetSize().y >= vGAGE_BOX_SIZE.y ){
			m_upGageBox->SetSize( { vGAGE_BOX_SIZE.x, vGAGE_BOX_SIZE.y, 1.0f } );
			m_enMode = enMODE::GAGE_MOVE;
			m_iTimer = 0;

			//�Q�[�W�̏�����.
			for( char i=0; i<m_vupGage.size(); i++ ){
				m_vupGage[i]->SetScale( {
					m_upGageBox->GetSize().x / fGAGE_SIZE_RATE, m_upGageBox->GetSize().y, 0.0f } );
				m_vupGage[i]->SetPos( {
					0.0f - ( m_vupGage[i]->GetScale().x * static_cast<float>( i ) ), 
					m_upGageBox->GetPos().y, 
					0.0f } );
			}
		}
		break;
	
	case enMODE::GAGE_MOVE://�Q�[�W������.
		if( m_iTimer < iSTOP_TIME_SHORT ) break;

		for( char i=0; i<m_vupGage.size(); i++ ){
			m_vupGage[i]->AddPos( { m_vupGage[i]->GetScale().x, 0.0f, 0.0f } );
			if( m_vupGage[i]->GetPos().x > WND_W ){
				m_vupGage[i]->SetPos( { 
					m_upGageBox->GetPos().x - ( m_upGageBox->GetSize().x * 0.5f ), 
					m_upGageBox->GetPos().y,
					0.0f } );
			}
		}
		break;
	}
	m_iTimer ++;

	m_upLineBox->Update();
	m_upGageBox->Update();

	Render();

}

//�N�����̕`��.
void clsRENDER_AT_START_UP::Render()
{
	//��ʂ̃N���A.
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };//�N���A�F(RGBA��)(0.0f~1.0f).
	//�J���[�o�b�N�o�b�t�@.
	m_wpContext->ClearRenderTargetView(
		m_wpBackBuffer_TexRTV, ClearColor );
	//�f�v�X�X�e���V���r���[�o�b�N�o�b�t�@.
	m_wpContext->ClearDepthStencilView(
		m_wpBackBuffer_DSTexDSV,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 0 );

	SetDepth( false );	//Z�e�X�g:OFF.


	for( unsigned int i=0; i<m_vupRogo.size(); i++ ){
//		m_vupRogo[i]->Render();
	}

	for( unsigned int i=0; i<m_vupGage.size(); i++ ){
		//�g�̒������`�悷��.
		if( m_vupGage[i]->GetPos().x < m_upGageBox->GetPos().x - ( m_upGageBox->GetSize().x * 0.5f ) ||
			m_vupGage[i]->GetPos().x > m_upGageBox->GetPos().x + ( m_upGageBox->GetSize().x * 0.5f ) )
		{ continue; }
		m_vupGage[i]->Render();
	}

	m_upLineBox->Render();
	m_upGageBox->Render();

	SetDepth( true );	//Z�e�X�g:ON.

	//�����_�����O���ꂽ�C���[�W��\��.
	m_wpSwapChain->Present( 0, 0 );
}


//�[�x�e�X�g(Z�e�X�g)ON/OFF�ؑ�.
void clsRENDER_AT_START_UP::SetDepth( bool isOn )
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc,
		sizeof( D3D11_DEPTH_STENCIL_DESC ) );
	depthStencilDesc.DepthEnable = isOn;

	m_wpDevice->CreateDepthStencilState(
		&depthStencilDesc, &m_wpDepthStencilState );
	m_wpContext->OMSetDepthStencilState(
		m_wpDepthStencilState, 1 );
}
