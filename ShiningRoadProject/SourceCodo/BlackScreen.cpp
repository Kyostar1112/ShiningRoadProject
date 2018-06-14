#include "BlackScreen.h"

const float fDARK_RIMIT = 1.0f;//�Ó]���E.
const float fDAWN_RIMIT = 0.0f;//���]���E.



clsBLACK_SCREEN::clsBLACK_SCREEN()
	:m_enState( enSTATE::NEUTRAL )
	,m_fChangeSpd( 0.0f )
	,m_uiFlgGroup( 0 )
{
}

clsBLACK_SCREEN::~clsBLACK_SCREEN()
{
	m_uiFlgGroup = 0;
	m_fChangeSpd = 0;
	m_enState = enSTATE::BRIGHT;
}

//�Ó]�w��.//Alpha Per Frame.
void clsBLACK_SCREEN::GetDark( const float fDarkSpd )
{
//	//�쓮���͎󂯕t���Ȃ�.
//	if( m_enState != enSTATE::NEUTRAL )	return;
	//�Â��Ȃ�Ȃ��ꍇ���󂯕t���Ȃ�.
	if( fDarkSpd <= 0.0f )	return;

	m_fChangeSpd = fDarkSpd;
	UpdateBitFlg( DARK_ROUTE, true );
	UpdateBitFlg( BRIGHT_ROUTE, false );
	m_enState = enSTATE::DARK;
}

//���]�w��.//Alpha Per Frame.
void clsBLACK_SCREEN::GetBright( const float fBrightSpd )
{
//	//�쓮���͎󂯕t���Ȃ�.
//	if( m_enState != enSTATE::NEUTRAL )	return;
	//���邭�Ȃ�Ȃ��ꍇ���󂯕t���Ȃ�.
	if( fBrightSpd >= 0.0f )	return;

	m_fChangeSpd = fBrightSpd;
	UpdateBitFlg( BRIGHT_ROUTE, true );
	UpdateBitFlg( DARK_ROUTE, false );
	m_enState = enSTATE::BRIGHT;
}

//�Ö��]�̎��s.
void clsBLACK_SCREEN::Update()
{
	if( m_enState == enSTATE::NEUTRAL )	return;

	//���ߒl�̍X�V���s���A�I�������Ȃ�΂��̎|��Ԃ�.
	if( !AddAlpha( m_fChangeSpd ) ){
		//����if���̒��ւ́A���ߒl���I�[�o�[���������.
		//�Ó]���������Ȃ�.
		if( isBitFlg( DARK_ROUTE ) ){
			UpdateBitFlg( DARK_ROUTE, false );
			UpdateBitFlg( DARK_END, true );
		}
		//���]���������Ȃ�.
		else if( isBitFlg( BRIGHT_ROUTE ) ){
			UpdateBitFlg( BRIGHT_ROUTE, false );
			UpdateBitFlg( BRIGHT_END, true );
		}
		m_enState = enSTATE::NEUTRAL;
	}
}

//�Ó]�����������true��Ԃ�.
bool clsBLACK_SCREEN::isDarkEnd()
{
	if( isBitFlg( DARK_END ) ){
		UpdateBitFlg( DARK_END, false );
		m_enState = enSTATE::NEUTRAL;
		return true;
	}

	return false;
}


//���]�����������true��Ԃ�.
bool clsBLACK_SCREEN::isBrightEnd()
{
	if( isBitFlg( BRIGHT_END ) ){
		UpdateBitFlg( BRIGHT_END, false );
		m_enState = enSTATE::NEUTRAL;
		return true;
	}

	return false;
}



//�r�b�g�t���O�X�V.
void clsBLACK_SCREEN::UpdateBitFlg( const enFLG_GROUP enFlg, const bool bStand )
{
	//�r�b�g�𗧂Ă�.
	if( bStand ){
		m_uiFlgGroup |= 1 << enFlg;
	}
	//�r�b�g�𗎂Ƃ�.
	else{
		m_uiFlgGroup &= ~( 1 << enFlg );
	}
}


//�t���O�`�F�b�N.
bool clsBLACK_SCREEN::isBitFlg( const enFLG_GROUP enFlg ) const
{
	if( ( m_uiFlgGroup >> enFlg ) & 1 ){
		return true;
	}
	return false;
}
