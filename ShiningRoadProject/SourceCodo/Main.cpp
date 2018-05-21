#include "Main.h"
#include <stdio.h>

//Using�錾.
using namespace std;

//��������������������������������������������
//�O���[�o���ϐ�.
//��������������������������������������������
clsMain* g_pClsMain = nullptr;


//��������������������������������������������
//	�萔.
//��������������������������������������������








//���C�g����.
const D3DXVECTOR3 vLIGHT_DIR = { 0.0f, 0.01f, 0.02f };

//�J�����̂��.
const float fZOOM = static_cast<float>( D3DX_PI / 4.0 );

//�`����E����.
const float fRENDER_LIMIT = 150.0f;











//��������������������������������������������
//	�萔�I��.
//��������������������������������������������

//============================================================
//	���C���֐�.
//============================================================
INT WINAPI WinMain(
	HINSTANCE hInstance,		//�C���X�^���ԍ�(�E�B���h�E�̔ԍ�).
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	INT nCmdShow )
{
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	g_pClsMain = new clsMain;	//������&�N���X�̐錾.

	//�N���X�����݂��Ă��邩�`�F�b�N.
	if( g_pClsMain != nullptr ){
		//�E�B���h�E�쐬����.
		if( SUCCEEDED(
			g_pClsMain->InitWindow(
				hInstance,
				64, 64,
				WND_W, WND_H,
				WND_TITLE ) ) )
		{
			//Dx11�p�̏�����
			if( SUCCEEDED( g_pClsMain->InitD3D() ) ){
				//���b�Z�[�W���[�v.
				g_pClsMain->Loop();
			}
		}
		//�I��.
		g_pClsMain->DestroyD3D();//Direct3D�̉��.

		delete g_pClsMain;		//�N���X�̔j��.
	}

	return 0;
}


//============================================================
//	�E�B���h�E�v���V�[�W��.
//============================================================
LRESULT CALLBACK WndProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam )
{
	//�v���V�[�W��.
	return g_pClsMain->MsgProc( hWnd, uMsg, wParam, lParam );
}


//============================================================
//	���C���N���X.
//============================================================

//============================================================
//	�R���X�g���N�^.
//============================================================
clsMain::clsMain() :
	m_hWnd( nullptr ),
	m_pDevice( nullptr ),
	m_pDeviceContext( nullptr ),
	m_pSwapChain( nullptr ),
	m_pBackBuffer_TexRTV( nullptr ),
	m_pBackBuffer_DSTex( nullptr ),
	m_pBackBuffer_DSTexDSV( nullptr ),
	m_pDepthStencilState( nullptr ),
	m_pGame( nullptr )
{

	//���C�g����.
	m_vLight = vLIGHT_DIR;

}

//============================================================
//	�f�X�g���N�^.
//============================================================
clsMain::~clsMain()
{

}

//============================================================
//�E�B���h�E�������֐�.
//============================================================
HRESULT clsMain::InitWindow(
	HINSTANCE hInstance,	//�C���X�^���X.
	INT x, INT y,			//�E�B���h�E��x,y���W.
	INT width, INT height,	//�E�B���h�E�̕�,����.
	LPSTR WindowName )		//�E�B���h�E��.
{
	//�E�B���h�E�̒�`.
	WNDCLASSEX wc;
	ZeroMemory( &wc, sizeof( wc ) );//������.

	wc.cbSize			= sizeof( wc );
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= WndProc;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH)GetStockObject( LTGRAY_BRUSH );
	wc.lpszClassName	= APR_NAME;
	wc.hIconSm			= LoadIcon( NULL, IDI_APPLICATION );

	//�E�B���h�E�N���X��Windows�ɓo�^.
	if( !RegisterClassEx( &wc ) ){
		MessageBox( NULL, "�E�B���h�E�N���X�m�o�^�Ƀ~�X", "clsMainInitWindow", MB_OK );
		return E_FAIL;
	}

	//�E�B���h�E�̍쐬.
	m_hWnd = CreateWindow(
		APR_NAME,			//�A�v����.
		WindowName,			//�E�B���h�E�^�C�g��.
		WS_OVERLAPPEDWINDOW,//�E�B���h�E���.
		x, y,				//�\�����W.
		width, height,		//�E�B���h�E�̕�,����.
		NULL,				//�e�E�B���h�E�n���h��.
		NULL,				//���j���[�ݒ�.
		hInstance,			//�C���X�^���X�ԍ�.
		NULL );				//�E�B���h�E�쐬���ɔ�������C�x���g�ɓn���f�[�^.

	if( !m_hWnd ){
		MessageBox( NULL, "�E�B���h�E�쐬�Ƀ~�X", "clsMain::InitWindow", MB_OK );
		return E_FAIL;
	}
