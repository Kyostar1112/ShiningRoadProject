#include "AssembleUi.h"

#include "OperationString.h"
//#include <string>


//�t�@�C�������邩���ׂ�@�\�����.


using namespace std;


#define DEBUG_SPRITE_NAME m_vupStatusText[0]


//----- �p�[�c�J�e�S�� -----//.
//�p�[�c�J�e�S���T�C�Y.
const WHSIZE_FLOAT PARTS_TYPE_SIZE = { 102.0f, 70.0f };
//�p�[�c�J�e�S��UI�̊�ʒu.
const D3DXVECTOR3 vINIT_POS_PARTS_TYPE = { 32.0f, 87.0f, 0.0f };
//�p�[�c�J�e�S���̍��W�̍�.
const float fOFFSET_POS_X_PARTS_TYPE = PARTS_TYPE_SIZE.w + 18.0f;
//�p�[�c�J�e�S���ւ̃p�X.
const char* sPATH_PARTS_TYPE = "Data\\Image\\AssembleUi\\";
//�J�e�S���̐�.
const char cPARTS_TYPE_NUM = 6;
//�p�[�c�J�e�S���摜�p�X( sPATH_PARTS_TYPE�ɂ������� ).
const string sPATH_PARTS_TYPE_CHILDREN[ cPARTS_TYPE_NUM ] =
{
	"LegType.png", "CoreType.png", "HeadType.png", "ArmsType.png", "WeaponLeftType.png" ,"WeaponRightType.png" 
};
//----- �p�[�c�J�e�S�� �I��� -----//.

//�I�𒆃p�[�c�J�e�S���p�X.
const char* sPATH_SELECT_PARTS_TYPE = "Data\\Image\\AssembleUi\\SelectPartsType.png";
const float fALPHA_SELECT_PARTS_TYPE = 0.5f;


//----- �o���{�^�� -----//.
const char* sPATH_MISSION_START_BUTTON = "Data\\Image\\AssembleUi\\MissionStart.png";
const WHSIZE_FLOAT SIZE_MISSION_START_BUTTON = { 120.0f, 80.0f };
const D3DXVECTOR3 vINIT_POS_MISSION_START_BUTTON = 
	{ vINIT_POS_PARTS_TYPE.x + fOFFSET_POS_X_PARTS_TYPE * cPARTS_TYPE_NUM, //700.75f.<=760.0f
	vINIT_POS_PARTS_TYPE.y,
	0.0f };


//----- �o���{�^�� �I��� -----//.



//----- �e�p�[�cUI -----//.
//�T�C�Y.
const WHSIZE_FLOAT PARTS_ICON_SIZE = PARTS_TYPE_SIZE;
//UI���m�̌���.
const float fPARTS_ICON_OFFSET = 18.0f;
//�J�e�S������̌���.
const float fPARTS_ICON_OFFSET_FROM_PARTS_TYPE = 18.0f;
//��ʒu.
const D3DXVECTOR3 vINIT_POS_PARTS_ICON = { vINIT_POS_PARTS_TYPE.x, 176.0f, 0.0f };

//�e�p�[�c�ւ̃A�C�R���p�X�ւ̓���.
const string sPATH_PARTS_ICON_ROOT = "Data\\RoboParts\\";
//�e�p�[�c�ւ̃A�C�R���p�X�ւ̓���( �e�p�[�c ).
const string sPATH_PARTS_ICON_PARTS[] = {
	"Leg", "Core", "Head", "Arms", "Weapon", "Weapon"
};
//�A�C�R���̃t�@�C����.
const char* sPATH_PARTS_ICON_END = "\\Icon.png";


//�G���[�摜.
const string sNO_DATA_FILE_NAME = "Data\\Image\\PartsIcon\\NoData.png";
//----- �e�p�[�cUI �I��� -----//.

//�I�𒆊e�p�[�cUI�p�X.
const char* sPATH_SELECT_PARTS_NUM = "Data\\Image\\AssembleUi\\SelectPartsNum.png";
const float fALPHA_SELECT_PARTS_NUM = fALPHA_SELECT_PARTS_TYPE;



//----- �p�[�c�E�B���h�E -----//.
//478.25f.
const D3DXVECTOR3 vINIT_POS_PARTS_WINDOW = 
	{ 153.0f, 176.0f, 0.0f };
 const WHSIZE_FLOAT INIT_SIZE_PARTS_WINDOW  = { 576.0f, 482.0f };
