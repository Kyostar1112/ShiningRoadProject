#pragma once

#include "PartsBase.h"



class clsPARTS_WEAPON : public clsPARTS_BASE
{
public:
	clsPARTS_WEAPON();
	~clsPARTS_WEAPON();

	void SetAtk( const int iAtk );
	int GetAtk() const;

	void SetLoadTime( const int iLoad );
	int GetLoadTime() const;

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

	int m_iAtk;		//�U����.
	int m_iLoadTime;//���U����.

};

