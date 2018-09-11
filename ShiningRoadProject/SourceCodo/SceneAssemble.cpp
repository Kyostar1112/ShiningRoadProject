#include "SceneAssemble.h"

using namespace std;

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
//const D3DXVECTOR3 vINIT_ROBO_POS = { 52.0f, -35.0f, 17.0f };
//const D3DXVECTOR3 vINIT_ROBO_ROT = { 6.03318501f, 0.649538994f, 6.18318605f };
const D3DXVECTOR3 vINIT_ROBO_POS = { 0.0f, 0.0f, 0.0f };
const D3DXVECTOR3 vINIT_ROBO_ROT = { 0.0f, static_cast<float>( M_PI_4 ) * 0.5f, 0.0f };
const float fINIT_ROBO_SCALE = 0.75f;

//�J�����̏����ʒu.
const D3DXVECTOR3 vINIT_CAMERA_POS = { 0.0f, 0.0f, -100.0f };
const D3DXVECTOR3 vINIT_CAMERA_LOOK_POS = { 0.0f, 0.0f, 0.0f };


//�X�e�[�^�X�́ACSV������s��.
const int iSTATUS_CUT_NUM = 2;//�ԍ��Ɩ��O.

//----- �p�[�c�E�B���h�E�p -----//.
//�r���[�|�[�g.
const FLOAT INIT_VP_PARTS_W = 576.0f;
const FLOAT INIT_VP_PARTS_H = 482.0f;
const FLOAT INIT_VP_PARTS_X = 153.0f;
const FLOAT INIT_VP_PARTS_Y = 176.0f;
const FLOAT INIT_VP_PARTS_MIN =	0.0f;
const FLOAT INIT_VP_PARTS_MAX =	1.0f;
//�J����.
const D3DXVECTOR3 vPARTS_VIEW_CAM_POS  = { 0.0f, 0.0f, -100.0f };
const D3DXVECTOR3 vPARTS_VIEW_CAM_LOOK = { 0.0f, 0.0f, 0.0f };
//----- �p�[�c�E�B���h�E�p -----//.

//----- ���{�E�B���h�E�p -----//.
//�r���[�|�[�g.
const FLOAT INIT_VP_ROBO_W = 490.0f;
const FLOAT INIT_VP_ROBO_H = 570.0f;
const FLOAT INIT_VP_ROBO_X = 753.0f;
const FLOAT INIT_VP_ROBO_Y = 87.0f;
const FLOAT INIT_VP_ROBO_MIN =	0.0f;
const FLOAT INIT_VP_ROBO_MAX =	1.0f;
//�J����.
const D3DXVECTOR3 vROBO_VIEW_CAM_POS  = { 0.0f, 20.0f, -100.0f };
const D3DXVECTOR3 vROBO_VIEW_CAM_LOOK = { 0.0f, 0.0f, 0.0f };
//----- ���{�E�B���h�E�p -----//.

//----- �w�i -----//.
const char* sBACK_SPRITE_PATH = "Data\\Image\\AssembleUi\\AssembleBack.png";
const D3DXVECTOR3 vBACK_POS = { 0.0f, 0.0f, 0.0f };

//----- �w�i -----//.


//���{��UI.
const char* sFONT_TEXT_PATH_ASSEMBLE = "Data\\Font\\Text\\TextAssemble.csv";
//�{�^������.
const D3DXVECTOR3 vFONT_BUTTON_POS = { 600.0f, 40.0f, 0.0f };
const float fFONT_BUTTON_SCALE = 14.0f;
const int iFONT_BUTTON_LINE = 0;
const int iFONT_BUTTON_TEXT_SIZE = 64;

//�p�[�c�A�X�e�[�^�X����.
const D3DXVECTOR3 vFONT_COMMENT_POS = { 28.0f, 680.0f, 0.0f };
const float fFONT_COMMENT_SCALE = 16.0f;
const int iFONT_COMMENT_LINE = 1;
const int iFONT_COMMENT_TEXT_SIZE = 128;

