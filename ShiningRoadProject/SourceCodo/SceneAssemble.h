#pragma once

#include "File.h"

#include "SceneBase.h"
#include "CameraAssemble.h"
#include "AssembleModel.h"

#include "AssembleUi.h"



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

	//�p�[�c�I�𒆂�����ȊO��.
	clsASSEMBLE_UI::enSELECT_MODE m_enSelectMode;


	void CreateProduct() final;
	void UpdateProduct( enSCENE &enNextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) final;

	//�R���g���[������.
	//�J�[�\���ړ�.
	void MoveCursor();//�J�[�\���ړ��̋��ʓ���.
	void MoveCursorUp();
	void MoveCursorDown();
	void MoveCursorRight();
	void MoveCursorLeft();
	//����.
	void Enter( enSCENE &enNextScene );
	//�o��.
	void MissionStart( enSCENE &enNextScene );
	//�p�[�c�ύX.
	void AssembleParts();
	//�߂�.
	void Undo( enSCENE &enNextScene );
	PARTS_SELECT m_OldSelect;//Undo()�̂��߂ɕK�v( �̂��ɔz�񉻂��� ).



	//�͈͓��Ɏ��߂�( �p�[�c�̑I�������I�[�o�[���Ȃ��悤�ɂ��� ).
	//min�͂��̐��l��菬�����Ȃ�Ȃ��Amax�͂���ȏ�ɂ͂Ȃ�Ȃ�.
	// min <= t < max.
	template< class T, class MIN, class MAX >
	T KeepRange( T t, const MIN min, const MAX max ) const;	


#if _DEBUG
	//�f�o�b�N�J�e�L�X�g�̕\��.
	void RenderDebugText() final;
#endif//#if _DEBUG

	D3D11_VIEWPORT* m_pViewPortSub;


	//�����������郂�f��.
	clsASSEMBLE_MODEL*	m_pAsmModel;

	//�I�𒆃p�[�c.
	clsSkinMesh* m_pSelectParts;

	//UI.
	clsASSEMBLE_UI*		m_pUI;

	std::vector< std::shared_ptr< clsFILE > >	m_vspFile;
	UCHAR										m_cuFileMax;

//	clsSPRITE2D_CENTER* m_pSprite;
//	clsCharaStatic* m_pTestChara;
//	clsCharaStatic* m_pParts;



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
	};

};



