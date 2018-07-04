#pragma once

//#include "Global.h"
#include "Sprite2DCenter.h"


class clsRENDER_AT_START_UP
{
public:
	clsRENDER_AT_START_UP(
		ID3D11Device*			const pDevice,
		ID3D11DeviceContext*	const pContext,
		IDXGISwapChain*			const pSwapChain,
		ID3D11RenderTargetView*	const pBackBuffer_TexRTV,
		ID3D11DepthStencilView*	const pBackBuffer_DSTexDSV );
	~clsRENDER_AT_START_UP();

	//���[�v����.
	void Loop();


private:

	//�`��.
	void Render();

	std::unique_ptr< clsSPRITE2D_CENTER > m_upRogo;

	ID3D11Device*			m_wpDevice;
	ID3D11DeviceContext*	m_wpContext;			//�f�o�C�X�R���e�L�X�g.
	IDXGISwapChain*			m_wpSwapChain;			//�X���b�v�`�F�[��.
	ID3D11RenderTargetView*	m_wpBackBuffer_TexRTV;	//�����_�[�^�[�Q�b�g�r���[.
	ID3D11DepthStencilView*	m_wpBackBuffer_DSTexDSV;//�f�v�X�X�e���V���r���[.

};