//================================//
//========== �g�݊����N���X ==========//
//================================//
clsSCENE_ASSEMBLE::clsSCENE_ASSEMBLE( clsPOINTER_GROUP* const ptrGroup ) : clsSCENE_BASE( ptrGroup )
	,m_pAsmModel( nullptr )
	,m_pUI( nullptr )
	,m_pViewPortPartsWindow( nullptr )
	,m_pViewPortRoboWindow( nullptr )
	,m_cuFileMax( 0 )
	,m_pSelectParts( nullptr )
//	,m_enSelectMode()
{
	m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::PARTS;
}

clsSCENE_ASSEMBLE::~clsSCENE_ASSEMBLE()
{

	SAFE_DELETE( m_pViewPortRoboWindow );
	SAFE_DELETE( m_pViewPortPartsWindow );
	SAFE_DELETE( m_pAsmModel );
	SAFE_DELETE( m_pUI );

	for( unsigned int i=0; i<m_vspFile.size(); i++ ){
		if( m_vspFile[i] == nullptr ) continue;
		m_vspFile[i]->Close();
		m_vspFile[i].reset();
	}
	m_vspFile.clear();
	m_vspFile.shrink_to_fit();

	m_cuFileMax = 0;
	m_pSelectParts = nullptr;
}

void clsSCENE_ASSEMBLE::CreateProduct()
{
	m_wpFont->Create( sFONT_TEXT_PATH_ASSEMBLE );

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

	//�w�i.
	SPRITE_STATE ss;
	ss.Disp = { WND_W, WND_H };
	m_upBack = make_unique< clsSprite2D >();
	m_upBack->Create( m_wpDevice, m_wpContext, sBACK_SPRITE_PATH, ss );
	m_upBack->SetPos( vBACK_POS );


	//UI�̐��p�ϐ�.
	clsASSEMBLE_UI::PARTS_NUM_DATA partsData;
	partsData.resize( clsASSEMBLE_MODEL::ENUM_SIZE );

	//�p�[�c�̃X�e�[�^�X�ǂݍ���.
	m_cuFileMax = clsASSEMBLE_MODEL::ENUM_SIZE;
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
	m_pUI = new clsASSEMBLE_UI( m_wpFont );
	m_pUI->Create( m_wpDevice, m_wpContext, partsData );

	//���f������쐬.
	assert( m_pAsmModel == nullptr );
	m_pAsmModel = new clsASSEMBLE_MODEL;
	m_pAsmModel->Create( m_wpResource, m_wpRoboStatus );
	m_pAsmModel->SetPos( vINIT_ROBO_POS );
	m_pAsmModel->SetRot( vINIT_ROBO_ROT );
	m_pAsmModel->SetScale( fINIT_ROBO_SCALE );

	assert( m_wpCamera );
	m_wpCamera->SetPos( vINIT_CAMERA_POS );
	m_wpCamera->SetLookPos( vINIT_CAMERA_LOOK_POS );

	//�������̃p�[�c�����̑I�����ɓK������.
	m_PartsSelect.Num[ static_cast<char>( clsASSEMBLE_MODEL::LEG ) ]		= m_wpRoboStatus->GetPartsNum( enPARTS::LEG );
	m_PartsSelect.Num[ static_cast<char>( clsASSEMBLE_MODEL::CORE ) ]		= m_wpRoboStatus->GetPartsNum( enPARTS::CORE );
	m_PartsSelect.Num[ static_cast<char>( clsASSEMBLE_MODEL::HEAD ) ]		= m_wpRoboStatus->GetPartsNum( enPARTS::HEAD );
	m_PartsSelect.Num[ static_cast<char>( clsASSEMBLE_MODEL::ARMS ) ]		= m_wpRoboStatus->GetPartsNum( enPARTS::HEAD );
	m_PartsSelect.Num[ static_cast<char>( clsASSEMBLE_MODEL::WEAPON_L ) ]	= m_wpRoboStatus->GetPartsNum( enPARTS::WEAPON_L );
	m_PartsSelect.Num[ static_cast<char>( clsASSEMBLE_MODEL::WEAPON_R ) ]	= m_wpRoboStatus->GetPartsNum( enPARTS::WEAPON_R );

	//�~�b�V�����V�[���Ɉ����p�����̏�����.
	assert( m_wpRoboStatus );
	m_wpRoboStatus->Clear();

	//�p�[�c�r���[.
	assert( !m_pViewPortPartsWindow );
	m_pViewPortPartsWindow = new D3D11_VIEWPORT;
	m_pViewPortPartsWindow->Width	 = INIT_VP_PARTS_W;
	m_pViewPortPartsWindow->Height	 = INIT_VP_PARTS_H;
	m_pViewPortPartsWindow->TopLeftX = INIT_VP_PARTS_X;
	m_pViewPortPartsWindow->TopLeftY = INIT_VP_PARTS_Y;
	m_pViewPortPartsWindow->MinDepth = INIT_VP_PARTS_MIN;
	m_pViewPortPartsWindow->MaxDepth = INIT_VP_PARTS_MAX;

	//���{�r���[.
	assert( !m_pViewPortRoboWindow );
	m_pViewPortRoboWindow = new D3D11_VIEWPORT;
	m_pViewPortRoboWindow->Width	= INIT_VP_ROBO_W;
	m_pViewPortRoboWindow->Height	= INIT_VP_ROBO_H;
	m_pViewPortRoboWindow->TopLeftX = INIT_VP_ROBO_X;
	m_pViewPortRoboWindow->TopLeftY = INIT_VP_ROBO_Y;
	m_pViewPortRoboWindow->MinDepth = INIT_VP_ROBO_MIN;
	m_pViewPortRoboWindow->MaxDepth = INIT_VP_ROBO_MAX;

	//�p�[�c�r���[�ɒu���p�[�c.
	assert( !m_pSelectParts );
	m_pSelectParts = new clsPARTS_WINDOW_MODEL( m_wpResource, m_wpRoboStatus );
//	m_pSelectParts->AttachModel( m_wpResource->GetPartsModels(
//		static_cast< enPARTS >( m_PartsSelect.Type ),
//		static_cast< SKIN_ENUM_TYPE >( m_PartsSelect.Num[ m_PartsSelect.Type ] ) ) );

}

