#pragma once


#include "PartsArmBase.h"



class clsPARTS_ARM_L : public clsPARTS_BASE
{
public:
	clsPARTS_ARM_L();
	~clsPARTS_ARM_L();

private:
	//----- �e�V�[�����Ƃ̊֐� -----//.
	void CreateProduct() final;//�e�V�[����Create.
	void UpdateProduct() final;//�e�V�[����Update.
	void RenderProduct(
		const D3DXMATRIX& const mView, 
		const D3DXMATRIX& const mProj, 
		const D3DXVECTOR3& const vLight, 
		const D3DXVECTOR3& const vEye,
		const D3DXVECTOR4 &vColor,
		const bool isAlpha ) final;//�e�V�[����Render.
	//----- �e�V�[�����Ƃ̊֐� -----//.

};

