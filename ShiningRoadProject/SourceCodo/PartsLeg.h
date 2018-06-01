#pragma once


#include "PartsBase.h"


class clsPARTS_LEG : public clsPARTS_BASE
{
public:
	clsPARTS_LEG();
	~clsPARTS_LEG();

	void SetWalkSpd( const float fSpd );
	float GetWalkSpd() const;

	void SetBoostSpd( const float fSpd );
	float GetBoostSpd() const;

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

	float m_fWalkSpd;
	float m_fBoostSpd;

};