const char* sPATH_PARTS_WINDOW = "Data\\Image\\AssembleUi\\PartsWindow.png";

//����( �X�e�[�^�X�E�B���h�E����ɂ��Ă��� ).
const float TEXT_SCALE_PARTS_NAME = 2.0f;
const D3DXVECTOR2 vTEXT_POS_PARTS_NAME = {
	vINIT_POS_PARTS_WINDOW.x + 4.5f,
	vINIT_POS_PARTS_WINDOW.y + 16.25f 
};
const float fPARTS_WINDOW_ALPHA = 0.5f;
//----- �p�[�c�E�B���h�E�I��� -----//.


//----- ���{�E�B���h�E -----//.
const char* sROBO_WINDOW_PATH = "Data\\Image\\AssembleUi\\RoboWindow.png";
const WHSIZE_FLOAT INIT_SIZE_ROBO_WINDOW  = { 490.0f, 570.0f };
const D3DXVECTOR3 INIT_POS_ROBO_WINDOW = { 753.0f, 87.0f, 0.0f };
const float fROBO_WINDOW_ALPHA = 0.5f;
//----- ���{�E�B���h�E �I��� -----//.




//----- �X�e�[�^�X�E�B���h�E -----//.
const WHSIZE_FLOAT INIT_SIZE_STATUS_WINDOW  = { INIT_SIZE_PARTS_WINDOW.w, 24.0f };//360.0f.
const D3DXVECTOR3 vINIT_POS_STATUS_WINDOW = { 
	vINIT_POS_PARTS_WINDOW.x, 
	vINIT_POS_PARTS_WINDOW.y + INIT_SIZE_PARTS_WINDOW.h - INIT_SIZE_STATUS_WINDOW.h, 
	0.0f };//179.5f;
const char* sPATH_STATUS_WINDOW = "Data\\Image\\AssembleUi\\StatusWindow.png";
const float fSTATUS_WINDOW_ALPHA = 0.75f;
const int iSTATUS_NUM_MAX = 11;//�X�e�[�^�X�̍ő吔.

//�X�e�[�^�X����.
//���̑��̃^�C�g��.
const float TEXT_SCALE_STATUS_TITLE = 2.0f;
const D3DXVECTOR2 vTEXT_POS_STATUS_TITLE_OFFSET_TO_STATUS_WINDOW = { 4.5f, 8.25f };
const D3DXVECTOR2 vTEXT_POS_STATUS_TITLE = {
	vINIT_POS_STATUS_WINDOW.x + vTEXT_POS_STATUS_TITLE_OFFSET_TO_STATUS_WINDOW.x,
	vINIT_POS_STATUS_WINDOW.y + vTEXT_POS_STATUS_TITLE_OFFSET_TO_STATUS_WINDOW.y };
const char* sSTATUS_TITLE_TEXT = "Parts Status";

//��s�ڈȍ~�̂��ꕝ.
const float fTEXT_POS_Y_OFFSET_STATUS = INIT_SIZE_STATUS_WINDOW.h;
//�����T�C�Y.
const float fTEXT_SCALE_STATUS = 1.5f;
//���ڕ����̍��W.
const D3DXVECTOR2 vTEXT_POS_OFFSET_TO_STATUS_WINDOW = { 5.0f, 8.75f };//������̂���.
const D3DXVECTOR2 vTEXT_POS_STATUS = {
	vINIT_POS_STATUS_WINDOW.x + vTEXT_POS_OFFSET_TO_STATUS_WINDOW.x,
	vINIT_POS_STATUS_WINDOW.y - vTEXT_POS_OFFSET_TO_STATUS_WINDOW.y 
	+ ( 12.0f ) };
//�l�����̍��W.
const D3DXVECTOR2 vTEXT_POS_STATUS_NUM = 
	{ vTEXT_POS_STATUS.x + INIT_SIZE_STATUS_WINDOW.w - 12.0f, vTEXT_POS_STATUS.y };
//----- �X�e�[�^�X�E�B���h�E�I��� -----//.



