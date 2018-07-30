#include "AssembleUi.h"

#include "OperationString.h"
//#include <string>


//�t�@�C�������邩���ׂ�@�\�����.


using namespace std;



//----- �p�[�c�J�e�S�� -----//.
//�p�[�c�J�e�S���T�C�Y.
const WHSIZE_FLOAT PARTS_TYPE_SIZE = { 110.0f, 40.0f };
//�p�[�c�J�e�S��UI�̊�ʒu.
const D3DXVECTOR3 vINIT_POS_PARTS_TYPE = { 16.0f, 95.0f, 0.0f };
//�p�[�c�J�e�S���̍��W�̍�.
const float fOFFSET_POS_X_PARTS_TYPE = PARTS_TYPE_SIZE.w + 4.0f;
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
	vINIT_POS_PARTS_TYPE.y, 0.0f };


//----- �o���{�^�� �I��� -----//.



//----- �e�p�[�cUI -----//.
//�T�C�Y.
const WHSIZE_FLOAT PARTS_ICON_SIZE = { 60.0f, 60.0f };
//UI���m�̌���.
const float fPARTS_ICON_OFFSET = 2.0f;
//�J�e�S������̌���.
const float fPARTS_ICON_OFFSET_FROM_PARTS_TYPE = 6.0f;
//��ʒu.
const D3DXVECTOR3 vINIT_POS_PARTS_ICON = { vINIT_POS_PARTS_TYPE.x, vINIT_POS_MISSION_START_BUTTON.y + SIZE_MISSION_START_BUTTON.h + fPARTS_ICON_OFFSET_FROM_PARTS_TYPE, 0.0f };

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




//----- �X�e�[�^�X�E�B���h�E -----//.
const D3DXVECTOR3 vINIT_POS_STATUS_WINDOW = { 98.0f, vINIT_POS_PARTS_ICON.y, 0.0f };//179.5f;
const WHSIZE_FLOAT INIT_SIZE_STATUS_WINDOW  = { 415.0f, 468.0f };//360.0f.
const char* sPATH_STATUS_WINDOW = "Data\\Image\\AssembleUi\\StatusWindow.png";
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
const float fTEXT_POS_Y_OFFSET_STATUS = INIT_SIZE_STATUS_WINDOW.h / ( iSTATUS_NUM_MAX + 1 );//����+1�̓X�e�[�^�X�^�C�g���̈�.
const float fTEXT_SCALE_STATUS = 1.5f;
//���ڕ����̍��W.
const D3DXVECTOR2 vTEXT_POS_OFFSET_TO_STATUS_WINDOW = { 5.0f, 8.75f };//������̂���.
const D3DXVECTOR2 vTEXT_POS_STATUS = {
	vINIT_POS_STATUS_WINDOW.x + vTEXT_POS_OFFSET_TO_STATUS_WINDOW.x,
	vINIT_POS_STATUS_WINDOW.y + vTEXT_POS_OFFSET_TO_STATUS_WINDOW.y + fTEXT_POS_Y_OFFSET_STATUS };
//�l�����̍��W.
const D3DXVECTOR2 vTEXT_POS_STATUS_NUM = 
	{ vTEXT_POS_STATUS.x + INIT_SIZE_STATUS_WINDOW.w - 12.0f, vTEXT_POS_STATUS.y };
//----- �X�e�[�^�X�E�B���h�E�I��� -----//.


//----- �p�[�c�E�B���h�E -----//.
//�p�[�c�̎p�̂܂�X���W.
const float fOFFSET_PARTS_WINDOW_TO_STATUS_WINDOW = 8.0f;//�X�e�[�^�X�E�B���h�E�Ƃ̌���.
//478.25f.
const D3DXVECTOR3 vINIT_POS_PARTS_WINDOW = { 
	vINIT_POS_STATUS_WINDOW.x + INIT_SIZE_STATUS_WINDOW.w + fOFFSET_PARTS_WINDOW_TO_STATUS_WINDOW, 
	vINIT_POS_STATUS_WINDOW.y, 
	0.0f };
const WHSIZE_FLOAT INIT_SIZE_PARTS_WINDOW  = { 300.0f, 468.0f };
const char* sPATH_PARTS_WINDOW = "Data\\Image\\PartsIcon\\NoData.png";

