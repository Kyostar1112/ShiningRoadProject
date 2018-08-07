#pragma once

#include "Global.h"

#if _DEBUG
#include "DebugText.h"
#endif//#if _DEBUG

#include "CharaStatic.h"

#include "PtrGroup.h"

#include "Sprite2DCenter.h"


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
	void Render();
	//----- �e�V�[������ -----//.


	//���C���܂ő���グ��.
	D3DXVECTOR3 GetCameraPos() const;
	D3DXVECTOR3 GetCameraLookPos() const;

protected:

	//----- �e�V�[�����Ƃ̊֐� -----//.
	virtual void CreateProduct() = 0;//�e�V�[����Create.
	virtual void UpdateProduct( enSCENE &enNextScene ) = 0;//�e�V�[����Update.
	virtual void RenderProduct( const D3DXVECTOR3 &vCamPos ) = 0;//�e�V�[����Render.
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

	//----- Render�p -----//.
	//�[�x�e�X�g(Z�e�X�g)�@ON/OFF�ؑ�.
	void SetDepth( const bool isOn );
	D3DXMATRIX		m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX		m_mProj;	//�v���W�F�N�V�����s��.
	D3DXVECTOR3		m_vLight;	//���C�g�̕���.

	//---�p�����RenderProduct�Ŏg�p����---.
	void SetViewPort( D3D11_VIEWPORT* const pVp, const D3DXVECTOR3 &vCamPos, const D3DXVECTOR3 &vCamLookPos );
	//���C���Ŏg���Ă���r���[�|�[�g�̃|�C���^�擾( SetViewPort�֐��̈����p ).
	D3D11_VIEWPORT* GetViewPortMainPtr();
	//----- Render�p -----//.


	//�f�o�b�O�e�L�X�g�N���X.
#if _DEBUG
//	clsDebugText*	m_upText;
	std::unique_ptr< clsDebugText >	m_upText;
	//�f�o�b�N�J�e�L�X�g�̕\��.
	virtual void RenderDebugText();
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
	clsROBO_STATUS*			m_wpRoboStatus;
	clsBLACK_SCREEN*		m_wpBlackScreen;


private:
	//----- Render�p -----//.
	//�J�����֐�.
	void Camera();
	//�v���W�F�N�V�����֐�.
	void Proj();
	//----- Render�p -----//.

	//�f�o�b�O�p�V�[���؂�ւ�.
	void DebugChangeScene( enSCENE &enNextScene ) const;

	//�Ó]���ɑ҂��Ă���邽�߂ɕK�v.
	enSCENE m_enNextScene;

	//2DSp�p.
	D3D10_VIEWPORT* m_wpViewPort10;
	//�����p( ���C���̃r���[�|�[�g ).
	D3D11_VIEWPORT* m_wpViewPort11;
	
	//�f�f�p( �����ݎg���Ă���r���[�|�[�g ).
	D3D11_VIEWPORT* m_wpViewPortUsing;


	ID3D11DepthStencilState*	m_wpDepthStencilState;//�[�x(Z)�e�X�g�ݒ�.


};
