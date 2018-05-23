#pragma once

#include "SceneClass.h"
#include "CameraTitle.h"



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
	void UpdateProduct( enSCENE &nextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) final;


	//�e�X�g�p���f��( ����͏����Ă��ǂ��ł��A����Ȃ��ł� ).
	clsCharaStatic* m_pTestChara;


};