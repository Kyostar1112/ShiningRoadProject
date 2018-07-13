#include "SceneAssemble.h"

using namespace std;

#define TEST_TEX_PASS "Data\\Load\\LoadBack.png"

//�v�f����<clsSCENE_ASSEMBLE::ENUM_SIZE>.
const string sPARTS_STATUS_PASS[] =
{
	"Data\\RoboParts\\Leg\\RoboPartsData.csv",
	"Data\\RoboParts\\Core\\RoboPartsData.csv",
	"Data\\RoboParts\\Head\\RoboPartsData.csv",
	"Data\\RoboParts\\Arms\\RoboPartsData.csv",
	"Data\\RoboParts\\Weapon\\RoboPartsData.csv",
	"Data\\RoboParts\\Weapon\\RoboPartsData.csv",
};

//���f������̏����ʒu.
const D3DXVECTOR3 vINIT_ROBO_POS = { 52.0f, -35.0f, 17.0f };
const D3DXVECTOR3 vINIT_ROBO_ROT = { 6.03318501f, 0.649538994f, 6.18318605f };
const float fINIT_ROBO_SCALE = 0.5f;

//�J�����̏����ʒu.
const D3DXVECTOR3 vINIT_CAMERA_POS = { 0.0f, 0.0f, -100.0f };
const D3DXVECTOR3 vINIT_CAMERA_LOOK_POS = { 0.0f, 0.0f, 0.0f };


//�X�e�[�^�X�́ACSV������s��.
const int iSTATUS_CUT_NUM = 2;//�ԍ��Ɩ��O.



//================================//
//========== �g�݊����N���X ==========//
//================================//
clsSCENE_ASSEMBLE::clsSCENE_ASSEMBLE( clsPOINTER_GROUP* const ptrGroup ) : clsSCENE_BASE( ptrGroup )
	,m_pAsmModel( nullptr )
	,m_pUI( nullptr )
	,m_cuFileMax( 0 )
{

}

clsSCENE_ASSEMBLE::~clsSCENE_ASSEMBLE()
{
	SAFE_DELETE( m_pAsmModel );
	SAFE_DELETE( m_pUI );

	for( unsigned int i=0; i<m_vspFile.size(); i++ ){
		if( m_vspFile[i] == nullptr ) continue;
		m_vspFile[i]->Close();
		m_vspFile[i].reset();
	}
	
	m_cuFileMax = 0;
}

void clsSCENE_ASSEMBLE::CreateProduct()
{

//	m_pTestChara = new clsCharaStatic;
//	m_pTestChara->AttachModel( 
//		m_wpResource->GetStaticModels( 
//		clsResource::enSTATIC_MODEL::enStaticModel_Ground ) );
//	m_pTestChara->Init();
//	m_pTestChara->SetPosition( D3DXVECTOR3( 1.0f, 0.0f, 50.0f ) );
//
//	m_pParts = new clsCharaStatic;
//	m_pParts->AttachModel( 
//		m_wpResource->GetStaticModels( 
//		clsResource::enSTATIC_MODEL::enStaticModel_Enemy ) );
//	m_pParts->Init();
//	m_pParts->SetPosition( D3DXVECTOR3( -2.0f, 1.0f, 0.0f ) );
//


	//UI�̐��p�ϐ�.
	clsASSEMBLE_UI::PARTS_NUM_DATA partsData;
	partsData.resize( enPARTS_TYPES::ENUM_SIZE );

	//�p�[�c�̃X�e�[�^�X�ǂݍ���.
	m_cuFileMax = enPARTS_TYPES::ENUM_SIZE;
	m_vspFile.resize( m_cuFileMax ); 
	for( UCHAR i=0; i<m_vspFile.size(); i++ ){
		if( m_vspFile[i] != nullptr ){
			assert( !"m_spFile[i]�͍쐬�ς݂ł�" );
			continue;
		}
		m_vspFile[i] = make_shared< clsFILE >();
		m_vspFile[i]->Open( sPARTS_STATUS_PASS[i] );

		partsData[i] = m_vspFile[i]->GetSizeRow();
	}

	//UI.
	assert( !m_pUI );
	m_pUI = new clsASSEMBLE_UI;
	m_pUI->Create( m_wpDevice, m_wpContext, partsData );

	//���f������쐬.
	assert( m_pAsmModel == nullptr );
	m_pAsmModel = new clsASSEMBLE_MODEL;
	m_pAsmModel->Create( m_wpResource, m_wpRoboStatus );
	m_pAsmModel->SetPos( vINIT_ROBO_POS );
	m_pAsmModel->SetRot( vINIT_ROBO_ROT );
	m_pAsmModel->SetScale( fINIT_ROBO_SCALE );

	m_wpCamera->SetPos( vINIT_CAMERA_POS );
	m_wpCamera->SetLookPos( vINIT_CAMERA_LOOK_POS );

	//�~�b�V�����V�[���Ɉ����p�����̏�����.
	m_wpRoboStatus->Clear();
}

