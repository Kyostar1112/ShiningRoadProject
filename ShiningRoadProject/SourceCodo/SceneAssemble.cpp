#include "SceneAssemble.h"
#include "WindowBox.h"

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
const D3DXVECTOR3 vROBO_VIEW_CAM_POS  = { 0.0f, 10.0f, -100.0f };
const D3DXVECTOR3 vROBO_VIEW_CAM_LOOK = { 0.0f,-10.0f, 0.0f };
//----- ���{�E�B���h�E�p -----//.

//----- �w�i -----//.
const char* sBACK_SPRITE_PATH = "Data\\Image\\AssembleUi\\AssembleBack.png";
const D3DXVECTOR3 vBACK_POS = { 0.0f, 0.0f, 0.0f };

//----- �w�i -----//.


////----- ��� -----//.
//m_upArrow
const WHSIZE_FLOAT ARROW_DISP = { 14.0f, 36.0f };
const char* sPATH_ARROW = "Data\\Image\\AssembleUi\\Arrow.png";
const char cARROW_FOR_MAX_NUM = 2;

const D3DXVECTOR3 vARROW_POS_TYPE = { -6.0f + 32.0f - ( ARROW_DISP.w * 0.5f ), 122.0f, 0.0f };
const float fARROW_POS_TYPE_OFFSET_X = 6.0f + 6.0f * 120.0f;
const float fARROW_ROLL_ADD = static_cast<float>( M_PI );

const float fARROW_ROLL_PARTS = static_cast<float>( M_PI_2 );
const D3DXVECTOR3 vARROW_POS_PARTS = { 83.0f, 172.0f - ARROW_DISP.w * 0.5f, 0.0f };
const float fARROW_POS_PARTS_OFFSET_Y = ( 4.0f );
const float fARROW_POS_PARTS_OFFSET_Y_RATE_PARTS_MAX = ( 70.0f + 18.0f );
////----- ��� �I��� -----//.




//���b�Z�{�b�N�X.
const float fBOX_ALPHA = 0.75f;
const D3DXVECTOR3 vBOX_POS = { WND_W/2, WND_H/2, 0.0f };//�V�[���ړ�.
const D3DXVECTOR3 vBOX_SIZE = { WND_W/2, WND_H/2, 0.0f };
const D3DXVECTOR3 vBOX_POS_COLOR = { 380.0f, WND_H/2, 0.0f };//�F�ւ�.
const D3DXVECTOR3 vBOX_SIZE_COLOR = { 678.0f, 500.0f, 0.0f };
const float fBOX_BIG_SPD_W = 60.0f;
const float fBOX_BIG_SPD_H = 40.0f;
const clsLINE_BOX::encBEFOR_CHANGE encBOX_APPEAR_CHANGE_MODE = clsLINE_BOX::encBEFOR_CHANGE::WIDTH;
const float fBOX_SMALL_SPD_RATE = 1.0 / 16.0f;
const clsLINE_BOX::encBEFOR_CHANGE encBOX_DISAPPEAR_CHANGE_MODE = clsLINE_BOX::encBEFOR_CHANGE::BOTH;
const int iBOX_MESSAGE_LINE_GO_MISSION = 1;
const int iBOX_MESSAGE_LINE_BACK_TITLE = iBOX_MESSAGE_LINE_GO_MISSION + 1;
const int iBOX_MESSAGE_LINE_COLOR_CHANGE = iBOX_MESSAGE_LINE_BACK_TITLE + 1;


//�F�Q�[�W�g.
const char sCOLOR_GAGE_PATH_BONE[] = "Data\\Image\\AssembleUi\\ColorGageBone.png";
const WHSIZE_FLOAT COLOR_GAGE_SIZE_BONE = { 480.0f, 32.0f };
const D3DXVECTOR3 vCOLOR_GAGE_POS_BONE  = { 420.0f, 220.0f, 0.0f };
const float fCOLOR_GAGE_OFFSET_BONE = COLOR_GAGE_SIZE_BONE.h + 20.0f;
const float fCOLOR_GAGE_OFFSET_BONE_2 =  24.0f;//�p�[�c�̃x�[�X�Ƒ��b�̍��Ԃ̒ǉ��I�t�Z�b�g.
//�Q�[�W�{��.
const char sCOLOR_GAGE_PATH[] = "Data\\Image\\AssembleUi\\ColorGage.png";
const WHSIZE_FLOAT COLOR_GAGE_SIZE = { 32.0f, 32.0f };
const float fCOLOR_GAGE_ALPHA = 0.5f;
const D3DXVECTOR3 vCOLOR_GAGE_COLOR[] = {
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
};

//YesNo.
const float fMESSAGEBOX_BUTTON_X_OFFSET = 100.0f;
const float fMESSAGEBOX_BUTTON_Y = WND_H/2 + 100.0f;
const D3DXVECTOR3 vMESSAGEBOX_YES_BUTTON_POS = { WND_W/2 - fMESSAGEBOX_BUTTON_X_OFFSET, fMESSAGEBOX_BUTTON_Y, 0.0f };
const D3DXVECTOR3 vMESSAGEBOX_NO_BUTTON_POS =  { WND_W/2 + fMESSAGEBOX_BUTTON_X_OFFSET, fMESSAGEBOX_BUTTON_Y, 0.0f };
const WHSIZE_FLOAT MESSAGEBOX_BUTTON_YES_NO_DISP = { 80.0f, 60.0f }; 
const WHSIZE_FLOAT MESSAGEBOX_BUTTON_YES_NO_ANIM = { 2.0f, 2.0f }; 
const char* sMESSAGEBOX_BUTTON_YES_NO_PATH = "Data\\Image\\AssembleUi\\YesNo.png";
const POINTFLOAT MESSAGEBOX_YES_BUTTON_ANIM = { 0.0f, 0.0f };
const POINTFLOAT MESSAGEBOX_NO_BUTTON_ANIM = { 1.0f, 0.0f };
const float fMESSAGEBOX_YES_NO_BUTTON_SELECT_ANIM = 1.0f;


