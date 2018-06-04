#include "DxInput.h"
#include<math.h>

LPDIRECTINPUT8 g_pDI2 = NULL;			// DxInput�I�u�W�F�N�g.
LPDIRECTINPUTDEVICE8 g_pPad2=NULL;	// �f�o�C�X(�R���g���[��)�I�u�W�F�N�g.


// �W���C�X�e�B�b�N�񋓊֐�.
BOOL CALLBACK EnumJoysticksCallBack( const DIDEVICEINSTANCE *pdidInstance, VOID *pContext )
{
	HRESULT hRlt;	// �֐����A�l.

	// �f�o�C�X(�R���g���[��)�̍쐬.
	hRlt = g_pDI2->CreateDevice(
		pdidInstance->guidInstance,	// �f�o�C�X�̔ԍ�.
		&g_pPad2,	// (out)�쐬�����f�o�C�X�I�u�W�F�N�g.
		NULL );
	if( hRlt != DI_OK ){
		return DIENUM_CONTINUE;	// ���̃f�o�C�X��v��.
	}
	return DIENUM_STOP;	// �񋓒�~.
}

// �I�u�W�F�N�g�̗񋓊֐�.
BOOL CALLBACK EnumObjectsCallBack( const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext )
{
	// ��(�X�e�B�b�N)�������Ă��邩�H
	if( pdidoi->dwType & DIDFT_AXIS )
	{
		// ���͏��͈̔͂�ݒ肷��
		DIPROPRANGE diprg;	// �͈͐ݒ�\����

		diprg.diph.dwSize = sizeof( DIPROPRANGE );			// �\���̂̃T�C�Y
		diprg.diph.dwHeaderSize = sizeof( DIPROPHEADER );	// �w�b�_�[���̃T�C�Y
		diprg.diph.dwObj = pdidoi->dwType;					// ��(�I�u�W�F�N�g)
		diprg.diph.dwHow = DIPH_BYID;						// dwObj�ɐݒ肳�����̂�
															// �I�u�W�F�N�g�̎�ނ��H�C���X�^���X�ԍ����H

		diprg.lMax = +g_iAxisMax;	// �ő�l
		diprg.lMin = -g_iAxisMax;	// �ŏ��l

		// �͈͂�ݒ�
		if( FAILED( g_pPad2->SetProperty(
					DIPROP_RANGE,	// �͈�
					&diprg.diph ) ) )// �͈͐ݒ�\����
		{
			return DIENUM_STOP;
		}
	}
	return DIENUM_CONTINUE;
}

//�ݽ�׸�.
clsDxInput::clsDxInput() : m_DI(NULL), m_Pad(NULL)
{
	
}

//�޽�׸�.
clsDxInput::~clsDxInput()
{

}

