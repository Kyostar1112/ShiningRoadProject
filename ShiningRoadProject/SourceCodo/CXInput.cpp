#include "CXInput.h"
#define _USE_MATH_DEFINES
#include <math.h>


//スティックの倒し具合.
const float fSLOPE_MAX = 1.0f;
const float fSLOPE_MIN = 0.0f;

//日吉君のDxInputとのすり合わせ( スティックの角度を[0〜360]->[-180〜180]にする ).
#ifdef HIYOSHI_DX_INPUT
//difference = 差.
const float fDIFF_HIYOSHI_DX_INPUT_DIR = static_cast<float>( M_PI );
#endif//#ifdef HIYOSHI_DX_INPUT


clsXInput::clsXInput()
{
	ZeroMemory( this, sizeof( clsXInput ) );
}
clsXInput::~clsXInput()
{
	EndProc();
}

//終了処理.
void clsXInput::EndProc()
{
	SetVibration( 0, 0 );
	XInputEnable( false );
}




//更新.
bool clsXInput::UpdateStatus(){

	m_stateOld = m_state;//判断用.

	//振動制限時間.
	VibTimerCnt();

	//振動減衰.
	VibDecrease( m_iVibL, m_iVibDecL );
	VibDecrease( m_iVibR, m_iVibDecR );

	//オーバーしない.
	VibSafe( m_iVibL, m_iVibDecL );
	VibSafe( m_iVibR, m_iVibDecR );

	//振動.
	SetVibration( m_iVibL, m_iVibR );

	if( ERROR_SUCCESS == XInputGetState(
		m_padId,
		&m_state ) ) 
	{
		return true;
	}
	return false;
}
////更新( 使わない? ).
//bool clsXInput::UpdateKeyStatus(){
//	if( ERROR_SUCCESS == XInputGetKeystroke(
//		m_padId,
//		0,
//		&m_keystroke ) )
//	{
//		return true;
//	}
//	return false;
//}

bool clsXInput::isPressStay( const WORD _padKey ) const
{
	if( m_state.Gamepad.wButtons & _padKey ){
		return true;
	}
	return false;
}
bool clsXInput::isPressEnter( const WORD _padKey ) const
{
	if( m_state.Gamepad.wButtons & _padKey &&
		!( m_stateOld.Gamepad.wButtons & _padKey ) )
	{
		return true;
	}
	return false;
}
bool clsXInput::isPressExit( const WORD _padKey ) const
{
	if( !( m_state.Gamepad.wButtons & _padKey ) &&
		m_stateOld.Gamepad.wButtons & _padKey )
	{
		return true;
	}
	return false;
}

//LRトリガーをボタンのように扱おう.
bool clsXInput::isLTriggerEnter() const
{
	if( GetLTrigger() >= XINPUT_TRIGGER_MAX &&
		m_stateOld.Gamepad.bLeftTrigger < XINPUT_TRIGGER_MAX )
	{
		return true;
	}
	return false;
}
bool clsXInput::isLTriggerStay() const
{
	if( GetLTrigger() > 0.0f ){
		return true;
	}
	return false;
}
bool clsXInput::isLTriggerExit() const
{
	if( GetLTrigger() < XINPUT_TRIGGER_MAX &&
		m_stateOld.Gamepad.bLeftTrigger >= XINPUT_TRIGGER_MAX )
	{
		return true;
	}
	return false;
}

bool clsXInput::isRTriggerEnter() const
{
	if( GetRTrigger() >= XINPUT_TRIGGER_MAX &&
		m_stateOld.Gamepad.bRightTrigger < XINPUT_TRIGGER_MAX )
	{
		return true;
	}
	return false;
}

bool clsXInput::isRTriggerStay() const
{
	if( GetRTrigger() > 0.0f ){
		return true;
	}
	return false;
}

bool clsXInput::isRTriggerExit() const
{
	if( GetRTrigger() < XINPUT_TRIGGER_MAX &&
		m_stateOld.Gamepad.bRightTrigger >= XINPUT_TRIGGER_MAX )
	{
		return true;
	}
	return false;
}

//トリガー、スティック.
#ifndef NORMALIZE_ANALOG_INPUT
BYTE clsXInput::GetLTrigger() const 
{
	return m_state.Gamepad.bLeftTrigger;
}
BYTE clsXInput::GetRTrigger() const 
{
	return m_state.Gamepad.bRightTrigger;
}
SHORT clsXInput::GetLStickX() const 
{
	return m_state.Gamepad.sThumbLX;
}
SHORT clsXInput::GetLStickY() const 
{
	return m_state.Gamepad.sThumbLY;
}
SHORT clsXInput::GetRStickX() const 
{
	return m_state.Gamepad.sThumbRX;
}
SHORT clsXInput::GetRStickY() const 
{
	return m_state.Gamepad.sThumbRY;
}
#else//##ifndef NORMALIZE_ANALOG_INPUT
float clsXInput::GetLTrigger() const 
{
	return static_cast<float>( m_state.Gamepad.bLeftTrigger ) / static_cast<float>( XINPUT_TRIGGER_MAX );
}
float clsXInput::GetRTrigger() const 
{
	return static_cast<float>( m_state.Gamepad.bRightTrigger ) / static_cast<float>( XINPUT_TRIGGER_MAX );
}
float clsXInput::GetLStickX() const 
{
	return static_cast<float>( m_state.Gamepad.sThumbLX ) / static_cast<float>( XINPUT_THUMB_MAX );
}
float clsXInput::GetLStickY() const 
{
	return static_cast<float>( m_state.Gamepad.sThumbLY ) / static_cast<float>( XINPUT_THUMB_MAX );
}
float clsXInput::GetRStickX() const 
{
	return static_cast<float>( m_state.Gamepad.sThumbRX ) / static_cast<float>( XINPUT_THUMB_MAX );
}
float clsXInput::GetRStickY() const 
{
	return static_cast<float>( m_state.Gamepad.sThumbRY ) / static_cast<float>( XINPUT_THUMB_MAX );
}
#endif//##ifndef NORMALIZE_ANALOG_INPUT





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