//���{��UI.
const char* sFONT_TEXT_PATH_ASSEMBLE = "Data\\Font\\Text\\TextAssemble.csv";
//�{�^������.
const D3DXVECTOR3 vFONT_BUTTON_POS = { 650.0f, 40.0f, 0.0f };
const float fFONT_BUTTON_SCALE = 14.0f;
const int iFONT_BUTTON_LINE = 0;

//�o�����b�Z�[�W.
const D3DXVECTOR3 vFONT_MESSAGE_BOX_TITLE_POS = { 480.0f, 230.0f, 0.0f };
const float fFONT_MESSAGE_BOX_TITLE_SCALE = 24.0f;

//�F�ւ����b�Z�[�W.
const D3DXVECTOR3 vFONT_MESSAGE_BOX_COLOR_CHANGE = { 250.0f, 140.0f, 0.0f };

//�F�ւ�text.
const float fCOLOR_CHANGE_BOX_IN_TEXT_RGB_SCALE = 2.0f;
const float COLOR_CHANGE_BOX_IN_TEXT_RGB_OFFSET_X = -30.0f;
const float COLOR_CHANGE_BOX_IN_TEXT_RGB_OFFSET_Y = -10.0f;
const string sCOLOR_CHANGE_BOX_IN_TEXT_RGB_TEXT[] = {
	"R",
	"G",
	"B",
	"R",
	"G",
	"B",
}; 

const float fCOLOR_CHANGE_BOX_IN_TEXT_COLOR1_2_SCALE = 2.5f;
D3DXVECTOR2 vCOLOR_CHANGE_BOX_IN_TEXT_COLOR1_2_POS = { 60.0f, 170.0f };
float fCOLOR_CHANGE_BOX_IN_TEXT_COLOR1_2_POS_ADD_Y = fCOLOR_GAGE_OFFSET_BONE * 3 + fCOLOR_GAGE_OFFSET_BONE_2; 
const string sCOLOR_CHANGE_BOX_IN_TEXT_COLOR1_2_TEXT[] = {
	"Color1", "Color2"
};

const char sCOLOR_CHANGE_BOX_IN_SELECT_COLOR_PATH[] = "Data\\Image\\AssembleUi\\ColorSelect.png"; 
const WHSIZE_FLOAT COLOR_CHANGE_BOX_IN_SELECT_COLOR_SIZE = { 24.0f, 24.0f };




//�Y�[�����E.
const float fZOOM_RIMIT_MIN = -100.0f;
const float fZOOM_RIMIT_MAX = 35.0f;



//================================//
//========== �g�݊����N���X ==========//
//================================//
clsSCENE_ASSEMBLE::clsSCENE_ASSEMBLE( clsPOINTER_GROUP* const ptrGroup ) : clsSCENE_BASE( ptrGroup )
	,m_pAsmModel( nullptr )
	,m_pUI( nullptr )
	,m_pViewPortPartsWindow( nullptr )
	,m_pViewPortRoboWindow( nullptr )
	,m_pSelectParts( nullptr )
	,m_iMessageNum( 0 )
	,m_isMessageBoxYes( true )
	,m_isCanControl( false )
	,m_pColorGagesBone()
	,m_enColorGageIndex( clsROBO_STATUS::enCOLOR_GAGE_BASE_R )
	,m_fDistanceAssembleModel( 0.0f )
//	,m_enSelectMode()
{
	m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::PARTS;

	for( char i=0; i<clsROBO_STATUS::enCOLOR_GAGE_size; i++ ){
		m_pColorGagesBone[i] = nullptr;
	}
}

clsSCENE_ASSEMBLE::~clsSCENE_ASSEMBLE()
{
	for( char i=0; i<clsROBO_STATUS::enCOLOR_GAGE_size; i++ ){
		SAFE_DELETE( m_pColorGagesBone[i] );
	}

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

	m_pSelectParts = nullptr;
}

