#pragma once

#include "AssembleModel.h"


//�r�𗼘r�\�������������߂̃N���X.
class clsPARTS_WINDOW_MODEL_FOR_ARMS : public clsASSEMBLE_MODEL
{
public:
	clsPARTS_WINDOW_MODEL_FOR_ARMS();
	~clsPARTS_WINDOW_MODEL_FOR_ARMS();

	void UpdateProduct() final;

	//�p�����ƈႢ�A��܈����̃��f����\������.
	void Render(
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye,
		const enPARTS_TYPES RenderParts = enPARTS_TYPES::ENUM_SIZE/*,
		const D3DXVECTOR4& vColor = { 1.0f, 1.0f, 1.0f, 1.0f },
		const bool isAlpha = false*/ ) final;

private:
	//�`�悷�邩�ۂ���f���o��.
	bool isRender( const enPARTS_TYPES AlphaParts, const UINT uiIndex );

};
