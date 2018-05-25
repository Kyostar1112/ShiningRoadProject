#pragma once

#include "PartsBase.h"
#include "FactoryParts.h"

//�A�Z���u���V�[���̃��f������.
class clsASSEMBLE_MODEL
{
public:
	clsASSEMBLE_MODEL();
	~clsASSEMBLE_MODEL();

	//�A�Z���u���V�[���̊e�֐����Ŏg���܂�.
	void Create();
	void UpDate();
	void Render(
		const D3DXMATRIX& const mView, 
		const D3DXMATRIX& const mProj, 
		const D3DXVECTOR3& const vLight, 
		const D3DXVECTOR3& const vEye,
		const D3DXVECTOR4 &vColor = { 1.0f, 1.0f, 1.0f, 1.0f },
		const bool isAlpha = false );

	//���f�����ς�.
	void AttachModel( const enPARTS enParts, clsD3DXSKINMESH* const pModel );


private:

	//���f���̏����Z�b�g.
	void Init();

	clsFACTORY_PARTS*	m_pPartsFactory;
	//�p�[�c�̐����̃|�C���^.
	clsPARTS_BASE**	m_wppParts;
	UCHAR			m_ucPartsMax;//�p�[�c�̍ő吔.

};

