#include "CameraTitle.h"
#define _USE_MATH_DEFINES
#include <math.h>

struct INIT_DATA
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vRot;
};

//----- �ŏ� -----//.
const INIT_DATA START_INIT_DATA = 
{
	{ 8.963961f, 26.0f, 32.168831f },
	{ 8.963961f, 27.0f, 50.0f },
	{ 0.0f, 0.0f, 0.0f }
};
const float fSTART_MOVE_SPD_INIT = -7.5f;
const float fSTART_MOVE_ACC_INIT = 0.5f + 0.25f + 0.125f + 0.0625f;//0.5 0.25 0.125 0.0625 0.03125
const float fSTART_ROT_Y = -0.29f;

const float fSTART_END_SPD = 0.03125f;

//----- �ŏ� -----//.


//----- ��] -----//.
const D3DXVECTOR3 vSPN_INIT_LOOK = { 0.0f, 30.875f, 0.0f };
const D3DXVECTOR3 vSPN_MOVE_SPD = { 0.0f, 0.0f, 0.0f };
const D3DXVECTOR3 vSPN_MOVE_ACC = { 0.000001f, 0.0f, 0.0005f };//0.0005.
const float fSPN_SPN_SPD_LIMIT = 0.0008f;
//----- ��] -----//.

//----- ��]���Y�[�����ǂ� -----//.
const float fSPN_ZOOM_CHANGE_SPD = 0.1f;//0.1
//----- ��]���Y�[�����ǂ� -----//.


clsCAMERA_TITLE::clsCAMERA_TITLE()
	:m_enMode( enMODE::START )
	,m_fDistance()
	,m_MoveFlg()
{
	Init( enMODE::START );
}

clsCAMERA_TITLE::~clsCAMERA_TITLE()
{
}

void clsCAMERA_TITLE::Create()
{
}

