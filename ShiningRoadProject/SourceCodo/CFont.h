#ifndef _C_FONT_H_
#define _C_FONT_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Global.h"


//�A���C�������g�ݒ�(�����I��16�o�C�g�ɐݒ肷��).
#define ALIGN16 _declspec( align ( 16 ) )


//���{���UI�p.
class clsFont
{
public:

	clsFont( 
		ID3D11Device* const pDevice, 
		ID3D11DeviceContext* const pContext );
	~clsFont();

	void Create( const char *sTextFileName );//�V�[���J�n���Ɏg��.
	void Release();							//�V�[���I�����Ɏg��.

	void Render( const int iTex, const int iCharNum = -1 );



	void SetPos( const D3DXVECTOR3 &vPos );
	D3DXVECTOR3 GetPos();

	void SetScale( const float fScale );
	float GetScale();

	void SetColor( const D3DXVECTOR4 &vColor );
	void SetAlpha( const float fAlpha );

	
private:

	//�u�����h�X�e�[�g�쐬.
	HRESULT CreateBlendState();
	//�V�F�[�_�쐬.
	HRESULT CreateShader();
	//�o�[�e�b�N�X�V�F�[�_�쐬.
	HRESULT CreateVertexBuffer();
	//�萔�o�b�t�@�쐬.
	HRESULT CreateConstantBuffer();
	HRESULT LoadTextFile( const char *FileName );//3�s, ������.
	HRESULT	CreateTexture();

	void SetBlend( const bool isAlpha );


private:

	//�\����.
	struct FONTSHADER_CONSTANT_BUFFER
	{
		ALIGN16 D3DXMATRIX mW;			//�ʒu�ƃJ�����ʒu�ƕ\����ʐݒ�.
		ALIGN16 float ViewPortWidth;	//�J���[(RGBA�̌^�ɍ��킹��).
		ALIGN16 float ViewPortHeight;	//UV���W.
		ALIGN16 float Alpha;	//���ߒl.
		ALIGN16 D3DXVECTOR2 Uv;	//UV���W.
		ALIGN16 D3DXVECTOR4 Color;	//UV���W.
	};

	//���_�̍\����.
	struct FONT_VERTEX
	{
		D3DXVECTOR3 Pos;		//�ʒu.
		D3DXVECTOR2 Tex;		//�e�N�X�`��.
	};

	D3DXVECTOR3		m_vPos;			//�ʒu.
	float			m_fScale;		//�g�k.
	D3DXVECTOR4		m_vColor;		//�F.
	float			m_fAlpha;
		
	//�e�N�X�`���T�C�Y( �𑜓x ).
	int		m_iFontSize;
	//�����ƕ����̌���.
	float	m_fFontMarginX;
	float	m_fFontMarginY;
	float	m_fIndentionPosint;//���s����x���W.

	std::vector< std::string > 		m_sTextData;//[ TEXT_H ][ TEXT_W ]	//����.

	DESIGNVECTOR		m_Design;

	//�e�N�X�`���֘A.
	std::vector< ID3D11Texture2D* >							m_vpTex2D;//[ TEXT_H ];//2�c�e�N�X�`��.
	std::vector< std::vector< ID3D11ShaderResourceView* > > m_vvpAsciiTexture;//[ TEXT_H ][ TEXT_W ]; //�e�N�X�`��.


	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pContext;

	//�|���S���p.
	ID3D11VertexShader* m_pVertexShader;	//���_�V�F�[�_�[.
	ID3D11InputLayout*	m_pVertexLayout;	//���_���C�A�E�g.
	ID3D11PixelShader*  m_pPixelShader;		//�s�N�Z���V�F�[�_�[.
	ID3D11Buffer*		m_pConstantBuffer;	//�R���X�^���g�o�b�t�@.
	ID3D11Buffer*		m_pVertexBuffer;	//���_�o�b�t�@	.

	ID3D11SamplerState* m_pSampleLinear;	//�e�N�X�`���̃T���v���[.

	ID3D11BlendState*	m_pBlendState[ enBLEND_STATE_size ];		//�u�����h�X�e�[�g.

};

#endif _C_FONT_H_