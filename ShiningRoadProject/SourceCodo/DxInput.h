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

	//���X�e�B�b�N.
	float m_fLSDir;
	float m_fHorLSPush;
	float m_fVerLSPush;

	//�E�X�e�B�b�N.
	float m_fRSDir;
	float m_fHorRSPush;
	float m_fVerRSPush;

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
	float GetHorLSEnter();
	float GetHorLSStay();

	float GetVerLSPush();
	float GetVerLSEnter();
	float GetVerLSStay();

	float GetRSDir();
	float GetRSPush();
	float GetHorRSPush();
	float GetVerRSPush();

private:
	unsigned int m_uInputState;//���͏��.

	LPDIRECTINPUT8 m_DI;//DxInput��޼ު��.
	LPDIRECTINPUTDEVICE8 m_Pad;//���޲�(���۰�)��޼ު��.
};

#endif //#ifndef _DINPUT_H_

