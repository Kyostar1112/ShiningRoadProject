#include "PartsWeapon.h"


clsPARTS_WEAPON::clsPARTS_WEAPON()
{
}

clsPARTS_WEAPON::~clsPARTS_WEAPON()
{
}

//�쐬��.
void clsPARTS_WEAPON::CreateProduct()
{
}

//���t���[��.
void clsPARTS_WEAPON::UpdateProduct()
{
}

//�`��.
void clsPARTS_WEAPON::RenderProduct(
	const D3DXMATRIX& const mView, 
	const D3DXMATRIX& const mProj, 
	const D3DXVECTOR3& const vLight, 
	const D3DXVECTOR3& const vEye,
	const D3DXVECTOR4 &vColor,
	const bool isAlpha )
{
}

void clsPARTS_WEAPON::SetAtk( const int iAtk )
{
	m_iAtk = iAtk;
}
int clsPARTS_WEAPON::GetAtk() const
{
	return m_iAtk;
}


void clsPARTS_WEAPON::SetLoadTime( const int iLoad )
{
	m_iLoadTime = iLoad;
}
int clsPARTS_WEAPON::GetLoadTime() const
{
	return m_iLoadTime;
}




