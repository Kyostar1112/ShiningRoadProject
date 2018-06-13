#pragma once

#include "FactoryParts.h"

#include "Resource.h"

#include "RoboStatus.h"



//�A�Z���u���V�[���̃��f������.
class clsASSEMBLE_MODEL
{
public:
	clsASSEMBLE_MODEL();
	~clsASSEMBLE_MODEL();


	//�A�Z���u���V�[���̊e�֐����Ŏg���܂�.
	void Create( clsResource* const pResource, clsROBO_STATUS* const pStatus );
	void UpDate();
	void Render(
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye,
		const D3DXVECTOR4 &vColor = { 1.0f, 1.0f, 1.0f, 1.0f },
		const bool isAlpha = false );

	//���f���̏����Z�b�g.
	void Init( clsROBO_STATUS* const pStatus );

	//���f�����ς�.
	void AttachModel( const enPARTS enParts, const SKIN_ENUM_TYPE PartsNum );

	//�g�����X�t�H�[��.
	void SetPos( const D3DXVECTOR3 &vPos );
	void AddPos( const D3DXVECTOR3 &vVec );
	D3DXVECTOR3 GetPos() const;

	void SetRot( const D3DXVECTOR3 &vRot );
	void AddRot( const D3DXVECTOR3 &vRot );

	void SetScale( const float fScale );

	void SetAnimSpd( const double &dSpd );

	//�p�[�c�̃A�j���[�V�����ύX.
	bool PartsAnimChange( const enPARTS enParts, const int iIndex );

#if _DEBUG
	//�e�p�[�c��pos.
	D3DXVECTOR3 GetPartsPos( const UCHAR ucParts ) const;
#endif//#if _DEBUG

private:

	//�A�j���[�V�������Z�b�g.
	void AnimReSet();

	//��]�l�}��.
	float GuardDirOver( float &outTheta ) const;

	double m_dAnimSpd;

	TRANSFORM m_Trans;

	clsResource* m_wpResource;

	clsFACTORY_PARTS*	m_pPartsFactory;
	//�p�[�c�̐����̃|�C���^.
	clsPARTS_BASE**	m_wppParts;
	


	//�r�̊p�x�𕐊���͎ʂ���.
	void FitJointModel( 
		clsPARTS_BASE *pMover, clsPARTS_BASE *pBace,
		char *RootBone, char *EndBone );

};

