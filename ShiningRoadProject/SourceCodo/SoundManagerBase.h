#pragma once


#include "Sound.h"

#include <vector>
#include <memory>


//�T�E���h�N���X�̊��N���X.
class clsSOUND_MANAGER_BASE
{
public:
	clsSOUND_MANAGER_BASE( const HWND hWnd );
	virtual ~clsSOUND_MANAGER_BASE();

	//new����Ɉ�x�����g�p.
	void Create();

	//���ׂĒ�~.
	void StopAllSound();

	//----- BGM -----//
	//�Đ��֐�.
	bool PlayBGM( const int bgmNo, const bool bNotify = true ) const;
	//��~�֐�.
	bool StopBGM( const int bgmNo ) const;
	//���̒�~���m�F����֐�.
	bool IsStoppedBGM( const int bgmNo ) const;
	//���̍Đ������m�F����֐�.
	bool IsPlayingBGM( const int bgmNo ) const;
	//�����߂��֐�(�Đ��ʒu������).
	bool SeekToStartBGM( const int bgmNo ) const;


	//----- SE -----//
	//�Đ��֐�.
	bool PlaySE( const int seNo, const bool bNotify = false ) const;
	//��~�֐�.
	bool StopSE( const int seNo ) const;
	//���̒�~���m�F����֐�.
	bool IsStoppedSE( const int seNo ) const;
	//���̍Đ������m�F����֐�.
	bool IsPlayingSE( const int seNo ) const;
	//�����߂��֐�(�Đ��ʒu������).
	bool SeekToStartSE( const int seNo ) const;

protected:

	//�e�p���N���X�̃N���X����m_sSceneName�ɓ����.
	virtual void CreateSceneName() = 0;

	//�p���N���X�Œ��g������.
	std::string m_sSceneName;

private:

	//�T�E���h�f�[�^�쐬.
	void CreateSoundData(
		std::vector< clsSound::SOUND_DATA > &vData,
		const std::string sFilePath );

	//�T�E���h�N���X�쐬.
	void CreateSound( 
		std::vector< std::unique_ptr< clsSound > > &vpSound,
		const std::string sFilePath );

	//�T�E���h�N���X.
	std::vector< std::unique_ptr< clsSound > > m_vupBgm;
	std::vector< std::unique_ptr< clsSound > > m_vupSe;

	//���U�[�u�̃T�C�Y.
	const unsigned int m_uiRESERVE_SIZE_BGM;
	const unsigned int m_uiRESERVE_SIZE_SE;

	HWND m_hWnd;

};

