#include "AssembleModel.h"

//�z��̓Y����.
const UCHAR ucLEG = static_cast<UCHAR>( enPARTS::LEG );
const UCHAR ucCORE = static_cast<UCHAR>( enPARTS::CORE );
const UCHAR ucHEAD = static_cast<UCHAR>( enPARTS::HEAD );
const UCHAR ucARM_L = static_cast<UCHAR>( enPARTS::ARM_L );
const UCHAR ucARM_R = static_cast<UCHAR>( enPARTS::ARM_R );
const UCHAR ucWEAPON_L = static_cast<UCHAR>( enPARTS::WEAPON_L );
const UCHAR ucWEAPON_R = static_cast<UCHAR>( enPARTS::WEAPON_R );

//�p�[�c��ނ̐�.
const UCHAR	ucPARTS_MAX = static_cast<UCHAR>( enPARTS::MAX );


//�A�������̃{�[����.
#define BONE_NAME_LEG_TO_CORE		"LegJunctionCore"
#define BONE_NAME_CORE_TO_HEAD		"CoreJunctionHead"
#define BONE_NAME_CORE_TO_ARM_L	 	"CoreJunctionArmL"
#define BONE_NAME_CORE_TO_ARM_R	 	"CoreJunctionArmR"
#define BONE_NAME_ARM_L_TO_WEAPON_L "ArmLJunctionWeapon"
#define BONE_NAME_ARM_R_TO_WEAPON_R "ArmRJunctionWeapon"



clsASSEMBLE_MODEL::clsASSEMBLE_MODEL()
	:m_wpResource( nullptr )
	,m_pPartsFactory( nullptr )
	,m_wppParts( nullptr )
	,m_dAnimSpd( 0.0 )
{
	m_dAnimSpd = 1.0;
}

clsASSEMBLE_MODEL::~clsASSEMBLE_MODEL()
{
	if( m_wppParts != nullptr ){
		for( UCHAR i=0; i<ucPARTS_MAX; i++ ){
			if( m_wppParts[i] != nullptr ){
				m_wppParts[i]->DetatchModel();
				delete m_wppParts[i];
				m_wppParts[i] = nullptr;
			}
		}
		delete[] m_wppParts;
		m_wppParts = nullptr;
	}
	SAFE_DELETE( m_pPartsFactory );
	m_wpResource = nullptr;
}



void clsASSEMBLE_MODEL::Create( clsResource* const pResource )
{
	ASSERT_IF_NOT_NULL( m_pPartsFactory );
	ASSERT_IF_NOT_NULL( m_wppParts );
	ASSERT_IF_NOT_NULL( m_wpResource );

	m_wpResource = pResource;


	m_pPartsFactory = new clsFACTORY_PARTS;

	m_wppParts = new clsPARTS_BASE*[ucPARTS_MAX];
	for( UCHAR i=0; i<ucPARTS_MAX; i++ ){
		m_wppParts[i] = m_pPartsFactory->Create( static_cast<enPARTS>( i ) );
	}

	Init();
}

//���f���̏����Z�b�g.
void clsASSEMBLE_MODEL::Init()
{
	AttachModel( enPARTS::LEG, 0 );
	AttachModel( enPARTS::CORE, 0 );
	AttachModel( enPARTS::HEAD, 0 );
	AttachModel( enPARTS::ARM_L, 0 );
	AttachModel( enPARTS::ARM_R, 0 );
	AttachModel( enPARTS::WEAPON_L, 0 );
	AttachModel( enPARTS::WEAPON_R, 0 );
	SetPos( { 0.0f, 0.0f, 0.0f } );
	SetRot( { 0.0f, 0.0f, 0.0f } );
	SetScale( 1.0f );
	SetAnimSpd( 0.1 );
}

void clsASSEMBLE_MODEL::UpDate()
{
	ASSERT_IF_NULL( m_wppParts );
	for( UCHAR i=0; i<ucPARTS_MAX; i++ ){
		ASSERT_IF_NULL( m_wppParts[i] );
		m_wppParts[i]->Update();
	}
}

