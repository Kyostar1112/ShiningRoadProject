#pragma once

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )	

//============================================================
//	�C���N���[�h.
//============================================================
#include "MyMacro.h"

#include "TextSpriteStruct.h"

#include <string>

//UI�Ƃ��ĕ���������.
class clsUiText
{
public:
	clsUiText();
	~clsUiText();

	//�e�L�X�g�̍��悹�A�E��.
	enum class enPOS : UINT
	{
		LEFT,
		RIGHT,
		MIDDLE,
	};

	HRESULT Create( 
		ID3D11DeviceContext* const pContext,
		const DWORD &dwWidth, const DWORD &dwHeight,
		const float fScale );


	//�����_�����O�֐�.
	//�f�t�H���g������true�ɂ���ƉE�[���w����W�ɗ���.
	void Render( const enPOS enPos = enPOS::LEFT );

	void SetPos( const D3DXVECTOR2 &vPos );
	D3DXVECTOR3 GetPos(){
		D3DXVECTOR3 g;
		g.x = m_vPos.x;
		g.y = m_vPos.y;
		g.z = 0.0f;
		return g;
	};
	void AddPos( const D3DXVECTOR2 &vPos );

	void SetScale( const float fScale );

	void SetText( const char* sText );

	void SetColor( const D3DXVECTOR4 &vColor = { 1.0f, 1.0f, 1.0f, 1.0f } );

private:

	//�t�H���g�����_�����O�֐�.
	void RenderFont( const int FontIndex, const float x, const float y, const float z ) const;

	//����(�A���t�@�u�����h)�ݒ�̐؂�ւ�.
	void SetBlend( const bool flg );

	//���A�v���Ɉ��.
	ID3D11Device*			m_pDevice11;		//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pDeviceContext11;	//�f�o�C�X�R���e�L�X�g.

	//�����f���̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;	//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;	//���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;		//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pConstantBuffer;	//�R���X�^���g�o�b�t�@.

	//�����f�����Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer[100];	//���_�o�b�t�@(100��).

	ID3D11ShaderResourceView*	m_pAsciiTexture;//�A�X�L�[�e�N�X�`��.
	ID3D11SamplerState*			m_pSampleLinear;//�e�N�X�`���̃T���v���[:/�e�N�X�`���Ɋe��t�B���^��������.

	ID3D11BlendState*			m_pBlendState;	//�u�����h�X�e�[�g.


	DWORD	m_dwWindowWidth;	//�E�B���h�E��.
	DWORD	m_dwWindowHeight;	//�E�B���h�E����.

	float		m_fKerning[100];	//�J�[�����O(100��).
	D3DXVECTOR2 m_vPos;
	float		m_fScale;			//�g�k�l.
//	float		m_fAlpha;			//���ߒl.
	D3DXVECTOR4	m_vColor;		//�F.

	std::string m_sText;//�`�敶��.

	D3DXMATRIX m_mView;	//�r���[�s��.
	D3DXMATRIX m_mProj;	//�v���W�F�N�V�����s��.
	


};