#ifdef Inoue
#ifdef _DEBUG
	DragAcceptFiles(
		m_hWnd,    // �o�^����E�B���h�E
		true // �A�N�Z�v�g�I�v�V����
	   );
#endif	//#ifdef _DEBUG
#endif//#ifdef Inoue

	//�E�B���h�E�̕\��.
	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );

	//�}�E�X�J�[�\���̔�\��.
#ifndef _DEBUG
	ShowCursor(false);
#endif//#ifndef _DEBUG

	return S_OK;
}

//============================================================
//	�E�B���h�E�֐�(���b�Z�[�W���̏���).
//============================================================
LRESULT clsMain::MsgProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_DESTROY:	//�E�B���h�E�j����.
		//�A�v���P�[�V�����̏I����Windows�ɒʒm����.
		PostQuitMessage( 0 );
		break;
	case WM_DROPFILES:
//		{
//		HDROP hDrop;
//		UINT uFileNo;
//		g_bFileActive = true;
//		hDrop = (HDROP)wParam;
//		uFileNo = DragQueryFile( (HDROP)wParam, 0xFFFFFFFF, NULL, 0 );
//		char Path[MAX_PATH];
//		for (int i = 0; i < (int)uFileNo; i++){
//			DragQueryFile( hDrop, i, Path, sizeof( Path ) );
//			g_vsFilePath.push_back(Path);
//		}
//		DragFinish( hDrop );
//		}
		break;
	case WM_KEYDOWN:	//�L�[�{�[�h�������ꂽ�Ƃ�.
		//�L�[�ʂ̏���.
		switch( (char)wParam )
		{
		case VK_ESCAPE:	//ESC�L�[.
			if( MessageBox( NULL,
				"�Q�[�����I�����܂���?", "Message",
				MB_YESNO ) == IDYES )
			{
				//�E�B���h�E��j������.
				DestroyWindow( hWnd );
			}
			break;
		}
		break;
	}

	//���C���ɕԂ����.
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


//============================================================
//	���b�Z�[�W���[�v�ƃA�v���P�[�V���������̓����.
//============================================================
void clsMain::Loop()
{
	//���b�V���ǂݍ��݊֐����܂Ƃ߂�����.
	ReadMesh();


	//----------------------------------------------------------
	//	�t���[�����[�g.
	//----------------------------------------------------------
	float fRate		= 0.0f;	//���[�g.
	float fFPS		= 60.0f;//FPS�l.
	DWORD sync_old	= timeGetTime();	//�ߋ�����.
	DWORD sync_now;
	//���ԏ����ׁ̈A�ŏ��P�ʂ�1�~���b�ɕύX.
	timeBeginPeriod( 1 );


	//���b�Z�[�W���[�v.
	MSG msg = { 0 };
	ZeroMemory( &msg, sizeof( msg ) );

	while( msg.message != WM_QUIT )
	{
		Sleep( 1 );
		sync_now = timeGetTime();	//���ݎ��Ԃ��擾.

		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ){
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		fRate = 1000.0f / fFPS;	//���z���Ԃ��Z�o.

		if( sync_now - sync_old >= fRate ){
			sync_old = sync_now;	//���ݎ��Ԃɒu������.

			//�A�v���P�[�V���������͂���������.
			AppMain();
		}
	}
	//�A�v���P�[�V�����̏I��.
	timeEndPeriod( 1 );	//����.
}

//============================================================
//	�A�v���P�[�V�������C������.
//============================================================
void clsMain::AppMain()
{
#if _DEBUG

#endif //#if _DEBUG

	//�Q�[�����[�v.
	ASSERT_IF_NULL( m_pGame );
	m_pGame->Update();

	//�����_�����O.
	Render();
}