void clsASSEMBLE_MODEL::Render(
	const D3DXMATRIX& mView, 
	const D3DXMATRIX& mProj, 
	const D3DXVECTOR3& vLight, 
	const D3DXVECTOR3& vEye,
	const D3DXVECTOR4 &vColor,
	const bool isAlpha )
{
	ASSERT_IF_NULL( m_wppParts );
	for( UCHAR i=0; i<ucPARTS_MAX; i++ ){
		ASSERT_IF_NULL( m_wppParts[i] );
		m_wppParts[i]->ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
		SetPos( GetPos() );
		m_wppParts[i]->ModelUpdate( m_wppParts[i]->m_Trans );
	}
//	m_wppParts[ucLEG]->ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
//	m_wppParts[ucCORE]->ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
//	m_wppParts[ucHEAD]->ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
//	m_wppParts[ucARM_L]->ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
//	m_wppParts[ucARM_R]->ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
//	m_wppParts[ucWEAPON_L]->ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
//	m_wppParts[ucWEAPON_R]->ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
}


//���f�����ς�.
void clsASSEMBLE_MODEL::AttachModel( 
	const enPARTS enParts,
	const SKIN_ENUM_TYPE PartsNum )
{
	UCHAR ucParts = static_cast<UCHAR>( enParts );
	ASSERT_IF_NULL( m_wppParts );
	ASSERT_IF_NULL( m_wppParts[ucParts] );
	m_wppParts[ucParts]->DetatchModel();
	m_wppParts[ucParts]->AttachModel( 
		m_wpResource->GetPartsModels( enParts, PartsNum ) );
	m_wppParts[ucParts]->SetAnimSpeed( m_dAnimSpd );
	
}


//�g�����X�t�H�[��.
void clsASSEMBLE_MODEL::SetPos( const D3DXVECTOR3 &vPos )
{
	m_Trans.vPos = vPos;

	ASSERT_IF_NULL( m_wppParts );
	for( UCHAR i=0; i<ucPARTS_MAX; i++ ){
		ASSERT_IF_NULL( m_wppParts[i] );
//		m_wppParts[i]->SetPosition( m_Trans.vPos );
	}

	m_wppParts[ucLEG]->SetPosition( m_Trans.vPos );

	m_wppParts[ucCORE]->SetPosition( 
 		m_wppParts[ucLEG]->GetBonePos( BONE_NAME_LEG_TO_CORE ) );

	m_wppParts[ucHEAD]->SetPosition( 
		m_wppParts[ucCORE]->GetBonePos( BONE_NAME_CORE_TO_HEAD ) );

	m_wppParts[ucARM_L]->SetPosition( 
		m_wppParts[ucCORE]->GetBonePos( BONE_NAME_CORE_TO_ARM_L ) );

	m_wppParts[ucARM_R]->SetPosition( 
		m_wppParts[ucCORE]->GetBonePos( BONE_NAME_CORE_TO_ARM_R ) );

	m_wppParts[ucWEAPON_L]->SetPosition( 
		m_wppParts[ucARM_L]->GetBonePos( BONE_NAME_ARM_L_TO_WEAPON_L ) );
										   
	m_wppParts[ucWEAPON_R]->SetPosition( 
		m_wppParts[ucARM_R]->GetBonePos( BONE_NAME_ARM_R_TO_WEAPON_R ) );

	FitJointModel( m_wppParts[ucWEAPON_L], m_wppParts[ucARM_L],
		"ArmLJunctionCore", "ArmLJunctionWeapon" );//ArmLJunctionWeapon.
	FitJointModel( m_wppParts[ucWEAPON_R], m_wppParts[ucARM_R],
		"ArmR0", "ArmR3" );
}
void clsASSEMBLE_MODEL::AddPos( const D3DXVECTOR3 &vVec )
{
	SetPos( m_Trans.vPos + vVec );
}
D3DXVECTOR3 clsASSEMBLE_MODEL::GetPos() const
{
	return m_Trans.vPos;
}



