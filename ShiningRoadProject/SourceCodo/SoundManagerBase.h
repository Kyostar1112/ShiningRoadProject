#pragma once


#include "Sound.h"

#include <vector>
#include <deque>
#include <memory>



//�T�E���h�N���X�̊��N���X.
class clsSOUND_MANAGER_BASE
{
public:
	clsSOUND_MANAGER_BASE( const HWND hWnd );
	virtual ~clsSOUND_MANAGER_BASE();

	//new����Ɉ�x�����g�p.
	void Create();

	//���t���[�����g��.
	void UpdateLoop();

	//���ׂĒ�~.
	void StopAllSound();

	//----- BGM -----//
	//�Đ��֐�.
	bool PlayBGM( const int bgmNo, const bool bNotify = true );
	//��~�֐�.
	bool StopBGM( const int bgmNo );
	//���̒�~���m�F����֐�.
	bool IsStoppedBGM( const int bgmNo ) const;
	//���̍Đ������m�F����֐�.
	bool IsPlayingBGM( const int bgmNo ) const;
	//�����߂��֐�(�Đ��ʒu������).
	bool SeekToStartBGM( const int bgmNo ) const;


	//----- SE -----//
	//�Đ��֐�.
	bool PlaySE( const int seNo, const bool bNotify = false );
	//��~�֐�.
	bool StopSE( const int seNo );
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

	//�����^�͌����Ȃ̂�.
	using SOUND_SET = std::vector< std::unique_ptr< clsSound > >;

	//�T�E���h�N���X�쐬.
	void CreateSound( 
		SOUND_SET &vpSound,
		std::deque<bool> &dqbLoop,
		const unsigned int uiRESERVE_SIZE,
		const std::string sFilePath );

	//�T�E���h�f�[�^�쐬.
	void CreateSoundData(
		std::vector< clsSound::SOUND_DATA > &vData,
		const std::string sFilePath );

	//�T�E���h�N���X.
	SOUND_SET m_vupBgm;
	SOUND_SET m_vupSe;
	//���[�v�Đ����邩�̃t���O.
	std::deque<bool> m_dqbLoopBgm;
	std::deque<bool> m_dqbLoopSe;

	//���U�[�u�̃T�C�Y.
	const unsigned int m_uiRESERVE_SIZE_BGM;
	const unsigned int m_uiRESERVE_SIZE_SE;

	HWND m_hWnd;

};

