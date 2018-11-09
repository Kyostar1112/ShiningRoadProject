#ifndef SCENE_BASE_H_
#define SCENE_BASE_H_

//���Ă���ƃo�b�N�o�b�t�@�ł͂Ȃ���������e�N�X�`���ɕ`�悷��.
//#define RENDER_SCREEN_TEXTURE_


#include "Global.h"

#if _DEBUG
#include "DebugText.h"
#endif//#if _DEBUG

#include "CharaStatic.h"

#include "PtrGroup.h"

#include "Sprite2DCenter.h"

#include "UiText.h"

//#include "KeyInput.h"


//================================//
//========== ���N���X ==========//
//================================//
class clsSCENE_BASE
{
public:
	//�����̓��\�[�X�Ȃǂ̃|�C���^�̂܂Ƃ�.
	clsSCENE_BASE( clsPOINTER_GROUP* const ptrGroup );
	virtual ~clsSCENE_BASE();

	//----- �e�V�[������ -----//.
	//�V�[���쐬����ɁuSceneManager.cpp�v�́uSwitchScene�v�֐����Ŏg�p����Ă���.
	void Create();
	//���[�v���̏���( �������֐����ŕύX����ƍ��̃V�[�����j������A.
	//				  �w�肵���V�[������������� ).
	void Update( enSCENE &enNextScene );
	//�V�[�����̃I�u�W�F�N�g�̕`��֐��̂܂Ƃ�.
	void Render( 
		ID3D11RenderTargetView* const pBackBuffer_TexRTV,
		ID3D11DepthStencilView* const pDepthStencilView );
	//----- �e�V�[������ -----//.


	//���C���܂ő���グ��.
	D3DXVECTOR3 GetCameraPos() const;
	D3DXVECTOR3 GetCameraLookPos() const;

protected:

	//----- �e�V�[�����Ƃ̊֐� -----//.
	virtual void CreateProduct() = 0;//�e�V�[����Create.
	virtual void UpdateProduct( enSCENE &enNextScene ) = 0;//�e�V�[����Update.
	virtual void RenderProduct( const D3DXVECTOR3 &vCamPos ) = 0;//�e�V�[����Render.
	virtual void RenderUi() = 0;//�e�V�[���́u UI�� �vRender.
	//----- �e�V�[�����Ƃ̊֐� -----//.

	//3D���W���X�N���[��( 2D )���W�ւƕϊ�����.
	//dimensions(����) conversion(�ϊ�).
	//�߂�l��2D���W.
	D3DXVECTOR3 ConvDimPos( const D3DXVECTOR3 &v3DPos );


	//���j���[����Ɏg���Ă�.
	bool isPressRight();
	bool isPressLeft();
	bool isPressUp();
	bool isPressDown();
	bool isPressEnter();
	bool isPressExit();

	//�������ςȂ��œ���( true�Ȃ�X�e�B�b�N�L�� ).
	bool isPressHoldRight( bool isWithStick = true );
	bool isPressHoldLeft ( bool isWithStick = true );
	bool isPressHoldUp	 ( bool isWithStick = true );
	bool isPressHoldDown ( bool isWithStick = true );
//	int m_iHoldFreamRight;
//	int m_iHoldFreamLeft;
//	int m_iHoldFreamUp;
//	int m_iHoldFreamDown;
	struct HOLD_STATE
	{
		int iHoldFream;
		int iFirstPush;//�ŏ��̈��.
		HOLD_STATE()
		:iHoldFream( 0 )
		,iFirstPush( 0 )
		{}
	};
	HOLD_STATE m_HoldRight;
	HOLD_STATE m_HoldLeft;
	HOLD_STATE m_HoldUp;
	HOLD_STATE m_HoldDown;

	//----- Render�p -----//.
	//�[�x�e�X�g(Z�e�X�g)�@ON/OFF�ؑ�.
	void SetDepth( const bool isOn );
	D3DXMATRIX		m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX		m_mProj;	//�v���W�F�N�V�����s��.
	D3DXVECTOR3		m_vLight;	//���C�g�̕���.

