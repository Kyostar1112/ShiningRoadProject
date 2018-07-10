#include "PartsBase.h"

using namespace std;

//�{�[����������Ȃ��Ƃ��Ƀ��b�Z�[�W���o���Ȃ����.
//#define ERROR_MESSAGE_MACRO_BONE_NAME_NOT_FIND

clsPARTS_BASE::clsPARTS_BASE()
{	
}

clsPARTS_BASE::~clsPARTS_BASE()
{
}



//�쐬��.
void clsPARTS_BASE::Create()
{
	m_sPartsName = "NoName";
	CreateProduct();
}

//���t���[��.
void clsPARTS_BASE::Update()
{
	UpdateProduct();
	ModelUpdate( m_Trans );
}

//�`��.
void clsPARTS_BASE::Render(
	const D3DXMATRIX& mView, 
	const D3DXMATRIX& mProj, 
	const D3DXVECTOR3& vLight, 
	const D3DXVECTOR3& vEye,
	const D3DXVECTOR4& vColor,
	const bool isAlpha )
{
	ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
}

//�p�[�c�̖��O���o����.
void clsPARTS_BASE::SetPartsName( const string &sPartsName )
{
	m_sPartsName = sPartsName;
}


D3DXVECTOR3 clsPARTS_BASE::GetBonePos( const char* sBoneName, const bool isLocalPos )
{
	D3DXVECTOR3 vBonePos;

	//�{�[���̍��W�����.
	if( !m_pMesh->GetPosFromBone( sBoneName, &vBonePos, isLocalPos ) ){
		//�{�[����������Ȃ����.
		string tmpS = m_sPartsName + "��" +  sBoneName;
#ifdef ERROR_MESSAGE_MACRO_BONE_NAME_NOT_FIND
		ERR_MSG( tmpS.c_str(), "���̃��f���ɂ��̖��O�̃{�[���͑��݂��܂���" );
#endif//#ifdef ERROR_MESSAGE_MACRO_BONE_NAME_NOT_FIND
	}

	return vBonePos;
}


//�A�j���[�V�����ύX.//�ύX�ł���Ȃ�true, �ύX�ł��Ȃ��Ȃ�false���Ԃ�.
bool clsPARTS_BASE::PartsAnimChange( const int iIndex )
{
	return SetAnimChange( iIndex );
}
