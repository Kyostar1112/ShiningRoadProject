#pragma once

#include "DxInput.h"
#include "Resource.h"
#include "Effects.h"
#include "SoundManager.h"
#include "Camera.h"




class clsPOINTER_GROUP
{
public:
	//�����͐�Ες��Ȃ��̂ŃR���X�g���N�^�ŏ���������.
	clsPOINTER_GROUP( 
		ID3D11Device* const pDevice,
		ID3D11DeviceContext* const pContext,
		D3D10_VIEWPORT* const pViewPort,
		clsDxInput* const pInput,
		clsResource* const pResource,
		clsEffects* const pEffects,
		clsSOUND_MANAGER* const pSound );
	~clsPOINTER_GROUP();

	//�J�����̃A�h���X�擾.
	void UpdateCameraPtr( clsCAMERA_BASE* const pCamera );

	//----- �|�C���^�[��n�� -----//.
	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;
	D3D10_VIEWPORT* GetViewPort() const;
	//�W���C�X�e�B�b�N.
	clsDxInput* GetDxInput() const;
	//���\�[�X.
	clsResource* GetResource() const;
	//�G�t�F�N�g�N���X.
	clsEffects*	GetEffects() const;
	//BGM,SE.
	clsSOUND_MANAGER*	GetSound() const;
	//�J����.
	clsCAMERA_BASE*	GetCamera() const;

private:
	//�f�o�C�X�I�u�W�F�N�g.
	ID3D11Device*			m_wpDevice;
	ID3D11DeviceContext*	m_wpContext;
	//2DSp�p.
	D3D10_VIEWPORT* m_wpViewPort;

	//�W���C�X�e�B�b�N.
	clsDxInput*		m_wpDxInput;
	//���\�[�X.
	clsResource* m_wpResource;
	//�G�t�F�N�g�N���X.
	clsEffects*	m_wpEffects;
	//BGM,SE.
	clsSOUND_MANAGER*	m_wpSound;

	//�J����( ���������V�[���؂�ւ����Ƃɕς�� ).
	clsCAMERA_BASE*		m_wpCamera;

};

