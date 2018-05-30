#pragma once

#include "SceneClass.h"
#include "CameraMission.h"


#include"TestObject.h"


//================================//
//========== �~�b�V�������N���X ==========//
//================================//
class clsSCENE_MISSION : public clsSCENE_BASE
{
public:
	//�����̓��\�[�X�Ȃǂ̃|�C���^�̂܂Ƃ�( �����͊��N���X�Ŏ�舵���Ă���̂œ��Ɉӎ����Ȃ��đ��v�ł� ).
	clsSCENE_MISSION( clsPOINTER_GROUP* const ptrGroup );
	~clsSCENE_MISSION();

//	//�uSceneManager.cpp�v�́uSwitchScene�v�֐����ŃV�[���쐬����Ɏg�p�����.
//	void Create() final;
//
//	//���[�v���̏���( �����̃t���O�����֐����ŕύX����ƍ��̃V�[�����j������A.
//	//				  �w�肵���V�[������������� ).
//	//���̃t���O�̏ڍׂ́uSceneClass.h�v�́uenSCENE�v�����Ă�������.
//	void Update( enSCENE &nextScene ) final;
//
//	//�V�[�����̃I�u�W�F�N�g�̕`��֐��̂܂Ƃ�.
//	void Render() final;

private:

	void CreateProduct() final;
	void UpdateProduct( enSCENE &nextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) final;

#if _DEBUG
	//�f�o�b�N�J�e�L�X�g�̕\��.
	void RenderDebugText() final;
#endif//#if _DEBUG

	//�e�X�g�p���f��( ����͏����Ă��ǂ��ł��A����Ȃ��ł� ).
	clsTestObj* m_pTestRobo;
	clsCharaStatic* m_pTestChara;

	clsDX9Mesh* m_pStage;

	clsCAMERA_MISSION* m_pCam;

	//���N���X�Ɉȉ�������܂�.
	//�J����.
	//���\�[�X.
	//�G�t�F�N�g.
	//�T�E���h.

};