void clsSCENE_ASSEMBLE::CreateProduct()
{
	m_wpFont->Create( sFONT_TEXT_PATH_ASSEMBLE );

	m_wpSound->PlayBGM( enBGM_MAOU2 );


	//�w�i.
	SPRITE_STATE ss;
	ss.Disp = { WND_W, WND_H };
	m_upBack = make_unique< clsSprite2D >();
	m_upBack->Create( m_wpDevice, m_wpContext, sBACK_SPRITE_PATH, ss );
	m_upBack->SetPos( vBACK_POS );

	//���.
	assert( !m_upArrow );
	ss.Disp = ARROW_DISP;
	m_upArrow = make_unique< clsSPRITE2D_CENTER >();
	m_upArrow->Create( m_wpDevice, m_wpContext, sPATH_ARROW, ss );


	//�~�b�V�����V�[���Ɉ����p�����̏�����.
	assert( m_wpRoboStatus );
	m_wpRoboStatus->Clear();

	//UI�̐��p�ϐ�.
	clsASSEMBLE_UI::PARTS_NUM_DATA partsData;
	partsData.resize( clsASSEMBLE_MODEL::ENUM_SIZE );

	//�p�[�c�̃X�e�[�^�X�ǂݍ���.
	UCHAR ucFileMax = clsASSEMBLE_MODEL::ENUM_SIZE;
	m_vspFile.resize( ucFileMax ); 
	for( UCHAR i=0; i<m_vspFile.size(); i++ ){
		if( m_vspFile[i] != nullptr ){
			assert( !"m_spFile[i]�͍쐬�ς݂ł�" );
			continue;
		}
		m_vspFile[i] = make_shared< clsFILE >();
		m_vspFile[i]->Open( sPARTS_STATUS_PASS[i] );

		partsData[i] = m_vspFile[i]->GetSizeRow();
	}

	//��.
	assert( !m_upBox );
	m_upBox = make_unique< clsWINDOW_BOX >( m_wpDevice, m_wpContext );
	m_upBox->SetPos( vBOX_POS );
	m_upBox->SetSize( 0.0f );
	m_upBox->SetAlpha( fBOX_ALPHA );

	//yesno.
	assert( !m_upYesNo );
	ss.Disp = MESSAGEBOX_BUTTON_YES_NO_DISP;
	ss.Anim = MESSAGEBOX_BUTTON_YES_NO_ANIM;
	m_upYesNo = make_unique< clsSPRITE2D_CENTER >();
	m_upYesNo->Create( m_wpDevice, m_wpContext, sMESSAGEBOX_BUTTON_YES_NO_PATH, ss );


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

	//�X�e�[�^�X�̏�����.
	for( m_PartsSelect.Type=0; m_PartsSelect.Type<clsASSEMBLE_MODEL::ENUM_SIZE; m_PartsSelect.Type++ ){
		AssembleParts();
	}
	m_PartsSelect.Type = 0;

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


	//�F�Q�[�W��.
	ss.Disp = COLOR_GAGE_SIZE_BONE;
	ss.Anim = { 1.0f, 1.0f };
	for( char i=0; i<clsROBO_STATUS::enCOLOR_GAGE_size; i++ ){
		assert( !m_pColorGagesBone[i] );
		m_pColorGagesBone[i] = new clsSPRITE2D_CENTER;
		m_pColorGagesBone[i]->Create( m_wpDevice, m_wpContext, sCOLOR_GAGE_PATH_BONE, ss );
		m_pColorGagesBone[i]->SetPos( vCOLOR_GAGE_POS_BONE );
		m_pColorGagesBone[i]->AddPos( { 0.0f, fCOLOR_GAGE_OFFSET_BONE * static_cast<float>( i ), 0.0f } );
		if( i >= clsROBO_STATUS::enCOLOR_GAGE_ARMOR_R ){
			m_pColorGagesBone[i]->AddPos( { 0.0f, fCOLOR_GAGE_OFFSET_BONE_2, 0.0f } );
		}
		m_pColorGagesBone[i]->SetAlpha( 0.0f );
	}

	//�F�Q�[�W.
	ss.Disp = COLOR_GAGE_SIZE;
	for( char i=0; i<clsROBO_STATUS::enCOLOR_GAGE_size; i++ ){
		const float fPOS_RATE = -0.5f;
		assert( !m_pColorGages[i] );
		m_pColorGages[i] = new clsSprite2D;
		m_pColorGages[i]->Create( m_wpDevice, m_wpContext, sCOLOR_GAGE_PATH, ss );
		m_pColorGages[i]->SetPos( m_pColorGagesBone[i]->GetPos() );
		m_pColorGages[i]->AddPos( { COLOR_GAGE_SIZE_BONE.w * fPOS_RATE, COLOR_GAGE_SIZE.h * fPOS_RATE, 0.0f } );
		m_pColorGages[i]->SetAlpha( fCOLOR_GAGE_ALPHA );
	}
	//�F����text.
	for( char i=0; i<clsROBO_STATUS::enCOLOR_GAGE_size; i++ ){
		const float fPOS_RATE = -0.5f;
		assert( !m_upColorTexts[i] );
		m_upColorTexts[i] = make_unique< clsUiText >();
		m_upColorTexts[i]->Create( m_wpContext, WND_W, WND_H, fCOLOR_CHANGE_BOX_IN_TEXT_RGB_SCALE );
		m_upColorTexts[i]->SetPos( { m_pColorGagesBone[i]->GetPos().x, m_pColorGagesBone[i]->GetPos().y } );
		m_upColorTexts[i]->AddPos( { 
			COLOR_GAGE_SIZE_BONE.w * fPOS_RATE + COLOR_CHANGE_BOX_IN_TEXT_RGB_OFFSET_X,
			COLOR_CHANGE_BOX_IN_TEXT_RGB_OFFSET_Y } );
		m_upColorTexts[i]->SetText( sCOLOR_CHANGE_BOX_IN_TEXT_RGB_TEXT[i].c_str() );
	}
	assert( !m_upColorNumText );
	m_upColorNumText = make_unique< clsUiText >();
	m_upColorNumText->Create( m_wpContext, WND_W, WND_H, fCOLOR_CHANGE_BOX_IN_TEXT_COLOR1_2_SCALE );
	m_upColorNumText->SetPos( vCOLOR_CHANGE_BOX_IN_TEXT_COLOR1_2_POS );
	//�F�̑I����.
	assert( !m_upSelectColor );
	ss.Disp = COLOR_CHANGE_BOX_IN_SELECT_COLOR_SIZE;
	m_upSelectColor = make_unique< clsSPRITE2D_CENTER >();
	m_upSelectColor->Create( m_wpDevice, m_wpContext, sCOLOR_CHANGE_BOX_IN_SELECT_COLOR_PATH, ss );


	//�p�[�c�r���[�ɒu���p�[�c.
	assert( !m_pSelectParts );
	m_pSelectParts = new clsPARTS_WINDOW_MODEL( m_wpResource, m_wpRoboStatus );

}