void clsSCENE_ASSEMBLE::UpdateProduct( enSCENE &enNextScene )
{
	assert( m_wpSound );

	int a = m_wpRoboStatus->GetRoboState( clsROBO_STATUS::HP );

#if _DEBUG
	//�e�X�g���f�������� & �p�[�c�ؑ�.
	if( GetAsyncKeyState( 'Z' ) & 0x1 ){
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
	if( isPressRight()	)MoveCursorRight();
	if( isPressLeft()	)MoveCursorLeft();
	if( isPressUp()		)MoveCursorUp();
	if( isPressDown()	)MoveCursorDown();
	if( m_wpXInput->isPressEnter( XINPUT_B ) ||
		GetAsyncKeyState( VK_RETURN ) & 0x1 )
	{
		Enter( enNextScene );
	}
	if( isPressExit() ){
		Undo( enNextScene );
	}
	//���̃V�[����.
	if( m_wpXInput->isPressEnter( XINPUT_START ) || 
		GetAsyncKeyState( VK_SPACE ) )
	{
		MissionStart( enNextScene );
	}
	//�X�e�[�^�X�E�B���h�E���B��.
	if( m_wpXInput->isPressEnter( XINPUT_Y ) ){
		m_pUI->SwitchDispStatusComment();
		m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::PARTS;
	}
	//�X�e�[�^�X��comment�ؑ�.
	if( m_wpXInput->isPressEnter( XINPUT_X ) ){
		if( m_pUI->isCanSwitchStatusComment() ){
			if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ||
				m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS )
			{
				m_pUI->SwitchStatusComment();
				if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ){
					m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::STATUS;
				}
				else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS ){
					m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::PARTS;
				}
			}
		}
	}


	assert( m_pUI );
	m_pUI->Input( m_wpXInput, m_wpDxInput );
	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ||
		m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS ){
		assert( m_vspFile[m_PartsSelect.Type] );
		m_pUI->Update( 
			m_enSelectMode,
			m_vspFile[m_PartsSelect.Type], 
			m_pAsmModel,
			m_PartsSelect.Type, 
			m_PartsSelect.Num[m_PartsSelect.Type], 
			iSTATUS_CUT_NUM );
	}
	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::MISSION_START ){
		m_pUI->Update( m_enSelectMode );
	}

	assert( m_pAsmModel );
	m_pAsmModel->UpDate();

