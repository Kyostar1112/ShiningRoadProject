#ifndef XINPUT_H_
#define XINPUT_H_


/*
	//Scene�N���X�ł̎g����.
	if( m_wpXInput->isPressEnter( XINPUT_B ) ){}//�{�^��.
	if( m_wpXInput->isRTriggerEnter() ){}		//�g���K�[���������܂ꂽ�u��.


	//�e�X�e�B�b�N�̓|���.
	if( m_wpXInput->GetLStickTheta() ){}//�X�e�B�b�N�̊p�x(����).
	if( m_wpXInput->GetLStickSlope() ){}//�ǂꂾ���[���|���Ă��邩�F0.0f�`1.0f�ŕԂ�.


	if( m_wpXInput->SetVibPowerL( INPUT_VIBRATION_MAX, 60, 0 ) ){}	//�U��.

*/

#include <Windows.h>
#include <Xinput.h>

#pragma comment( lib, "xinput.lib" )

//�l.
#define INPUT_TRIGGER_MIN	(0)		//�g���K�[.
#define INPUT_TRIGGER_MAX	(255)
#define INPUT_THUMB_MIN		(-32768)//�X�e�B�b�N.
#define INPUT_THUMB_MAX		(32767)
#define INPUT_VIBRATION_MIN	(0)		//�U��.
#define INPUT_VIBRATION_MAX	(65535)

//�X�e�B�b�N�̓|���.
const float fSLOPE_MAX = 1.0f;
const float fSLOPE_MIN = 0.0f;



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

	clsXInput(){
		ZeroMemory( this, sizeof( clsXInput ) );
	}
	~clsXInput(){
	
	}

	//���t���[����.
	bool UpdateStatus();
	bool UpdateKeyStatus();//�g��Ȃ�����?.

	//�{�^������.
	bool isPressEnter( const WORD _padKey ) const;	//�������u��.
	bool isPressStay( const WORD _padKey ) const;	//������Ă��.
	bool isPressExit( const WORD _padKey ) const;	//�������u��.

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
	
	//LR�g���K�[���{�^���̂悤�Ɉ�����.
	bool isLTriggerEnter() const;
	bool isLTriggerStay() const;
	bool isLTriggerExit() const;
	bool isRTriggerEnter() const;
	bool isRTriggerStay() const;
	bool isRTriggerExit() const;



	//���X�e�B�b�N�̊p�x.
	float GetLStickTheta() const;
	//�E�X�e�B�b�N�̊p�x.
	float GetRStickTheta() const;

	//�e�X�e�B�b�N�̓|���( �ǂꂾ���[���|���Ă��邩�F0.0f�`1.0f�ŕԂ� ).
	float GetLStickSlope() const;
	float GetRStickSlope() const;


	//�U����^���悤.//�������F�U���̋���, �������F�U������(���t���[��), ��O�����F������(1�t���[���������).
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


