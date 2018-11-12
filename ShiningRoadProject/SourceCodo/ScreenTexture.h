#ifndef SCREEN_TEXTURE_H_
#define SCREEN_TEXTURE_H_

#include "Global.h"

//�����_�����O�e�N�X�`���p.
//�����Ȃ�o�b�N�o�b�t�@�ł͂Ȃ��������񂱂��ɕ`�悷��.
class clsSCREEN_TEXTURE
{
public:
	clsSCREEN_TEXTURE(
		ID3D11DeviceContext* const pContext );
	~clsSCREEN_TEXTURE();


	//Rendertarget���e�N�X�`���ɂ���.
	void SetRenderTargetTexture( ID3D11DepthStencilView* const pDepthStencilView );
	//�e�N�X�`���̓��e����ʂɕ`��.
	void RenderWindowFromTexture( 
		ID3D11RenderTargetView* const pBackBuffer_TexRTV,
		ID3D11DepthStencilView* const pDepthStencilView );

	//true�Ńm�C�Y.
	void SetNoiseFlag( const bool isNoise ){
		m_isNoise = isNoise;
	};

private:

	HRESULT CreateTexture();
	HRESULT CreateShader();
	HRESULT CreateConstantBuffer();

private:


	bool		m_isNoise;

	D3DXVECTOR2 m_vNoiseStart;
	D3DXVECTOR2 m_vNoiseEnd;


	ID3D11Device*				m_wpDevice;
	ID3D11DeviceContext*		m_wpContext;


	ID3D11Texture2D*			m_pTexture;
	ID3D11RenderTargetView*		m_pRenderTargetView;
	ID3D11ShaderResourceView*	m_pShaderResourceView;
	ID3D11SamplerState*			m_pSamplerState;
	ID3D11VertexShader*			m_pVertexShader;	
	ID3D11PixelShader*			m_pDefaultPS;	//�ʏ펞.	
	ID3D11PixelShader*			m_pNoisePS;		//�m�C�Y.
	ID3D11Buffer*				m_pConstantBuffer;

};

#endif//#ifndef SCREEN_TEXTURE_H_