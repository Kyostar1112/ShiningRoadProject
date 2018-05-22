#pragma once

#include "SceneClass.h"
#include "CameraTitle.h"



//================================//
//========== �^�C�g���N���X ==========//
//================================//
class clsTITLE : public clsSCENE_BASE
{
public:
	clsTITLE( clsPOINTER_GROUP* const ptrGroup );
	~clsTITLE();





private:

	void CreateProduct() final;
	void UpdateProduct( enSCENE &nextScene ) final;
	void RenderProduct() final;


	//�e�X�g�p���f��( ����͏����Ă��ǂ��ł��A����Ȃ��ł� ).
	clsCharaStatic* m_pTestChara;


};
