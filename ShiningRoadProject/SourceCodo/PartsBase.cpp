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
	const D3DXMATRIX& mView, 
	const D3DXMATRIX& mProj, 
	const D3DXVECTOR3& vLight, 
	const D3DXVECTOR3& vEye,
	const D3DXVECTOR4 &vColor,
	const bool isAlpha )
{
	ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
}



//�A�j���[�V�����ύX.//�ύX�ł���Ȃ�true, �ύX�ł��Ȃ��Ȃ�false���Ԃ�.
bool clsPARTS_BASE::PartsAnimChange( const int iIndex )
{
	return SetAnimChange( iIndex );
}
