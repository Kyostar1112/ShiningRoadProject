#ifndef XINPUT_H_
#define XINPUT_H_

#include <Windows.h>
#include <Xinput.h>

#pragma comment( lib, "xinput.lib" )

//�l.
#define INPUT_TRIGGER_MIN	(0)
#define INPUT_TRIGGER_MAX	(255)
#define INPUT_THUMB_MIN		(-32768)
#define INPUT_THUMB_MAX		(32767)
#define INPUT_VIBRATION_MIN	(0)
#define INPUT_VIBRATION_MAX	(65535)



//�L�[.
#define XINPUT_UP		( XINPUT_GAMEPAD_DPAD_UP )
#define XINPUT_DOWN		( XINPUT_GAMEPAD_DPAD_DOWN )
#define XINPUT_LEFT		( XINPUT_GAMEPAD_DPAD_LEFT )
#define XINPUT_RIGHT	( XINPUT_GAMEPAD_DPAD_RIGHT )
#define XINPUT_START	( XINPUT_GAMEPAD_START )
#define XINPUT_BACK		( XINPUT_GAMEPAD_BACK )
#define XINPUT_LSTICK	( XINPUT_GAMEPAD_LEFT_THUMB )
#define XINPUT_RSTICK	( XINPUT_GAMEPAD_RIGHT_THUMB )
#define XINPUT_LB		( XINPUT_GAMEPAD_LEFT_SHOULDER )
#define XINPUT_RB		( XINPUT_GAMEPAD_RIGHT_SHOULDER )
#define XINPUT_A		( XINPUT_GAMEPAD_A )
#define XINPUT_B		( XINPUT_GAMEPAD_B )
#define XINPUT_X		( XINPUT_GAMEPAD_X )
#define XINPUT_Y		( XINPUT_GAMEPAD_Y )


class clsXInput
{
public:
	//�X�e�B�b�N�̓|�����ɂ�铮��̕ω�.
	enum class enSTICK_SLOPE : UCHAR
	{
		NOTHING = 0,
		LOW,
		HIGH
	};

	clsXInput(){
		ZeroMemory( this, sizeof( clsXInput ) );
	}
	~clsXInput(){}

	//���t���[����.
	bool UpdateStatus();
	bool UpdateKeyStatus();//�g��Ȃ�����?.

	//�{�^������.
	bool IsPressEnter( const WORD _padKey ) const;
	bool IsPressStay( const WORD _padKey ) const;
	bool IsPressExit( const WORD _padKey ) const;

	//�g���K�[�{�^������.
	BYTE GetLTrigger() const {
		return m_state.Gamepad.bLeftTrigger;
	}
	BYTE GetRTrigger() const {
		return m_state.Gamepad.bRightTrigger;
	}
	SHORT GetLThumbX() const {
		return m_state.Gamepad.sThumbLX;
	}
	SHORT GetLThumbY() const {
		return m_state.Gamepad.sThumbLY;
	}
	SHORT GetRThumbX() const {
		return m_state.Gamepad.sThumbRX;
	}
	SHORT GetRThumbY() const {
		return m_state.Gamepad.sThumbRY;
	}


	//���X�e�B�b�N�̊p�x.
	float GetLStickTheta() const;
	//�E�X�e�B�b�N�̊p�x.
	float GetRStickTheta() const;

	//�e�X�e�B�b�N�̓|���.
	enSTICK_SLOPE GetLStickSlope() const;
	enSTICK_SLOPE GetRStickSlope() const;


	//�U����^���悤.
	void SetVibPowerL( int iVibL, const int iTime, int iVibDecL = 0 );
	void SetVibPowerR( int iVibR, const int iTime, int iVibDecR = 0 );

	//�I������.
	void EndProc(){
		SetVibration( 0, 0 );
//		XInputEnable( false );
	}

private:
	//�U��.
	bool SetVibration( const WORD LMotorSpd, const WORD RMotorSpd );

	//�X�e�B�b�N�̊p�x.
	float GetStickTheta( const SHORT lY, const SHORT lX ) const;
	//�X�e�B�b�N�̌X��.
	float GetStickSlope( const SHORT lY, const SHORT lX ) const;


	DWORD				m_padId;
	XINPUT_STATE		m_state;
	XINPUT_STATE		m_stateOld;//���f�p.
	XINPUT_KEYSTROKE	m_keystroke;
	XINPUT_VIBRATION	m_vibration;

	//�U���⏕.
	void VibSafe( int &iVibPower, int &iVibDec ) const;//�͈͓��Ɏ��߂�.
	void VibDecrease( int &iVibPower, const int iDecPower ) const;//����.
	void VibTimerCnt();//�^�C�}�[�J�E���g.
	int		m_iVibL;//�U����.
	int		m_iVibR;
	int		m_iVibDecL;//���������.
	int		m_iVibDecR;
	int		m_iVibTimerL;//���܂鎞��.
	int		m_iVibTimerR;
	

};

#endif//#ifndef XINPUT_H_


