//#define CAN_CHECK_STRING_BYTE_TYPE//�����̉p�����A���{�ꕶ����1�o�C�g�ځA2�o�C�g�ڂ̔��肪�ł���Ȃ����.

#include "CFont.h"

#include "File.h"

#include <assert.h>



using namespace std;

//�t�H���g�̃p�X.
const char* sFONT_STYLE_PATH = "Data\\Font\\FontType\\Makinas-Scrap-5.otf";//Makinas-Scrap-5.otf.//aozora.ttf.

//#define sFONT_NAME "�������疾�� Medium"
#define sFONT_NAME "�}�L�i�X Scrap 5"

#define FONT_SHADER		"Shader\\FontText.hlsl"


const float fPOS_Z = 0.01f;

clsFont::clsFont( 
	ID3D11Device* const pDevice, 
	ID3D11DeviceContext* const pContext )
	:m_pDevice( pDevice )
	,m_pContext( pContext )
	,m_pVertexShader( nullptr )
	,m_pVertexLayout( nullptr )
	,m_pPixelShader( nullptr )
	,m_pVertexBuffer( nullptr )
	,m_pSampleLinear( nullptr )
	,m_pConstantBuffer( nullptr )
	,m_vpTex2D()
	,m_vvpAsciiTexture()
//	,m_pBlendState()
	,m_sTextData()
	,m_fAlpha( 1.0f )
	,m_vColor( { 1.0f, 1.0f, 1.0f, 1.0f } )
	,m_Design()
	,m_iTextRow( 0 )
{
	for( unsigned char i=0; i<enBLEND_STATE_size; i++ ){
		m_pBlendState[i] = nullptr;
	}


	if( !AddFontResourceEx(
		sFONT_STYLE_PATH,
		FR_PRIVATE,
		&m_Design ) )
	{
		ERR_MSG("�t�H���g���s", "Error");
	}

	m_Rect = {  WND_W / 8,//left.
				WND_H / 2,//top.
				WND_W / 3 + WND_W / 2,//right.
				WND_H / 4 + WND_H / 2 //bottom.
	};    

	if( FAILED( CreateBlendState() ) ){
		assert( !"Can't Blend State" );
	}


	LoadFont();

	//�O�����󂯓n��.
//	m_vPos = D3DXVECTOR3( 0.0f, m_iFontSize, 0.01f );
	m_vPos = D3DXVECTOR3( 0.0f, 0.0f, fPOS_Z );
	m_fScale = static_cast<float>( m_iFontSize );

	if( FAILED( CreateShader() ) ){
		assert( !"Can't Create Shader" );
	}
	if( FAILED( CreateVertexBuffer() ) ){
		assert( !"Can't Create VertexBuffer" );
	}
	if( FAILED( CreateConstantBuffer() ) ){
		assert( !"Can't Create ConstantBuffer" );
	}

}

clsFont::~clsFont()
{
	Release();

	SAFE_RELEASE( m_pConstantBuffer );
	SAFE_RELEASE( m_pSampleLinear );
	SAFE_RELEASE( m_pVertexBuffer );
	SAFE_RELEASE( m_pPixelShader ) ;
	SAFE_RELEASE( m_pVertexLayout );
	SAFE_RELEASE( m_pVertexShader );

	for( unsigned char i=0; i<enBLEND_STATE_size; i++ ){
		SAFE_RELEASE( m_pBlendState[i] );
	}

	//���\�[�X�폜.
	if( !RemoveFontResourceEx(
		sFONT_STYLE_PATH,
		FR_PRIVATE,
		&m_Design ) )
	{
		assert( !"�t�H���g���\�[�X������s" );
	}

	m_pContext = nullptr;
	m_pDevice = nullptr;
}