//============================================================
//	�`��(�����_�����O).
//	�V�[��(���)����ʂɃ����_�����O(�`��).
//	(��DX9MESH����Main����2���݂���̂Œ���).
//============================================================
void clsMain::Render()
{
	//��ʂ̃N���A.
	float ClearColor[4] = { 0.5f, 0.25f, 2.0f, 1.0f };//�N���A�F(RGBA��)(0.0f~1.0f).
	//�J���[�o�b�N�o�b�t�@.
	m_pDeviceContext->ClearRenderTargetView(
		m_pBackBuffer_TexRTV, ClearColor );
	//�f�v�X�X�e���V���r���[�o�b�N�o�b�t�@.
	m_pDeviceContext->ClearDepthStencilView(
		m_pBackBuffer_DSTexDSV,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 0 );

	//�J�����֐�.
	Camera();
	//�v���W�F�N�V�����֐�.
	Proj();

	//����Render�֐��̑O��AppMain�֐��Ń`�F�b�N���Ă���̂ŃA�T�[�g�͏Ȃ�.
//	ASSERT_IF_NULL( m_pGame );
	m_pGame->Render( m_mView, m_mProj, m_vLight );
	
	//2D?.
//	SetDepth( false );	//Z�e�X�g:OFF.
//	SetDepth( true );	//Z�e�X�g:ON.


#if _DEBUG
	SetDepth( false );	//Z�e�X�g:OFF.
	//�f�o�b�O�e�L�X�g.
	RenderDebugText();
	SetDepth( true );	//Z�e�X�g:ON.
#endif//#if _DEBUG

	//�����_�����O���ꂽ�C���[�W��\��.
	m_pSwapChain->Present( 0, 0 );

}