void clsSCENE_ASSEMBLE::UpdateProduct( enSCENE &enNextScene )
{
	assert( m_wpSound );

	//�Ó]���͑���s�\.
	if( m_wpBlackScreen->GetAlpha() ){
		m_isCanControl = false;
	}
	else{
		m_isCanControl = true;
	}

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

	//����.
	if( m_isCanControl ){
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
			Exit();
		}
		//���̃V�[���ւ̃E�B���h�E���o��.
		if( m_wpXInput->isPressEnter( XINPUT_START ) || 
			GetAsyncKeyState( VK_SPACE ) & 0x1 )
		{
			//�E�B���h�E���o���ĂȂ����͎��̃V�[���ւ̃E�B���h�E���o��.
			if( isMessageBoxClose() ){
				AppearMessageBox( clsASSEMBLE_UI::enSELECT_MODE::MISSION_START );
			}
			//�E�B���h�E���o���Ă���Ƃ��͂��̃E�B���h�E�̌���{�^���ɂ��Ȃ�.
			else{
				Enter( enNextScene );
			}
		}
		//�J���[�`�F���W.
		if( m_wpXInput->isPressEnter( XINPUT_BACK ) ||
			GetAsyncKeyState( VK_SHIFT ) & 0x1 )
		{
			//�J����Ȃ�J��.
			if( isMessageBoxClose() ){
				AppearMessageBox( clsASSEMBLE_UI::enSELECT_MODE::COLOR_CHANGE );
			}
			//���ɊJ���Ă��Ă���Ȃ����.
			else{
				DisAppearMessageBox();
			}
		}
		//�X�e�[�^�X�E�B���h�E���B��.
		if( m_wpXInput->isPressEnter( XINPUT_Y ) ){
			SwitchDispStatus();
		}
		//�X�e�[�^�X��comment�ؑ�.
		if( m_wpXInput->isPressEnter( XINPUT_X ) )
		{
			if( m_pUI->isCanSwitchStatusComment() &&
				isMessageBoxClose() )
			{
				if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ){
					ChangeStatusSelect();
				}
				else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS ){
					ChangePartsSelect();
				}
			}
		}
	}

	//���f����].
	const float fMODEL_SPN_SPD = 0.05f;
	if( m_wpXInput->isSlopeStay( XINPUT_RIGHT, false ) ){
		m_pAsmModel->AddRot( { 0.0f, fMODEL_SPN_SPD, 0.0f } );
	}
	if( m_wpXInput->isSlopeStay( XINPUT_LEFT, false ) ){
		m_pAsmModel->AddRot( { 0.0f, -fMODEL_SPN_SPD, 0.0f } );
	}
	//���f���Y�[��.
	const float fMODEL_MOVE_SPD = 5.0f;
	if( m_wpXInput->isSlopeStay( XINPUT_UP, false ) ){
		m_fDistanceAssembleModel += fMODEL_MOVE_SPD;
		if( m_fDistanceAssembleModel > fZOOM_RIMIT_MAX ){
			m_fDistanceAssembleModel = fZOOM_RIMIT_MAX;
		}
	}
	if( m_wpXInput->isSlopeStay( XINPUT_DOWN, false ) ){
		m_fDistanceAssembleModel -= fMODEL_MOVE_SPD;
		if( m_fDistanceAssembleModel < fZOOM_RIMIT_MIN ){
			m_fDistanceAssembleModel = fZOOM_RIMIT_MIN;
		}
	}



	assert( m_pUI );
	m_pUI->Input( m_wpXInput, m_wpDxInput );
	if( isMessageBoxClose() ){
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

	assert( m_pSelectParts );
	m_pSelectParts->SetColors( m_pAsmModel->GetColor() );
	m_pSelectParts->Update( m_PartsSelect.Type, m_PartsSelect.Num[ m_PartsSelect.Type ] );

	assert( m_upBox );
	m_upBox->Update();

}

void clsSCENE_ASSEMBLE::RenderProduct( const D3DXVECTOR3 &vCamPos )
{


}