void clsSCENE_ASSEMBLE::UpdateProduct( enSCENE &enNextScene )
{
#if _DEBUG
	//�e�X�g���f�������� & �p�[�c�ؑ�.
	if( GetAsyncKeyState( VK_SPACE ) & 0x1 ){
#ifdef RESOURCE_READ_PARTS_MODEL_LOCK

		static int tmpI = 0; 
		tmpI ++;
		if( tmpI >= iTEST_ROBO_PARTS_MODEL_MAX ) tmpI = 0;

		m_pAsmModel->AttachModel( enPARTS::LEG, tmpI );
		m_pAsmModel->AttachModel( enPARTS::CORE, tmpI );
		m_pAsmModel->AttachModel( enPARTS::HEAD, tmpI );
		m_pAsmModel->AttachModel( enPARTS::ARM_L, tmpI );
		m_pAsmModel->AttachModel( enPARTS::ARM_R, tmpI );
		m_pAsmModel->AttachModel( enPARTS::WEAPON_L, tmpI );
		m_pAsmModel->AttachModel( enPARTS::WEAPON_R, tmpI );

#endif//#ifndef RESOURCE_READ_PARTS_MODEL_LOCK
		m_pAsmModel->SetPos( vINIT_ROBO_POS );
		m_pAsmModel->SetRot( vINIT_ROBO_ROT );
		m_pAsmModel->SetScale( fINIT_ROBO_SCALE );

		m_pAsmModel->SetRot( { 0.0f, 0.0f, 0.0f } );

		m_wpSound->StopAllSound();
	}

	//�e�X�g���f���ړ�.
	float fff = 1.0f;
	if( GetAsyncKeyState( 'W' ) & 0x8000 ) m_pAsmModel->AddPos( { 0.0f, fff, 0.0f } );
	if( GetAsyncKeyState( 'S' ) & 0x8000 ) m_pAsmModel->AddPos( { 0.0f, -fff, 0.0f } );
	if( GetAsyncKeyState( 'D' ) & 0x8000 ) m_pAsmModel->AddPos( { fff, 0.0f, 0.0f } );
	if( GetAsyncKeyState( 'A' ) & 0x8000 ) m_pAsmModel->AddPos( { -fff, 0.0f, 0.0f } );
	if( GetAsyncKeyState( 'E' ) & 0x8000 ) m_pAsmModel->AddPos( { 0.0f, 0.0f, fff } );
	if( GetAsyncKeyState( 'Q' ) & 0x8000 ) m_pAsmModel->AddPos( { 0.0f, 0.0f, -fff } );
	float rrr = 0.05f;
	if( GetAsyncKeyState( 'T' ) & 0x8000 ) m_pAsmModel->AddRot( { 0.0f, rrr, 0.0f } );
	if( GetAsyncKeyState( 'G' ) & 0x8000 ) m_pAsmModel->AddRot( { 0.0f, -rrr, 0.0f } );
	if( GetAsyncKeyState( 'F' ) & 0x8000 ) m_pAsmModel->AddRot( { rrr, 0.0f, 0.0f } );
	if( GetAsyncKeyState( 'H' ) & 0x8000 ) m_pAsmModel->AddRot( { -rrr, 0.0f, 0.0f } );
	if( GetAsyncKeyState( 'R' ) & 0x8000 ) m_pAsmModel->AddRot( { 0.0f, 0.0f, rrr } );
	if( GetAsyncKeyState( 'Y' ) & 0x8000 ) m_pAsmModel->AddRot( { 0.0f, 0.0f, -rrr } );


	if( GetAsyncKeyState( VK_F6 ) & 0x1 ){
//		enNextScene = enSCENE::MISSION;
		static int tmpLAnim = 0;
		m_pAsmModel->PartsAnimChange( static_cast<enPARTS>( m_PartsSelect.Type ), tmpLAnim++ );
		if( tmpLAnim >= 5 ) tmpLAnim = 0;
	}
	if( GetAsyncKeyState( VK_F7 ) & 0x1 ){
		static int siCORE_ANIM_NO = 0;
		m_pAsmModel->PartsAnimChange( enPARTS::LEG, siCORE_ANIM_NO++ );
		if( siCORE_ANIM_NO > 1 ) siCORE_ANIM_NO = 0;
	}



	if( GetAsyncKeyState( 'Z' ) & 0x1 )m_wpSound->PlaySE( 0 );
	if( GetAsyncKeyState( 'X' ) & 0x1 )m_wpSound->PlaySE( 1 );
	if( GetAsyncKeyState( 'C' ) & 0x1 )m_wpSound->PlaySE( 2 );
	if( GetAsyncKeyState( 'V' ) & 0x1 )m_wpSound->PlaySE( 3 );
	if( GetAsyncKeyState( 'B' ) & 0x1 )m_wpSound->PlaySE( 4 );
	if( GetAsyncKeyState( 'N' ) & 0x1 ){
		m_ehHibana = m_wpEffects->Play( 
			2, { 0.0f, 20.0f, 0.0f } );
	}



#endif//#if _DEBUG





	//�I����.
	if( isPressRight() )MoveCursorRight();
	if( isPressLeft() )	MoveCursorLeft();
	if( isPressUp() )	MoveCursorUp();
	if( isPressDown() )	MoveCursorDown();
	if( isPressEnter() ){
		Enter();
		m_wpSound->PlaySE( enSE::ENTER );
	}
	if( isPressExit() ){
		Undo();
		m_wpSound->PlaySE( enSE::EXIT, true );
	}


	m_pUI->Input();
	m_pUI->Update( m_vspFile[m_PartsSelect.Type], m_PartsSelect.Type, m_PartsSelect.Num, iSTATUS_CUT_NUM );
	m_pAsmModel->UpDate();

}

