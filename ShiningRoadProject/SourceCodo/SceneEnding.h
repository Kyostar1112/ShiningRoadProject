#pragma once

#include "SceneClass.h"
#include "CameraEnding.h"


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
	void UpdateProduct( enSCENE &nextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) final;


};