//----- �w�b�_�[�ƃt�b�^�[ -----//.
const char* sHEADER_FILE_PATH = "Data\\Image\\AssembleUi\\Header.png";
const char* sFOOTER_FILE_PATH = "Data\\Image\\AssembleUi\\Footer.png";
const WHSIZE_FLOAT INIT_SIZE_HEADER  = { WND_W, 54.0f };
const WHSIZE_FLOAT INIT_SIZE_FOOTER  = { WND_W, 30.0f };
const D3DXVECTOR3 INIT_POS_HEADER = { 0.0f, 14.0f, 0.0f };
const D3DXVECTOR3 INIT_POS_FOOTER = { 0.0f, WND_H - INIT_SIZE_FOOTER.h - 15.0f, 0.0f };
//����.
const float fTEXT_SCALE_HEADER = 4.0f;
const float fTEXT_SCALE_FOOTER = 1.0f;
const D3DXVECTOR2 vTEXT_POS_OFFSET_HEADER = { 57.0f, 7.0f };//�摜�Ƃ̂���.
const D3DXVECTOR2 vTEXT_POS_OFFSET_FOOTER = { 57.0f, 6.0f };
const D3DXVECTOR2 vTEXT_POS_HEADER = { INIT_POS_HEADER.x + vTEXT_POS_OFFSET_HEADER.x, INIT_POS_HEADER.y + vTEXT_POS_OFFSET_HEADER.y };
const D3DXVECTOR2 vTEXT_POS_FOOTER = { INIT_POS_FOOTER.x + vTEXT_POS_OFFSET_FOOTER.x, INIT_POS_FOOTER.y + vTEXT_POS_OFFSET_FOOTER.y };
const char* sHEADER_TEXT = "ASSEMBLE";
const char* sFOOTER_TEXT = "Enter : B";
const float fHEADER_ALPHA = 0.5f;
const float fFOOTER_ALPHA = 0.5f;
//----- �w�b�_�[�ƃt�b�^�[ �I��� -----//.









#if _DEBUG
//�ڈ�.
const char* sPATH_DESIGN = "Data\\Image\\AssembleDesign.png";
const D3DXVECTOR3 vINIT_POS_DESIGN = { 0.0f, 0.0f, 0.0f };
const float fINIT_SCALE_DESIGN = 0.1875f;
#endif//#if _DEBUG



//�p�[�c�����i�[����Ă���f�[�^�ԍ�.
const int iSTATUS_PARTS_NAME_NUM = 1;//.
//�B���Ȃ��X�e�[�^�X�̐�.
const int iOPEN_STATUS_NUM[] =
{ 5, 8, 4, 5, 9, 9 };
//�X�e�[�^�X�̖��O.
const char* sHP_NAME = "Armor Point";
const string sSTATUS_NAME_LEG[] = 
	{ sHP_NAME, "Walk Speed", "Stability", "Turning", "Jump Power"  };
const string sSTATUS_NAME_CORE[] = 
	{ sHP_NAME, "EN Capacity", "EN Output", "Boost Horizontal Power", "Boost Horizontal Cost", "Boost Vertical Power", "Boost Vertical Cost", "Activity Time" };
const string sSTATUS_NAME_HEAD[] = 
	{ sHP_NAME, "Search", "Lock on Speed", "Lock on Range" };
const string sSTATUS_NAME_ARMS[] = 
	{ sHP_NAME, "Aiming", "Boost Quick Power", "Boost Quick Cost", "Boost Quick Time" };
const string sSTATUS_NAME_WEAPON[] = 
	{ "Attack Power", "Bullet Speed", "Bullet Range", "EN Cost", "Load Time", "Lock on Time", "Stability of Shooting", "Magazine Load Time", "Bullets Num" };




