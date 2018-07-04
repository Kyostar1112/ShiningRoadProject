#include "RenderAtStartUp.h"

using namespace std;

const WHSIZE_FLOAT INIT_DISP = { 256, 256 };
const WHSIZE_FLOAT INIT_ANIM = { 3, 2 };

const D3DXVECTOR3 vINIT_POS = { WND_W * 0.5f, WND_H * 0.5f, 0.0f };
const D3DXVECTOR3 vUPDATE_ROT = { 0.0f, 0.0f, 0.0625f };

const char* cIMAGE_PATH = "Data\\Image\\StartUp\\Gear.png";

const char cSPRITE_MAX = 16;

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
}

clsRENDER_AT_START_UP::~clsRENDER_AT_START_UP()
{
	End();
	for( unsigned int i=0; i<m_vupRogo.size(); i++ ){
		if( m_vupRogo[i] ){
			m_vupRogo[i].reset( nullptr );
		}
	}
	m_vupRogo.clear();
	m_vupRogo.shrink_to_fit();

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
	float fFPS		= g_fFPS;//FPS�l.
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

			for( unsigned int i=0; i<m_vupRogo.size(); i++ ){
				m_vupRogo[i]->AddRot( vUPDATE_ROT*( (i+1) * 0.5f) );
			}
			Render();
		}
	}
	timeEndPeriod( 1 );	//����.
}

//�I������.
void clsRENDER_AT_START_UP::End()
{
	m_bEnd = true;
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
		m_vupRogo[i]->Render();
	}
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