void clsSCENE_ASSEMBLE::RenderProduct( const D3DXVECTOR3 &vCamPos )
{
//	m_pSprite->SetPos( ConvDimPos( m_pParts->GetPosition() ) );
////	ConvDimPos( m_pSprite->GetPos(), m_pParts->GetPosition() );
//
//	m_pParts->Render( m_mView, m_mProj, m_vLight, vCamPos );
//	m_pTestChara->Render( m_mView, m_mProj, m_vLight, vCamPos, 
//		D3DXVECTOR4(0.5f,2.0f,0.5f,0.75f), true );

	m_pAsmModel->Render( m_mView, m_mProj, m_vLight, vCamPos );

	SetDepth( false );
	m_pUI->Render( m_PartsSelect.Type, m_PartsSelect.Num );
	SetDepth( true );
}



//�J�[�\���ړ�.
void clsSCENE_ASSEMBLE::MoveCursorUp()
{
	m_PartsSelect.Num --;

	m_PartsSelect.Num = 
		KeepRange( m_PartsSelect.Num, 0, m_vspFile[m_PartsSelect.Type]->GetSizeRow() );
}

void clsSCENE_ASSEMBLE::MoveCursorDown()
{
	m_PartsSelect.Num ++;

	m_PartsSelect.Num = 
		KeepRange( m_PartsSelect.Num, 0, m_vspFile[m_PartsSelect.Type]->GetSizeRow() );
}