clsASSEMBLE_UI::clsASSEMBLE_UI()
	:m_iStatusNum( 0 )
	,m_isDispStatus( true )
{
	//����for���p.
	const string* tmpStatusNamePtr[enPARTS_TYPE_SIZE] =
		{ &sSTATUS_NAME_LEG[0], &sSTATUS_NAME_CORE[0], &sSTATUS_NAME_HEAD[0], &sSTATUS_NAME_ARMS[0], &sSTATUS_NAME_WEAPON[0], &sSTATUS_NAME_WEAPON[0] };

	//�\�����镶����̃Z�b�g.
	for( int i=0; i<enPARTS_TYPE_SIZE; i++ ){
		//�\���X�e�[�^�X�̐������낦��.
		m_vsStatusNameBox[i].resize( iOPEN_STATUS_NUM[i] );

		//�X�e�[�^�X����������Z�b�g.
		for( int j=0; j<iOPEN_STATUS_NUM[i]; j++ ){
			m_vsStatusNameBox[i][j] = tmpStatusNamePtr[i][j];
		}
	}

	m_ViewPortPartsWindow.Width		= INIT_SIZE_PARTS_WINDOW.w;
	m_ViewPortPartsWindow.Height	= INIT_SIZE_PARTS_WINDOW.h;
	m_ViewPortPartsWindow.MinDepth	= 0.0f;
	m_ViewPortPartsWindow.MaxDepth	= 1.0f;
	m_ViewPortPartsWindow.TopLeftX	= vINIT_POS_PARTS_WINDOW.x;
	m_ViewPortPartsWindow.TopLeftY	= vINIT_POS_PARTS_WINDOW.y;
}

clsASSEMBLE_UI::~clsASSEMBLE_UI()
{
#if _DEBUG
	if( m_upDegine ){
		m_upDegine.reset( nullptr );
	}
#endif//#if _DEBUG

	for( unsigned int i=0; i<m_vupStatusNumText.size(); i++ ){
		if( m_vupStatusNumText[i] ){
			m_vupStatusNumText[i].reset( nullptr );
		}
	}
	m_vupStatusNumText.clear();
	m_vupStatusNumText.shrink_to_fit();

	for( unsigned int i=0; i<m_vupStatusText.size(); i++ ){
		if( m_vupStatusText[i] ){
			m_vupStatusText[i].reset( nullptr );
		}
	}

	m_vupStatusText.clear();
	m_vupStatusText.shrink_to_fit();

	m_pArrow.clear();
	m_pArrow.shrink_to_fit();


	m_vupPartsType.clear();
	m_vupPartsType.shrink_to_fit();



	for( int i=0; i<enPARTS_TYPE_SIZE; i++ ){
		m_vsStatusNameBox[i].clear();
		m_vsStatusNameBox[i].shrink_to_fit();
	}

	for( int i=0; i<enPARTS_TYPE_SIZE; i++ ){
		m_vupPartsIcon[i].clear();
		m_vupPartsIcon[i].shrink_to_fit();
	}

	m_iStatusNum = 0;
}



