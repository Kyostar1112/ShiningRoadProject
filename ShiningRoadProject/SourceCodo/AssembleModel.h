#pragma once

#include "PartsBase.h"
#include "FactoryParts.h"

#include "Resource.h"
#include "Object.h"
#include"SkinMesh.h"

//�A�Z���u���V�[���̃��f������.
class clsASSEMBLE_MODEL : public clsSkinMesh, public clsObject
{
public:
	clsASSEMBLE_MODEL();
	~clsASSEMBLE_MODEL();


	//�A�Z���u���V�[���̊e�֐����Ŏg���܂�.
	void Create( clsResource* const pResource );
	void UpDate();
	void Render(
		const D3DXMATRIX& const mView, 
		const D3DXMATRIX& const mProj, 
		const D3DXVECTOR3& const vLight, 
		const D3DXVECTOR3& const vEye,
		const D3DXVECTOR4 &vColor = { 1.0f, 1.0f, 1.0f, 1.0f },
		const bool isAlpha = false );

	//���f�����ς�.
	void AttachModel( const enPARTS enParts, const SKIN_ENUM_TYPE PartsNum );

	//�g�����X�t�H�[��.
	void SetPos( const D3DXVECTOR3 &vPos );
	void AddPos( const D3DXVECTOR3 &vVec );

	void SetRot( const D3DXVECTOR3 &vRot );
	void AddRot( const D3DXVECTOR3 &vRot );

	void SetScale( const float fScale );

	void SetAnimSpd( const double &dSpd );

private:

	//���f���̏����Z�b�g.
	void Init();

	//.
	

private:

	clsResource* m_wpResource;

	clsFACTORY_PARTS*	m_pPartsFactory;
	//�p�[�c�̐����̃|�C���^.
	clsPARTS_BASE**	m_wppParts;
	
};

