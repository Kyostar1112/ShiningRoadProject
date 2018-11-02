#include "BlackScreen.h"

namespace{

	const float fDARK_RIMIT = 1.0f;//�Ó]���E.
	const float fDAWN_RIMIT = 0.0f;//���]���E.

}

clsBLACK_SCREEN::clsBLACK_SCREEN()
	:m_enState( enSTATE::NEUTRAL )
	,m_fChangeSpd( fBLACK_SCREEN_DEFAULT_SPD )
	,m_uiFlgGroup( 0 )
{
}

clsBLACK_SCREEN::~clsBLACK_SCREEN()
{
	m_uiFlgGroup = 0;
	m_fChangeSpd = 0.0f;
	m_enState = enSTATE::NEUTRAL;
}

//�Ó]�w��.//Alpha Per Frame.
void clsBLACK_SCREEN::GetDark()
{
//	//�쓮���͎󂯕t���Ȃ�.
//	if( m_enState != enSTATE::NEUTRAL )	return;
	//�Â��Ȃ�Ȃ��ꍇ���󂯕t���Ȃ�.

	UpdateBitFlg( enFLG_GROUP::DARK_ROUTE, true );
	UpdateBitFlg( enFLG_GROUP::BRIGHT_ROUTE, false );
	m_enState = enSTATE::DARK;
}

//���]�w��.//Alpha Per Frame.
void clsBLACK_SCREEN::GetBright()
{
//	//�쓮���͎󂯕t���Ȃ�.
//	if( m_enState != enSTATE::NEUTRAL )	return;
	//���邭�Ȃ�Ȃ��ꍇ���󂯕t���Ȃ�.

	UpdateBitFlg( enFLG_GROUP::BRIGHT_ROUTE, true );
	UpdateBitFlg( enFLG_GROUP::DARK_ROUTE, false );
	m_enState = enSTATE::BRIGHT;
}

void clsBLACK_SCREEN::SetChangeSpd( const float fSpd )
{
	m_fChangeSpd = fSpd;
	if( fSpd < 0.0f ){
		m_fChangeSpd *= -1.0f;
	}
}


//�Ö��]�̎��s.
void clsBLACK_SCREEN::Update()
{
	float fChangeSpd = m_fChangeSpd;
	if( m_enState == enSTATE::NEUTRAL ){
		return;
	}
	//�t�].
	else if( m_enState == enSTATE::BRIGHT ){
		fChangeSpd *= -1.0f;
	}

	//���ߒl�̍X�V���s���A�I�������Ȃ�΂��̎|��Ԃ�.
	if( !AddAlpha( fChangeSpd ) ){
		//����if���̒��ւ́A���ߒl���I�[�o�[���������.
		//�Ó]���������Ȃ�.
		if( isBitFlg( enFLG_GROUP::DARK_ROUTE ) ){
			UpdateBitFlg( enFLG_GROUP::DARK_ROUTE, false );
			UpdateBitFlg( enFLG_GROUP::DARK_END, true );
		}
		//���]���������Ȃ�.
		else if( isBitFlg( enFLG_GROUP::BRIGHT_ROUTE ) ){
			UpdateBitFlg( enFLG_GROUP::BRIGHT_ROUTE, false );
			UpdateBitFlg( enFLG_GROUP::BRIGHT_END, true );
		}
		m_enState = enSTATE::NEUTRAL;
	}
}

//�Ó]�����������true��Ԃ�.
bool clsBLACK_SCREEN::isDarkEnd()
{
	if( isBitFlg( enFLG_GROUP::DARK_END ) ){
		UpdateBitFlg( enFLG_GROUP::DARK_END, false );
		m_enState = enSTATE::NEUTRAL;
		return true;
	}

	return false;
}


//���]�����������true��Ԃ�.
bool clsBLACK_SCREEN::isBrightEnd()
{
	if( isBitFlg( enFLG_GROUP::BRIGHT_END ) ){
		UpdateBitFlg( enFLG_GROUP::BRIGHT_END, false );
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
