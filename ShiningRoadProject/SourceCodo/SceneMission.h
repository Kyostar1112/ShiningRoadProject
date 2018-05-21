#pragma once

#include "SceneClass.h"
#include "CameraMission.h"


#include"Robo.h"


//================================//
//========== �~�b�V�������N���X ==========//
//================================//
class clsMISSION : public clsSCENE_BASE
{
public:
	//�����̓��\�[�X�Ȃǂ̃|�C���^�̂܂Ƃ�( �����͊��N���X�Ŏ�舵���Ă���̂œ��Ɉӎ����Ȃ��đ��v�ł� ).
	clsMISSION( clsPOINTER_GROUP* const ptrGroup );
	~clsMISSION();

	//�uSceneManager.cpp�v�́uSwitchScene�v�֐����ŃV�[���쐬����Ɏg�p�����.
	void Create() final;

	//���[�v���̏���( �����̃t���O�����֐����ŕύX����ƍ��̃V�[�����j������A.
	//				  �w�肵���V�[������������� ).
	//���̃t���O�̏ڍׂ́uSceneClass.h�v�́uenSCENE�v�����Ă�������.
	void Update( enSCENE &nextScene ) final;

	//�V�[�����̃I�u�W�F�N�g�̕`��֐��̂܂Ƃ�.
	void Render(
		const D3DXMATRIX &mView, 
		const D3DXMATRIX &mProj,
		const D3DXVECTOR3 &vLight ) const final;

private:


	//�e�X�g�p���f��( ����͏����Ă��ǂ��ł��A����Ȃ��ł� ).
	clsRobo* m_pTestRobo;
	clsCharaStatic* m_pTestChara;

	//���N���X�Ɉȉ�������܂�.
	//�J����.
	//���\�[�X.
	//�G�t�F�N�g.
	//�T�E���h.

};