void clsCAMERA_TITLE::Update()
{
	//��_�Ԃ̋���( 2�� ).
	float fX, fZ;
	fX = m_vPos.x - m_vLook.x;
	fZ = m_vPos.z - m_vLook.z;

	//����̊p�x�擾.
//	m_vRot.y = atan2f( -fX, -fZ );
////	m_vRot.y = atan2f( fZ, -fX );

	//��_�Ԃ̋���( �ΐ� ).
	fX *= fX;
	fZ *= fZ;
	m_fDistance = sqrtf( fX + fZ );

	//���[�h�ʓ���.
	switch( m_enMode )
	{
	case enMODE::START:
		Advancing( m_vMoveSpd.z );
		if( abs( m_vMoveSpd.z ) < abs( fSTART_END_SPD )){
			Init( enMODE::IDLE );
		}
		m_vMoveSpd.z *= m_vMoveAcc.z;
		break;
	case enMODE::IDLE:
		Init( enMODE::SPN_L );
		break;
	case enMODE::SPN_L:
		//���邭��.
		CameraSpnFunction();
		if(m_vRot.y >= static_cast<float>( M_PI ) ){
			Init( enMODE::SPN_L_2 );
		}
		break;
	case enMODE::SPN_L_2:
		CameraSpnFunction();
		CameraFakeZoomFunction();
		if( m_vRot.y >= static_cast<float>( M_PI ) * 2.0f ){
			Init( enMODE::SPN_L_3 );
		}
		break;
	case enMODE::SPN_L_3:
		CameraSpnFunction();
		CameraFakeZoomFunction();
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

	if( GetAsyncKeyState( 'H' ) & 0x8000 )	AddPos( { fMove, 0.0F, 0.0F } );
	if( GetAsyncKeyState( 'F' ) & 0x8000 )	AddPos( {-fMove, 0.0F, 0.0F } );
	if( GetAsyncKeyState( 'T' ) & 0x8000 )	AddPos( { 0.0F, fMove, 0.0F } );
	if( GetAsyncKeyState( 'G' ) & 0x8000 )	AddPos( { 0.0F,-fMove, 0.0F } );
	if( GetAsyncKeyState( 'R' ) & 0x8000 )	AddPos( { 0.0F, 0.0F, fMove } );
	if( GetAsyncKeyState( 'Y' ) & 0x8000 )	AddPos( { 0.0F, 0.0F,-fMove } );

	if( GetAsyncKeyState( 'L' ) & 0x8000 )	AddLookPos( { fMove, 0.0F, 0.0F } );
	if( GetAsyncKeyState( 'J' ) & 0x8000 )	AddLookPos( {-fMove, 0.0F, 0.0F } );
	if( GetAsyncKeyState( 'I' ) & 0x8000 )	AddLookPos( { 0.0F, fMove, 0.0F } );
	if( GetAsyncKeyState( 'K' ) & 0x8000 )	AddLookPos( { 0.0F,-fMove, 0.0F } );
	if( GetAsyncKeyState( 'U' ) & 0x8000 )	AddLookPos( { 0.0F, 0.0F, fMove } );
	if( GetAsyncKeyState( 'O' ) & 0x8000 )	AddLookPos( { 0.0F, 0.0F,-fMove } );

	if( GetAsyncKeyState( 'V' ) & 0x8000 )	AddDistance(-fMove, true );
	if( GetAsyncKeyState( 'B' ) & 0x8000 )	AddDistance( fMove, true );
	if( GetAsyncKeyState( 'N' ) & 0x8000 )	AddDistance(-fMove, false );
	if( GetAsyncKeyState( 'M' ) & 0x8000 )	AddDistance( fMove, false );

}

//�e���[�h�̏�����.
void clsCAMERA_TITLE::Init( const enMODE enMode )
{
	INIT_DATA InitData = { m_vPos, m_vLook, m_vRot, };
	float fRotY = 0.0f;
	m_enMode = enMode;

	switch( m_enMode )
	{
	case enMODE::START:
		InitData = START_INIT_DATA;
		fRotY = fSTART_ROT_Y;
		m_vMoveSpd = { 0.0f, 0.0f, fSTART_MOVE_SPD_INIT };
		m_vMoveAcc = { 0.0f, 0.0f, fSTART_MOVE_ACC_INIT };
		break;
	case enMODE::SPN_L:
		InitData.vLook = vSPN_INIT_LOOK;
		m_vMoveSpd = vSPN_MOVE_SPD;
		m_vMoveAcc = vSPN_MOVE_ACC;
		break;
	case enMODE::SPN_L_2:
		m_MoveFlg.z = true;
		break;
	case enMODE::SPN_L_3:
		break;
	}

	SetPos		( InitData.vPos );
	SetLookPos	( InitData.vLook );
	SetRot		( InitData.vRot );

	//Turn�ɕK�v.
	//��_�Ԃ̋���( 2�� ).
	float fX, fZ;
	fX = m_vPos.x - m_vLook.x;
	fZ = m_vPos.z - m_vLook.z;
	fX *= fX;
	fZ *= fZ;
	m_fDistance = sqrtf( fX + fZ );

	Turn( fRotY );
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


//���_�Ƃ̋�����ύX.
void clsCAMERA_TITLE::AddDistance( const float fAdd, const bool isCamMove )
{
	D3DXMATRIX mYaw;
	D3DXMatrixRotationY( &mYaw, m_vRot.y );

	D3DXVECTOR3 vAxisZ( 0.0f, 0.0f, 1.0f );

	//Z���x�N�g�����̂��̂���]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord(
		&vAxisZ,
		&vAxisZ,
		&mYaw );

	if( isCamMove ){
		m_vPos.z  += vAxisZ.z * fAdd;
		m_vPos.x  -= vAxisZ.x * fAdd;
	}
	//�������͖�����.
	else{
		m_vLook.z += vAxisZ.z * -fAdd;
		m_vLook.x -= vAxisZ.x * -fAdd;
	}
}


//���邭��.
void clsCAMERA_TITLE::CameraSpnFunction()
{
	Spn( -m_vMoveSpd.x );
	m_vMoveSpd.x += m_vMoveAcc.x;
	if( m_vMoveSpd.x > fSPN_SPN_SPD_LIMIT ){
		m_vMoveSpd.x = fSPN_SPN_SPD_LIMIT;
	}
	if( m_vRot.y >= static_cast<float>( M_PI ) * 2.0f ){
		m_vRot.y -= static_cast<float>( M_PI ) * 2.0f;
	}
}

//�Y�[��.
void clsCAMERA_TITLE::CameraFakeZoomFunction()
{
	//�Y�[�����ۂ�����.
	if( m_MoveFlg.z ){
		m_vMoveSpd.z += m_vMoveAcc.z;
		if( m_vMoveSpd.z > fSPN_ZOOM_CHANGE_SPD )
			m_MoveFlg.z = false;
	}
	else{
		m_vMoveSpd.z -= m_vMoveAcc.z;
		if( m_vMoveSpd.z < -fSPN_ZOOM_CHANGE_SPD ) 
			m_MoveFlg.z = true;
	}
	AddDistance( m_vMoveSpd.z, true );
}
