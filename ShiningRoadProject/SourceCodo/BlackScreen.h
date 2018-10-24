#ifndef BLACK_SCREEN_H_
#define BLACK_SCREEN_H_


#include "Sprite2D.h"

const float fBLACK_SCREEN_DEFAULT_SPD = 1.0f / ( 60.0f * 2.0f ) * 2.0f;


class clsBLACK_SCREEN : public clsSprite2D
{
public:
	clsBLACK_SCREEN();
	~clsBLACK_SCREEN();

	//�Ö��]�̎��s( ���t���[�� ).
	void Update();

	//0.0f �` 1.0f�ŗ^���Ă�( �͂ݏo�Ă��A�킴�ƂȂ���͂Ȃ��� ).
	void SetChangeSpd( const float fSpd );

	//----- �Ö��]�̎w�� -----.
	//�Ó]�w��.//Alpha Per Frame.
	void GetDark();
	//���]�w��.//Alpha Per Frame.
	void GetBright();


	//�Ó]�����������true��Ԃ�( ���̏u�Ԃ��� ).
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

	//�Ó]���ł���?�A�̃t���O.
	enum class enSTATE : UCHAR
	{
		NEUTRAL = 0,//�������Ă��Ȃ�.
		DARK,		//�Ó].
		BRIGHT		//���].
	}	m_enState;


	//�r�b�g�t���O�X�V.
	void UpdateBitFlg( const enFLG_GROUP enFlg, const bool bStand );
	//�t���O�`�F�b�N.
	bool isBitFlg( const enFLG_GROUP enFlg ) const;

	//�Ö��]���x.
	float m_fChangeSpd;

	//�e��t���O�܂Ƃ�.
	unsigned int m_uiFlgGroup;

};

#endif//#ifndef BLACK_SCREEN_H_