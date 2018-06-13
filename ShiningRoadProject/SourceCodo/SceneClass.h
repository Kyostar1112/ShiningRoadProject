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
	void Update( enSCENE &nextScene );
	//�V�[�����̃I�u�W�F�N�g�̕`��֐��̂܂Ƃ�.
	void Render();
	//----- �e�V�[������ -----//.



	//���C���܂ő���グ��.
	D3DXVECTOR3 GetCameraPos() const;
	D3DXVECTOR3 GetCameraLookPos() const;

protected:


	//----- �e�V�[�����Ƃ̊֐� -----//.
	virtual void CreateProduct() = 0;//�e�V�[����Create.
	virtual void UpdateProduct( enSCENE &nextScene ) = 0;//�e�V�[����Update.
	virtual void RenderProduct( const D3DXVECTOR3 &vCamPos ) = 0;//�e�V�[����Render.
	//----- �e�V�[�����Ƃ̊֐� -----//.

	//3D���W���X�N���[��( 2D )���W�ւƕϊ�����.
	//dimensions(����) conversion(�ϊ�).
	//�߂�l��2D���W.
	D3DXVECTOR3 ConvDimPos( const D3DXVECTOR3 &v3DPos );


	//�f�o�b�O�p�V�[���؂�ւ�.
	//���ׂẴV�[���̈�ԉ��ɒu���Ă���.
	void DebugChangeScene( enSCENE &nextScene ) const;


	//----- Render�p -----//.
	//�J�����֐�.
	void Camera();
	//�v���W�F�N�V�����֐�.
	void Proj();
	//�[�x�e�X�g(Z�e�X�g)�@ON/OFF�ؑ�.
	void SetDepth( const bool isOn );
	D3DXMATRIX		m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX		m_mProj;	//�v���W�F�N�V�����s��.
	D3DXVECTOR3		m_vLight;	//���C�g�̕���.
	//----- Render�p -----//.


//���N���X�̃|�C���^�͊��N���X�Ŕj�����܂�.
//�h���N���X�ł͔j�����Ȃ��ł�������.

	//�f�o�b�O�e�L�X�g�N���X.
#if _DEBUG
	clsDebugText*	m_upText;
	//�f�o�b�N�J�e�L�X�g�̕\��.
	virtual void RenderDebugText();
#endif//#if _DEBUG


	//�ȉ��A�����Ƃ�delete���Ȃ���null���Ă�( ���̊��N���X�̃f�X�g���N�^�ł���Ă��܂� ).
	//�J����( �K�v�Ȃ�΂���������āA�V�[�����ƂɈقȂ����@�\�̃J���������܂��傤 ).
	ID3D11Device*				m_wpDevice;	//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*		m_wpContext;//�f�o�C�X�R���e�L�X�g.
	D3D10_VIEWPORT*				m_wpViewPort;//2DSp�p.
	ID3D11DepthStencilState*	m_wpDepthStencilState;//�[�x(Z)�e�X�g�ݒ�.
	clsPOINTER_GROUP*	m_wpPtrGroup;
	clsDxInput*			m_wpDxInput;
	clsResource*		m_wpResource;
	clsEffects*			m_wpEffects;
	clsSOUND_MANAGER*	m_wpSound;
	clsCAMERA_BASE*		m_wpCamera;	
	clsROBO_STATUS*		m_wpRoboStatus;

};
