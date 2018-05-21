#ifndef CHARA_STATIC_H_
#define CHARA_STATIC_H_


#include "GameObject.h"
#include "DX9Mesh.h"


class clsCharaStatic : public clsGameObject
{
public:
	clsCharaStatic();
	virtual ~clsCharaStatic();

	virtual void Init(){};



	//���f���f�[�^�֘A�t���֐�clsDX9Mesh
	virtual void AttachModel( clsDX9Mesh* const pModel );

	//���f���f�[�^�֘A�t�������֐�.
	virtual void DetatchModel();

	//�����_�����O�֐�.
	virtual void Render( 
				const D3DXMATRIX &mView, const D3DXMATRIX &mProj,
				const D3DXVECTOR3 &vLight, const D3DXVECTOR3 &vEye,
				const D3DXVECTOR4 vColor = D3DXVECTOR4( 1.0f,1.0f,1.0f,1.0f ),
				const bool bAlpha = false );

	//�ʒu�X�V�֐�.
	void UpdatePos();
	enDIRECTION		m_enDir;	//����.
	float			m_fSpd;


	clsDX9Mesh*		m_pModel;

//	LPD3DXMESH	m_pMeshForRay;	//���C�ƃ��b�V���p.






protected:




	//���W���]�l���X�V����.
	virtual void UpDateModel();

};


#endif//#ifndef CHARA_STATIC_H_