#ifndef SPRITE_H_
#define SPRITE_H_

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )	

//============================================================
//	�C���N���[�h.
//============================================================
#include "Common.h"//���ʃN���X.


//============================================================
//	�\����.
//============================================================
//�R���X�^���g�o�b�t�@�̃A�v�����̒�`(Simple.hlsl).
//�V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
struct SPRITESHADER_CONSTANT_BUFFER
{
	D3DXMATRIX	mWVP;		//���[���h,�r���[,�ˉe�̍����ϊ��s��.
	D3DXVECTOR4	vColor;		//�J���[(RGBA�̌^�ɍ��킹��) : �e�N�X�`���̏ォ��F���ڂ���(�Ԃ��ۂ��������邽�߂Ƃ�).
	D3DXVECTOR4	vUV;		//UV���W.
};

////���_�̍\����.
//struct SpriteVertex
//{
//	D3DXVECTOR3 vPos;	//���_���W(x,y,z).
//	D3DXVECTOR2 vTex;	//�e�N�X�`�����W.
//};




//============================================================
//	�X�v���C�g�N���X.
//============================================================
class clsSprite
	: public clsCommon
{
public:
	clsSprite();	//�R���X�g���N�^.
	virtual ~clsSprite();	//�f�X�g���N�^.

	//������.
	HRESULT Create( ID3D11Device* const pDevice11,
		ID3D11DeviceContext* const pContext11 );


	//�`��(�����_�����O)(��DX9MESH����Main����2���݂���̂Œ���).
	virtual void Render( const D3DXMATRIX& mView, const D3DXMATRIX& mProj,
				 const D3DXVECTOR3 &vEye );

	void SetScale( const float fScale ){
		m_fScale = fScale;
	}


	D3DXVECTOR3		m_vPos;	//�ʒu.

	int		m_AnimCount;//UV�X�N���[��.

	bool	m_bDispFlg;//�\���t���O.


protected:

	//�V�F�[�_�쐬.
	HRESULT InitShader();
	////���f���쐬.
	virtual HRESULT InitModel();

	//�����f���̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;	//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;	//���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;		//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pConstantBuffer;	//�R���X�^���g�o�b�t�@.

	//�����f�����Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;	//���_�o�b�t�@.

	ID3D11ShaderResourceView*	m_pTexture;		//�e�N�X�`��.
	ID3D11SamplerState*			m_pSampleLinear;//�e�N�X�`���̃T���v���[:/�e�N�X�`���Ɋe��t�B���^��������.



	float m_fScale;


};


#endif	//#ifndef SPRITE_H_
