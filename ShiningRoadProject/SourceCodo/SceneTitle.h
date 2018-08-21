#pragma once

#include "SceneBase.h"
#include "CameraTitle.h"
#include "Sprite2DCenter.h"

#include "AssembleModel.h"


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


#if _DEBUG
	//�f�o�b�N�J�e�L�X�g�̕\��.
	void RenderDebugText() final;
#endif//#if _DEBUG

	//�^�C�g���ŃY���Ƃ������ރ��{�b�g�N.
	clsASSEMBLE_MODEL*	m_pRoboModel;

	//�w�i.
	std::unique_ptr< clsCharaStatic > m_upBack;

	std::unique_ptr< clsSPRITE2D_CENTER > m_upLogo;

	//�e�X�g�p�G�t�F�N�g.
	::Effekseer::Handle m_ehHibana;

};
