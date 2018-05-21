#define _CRT_SECURE_NO_WARNINGS
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )
//============================================================
//	�C���N���[�h.
//============================================================
#include <Windows.h>

//���������[�N���o�p.
#include <crtdbg.h>

#include <D3DX11.h>
#include <D3D11.h>

#include <D3DX10.h>//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>

#include "Global.h"
#include "MyMacro.h"

#if _DEBUG
#include "DebugText.h"
#include "Ray.h"		//���C�\���N���X.
#endif//#if _DEBUG


//#include "Sound.h"		//�T�E���h�N���X.
//
//
//
//#include "Effects.h"//Effekseer���Ǘ�����N���X.
//
//
//#include "CXInput.h"
//
//#include "Resource.h"
//
//#include "File.h"


#include "Game.h"



//============================================================
//	���C�u����.
//============================================================
#pragma comment( lib, "winmm.lib" )

#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )

#pragma comment( lib, "d3dx10.lib" )//�uD3DX�`�v�̒�`�g�p���ɕK�v.



//============================================================
//	�萔.
//============================================================
#define WND_TITLE	"��]���N"
#define APR_NAME	"ShiningRoadProject"


//============================================================
//	�\����.
//============================================================
////�J�������.
//struct CAMERA
//{
//	D3DXVECTOR3 vEye;	//�J�����ʒu.
//	D3DXVECTOR3 vLook;	//�����ʒu.
//	float		fYaw;	//��]�l.
//	D3DXMATRIX	mRot;	//��]�s��.
//};


//============================================================
//	�񋓑�.
//============================================================

//============================================================
//	���C���N���X.
//============================================================
class clsMain
{
public:
	clsMain();	//�R���X�g���N�^.
	~clsMain();	//�f�X�g���N�^.

	//�E�B���h�E�������֐�.
	HRESULT InitWindow(
		HINSTANCE hInstance,
		INT x, INT y, INT width, INT height,
		LPSTR WindowName);

	//�E�B���h�E�֐�(���b�Z�[�W���̏���).
	LRESULT MsgProc(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam );

	//DirectX������.
	HRESULT InitD3D();
	//Direct3D�I������.
	void DestroyD3D();

	//���b�Z�[�W���[�v.
	void Loop();

private:

	//�A�v���P�[�V�������C������.
	void AppMain();
	//�`��(�����_�����O).
	void Render();


	//���b�V���ǂݍ��݊֐�(�܂Ƃ߂�).
	HRESULT ReadMesh();

#if _DEBUG
	//�X�t�B�A�쐬.
	HRESULT InitSphere( clsDX9Mesh* pMesh, float fScale = 0.7f );
	//�X�t�B�A�Փ˔���֐�.
	bool Collision( clsDX9Mesh* pAttacker, clsDX9Mesh* pTarget );
	//�o�E���f�B���O�{�b�N�X�쐬.
	HRESULT InitBBox( clsDX9Mesh* pMesh );
	//�{�b�N�X�Փ˔���֐�.
	bool BBoxCollision( clsDX9Mesh* pAttacker, clsDX9Mesh* pTarget );

	//�f�o�b�O�e�L�X�g�N���X.
	clsDebugText*	m_pText;


	//���C�\���N���X.
	clsRay*			m_pRayV;	//����.
	clsRay*			m_pRayFB;	//�O��.
	clsRay*			m_pRayH;	//���E.


#endif //#if _DEBUG


	//�[�x�e�X�g(Z�e�X�g)�@ON/OFF�ؑ�.
	void SetDepth( const bool bFlg );

	//�{�[���̍��W���Ƃ�(���b�v�֐�).
	void GetPosFromBone( clsD3DXSKINMESH* skinMesh, char BoneName[], D3DXVECTOR3& Pos );

	//�J�����֐�.
	void Camera();
	//�v���W�F�N�V�����֐�.
	void Proj();




	//�f�o�b�N�J�e�L�X�g�̕\��.
	void RenderDebugText();




	



	HWND	m_hWnd;	//�E�B���h�E�n���h��.

	//���A�v���Ɉ��.
	ID3D11Device*			m_pDevice;			//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pDeviceContext;	//�f�o�C�X�R���e�L�X�g.
	IDXGISwapChain*			m_pSwapChain;		//�X���b�v�`�F�[��.
	ID3D11RenderTargetView*	m_pBackBuffer_TexRTV;//�����_�[�^�[�Q�b�g�r���[.
	ID3D11Texture2D*		m_pBackBuffer_DSTex;//�o�b�N�o�b�t�@.
	ID3D11DepthStencilView*	m_pBackBuffer_DSTexDSV;//�f�v�X�X�e���V���r���[.

	D3DXVECTOR3		m_vLight;	//���C�g�̕���.

	D3DXMATRIX		m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX		m_mProj;	//�v���W�F�N�V�����s��.

	//�[�x(Z)�e�X�g�ݒ�.
	ID3D11DepthStencilState* m_pDepthStencilState;



	//�Q�[��.
	clsGAME*		m_pGame;






#ifdef Tahara
	//ConvDimPos�̎��O����.
	void SetViewPort10( D3D11_VIEWPORT* Vp );
	//3D���W�̃X�N���[��( 2D )���W�ϊ�.dimensions(����) conversion(�ϊ�)
	D3DXVECTOR3 ConvDimPos( D3DXVECTOR3 v2DPos, D3DXVECTOR3 v3DPos );
	//2DSp�p.
	D3D10_VIEWPORT m_ViewPort;

#endif//#ifdef Tahara






};