void clsSCENE_ASSEMBLE::RenderUi()
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
	RoboViewCam.SetPos( vROBO_VIEW_CAM_POS );;
	RoboViewCam.AddPos( { 0.0f, 0.0f, m_fDistanceAssembleModel } );
	RoboViewCam.SetLookPos( vROBO_VIEW_CAM_LOOK );
	RoboViewCam.AddPos( m_pAsmModel->GetBonePos( enPARTS::LEG, sBONE_NAME_LEG_TO_CORE ) );


	//�w�i.
	assert( m_upBack );
	m_upBack->Render();

	//�قƂ�ǂ�UI.
	assert( m_pUI );
	m_pUI->Render( m_enSelectMode, m_PartsSelect.Type, m_PartsSelect.Num[m_PartsSelect.Type] );


	//���.
	assert( m_upArrow );
	//�p�[�c�^�C�v.
	m_upArrow->SetPos( vARROW_POS_TYPE );
	m_upArrow->SetRot( { 0.0f, 0.0f, 0.0f } );
	for( char i=0; i<cARROW_FOR_MAX_NUM; i++ ){
		m_upArrow->Render();
		m_upArrow->AddPos( { fARROW_POS_TYPE_OFFSET_X, 0.0f, 0.0f } );
		m_upArrow->AddRot( { 0.0f, 0.0f, fARROW_ROLL_ADD } );
	}
	//�e�p�[�c.m_vspFile
	m_upArrow->SetPos( vARROW_POS_PARTS );
	m_upArrow->SetRot( { 0.0f, 0.0f, fARROW_ROLL_PARTS } );
	//���I�����Ă���p�[�c�̍ő吔.
	const float fPARTS_MAX = static_cast<float>( m_vspFile[ m_PartsSelect.Type ]->GetSizeRow() );
	for( char i=0; i<cARROW_FOR_MAX_NUM; i++ ){
		m_upArrow->Render();
		m_upArrow->AddPos( { 0.0f, fARROW_POS_PARTS_OFFSET_Y, 0.0f } );
		m_upArrow->AddPos( { 
			0.0f, 
			fARROW_POS_PARTS_OFFSET_Y_RATE_PARTS_MAX * fPARTS_MAX, 
			0.0f } );
		m_upArrow->AddRot( { 0.0f, 0.0f, fARROW_ROLL_ADD } );
	}

	//�{�^���̐���.
	assert( m_wpFont );
	m_wpFont->SetPos( vFONT_BUTTON_POS );
	m_wpFont->SetScale( fFONT_BUTTON_SCALE );
	m_wpFont->Render( iFONT_BUTTON_LINE );



	//�p�[�c�`��.
	SetDepth( true );
	SetViewPort( 
		m_pViewPortPartsWindow, 
		PartsViewCam.GetPos(), PartsViewCam.GetLookPos(),
		m_pViewPortPartsWindow->Width, m_pViewPortPartsWindow->Height );
	assert( m_pSelectParts );
	m_pSelectParts->Render( m_mView, m_mProj, m_vLight, PartsViewCam.GetPos(), isMessageBoxClose() );


	//���{�`��.
	SetViewPort( 
		m_pViewPortRoboWindow, 
		RoboViewCam.GetPos(), RoboViewCam.GetLookPos(),
		m_pViewPortRoboWindow->Width, m_pViewPortRoboWindow->Height );
	assert( m_pAsmModel );
	//�p�[�c�I�𒆂͑I�����Ă���p�[�c�����点��.
	if( isMessageBoxClose() )
	{
		m_pAsmModel->Render( m_mView, m_mProj, m_vLight, RoboViewCam.GetPos(), 
			static_cast< clsASSEMBLE_MODEL::enPARTS_TYPES >( m_PartsSelect.Type ) );
	}
	else{
		m_pAsmModel->Render( m_mView, m_mProj, m_vLight, RoboViewCam.GetPos() );
	}
	SetDepth( false );



	//�p�[�c�̃X�e�[�^�X.
	SetViewPort( 
		GetViewPortMainPtr(), 
		m_wpCamera->GetPos(), m_wpCamera->GetLookPos(),
		WND_W, WND_H );
	assert( m_pUI );
	m_pUI->RenderPartsState( m_enSelectMode, m_PartsSelect.Type, m_PartsSelect.Num[m_PartsSelect.Type] );


	//��.
	assert( m_upBox );
	m_upBox->Render();

	//���b�Z�{�b�N�X�̏�ɒu����������.
	if( m_upBox->isStopChange() && m_upBox->GetSize().x ){
		D3DXVECTOR3 tmpMessagePos = vFONT_MESSAGE_BOX_TITLE_POS;
		//�F�ւ�.
		if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::COLOR_CHANGE ){
			tmpMessagePos = vFONT_MESSAGE_BOX_COLOR_CHANGE;
			assert( m_upSelectColor );
			const D3DXVECTOR3 vADD_SELECT_COLOR_OFFSET = { 10.0f, 2.0f, 0.0f };
			m_upSelectColor->SetPos( m_pColorGagesBone[ m_enColorGageIndex ]->GetPos() );
			m_upSelectColor->AddPos( { m_upColorTexts[0]->GetPos().x - m_pColorGagesBone[0]->GetPos().x, 0.0f, 0.0f } );
			m_upSelectColor->AddPos( vADD_SELECT_COLOR_OFFSET );
			m_upSelectColor->Render();
			for( char i=0; i<clsROBO_STATUS::enCOLOR_GAGE_size; i++ ){
				m_pColorGagesBone[i]->Render();
				m_pColorGages[i]->SetScale( { 
					m_pAsmModel->GetColorGradation( static_cast<clsROBO_STATUS::enCOLOR_GAGE>( i ) ) * ( COLOR_GAGE_SIZE_BONE.w / COLOR_GAGE_SIZE.w ),
					1.0f, 
					1.0f } );
 				m_pColorGages[i]->SetColor( vCOLOR_GAGE_COLOR[i] );
				m_pColorGages[i]->Render();
				m_upColorTexts[i]->Render();

				int tnpIndex = 0;
				m_upColorNumText->SetPos( vCOLOR_CHANGE_BOX_IN_TEXT_COLOR1_2_POS );
				m_upColorNumText->SetText( sCOLOR_CHANGE_BOX_IN_TEXT_COLOR1_2_TEXT[ tnpIndex ++ ].c_str() );
				m_upColorNumText->Render();
				m_upColorNumText->AddPos( { 0.0f, fCOLOR_CHANGE_BOX_IN_TEXT_COLOR1_2_POS_ADD_Y } );
				m_upColorNumText->SetText( sCOLOR_CHANGE_BOX_IN_TEXT_COLOR1_2_TEXT[ tnpIndex ++ ].c_str() );
				m_upColorNumText->Render();
			}
		}
		//�V�[���ړ�.
		else {
			//�I�����̃{�^��.
			//yes.
			POINTFLOAT tmpAnim = MESSAGEBOX_YES_BUTTON_ANIM;
			if( m_isMessageBoxYes ){
				tmpAnim.y = fMESSAGEBOX_YES_NO_BUTTON_SELECT_ANIM;
			}
			m_upYesNo->SetPos( vMESSAGEBOX_YES_BUTTON_POS );
			m_upYesNo->SetAnim( tmpAnim );
			m_upYesNo->Render();
			//no.
			tmpAnim = MESSAGEBOX_NO_BUTTON_ANIM;
			if( !m_isMessageBoxYes ){
				tmpAnim.y = fMESSAGEBOX_YES_NO_BUTTON_SELECT_ANIM;
			}
			m_upYesNo->SetPos( vMESSAGEBOX_NO_BUTTON_POS );
			m_upYesNo->SetAnim( tmpAnim );
			m_upYesNo->Render();
		}
		//�I�����̃^�C�g��.
		m_wpFont->SetPos( tmpMessagePos );
		m_wpFont->SetScale( fFONT_MESSAGE_BOX_TITLE_SCALE );
		m_wpFont->Render( m_iMessageNum );
	}

}

