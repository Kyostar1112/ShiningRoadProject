#include "Resource.h"

clsResource::clsResource()
{
	m_hWnd = nullptr;
	m_pDevice11 = nullptr;
	m_pCotext11 = nullptr;
	m_ppStaticModels = nullptr;
	m_ppSkinModels = nullptr;
	ZeroMemory( m_FilePath, sizeof( m_FilePath ) );
}

clsResource::~clsResource()
{
	for( UCHAR i=0; i<enStaticModel_Max; i++ ){
		ReleaseStaticModel( static_cast<enSTATIC_MODEL>( i ) );
	}
	for (UCHAR i = 0; i<enSkinModel_Max; i++){
		ReleaseSkinModel( static_cast<enSKIN_MODEL>( i ) );
	}
	//�X�L�����b�V���̃|�C���^�̈�����.
	if( m_ppSkinModels ){
		delete[] m_ppSkinModels;
		m_ppSkinModels = nullptr;
	}
	//�X�^�e�B�b�N���b�V���̃|�C���^�̈�����.
	if( m_ppStaticModels ){
		delete[] m_ppStaticModels;
		m_ppStaticModels = nullptr;
	}


	m_pCotext11 = nullptr;
	m_pDevice11 = nullptr;
	m_hWnd = nullptr;
}


//new����Ɏg��.
void clsResource::Create( const HWND hWnd, ID3D11Device* const pDevice, ID3D11DeviceContext* const pContext )
{
	InitStaticModel( hWnd, pDevice, pContext );
	InitSkinModel( hWnd, pDevice, pContext );

	CreateStaticModel( 
		"Data\\Stage\\yuka.x", 
		clsResource::enSTATIC_MODEL::enStaticModel_Ground );
	CreateStaticModel(
		"Data\\Trap\\Spia.x", 
		clsResource::enSTATIC_MODEL::enStaticModel_Enemy );

	CreateSkinModel(
		"Data\\hime\\hime_run.x", 
		clsResource::enSKIN_MODEL::enSkinModel_Player );
}


//==================================================.
//	������.
//==================================================.
HRESULT clsResource::InitStaticModel( 
			const HWND hWnd,
			ID3D11Device* const pDevice,
			ID3D11DeviceContext* const pContext)
{
	m_hWnd = hWnd;
	m_pDevice11 = pDevice;
	m_pCotext11 = pContext;
	//�X�^�e�B�b�N���b�V���̃|�C���^�̈���m��.
	m_ppStaticModels = new clsDX9Mesh*[ enStaticModel_Max ];
	for( int i=0; i<enStaticModel_Max; i++ ){
		m_ppStaticModels[i] = nullptr;
	}

	return S_OK;
}
HRESULT clsResource::InitSkinModel( 
			const HWND hWnd,
			ID3D11Device* const pDevice,
			ID3D11DeviceContext* const pContext)
{
	m_Si.hWnd = hWnd;
	m_Si.pDevice = pDevice;
	m_Si.pDeviceContext = pContext;
	//�X�L�����b�V���̃|�C���^�̈���m��.
	m_ppSkinModels = new clsD3DXSKINMESH*[enSkinModel_Max];
	for (int i = 0; i<enSkinModel_Max; i++){
		m_ppSkinModels[i] = nullptr;
	}

	return S_OK;
}



//==================================================.
//	���f���Ǎ�.
//==================================================.
// Static Model.
HRESULT clsResource::CreateStaticModel( LPSTR const fileName, const enSTATIC_MODEL enModel )
{
	//�񋓑͈͓̂̔�?.
	if( !IsRangeStaticModel( enModel ) ){
		return E_FAIL;
	}
	//���Ƀf�[�^�����邩.
	if( m_ppStaticModels[ enModel ] != nullptr ){
		return E_FAIL;
	}

	//���f���Ǎ�.
	m_ppStaticModels[ enModel ] = new clsDX9Mesh;
	m_ppStaticModels[ enModel ]->Init(
		m_hWnd, m_pDevice11, m_pCotext11, fileName );

	return S_OK;
}
//	Skin Model.
HRESULT clsResource::CreateSkinModel( LPSTR const fileName, const enSKIN_MODEL enModel )
{
	//�񋓑͈͓̂̔���.
	if ( !IsRangeSkinModel( enModel ) ){
		return E_FAIL;
	}

	//���Ƀf�[�^�����邩.
	if ( m_ppSkinModels[ enModel ] != nullptr ){
		return E_FAIL;
	}

	//���f���Ǎ�.
	m_ppSkinModels[ enModel ] = new clsD3DXSKINMESH;
	m_ppSkinModels[ enModel ]->Init( &m_Si );
	m_ppSkinModels[ enModel ]->CreateFromX( fileName );

	return S_OK;
}

//==================================================.
//	���f���̃|�C���^�擾.
//==================================================.
//	Static Model.
clsDX9Mesh* clsResource::GetStaticModels( const enSTATIC_MODEL enModel ) const
{
	//�񋓑͈͓̂̔�?.
	if( !IsRangeStaticModel( enModel ) ){
		return nullptr;
	}
	//���Ƀf�[�^�����邩.
	if( m_ppStaticModels[ enModel ] == nullptr ){
		return nullptr;
	}
	
	//���f���̃|�C���^�Ԃ�.
	return m_ppStaticModels[ enModel ];
}
//	Skin Model.
clsD3DXSKINMESH* clsResource::GetSkinModels( const enSKIN_MODEL enModel) const
{
	//�񋓑͈͓̂̔�?.
	if ( !IsRangeSkinModel( enModel ) ){
		return nullptr;
	}

	//���Ƀf�[�^�����邩.
	if ( m_ppSkinModels[ enModel ] == nullptr ){
		return nullptr;
	}

	//���f���̃|�C���^�Ԃ�.
	return m_ppSkinModels[ enModel ];
}


//==================================================.
//	���.
//==================================================.
//	Static Model.
HRESULT clsResource::ReleaseStaticModel( const enSTATIC_MODEL enModel )
{
	//�񋓑͈͓̂̔�?.
	if( !IsRangeStaticModel( enModel ) ){
		return E_FAIL;
	}
	//���Ƀf�[�^�����邩.
	if( m_ppStaticModels[ enModel ] == nullptr ){
		return E_FAIL;
	}

	delete m_ppStaticModels[ enModel ];
	m_ppStaticModels[ enModel ] = nullptr;

	return S_OK;
}
//	Skin Model.
HRESULT clsResource::ReleaseSkinModel( const enSKIN_MODEL enModel )
{
	//�񋓑͈͓̂̔�?.
	if( !IsRangeSkinModel( enModel ) ){
		return E_FAIL;
	}
	//���Ƀf�[�^�����邩.
	if( m_ppSkinModels[ enModel ] == nullptr ){
		return E_FAIL;
	}

	delete m_ppSkinModels[ enModel ];
	m_ppSkinModels[ enModel ] = nullptr;

	return S_OK;
}


//==================================================.
//	�͈͓����`�F�b�N����֐�.
//==================================================.
bool clsResource::IsRangeStaticModel( const enSTATIC_MODEL enModel ) const
{
	if( 0 <= enModel && enModel < enStaticModel_Max ){
		return true;//�͈͓�.
	}
	return false;	//�͈͊O.
}
bool clsResource::IsRangeSkinModel( const enSKIN_MODEL enModel ) const
{
	if (0 <= enModel && enModel < enSkinModel_Max){
		return true;
	}
	return false;
}