//�u�����h�X�e�[�g�쐬.
HRESULT clsFont::CreateBlendState()
{
	//�A���t�@�u�����h�p�u�����h�X�e�[�g�쐬.
	//png�t�@�C�����ɃA���t�@��񂪂���̂ŁA���߂���悤�Ƀu�����h�X�e�[�g�Őݒ肷��.
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof( D3D11_BLEND_DESC ) );	//������.
	blendDesc.IndependentBlendEnable = false;			//false:RenderTarget[0]�̃����o�[�̂ݎg�p����Btrue:RenderTarget[0�`7]���g�p�ł���(�����_�[�^�[�Q�b�g���ɓƗ������u�����h����).
	blendDesc.AlphaToCoverageEnable = false;			//true:�A���t�@�g�D�J�o���b�W���g�p����.

	//�\���^�C�v
//	blendDesc.RenderTarget[0].BlendEnable = true;					//true:�A���t�@�u�����h���g�p����.
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;		//�A���t�@�u�����h���w��.
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;//�A���t�@�u�����h�̔��]���w��.
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;			//ADD�F���Z����.
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;		//���̂܂܎g�p.
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;		//�������Ȃ�.
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;	//ADD�F���Z����.
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;//�S�Ă̐���(RGBA)�ւ̃f�[�^�̊i�[��������.

	bool tmpBlendEnable[ enBLEND_STATE_size ];
	tmpBlendEnable[ enBLEND_STATE_ALPHA_ON ] = true;
	tmpBlendEnable[ enBLEND_STATE_ALPHA_OFF ] = false;

	for( unsigned char i=0; i<enBLEND_STATE_size; i++ )
	{
		blendDesc.RenderTarget[0].BlendEnable = tmpBlendEnable[i];
		if( FAILED( m_pDevice->CreateBlendState( &blendDesc, &m_pBlendState[i] ) ) ){
			assert( !"�u�����h�X�e�[�g�̍쐬�Ɏ��s" );
			return E_FAIL;
		}
	}

	return S_OK;
}

//�t�H���g���Ǎ�.
bool clsFont::LoadFont()
{
	m_iFontSize = 32;//22;
	m_iFontMarginX = 4;//5;
	m_iFontMarginY = 4;//5;
	m_strFont.iFontDispSpeed = 2;
	m_strFont.iFontAutoFlg = 120;

	return true;
}

