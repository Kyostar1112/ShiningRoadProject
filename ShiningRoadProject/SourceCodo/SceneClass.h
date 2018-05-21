#pragma once

#include "Global.h"

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

	//�V�[���쐬����ɁuSceneManager.cpp�v�́uSwitchScene�v�֐����Ŏg�p����Ă���.
	virtual void Create() = 0;
	//���[�v���̏���( �������֐����ŕύX����ƍ��̃V�[�����j������A.
	//				  �w�肵���V�[������������� ).
	virtual void Update( enSCENE &nextScene ) = 0;
	//�V�[�����̃I�u�W�F�N�g�̕`��֐��̂܂Ƃ�.
	virtual void Render(
		const D3DXMATRIX &mView, 
		const D3DXMATRIX &mProj,
		const D3DXVECTOR3 &vLight ) const = 0;



	//���C���܂ő���グ��.
	D3DXVECTOR3 GetCameraPos() const;
	D3DXVECTOR3 GetCameraLookPos() const;

protected:

	//�f�o�b�O�p�V�[���؂�ւ�.
	//���ׂẴV�[���̈�ԉ��ɒu���Ă���.
	void DebugChangeScene( enSCENE &nextScene ) const;

//���N���X�̃|�C���^�͊��N���X�Ŕj�����܂�.
//�h���N���X�ł͔j�����Ȃ��ł�������.



	//�ȉ��A�����Ƃ�delete���Ȃ���null���Ă�( ���̊��N���X�̃f�X�g���N�^�ł���Ă��܂� ).
	//�J����( �K�v�Ȃ�΂���������āA�V�[�����ƂɈقȂ����@�\�̃J���������܂��傤 ).
	ID3D11Device*			m_wpDevice;		//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_wpContext;//�f�o�C�X�R���e�L�X�g.
	clsPOINTER_GROUP*	m_wpPtrGroup;
	clsDxInput*			m_wpDxInput;
	clsResource*		m_wpResource;
	clsEffects*			m_wpEffects;
	clsSOUND_MANAGER*	m_wpSound;
	clsCAMERA_BASE*		m_wpCamera;


};
