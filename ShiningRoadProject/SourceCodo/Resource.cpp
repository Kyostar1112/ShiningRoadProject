#include "Resource.h"

using namespace std;
const string sPARTS_PASS = "Data\\RoboParts\\";
const string sLEG_PASS = sPARTS_PASS + "Leg\\Leg";
const string sCORE_PASS = sPARTS_PASS + "Core\\Core";
const string sHEAD_PASS = sPARTS_PASS + "Head\\Head";
const string sARML_PASS = sPARTS_PASS + "ArmL\\ArmL";
const string sARMR_PASS = sPARTS_PASS + "ArmR\\ArmR";
const string sWEAPON_PASS = sPARTS_PASS + "Weapon\\Weapon";
//extension = �g���q.
const string sEXTENSION_X = ".X";//��L�̃p�X�Ƃ���̊Ԃɐ���������Ŏg��.


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
		"Data\\Stage\\kami_map.x",
//		"Data\\RoboParts\\Head\\Head1.X",
//		"Data\\RoboParts\\Head\\Head1.X",
//		"Data\\RoboParts\\Leg\\Leg4.X",
//		"Data\\RoboParts\\ArmR\\ArmR1.X",
//		"Data\\RoboParts\\Core\\Core1.X",
		enSTATIC_MODEL::enStaticModel_Ground );
	CreateStaticModel(
		"Data\\Trap\\Spia.x", 
		enSTATIC_MODEL::enStaticModel_Enemy );

	CreateSkinModel(
		"Data\\hime\\hime_run.x", 
		enSKIN_MODEL::enSkinModel_Player );
	CreateSkinModel(
//		"Data\\RoboParts\\Leg\\Leg4.X",
		"Data\\hime\\hime_kougeki.x", 
		enSKIN_MODEL::enSkinModel_Leg );

	//�p�[�c�쐬.
//	CreatePartsGroup();
}

//�p�[�c�쐬.
void clsResource::CreatePartsGroup()
{
//	//�r.
//	for( UCHAR i=0; i<enLegModelMax - enLegModel0; i++ ){
//		ostringstream ss;
//		ss << static_cast<int>( i );
//		string tmpString = sLEG_PASS + ss.str() + sEXTENSION_X;
//		char *tmpPass = new char[tmpString.size() + 1];
//		char_traits<char>::copy( 
//			tmpPass, tmpString.c_str(), tmpString.size() + 1 );
//		CreateSkinModel(
//			tmpPass, 
//			static_cast<enSKIN_MODEL>( enLEG_MODEL::enLegModel0 + i ) );
//
//		delete[] tmpPass;
//	}
//
//	//�R�A.
//	for( UCHAR i=0; i<enCoreModelMax - enCoreModel0; i++ ){
//		ostringstream ss;
//		ss << static_cast<int>( i );
//		string tmpString = sCORE_PASS + ss.str() + sEXTENSION_X;
//		char *tmpPass = new char[tmpString.size() + 1];
//		char_traits<char>::copy( 
//			tmpPass, tmpString.c_str(), tmpString.size() + 1 );
//		CreateSkinModel(
//			tmpPass, 
//			static_cast<enSKIN_MODEL>( enCORE_MODEL::enCoreModel0 + i ) );
//
//		delete[] tmpPass;
//	}

	CreateParts( enPARTS::LEG );
	CreateParts( enPARTS::CORE );
	CreateParts( enPARTS::HEAD );
	CreateParts( enPARTS::ARM_L	);
	CreateParts( enPARTS::ARM_R	);
	CreateParts( enPARTS::WEAPON_L );//�����LR�����Ȃ̂�R�͖���.

}
void clsResource::CreateParts( const enPARTS enParts )
{
//	UCHAR ucStart, ucMax;
//	string sPass = SetVarToCreateParts( ucStart, ucMax, enParts );
//	
//	//�쐬.
//	for( UCHAR i=0; i<ucMax - ucStart; i++ ){
//		ostringstream ss;
//		ss << static_cast<int>( i );
//		string tmpString = sPass + ss.str();
//		tmpString += sEXTENSION_X;
//		//�������m��.
//		char *tmpPass = new char[tmpString.size() + 1];
//		//string����char[]�փR�s�[.
//		char_traits<char>::copy( 
//			tmpPass, tmpString.c_str(), tmpString.size() + 1 );
//		//���.
//		CreateSkinModel(
//			tmpPass, 
//			static_cast<enSKIN_MODEL>( ucStart + i ) );
//
//		delete[] tmpPass;
//	}
}
/*
//CreateParts�ŕK�v�ȕϐ�����������.
string clsResource::SetVarToCreateParts(
	UCHAR &ucStart,	//(out)���̃p�[�c�̎n�܂�ԍ�.
	UCHAR &ucMax,	//(out)���̃p�[�c�̍ő�ԍ�.
	const enPARTS enParts )
{
	string sPass;
	switch(enParts)
	{
	case enPARTS::LEG:
		ucStart = enLegModel0;
		ucMax = enLegModelMax;
		sPass = sLEG_PASS;
		break;
	case enPARTS::CORE:
		ucStart = enCoreModel0;
		ucMax = enCoreModelMax;
		sPass = sCORE_PASS;
		break;
	case enPARTS::HEAD:
		ucStart = enHeadModel0;
		ucMax = enHeadModelMax;
		sPass = sHEAD_PASS;
		break;
	case enPARTS::ARM_L:
		ucStart = enArmLModel0;
		ucMax = enArmLModelMax;
		sPass = sARML_PASS;
		break;
	case enPARTS::ARM_R:
		ucStart = enArmRModel0;
		ucMax = enArmRModelMax;
		sPass = sARMR_PASS;
		break;
	case enPARTS::WEAPON_L:
	case enPARTS::WEAPON_R:
		ucStart = enWeaponModel0;
		ucMax = enWeaponModelMax;
		sPass = sWEAPON_PASS;
		break;
	default:
		break;
	}
	return sPass;
}
*/

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
	for( UCHAR i=0; i<enStaticModel_Max; i++ ){
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
	for ( UCHAR i = 0; i<enSkinModel_Max; i++ ){
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
	if (0 <= enModel && enModel < enSkinModel_Max ){
		return true;
	}
	return false;
}