//�V�F�[�_�̍쐬.
HRESULT clsFont::CreateShader()
{
	ID3DBlob *pCompileShader = NULL;
	ID3DBlob *pErrors = NULL;

	char strDir[512];
	GetCurrentDirectory( sizeof( strDir ), strDir );


	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬.
	if( FAILED(D3DX11CompileFromFile(
		FONT_SHADER, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL,
		&pCompileShader, &pErrors, NULL ) ) )
	{
		assert( "�u���u�쐬���s(VS)" );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//Vertex Shader�̍쐬.
	if( FAILED( m_pDevice->CreateVertexShader(
		(pCompileShader)->GetBufferPointer(),
		(pCompileShader)->GetBufferSize(),
		NULL, &m_pVertexShader ) ) )	//(out)���_�V�F�[�_�[.
	{
		assert( "Vertex Shader�쐬���s(VS)" );
		return E_FAIL;
	}

	//���_�C���v�b�g���C�A�E�g���`.
	D3D11_INPUT_ELEMENT_DESC layout_Ita[] =
	{
		{ 
			"POSITION",							//�ʒu.
			0, DXGI_FORMAT_R32G32B32_FLOAT,		//DXGI�̃t�H�[�}�b�g32bitfloat�^.
			0,
			0,									//�f�[�^�̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0 
		},
		{ 
			"TEXCOORD",							//�e�N�X�`���ʒu.
			0, DXGI_FORMAT_R32G32_FLOAT,
			0,
			12,									//�e�N�X�`���f�[�^�̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0 
		},
	};
	UINT numElements_Ita = sizeof( layout_Ita ) / sizeof( layout_Ita[0] );

	//���_�C���v�b�g���C�A�E�g�쐬.
	if( FAILED( m_pDevice->CreateInputLayout(layout_Ita,
		numElements_Ita, pCompileShader->GetBufferPointer(),	//(out)���_�C���v�b�g���C�A�E�g.
		pCompileShader->GetBufferSize(), &m_pVertexLayout ) ) )
	{
		assert( "���_�C���v�b�g���C�A�E�g�̍쐬���s" );
		return FALSE;
	}

	//�u���u����s�N�Z���V�F�[�_�[�쐬.
	if( FAILED( D3DX11CompileFromFile(
		FONT_SHADER, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL,
		&pCompileShader, &pErrors, NULL ) ) )
	{
		assert( "�u���u�쐬���s(PS)" );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//Pixel Shader�̍쐬.
	if( FAILED( m_pDevice->CreatePixelShader(
		(pCompileShader)->GetBufferPointer(),
		(pCompileShader)->GetBufferSize(), NULL, &m_pPixelShader ) ) )	//(out)���_.
	{
		assert( "�s�N�Z���V�F�[�_�[�쐬���s" );
		return E_FAIL;
	}

	SAFE_RELEASE( pCompileShader );	//�u���u���.



	return S_OK;
}

//�o�[�e�b�N�X�o�b�t�@�̍쐬.
HRESULT clsFont::CreateVertexBuffer()
{
	// Create VB.
	//�o�[�e�b�N�X�o�b�t�@�[�쐬.
	FONT_VERTEX vertices[4];

	FONT_VERTEX vertices2[] =
	{
		//���_���W�i���A���A���j�@�@�@�@UV���W�iu,v�j.
		D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), D3DXVECTOR2( 0.0f, 1.0f ),	//���_�P.
		D3DXVECTOR3( 0.0f,-1.0f, 0.0f ), D3DXVECTOR2( 0.0f, 0.0f ),	//���_�Q.
		D3DXVECTOR3( 1.0f, 1.0f, 0.0f ), D3DXVECTOR2( 1.0f, 1.0f ),	//���_�R.
		D3DXVECTOR3( 1.0f,-1.0f, 0.0f ), D3DXVECTOR2( 1.0f, 0.0f ),	//���_�S.
	};
	vertices[0] = vertices2[0];
	vertices[1] = vertices2[1];
	vertices[2] = vertices2[2];
	vertices[3] = vertices2[3];


	D3D11_BUFFER_DESC bd;					//�o�b�t�@�̍\����.
	bd.Usage = D3D11_USAGE_DEFAULT;			//�g�p���@.
	bd.ByteWidth = sizeof( FONT_VERTEX ) * 4;//���_�̃T�C�Y�i���_*�R�j.
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���_�o�b�t�@�Ƃ��Ĉ���.
	bd.CPUAccessFlags = 0;					//CPU����̓A�N�Z�X���Ȃ�.
	bd.MiscFlags = 0;						//���̑��̐ݒ�Ȃ�.

	//�T�u���\�[�X�f�[�^�\����.
	D3D11_SUBRESOURCE_DATA InitDate;
	InitDate.pSysMem = vertices;		//�O�p�`�̒��_�����Z�b�g.
	//���_�o�b�t�@�̍쐬.
	if( FAILED( m_pDevice->CreateBuffer( &bd, &InitDate, &m_pVertexBuffer ) ) )
	{
		ERR_MSG("���_�o�b�t�@(m_pItaVB)�̍쐬�Ɏ��s", "InitPolygon");
		return E_FAIL;
	}

	//���_�o�b�t�@���Z�b�g.
	UINT stride = sizeof(FONT_VERTEX);	//���_�Ԃ̃T�C�Y.
	UINT offset = 0;					//�I�t�Z�b�g�l.
	m_pContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

	//�e�N�X�`���p�T���v���[�쐬.
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory( &SamDesc, sizeof( D3D11_SAMPLER_DESC ) );
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	//���j�A�t�B���^�[�i���`��ԁj.
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;		//���b�s���O���[�h�iWRAP�F�J��Ԃ�).
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	m_pDevice->CreateSamplerState( &SamDesc, &m_pSampleLinear );	//�iout)�T���v���[.

	return S_OK;
}

//�萔�o�b�t�@�̍쐬.
HRESULT clsFont::CreateConstantBuffer()
{
	//�R���X�^���g�o�b�t�@�쐬(�|���p).
	D3D11_BUFFER_DESC ItaBD;
	ItaBD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//�R���X�^���X�g�o�b�t�@���w��.
	ItaBD.ByteWidth = sizeof( FONTSHADER_CONSTANT_BUFFER );	//�R���X�^���X�g�o�b�t�@�̃T�C�Y.
	ItaBD.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;			//�������݂ŃA�N�Z�X.
	ItaBD.MiscFlags = 0;
	ItaBD.StructureByteStride = 0;
	ItaBD.Usage = D3D11_USAGE_DYNAMIC;					//�g�p�@�F���ڏ�������.

	//�R���X�^���X�g�o�b�t�@�쐬.
	if( FAILED( m_pDevice->CreateBuffer(
		&ItaBD, NULL, &m_pConstantBuffer ) ) )
	{
		ERR_MSG("�R���X�^���g�o�b�t�@(Ita)�̍쐬�Ɏ��s", "InitShader");
		return E_FAIL;
	}


	return S_OK;
}

//�t�@�C���ǂݍ���.
HRESULT clsFont::LoadTextFile( const char *sTextFileName )
{
	//�t�@�C���|�C���^.
	clsFILE File;

	if( !File.Open( sTextFileName ) ){
		return E_FAIL;
	}


	//������.
	//�s��.
	m_iTextRow = File.GetSizeRow();
	m_sTextData.resize( m_iTextRow );
	m_vpTex2D.resize( m_iTextRow, nullptr );
	m_vvpAsciiTexture.resize( m_iTextRow );

	for( unsigned int i=0; i<File.GetSizeRow(); i++ )
	{
		const int iCol = File.GetDataString( i, 0 ).size();//������̒���.
		//��s���R�s�[.
		m_sTextData[i] = File.GetDataString( i, 0 );
#ifndef CAN_CHECK_STRING_BYTE_TYPE
		m_vvpAsciiTexture[i].resize( iCol, nullptr );
#else//#ifndef CAN_CHECK_STRING_BYTE_TYPE
		m_vvpAsciiTexture[i].reserve( m_sTextData[i].size() );

		const int iNullPlus = 1;//�k�������̕�.
		for( unsigned int j=0; j<m_sTextData[i].size()-iNullPlus; j++ )
		{
			if( IsDBCSLeadByte( m_sTextData[i][j] ) ){
				m_vvpAsciiTexture[i].push_back( nullptr );
			}
		}
		m_vvpAsciiTexture[i].shrink_to_fit();
#endif//#ifndef CAN_CHECK_STRING_BYTE_TYPE
	}

//	if( IsDBCSLeadByte( m_sTextData[iTex][i] ) )


	//�t�@�C���̃N���[�Y.
	File.Close();

	return S_OK;
}

//�e�N�X�`���쐬.
HRESULT clsFont::CreateTexture()
{
	//fontCreate.
	LOGFONT lf = {
		m_iFontSize, 0, 0, 0, 
		0, 0, 0, 0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FIXED_PITCH | FF_ROMAN,
		TEXT( sFONT_NAME )
	};

	for( int iTex=0; iTex<m_iTextRow; iTex++ )
	{
		HFONT hFont = CreateFontIndirect( &lf );
		if( !hFont )
		{
			ERR_MSG("�t�H���g�쐬�s��", "Error");
			return E_FAIL;
		}

		HDC hdc = GetDC( NULL );

		HFONT oldFont = (HFONT)SelectObject( hdc, hFont );

		int iByteMax = strlen( m_sTextData[ iTex ].c_str() );

		for( int i=0; i<iByteMax; i++ )
		{
			if( IsDBCSLeadByte( m_sTextData[ iTex ][i] ) ){
				i++;
			}
		}

		UINT code;
		int iCharCnt = 0;//������J�E���g.
		for( int i=0; i<iByteMax; i++ )
		{
			//�����R�[�h�擾.
			if( IsDBCSLeadByte( m_sTextData[ iTex ][i] ) )
			{
				code = (BYTE)m_sTextData[ iTex ][i] << 8 | (BYTE)m_sTextData[ iTex ][ i + 1 ];
			}
			else{
				code = m_sTextData[ iTex ][i];
			}
			//�t�H���g�r�b�g�}�b�v�擾.
			TEXTMETRIC TM;
			GetTextMetrics( hdc, &TM );
			GLYPHMETRICS GM;
			const int grad = GGO_GRAY4_BITMAP;

			CONST MAT2 Mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
			DWORD size = GetGlyphOutline( hdc, code, grad, &GM, 0, NULL, &Mat );
			BYTE* ptr = new BYTE[ size ];
			GetGlyphOutline( hdc, code, grad, &GM, size, ptr, &Mat );

			//----- �������݉\�e�N�X�`���쐬 -----//.

			//CPU�ŏ������݂��ł���e�N�X�`���쐬.
			//�e�N�X�`���쐬.
			D3D11_TEXTURE2D_DESC desc;
			memset( &desc, 0, sizeof( desc ) );
			desc.Width = GM.gmCellIncX;
			desc.Height = TM.tmHeight;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			if( FAILED( m_pDevice->CreateTexture2D( &desc, 0, &m_vpTex2D[ iTex ] ) ) )
			{
				MessageBox( 0, "�e�N�X�`���쐬���s", "CreateTexture", MB_OK );
				return E_FAIL;
			}

			D3D11_MAPPED_SUBRESOURCE hMappedResource;
			if( FAILED
				( m_pContext->Map(
				m_vpTex2D[ iTex ],
				0,
				D3D11_MAP_WRITE_DISCARD,
				0,
				&hMappedResource ) ) )
			{
				MessageBox(NULL, "�e�N�X�`���쐬���s",
					"CreateTex::->Map", MB_OK);
				return E_FAIL;
			}
			// �����ŏ�������.
			BYTE* pBits = (BYTE*)hMappedResource.pData;

			// �t�H���g���̏�������.
			// iOfs_x, iOfs_y : �����o���ʒu(����).
			// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���.
			// Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K).
			int iOfs_x = GM.gmptGlyphOrigin.x;
			int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
			int iBmp_w = GM.gmBlackBoxX + ( 4 - ( GM.gmBlackBoxX % 4 ) ) % 4;
			int iBmp_h = GM.gmBlackBoxY;
			int Level = 17;
			int x, y;

			DWORD Alpha, Color;
			memset( pBits, 0, hMappedResource.RowPitch * TM.tmHeight );
			for( y=iOfs_y; y<iOfs_y+iBmp_h; y++ )
			{
				for( x=iOfs_x; x<iOfs_x+iBmp_w; x++ )
				{
					Alpha = ( 255 * ptr[ x - iOfs_x + iBmp_w * ( y - iOfs_y ) ] ) / ( Level - 1 );
					Color = 0x00ffffff | ( Alpha << 24 );

					memcpy( (BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, &Color, sizeof( DWORD ) );
				}
			}

			m_pContext->Unmap( m_vpTex2D[ iTex ], 0 );

			//�e�N�X�`�������擾����.
			D3D11_TEXTURE2D_DESC texDesc;
			m_vpTex2D[ iTex ]->GetDesc( &texDesc );

			//ShaderResourceView�̏����쐬����.
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			ZeroMemory( &srvDesc, sizeof( srvDesc ) );
			srvDesc.Format = texDesc.Format;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

			if( FAILED( m_pDevice->CreateShaderResourceView(
				m_vpTex2D[ iTex ], &srvDesc, &m_vvpAsciiTexture[ iTex ][ iCharCnt ] ) ) )
			{
				assert( !"�e�N�X�`���쐬���s" );
				return E_FAIL;
			}

			//�����R�[�h�擾.
			if( IsDBCSLeadByte( m_sTextData[ iTex ][i] ) )
			{
				i++;
			}
			iCharCnt++;//����.
			delete[] ptr;
			ptr = nullptr;
		}
		//�f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̉��.
		SelectObject( hdc, oldFont );
		DeleteObject( hFont );
		ReleaseDC( NULL, hdc );
	}
	return S_OK;
}

void clsFont::Create( const char *sTextFileName )
{
	if( FAILED( LoadTextFile( sTextFileName ) ) ){
		assert( !"Can't Load Text File" );
	}

	if( FAILED( CreateTexture() ) ){
		assert( !"Can't Create Texture" );
	}
}

void clsFont::Release()
{
	m_sTextData.clear();
	m_sTextData.shrink_to_fit();

	for( unsigned int iTex=0; iTex<m_vvpAsciiTexture.size(); iTex++ )
	{
		for( unsigned int i=0; i<m_vvpAsciiTexture[ iTex ].size(); i++ )
		{
//			SAFE_DELETE(m_pAsciiTexture[ iTex ][i]);
			if( !m_vvpAsciiTexture[ iTex ][i] ) continue;
			m_vvpAsciiTexture[ iTex ][i]->Release();
			m_vvpAsciiTexture[ iTex ][i] = nullptr;
		}
		m_vvpAsciiTexture[ iTex ].clear();
		m_vvpAsciiTexture[ iTex ].shrink_to_fit();
	}
	m_vvpAsciiTexture.clear();
	m_vvpAsciiTexture.shrink_to_fit();

	for( unsigned int iTex=0; iTex<m_vpTex2D.size(); iTex++ ){
//		SAFE_DELETE(m_pTex2D[ iTex ]);
		if( !m_vpTex2D[ iTex ] ) continue;
		m_vpTex2D[ iTex ]->Release();
		m_vpTex2D[ iTex ] = nullptr;
	}
	m_vpTex2D.clear();
	m_vpTex2D.shrink_to_fit();
}


//							���i( ���s��? )	�@		��������.
void clsFont::Render( const int iTex, const int iCharNum )
{
	if( iTex <= -1 ) return;
	if( iTex >= static_cast<int>( m_vvpAsciiTexture.size() ) ) return;
	if( iCharNum <= -1 ) return;

	//�g�p����V�F�[�_�[�̓o�^.
	m_pContext->VSSetShader( m_pVertexShader,	NULL, 0 );
	m_pContext->PSSetShader( m_pPixelShader,	NULL, 0 );
	m_pContext->GSSetShader( NULL,				NULL, 0 );

	//������̍�������W�̈ʒu�Ɏ����Ă��邽�߂ɕK�v.
	const D3DXVECTOR3 vOFFSET_POS = { -m_fScale, m_fScale * 0.5f, 0.0f };
	D3DXVECTOR3 vPos = m_vPos + vOFFSET_POS;

	int ii = 0;
	int iCnt = 0;

//	for ( int i = 0; i<iCharNum; i++ )
	for ( int i = 0; i<m_vvpAsciiTexture[ iTex ].size(); i++ )
	{
		if( static_cast<unsigned int>( i ) >= m_vvpAsciiTexture[ iTex ].size() ){
			break;
		}
#if 0
		if( vPos.x + m_iFontSize + ( m_fScale + m_fFontMarginX ) * iCnt <= 
			m_Rect.right )
		{
			//�w��͈͂̒�.
			iCnt++;
		}
		else{
			//�͈͎w��O�A��i���炷.
			ii++;
			iCnt = 1;
		}
#else
		//����ɉ��s���Ȃ�.
		iCnt++;
#endif
		//���[���h�ϊ�.
		D3DXMATRIX mWorld, mScale, mTran;		//���[���h�s��.
		D3DXMatrixIdentity( &mWorld );
		D3DXMatrixTranslation( &mTran, 
			vPos.x + ( m_fScale + m_iFontMarginX ) * iCnt,
			vPos.y + ( m_fScale + m_iFontMarginY ) * ii * 2,
			vPos.z );

		D3DXMatrixScaling( &mScale, m_fScale, m_fScale, 1.0f );
		mWorld = mScale * mTran;


		//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��.
		D3D11_MAPPED_SUBRESOURCE	pData;
		FONTSHADER_CONSTANT_BUFFER	cb;
		if( SUCCEEDED( m_pContext->Map(
			m_pConstantBuffer, 0,
			D3D11_MAP_WRITE_DISCARD,
			0, &pData ) ) )
		{
			//���[���h�s���n��.
			cb.mW = mWorld;
			D3DXMatrixTranspose( &cb.mW, &cb.mW );
			cb.ViewPortWidth = WND_W;
			cb.ViewPortHeight = WND_H;


			cb.Uv = { 0.0f, 0.0f };

			cb.Color = m_vColor;
			//�����x��n��.
			cb.Alpha = m_fAlpha;

			memcpy_s( pData.pData, pData.RowPitch, (void*)( &cb ), sizeof( cb ) );
			m_pContext->Unmap( m_pConstantBuffer, 0 );
		}

		//���̃R���X�^���g�o�b�t�@���g���V�F�[�_�[�̓o�^.
		m_pContext->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );
		m_pContext->PSSetConstantBuffers( 0, 1, &m_pConstantBuffer );

		//�o�[�e�b�N�X�o�b�t�@���Z�b�g.
		UINT stride = sizeof( FONT_VERTEX );
		UINT offset = 0;
		m_pContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

		//�g�|���W�[.
		m_pContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
		//���_�C���v�b�g���C�A�E�g���Z�b�g.
		m_pContext->IASetInputLayout(m_pVertexLayout);

		//�e�N�X�`�����V�F�[�_�[�ɓn��.
		m_pContext->PSSetSamplers( 0, 1, &m_pSampleLinear );
		m_pContext->PSSetShaderResources( 0, 1, &m_vvpAsciiTexture[ iTex ][i] );

		//�A���t�@�u�����h�p�u�����h�X�e�[�g�쐬.
		SetBlend( true );

		//�`��.
		m_pContext->Draw( 4, 0 );
	}
}



void clsFont::SetPos( const D3DXVECTOR3 &vPos )
{
	m_vPos = vPos;
	m_vPos.z += fPOS_Z;
}

D3DXVECTOR3 clsFont::GetPos()
{
	return m_vPos;
}

void clsFont::SetScale( const float fScale )
{
	m_fScale = fScale;
}

float clsFont::GetScale()
{
	return m_fScale;
}
	 
void clsFont::SetColor( const D3DXVECTOR4 &vColor )
{
	const float fNOT_ALPHA = 1.0f;
	m_vColor = vColor;
	m_vColor.w = fNOT_ALPHA;
}

void clsFont::SetAlpha( const float fAlpha )
{
	m_fAlpha = fAlpha;
}

void clsFont::SetBlend( const bool isAlpha )
{
	UINT mask = 0xffffffff;	//�}�X�N�l��.

	if( isAlpha ){		
		//�u�����h�X�e�[�g�̐ݒ�.
		m_pContext->OMSetBlendState( m_pBlendState[ enBLEND_STATE_ALPHA_ON ], NULL, mask );
	}
	else{
		m_pContext->OMSetBlendState( m_pBlendState[ enBLEND_STATE_ALPHA_OFF ], NULL, mask );
	}
}

