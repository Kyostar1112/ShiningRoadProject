#pragma once

#include "PartsBase.h"



class clsPARTS_HEAD : public clsPARTS_BASE
{
public:
	clsPARTS_HEAD();
	~clsPARTS_HEAD();

	void SetHp( const int iHp );
	int GetHp() const;
	void AddHp( const int iHp );


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

	int m_iHp;

};