//����( �X�e�[�^�X�E�B���h�E����ɂ��Ă��� ).
const float TEXT_SCALE_PARTS_NAME = TEXT_SCALE_STATUS_TITLE;
const D3DXVECTOR2 vTEXT_POS_PARTS_NAME = 
	{ vTEXT_POS_STATUS_TITLE.x + INIT_SIZE_STATUS_WINDOW.w + fOFFSET_PARTS_WINDOW_TO_STATUS_WINDOW, vTEXT_POS_STATUS_TITLE.y };

//----- �p�[�c�E�B���h�E�I��� -----//.






//----- �w�b�_�[�ƃt�b�^�[ -----//.
const WHSIZE_FLOAT INIT_SIZE_HEADER  = { WND_W, 60.0f };
const WHSIZE_FLOAT INIT_SIZE_FOOTER  = { WND_W, 24.0f };
const D3DXVECTOR3 INIT_POS_HEADER = { 0.0f, 20.0f, 0.0f };
const D3DXVECTOR3 INIT_POS_FOOTER = { 0.0f, WND_H - INIT_SIZE_FOOTER.h - 14.0f, 0.0f };
//����.
const float fTEXT_SCALE_HEADER = 4.0f;
const float fTEXT_SCALE_FOOTER = 1.0f;
const D3DXVECTOR2 vTEXT_POS_OFFSET_HEADER = { 57.0f, 7.0f };//�摜�Ƃ̂���.
const D3DXVECTOR2 vTEXT_POS_OFFSET_FOOTER = { 57.0f, 6.0f };
const D3DXVECTOR2 vTEXT_POS_HEADER = { INIT_POS_HEADER.x + vTEXT_POS_OFFSET_HEADER.x, INIT_POS_HEADER.y + vTEXT_POS_OFFSET_HEADER.y };
const D3DXVECTOR2 vTEXT_POS_FOOTER = { INIT_POS_FOOTER.x + vTEXT_POS_OFFSET_FOOTER.x, INIT_POS_FOOTER.y + vTEXT_POS_OFFSET_FOOTER.y };
const char* sHEADER_TEXT = "ASSEMBLE";
const char* sFOOTER_TEXT = "Enter : B";
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
{ 5, 11, 2, 2, 10, 10 };
//�X�e�[�^�X�̖��O.
const string sSTATUS_NAME_LEG[] = 
	{ "HP", "Walk Speed", "Stability", "Turning", "Jump Power"  };
const string sSTATUS_NAME_CORE[] = 
	{ "HP", "EN Capacity", "EN Output", "Boost Horizontal Power", "Boost Horizontal Cost", "Boost Vertical Power", "Boost Vertical Cost", "Boost Quick Power", "Boost Quick Cost", "Boost Quick Time", "Activity Time" };
const string sSTATUS_NAME_HEAD[] = 
	{ "HP", "Search" };
const string sSTATUS_NAME_ARMS[] = 
	{ "HP", "Aiming" };
const string sSTATUS_NAME_WEAPON[] = 
	{ "Attack Power", "Bullet Speed", "Bullet Range", "Cost", "Load Time", "Lock on Time", "Lock on Range", "Stability", "Magazine Load Time", "Bullets Num" };




clsASSEMBLE_UI::clsASSEMBLE_UI()
	:m_iStatusNum( 0 )
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



	//�X�e�[�^�X���\������鑋.
	assert( !m_upStatusWindow );
	ss.Disp = INIT_SIZE_STATUS_WINDOW;
	m_upStatusWindow = make_unique< clsSprite2D >();
	m_upStatusWindow->Create( pDevice, pContext, sPATH_STATUS_WINDOW, ss );
	m_upStatusWindow->SetPos( vINIT_POS_STATUS_WINDOW );

	//�p�[�c�̒P�̃��f���\�������.
	assert( !m_upPartsWindow );
	ss.Disp = INIT_SIZE_PARTS_WINDOW;
	m_upPartsWindow = make_unique< clsSprite2D >();
	m_upPartsWindow->Create( pDevice, pContext, sPATH_PARTS_WINDOW, ss );
	m_upPartsWindow->SetPos( vINIT_POS_PARTS_WINDOW );

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
	m_upHeader->Create( pDevice, pContext, sNO_DATA_FILE_NAME.c_str(), ss );
	m_upHeader->SetPos( INIT_POS_HEADER );

	//�t�b�^�[.
	assert( !m_upFooter );
	ss.Disp = INIT_SIZE_FOOTER;
	m_upFooter = make_unique< clsSprite2D >();
	m_upFooter->Create( pDevice, pContext, sNO_DATA_FILE_NAME.c_str(), ss );
	m_upFooter->SetPos( INIT_POS_FOOTER );


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



	//�X�e�[�^�X�^�C�g��.
	assert( !m_upStatusTitleText );
	m_upStatusTitleText = make_unique< clsUiText >();
	m_upStatusTitleText->Create( pContext, WND_W, WND_H, TEXT_SCALE_STATUS_TITLE );
	m_upStatusTitleText->SetPos( vTEXT_POS_STATUS_TITLE );
	m_upStatusTitleText->SetText( sSTATUS_TITLE_TEXT );

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
	m_upDegine->SetAlpha( fINIT_SCALE_DESIGN );
