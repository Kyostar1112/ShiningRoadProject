#include "CharaStatic.h"



clsCharaStatic::clsCharaStatic() :
	m_pModel( nullptr )
{
}

clsCharaStatic::~clsCharaStatic()
{
	DetatchModel();
}



//�����_�����O�֐�.
void clsCharaStatic::Render(
	const D3DXMATRIX &mView, const D3DXMATRIX &mProj,
	const D3DXVECTOR3 &vLight, const D3DXVECTOR3 &vEye,
	const D3DXVECTOR4 &vColor , const bool bAlpha )
{
	if( m_pModel == nullptr ) return;

	//���W�X�V����.
	UpDateModel();
	
	//���b�V���̃����_�����O�֐����Ă�.
	m_pModel->Render( mView, mProj, vLight, vEye, vColor, bAlpha );
}

//���f���f�[�^�֘A�t���֐�clsDX9Mesh
void clsCharaStatic::AttachModel( clsDX9Mesh* const pModel )
{
	if( pModel != nullptr ){
		m_pModel = pModel;
	}
}

//���f���f�[�^�֘A�t�������֐�.
void clsCharaStatic::DetatchModel()
{
	m_pModel = nullptr;
}




//���W���]�l���X�V����.
void clsCharaStatic::UpDateModel()
{
	if( m_pModel == nullptr ){
		return;
	}

	m_pModel->m_Trans.vPos	= m_vPos;
	m_pModel->m_Trans.fYaw	= m_vRot.y;
	m_pModel->m_Trans.fPitch= m_vRot.x;
	m_pModel->m_Trans.fRoll	= m_vRot.z;
	m_pModel->m_Trans.vScale = m_vScale;
}


//============================================================
//	�ʒu�X�V�֐�.
//============================================================
void clsCharaStatic::UpdatePos()
{
	//�L�����N�^�ړ�����(���W�R��)
	D3DXMATRIX mYaw;
	D3DXMatrixRotationY( &mYaw, m_vRot.y );

	//Z���x�N�g����p��.
	D3DXVECTOR3	vecAxisZ( 0.0f, 0.0f, 1.0f );

	//Z���x�N�g�����̂��̂���]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord(
		&vecAxisZ,	//(out)
		&vecAxisZ,
		&mYaw );	//Y����]�s��.

	//�����ɂ���Đi�s������l��ݒ�.
	switch( m_enDir )
	{
	case enDIRECTION::STOP:
		break;
	case enDIRECTION::FOWARD:	//�O�i.
		//����������*�i�߂�l(0.1f).
		m_vPos -= vecAxisZ * 0.15f * m_fSpd;
		break;
	case enDIRECTION::BACK:	//���.
		m_vPos += vecAxisZ * 0.15f * m_fSpd;
		break;
	}

}



clsDX9Mesh* clsCharaStatic::GetModelPtr()
{
	return m_pModel;
}



