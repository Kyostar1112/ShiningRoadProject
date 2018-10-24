#ifndef SCENE_TITLE_H_
#define SCENE_TITLE_H_


#include "SceneBase.h"
#include "CameraTitle.h"
#include "Sprite2DCenter.h"

#include "AssembleModel.h"


class clsMENU_WINDOW_TITLE_START_OR_END;

//================================//
//========== �^�C�g���N���X ==========//
//================================//
class clsSCENE_TITLE : public clsSCENE_BASE
{
public:
	clsSCENE_TITLE( clsPOINTER_GROUP* const ptrGroup );
	~clsSCENE_TITLE();


private:

	void CreateProduct() final;
	void UpdateProduct( enSCENE &enNextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) final;
	void RenderUi() final;//�u UI�� �vRender.

	//���j���[�̓���.
	void MenuUpdate( enSCENE &enNextScene );

	//�^�C�g���ŃY���Ƃ������ރ��{�b�g�N.
	clsASSEMBLE_MODEL*	m_pRoboModel;

	//�w�i.
	std::unique_ptr< clsCharaStatic > m_upBack;

	std::unique_ptr< clsSprite2D > m_upLogo;

	std::unique_ptr< clsSprite2D > m_upFlash;



	std::unique_ptr< clsMENU_WINDOW_TITLE_START_OR_END > m_upMenuBox;

	//���j���[����󂯎���������ƍ�����.
	enum enINFORMATION : char
	{
		enINFORMATION_GAME_END = 0,
		enINFORMATION_NEXT_SCENE,
		enINFORMATION_CLOSE_MENU,

		enINFORMATION_size
	};
	unsigned int m_uiInformationDataArray[ enINFORMATION_size ];


	//�e�X�g�p�G�t�F�N�g.
	::Effekseer::Handle m_ehHibana;

	//���̈���.
	enum enBGM : int
	{
		enBGM_MAOU1 = 0,
		enBGM_MAOU3,
	};

	enum enSE : int
	{
		enSE_CURSOL_MOVE = 0,
		enSE_ENTER,
		enSE_EXIT,

		enSE_BOMBER,

		enSE_WIN_APP,
		enSE_WIN_DIS_APP
	};


#if _DEBUG
	//�f�o�b�N�J�e�L�X�g�̕\��.
	void RenderDebugText() final;
#endif//#if _DEBUG

};
#endif//#ifndef SCENE_TITLE_H_