void clsASSEMBLE_UI::Create(
		ID3D11Device* const pDevice, 
		ID3D11DeviceContext* const pContext,
		PARTS_NUM_DATA data  )
{
	//�ǂ����̘r�ɕ��펝�������?�̑�.
	assert( !m_upWndBox );
	m_upWndBox = make_unique< clsWINDOW_BOX >( pDevice, pContext );

	string tmpString;

	//�p�[�c���ڏ�����.
	assert( m_vupPartsType.size() == 0 );
	m_vupPartsType.reserve( enPARTS_TYPE_SIZE );
	SPRITE_STATE ss;
	ss.Disp = PARTS_TYPE_SIZE;
	for( unsigned int i=0; i<enPARTS_TYPE_SIZE; i++ ){
		m_vupPartsType.push_back( nullptr );
		m_vupPartsType[i] = make_unique< clsSprite2D >();

		tmpString = sPATH_PARTS_TYPE + sPATH_PARTS_TYPE_CHILDREN[i];
		m_vupPartsType[i]->Create( pDevice, pContext, tmpString.c_str(), ss );

		m_vupPartsType[i]->SetPos( vINIT_POS_PARTS_TYPE );
		m_vupPartsType[i]->AddPos( { fOFFSET_POS_X_PARTS_TYPE * static_cast<float>( i ), 0.0f, 0.0f } );
	}

	//�I�𒆃p�[�c����.
	assert( !m_upPartsTypeSelect );
	m_upPartsTypeSelect = make_unique< clsSprite2D >();
	m_upPartsTypeSelect->Create( pDevice, pContext, sPATH_SELECT_PARTS_TYPE, ss );
	m_upPartsTypeSelect->SetAlpha( fALPHA_SELECT_PARTS_TYPE );

	//�e�p�[�cUI.
	clsOPERATION_STRING OprtStr;
	ss.Disp = PARTS_ICON_SIZE;
	for( int i=0; i<enPARTS_TYPE_SIZE; i++ ){
		assert( m_vupPartsIcon[i].size() == 0 );
		m_vupPartsIcon[i].reserve( data[i] );

		for( int j=0; j<data[i]; j++ ){
			m_vupPartsIcon[i].push_back( nullptr );
			m_vupPartsIcon[i][j] = make_unique< clsSprite2D >();

			tmpString = sPATH_PARTS_ICON_ROOT + sPATH_PARTS_ICON_PARTS[i] + "\\" + sPATH_PARTS_ICON_PARTS[i];
			tmpString = OprtStr.ConsolidatedNumber( tmpString, j );//�f�B���N�g���ԍ��ԍ��A��.
			tmpString += sPATH_PARTS_ICON_END;//�t�@�C����.

			//�A�C�R���摜��������Ȃ����NODATA�摜��ǂݍ���.
			if( FAILED( m_vupPartsIcon[i][j]->Create( pDevice, pContext, tmpString.c_str(), ss ) ) ){
				m_vupPartsIcon[i][j]->Create( pDevice, pContext, sNO_DATA_FILE_NAME.c_str(), ss );
			}

			m_vupPartsIcon[i][j]->SetPos( vINIT_POS_PARTS_ICON );
			m_vupPartsIcon[i][j]->AddPos( { 0.0f, ( fPARTS_ICON_OFFSET + PARTS_ICON_SIZE.h ) * static_cast<float>( j ), 0.0f } );
		}
	}
	//�I�𒆊e�p�[�c�A�C�R��.
	assert( !m_upPartsNumSelect );
	m_upPartsNumSelect = make_unique< clsSprite2D >();
	m_upPartsNumSelect->Create( pDevice, pContext, sPATH_SELECT_PARTS_NUM, ss );
	m_upPartsNumSelect->SetAlpha( fALPHA_SELECT_PARTS_NUM );


	//�p�[�c�̒P�̃��f���\�������.
	assert( !m_upPartsWindow );
	ss.Disp = INIT_SIZE_PARTS_WINDOW;
	m_upPartsWindow = make_unique< clsSprite2D >();
	m_upPartsWindow->Create( pDevice, pContext, sPATH_PARTS_WINDOW, ss );
	m_upPartsWindow->SetPos( vINIT_POS_PARTS_WINDOW );
	m_upPartsWindow->SetAlpha( fPARTS_WINDOW_ALPHA );

	//���{�E�B���h�E.
	assert( !m_upRoboWindow );
	ss.Disp = INIT_SIZE_ROBO_WINDOW;
	m_upRoboWindow = make_unique< clsSprite2D >();
	m_upRoboWindow->Create( pDevice, pContext, sROBO_WINDOW_PATH, ss );
	m_upRoboWindow->SetPos( INIT_POS_ROBO_WINDOW );
	m_upRoboWindow->SetAlpha( fROBO_WINDOW_ALPHA );

	//�o���{�^��.
	assert( !m_upMissionStart );
	ss.Disp = SIZE_MISSION_START_BUTTON;
	m_upMissionStart = make_unique< clsSprite2D >();
	m_upMissionStart->Create( pDevice, pContext, sPATH_MISSION_START_BUTTON, ss );
	m_upMissionStart->SetPos( vINIT_POS_MISSION_START_BUTTON );

	//�w�b�_�[.
	assert( !m_upHeader );
	ss.Disp = INIT_SIZE_HEADER;
	m_upHeader = make_unique< clsSprite2D >();
	m_upHeader->Create( pDevice, pContext, sHEADER_FILE_PATH, ss );
	m_upHeader->SetPos( INIT_POS_HEADER );
	m_upHeader->SetAlpha( fHEADER_ALPHA );

	//�t�b�^�[.
	assert( !m_upFooter );
	ss.Disp = INIT_SIZE_FOOTER;
	m_upFooter = make_unique< clsSprite2D >();
	m_upFooter->Create( pDevice, pContext, sFOOTER_FILE_PATH, ss );
	m_upFooter->SetPos( INIT_POS_FOOTER );
	m_upFooter->SetAlpha( fFOOTER_ALPHA );

	//�w�b�_�[����.
	assert( !m_upHeaderText );
	m_upHeaderText = make_unique< clsUiText >();
	m_upHeaderText->Create( pContext, WND_W, WND_H, fTEXT_SCALE_HEADER );
	m_upHeaderText->SetPos( vTEXT_POS_HEADER );
	m_upHeaderText->SetText( sHEADER_TEXT );

	//�t�b�^�[����.
	assert( !m_upFooterText );
	m_upFooterText = make_unique< clsUiText >();
	m_upFooterText->Create( pContext, WND_W, WND_H, fTEXT_SCALE_FOOTER );
	m_upFooterText->SetPos( vTEXT_POS_FOOTER );
	m_upFooterText->SetText( sFOOTER_TEXT );



	//�X�e�[�^�X���\������鑋.
	assert( !m_upStatusWindow );
	ss.Disp = INIT_SIZE_STATUS_WINDOW;
	m_upStatusWindow = make_unique< clsSprite2D >();
	m_upStatusWindow->Create( pDevice, pContext, sPATH_STATUS_WINDOW, ss );
	m_upStatusWindow->SetPos( vINIT_POS_STATUS_WINDOW );
	m_upStatusWindow->SetAlpha( fSTATUS_WINDOW_ALPHA );


	//�X�e�[�^�X����.
	assert( !m_vupStatusText.size() );
	m_vupStatusText.resize( iSTATUS_NUM_MAX );
	for( int i=0; i<iSTATUS_NUM_MAX; i++ ){
//		m_vupStatusText.push_back( nullptr );
		m_vupStatusText[i] = make_unique< clsUiText >();
		m_vupStatusText[i]->Create( pContext, WND_W, WND_H, fTEXT_SCALE_STATUS );
		m_vupStatusText[i]->SetPos( vTEXT_POS_STATUS );
		m_vupStatusText[i]->AddPos( { 0.0f, fTEXT_POS_Y_OFFSET_STATUS * static_cast<float>( i ) } );
//		m_vupStatusText[i]->SetText( "Magazine Load Time" );
	}
	m_vupStatusText.shrink_to_fit();

	//�X�e�[�^�X�l.
	assert( !m_vupStatusNumText.size() );
	m_vupStatusNumText.reserve( iSTATUS_NUM_MAX );
	m_vupStatusNumText.resize( iSTATUS_NUM_MAX );
	for( int i=0; i<iSTATUS_NUM_MAX; i++ ){
//		m_vupStatusNumText.push_back( nullptr );
		m_vupStatusNumText[i] = make_unique< clsUiText >();
		m_vupStatusNumText[i]->Create( pContext, WND_W, WND_H, fTEXT_SCALE_STATUS );
		m_vupStatusNumText[i]->SetPos( vTEXT_POS_STATUS_NUM );
		m_vupStatusNumText[i]->AddPos( { 0.0f, fTEXT_POS_Y_OFFSET_STATUS * static_cast<float>( i ) } );
//		m_vupStatusNumText[i]->SetText( "12345 >> 12345" );
	}
	m_vupStatusNumText.shrink_to_fit();

	//�p�[�c��.
	assert( !m_upPartsNameText );
	m_upPartsNameText = make_unique< clsUiText >();
	m_upPartsNameText->Create( pContext, WND_W, WND_H, TEXT_SCALE_PARTS_NAME );
	m_upPartsNameText->SetPos( vTEXT_POS_PARTS_NAME );
//	m_upPartsNameText->SetText( "PARTS_NAME" );



#if _DEBUG
	ss.Disp = { WND_W, WND_H };
	m_upDegine = make_unique< clsSprite2D >();
	m_upDegine->Create( pDevice, pContext, sPATH_DESIGN, ss );
	m_upDegine->SetPos( vINIT_POS_DESIGN );
	m_upDegine->SetAlpha( 0.5f );
#endif//#if _DEBUG
}


