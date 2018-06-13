#pragma once


#include "PartsArmBase.h"



class clsPARTS_ARM_L : public clsPARTS_BASE
{
public:
	clsPARTS_ARM_L();
	~clsPARTS_ARM_L();

private:
	//----- 各パーツごとの関数 -----//.
	void CreateProduct() final;//各シーンのCreate.
	void UpdateProduct() final;//各シーンのUpdate.
	//----- 各パーツごとの関数 -----//.

};

