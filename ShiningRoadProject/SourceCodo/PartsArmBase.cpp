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
	SetStatusMax( enSTATUS::size );
}

//毎フレーム.
void clsPARTS_ARM_BASE::UpdateProduct()
{
}

