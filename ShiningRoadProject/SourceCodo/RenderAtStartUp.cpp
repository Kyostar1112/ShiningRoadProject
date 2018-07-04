#include "RenderAtStartUp.h"

using namespace std;

const WHSIZE_FLOAT INIT_DISP = { 256, 256 };

const D3DXVECTOR3 vINIT_POS = { WND_W * 0.5f, WND_H * 0.5f, 0.0f };
const D3DXVECTOR3 vUPDATE_ROT = { 0.0f, 0.0f, 0.0625f };

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
,m_bEnd( false )
{
	SPRITE_STATE ss;
	ss.Disp = INIT_DISP;

	for(int i=0; i<TEST_MAX_BEI_MAX; i++)m_upRogo[i] = make_unique< clsSPRITE2D_CENTER >();
	for(int i=0; i<TEST_MAX_BEI_MAX; i++)m_upRogo[i]->Create( m_wpDevice, m_wpContext, cIMAGE_PATH, ss );

//	m_upRogo->SetPos( vINIT_POS );
	for(int i=0; i<TEST_MAX_BEI_MAX; i++)m_upRogo[i]->SetPos( { 0.0f, 0.0f, 0.0f } );
	for(int i=0; i<TEST_MAX_BEI_MAX; i++)m_upRogo[i]->AddPos( { 5.0f*i, 1.0f*i, 0.0f } );
}

clsRENDER_AT_START_UP::~clsRENDER_AT_START_UP()
{
	End();
	for(int i=0; i<TEST_MAX_BEI_MAX; i++){
		if( m_upRogo[i] ){
			m_upRogo[i].reset( nullptr );
		}
	}
	m_bEnd = false;

	m_wpContext = nullptr;			
	m_wpSwapChain = nullptr;			
	m_wpBackBuffer_TexRTV = nullptr;	
	m_wpBackBuffer_DSTexDSV = nullptr;
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

			for(int i=0; i<TEST_MAX_BEI_MAX; i++)m_upRogo[i]->AddRot( vUPDATE_ROT*i );
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

	for(int i=0; i<TEST_MAX_BEI_MAX; i++)m_upRogo[i]->Render();

	//�����_�����O���ꂽ�C���[�W��\��.
	m_wpSwapChain->Present( 0, 0 );
}