void clsASSEMBLE_UI::Input(	
		const clsXInput* const pXInput,
		const clsDxInput* const pDxInput )
{
#if _DEBUG
	float move = 1.0f;
	if( GetAsyncKeyState( VK_RIGHT )& 0x8000 )	DEBUG_SPRITE_NAME->AddPos( { move, 0.0f/*, 0.0f*/ } );
	if( GetAsyncKeyState( VK_LEFT ) & 0x8000 )	DEBUG_SPRITE_NAME->AddPos( {-move, 0.0f/*, 0.0f*/ } );
	if( GetAsyncKeyState( VK_UP )	& 0x8000 )	DEBUG_SPRITE_NAME->AddPos( { 0.0f,-move/*, 0.0f*/ } );
	if( GetAsyncKeyState( VK_DOWN ) & 0x8000 )	DEBUG_SPRITE_NAME->AddPos( { 0.0f, move/*, 0.0f*/ } );

//	float scale = 0.01f;
//	if( GetAsyncKeyState( 'D' ) & 0x8000 )	DEBUG_SPRITE_NAME->AddScale( { 1+scale, 1.0f, 0.0f } );
//	if( GetAsyncKeyState( 'A' ) & 0x8000 )	DEBUG_SPRITE_NAME->AddScale( { 1-scale, 1.0f, 0.0f } );
//	if( GetAsyncKeyState( 'W' ) & 0x8000 )	DEBUG_SPRITE_NAME->AddScale( { 1.0f, 1-scale, 0.0f } );
//	if( GetAsyncKeyState( 'S' ) & 0x8000 )	DEBUG_SPRITE_NAME->AddScale( { 1.0f, 1+scale, 0.0f } );
//	if( GetAsyncKeyState( 'E' ) & 0x8000 )	DEBUG_SPRITE_NAME->AddScale( 1+scale );
//	if( GetAsyncKeyState( 'Q' ) & 0x8000 )	DEBUG_SPRITE_NAME->AddScale( 1-scale );


#endif//#if _DEBUG

	if( pXInput->isPressEnter( XINPUT_Y ) )
	{
		if( m_isDispStatus )	m_isDispStatus = false;
		else					m_isDispStatus = true;
	}


}


