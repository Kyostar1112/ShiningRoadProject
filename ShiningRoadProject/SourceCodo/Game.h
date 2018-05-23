#pragma once

#include "FactoryScene.h"
#include "FactoryCamera.h"
#include "DxInput.h"



//�Q�[���̓����͂��̃N���X�̒��ōs��.
class clsGAME
{
public:
	//�����̓V�[���̏������ɕK�v�Ȃ���.
	clsGAME( 
		const HWND hWnd, 
		ID3D11Device* const pDevice, 
		ID3D11DeviceContext* const pContext,
		D3D10_VIEWPORT* const pViewPort );
	~clsGAME();

	//new����Ɏg��.
	void Create();
	//���t���[���g��.
	void Update();
	//���t���[���g��.
	void Render();


	//�����̃V�[���ɐ؂�ւ�.
	void SwitchScene( const enSCENE enNextScene );

	//���b�v�֐�.
	D3DXVECTOR3 GetCameraPos() const;
	D3DXVECTOR3 GetCameraLookPos() const;


private:


	//�V�[���N���X.
	clsSCENE_BASE*		m_pScene;
	//�V�[���̃t�@�N�g��.
	clsSCENE_FACTORY* m_pSceneFactory;

	//�J����.
	clsCAMERA_BASE*	m_spCamera;
	//�J�����t�@�N�g��.
	clsFACTORY_CAMERA* m_pCameraFactory;

	//�V�[���������ɕK�v�ȃ|�C���^�̂܂Ƃ�.
	clsPOINTER_GROUP* m_pPtrGroup; 


	//�����Ƃ�delete���Ȃ���null���Ă�.
	HWND m_hWnd;
	ID3D11Device*			m_wpDevice;		//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_wpContext;	//�f�o�C�X�R���e�L�X�g.
	//2DSp�p.
	D3D10_VIEWPORT* m_wpViewPort;

	//�W���C�X�e�B�b�N.
	clsDxInput*		m_spDxInput;

	//���\�[�X�N���X.
	clsResource*	m_pResource;
	//�G�t�F�N�g.
	clsEffects*		m_pEffect;
	//�T�E���h.
	clsSOUND_MANAGER* m_pSound;


};