//�J�[�\���ړ�.
//�J�[�\���ړ��̋��ʓ���.
void clsSCENE_ASSEMBLE::MoveCursor()
{
//	m_wpSound->PlaySE( enSE_CURSOL_MOVE );
}


void clsSCENE_ASSEMBLE::MoveCursorUp()
{
	MoveCursor();

	//�p�[�c�J�e�S����I��łȂ��Ȃ�p�[�c��I�΂��Ȃ���.
	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ){
		m_wpSound->PlaySE( enSE_CURSOL_MOVE );

		m_PartsSelect.Num[m_PartsSelect.Type] --;

		m_PartsSelect.Num[m_PartsSelect.Type] = 
			LoopRange( m_PartsSelect.Num[m_PartsSelect.Type], 0, m_vspFile[m_PartsSelect.Type]->GetSizeRow() );
	}
	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS ){
		m_wpSound->PlaySE( enSE_CURSOL_MOVE );
		m_pUI->AddStatusCommentNo( false );
	}
	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::COLOR_CHANGE ){
		m_wpSound->PlaySE( enSE_CURSOL_MOVE );

		m_enColorGageIndex = static_cast<clsROBO_STATUS::enCOLOR_GAGE>( m_enColorGageIndex - 1 );
		m_enColorGageIndex = LoopRange( m_enColorGageIndex, clsROBO_STATUS::enCOLOR_GAGE_BASE_R, clsROBO_STATUS::enCOLOR_GAGE_size );
	}
}

void clsSCENE_ASSEMBLE::MoveCursorDown()
{
	MoveCursor();

	//�p�[�c�J�e�S����I��łȂ��Ȃ�p�[�c��I�΂��Ȃ���.
	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ){
		m_wpSound->PlaySE( enSE_CURSOL_MOVE );

		m_PartsSelect.Num[m_PartsSelect.Type] ++;

		m_PartsSelect.Num[m_PartsSelect.Type] = 
			LoopRange( m_PartsSelect.Num[m_PartsSelect.Type], 0, m_vspFile[m_PartsSelect.Type]->GetSizeRow() );
	}
	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS ){
		m_wpSound->PlaySE( enSE_CURSOL_MOVE );
		m_pUI->AddStatusCommentNo( true );
	}
	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::COLOR_CHANGE ){
		m_wpSound->PlaySE( enSE_CURSOL_MOVE );

		m_enColorGageIndex = static_cast<clsROBO_STATUS::enCOLOR_GAGE>( m_enColorGageIndex + 1 );
		m_enColorGageIndex = LoopRange( m_enColorGageIndex, clsROBO_STATUS::enCOLOR_GAGE_BASE_R, clsROBO_STATUS::enCOLOR_GAGE_size );
	}

}

