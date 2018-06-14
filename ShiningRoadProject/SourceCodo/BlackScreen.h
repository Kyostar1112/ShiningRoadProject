#pragma once

#include "Sprite2D.h"

const float fBLACK_SCREEN_DEFAULT_SPD = 1.0f / ( 60.0f * 2.0f );


class clsBLACK_SCREEN : public clsSprite2D
{
public:
	clsBLACK_SCREEN();
	~clsBLACK_SCREEN();

	//�Ó]���ł���?�A�̃t���O.
	enum class enSTATE : UCHAR
	{
		NEUTRAL = 0,//�������Ă��Ȃ�.
		DARK,		//�Ó].
		BRIGHT		//���].
	};

	//----- �Ö��]�̎w�� -----.
	//�Ó]�w��.//Alpha Per Frame.
	void GetDark( const float fDarkSpd = fBLACK_SCREEN_DEFAULT_SPD );
	//���]�w��.//Alpha Per Frame.
	void GetBright( const float fBrightSpd = -fBLACK_SCREEN_DEFAULT_SPD );

	//�Ö��]�̎��s.
	void Update();

	//�Ó]�����������true��Ԃ�.
	bool isDarkEnd();
	//���]�����������true��Ԃ�.
	bool isBrightEnd();

private:

	//�t���O�p�񋓑�.
	enum enFLG_GROUP : UCHAR
	{
		DARK_END = 0,//�Ó]���I������u��.
		DARK_ROUTE	,//�Ó]��.
		BRIGHT_END	,//���]���I������u��.
		BRIGHT_ROUTE,//���]��.
	};

	//�r�b�g�t���O�X�V.
	void UpdateBitFlg( const enFLG_GROUP enFlg, const bool bStand );
	//�t���O�`�F�b�N.
	bool isBitFlg( const enFLG_GROUP enFlg ) const;

	//�Ó]���ł���?�A�̃t���O.
	enSTATE m_enState;

	//�Ö��]���x.
	float m_fChangeSpd;

//	//�Ó]�̏I����m�点��t���O.
//	bool m_bDarkEnd;

	//�e��t���O�܂Ƃ�.
	unsigned int m_uiFlgGroup;

};

