#include "PartsArmBase.h"


clsPARTS_ARM_BASE::clsPARTS_ARM_BASE()
{
}

clsPARTS_ARM_BASE::~clsPARTS_ARM_BASE()
{
}

//作成時.
void clsPARTS_ARM_BASE::CreateProduct()
{
}

//毎フレーム.
void clsPARTS_ARM_BASE::UpdateProduct()
{
}

//描画.
void clsPARTS_ARM_BASE::RenderProduct(
	const D3DXMATRIX& const mView, 
	const D3DXMATRIX& const mProj, 
	const D3DXVECTOR3& const vLight, 
	const D3DXVECTOR3& const vEye,
	const D3DXVECTOR4 &vColor,
	const bool isAlpha )
{
}
