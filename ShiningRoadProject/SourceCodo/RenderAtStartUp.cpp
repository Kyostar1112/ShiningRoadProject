#include "RenderAtStartUp.h"

using namespace std;

const WHSIZE_FLOAT INIT_DISP = { 256, 256 };

const D3DXVECTOR3 vINIT_POS = { WND_W * 0.5f, WND_H * 0.5f, 0.0f };
const D3DXVECTOR3 vUPDATE_ROT = { 0.0f, 0.0f, 0.125f };

const char* cIMAGE_PATH = "Data\\Image\\PartsIcon\\NoData.png";

clsRENDER_AT_START_UP::clsRENDER_AT_START_UP(	
	ID3D11Device*			const pDevice,
	ID3D11DeviceContext*	const pContext,
	IDXGISwapChain*			const pSwapChain,
	ID3D11RenderTargetView*	const pBackBuffer_TexRTV,
	ID3D11DepthStencilView*	const pBackBuffer_DSTexDSV )
:m_wpDevice(pDevice)
,m_wpContext( pContext )
,m_wpSwapChain( pSwapChain )
,m_wpBackBuffer_TexRTV( pBackBuffer_TexRTV )
,m_wpBackBuffer_DSTexDSV( pBackBuffer_DSTexDSV )
{
	SPRITE_STATE ss;
	ss.Disp = INIT_DISP;

	m_upRogo = make_unique< clsSPRITE2D_CENTER >();
	m_upRogo->Create( m_wpDevice, m_wpContext, cIMAGE_PATH, ss );

	m_upRogo->SetPos( vINIT_POS );
}

clsRENDER_AT_START_UP::~clsRENDER_AT_START_UP()
{
	if( m_upRogo ){
		m_upRogo.reset( nullptr );
	}

	m_wpContext = nullptr;			
	m_wpSwapChain = nullptr;			
	m_wpBackBuffer_TexRTV = nullptr;	
	m_wpBackBuffer_DSTexDSV = nullptr;
}


//���[�v����.
void clsRENDER_AT_START_UP::Loop()
{
	m_upRogo->AddRot( vUPDATE_ROT );
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

	m_upRogo->Render();

	//�����_�����O���ꂽ�C���[�W��\��.
	m_wpSwapChain->Present( 0, 0 );
}