//============================================================
//	DirectX������.
//============================================================
HRESULT clsMain::InitD3D()
{
	//---------------------------------------------------
	//	�f�o�C�X�ƃX���b�v�`�F�[���֌W.
	//---------------------------------------------------

	//�X���b�v�`�F�[���\����.
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount		= 1;		//�o�b�N�o�b�t�@�̐�.
	sd.BufferDesc.Width	= WND_W;
	sd.BufferDesc.Height= WND_H;
	sd.BufferDesc.Format= DXGI_FORMAT_R8G8B8A8_UNORM;
									//�t�H�[�}�b�g(32�r�b�g�J���[).
	sd.BufferDesc.RefreshRate.Numerator = 60;
									//���t���b�V�����[�g(����) ��FPS:60.
	sd.BufferDesc.RefreshRate.Denominator = 1;
									//���t���b�V�����[�g(���q).
	sd.BufferUsage		= DXGI_USAGE_RENDER_TARGET_OUTPUT;
									//�g����(�\����).
	sd.OutputWindow		= m_hWnd;	//�E�B���h�E�n���h��.
	sd.SampleDesc.Count	= 1;		//�}���`�T���v���̐�.
	sd.SampleDesc.Quality=0;		//�}���`�T���v���̃N�I���e�B.
	sd.Windowed			= TRUE;		//�E�B���h�E���[�h(�t���X�N����FALSE).


	//�쐬�����݂�@�\���x���̗D����w��.
	//	(GPU���T�|�[�g����@�\�Z�b�g�̒�`).
	//	D3D_FEATURE_LEVEL�񋓑̂̔z��.
	//	D3D_FEATURE_LEVEL_10_1:Direct3D 10.1��GPU���x��.
	D3D_FEATURE_LEVEL	pFeatureLevels	= D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL*	pFeatureLevel	= nullptr;	//�z��̗v�f��.


	//�f�o�C�X�ƃX���b�v�`�F�[���̍쐬.
	//	�n�[�h�E�F�A(GPU)�f�o�C�X�ō쐬.
	if( FAILED(
		D3D11CreateDeviceAndSwapChain(
			NULL,					//�r�f�I�A�_�v�^�ւ̃|�C���^.
			D3D_DRIVER_TYPE_HARDWARE,//�쐬����f�o�C�X�̎��.
			NULL,					//�\�t�g�E�F�A���X�^���C�U�[����������DLL�̃n���h��.
			0,						//�L���ɂ��郉���^�C�����C���[.
			&pFeatureLevels,		//�쐬�����݂�@�\���x���̏������w�肷��z��.
			1,						//���̗v�f��.
			D3D11_SDK_VERSION,		//SDK�̃o�[�W����.
			&sd,					//�X���b�v�`�F�[���̏������p�����[�^�̃|�C���^.
			&m_pSwapChain,			//(out)�����_�����O�Ɏg�p���ꂽ�X���b�v�`�F�[��.
			&m_pDevice,				//(out)�쐬���ꂽ�f�o�C�X.
			pFeatureLevel,			//�@�\���x���̔z��ɂ���ŏ��̗v�f��\���|�C���^.
			&m_pDeviceContext ) ) )	//(out)�f�o�C�X�R���e�L�X�g.
	{
		//WARP�f�o�C�X�̍쐬.
		// D3D_FEATURE_LEVEL_9_1 �` D3D_FEATURE_LEVEL_10_1.
		if( FAILED(
			D3D11CreateDeviceAndSwapChain(
				NULL, D3D_DRIVER_TYPE_WARP,
				NULL, 0, &pFeatureLevels, 1,
				D3D11_SDK_VERSION, &sd,
				&m_pSwapChain, &m_pDevice,
				pFeatureLevel, &m_pDeviceContext ) ) )
		{
			//���t�@�����X�f�o�C�X�̍쐬.
			//	DirectX SDK���C���X�g�[������Ă��Ȃ��Ǝg���Ȃ�.
			if( FAILED(
				D3D11CreateDeviceAndSwapChain(
					NULL, D3D_DRIVER_TYPE_REFERENCE,
					NULL, 0, &pFeatureLevels, 1,
					D3D11_SDK_VERSION, &sd,
					&m_pSwapChain, &m_pDevice,
					pFeatureLevel, &m_pDeviceContext ) ) )
			{
				MessageBox( NULL, "�f�o�C�X�ƃX���b�v�`�F�[���̍쐬�Ƀ~�X", "error(main.cpp)", MB_OK );
				return E_FAIL;
			}
		}
	}


	//�e��e�N�X�`���[�ƁA����ɕt�т���e��r���[(���)���쐬.

	//---------------------------------------------------
	//	�o�b�N�o�b�t�@����:�J���[�o�b�t�@�ݒ�.
	//---------------------------------------------------

	//�o�b�N�o�b�t�@�e�N�X�`���[���擾(���ɂ���̂ō쐬�͂Ȃ�).
	ID3D11Texture2D *pBackBuffer_Tex;
	m_pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),	//__uuidof:���Ɋ֘A�t����GUID���擾.
									//		   Texture2D�̗B��̕��Ƃ��Ĉ���.
		(LPVOID*)&pBackBuffer_Tex );//(out)�o�b�N�o�b�t�@�e�N�X�`��.

	//���̃e�N�X�`���[�ɑ΂������_�[�^�[�Q�b�g�r���[(RTV)���쐬.
	m_pDevice->CreateRenderTargetView(
		pBackBuffer_Tex,
		NULL,
		&m_pBackBuffer_TexRTV );//(out)RTV.
	//�o�b�N�o�b�t�@�e�N�X�`���[�����.
	SAFE_RELEASE( pBackBuffer_Tex );//�}�N�����ɃZ�~�R����������̂ł���Ȃ��������ڂ̓���ł��Ă���.

	//---------------------------------------------------
	//	�o�b�N�o�b�t�@����:�f�v�X(�[�x)�X�e���V���֌W.
	//---------------------------------------------------

	//�f�v�X(�[��or�[�x)�X�e���V���r���[�p�̃e�N�X�`���[���쐬.
	D3D11_TEXTURE2D_DESC descDepth;

	descDepth.Width				= WND_W;					//��.
	descDepth.Height			= WND_H;					//����.
	descDepth.MipLevels			= 1;						//�~�b�v�}�b�v���x��:1.
	descDepth.ArraySize			= 1;						//�z��:1.
	descDepth.Format			= DXGI_FORMAT_D32_FLOAT;	//32�r�b�g�t�H�[�}�b�g.
	descDepth.SampleDesc.Count	= 1;						//�}���`�T���v���̐�.
	descDepth.SampleDesc.Quality= 0;						//�}���`�T���v���̃N�I���e�B.
	descDepth.Usage				= D3D11_USAGE_DEFAULT;		//�g�p���@:�f�t�H���g.
	descDepth.BindFlags			= D3D11_BIND_DEPTH_STENCIL;	//�[�x(�X�e���V���Ƃ��Ďg�p).
	descDepth.CPUAccessFlags	= 0;						//CPU����A�N�Z�X���Ȃ�.
	descDepth.MiscFlags			= 0;						//���̑��ݒ�Ȃ�.

	m_pDevice->CreateTexture2D(
		&descDepth,
		NULL,
		&m_pBackBuffer_DSTex );//(out)�f�v�X�X�e���V���p�e�N�X�`��.

	//���̃e�N�X�`���ɑ΂��f�v�X�X�e���V���r���[(DSV)���쐬.
	m_pDevice->CreateDepthStencilView(
		m_pBackBuffer_DSTex,
		NULL,
		&m_pBackBuffer_DSTexDSV );//(out)DSV.

	//�����_�[�^�[�Q�b�g�r���[�ƃf�v�X�X�e���V���r���[���p�C�v���C���ɃZ�b�g.
	m_pDeviceContext->OMSetRenderTargets(
		1,
		&m_pBackBuffer_TexRTV,
		m_pBackBuffer_DSTexDSV );


	//�[�x�e�X�g(Z�e�X�g)��L���ɂ���.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc,
		sizeof( D3D11_DEPTH_STENCIL_DESC ) );
	depthStencilDesc.DepthEnable = true;

	if( SUCCEEDED( m_pDevice->CreateDepthStencilState(
		&depthStencilDesc, &m_pDepthStencilState ) ) )
	{
		m_pDeviceContext->OMSetDepthStencilState(
			m_pDepthStencilState, 1 );
	}

	//�r���[�|�[�g�̐ݒ�.
	D3D11_VIEWPORT vp;
	vp.Width	= WND_W;//��.
	vp.Height	= WND_H;//����.
	vp.MinDepth	= 0.0f;	//�ŏ��[�x(��O).
	vp.MaxDepth	= 1.0f;	//�ő�[�x(��).
	vp.TopLeftX	= 0.0f;	//����ʒux.
	vp.TopLeftY	= 0.0f;	//����ʒuy.
	m_pDeviceContext->RSSetViewports( 1, &vp );

	//Sp2D�p.
	SetViewPort10( &vp );

	//���X�^���C�Y(�ʂ̓h��Ԃ���)�ݒ�.
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory( &rdc, sizeof( rdc ) );
	rdc.FillMode = D3D11_FILL_SOLID;	//�h��Ԃ�(�\���b�h).
	rdc.CullMode = D3D11_CULL_NONE;
					//D3D11_CULL_NONE :�J�����O��؂�(���w�ʂ�`�悷��).
					//D3D11_CULL_BACK :�w�ʂ�`�悵�Ȃ�.
					//D3D11_CULL_FRONT:���ʂ�`�悵�Ȃ�.
	rdc.FrontCounterClockwise	= FALSE;
								//�|���S���̕\�������肷��t���O.
								//TRUE :�����Ȃ�O����,�E���Ȃ������.
								//FALSE:���̋t�ɂȂ�.
	rdc.DepthClipEnable	= FALSE;	//�����ɂ��ẴN���b�s���O�L��.

	ID3D11RasterizerState* pIr	= nullptr;
	m_pDevice->CreateRasterizerState( &rdc, &pIr );
	m_pDeviceContext->RSSetState( pIr );
	SAFE_RELEASE( pIr );

	return S_OK;
}

