#ifndef SPRITE_2D_H_
#define SPRITE_2D_H_

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )

#include "Common.h"//���ʃN���X.

#define ALIGN16	_declspec(align(16))


//======================================
//	�\����.
//======================================
//�R���X�^���g�o�b�t�@�̃A�v�����̒�`(Sprite2D.hlsl)
//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
struct SPRITE2D_CONSTANT_BUFFER
{
	ALIGN16 D3DXMATRIX	mW;				//���[���h�s��.
	ALIGN16 float		fViewPortWidth;	//�r���[�|�[�g��.
	ALIGN16 float		fViewPortHeight;//�r���[�|�[�g����.
	ALIGN16	float		fAlpha;			//�A���t�@�l(���߂Ŏg�p����)
	ALIGN16 D3DXVECTOR2	vUV;			//UV���W.
};

//�X�v���C�g�\����.
struct SPRITE_STATE
{
	WHSIZE_FLOAT	Disp;	//�\��������.
	WHSIZE_FLOAT	Anim;	//���R�}?.
	SPRITE_STATE(){
		Disp = { WND_W, WND_H };
		Anim = { 1.0f, 1.0f };
	}
};


/*************************************************
*	Sprite2D�N���X.
**/
class clsSprite2D : public clsCommon
{

public:
	clsSprite2D();	//�R���X�g���N�^.
	virtual ~clsSprite2D();	//�f�X�g���N�^.

	//������.
	HRESULT Create( 
		ID3D11Device* const pDevice11,
		ID3D11DeviceContext* const pContext11,
		const char* fileName, 
		const SPRITE_STATE ss );


	//�`��(�����_�����O)
	virtual void Render();


	void SetPos( const D3DXVECTOR3 &vPos );
	void SetScale( const D3DXVECTOR3 &vScale );
	void SetScale( const float &fScale, 
		const bool withZ = false );	//X��Y�𓙂����{���ŏ�����.
									//��������true�ɂ����Z�ɂ��e������.		
	void SetAlpha( const float fAlpha );
	//�͈͂�over�����false���Ԃ��Ă���.
	bool AddAlpha( const float fAlpha );
	float GetAlpha();

	D3DXVECTOR3 GetPos() const;
	D3DXVECTOR3 GetScale() const;


	void AddPos( const D3DXVECTOR3 &vPos );		//���������Z����.
	void AddScale( const D3DXVECTOR3 &vScale );	//�����{�ɂ���.
	void AddScale( const float &fScale, const bool withZ = false );

	void SetAnim( const POINTFLOAT &anim );

protected:


	//�V�F�[�_�쐬.
	HRESULT InitShader();
	//���f���쐬.
	virtual HRESULT InitModel( SPRITE_STATE ss );
	//�e�N�X�`���쐬.
	HRESULT CreateTexture( const char* const fileName,
		ID3D11ShaderResourceView** pTex );

	void Release();


	//�����f���̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;//���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;	//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pConstantBuffer;//�R���X�^���g�o�b�t�@.

	//�����f�����Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;//���_�o�b�t�@.

	ID3D11ShaderResourceView*	m_pTexture;//�e�N�X�`��.
	ID3D11SamplerState*			m_pSampleLinear;//�e�N�X�`���̃T���v��-:�e�N�X�`���[�Ɋe��t�B���^��������.


	SPRITE_STATE	m_SState;	//�X�v���C�g���.
	POINTFLOAT		m_fPatternNo;//�}�X�ڔԍ�.		

	D3DXVECTOR3		m_vPos;	//�ʒu.

	D3DXVECTOR3		m_vScale;

	float			m_fAlpha;	//�A���t�@�l.
};



#endif//#ifndef SPRITE_2D_H_