//	m_pSelectParts->DetatchModel();
//	m_pSelectParts->AttachModel( m_wpResource->GetPartsModels(
//		static_cast< enPARTS >( m_PartsSelect.Type ),
//		static_cast< SKIN_ENUM_TYPE >( m_PartsSelect.Num[ m_PartsSelect.Type ] ) ) );
	assert( m_pSelectParts );
	m_pSelectParts->Update( m_PartsSelect.Type, m_PartsSelect.Num[ m_PartsSelect.Type ] );

}

void clsSCENE_ASSEMBLE::RenderProduct( const D3DXVECTOR3 &vCamPos )
{
	//�p�[�c�`��p.
	clsCAMERA_ASSEMBLE PartsViewCam;
	PartsViewCam.Create();
	PartsViewCam.SetPos( vPARTS_VIEW_CAM_POS );
	PartsViewCam.SetLookPos( vPARTS_VIEW_CAM_LOOK );
	PartsViewCam.AddPos( m_pSelectParts->GetSelectPartsHeight() );

	//���{�`��p.
	clsCAMERA_ASSEMBLE RoboViewCam;
	RoboViewCam.Create();
	RoboViewCam.SetPos( vROBO_VIEW_CAM_POS );
	RoboViewCam.SetLookPos( vROBO_VIEW_CAM_LOOK );
	RoboViewCam.AddPos( m_pAsmModel->GetBonePos( enPARTS::LEG, sBONE_NAME_LEG_TO_CORE ) );


	//�w�i.
	assert( m_upBack );
	SetDepth( false );
	m_upBack->Render();
	SetDepth( true );


	assert( m_pUI );
	SetDepth( false );
	m_pUI->Render( m_enSelectMode, m_PartsSelect.Type, m_PartsSelect.Num[m_PartsSelect.Type] );
	SetDepth( true );

	//�p�[�c�`��.
	SetViewPort( 
		m_pViewPortPartsWindow, 
		PartsViewCam.GetPos(), PartsViewCam.GetLookPos(),
		m_pViewPortPartsWindow->Width, m_pViewPortPartsWindow->Height );
	assert( m_pSelectParts );
	m_pSelectParts->Render( m_mView, m_mProj, m_vLight, PartsViewCam.GetPos(), isMissionStart() );

	//�p�[�c�̃X�e�[�^�X.
	SetViewPort( 
		GetViewPortMainPtr(), 
		m_wpCamera->GetPos(), m_wpCamera->GetLookPos(),
		WND_W, WND_H );
	assert( m_pUI );
	SetDepth( false );
	m_pUI->RenderPartsState( m_enSelectMode, m_PartsSelect.Type, m_PartsSelect.Num[m_PartsSelect.Type] );
	SetDepth( true );


	//���{�`��.
	SetViewPort( 
		m_pViewPortRoboWindow, 
		RoboViewCam.GetPos(), RoboViewCam.GetLookPos(),
		m_pViewPortRoboWindow->Width, m_pViewPortRoboWindow->Height );
	assert( m_pAsmModel );
	//�p�[�c�I�𒆂͑I�����Ă���p�[�c�����点��.
	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ||
		m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS )
	{
		m_pAsmModel->Render( m_mView, m_mProj, m_vLight, RoboViewCam.GetPos(), 
			static_cast< clsASSEMBLE_MODEL::enPARTS_TYPES >( m_PartsSelect.Type ) );
	}
	else{
		m_pAsmModel->Render( m_mView, m_mProj, m_vLight, RoboViewCam.GetPos() );
	}


}

