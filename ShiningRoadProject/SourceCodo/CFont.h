#ifndef _C_FONT_H_
#define _C_FONT_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Global.h"


//�ײ���Đݒ�(�����I��16�޲Ăɐݒ肷��)
#define ALIGN16 _declspec(align(16))

//const int TEXT_H = 256;	//�s��
//const int TEXT_W = 256;	//�s��



class clsFont
{
public:

	clsFont( 
		ID3D11Device* const pDevice, 
		ID3D11DeviceContext* const pContext );
	~clsFont();

	void Create( const char *sTextFileName );//�V�[���J�n���Ɏg��.
	void Release();							//�V�[���I�����Ɏg��.

	void Render( int iTex, int iCharNum );



	void SetPos( const D3DXVECTOR3 &vPos );
	D3DXVECTOR3 GetPos();

	void SetScale( const float fScale );
	float GetScale();

	void SetColor( const D3DXVECTOR4 &vColor );
	void SetAlpha( const float fAlpha );

	
private:

	//̫�č\����.
	struct strFont
	{
		int iFontDispSpeed;
		int iFontAutoFlg;
	}m_strFont;


	//�\����
	struct FONTSHADER_CONSTANT_BUFFER
	{
		ALIGN16 D3DXMATRIX mW;			//�ʒu�ƶ�׈ʒu�ƕ\����ʐݒ�
		ALIGN16 float ViewPortWidth;	//�װ(RGBA�̌^�ɍ��킹��)
		ALIGN16 float ViewPortHeight;	//UV���W
		ALIGN16 float Alpha;	//���ߒl
		ALIGN16 D3DXVECTOR2 Uv;	//UV���W
		ALIGN16 D3DXVECTOR4 Color;	//UV���W
	};

	//���_�̍\����
	struct FONT_VERTEX
	{
		D3DXVECTOR3 Pos;		//�ʒu
		D3DXVECTOR2 Tex;		//ø���
	};

	//̫�ď��Ǎ�.
	bool LoadFont();
	//����ލ쐬.
	HRESULT CreateShader();
	//�ްï������ލ쐬.
	HRESULT CreateVertexBuffer();
	//�萔�ޯ̧�쐬.
	HRESULT CreateConstantBuffer();
	void LoadTextFile( const char *FileName );//3�s, ������.
	HRESULT	CreateTexture();
	void SetBlendSprite( const bool isAlpha );

	D3DXVECTOR3		m_vPos;			//�ʒu
	float			m_fScale;		//�g�k
	D3DXVECTOR4		m_vColor;		//�F
	float			m_fAlpha;
		

	int				m_iTextRow;//�e�L�X�g�̍s��.

	int				m_iFontH;					//�ǂݍ��񂾕��͂����s���邩.

	DESIGNVECTOR		m_Design;
	RECT				m_Rect;			//�w�蕝�ݒ�.

	std::vector< std::string > 		m_sTextData;//[TEXT_H][TEXT_W]	//����.

	int m_fFontSize;
	int m_fFontMarginX;
	int m_fFontMarginY;


	//�e�N�X�`���֘A
	std::vector< ID3D11Texture2D* >		  m_vpTex2D;//[TEXT_H];//2�c�e�N�X�`��
	std::vector< std::vector< ID3D11ShaderResourceView* > > m_vvpAsciiTexture;//[TEXT_H][TEXT_W]; //ø����


	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pContext;

	//����غ�ݗp
	ID3D11VertexShader* m_pVertexShader;	//���_����ް
	ID3D11InputLayout*	m_pVertexLayout;	//���_ڲ���
	ID3D11PixelShader*  m_pPixelShader;		//�߸�ټ���ް
	ID3D11Buffer*		m_pConstantBuffer;	//�ݽ����ޯ̧
	ID3D11Buffer*		m_pVertexBuffer;	//���_�o�b�t�@	

	ID3D11BlendState*	m_pBlendState;		//�����޽ð�
	ID3D11SamplerState* m_pSampleLinear;	//ø����̻���װ



};

#endif _C_FONT_H_