void clsSCENE_ASSEMBLE::MoveCursorRight()
{
	m_PartsSelect.Type ++;

	m_PartsSelect.Type = 
		KeepRange( m_PartsSelect.Type, 0, enPARTS_TYPES::ENUM_SIZE );
	//�p�[�c��ނ����ւ����Ƃ��Ƀp�[�c�����Ⴄ�ƍ���̂�.
	m_PartsSelect.Num = 
		KeepRange( m_PartsSelect.Num, 0, m_vspFile[m_PartsSelect.Type]->GetSizeRow() );
}

void clsSCENE_ASSEMBLE::MoveCursorLeft()
{
	m_PartsSelect.Type --;

	m_PartsSelect.Type = 
		KeepRange( m_PartsSelect.Type, 0, enPARTS_TYPES::ENUM_SIZE );
	//�p�[�c��ނ����ւ����Ƃ��Ƀp�[�c�����Ⴄ�ƍ���̂�.
	m_PartsSelect.Num = 
		KeepRange( m_PartsSelect.Num, 0, m_vspFile[m_PartsSelect.Type]->GetSizeRow() );
}

//����.
void clsSCENE_ASSEMBLE::Enter()
{
	//�X�e�[�^�X�������ڂ���̂�.
	const int iStatusSize = m_vspFile[ m_PartsSelect.Type ]->GetSizeCol() - iSTATUS_CUT_NUM;

	//�����p�ϐ�.
	vector<int> tmpStatus;
	tmpStatus.reserve( iStatusSize );
	for( int i=0; i<iStatusSize; i++ ){
		//m_vspFile[]�̓Y�����͂ǂ̃p�[�c���A�ł���.
		tmpStatus.push_back( 
			m_vspFile[ m_PartsSelect.Type ]->
				GetDataInt( m_PartsSelect.Num, i + iSTATUS_CUT_NUM ) );
		//GetDataInt()�̑������́A���̃p�[�c���ʂ̉��Ԗڂ̍s���Q�Ƃ���΂悢�̂�.
		//��������iSTATUS_CUT_NUM�𑫂��Ă���̂́A���̕\�ɂ���p�[�c�ԍ��Ɩ��O�͂���Ȃ�����J�b�g���邽�߂ł���.
	}

	//���x���L���X�g������̂͌��Ȃ̂�.
	UCHAR tmpPartsNum = static_cast<UCHAR>( m_PartsSelect.Num );

	switch( m_PartsSelect.Type )
	{
	case enPARTS_TYPES::LEG:
		m_wpRoboStatus->ReceiveLeg( tmpStatus,	tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::LEG, tmpPartsNum );
		break;
	case enPARTS_TYPES::CORE:
		m_wpRoboStatus->ReceiveCore( tmpStatus,		tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::CORE,	tmpPartsNum );
		break;
	case enPARTS_TYPES::HEAD:
		m_wpRoboStatus->ReceiveHead( tmpStatus,		tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::HEAD,	tmpPartsNum );
		break;
	case enPARTS_TYPES::ARMS:
		m_wpRoboStatus->ReceiveArms( tmpStatus,		tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::ARM_L,	tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::ARM_R,	tmpPartsNum );
		break;
	case enPARTS_TYPES::WEAPON_L:
		m_wpRoboStatus->ReceiveWeaponL( tmpStatus,	tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::WEAPON_L,tmpPartsNum );
		break;
	case enPARTS_TYPES::WEAPON_R:
		m_wpRoboStatus->ReceiveWeaponR( tmpStatus,	tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::WEAPON_R,tmpPartsNum );
		break;
	default:
		break;
	}

	//�����p�ϐ��̕ЂÂ�.
	tmpStatus.clear();
	tmpStatus.shrink_to_fit();

//	enNextScene = enSCENE::MISSION;
}