void clsSCENE_ASSEMBLE::RenderUi()
{

	//�{�^���̐���.
	m_wpFont->SetPos( vFONT_BUTTON_POS );
	m_wpFont->SetScale( fFONT_BUTTON_SCALE );
	m_wpFont->Render( iFONT_BUTTON_LINE, iFONT_BUTTON_TEXT_SIZE );


//	//�X�̐���.
//	m_wpFont->SetPos( { 0.0f,  WND_H*0.5f, 0.0f } );
//	m_wpFont->SetScale( 64.0f );
//	m_wpFont->Render( 0, 128 );

}

//�J�[�\���ړ�.
//�J�[�\���ړ��̋��ʓ���.
void clsSCENE_ASSEMBLE::MoveCursor()
{
	m_wpSound->PlaySE( enSE::CURSOL_MOVE );
}


void clsSCENE_ASSEMBLE::MoveCursorUp()
{
	MoveCursor();

	//�p�[�c�J�e�S����I��łȂ��Ȃ�p�[�c��I�΂��Ȃ���.
	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ){
		m_PartsSelect.Num[m_PartsSelect.Type] --;

		m_PartsSelect.Num[m_PartsSelect.Type] = 
			KeepRange( m_PartsSelect.Num[m_PartsSelect.Type], 0, m_vspFile[m_PartsSelect.Type]->GetSizeRow() );
	}
	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS ){
		m_pUI->AddStatusCommentNo( false );
	}
}

void clsSCENE_ASSEMBLE::MoveCursorDown()
{
	MoveCursor();

	//�p�[�c�J�e�S����I��łȂ��Ȃ�p�[�c��I�΂��Ȃ���.
	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ){
		m_PartsSelect.Num[m_PartsSelect.Type] ++;

		m_PartsSelect.Num[m_PartsSelect.Type] = 
			KeepRange( m_PartsSelect.Num[m_PartsSelect.Type], 0, m_vspFile[m_PartsSelect.Type]->GetSizeRow() );
	}
	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS ){
		m_pUI->AddStatusCommentNo( true );
	}

}

void clsSCENE_ASSEMBLE::MoveCursorRight()
{
	MoveCursor();

	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ||
		m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS )
	{
		m_PartsSelect.Type ++;
		m_pUI->AddCommentNoForChangePartsType();

//		//����𒴂�����.
//		if( m_PartsSelect.Type >= clsASSEMBLE_MODEL::ENUM_SIZE ){
//			//�o��.
//			m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::MISSION_START;
//		}

		m_PartsSelect.Type = 
			KeepRange( m_PartsSelect.Type, 0, clsASSEMBLE_MODEL::ENUM_SIZE );
	}
//	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::MISSION_START ){
//	}
}

void clsSCENE_ASSEMBLE::MoveCursorLeft()
{
	MoveCursor();

	//�p�[�c��I��.
	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ||
		m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS )
	{
		m_PartsSelect.Type --;
		m_pUI->AddCommentNoForChangePartsType();

		m_PartsSelect.Type = 
			KeepRange( m_PartsSelect.Type, 0, clsASSEMBLE_MODEL::ENUM_SIZE );
	}
	//�߂点�Ȃ���.
//	//�p�[�c�I���ɖ߂�.
//	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::MISSION_START ){
//		m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::PARTS;
//	}
}

//����.
void clsSCENE_ASSEMBLE::Enter( enSCENE &enNextScene )
{
	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ){
		AssembleParts();
	}
	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::MISSION_START ){
		MissionStart( enNextScene );
	}
}

//�o��.
void clsSCENE_ASSEMBLE::MissionStart( enSCENE &enNextScene )
{
	m_wpSound->PlaySE( enSE::MISSION_START );
	enNextScene = enSCENE::MISSION;

	m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::MISSION_START;
}

