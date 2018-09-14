#pragma once

#include "File.h"

#include "SceneBase.h"
#include "CameraAssemble.h"
#include "AssembleModel.h"

#include "AssembleUi.h"

#include "PartsWindowModel.h"
class clsWINDOW_BOX;


//================================//
//========== �g�݊����N���X ==========//
//================================//
class clsSCENE_ASSEMBLE : public clsSCENE_BASE
{
public:

	clsSCENE_ASSEMBLE( clsPOINTER_GROUP* const ptrGroup );
	~clsSCENE_ASSEMBLE();


private:


	//�ǂ̃p�[�c��I��ł��?.
	struct PARTS_SELECT
	{
		short Type;	//�p�[�c�̎��( �r�A�R�A�� ).
		short Num[clsASSEMBLE_MODEL::ENUM_SIZE];	//�p�[�c�ԍ�.

		PARTS_SELECT()
		:Num()
		{
			Type = 0;
		}
	}m_PartsSelect;


	void CreateProduct() final;
	void UpdateProduct( enSCENE &enNextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) final;
	void RenderUi() final;//�u UI�� �vRender.

	//�R���g���[������.
	//�J�[�\���ړ�.
	void MoveCursor();//�J�[�\���ړ��̋��ʓ���.
	void MoveCursorUp();
	void MoveCursorDown();
	void MoveCursorRight();
	void MoveCursorLeft();
	//����.
	void Enter( enSCENE &enNextScene );
	//�L�����Z��.
	void Exit();


	//���b�Z�{�b�N�X�o��.
	void AppearMessageBox( const clsASSEMBLE_UI::enSELECT_MODE encMode );
	//���b�Z�{�b�N�X����.
	void DisAppearMessageBox();
	//�p�[�c�ύX.
	void AssembleParts();
	//�X�e�[�^�X�̕\����\���ؑ�.
	void SwitchDispStatus();
	//�p�[�c�I���ƃX�e�[�^�X�I���̐؂�ւ�.
	void ChangePartsSelect();
	void ChangeStatusSelect();
	//�o��.
	void MissionStart( enSCENE &enNextScene );
	//�^�C�g���ɖ߂�.
	void TitleBack( enSCENE &enNextScene );



	//�͈͓��Ɏ��߂�( �p�[�c�̑I�������I�[�o�[���Ȃ��悤�ɂ��� ).
	//min�͂��̐��l��菬�����Ȃ�Ȃ��Amax�͂���ȏ�ɂ͂Ȃ�Ȃ�.
	// min <= t < max.
	template< class T, class MIN, class MAX >
	T LoopRange( T t, const MIN min, const MAX max ) const;

	//���b�Z�{�b�N�X�����Ă���Ȃ�true.
	bool isMessageBoxClose();


#if _DEBUG
	//�f�o�b�N�J�e�L�X�g�̕\��.
	void RenderDebugText() final;
#endif//#if _DEBUG

	//�p�[�c�I�𒆂�����ȊO��.
	clsASSEMBLE_UI::enSELECT_MODE m_enSelectMode;

	//�p�[�c�E�B���h�E�p.
	D3D11_VIEWPORT* m_pViewPortPartsWindow;
	//���{�E�B���h�E�p.
	D3D11_VIEWPORT* m_pViewPortRoboWindow;

	//�w�i.
	std::unique_ptr< clsSprite2D > m_upBack;

	//�����������郂�f��.
	clsASSEMBLE_MODEL*	m_pAsmModel;

	//�I�𒆃p�[�c.
	clsPARTS_WINDOW_MODEL* m_pSelectParts;

	//���.
	std::unique_ptr< clsSPRITE2D_CENTER > m_upArrow;


	//���b�Z�{�b�N�X.
	std::unique_ptr< clsWINDOW_BOX >	m_upBox;
	//���b�Z�̍s����\��.
	int									m_iMessageNum;

	//���b�Z�{�b�N�X�̑I����.
	std::unique_ptr< clsSPRITE2D_CENTER >	m_upYesNo;
	bool									m_isMessageBoxYes;

	//UI.
	clsASSEMBLE_UI*		m_pUI;

	std::vector< std::shared_ptr< clsFILE > >	m_vspFile;


//	clsSPRITE2D_CENTER* m_pSprite;
//	clsCharaStatic* m_pTestChara;
//	clsCharaStatic* m_pParts;

	//����\�Ȃ�true.
	bool m_isCanControl;
		

	//�G�t�F�N�g.
	::Effekseer::Handle m_ehHibana;


	//���̈���.
	enum enBGM : int
	{
		ASSEMBLE = 0,
	};

	enum enSE : int
	{
		CURSOL_MOVE = 0,
		ENTER,
		EXIT,
		MISSION_START,
		WIN_APP,
		WIN_DISAPP,
	};

};



