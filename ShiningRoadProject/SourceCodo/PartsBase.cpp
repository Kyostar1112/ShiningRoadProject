#include "PartsBase.h"



clsPARTS_BASE::clsPARTS_BASE()
{
	
}

clsPARTS_BASE::~clsPARTS_BASE()
{

	
}



//�쐬��.
void clsPARTS_BASE::Create()
{
	CreateProduct();
}
//���t���[��.
void clsPARTS_BASE::Update()
{
	UpdateProduct();
	ModelUpdate( m_Trans );
}
//�`��.
void clsPARTS_BASE::Render(
	const D3DXMATRIX& const mView, 
	const D3DXMATRIX& const mProj, 
	const D3DXVECTOR3& const vLight, 
	const D3DXVECTOR3& const vEye,
	const D3DXVECTOR4 &vColor,
	const bool isAlpha )
{
//	ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
//	SetPosition( GetPosition() );
//	ModelUpdate( m_Trans );

	RenderProduct( mView, mProj, vLight, vEye, vColor, isAlpha );
}
