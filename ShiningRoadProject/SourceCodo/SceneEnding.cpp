#include "SceneEnding.h"

//================================//
//========== �G���f�B���O�N���X ==========//
//================================//
clsENDING::clsENDING( clsPOINTER_GROUP* const ptrGroup ) : clsSCENE_BASE( ptrGroup )
{
}

clsENDING::~clsENDING()
{
}

void clsENDING::CreateProduct()
{

}


void clsENDING::UpdateProduct( enSCENE &nextScene )
{


	DebugChangeScene( nextScene );
}

void clsENDING::RenderProduct()

{
	//Render�֐��̈����������₷�����邽�߂̕ϐ�.
	D3DXVECTOR3 vCamPos = m_wpCamera->GetPos();

}