//============================================================
//	Direct3D�I������.
//============================================================
void clsMain::DestroyD3D()
{
#if _DEBUG
	//�f�o�b�O�e�L�X�g.
	if( m_pText != nullptr ){
		delete m_pText;
		m_pText = nullptr;
	}

	if( m_pRayH != nullptr ){
		delete m_pRayH;
		m_pRayH = nullptr;
	}
	if( m_pRayFB != nullptr ){
		delete m_pRayFB;
		m_pRayFB = nullptr;
	}
	if( m_pRayV != nullptr ){
		delete m_pRayV;
		m_pRayV = nullptr;
	}



#endif //#if _DEBUG

#ifdef Tahara


	SAFE_DELETE( m_pGame );


#endif //#ifdef Tahara

	SAFE_RELEASE( m_pBackBuffer_DSTexDSV );
	SAFE_RELEASE( m_pBackBuffer_DSTex );
	SAFE_RELEASE( m_pBackBuffer_TexRTV );
	SAFE_RELEASE( m_pSwapChain );
	SAFE_RELEASE( m_pDeviceContext );
	SAFE_RELEASE( m_pDevice );
}



#if _DEBUG

////============================================================
//	�X�t�B�A�쐬.
////============================================================
HRESULT clsMain::InitSphere( clsDX9Mesh* pMesh, float fScale )
{
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;	//���_�o�b�t�@.
	void*	pVertices = nullptr;	//���_.
	D3DXVECTOR3	vCenter;		//���S.
	float	fRadius;			//���a.

	//���_�o�b�t�@���擾.
	if( FAILED( pMesh->m_pMesh->GetVertexBuffer( &pVB ) ) ){
		return E_FAIL;
	}

	//���b�V���̒��_�o�b�t�@�����b�N����.
	if( FAILED( pVB->Lock( 0, 0, &pVertices, 0 ) ) ){
		SAFE_RELEASE( pVB );
		return E_FAIL;
	}

	//���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����.
	D3DXComputeBoundingSphere(
		(D3DXVECTOR3*)pVertices,
		pMesh->m_pMesh->GetNumVertices(),	//���_�̐�.
		D3DXGetFVFVertexSize( pMesh->m_pMesh->GetFVF()),	//���_�̏��.
		&vCenter,	//(out)���S���W.
		&fRadius );	//(out)���a.

	//�A�����b�N.
	pVB->Unlock();
	SAFE_RELEASE( pVB );

	//���S�Ɣ��a���\���̂ɐݒ�.
	pMesh->m_Sphere.vCenter	= vCenter;
	pMesh->m_Sphere.fRadius	= fRadius * fScale;


	return S_OK;
}

