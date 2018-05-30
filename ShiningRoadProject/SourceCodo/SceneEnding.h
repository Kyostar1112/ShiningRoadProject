#pragma once

#include "SceneClass.h"
#include "CameraEnding.h"


//================================//
//========== エンディングクラス ==========//
//================================//
class clsSCENE_ENDING : public clsSCENE_BASE
{
public:
	clsSCENE_ENDING( clsPOINTER_GROUP* const ptrGroup );
	~clsSCENE_ENDING();


private:
	void CreateProduct() final;
	void UpdateProduct( enSCENE &nextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) const final;

#if _DEBUG
	//デバック゛テキストの表示.
	void RenderDebugText() final;
#endif//#if _DEBUG

};