//スティックの角度.
float clsXInput::GetStickTheta( const SHORT lY, const SHORT lX ) const
{
	double Theta = 0.0;
	Theta = atan2( (double)lY, (double)lX );

	//微調整.
	Theta += M_PI;

	//オーバーしない.
	if( Theta > M_PI * 2.0 )Theta -= M_PI * 2.0;
	else if( Theta < 0.0 )	Theta += M_PI * 2.0;

	return (float)Theta;
}
//スティックの傾き.
float clsXInput::GetStickSlope( const SHORT lY, const SHORT lX ) const
{
	LONG LX = lX * lX;
	LONG LY = lY * lY;

	float slope = sqrtf( (float)LY + (float)LX );

	return slope;
}


//左スティックの角度.
float clsXInput::GetLStickTheta() const
{
	float fReturn = GetStickTheta( GetLThumbXtoSlope(), GetLThumbYtoSlope() );
#ifdef HIYOSHI_DX_INPUT
	fReturn -= fDIFF_HIYOSHI_DX_INPUT_DIR;
#endif//#ifdef HIYOSHI_DX_INPUT
	return fReturn;
}
//右スティックの角度.
float clsXInput::GetRStickTheta() const
{
	float fReturn = GetStickTheta( GetRThumbXtoSlope(), GetRThumbYtoSlope() );
#ifdef HIYOSHI_DX_INPUT
	fReturn -= fDIFF_HIYOSHI_DX_INPUT_DIR;
#endif//#ifdef HIYOSHI_DX_INPUT
	return fReturn;
}

//各スティックの倒し具合.
float clsXInput::GetLStickSlope() const
{
	//斜めの長さが出る.
	float fSlope = GetStickSlope( GetLThumbYtoSlope(), GetLThumbXtoSlope() ); 

	fSlope = fSlope / XINPUT_THUMB_MAX;

	return fSlope;
}
float clsXInput::GetRStickSlope() const
{
	float fSlope = GetStickSlope( GetRThumbYtoSlope(), GetRThumbXtoSlope() ); 

	fSlope = fSlope / XINPUT_THUMB_MAX;

	return fSlope;
}

//スティック入力( GetStickSlope()とGetStickTheta()の為 ).
SHORT clsXInput::GetLThumbXtoSlope() const 
{
	return m_state.Gamepad.sThumbLX;
}
SHORT clsXInput::GetLThumbYtoSlope() const 
{
	return m_state.Gamepad.sThumbLY;
}
SHORT clsXInput::GetRThumbXtoSlope() const 
{
	return m_state.Gamepad.sThumbRX;
}
SHORT clsXInput::GetRThumbYtoSlope() const 
{
	return m_state.Gamepad.sThumbRY;
}


//範囲内に収める.
void clsXInput::VibSafe( int &iVibPower, int &iVibDec ) const
{
	if( iVibPower > XINPUT_VIBRATION_MAX ){
		iVibPower = XINPUT_VIBRATION_MAX;
	}
	else if( iVibPower < XINPUT_VIBRATION_MIN ){
		iVibPower = XINPUT_VIBRATION_MIN;
		iVibDec = 0;
	}
}

//振動衰弱.
void clsXInput::VibDecrease( int &iVibPower, const int iDecPower ) const
{
	iVibPower -= iDecPower;
}

//振動を与えよう.
void clsXInput::SetVibPowerL( int iVibL, const int iTime, int iVibDecL )
{
	if( iVibDecL < 0 ){ iVibDecL = 0; }
	m_iVibDecL = iVibDecL;//減衰する?.
	m_iVibTimerL = iTime;
	m_iVibL = iVibL;
	VibSafe( m_iVibL, iVibDecL );
	SetVibration( m_iVibL, m_iVibR );
}
void clsXInput::SetVibPowerR( int iVibR, const int iTime, int iVibDecR )
{
	if( iVibDecR < 0 ){ iVibDecR = 0; }
	m_iVibDecR = iVibDecR;//減衰する?.
	m_iVibTimerR = iTime;
	m_iVibR = iVibR;
	VibSafe( m_iVibR, iVibDecR );
	SetVibration( m_iVibL, m_iVibR );
}

//タイマーカウント.
void clsXInput::VibTimerCnt()
{
	//マイナスは減らさない(ずっと震える).
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