#endif//#if _DEBUG
}


void clsASSEMBLE_UI::Input()
{
#if _DEBUG
	float move = 0.25f;
	if( GetAsyncKeyState( VK_RIGHT )& 0x8000 )	m_upMissionStart->AddPos( { move, 0.0f, 0.0f } );
	if( GetAsyncKeyState( VK_LEFT ) & 0x8000 )	m_upMissionStart->AddPos( {-move, 0.0f, 0.0f } );
	if( GetAsyncKeyState( VK_UP )	& 0x8000 )	m_upMissionStart->AddPos( { 0.0f,-move, 0.0f } );
	if( GetAsyncKeyState( VK_DOWN ) & 0x8000 )	m_upMissionStart->AddPos( { 0.0f, move, 0.0f } );
	float scale = 0.01f;
	if( GetAsyncKeyState( 'D' ) & 0x8000 )	m_upMissionStart->AddScale( { 1+scale, 1.0f, 0.0f } );
	if( GetAsyncKeyState( 'A' ) & 0x8000 )	m_upMissionStart->AddScale( { 1-scale, 1.0f, 0.0f } );
	if( GetAsyncKeyState( 'W' ) & 0x8000 )	m_upMissionStart->AddScale( { 1.0f, 1-scale, 0.0f } );
	if( GetAsyncKeyState( 'S' ) & 0x8000 )	m_upMissionStart->AddScale( { 1.0f, 1+scale, 0.0f } );
	if( GetAsyncKeyState( 'E' ) & 0x8000 )	m_upMissionStart->AddScale( 1+scale );
	if( GetAsyncKeyState( 'Q' ) & 0x8000 )	m_upMissionStart->AddScale( 1-scale );
#endif//#if _DEBUG
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
#if _DEBUG
	m_upDegine->Render();
#endif//#if _DEBUG

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

	assert( m_upStatusWindow );
	m_upStatusWindow->Render();
	assert( m_upPartsWindow );
	m_upPartsWindow->Render();

	assert( m_upMissionStart );
	m_upMissionStart->Render();

	assert( m_upHeaderText );
	m_upHeaderText->Render();
	assert( m_upFooterText );
	m_upFooterText->Render();

	assert( m_upStatusTitleText );
	m_upStatusTitleText->Render();


	//�p�[�c�I�𒆂̂ݕ`��.
	if( enSelect == enSELECT_MODE::PARTS ){
		//�I�𒆃J�e�S��.
		assert( m_upPartsTypeSelect );
		m_upPartsTypeSelect->Render();
		assert( m_upPartsNumSelect );
		m_upPartsNumSelect->Render();

		assert( m_upPartsNameText );
		m_upPartsNameText->Render();

		for( int i=0; i<m_iStatusNum; i++ ){
		assert( m_vupStatusText[i] );
			m_vupStatusText[i]->Render();
		assert( m_vupStatusNumText[i] );
			m_vupStatusNumText[i]->Render( true );
		}
	}

	assert( m_upWndBox );
	m_upWndBox->Render();
}




#if _DEBUG
//�f�o�b�O�e�L�X�g�p.
D3DXVECTOR3 clsASSEMBLE_UI::GetUiPos()
{
	return m_upFooter->GetPos();
}
#endif//#if _DEBUG