void clsSCENE_ASSEMBLE::MoveCursorRight()
{
	MoveCursor();

	//�p�[�c�I��.
	if( isMessageBoxClose() ){
		m_wpSound->PlaySE( enSE_CURSOL_MOVE );
		m_PartsSelect.Type ++;
		m_pUI->AddCommentNoForChangePartsType();


		m_PartsSelect.Type = 
			LoopRange( m_PartsSelect.Type, 0, clsASSEMBLE_MODEL::ENUM_SIZE );
	}
	//���b�Z�{�b�N�X�̑I����.
	else{
		if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::MISSION_START ||
			m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::TITLE_BACK )
		{
			if( m_isMessageBoxYes ){
				m_wpSound->PlaySE( enSE_CURSOL_MOVE );
				m_isMessageBoxYes = false;
			}
		}
		else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::COLOR_CHANGE ){
			m_wpSound->PlaySE( enSE_CURSOL_MOVE );
			AddRoboColor( true );
		}
	}
}

void clsSCENE_ASSEMBLE::MoveCursorLeft()
{
	MoveCursor();

	//�p�[�c��I��.
	if( isMessageBoxClose() ){
		m_wpSound->PlaySE( enSE_CURSOL_MOVE );
		m_PartsSelect.Type --;
		m_pUI->AddCommentNoForChangePartsType();

		m_PartsSelect.Type = 
			LoopRange( m_PartsSelect.Type, 0, clsASSEMBLE_MODEL::ENUM_SIZE );
	}
	//���b�Z�{�b�N�X�̑I����.
	else{
		if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::MISSION_START ||
			m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::TITLE_BACK )
		{
			if( !m_isMessageBoxYes ){
				m_wpSound->PlaySE( enSE_CURSOL_MOVE );
				m_isMessageBoxYes = true;
			}
		}
		else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::COLOR_CHANGE ){
			m_wpSound->PlaySE( enSE_CURSOL_MOVE );
			AddRoboColor( false );
		}
	}
}



//����.
void clsSCENE_ASSEMBLE::Enter( enSCENE &enNextScene )
{
//	m_wpSound->PlaySE( enSE::ENTER );

	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ){
		m_wpSound->PlaySE( enSE_ENTER );
		AssembleParts();
	}
	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::MISSION_START ){
		if( m_isMessageBoxYes ){ 
			MissionStart( enNextScene );
		}
		else{
			DisAppearMessageBox();
		}
	}
	else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::TITLE_BACK ){
		if( m_isMessageBoxYes ){ 
			TitleBack( enNextScene );
		}
		else{
			DisAppearMessageBox();
		}
	}
}
//�L�����Z��.
void clsSCENE_ASSEMBLE::Exit()
{
	//�Ȃ��Ƃ�.
	if( isMessageBoxClose() ){
		//�p�[�c��I��ł���Ȃ�.
		if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::PARTS ){
			//�E�B���h�E���o��.
			AppearMessageBox( clsASSEMBLE_UI::enSELECT_MODE::TITLE_BACK );
		}
		//�X�e�[�^�X�����Ă���Ȃ�.
		else if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::STATUS ){
			//�p�[�c�Z���N�g�ɖ߂�.
			ChangePartsSelect();
		}
	}
	//�E�B���h�E������Ƃ�.
	else{
		//�E�B���h�E������.
		DisAppearMessageBox();
	}
}

//�F�ւ�( ���E�L�[�������ꂽ ).
void clsSCENE_ASSEMBLE::AddRoboColor( const bool isIncrement )
{
//	unsigned int uiColorChangeNum = 0;
//	switch( m_enColorGageIndex )
//	{
//	case clsASSEMBLE_MODEL::enCOLOR_GAGE_BASE_R:
//	case clsASSEMBLE_MODEL::enCOLOR_GAGE_BASE_G:
//	case clsASSEMBLE_MODEL::enCOLOR_GAGE_BASE_B:
//		uiColorChangeNum = 0;
//		break;
//
//	case clsASSEMBLE_MODEL::enCOLOR_GAGE_ARMOR_R:
//	case clsASSEMBLE_MODEL::enCOLOR_GAGE_ARMOR_G:
//	case clsASSEMBLE_MODEL::enCOLOR_GAGE_ARMOR_B:
//		uiColorChangeNum = 1;
//		break;
//
//	default:
//		return;
//	}

	if( m_enColorGageIndex >= clsROBO_STATUS::enCOLOR_GAGE::enCOLOR_GAGE_size ){
		return;
	}

	assert( m_pAsmModel );
	//�E.
	if( isIncrement ){
		m_pAsmModel->IncrementColor( m_enColorGageIndex );
	}
	//��.
	else{
		m_pAsmModel->DecrementColor( m_enColorGageIndex );
	}

	//�F�̕ۑ�.
	for( char i=0; i<clsROBO_STATUS::enCOLOR_GAGE_size; i++ ){
		clsROBO_STATUS::enCOLOR_GAGE tmpIndex = static_cast<clsROBO_STATUS::enCOLOR_GAGE>( i );
		int iColorRank = m_pAsmModel->GetColorRank( tmpIndex );
		m_wpRoboStatus->SetColorRank( tmpIndex, iColorRank );
	}
}



//�o��.
void clsSCENE_ASSEMBLE::MissionStart( enSCENE &enNextScene )
{
	m_wpSound->PlaySE( enSE_MISSION_START );
	m_wpSound->PlaySE( enSE_ENTER );

	enNextScene = enSCENE::MISSION;
	m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::MISSION_START;

	m_wpSound->PlaySE( enSE_MISSION_START );
}

