#include "CXInput.h"
#define _USE_MATH_DEFINES
#include <math.h>


const float fSTICK_SLOPE_HIGH = 30000;
const float fSTICK_SLOPE_LOW = 10000;


//�X�V.
bool clsXInput::UpdateStatus(){

	m_stateOld = m_state;//���f�p.

	//�U����������.
	VibTimerCnt();

	//�U������.
	VibDecrease( m_iVibL, m_iVibDecL );
	VibDecrease( m_iVibR, m_iVibDecR );

	//�I�[�o�[���Ȃ�.
	VibSafe( m_iVibL, m_iVibDecL );
	VibSafe( m_iVibR, m_iVibDecR );

	//�U��.
	SetVibration( m_iVibL, m_iVibR );

	if( ERROR_SUCCESS == XInputGetState(
		m_padId,
		&m_state )) 
	{
		return true;
	}
	return false;
}
//�X�V( �g��Ȃ�? ).
bool clsXInput::UpdateKeyStatus(){
	if( ERROR_SUCCESS == XInputGetKeystroke(
		m_padId,
		0,
		&m_keystroke ) )
	{
		return true;
	}
	return false;
}

bool clsXInput::IsPressStay( const WORD _padKey ) const
{
	if( m_state.Gamepad.wButtons & _padKey ){
		return true;
	}
	return false;
}
bool clsXInput::IsPressEnter( const WORD _padKey ) const
{
	if( m_state.Gamepad.wButtons & _padKey &&
		!( m_stateOld.Gamepad.wButtons & _padKey ) )
	{
		return true;
	}
	return false;
}
bool clsXInput::IsPressExit( const WORD _padKey ) const
{
	if( !( m_state.Gamepad.wButtons & _padKey ) &&
		m_stateOld.Gamepad.wButtons & _padKey )
	{
		return true;
	}
	return false;
}

bool clsXInput::SetVibration( WORD LMotorSpd, WORD RMotorSpd )
{
	m_vibration.wLeftMotorSpeed		= LMotorSpd;
	m_vibration.wRightMotorSpeed	= RMotorSpd;

	if( ERROR_SUCCESS == XInputSetState(
		m_padId, &m_vibration )){
		return true;
	}
	return false;
}


//�X�e�B�b�N�̊p�x.
float clsXInput::GetStickTheta( const SHORT lY, const SHORT lX ) const
{
	double Theta = 0.0;
	Theta = atan2( (double)lY, (double)lX );

	//������.
	Theta += M_PI;

	//�I�[�o�[���Ȃ�.
	if( Theta > M_PI * 2.0 )Theta -= M_PI * 2.0;
	else if( Theta < 0.0 )	Theta += M_PI * 2.0;

	return (float)Theta;
}
//�X�e�B�b�N�̌X��.
float clsXInput::GetStickSlope( const SHORT lY, const SHORT lX ) const
{
	LONG LX = lX * lX;
	LONG LY = lY * lY;

	float slope = (float)sqrt( (double)LY + (double)LX );

	return slope;
}


//���X�e�B�b�N�̊p�x.
float clsXInput::GetLStickTheta() const
{
	return GetStickTheta( GetLThumbX(), GetLThumbY() );
}
//�E�X�e�B�b�N�̊p�x.
float clsXInput::GetRStickTheta() const
{
	return GetStickTheta( GetRThumbX(), GetRThumbY() );
}

//�e�X�e�B�b�N�̓|���.
clsXInput::enSTICK_SLOPE clsXInput::GetLStickSlope() const
{
	float fSlope = GetStickSlope( GetLThumbY(), GetLThumbX() ); 

	if( fSlope > fSTICK_SLOPE_HIGH )	return enSTICK_SLOPE::HIGH;
	else if( fSlope > fSTICK_SLOPE_LOW )return enSTICK_SLOPE::LOW;
	
	return enSTICK_SLOPE::NOTHING;
}
clsXInput::enSTICK_SLOPE clsXInput::GetRStickSlope() const
{
	float fSlope = GetStickSlope( GetRThumbY(), GetRThumbX() ); 

	if( fSlope > fSTICK_SLOPE_HIGH )	return enSTICK_SLOPE::HIGH;
	else if( fSlope > fSTICK_SLOPE_LOW )return enSTICK_SLOPE::LOW;

	return enSTICK_SLOPE::NOTHING;
}


//�͈͓��Ɏ��߂�.
void clsXInput::VibSafe( int &iVibPower, int &iVibDec ) const
{
	if( iVibPower > INPUT_VIBRATION_MAX ){
		iVibPower = INPUT_VIBRATION_MAX;
	}
	else if( iVibPower < INPUT_VIBRATION_MIN ){
		iVibPower = INPUT_VIBRATION_MIN;
		iVibDec = 0;
	}
}

//�U������.
void clsXInput::VibDecrease( int &iVibPower, const int iDecPower ) const
{
	iVibPower -= iDecPower;
}

//�U����^���悤.
void clsXInput::SetVibPowerL( int iVibL, const int iTime, int iVibDecL )
{
	if( iVibDecL < 0 ){ iVibDecL = 0; }
	m_iVibDecL = iVibDecL;//��������?.
	m_iVibTimerL = iTime;
	m_iVibL = iVibL;
	VibSafe( m_iVibL, iVibDecL );
	SetVibration( m_iVibL, m_iVibR );
}
void clsXInput::SetVibPowerR( int iVibR, const int iTime, int iVibDecR )
{
	if( iVibDecR < 0 ){ iVibDecR = 0; }
	m_iVibDecR = iVibDecR;//��������?.
	m_iVibTimerR = iTime;
	m_iVibR = iVibR;
	VibSafe( m_iVibR, iVibDecR );
	SetVibration( m_iVibL, m_iVibR );
}

//�^�C�}�[�J�E���g.
void clsXInput::VibTimerCnt()
{
	//�}�C�i�X�͌��炳�Ȃ�(�����Ɛk����).
	if( m_iVibTimerL >= 0 ){
		if( m_iVibTimerL == 0 ){
			m_iVibL = 0;
		}
		m_iVibTimerL --;
	}

	if( m_iVibTimerR >= 0 ){
		if( m_iVibTimerR == 0 ){
			m_iVibR = 0;
		}
		m_iVibTimerR --;
	}
}