// DirectInput�̏����ݒ�B
bool clsDxInput::initDI( HWND hWnd)
{
	HRESULT hRlt;	// �֐����A�l
	hRlt = DirectInput8Create(
			GetModuleHandle(NULL),	// DxInput���쐬����A�v���̃n���h��
			DIRECTINPUT_VERSION,	// �Œ�FDxInput�̃o�[�W����
			IID_IDirectInput8,		// �Œ�FUnicode��Ansi�̋�ʗp
			(VOID**)&m_DI,			// (out)DxInput�I�u�W�F�N�g
			NULL);					// NULL�Œ�
	if( hRlt != DI_OK ){
		MessageBox(NULL, "DxInput�̍쐬�Ɏ��s",	"�G���[", MB_OK);
		return false;
	}

	g_pDI2 = m_DI;

	// ���p�\�ȃR���g���[����T��(�񋓂���)
	hRlt = (*m_DI).EnumDevices(
			DI8DEVCLASS_GAMECTRL,	// �S�ẴQ�[���R���g���[��
			EnumJoysticksCallBack,	// �R���g���[���̗񋓊֐�
			NULL,					// �R�[���o�b�N�֐�����̒l
			DIEDFL_ATTACHEDONLY);	// �q�����Ă����ɂ̂�
	if( hRlt != DI_OK ){
		MessageBox(NULL, "���۰ׂ̊m�F�Ɏ��s", "�G���[", MB_OK);
	}

	m_Pad = g_pPad2;

	// �R���g���[���̐ڑ��m�F
	if( g_pPad2 == NULL ){
//		MessageBox( NULL, "���۰ׂ��ڑ�����Ă��܂���", "�G���[", MB_OK );
	}
	else {
		// �R���g���[���\���̂̃f�[�^�t�H�[�}�b�g���쐬
		hRlt = g_pPad2->SetDataFormat(
				&c_dfDIJoystick2);	//�Œ�
		if( hRlt != DI_OK ){
			MessageBox( NULL, "�ް�̫�ϯĂ̍쐬���s", "�G���[", MB_OK );
		}
		// (���̃f�o�C�X�Ƃ�)�������x���̐ݒ�
		hRlt = g_pPad2->SetCooperativeLevel(
				hWnd,
				DISCL_EXCLUSIVE |	// �r���A�N�Z�X
				DISCL_FOREGROUND );	// �t�H�A�O���E���h�A�N�Z�X��
		if( hRlt != DI_OK ){
			MessageBox( NULL, "�������ق̐ݒ莸�s", "�G���[", MB_OK );
		}
		// �g�p�\�ȃI�u�W�F�N�g(�{�^���Ȃ�)�̗�
		hRlt = g_pPad2->EnumObjects(
			EnumObjectsCallBack,	// �I�u�W�F�N�g�񋓊֐�
			(VOID*)hWnd,			// �R�[���o�b�N�֐��ɑ�����
			DIDFT_ALL );			// �S�ẴI�u�W�F�N�g
		if( hRlt != DI_OK ){
			MessageBox( NULL, "��޼ު�Ă̗񋓂Ɏ��s", "�G���[", MB_OK );
		}
	}

	return true;
}

//���͏��X�V�֐�.
HRESULT clsDxInput::UpdataInputState()
{
	HRESULT hRslt;//�֐����A�l.
	DIJOYSTATE2 js;//�ޮ��è�����\����.

	//�ޮ��è���̐ڑ��m�F.
	if (m_Pad == NULL)
	{
		return E_FAIL;
	}

	//�ޮ��è�����ύX����Ă��邩���m�F.
	hRslt = m_Pad->Poll();
	if (hRslt != DI_OK && hRslt != DI_NOEFFECT)//DI_NOEFFCT:�m�F�s�v�����޲�.
	{
		//���۰װ�ւ̱��������擾����.
		hRslt = m_Pad->Acquire();
		while (hRslt == DIERR_INPUTLOST)
		{
			hRslt = m_Pad->Acquire();
		}
		return S_OK;
	}

	//���۰װ���璼���ް����擾����.
	hRslt = m_Pad->GetDeviceState(
		sizeof(DIJOYSTATE2), //�擾���黲��.
		&js);//(out)�擾�ް�.
	if (hRslt != DI_OK)
	{
		return hRslt;
	}

	//���͏��̏�����.
	InitInputState();

	const int iAxisPushMin = g_iAxisMax / 4;

	//����۸޽è��(�è���̌X���(�V��)�̒l��500,-500�Ƃ��čl����)
	if (js.lX > iAxisPushMin)
	{
		AddInputState(enPKey_LRight);
	}

	else if (js.lX < -iAxisPushMin)
	{
		//����.
		AddInputState(enPKey_LLeft);
	}

	if (js.lY < -iAxisPushMin)
	{
		//�㷰.
		AddInputState(enPKey_LUp);
	}

	else if (js.lY > iAxisPushMin)
	{
		//�㷰.
		AddInputState(enPKey_LDown);
	}

	if (abs(js.lX) > iAxisPushMin)
	{
		m_fHorLSPush = (float)js.lX;
		m_fHorLSPush /= g_iAxisMax;
	}

	if (abs(js.lY) > iAxisPushMin)
	{
		m_fVerLSPush = (float)js.lY;
		m_fVerLSPush /= g_iAxisMax;
	}

	if ((abs(js.lX) + abs(js.lY)) / 2 > iAxisPushMin)
	{
		AddInputState(enPKey_L);
		m_fLSDir = atan2f((float)js.lX, (float)-js.lY);
	}

	if (js.lRx > iAxisPushMin)
	{
		AddInputState(enPKey_RRight);
	}

	else if (js.lRx < -iAxisPushMin)
	{
		//����.
		AddInputState(enPKey_RLeft);
	}

	if (js.lRy < -iAxisPushMin)
	{
		//�㷰.
		AddInputState(enPKey_RUp);
	}

	else if (js.lRy > iAxisPushMin)
	{
		//�㷰.
		AddInputState(enPKey_RDown);
	}

	if (abs(js.lRx) > iAxisPushMin)
	{
		m_fHorRSPush = (float)js.lRx;
		m_fHorRSPush /= g_iAxisMax;
	}

	if (abs(js.lRy) > iAxisPushMin)
	{
		m_fVerRSPush = (float)js.lRy;
		m_fVerRSPush /= g_iAxisMax;
	}

	if ((abs(js.lRx) + abs(js.lRy)) / 2 > iAxisPushMin)
	{
		AddInputState(enPKey_R);
		m_fRSDir = atan2f((float)js.lRx, (float)-js.lRy);
	}

	//����.
	for (int i = enPKey_00; i < enPKey_Max; i++)
	{
		if (js.rgbButtons[i - enPKey_00] & 0x80)
		{
			AddInputState((enPKey)i);
		}
	}
	
	if (js.lZ < -500)
	{
		AddInputState(enPKey_ZLeft);
	}

	if (js.lZ > 500)
	{
		AddInputState(enPKey_ZRight);
	}

	

	switch (js.rgdwPOV[0])
	{
	case 4500://�E��.
		AddInputState(enPKey_LUp);
		AddInputState(enPKey_LRight);
		break;
	case 13500://�E��.
		AddInputState(enPKey_LDown);
		AddInputState(enPKey_LRight);
		break;
	case 22500://����.
		AddInputState(enPKey_LDown);
		AddInputState(enPKey_LLeft);
		break;
	case 31500://����.
		AddInputState(enPKey_LUp);
		AddInputState(enPKey_LLeft);
		break;

	case 0://��.
		AddInputState(enPKey_LUp);
		break;
	case 9000://�E.
		AddInputState(enPKey_LRight);
		break;
	case 18000://��.
		AddInputState(enPKey_LDown);
		break;
	case 27000://��.
		AddInputState(enPKey_LLeft);
		break;

	default:
		break;
	}
		
	return S_OK;
}