	//---�p�����RenderProduct�Ŏg�p����---.
	void SetViewPort( 
		D3D11_VIEWPORT* const pVp, 
		const D3DXVECTOR3 &vCamPos, 
		const D3DXVECTOR3 &vCamLookPos,
		const float fWndW, const float fWndH );
	//���C���Ŏg���Ă���r���[�|�[�g�̃|�C���^�擾( SetViewPort�֐��̈����p ).
	D3D11_VIEWPORT* GetViewPortMainPtr();
	//----- Render�p -----//.



	//�f�o�b�O�e�L�X�g�N���X.
#if _DEBUG
//	clsDebugText*	m_upText;
	std::unique_ptr< clsDebugText >	m_upText;
	//�f�o�b�N�J�e�L�X�g�̕\��.
	virtual void RenderDebugText();
	//BGM�̃`�F�b�N.
	void DebugBgm();

#endif//#if _DEBUG


	//���N���X�̃|�C���^�͊��N���X�Ŕj�����܂�.
	//�h���N���X�ł͔j�����Ȃ��ł�������.

	//�ȉ��A�����Ƃ�delete���Ȃ���null���Ă�( ���̊��N���X�̃f�X�g���N�^�ł���Ă��܂� ).
	//�J����( �K�v�Ȃ�΂���������āA�V�[�����ƂɈقȂ����@�\�̃J���������܂��傤 ).
	clsPOINTER_GROUP*		m_wpPtrGroup;//�G�t�F�N�g����ʉ���K�v�Ƃ��郍�{�����ׂ̈ɂ�private�ɂ���킯�ɂ͂����Ȃ�.
	ID3D11Device*			m_wpDevice;	//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_wpContext;//�f�o�C�X�R���e�L�X�g.
	clsDxInput*				m_wpDxInput;
	clsXInput*				m_wpXInput;
	clsResource*			m_wpResource;
	clsEffects*				m_wpEffects;
	clsSOUND_MANAGER_BASE*	m_wpSound;
	clsCAMERA_BASE*			m_wpCamera;	
	clsROBO_STATUS_PLAYER*	m_wpRoboStatus;
	clsBLACK_SCREEN*		m_wpBlackScreen;
	clsFont*				m_wpFont;

private:

	HRESULT CreateDepthStencilState();

	//----- Render�p -----//.
	//�J�����֐�.
	void Camera();
	//�v���W�F�N�V�����֐�.
	void Proj();
	//----- Render�p -----//.

	//�f�o�b�O�p�V�[���؂�ւ�.
	void DebugChangeScene( enSCENE &enNextScene ) const;

private:

	//�Ó]���ɑ҂��Ă���邽�߂ɕK�v.
	enSCENE m_enNextScene;

	//2DSp�p.
	D3D10_VIEWPORT* m_wpViewPort10;
	//�����p( ���C���̃r���[�|�[�g ).
	D3D11_VIEWPORT* m_wpViewPort11;
	
	//�f�f�p( �����ݎg���Ă���r���[�|�[�g ).
	D3D11_VIEWPORT* m_wpViewPortUsing;

	//���son, off.
	ID3D11DepthStencilState* m_pDepthStencilStateOn;
	ID3D11DepthStencilState* m_pDepthStencilStateOff;

#ifdef RENDER_SCREEN_TEXTURE_
	//�����_�����O�e�N�X�`���p.
	ID3D11Texture2D*			m_pScreenTex;
	ID3D11RenderTargetView*		m_pScreenRTV;
	ID3D11ShaderResourceView*	m_pScreenSRV;
	ID3D11SamplerState*			m_pScreenSmp;
	ID3D11VertexShader*			m_pScreenVS;
	ID3D11PixelShader*			m_pScreenPS;
	HRESULT CreateScreenTexture();
	HRESULT CreateScreenShaderTexture();
	//Rendertarget���e�N�X�`���ɂ���.
	void SetRenderTargetTexture( ID3D11DepthStencilView* const pDepthStencilView );
	//�e�N�X�`���̓��e����ʂɕ`��.
	void RenderWindowFromTexture( 
		ID3D11RenderTargetView* const pBackBuffer_TexRTV,
		ID3D11DepthStencilView* const pDepthStencilView );
#endif//#ifdef RENDER_SCREEN_TEXTURE_


};
#endif//#ifndef SCENE_BASE_H_