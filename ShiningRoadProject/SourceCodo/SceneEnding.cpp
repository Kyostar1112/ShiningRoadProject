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

void clsENDING::Create()
{

}


void clsENDING::Update( enSCENE &nextScene )
{


	DebugChangeScene( nextScene );
}

void clsENDING::Render(
	const D3DXMATRIX &mView, 
	const D3DXMATRIX &mProj,
	const D3DXVECTOR3 &vLight ) const

{
	//Render�֐��̈����������₷�����邽�߂̕ϐ�.
	D3DXVECTOR3 vCamPos = m_wpCamera->GetPos();

}


