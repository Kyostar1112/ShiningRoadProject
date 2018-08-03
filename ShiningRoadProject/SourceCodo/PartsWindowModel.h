#pragma once


#include "AssembleModel.h"
class clsROBO_STATUS;

class clsPARTS_WINDOW_MODEL
{
public:
	clsPARTS_WINDOW_MODEL( clsResource* const pResource, clsROBO_STATUS* const pStatus );
	~clsPARTS_WINDOW_MODEL();

	void Update( const short Type, const short Num );

	void Render(
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye );

	//�A�Z���u���V�[���̃p�[�c�E�B���h�E�̃J�����̍����̊�ɂ���.
	D3DXVECTOR3 GetSelectPartsHeight();

private:

	//�I�𒆃p�[�c.
	std::unique_ptr< clsASSEMBLE_MODEL > m_upSelectParts;

	enPARTS			m_SelectType;
	SKIN_ENUM_TYPE	m_SelectNum;

	clsResource* m_wpResource;

};