////============================================================
//	�o�E���f�B���O�{�b�N�X�쐬.
////============================================================
HRESULT clsMain::InitBBox( clsDX9Mesh* pMesh )
{
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;
	VOID* pVertices = nullptr;
	D3DXVECTOR3 Max, Min;

	//���b�V���̒��_�o�b�t�@�����b�N����.
	if( FAILED( pMesh->m_pMesh->GetVertexBuffer( &pVB ) ) ){
		MessageBox( NULL, "���_�o�b�t�@�擾���s", "clsMain::InitBBox()", MB_OK );
		return E_FAIL;
	}
	if( FAILED( pVB->Lock( 0, 0, &pVertices, 0 ) ) ){
		MessageBox( NULL, "���_�o�b�t�@�̃��b�N�Ɏ��s", "clsMain::InitBBox()", MB_OK );
		return E_FAIL;
	}
	//���b�V�����̒��_�ʒu�̍ő�ƍŏ�����������.
	D3DXComputeBoundingBox(
		(D3DXVECTOR3*)pVertices,
		pMesh->m_pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(
			pMesh->m_pMesh->GetFVF() ),
			&Min, &Max );	//(out)�ŏ��A�ő咸�_.
	pVB->Unlock();			//�A�����b�N.
	SAFE_RELEASE( pVB );	//�g�p�ϒ��_�o�b�t�@�̉��.

	pMesh->m_BBox.vPosMax = Max;
	pMesh->m_BBox.vPosMin = Min;

	//���x�N�g��,���̒���(���̏ꍇ�{�b�N�X�̊e���a)������������.
	pMesh->m_BBox.fLengthX = ( Max.x - Min.x ) / 2.0f;
	pMesh->m_BBox.fLengthY = ( Max.y - Min.y ) / 2.0f;
	pMesh->m_BBox.fLengthZ = ( Max.z - Min.z ) / 2.0f;


	return S_OK;
}
#endif //#if _DEBUG



////============================================================
//	���b�V���ǂݍ��݊֐�(�܂Ƃ߂�).
////============================================================
HRESULT clsMain::ReadMesh()
{
	m_pGame = new clsGAME( m_hWnd, m_pDevice, m_pDeviceContext );
	m_pGame->Create();



#if _DEBUG


	//���C�\���̏�����(����).
	m_pRayV = new clsRay;
	m_pRayV->m_Ray.vPoint[0] = D3DXVECTOR3( 0.0f,-5.0f, 0.0f);
	m_pRayV->m_Ray.vPoint[1] = D3DXVECTOR3( 0.0f, 5.0f, 0.0f);
	m_pRayV->Init( m_pDevice, m_pDeviceContext );
	//���C�\���̏�����(�O��).
	m_pRayFB = new clsRay;
	m_pRayFB->m_Ray.vPoint[0] = D3DXVECTOR3( 0.0f, 0.0f,-5.0f);
	m_pRayFB->m_Ray.vPoint[1] = D3DXVECTOR3( 0.0f, 0.0f, 5.0f);
	m_pRayFB->Init( m_pDevice, m_pDeviceContext );
	//���C�\���̏�����(���E).
	if( m_pRayH == nullptr ){
		m_pRayH = new clsRay;
		int r = sizeof( clsRay );
		m_pRayH->m_Ray.vPoint[0] = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
		m_pRayH->m_Ray.vPoint[1] = D3DXVECTOR3( 5.0f, 0.0f, 0.0f);
		m_pRayH->Init( m_pDevice, m_pDeviceContext );
	}

	//�f�o�b�O�e�L�X�g�̏�����.
	m_pText = new clsDebugText;
	D3DXVECTOR4 vColor( 1.0f, 1.0f, 1.0f, 1.0f );
	if( FAILED( m_pText->Init(
		m_pDeviceContext,
		WND_W, WND_H, 50.0f,
		vColor ) ) )
	{
		MessageBox( NULL, "�f�o�b�O�e�L�X�g�쐬���s", "clsMain::Loop", MB_OK );
	}
#endif //#if _DEBUG

	return S_OK;
}



