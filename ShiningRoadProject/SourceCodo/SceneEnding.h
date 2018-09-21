#pragma once

#include "SceneBase.h"
#include "CameraEnding.h"

#include "Stage.h"


//================================//
//========== �G���f�B���O�N���X ==========//
//================================//
class clsSCENE_ENDING : public clsSCENE_BASE
{
public:
	clsSCENE_ENDING( clsPOINTER_GROUP* const ptrGroup );
	~clsSCENE_ENDING();


private:
	void CreateProduct() final;
	void UpdateProduct( enSCENE &enNextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) final;
	void RenderUi() final;//�u UI�� �vRender.

	//���̂΂œ��߂���X�v���C�g.
	std::vector< std::unique_ptr< clsSPRITE2D_CENTER > > m_vupSpriteAlpha;
	//�X�N���[������X�v���C�g.
	std::unique_ptr< clsSPRITE2D_CENTER > m_upSpriteScroll;

	unsigned int m_uiSpriteCnt;
	bool m_isSpriteAlphaAppear;
	int m_iIntervalCnt;//�n�܂�܂ł̎��ԃJ�E���g.
	bool m_isScroll;


	std::unique_ptr< clsStage >	m_upStage;//�e�X�g�p.

#if _DEBUG
	//�f�o�b�N�J�e�L�X�g�̕\��.
	void RenderDebugText() final;
#endif//#if _DEBUG

	//���̈���.
	enum enBGM : int
	{
		enBGM_MAFIA0 = 0,
		enBGM_MAFIA1,
		enBGM_MAOU2,
		enBGM_MUS0,
		enBGM_POKET0,
		enBGM_POKET1,
		enBGM_RENGOKU0
	};

	enum enSE : int
	{
		enSE_CURSOL_MOVE = 0,
		enSE_ENTER,
		enSE_EXIT,
	};

};
