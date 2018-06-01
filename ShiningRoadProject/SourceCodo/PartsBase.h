#pragma once

#include "Global.h"
#include "SkinMesh.h"

#include "Object.h"

//========== �p�[�c�̊��N���X ==========//.
class clsPARTS_BASE : public clsSkinMesh , public clsObject
{
public:
	clsPARTS_BASE();
	virtual ~clsPARTS_BASE();
	
	//�쐬��.
	void Create();
	//���t���[��.
	void Update();
	//�`��.
	void Render(
		const D3DXMATRIX& const mView, 
		const D3DXMATRIX& const mProj, 
		const D3DXVECTOR3& const vLight, 
		const D3DXVECTOR3& const vEye,
		const D3DXVECTOR4 &vColor,
		const bool isAlpha );

protected:
	//----- �e�V�[�����Ƃ̊֐� -----//.
	virtual void CreateProduct() = 0;//�e�V�[����Create.
	virtual void UpdateProduct() = 0;//�e�V�[����Update.
	virtual void RenderProduct(
		const D3DXMATRIX& const mView, 
		const D3DXMATRIX& const mProj, 
		const D3DXVECTOR3& const vLight, 
		const D3DXVECTOR3& const vEye,
		const D3DXVECTOR4 &vColor,
		const bool isAlpha ) = 0;//�e�V�[����Render.
	//----- �e�V�[�����Ƃ̊֐� -----//.

private:


};

