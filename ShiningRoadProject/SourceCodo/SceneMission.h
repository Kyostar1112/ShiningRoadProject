#pragma once

#include "SceneBase.h"
#include "CameraMission.h"

#include"Player.h"
#include"Stage.h"

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
//	void Update( enSCENE &enNextScene ) final;
//
//	//�V�[�����̃I�u�W�F�N�g�̕`��֐��̂܂Ƃ�.
//	void Render() final;

private:

	void CreateProduct() final;
	void UpdateProduct( enSCENE &enNextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) final;

#if _DEBUG
	//�f�o�b�N�J�e�L�X�g�̕\��.
	void RenderDebugText() final;
#endif//#if _DEBUG

	clsPlayer* m_pPlayer;

	std::vector<clsCharactor*> m_v_pFriends;
	std::vector<clsCharactor*> m_v_pEnemys;

	void CreateFriends();
	void CreateEnemys();

	void Collison();
	
	//���L������Shot�����L������Body�ɓ����锻������邩�͏����̌��ˍ����œ����.
	void ColFShottoFBody();
	void ColFShottoEBody();

	void ColEShottoFBody();
	void ColEShottoEBody();

	//�e�X�g�p���f��( ����͏����Ă��ǂ��ł��A����Ȃ��ł� ).
	
	//clsCharaStatic* m_pTestChara;

	clsStage* m_pStage;

	float m_fCamMoveSpeed;


	std::vector<clsSPRITE2D_CENTER*> m_v_pRader;
	std::vector<clsSPRITE2D_CENTER*> m_v_pLockOn;
	std::vector<clsUiText*> m_v_pBulletNum;


	//���N���X�Ɉȉ�������܂�.
	//�J����.
	//���\�[�X.
	//�G�t�F�N�g.
	//�T�E���h.

};