//�p�[�c�ύX.
void clsSCENE_ASSEMBLE::AssembleParts()
{
	m_wpSound->PlaySE( enSE::ENTER );

	//�X�e�[�^�X�������ڂ���̂�.
	const int iStatusSize = m_vspFile[ m_PartsSelect.Type ]->GetSizeCol() - iSTATUS_CUT_NUM;

	//�����p�ϐ�.
	vector<int> tmpStatus;
	tmpStatus.reserve( iStatusSize );
	for( int i=0; i<iStatusSize; i++ ){
		//m_vspFile[]�̓Y�����͂ǂ̃p�[�c���A�ł���.
		tmpStatus.push_back( 
			m_vspFile[ m_PartsSelect.Type ]->
				GetDataInt( m_PartsSelect.Num[m_PartsSelect.Type], i + iSTATUS_CUT_NUM ) );
		//GetDataInt()�̑������́A���̃p�[�c���ʂ̉��Ԗڂ̍s���Q�Ƃ���΂悢�̂�.
		//��������iSTATUS_CUT_NUM�𑫂��Ă���̂́A���̕\�ɂ���p�[�c�ԍ��Ɩ��O�͂���Ȃ�����J�b�g���邽�߂ł���.
	}

	//���x���L���X�g������̂͌��Ȃ̂�.
	UCHAR tmpPartsNum = static_cast<UCHAR>( m_PartsSelect.Num[m_PartsSelect.Type] );

	switch( m_PartsSelect.Type )
	{
	case clsASSEMBLE_MODEL::LEG:
		m_wpRoboStatus->ReceiveLeg( tmpStatus,		tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::LEG,		tmpPartsNum );
		break;
	case clsASSEMBLE_MODEL::CORE:
		m_wpRoboStatus->ReceiveCore( tmpStatus,		tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::CORE,	tmpPartsNum );
		break;
	case clsASSEMBLE_MODEL::HEAD:
		m_wpRoboStatus->ReceiveHead( tmpStatus,		tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::HEAD,	tmpPartsNum );
		break;
	case clsASSEMBLE_MODEL::ARMS:
		m_wpRoboStatus->ReceiveArms( tmpStatus,		tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::ARM_L,	tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::ARM_R,	tmpPartsNum );
		break;
	case clsASSEMBLE_MODEL::WEAPON_L:
		m_wpRoboStatus->ReceiveWeaponL( tmpStatus,	tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::WEAPON_L,tmpPartsNum );
		break;
	case clsASSEMBLE_MODEL::WEAPON_R:
		m_wpRoboStatus->ReceiveWeaponR( tmpStatus,	tmpPartsNum );
		m_pAsmModel->AttachModel( enPARTS::WEAPON_R,tmpPartsNum );
		break;
	default:
		break;
	}

	//�����p�ϐ��̕ЂÂ�.
	tmpStatus.clear();
	tmpStatus.shrink_to_fit();
}


//�߂�.
void clsSCENE_ASSEMBLE::Undo( enSCENE &enNextScene )
{
	m_wpSound->PlaySE( enSE::EXIT );
	enNextScene = enSCENE::TITLE;
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

//�J�[�\�����o���ɍ��킹�Ă���Ȃ�true.
bool clsSCENE_ASSEMBLE::isMissionStart()
{
	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::MISSION_START ){
		return false;
	}

	return true;
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

	//UI.
	sprintf_s( strDbgTxt, 
		"SpritePos : x[%f], y[%f]",
		m_pUI->GetUiPos().x, m_pUI->GetUiPos().y );
	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

//	//���{�ꕶ��.[400:-400,200][200:-200,100][50:-50,25]
//	sprintf_s( strDbgTxt, 
//		"Font : x[%f], y[%f], Scale[%f]",
//		setumeiX, setumeiY, m_wpFont->GetScale() );
//	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );

//	//�e�X�g�p�ɐ��l���o��.
//	string tmpsString;
//	tmpsString = m_vspFile[m_PartsSelect.Type]->GetDataString( m_PartsSelect.Num[m_PartsSelect.Type] );
//	const char* tmpcString = tmpsString.c_str();
//	sprintf_s( strDbgTxt, 
//		tmpcString );
//	m_upText->Render( strDbgTxt, 0, iTxtY += iOFFSET );



}
#endif //#if _DEBUG



