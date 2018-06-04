#pragma once


#include "Sound.h"


//���w��p�񋓑�.
enum enBGM : UCHAR
{
//	enBGM_START_UP = 0,
	enBGM_TITLE = 0,
	enBGM_ASSEMBLE,
	enBGM_MISSION,
	enBGM_ENDING,
	enBGM_OVER,

	enBGM_MAX,
};
enum enSE : UCHAR
{
	enSE_ENTER = 0,
	enSE_EXIT,

	enSE_MAX,
};


class clsSOUND_MANAGER
{
public:
	clsSOUND_MANAGER( const HWND hWnd );
	~clsSOUND_MANAGER();


	//----- BGM -----//
	//�Đ��֐�.
	bool PlayBGM( const enBGM bgmNo, const bool bNotify = true ) const;
	//��~�֐�.
	bool StopBGM( const enBGM bgmNo ) const;
	//���̒�~���m�F����֐�.
	bool IsStoppedBGM( const enBGM bgmNo ) const;
	//���̍Đ������m�F����֐�.
	bool IsPlayingBGM( const enBGM bgmNo ) const;
	//�����߂��֐�(�Đ��ʒu������).
	bool SeekToStartBGM( const enBGM bgmNo ) const;


	//----- SE -----//
	//�Đ��֐�.
	bool PlaySE( const enSE seNo, const bool bNotify = false ) const;
	//��~�֐�.
	bool StopSE( const enSE seNo ) const;
	//���̒�~���m�F����֐�.
	bool IsStoppedSE( const enSE seNo ) const;
	//���̍Đ������m�F����֐�.
	bool IsPlayingSE( const enSE seNo ) const;
	//�����߂��֐�(�Đ��ʒu������).
	bool SeekToStartSE( const enSE seNo ) const;

private:

	//�T�E���h�N���X�쐬.
	void CreateSound();

	//�T�E���h�N���X.
	clsSound*	m_pBgm[enBGM_MAX];

	clsSound*	m_pSe[enSE_MAX];


	HWND m_hWnd;
};