//============================================================
//	�[�x�e�X�g(Z�e�X�g)ON/OFF�ؑ�.
//============================================================
void clsMain::SetDepth( const bool bFlg )
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc,
		sizeof( D3D11_DEPTH_STENCIL_DESC ) );
	depthStencilDesc.DepthEnable = bFlg;

	m_pDevice->CreateDepthStencilState(
		&depthStencilDesc, &m_pDepthStencilState );
	m_pDeviceContext->OMSetDepthStencilState(
		m_pDepthStencilState, 1 );
}


#if _DEBUG
////============================================================
//	�Փ˔���֐�.
////============================================================
bool clsMain::Collision( clsDX9Mesh* pAttacker, clsDX9Mesh* pTarget)
{
	//2�̕��̂̒��S�Ԃ̋��������߂�.
	D3DXVECTOR3 vLength
		= pTarget->m_Trans.vPos - pAttacker->m_Trans.vPos;
	//�����ɕϊ�����.
	float Length = D3DXVec3Length( &vLength );

	//2���̊Ԃ̋������A2���̂̔��a�𑫂������̂��.
	//�������Ƃ������Ƃ́A�X�t�B�A���m���d�Ȃ��Ă���.
	//(�Փ˂��Ă���)�Ƃ�������.
	if( Length <=
		pAttacker->m_Sphere.fRadius + pTarget->m_Sphere.fRadius )
	{
		return true;//�Փ˂���.
	}
	return false;	//�Փ˂��Ă��Ȃ�.
}
//============================================================
//	�{�b�N�X�Փ˔���֐�.
//============================================================
bool clsMain::BBoxCollision( clsDX9Mesh* pAttacker, clsDX9Mesh* pTarget )
{
	//�U�����p��2�̒��_��p�ӂ�����������.
	D3DXVECTOR3 vecMaxAtk, vecMinAtk;	//�ő�A�ŏ����_.
	vecMaxAtk = pAttacker->m_BBox.vPosMax
				+ pAttacker->m_Trans.vPos;
	vecMinAtk = pAttacker->m_BBox.vPosMin
				+ pAttacker->m_Trans.vPos;

	//�ڕW���p��2�̒��_��p�ӂ�����������.
	D3DXVECTOR3 vecMaxTrg, vecMinTrg;	//�ő�A�ŏ����_.
	vecMaxTrg = pTarget->m_BBox.vPosMax
				+ pTarget->m_Trans.vPos;
	vecMinTrg = pTarget->m_BBox.vPosMin
				+ pTarget->m_Trans.vPos;

	//2�̕��̂��ꂼ��̍ő�A�ŏ��ʒu�Ƃ���,.
	//4�̏�񂪂���΁A�Փ˂����o�ł���.
	if( vecMinAtk.x < vecMaxTrg.x  &&  vecMaxAtk.x > vecMinTrg.x &&
		vecMinAtk.y < vecMaxTrg.y  &&  vecMaxAtk.y > vecMinTrg.y &&
		vecMinAtk.z < vecMaxTrg.z  &&  vecMaxAtk.z > vecMinTrg.z )
	{
		return true;//�Փ˂��Ă���.
	}

	return false;	//�Փ˂��Ă��Ȃ�.
}
#endif //#if _DEBUG


//============================================================
//	�{�[���̍��W���Ƃ�.
//============================================================
void clsMain::GetPosFromBone( clsD3DXSKINMESH* skinMesh, char BoneName[], D3DXVECTOR3& Pos )
{
	D3DXVECTOR3 vBonePos;
	if( skinMesh->GetPosFromBone( BoneName, &vBonePos ) ){
		Pos = vBonePos;
	}
}