//�߂�.
void clsSCENE_ASSEMBLE::Undo()
{

}





//�͈͓��Ɏ��߂�( �p�[�c�̑I�������I�[�o�[���Ȃ��悤�ɂ��� ).
//min�͂��̐��l��菬�����Ȃ�Ȃ��Amax�͂���ȏ�ɂ͂Ȃ�Ȃ�.
// min <= t < max.
template<class T, class MIN, class MAX >
T clsSCENE_ASSEMBLE::KeepRange( T t, const MIN min, const MAX max ) const
{
	int num = static_cast<int>( t );
	int Min = static_cast<int>( min );
	int Max = static_cast<int>( max );
	
	if( Min > num ){
		num = Min;
	}
	else if( num >= Max ){
		num = Max - 1;
	}

	return static_cast<T>( num );
}


//============================ �f�o�b�O�e�L�X�g ===========================//
#if _DEBUG
void clsSCENE_ASSEMBLE::RenderDebugText()
{
	//NULL�`�F�b�N.
	assert( m_upText );

	char strDbgTxt[256];
	int iTxtY = 0;
	const int iOFFSET = 10;//��s���ɂǂꂾ�����ɂ��炷��.
	
//	//���f����pos.
//	sprintf_s( strDbgTxt, 
//		"ModelPos : x[%f], y[%f], z[%f]",
//		m_pAsmModel->GetPos().x, 
//		m_pAsmModel->GetPos().y, 
//		m_pAsmModel->GetPos().z );
//	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );
//
//	sprintf_s( strDbgTxt, 
//		"ModelRot : x[%f], y[%f], z[%f]",
//		m_pAsmModel->GetRot().x, 
//		m_pAsmModel->GetRot().y, 
//		m_pAsmModel->GetRot().z );
//	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );
//
//	//�e�p�[�c��pos.
//	for( UCHAR ucNo=0; ucNo<static_cast<UCHAR>( enPARTS::MAX ); ucNo++ ){
//		sprintf_s( strDbgTxt, 
//			"PartsPos : x[%f], y[%f], z[%f]",
//			m_pAsmModel->GetPartsPos( ucNo ).x, 
//			m_pAsmModel->GetPartsPos( ucNo ).y, 
//			m_pAsmModel->GetPartsPos( ucNo ).z );
//		m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );
//	}
//
//	//�J����.
//	sprintf_s( strDbgTxt, 
//		"CameraPos : x[%f], y[%f], z[%f]",
//		GetCameraPos().x, GetCameraPos().y, GetCameraPos().z );
//	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );
//
//	sprintf_s( strDbgTxt, 
//		"CamLokPos : x[%f], y[%f], z[%f]",
//		GetCameraLookPos().x, GetCameraLookPos().y, GetCameraLookPos().z );
//	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );
//
//	//���C�g.
//	sprintf_s( strDbgTxt, 
//		"Light : x[%f], y[%f], z[%f]",
//		m_vLight.x, m_vLight.y, m_vLight.z );
//	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

//	//���C�g.
//	sprintf_s( strDbgTxt, 
//		"Light : x[%f], y[%f], z[%f]",
//		m_vLight.x, m_vLight.y, m_vLight.z );
//	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

	//�I����.
	sprintf_s( strDbgTxt, 
		"UiPos : x[%f], y[%f]",
		m_pUI->GetUiPos().x, m_pUI->GetUiPos().y );
	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

	//�e�X�g�p�ɐ��l���o��.
	string tmpsString;
	tmpsString = m_vspFile[m_PartsSelect.Type]->GetDataString( m_PartsSelect.Num );
	const char* tmpcString = tmpsString.c_str();
	sprintf_s( strDbgTxt, 
		tmpcString );
	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );



}
#endif //#if _DEBUG



