#ifndef _DINPUT_H_
#define _DINPUT_H_

#include <dinput.h>	// DirectInput�p.

// DirectX �֌W.
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "dinput8.lib" )	// �R���g���[������Ŏg�p.

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
	float m_fLSDir;

	float GetLSPush();
	float GetHorLSPush();
	float GetVerLSPush();
	float m_fHorLSPush;
	float m_fVerLSPush;

	float GetRSDir();
	float m_fRSDir;

	float GetRSPush();
	float GetHorRSPush();
	float GetVerRSPush();
	float m_fHorRSPush;
	float m_fVerRSPush;

private:
	LPDIRECTINPUT8 m_DI;//DxInput��޼ު��.
	LPDIRECTINPUTDEVICE8 m_Pad;//���޲�(���۰�)��޼ު��.

	unsigned int m_uInputState;//���͏��.

};

#endif //#ifndef _DINPUT_H_

