#include "GameObject.h"
#include "Main.h"




clsGameObject::clsGameObject()
		: m_vPos( 0.0f, 0.0f, 0.0f )
		, m_vRot( 0.0f, 0.0f, 0.0f )
		, m_vScale( 1.0f, 1.0f, 1.0f )
{
//	m_vPos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
//	m_vRot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
//	m_fScale = 1.0f;
}


clsGameObject::~clsGameObject()
{
}



//============================================================
//�ʒu�ݒ�.
//============================================================
//�ݒ�.
void clsGameObject::SetPosition( const D3DXVECTOR3 &vPos )
{	
	m_vPos = vPos;
}
void clsGameObject::SetPositionX( const float fPosX )
{
	m_vPos.x = fPosX;
}
void clsGameObject::SetPositionY( const float fPosY )
{
	m_vPos.y = fPosY;
}
void clsGameObject::SetPositionZ( const float fPosZ )
{
	m_vPos.z = fPosZ;
}
//�擾.
D3DXVECTOR3 clsGameObject::GetPosition() const
{
	return m_vPos;
}
float clsGameObject::GetPositionX() const
{
	return m_vPos.x;
}
float clsGameObject::GetPositionY() const
{
	return m_vPos.y;
}
float clsGameObject::GetPositionZ() const
{
	return m_vPos.z;
}
//��������.
void clsGameObject::AddPosition( const D3DXVECTOR3 &vMove )
{
	SetPosition( GetPosition() + vMove );
}
void clsGameObject::AddPositionX( const float fMoveX )
{
	SetPositionX( GetPositionX() + fMoveX );
}
void clsGameObject::AddPositionY( const float fMoveY )
{
	SetPositionY( GetPositionY() + fMoveY );
}
void clsGameObject::AddPositionZ( const float fMoveZ )
{
	SetPositionZ( GetPositionZ() + fMoveZ );
}


//============================================================
//��]�ݒ�.
//============================================================
//�ݒ�.
void clsGameObject::SetRotation( const D3DXVECTOR3 &vRot )
{ 
	m_vRot = vRot;
}
void clsGameObject::SetRotationY( const float fRotY )
{
	m_vRot.y = fRotY;
}
void clsGameObject::SetRotationZ( const float fRotZ )
{
	m_vRot.z = fRotZ;
}
//�擾.
D3DXVECTOR3 clsGameObject::GetRotation() const
{
	return m_vRot;
}
float clsGameObject::GetRotationX() const
{
	return m_vRot.x;
}
float clsGameObject::GetRotationY() const
{
	return m_vRot.y;
}
float clsGameObject::GetRotationZ() const
{
	return m_vRot.z;
}
//��������.
void clsGameObject::AddRotation( const D3DXVECTOR3 &vMove )
{
	D3DXVECTOR3 theta = GetRotation() + vMove;
	ThetaOverGuard( theta.x );
	ThetaOverGuard( theta.y );
	ThetaOverGuard( theta.z );
	SetRotation( theta );
}
void clsGameObject::AddRotationY( const float fMoveY )
{
	float theta = GetRotationY() + fMoveY;
	ThetaOverGuard( theta );
	SetRotationY( theta );
}
void clsGameObject::AddRotationZ( const float fMoveZ )
{
	float theta = GetRotationZ() + fMoveZ;
	ThetaOverGuard( theta );
	SetRotationZ( theta );
}

//============================================================
//�g�k�ݒ�.
//============================================================
void clsGameObject::SetScale( const float fScale )
{
	m_vScale.x = fScale;
	m_vScale.y = fScale;
	m_vScale.z = fScale;
}
void clsGameObject::SetScale( const D3DXVECTOR3 &vScale )
{
	m_vScale = vScale;
}
D3DXVECTOR3 clsGameObject::GetScale() const
{
	return m_vScale;
}


//============================================================
//	360�`0�ɔ[�߂�.
//============================================================
void clsGameObject::ThetaOverGuard( float& theta )
{
#define THETA_MAX (float)( M_PI * 2.0 )
	if( theta > THETA_MAX ){
		theta -= THETA_MAX;
	}
	else if( theta < 0.0f ){
		theta += THETA_MAX;
	}
}
void clsGameObject::ThetaOverGuard( double& theta )
{
#define THETA_MAX ( M_PI * 2.0 )
	if( theta > THETA_MAX ){
		theta -= THETA_MAX;
	}
	else if( theta < 0.0 ){
		theta += THETA_MAX;
	}
}


//==================================================
//	�����ŉ��ʂ�ς���.
//==================================================
int clsGameObject::ChangeVolumeDistance( const float fEarPosZ, const float fThisPosZ )
{
	const float VOL_DEAD_RANGE_NEAR = 24.0f;//���������鋗��.
	const float VOL_DEAD_RANGE_BACK = -8.0f;//���������鋗��.
	//�����������Ȃ鋗���i���ɍs���Ă��鎞�̏������Ȃ鑬���j.
	const float VOL_BACK_RATE = VOL_DEAD_RANGE_NEAR / VOL_DEAD_RANGE_BACK;//�}�C�i�X�͂��Ȃ��Ă悢.
	//									�i�����̎��͋����v�Z�̉ߒ��Ń}�C�i�X��������ł����������j.

	const int iVOL_MAX = 1000;

	//�������o��.
	float fRange = fThisPosZ - fEarPosZ;

	//����Ă���Ɖ����o���Ȃ�.
	//��O������(Player��).
	if( fRange > VOL_DEAD_RANGE_NEAR ){
		return 0;
	}
	//��������(Player��).
	else if( fRange < VOL_DEAD_RANGE_BACK ){
		return 0;
	}
	//�ԋ߂��ƍő�.
	else if( fRange == 0.0f ){
		return iVOL_MAX;
	}

	
	//���ʕω�.
	int vol;
	vol = (int)( (float)iVOL_MAX / fRange );//�����.//int�̌v�Z�����VS�����邩��(float)�ɂ��Ă���(int)�ɖ߂�.

	//�����Ȃ珬�����Ȃ�̂𑬂�����.
	if( fRange < 0.0f ){
		vol = (int)( (float)vol / VOL_BACK_RATE );//�����.
	}

	return vol;
}
