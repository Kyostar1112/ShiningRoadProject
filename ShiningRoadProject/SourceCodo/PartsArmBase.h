#pragma once


#include "PartsBase.h"



class clsPARTS_ARM_BASE : public clsPARTS_BASE
{
public:
	clsPARTS_ARM_BASE();
	virtual ~clsPARTS_ARM_BASE();

private:
	//----- �e�V�[�����Ƃ̊֐� -----//.
	virtual void CreateProduct() override;//�e�V�[����Create.
	virtual void UpdateProduct() override;//�e�V�[����Update.
	virtual void RenderProduct(
		const D3DXMATRIX& const mView, 
		const D3DXMATRIX& const mProj, 
		const D3DXVECTOR3& const vLight, 
		const D3DXVECTOR3& const vEye,
		const D3DXVECTOR4 &vColor,
		const bool isAlpha ) override;//�e�V�[����Render.
	//----- �e�V�[�����Ƃ̊֐� -----//.

};