//============================================================
//	�J�����֐�.
//============================================================
void clsMain::Camera()
{

////----------------------------.
////	�J�����Ǐ]������������.
////----------------------------.
////�J�����ʒu(���@�̔w������)�̈ʒu.
//m_Camera.vEye = m_Camera.vLook = m_pOldPlayer->m_vPos;
//m_Camera.fYaw = m_pOldPlayer->m_fYaw;
////Y����]�s��̍쐬.
//D3DXMatrixRotationY( &m_Camera.mRot, m_Camera.fYaw );
////���x�N�g��.
//D3DXVECTOR3 vecAxisZ( 0.0f, 0.0f, 1.0f );
////Z���x�N�g�����̂��̂���].
//D3DXVec3TransformCoord( &vecAxisZ, &vecAxisZ, &m_Camera.mRot );
//m_Camera.vEye	-= vecAxisZ * 4.0f;//���@�̔w����.
//m_Camera.vLook	+= vecAxisZ * 2.0f;//���@�̑O��.
//m_Camera.vEye.y		+= 2.0f;
//m_Camera.vLook.y	+= 0.2f;
////----------------------------.
////	�J�����Ǐ]���������܂�.
////----------------------------.


	//�r���[(�J����)�ϊ�.
	D3DXVECTOR3 vUpVec	( 0.0f, 1.0f, 0.0f );	//����ʒu.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)�r���[�v�Z����.
		&m_pGame->GetCameraPos(), &m_pGame->GetCameraLookPos(), &vUpVec );

}
//============================================================
//	�v���W�F�N�V�����֐�.
//============================================================
void clsMain::Proj()
{
	//�v���W�F�N�V����(�ˉe�s��)�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,			//(out)�v���W�F�N�V�����v�Z����.
		fZOOM,	//y�����̎���(���W�A���w��)������傫�������王�삪�����Ȃ�.
		(FLOAT)WND_W / (FLOAT)WND_H,//�A�X�y�N�g��(��/����).
		0.1f,				//�߂��r���[���ʂ�z�l.
		fRENDER_LIMIT );	//�����r���[���ʂ�z�l.100.f

}














//==========

void clsMain::RenderDebugText()
{
#if _DEBUG

	//NULL�`�F�b�N.
	if ( m_pText != nullptr ){
		char strDbgTxt[256];
		int dbgtxty = 0;
		int dbgTxtx = 20;



		sprintf_s( strDbgTxt, 
			"CameraPos : x[%f], y[%f], z[%f]",
			m_pGame->GetCameraPos().x, m_pGame->GetCameraPos().y, m_pGame->GetCameraPos().z );
		m_pText->Render(strDbgTxt, 0, dbgtxty);
		dbgtxty += 10;

		sprintf_s( strDbgTxt, 
			"CamLokPos : x[%f], y[%f], z[%f]",
			m_pGame->GetCameraLookPos().x, m_pGame->GetCameraLookPos().y, m_pGame->GetCameraLookPos().z );
		m_pText->Render(strDbgTxt, 0, dbgtxty);
		dbgtxty += 10;

//		sprintf_s( strDbgTxt, 
//			"CharacPos : x[%f], y[%f], z[%f]",
//			m_pTestChara->GetPositionX(), m_pTestChara->GetPositionY(), m_pTestChara->GetPositionZ() );
//		m_pText->Render(strDbgTxt, 0, dbgtxty);
//		dbgtxty += 10;



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

}




#ifdef Tahara
//ConvDimPos�̎��O����.
void clsMain::SetViewPort10( D3D11_VIEWPORT* Vp )
{
	m_ViewPort.TopLeftX = static_cast<INT>(Vp->TopLeftX);
	m_ViewPort.TopLeftY = static_cast<INT>(Vp->TopLeftY);
	m_ViewPort.MaxDepth = Vp->MaxDepth;
	m_ViewPort.MinDepth = Vp->MinDepth;
	m_ViewPort.Width	= static_cast<UINT>(Vp->Width);
	m_ViewPort.Height	= static_cast<UINT>(Vp->Height);
};

//3D���W�̃X�N���[��( 2D )���W�ϊ�.dimensions(����) conversion(�ϊ�)
D3DXVECTOR3 clsMain::ConvDimPos( D3DXVECTOR3 v2DPos, D3DXVECTOR3 v3DPos )
{
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity( &mWorld );
	D3DXVec3Project( &v2DPos, &v3DPos, &m_ViewPort, &m_mProj, &m_mView, &mWorld );
	return v2DPos;
}
#endif//#ifdef Tahara