void clsASSEMBLE_UI::Update( 
	enSELECT_MODE enSelect,
	shared_ptr< clsFILE > const spFile, 
	const int iPartsType,
	const int iPartsNum,
	const int iStatusCutNum )
{
	//�p�[�c�I�𒆂������Ȃ���.
	if( enSelect != enSELECT_MODE::PARTS ){
		return;
	}

	//�I�𒆂������������̔\��.
	assert( m_upPartsTypeSelect );
	m_upPartsTypeSelect->SetPos( m_vupPartsType[ iPartsType ]->GetPos() );
	assert( m_upPartsNumSelect );
	m_upPartsNumSelect->SetPos( m_vupPartsIcon[ iPartsType ][ iPartsNum ]->GetPos() );

	//������.
	assert( spFile );
	m_iStatusNum = iOPEN_STATUS_NUM[ iPartsType ];//�X�e�[�^�X�����s���邩���擾.

	//�X�e�[�^�X����,���l.
	assert( m_vupStatusText[ iPartsType ] );
	assert( m_vupStatusNumText[ iPartsType ] );
	const int iOFFSET_RATE_STATUS_TEXT_FOR_STATUS_WINDOW =  m_iStatusNum - 1;
	for( int i=0; i<iSTATUS_NUM_MAX; i++ ){
		m_vupStatusText[i]->SetPos( vTEXT_POS_STATUS );
		m_vupStatusText[i]->AddPos( { 0.0f, fTEXT_POS_Y_OFFSET_STATUS * static_cast<float>( i ) } );
		m_vupStatusText[i]->AddPos( { 0.0f, -INIT_SIZE_STATUS_WINDOW.h * static_cast<float>( iOFFSET_RATE_STATUS_TEXT_FOR_STATUS_WINDOW ) } );
		m_vupStatusNumText[i]->SetPos( vTEXT_POS_STATUS_NUM );
		m_vupStatusNumText[i]->AddPos( { 0.0f, fTEXT_POS_Y_OFFSET_STATUS * static_cast<float>( i ) } );
		m_vupStatusNumText[i]->AddPos( { 0.0f, -INIT_SIZE_STATUS_WINDOW.h * static_cast<float>( iOFFSET_RATE_STATUS_TEXT_FOR_STATUS_WINDOW ) } );
	}


	//��яo���Ȃ�.
	if( static_cast< unsigned int >( m_iStatusNum ) > m_vupStatusText.size() ||
		static_cast< unsigned int >( m_iStatusNum ) > m_vupStatusNumText.size() )
	{
		m_iStatusNum = 0;
	}

	//�p�[�c���Z�b�g.
	assert( m_upPartsNameText );
	m_upPartsNameText->SetText( 
		spFile->GetDataString( iPartsNum, iSTATUS_PARTS_NAME_NUM ).c_str() );

	//�X�e�[�^�X�E�B���h�E�̕�����.
	for( int i=0; i<iOPEN_STATUS_NUM[iPartsType]; i++ ){
		//�X�e�[�^�X���Z�b�g.
		assert( m_vupStatusText[i] );
		m_vupStatusText[i]->SetText( m_vsStatusNameBox[ iPartsType ][i].c_str() );
		//�X�e�[�^�X���l�Z�b�g.
		assert( m_vupStatusNumText[i] );
		m_vupStatusNumText[i]->SetText( spFile->GetDataString( iPartsNum, i + iStatusCutNum ).c_str() );
	}



	//�ǂ����̂��ŁH.
	assert( m_upWndBox );
	m_upWndBox->Update();
}