//���͏���ǉ�����֐�.
void clsDxInput::AddInputState(enPKey enKey)
{
	//<< ��ĉ��Z�q:���ɼ��.
	m_uInputState |= 1 << enKey;

}

//���͏�������������֐�.
void clsDxInput::InitInputState()
{
	m_uInputState = 0;

	m_fHorLSPush = 0.0f;
	m_fVerLSPush = 0.0f;
	m_fLSDir = 0.0f;

	m_fHorRSPush = 0.0f;
	m_fVerRSPush = 0.0f;
	m_fRSDir = 0.0f;
}

//������������֐�.
// ��UpdateInputState():�֐��œ��͏�񂪍X�V����Ă��邱�Ƃ��O��.
bool clsDxInput::IsPressKey(enPKey enKey)
{
	// >> ��ĉ��Z�q:�E�ɼ��.
	if ((m_uInputState >> enKey) & 1)
	{
		return true;
	}

	return false;
}

float clsDxInput::GetLSDir()
{
	return m_fLSDir;
}

float clsDxInput::GetLSPush()
{
	float fLSPush = abs(m_fHorLSPush) + abs(m_fVerLSPush);

	if (fLSPush >= 1.0f)
	{
		fLSPush = 1.0f;
	}
	return fLSPush;
}

float clsDxInput::GetHorLSPush()
{
	return m_fHorLSPush;
}

float clsDxInput::GetVerLSPush()
{
	return m_fVerLSPush;
}

float clsDxInput::GetRSDir()
{
	return m_fRSDir;
}

float clsDxInput::GetRSPush()
{
	float fRSPush = abs(m_fHorRSPush) + abs(m_fVerRSPush);

	if (fRSPush >= 1.0f)
	{
		fRSPush = 1.0f;
	}

	return fRSPush;
}

float clsDxInput::GetHorRSPush()
{
	return m_fHorRSPush;
}

float clsDxInput::GetVerRSPush()
{
	return m_fVerRSPush;
}