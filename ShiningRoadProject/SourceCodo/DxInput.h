#ifndef _DINPUT_H_
#define _DINPUT_H_

#include <dinput.h>	// DirectInput�p.

// DirectX �֌W.
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "dinput8.lib" )	// �R���g���[������Ŏg�p.

//---------------
//�O���[�o���ϐ�
//---------------
const int g_iAxisMax = 1000;
const int g_iAxisMin = g_iAxisMax / 4;

const float g_fPushMax = 1.0f;
const float g_fPushMin = 0.6f;
const float g_fNoPush = 0.0f;

//========================================================
//	�񋓑̐錾.
//========================================================
//�����.
enum enPKey
{
	enPKey_L,

	enPKey_LUp,
	enPKey_LDown,
	enPKey_LLeft,
	enPKey_LRight,

	enPKey_R,

	enPKey_RUp,
	enPKey_RDown,
	enPKey_RLeft,
	enPKey_RRight,

	enPKey_ZLeft,
	enPKey_ZRight,

	enPKey_00,
	enPKey_01,
	enPKey_02,
	enPKey_03,
	enPKey_04,
	enPKey_05,
	enPKey_06,
	enPKey_07,
	enPKey_08,
	enPKey_09,
	enPKey_10,
	enPKey_11,

	enPKey_Max,//���ő吔.
};

//========================================================
//	Ҳݸ׽.
//========================================================

class clsDxInput
{
public:
	clsDxInput();
	~clsDxInput();

	bool initDI(HWND hWnd);

	//���͏��X�V�֐�.
	HRESULT UpdataInputState();

	//���͏���ǉ�����֐�.
	void AddInputState(enPKey enKey);

	//���͏�������������֐�.
	void InitInputState();

	//������������֐�.
	bool IsPressKey(enPKey enKey);

	float GetLSDir();

	float GetLSPush();
	float GetHorLSPush();
	float GetVerLSPush();

	const bool IsLSUpEnter();
	const bool IsLSDownEnter();
	const bool IsLSLeftEnter();
	const bool IsLSRightEnter();

	const bool IsLSUpStay();
	const bool IsLSDownStay();
	const bool IsLSLeftStay();
	const bool IsLSRightStay();

	float GetRSDir();

	float GetRSPush();
	float GetHorRSPush();
	float GetVerRSPush();

	const bool IsRSUpEnter();
	const bool IsRSDownEnter();
	const bool IsRSLeftEnter();
	const bool IsRSRightEnter();
				 
	const bool IsRSUpStay();
	const bool IsRSDownStay();
	const bool IsRSLeftStay();
	const bool IsRSRightStay();

private:
	struct InputState
	{
		//���X�e�B�b�N.
		float fLSDir;
		float fHorLSPush;
		float fVerLSPush;

		//�E�X�e�B�b�N.
		float fRSDir;
		float fHorRSPush;
		float fVerRSPush;

		unsigned int uiKeyState;//���͏��.
	};

	InputState m_InputNowState;//���݂̓��͏��.
	InputState m_InputOldState;//1�t���[���O�̓��͏��.

	LPDIRECTINPUT8 m_DI;//DxInput��޼ު��.
	LPDIRECTINPUTDEVICE8 m_Pad;//���޲�(���۰�)��޼ު��.
};

#endif //#ifndef _DINPUT_H_

