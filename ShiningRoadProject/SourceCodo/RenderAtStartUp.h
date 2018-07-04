#pragma once

//#include "Global.h"
#include "Sprite2DCenter.h"
#include <vector>

class clsRENDER_AT_START_UP
{
public:
	clsRENDER_AT_START_UP(
		ID3D11Device*			 const pDevice,
		ID3D11DeviceContext*	 const pContext,
		IDXGISwapChain*			 const pSwapChain,
		ID3D11RenderTargetView*	 const pBackBuffer_TexRTV,
		ID3D11DepthStencilView*	 const pBackBuffer_DSTexDSV,
		ID3D11DepthStencilState* const pDepthStencilState );
	~clsRENDER_AT_START_UP();

	//���[�v����.
	void Loop();

	//�I������.
	void End();

private:

	//�`��.
	void Render();

	//�[�x�e�X�g(Z�e�X�g)ON/OFF�ؑ�.
	void SetDepth( bool isOn );

	std::vector< std::unique_ptr< clsSPRITE2D_CENTER > > m_vupRogo;

	bool						m_bEnd;//true�ɂȂ�����I��.

	ID3D11Device*				m_wpDevice;
	ID3D11DeviceContext*		m_wpContext;			//�f�o�C�X�R���e�L�X�g.
	IDXGISwapChain*				m_wpSwapChain;			//�X���b�v�`�F�[��.
	ID3D11RenderTargetView*		m_wpBackBuffer_TexRTV;	//�����_�[�^�[�Q�b�g�r���[.
	ID3D11DepthStencilView*		m_wpBackBuffer_DSTexDSV;//�f�v�X�X�e���V���r���[.
	ID3D11DepthStencilState*	m_wpDepthStencilState;	//�[�x(Z)�e�X�g�ݒ�.
};