void clsASSEMBLE_MODEL::SetRot( const D3DXVECTOR3 &vRot )
{
	ASSERT_IF_NULL( m_wppParts );
	D3DXVECTOR3 tmpRot = vRot;

	GuardDirOver( tmpRot.x );
	GuardDirOver( tmpRot.y );
	GuardDirOver( tmpRot.z );

	m_Trans.fPitch	= tmpRot.x;
	m_Trans.fYaw	= tmpRot.y;
	m_Trans.fRoll	= tmpRot.z;

	for( UCHAR i=0; i<ucPARTS_MAX; i++ ){
		ASSERT_IF_NULL( m_wppParts[i] );
		m_wppParts[i]->SetRotation( tmpRot );
	}
}
void clsASSEMBLE_MODEL::AddRot( const D3DXVECTOR3 &vRot )
{
	SetRot( D3DXVECTOR3( m_Trans.fPitch, m_Trans.fYaw, m_Trans.fRoll ) + vRot );
}

void clsASSEMBLE_MODEL::SetScale( const float fScale )
{
	ASSERT_IF_NULL( m_wppParts );
	m_Trans.vScale = { fScale, fScale, fScale };
	for( UCHAR i=0; i<ucPARTS_MAX; i++ ){
		ASSERT_IF_NULL( m_wppParts[i] );
		m_wppParts[i]->SetScale( fScale );
	}
}



void clsASSEMBLE_MODEL::SetAnimSpd( const double &dSpd )
{
	ASSERT_IF_NULL( m_wppParts );
	m_dAnimSpd = dSpd;
	for( UCHAR i=0; i<ucPARTS_MAX; i++ ){
		ASSERT_IF_NULL( m_wppParts[i] );
		m_wppParts[i]->SetAnimSpeed( m_dAnimSpd );
	}
}


//��]�l�}��.
float clsASSEMBLE_MODEL::GuardDirOver( float &outTheta ) const
{
	float fDIR_RIMIT = static_cast<float>( D3DX_PI * 2.0 ); 
	if( outTheta < 0.0 ){
		outTheta += fDIR_RIMIT;
	}
	else if( outTheta > fDIR_RIMIT ){
		outTheta -= fDIR_RIMIT;
	}
	else{
		return outTheta;
	}

	GuardDirOver( outTheta );

	return outTheta;
}




//�r�̊p�x�𕐊���͎ʂ���.
void clsASSEMBLE_MODEL::FitJointModel( 
	clsPARTS_BASE *pMover, clsPARTS_BASE *pBace,
	const char const *RootBone, const char const *EndBone )
{
	//�{�[���̃x�N�g�����o��.
	D3DXVECTOR3 vVec = 
		pBace->GetBonePos( const_cast<char*>( EndBone ) ) - 
		pBace->GetBonePos( const_cast<char*>( RootBone ) );
	D3DXVec3Normalize( &vVec, &vVec );

	D3DXVECTOR3 vRot = { 0.0f, 0.0f, 0.0f };
	vRot.x = atan2f( vVec.y, vVec.z );
	vRot.y = atan2f( vVec.z, vVec.x );
	vRot.z = atan2f( vVec.x, vVec.y );



	vRot.x = GuardDirOver( vRot.x );
	vRot.y = GuardDirOver( vRot.y );
	vRot.z = GuardDirOver( vRot.z );

	pMover->SetRotation( vRot );
}




#if _DEBUG
//�e�p�[�c��pos.
D3DXVECTOR3 clsASSEMBLE_MODEL::GetPartsPos( const UCHAR ucParts ) const
{
	ASSERT_IF_NULL( m_wppParts );
	ASSERT_IF_NULL( m_wppParts[ucParts] );
	return m_wppParts[ucParts]->GetPosition();
}
#endif//#if _DEBUG