void clsASSEMBLE_UI::Render( 
	enSELECT_MODE enSelect,
	const int iPartsType, 
	const int iPartsNum )
{

	//�p�[�c�J�e�S��.
	for( unsigned int i=0; i<m_vupPartsType.size(); i++ ){
		assert( m_vupPartsType[i] );
		m_vupPartsType[i]->Render();
	}

	//�p�[�c�A�C�R��.
	for( unsigned int j=0; j<m_vupPartsIcon[ iPartsType ].size(); j++ ){
		assert( m_vupPartsIcon[ iPartsType ][j] );
		m_vupPartsIcon[ iPartsType ][j]->Render();
	}

	assert( m_upHeader );
	m_upHeader->Render();

	assert( m_upFooter );
	m_upFooter->Render();

	assert( m_upPartsWindow );
	m_upPartsWindow->Render();
	assert( m_upRoboWindow );
	m_upRoboWindow->Render();


	assert( m_upMissionStart );
	m_upMissionStart->Render();

	assert( m_upHeaderText );
	m_upHeaderText->Render();
	assert( m_upFooterText );
	m_upFooterText->Render();



	//�p�[�c�I�𒆂̂ݕ`��.
	if( enSelect == enSELECT_MODE::PARTS ){
		//�I�𒆃J�e�S��.
		assert( m_upPartsTypeSelect );
		m_upPartsTypeSelect->Render();
		assert( m_upPartsNumSelect );
		m_upPartsNumSelect->Render();

		assert( m_upPartsNameText );
		m_upPartsNameText->Render();
	}

	assert( m_upWndBox );
	m_upWndBox->Render();

#if _DEBUG
	static bool bDesignDisp = true;
	if( GetAsyncKeyState( 'M' ) & 0x1 ){
		if( bDesignDisp )	bDesignDisp = false;
		else				bDesignDisp = true;
	};
	if( bDesignDisp )m_upDegine->Render();
#endif//#if _DEBUG

}

void clsASSEMBLE_UI::RenderPartsState( 
	enSELECT_MODE enSelect, 
	const int iPartsType, 
	const int iPartsNum )//�I�𒆃p�[�c�ԍ�.
{
	//�X�e�[�^�X��\�����Ȃ��Ȃ��΂�.
	if( !m_isDispStatus ) return;

	//�p�[�c�I�𒆂̂ݕ`��.
	if( enSelect == enSELECT_MODE::PARTS ){
		//��.
		assert( m_upStatusWindow );
		D3DXVECTOR3 vPos = m_upStatusWindow->GetPos();
		for( int i=0; i<m_iStatusNum; i++ ){
			m_upStatusWindow->Render();
			m_upStatusWindow->AddPos( { 0.0f, -INIT_SIZE_STATUS_WINDOW.h, 0.0f } );
		}
		m_upStatusWindow->SetPos( vPos );

		//���l.
		for( int i=0; i<m_iStatusNum; i++ ){
			assert( m_vupStatusText[i] );
			m_vupStatusText[i]->Render();
			assert( m_vupStatusNumText[i] );
			m_vupStatusNumText[i]->Render( clsUiText::enPOS::RIGHT );
		}
	}

}



#if _DEBUG
//�f�o�b�O�e�L�X�g�p.
D3DXVECTOR3 clsASSEMBLE_UI::GetUiPos()
{
	return DEBUG_SPRITE_NAME->GetPos();
}
#endif//#if _DEBUG