//�p�[�c�ύX.
void clsSCENE_ASSEMBLE::AssembleParts()
{
//	m_wpSound->PlaySE( enSE_ENTER );

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
void clsSCENE_ASSEMBLE::TitleBack( enSCENE &enNextScene )
{
	m_wpSound->PlaySE( enSE_EXIT );
	enNextScene = enSCENE::TITLE;
}








//�͈͓��Ɏ��߂�( �p�[�c�̑I�������I�[�o�[���Ȃ��悤�ɂ��� ).
//min�͂��̐��l��菬�����Ȃ�Ȃ��Amax�͂���ȏ�ɂ͂Ȃ�Ȃ�.
// min <= t < max.
template<class T, class MIN, class MAX >
T clsSCENE_ASSEMBLE::LoopRange( T t, const MIN min, const MAX max ) const
{
	int num = static_cast<int>( t );
	int Min = static_cast<int>( min );
	int Max = static_cast<int>( max );
	
//	if( Min > num ){
//		num = Min;
//	}
//	else if( num >= Max ){
//		num = Max - 1;
//	}
	if( Min > num ){
		num = Max - 1;
	}
	else if( num >= Max ){
		num = Min;
	}

	return static_cast<T>( num );
}

//�J�[�\�����o���ɍ��킹�Ă���Ȃ�true.
bool clsSCENE_ASSEMBLE::isMessageBoxClose()
{
	if( m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::MISSION_START ||
		m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::TITLE_BACK ||
		m_enSelectMode == clsASSEMBLE_UI::enSELECT_MODE::COLOR_CHANGE )
	{
		return false;
	}

	return true;
}

//���b�Z�{�b�N�X�o��.
void clsSCENE_ASSEMBLE::AppearMessageBox( 
	const clsASSEMBLE_UI::enSELECT_MODE encMode )
{
	m_upBox->AddChangeData( fBOX_BIG_SPD_W, fBOX_BIG_SPD_H, encBOX_APPEAR_CHANGE_MODE );
	m_enSelectMode = encMode;
	if( encMode == clsASSEMBLE_UI::enSELECT_MODE::MISSION_START ){
		m_wpSound->PlaySE( enSE_WIN_APP );
		m_iMessageNum = iBOX_MESSAGE_LINE_GO_MISSION;
		m_upBox->SetPos( vBOX_POS );
		m_upBox->SetSizeTarget( vBOX_SIZE );
	}
	else if( encMode == clsASSEMBLE_UI::enSELECT_MODE::TITLE_BACK ){
		m_wpSound->PlaySE( enSE_WIN_APP );
		m_iMessageNum = iBOX_MESSAGE_LINE_BACK_TITLE;
		m_upBox->SetPos( vBOX_POS );
		m_upBox->SetSizeTarget( vBOX_SIZE );
	}
	else if( encMode == clsASSEMBLE_UI::enSELECT_MODE::COLOR_CHANGE ){
		m_wpSound->PlaySE( enSE_WIN_APP );
		m_iMessageNum = iBOX_MESSAGE_LINE_COLOR_CHANGE;
		m_upBox->SetPos( vBOX_POS_COLOR );
		m_upBox->SetSizeTarget( vBOX_SIZE_COLOR );
		for( char i=0; i<clsROBO_STATUS::enCOLOR_GAGE_size; i++ ){
			m_pColorGagesBone[i]->SetAlpha( 1.0f );
		}
		m_enColorGageIndex = clsROBO_STATUS::enCOLOR_GAGE_BASE_R;
	}
}
//���b�Z�{�b�N�X����.
void clsSCENE_ASSEMBLE::DisAppearMessageBox()
{
	m_wpSound->PlaySE( enSE_WIN_DISAPP );

	m_upBox->SetSizeTarget( { 0.0f, 0.0f, 0.0f } );
	m_upBox->AddChangeData( 
		m_upBox->GetSize().x * fBOX_SMALL_SPD_RATE, 
		m_upBox->GetSize().y * fBOX_SMALL_SPD_RATE, 
		encBOX_DISAPPEAR_CHANGE_MODE );

	//����.
	for( char i=0; i<clsROBO_STATUS::enCOLOR_GAGE_size; i++ ){
		m_pColorGagesBone[i]->SetAlpha( 0.0f );
	}

	//�I������I�ׂ�悤�ɖ߂�.
	m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::PARTS;
	//������.
	m_isMessageBoxYes = true;
}


//�X�e�[�^�X�̕\����\���ؑ�.
void clsSCENE_ASSEMBLE::SwitchDispStatus()
{
	//�E�B���h�E���o���Ă�Ƃ��͖���.
	if( !isMessageBoxClose() ){
		return;
	}

	m_wpSound->PlaySE( enSE_CURSOL_MOVE );
	m_pUI->SwitchDispStatusComment();
	m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::PARTS;
}

//�p�[�c�I���ƃX�e�[�^�X�I���̐؂�ւ�.
void clsSCENE_ASSEMBLE::ChangePartsSelect()
{
	m_wpSound->PlaySE( enSE_EXIT );
	m_pUI->SwitchStatusComment();
	m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::PARTS;
}

void clsSCENE_ASSEMBLE::ChangeStatusSelect()
{
	m_wpSound->PlaySE( enSE_ENTER );
	m_pUI->SwitchStatusComment();
	m_enSelectMode = clsASSEMBLE_UI::enSELECT_MODE::STATUS;
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



