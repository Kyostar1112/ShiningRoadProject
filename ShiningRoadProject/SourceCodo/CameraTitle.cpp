#include "CameraTitle.h"
#define _USE_MATH_DEFINES
#include <math.h>


clsCAMERA_TITLE::clsCAMERA_TITLE()
	:m_enMode( enMODE::START )
	,m_fDistance()
{
}

clsCAMERA_TITLE::~clsCAMERA_TITLE()
{
}

void clsCAMERA_TITLE::Create()
{
}

void clsCAMERA_TITLE::Update()
{
	//��_�Ԃ̋���( x&z ).
	float fX, fY;
	fX = ( m_vPos.x - m_vLook.x );
	fY = ( m_vPos.z - m_vLook.z );
	fX *= fX;
	fY *= fY;
	m_fDistance = sqrtf( fX + fY );

	//����̊p�x�擾.
	m_vRot.y;

	//���[�h�ʓ���.
	switch( m_enMode )
	{
	case enMODE::START:
		break;
	case enMODE::UP_1:
		break;
	case enMODE::SPN_L:
		break;
	case enMODE::SPN_R:
		break;
	default:
		m_vPos.x += 0.1f;
		break;
	}

	float fRotSpd = 1.0f / 360.0f * M_PI;
	float fMove = 1.0f;

	if( GetAsyncKeyState( 'D' ) & 0x8000 )	Turn(-fRotSpd );
	if( GetAsyncKeyState( 'A' ) & 0x8000 )	Turn( fRotSpd );
	if( GetAsyncKeyState( 'W' ) & 0x8000 )	Advancing( fMove );
	if( GetAsyncKeyState( 'S' ) & 0x8000 )	Advancing(-fMove );
	if( GetAsyncKeyState( 'E' ) & 0x8000 )	Spn(-fRotSpd );
	if( GetAsyncKeyState( 'Q' ) & 0x8000 )	Spn( fRotSpd );

}

//�e���[�h�̏�����.
void clsCAMERA_TITLE::Init()
{

}


//�Ď��Ώۂ𒆐S�ɐ��񂷂�.
void clsCAMERA_TITLE::Spn( const float fSpn )
{
	m_vRot.y -= fSpn;

	m_vPos.x = m_vLook.x + cosf( m_vRot.y - M_PI_2 ) * m_fDistance;
	m_vPos.z = m_vLook.z + sinf( m_vRot.y - M_PI_2 ) * m_fDistance;
}

//�J�����ʒu�𒆐S�ɂ��Č���.
void clsCAMERA_TITLE::Turn( const float fTurn )
{
	m_vRot.y += fTurn;

	m_vLook.x = m_vPos.x + cosf( m_vRot.y + M_PI_2 ) * m_fDistance;
	m_vLook.z = m_vPos.z + sinf( m_vRot.y + M_PI_2 ) * m_fDistance;

}

//�㉺������.
void clsCAMERA_TITLE::UpDown( const float fRot )
{



}


//���̃J���������ɑO�i.advancing
void clsCAMERA_TITLE::Advancing( const float fMove )
{
	D3DXMATRIX mYaw;
	D3DXMatrixRotationY( &mYaw, m_vRot.y );

	D3DXVECTOR3 vAxisZ( 0.0f, 0.0f, 1.0f );

	//Z���x�N�g�����̂��̂���]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord(
		&vAxisZ,
		&vAxisZ,
		&mYaw );


	m_vPos.z  += vAxisZ.z * fMove;
	m_vLook.z += vAxisZ.z * fMove;

	m_vPos.x  -= vAxisZ.x * fMove;
	m_vLook.x -= vAxisZ.x * fMove;

}


