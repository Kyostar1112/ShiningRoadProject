#pragma once

#include "FactoryScene.h"
#include "FactoryCamera.h"
#include "FactorySoundManager.h"


#include "DxInput.h"
#include "CXInput.h"

#include "BlackScreen.h"

#include <memory>

//�Q�[���̓����͂��̃N���X�̒��ōs��.
class clsGAME
{
public:
	//�����̓V�[���̏������ɕK�v�Ȃ���.
	clsGAME( 
		const HWND hWnd, 
		ID3D11Device* const pDevice, 
		ID3D11DeviceContext* const pContext,
		D3D10_VIEWPORT* const pViewPort,
		ID3D11DepthStencilState* const pDepthState );
	~clsGAME();

	//new����Ɏg��.
	void Create();
	//���t���[���g��.
	void Update();
	//���t���[���g��.
	void Render();


	//���b�v�֐�.
	D3DXVECTOR3 GetCameraPos() const;
	D3DXVECTOR3 GetCameraLookPos() const;


private:

	//�����̃V�[���ɐ؂�ւ�.
	void SwitchScene( const enSCENE enNextScene, const bool bStartUp = false );

	//�V�[���N���X.
	clsSCENE_BASE*		m_upScene;
	//�V�[���̃t�@�N�g��.
	std::unique_ptr< clsSCENE_FACTORY > m_upSceneFactory;

	//�J����.
	clsCAMERA_BASE*	m_spCamera;
	//�J�����t�@�N�g��.
	std::unique_ptr< clsFACTORY_CAMERA > m_upCameraFactory;

	//�T�E���h�̃t�@�N�g��.
	std::unique_ptr< clsFACTORY_SOUND_MANAGER > m_upSoundFactory;
	

	//�V�[���������ɕK�v�ȃ|�C���^�̂܂Ƃ�.
	clsPOINTER_GROUP* m_spPtrGroup; 


	//�����Ƃ�delete���Ȃ���null���Ă�.
	HWND m_hWnd;
	ID3D11Device*			m_wpDevice;		//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_wpContext;	//�f�o�C�X�R���e�L�X�g.
	//2DSp�p.
	D3D10_VIEWPORT* m_wpViewPort;
	//�[�x(Z)�e�X�g�ݒ�.
	ID3D11DepthStencilState*	m_wpDepthStencilState;

	//�W���C�X�e�B�b�N.
	clsDxInput*		m_spDxInput;
	clsXInput*		m_spXInput;

	//���\�[�X�N���X.
	clsResource*	m_spResource;
	//�G�t�F�N�g.
	clsEffects*		m_spEffect;
	//�T�E���h.
	clsSOUND_MANAGER_BASE* m_spSound;

	//( �V�[�����܂��� )���{�b�g�̃X�e�[�^�X.
	clsROBO_STATUS*		m_spRoboStatus;

	//�Ö�����낤.
	clsBLACK_SCREEN* m_spBlackScreen;

};


