#include "PartsLeg.h"



clsPARTS_LEG::clsPARTS_LEG()
{
}

clsPARTS_LEG::~clsPARTS_LEG()
{
}

//�쐬��.
void clsPARTS_LEG::CreateProduct()
{
}

//���t���[��.
void clsPARTS_LEG::UpdateProduct()
{
}

//�`��.
void clsPARTS_LEG::RenderProduct(
	const D3DXMATRIX& const mView, 
	const D3DXMATRIX& const mProj, 
	const D3DXVECTOR3& const vLight, 
	const D3DXVECTOR3& const vEye,
	const D3DXVECTOR4 &vColor,
	const bool isAlpha )
{
}


void clsPARTS_LEG::SetWalkSpd( const float fSpd )
{
	m_fWalkSpd = fSpd;
}
float clsPARTS_LEG::GetWalkSpd() const
{
	return m_fWalkSpd;
}

void clsPARTS_LEG::SetBoostSpd( const float fSpd )
{
	m_fBoostSpd = fSpd;
}
float clsPARTS_LEG::GetBoostSpd() const
{
	return m_fBoostSpd;
}
