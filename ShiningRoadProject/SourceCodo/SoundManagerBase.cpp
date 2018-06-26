#include "SoundManagerBase.h"
#include "File.h"

#include <assert.h>

using namespace std;

const unsigned int uiRESERVE_SIZE_BGM = 16;
const unsigned int uiRESERVE_SIZE_SE = 256;

////BGM.
//const clsSound::SOUND_DATA BGM_DATA[] =
//{
//	//�^�C�g��.
//	{ "Title", "BGM\\100Title\\100Title.mp3", 350 },
//	//�A�Z���u��.
//	{ "Assemble", "BGM\\200Main\\010Stage.mp3", 250 },
//	//�~�b�V����.
//	{ "Mission", "BGM\\300Result\\200ResultJingle.mp3", 350 },
//	//�N���A.
//	{ "Clear", "BGM\\400Clear\\100EndRoll.mp3", 200 },
//	//�Q�[���I�[�o�[.
//	{ "GameOver", "BGM\\500Over\\100Bye.mp3", 300 },
//};
//
////SE.
//const clsSound::SOUND_DATA SE_DATA[] =
//{
//	//���邢���.
//	{ "Enter", "SE\\700Button\\100Enter.wav", 300 },
//	//�Â����.
//	{ "Exit", "SE\\700Button\\200Exit.wav", 300 },
//};

//push_back�p.
const clsSound::SOUND_DATA INIT_SOUND_DATA = { "", "", 1000 };
const char cALIAS_NUM = 0;
const char cPATH_NUM = 1;
const char cVOLUME_NUM = 2;

//�t�@�C���N���X�̃p�X�p.
const string sDATA_PASS = "Data\\Sound\\Data\\";
const string sBGM_PASS = "BGM.csv";
const string sSE_PASS = "SE.csv";

//�T�E���h�N���X�֎w�����o���ۂ�vector�͈̔͂𒴂��Ă�����A���߂ł��Ƃ�������������}�N��.
#define SOUND_NUMBER_OVER_SHECK(no,vp) \
if( (no) >= static_cast<int>( (vp).size() ) ){\
	assert( !"�w�肳�ꂽ�ԍ���BGM�͑��݂��܂���" );\
	return false;\
}
	

//���[�v�t���O�̏�����.
const bool bLOOP_INIT = false;


clsSOUND_MANAGER_BASE::clsSOUND_MANAGER_BASE( const HWND hWnd )
	:m_hWnd( hWnd )
	,m_vupBgm()
	,m_vupSe()
//	,m_dqbLoopBgm()
//	,m_dqbLoopSe()
	,m_uiRESERVE_SIZE_BGM( uiRESERVE_SIZE_BGM )
	,m_uiRESERVE_SIZE_SE( uiRESERVE_SIZE_SE )	
{
}

clsSOUND_MANAGER_BASE::~clsSOUND_MANAGER_BASE()
{
	StopAllSound();

	//�T�E���h�N���X.
	for( unsigned int i=0; i<m_vupSe.size(); i++ ){
		if( m_vupSe[i] ){
			m_vupSe[i]->Close();
			m_vupSe[i].reset();
			m_vupSe[i] = nullptr;
		}
	}
	m_vupSe.clear();
	m_vupSe.shrink_to_fit();

	for( unsigned int i=0; i<m_vupBgm.size(); i++ ){
		if( m_vupBgm[i] ){
			m_vupBgm[i]->Close();
			m_vupBgm[i].reset();
			m_vupBgm[i] = nullptr;
		}
	}
	m_vupBgm.clear();
	m_vupBgm.shrink_to_fit();

	m_dqbLoopBgm.clear();
	m_dqbLoopBgm.shrink_to_fit();
	m_dqbLoopSe.clear();
	m_dqbLoopSe.shrink_to_fit();

	m_hWnd = nullptr;

}





void clsSOUND_MANAGER_BASE::Create()
{
	//�p���N���X�œ����֐�( m_sSceneName������ ).
	CreateSceneName();

	string tmpPass = sDATA_PASS + m_sSceneName;

	//BGM.
	CreateSound( m_vupBgm, m_dqbLoopBgm, uiRESERVE_SIZE_BGM, tmpPass + sBGM_PASS );
	//SE.
	CreateSound( m_vupSe, m_dqbLoopSe, uiRESERVE_SIZE_SE, tmpPass + sSE_PASS );
}

//���t���[�����g��.
void clsSOUND_MANAGER_BASE::UpdateLoop()
{
	//���[�v�Đ�.
	for( unsigned int i=0; i<m_vupBgm.size(); i++ ){
		//���݂���?.
		if( !m_vupBgm[i] ){
			continue;
		}
		//���[�v����K�v����?.
		if( !m_dqbLoopBgm[i] ){
			continue;
		}
		//�~�܂��Ă���Ȃ�.
		if( IsStoppedBGM( i ) ){
			//������x.
			PlayBGM( i, true );//���[�v���鉹�͎������[�v�ł���悤�ɂ���.
		}		
	}

	for( unsigned int i=0; i<m_vupSe.size(); i++ ){
		if( !m_vupSe[i] ){
			continue;
		}
		if( !m_dqbLoopSe[i] ){
			continue;
		}
		if( IsStoppedSE( i ) ){
			PlaySE( i, true );
		}		
	}
}

//���ׂĒ�~.
void clsSOUND_MANAGER_BASE::StopAllSound()
{
	for( unsigned int i=0; i<m_vupBgm.size(); i++ ){
		StopBGM( i );
	}

	for( unsigned int i=0; i<m_vupSe.size(); i++ ){
		StopSE( i );
	}
}


//�T�E���h�N���X�쐬.
void clsSOUND_MANAGER_BASE::CreateSound( 
	SOUND_SET &vpSound,
	std::deque<bool> &dqbLoop,
	const unsigned int uiRESERVE_SIZE,
	const string sFilePath )
{
	//�T�E���h�f�[�^.
	vector< clsSound::SOUND_DATA > vData;
	CreateSoundData( vData, sFilePath );

	//���̐�.
	int iSoundNum = vData.size();

	//�e�ʂ𑽂߂ɂƂ�.
	vpSound.reserve( uiRESERVE_SIZE );


	for( int i=0; i<iSoundNum; i++ ){
		//�z��𑝂₵��new( make_unique )����.
		vpSound.push_back( nullptr );
		vpSound[i] = make_unique<clsSound>();

		//�쐬.
		vpSound[i]->Open( vData[i].sPath.c_str(), vData[i].sAlias.c_str(), m_hWnd );
		//�ő剹�ʐݒ�.
		vpSound[i]->SetMaxVolume( vData[i].iMaxVolume );
		//�����ʏ�����.
		vpSound[i]->SetVolume( vData[i].iMaxVolume );
	}
	//�]���ȕ�������.
	vpSound.shrink_to_fit();
	vData.clear();
	vData.shrink_to_fit();
	//���[�v�t���O�쐬.
	dqbLoop.resize( vpSound.size(), bLOOP_INIT );
	dqbLoop.shrink_to_fit();
}

//�T�E���h�f�[�^�쐬.
void clsSOUND_MANAGER_BASE::CreateSoundData(
	vector< clsSound::SOUND_DATA > &vData,
	const string sFilePath )
{
	unique_ptr< clsFILE > upFile = make_unique< clsFILE >();
	//�J���Ȃ�������X���[.
	if( upFile->Open( sFilePath ) ){
		//�Ƃ肠��������.
		vData.clear();
		//�t�@�C�����Ƃ����s�������₷.
		vData.reserve( upFile->GetSizeRow() );
		for( unsigned int i=0; i<upFile->GetSizeRow(); i++ ){
			vData.push_back( INIT_SOUND_DATA );

			vData[i].sAlias = upFile->GetDataString( i, cALIAS_NUM );
			vData[i].sPath = upFile->GetDataString( i, cPATH_NUM );
			vData[i].iMaxVolume = upFile->GetDataInt( i, cVOLUME_NUM );
		}
		vData.shrink_to_fit();

	}
	upFile->Close();
	upFile.reset( nullptr );
}




//----- BGM -----//
//�Đ��֐�.
bool clsSOUND_MANAGER_BASE::PlayBGM( const int bgmNo, const bool bNotify )
{
	SOUND_NUMBER_OVER_SHECK( bgmNo, m_vupBgm );
	m_vupBgm[bgmNo]->SeekToStart();

	m_dqbLoopBgm[bgmNo] = bNotify;

	return m_vupBgm[bgmNo]->Play( bNotify );
}
//��~�֐�.
bool clsSOUND_MANAGER_BASE::StopBGM( const int bgmNo )
{
	SOUND_NUMBER_OVER_SHECK( bgmNo, m_vupBgm );
	m_vupBgm[bgmNo]->SeekToStart();

	m_dqbLoopBgm[bgmNo] = bLOOP_INIT;

	return m_vupBgm[bgmNo]->Stop();
}
//���̒�~���m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsStoppedBGM( const int bgmNo ) const
{
	SOUND_NUMBER_OVER_SHECK( bgmNo, m_vupBgm );
	return m_vupBgm[bgmNo]->IsStopped();
}
//���̍Đ������m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsPlayingBGM( const int bgmNo ) const
{
	SOUND_NUMBER_OVER_SHECK( bgmNo, m_vupBgm );
	return m_vupBgm[bgmNo]->IsPlaying();
}
//�����߂��֐�(�Đ��ʒu������).
bool clsSOUND_MANAGER_BASE::SeekToStartBGM( const int bgmNo ) const
{
	SOUND_NUMBER_OVER_SHECK( bgmNo, m_vupBgm );
	return m_vupBgm[bgmNo]->SeekToStart();
}


//----- SE -----//
//�Đ��֐�.
bool clsSOUND_MANAGER_BASE::PlaySE( const int seNo, const bool bNotify )
{
	SOUND_NUMBER_OVER_SHECK( seNo, m_vupSe );
	m_vupSe[seNo]->SeekToStart();

	m_dqbLoopSe[seNo] = bNotify;

	return m_vupSe[seNo]->Play( bNotify );
}
//��~�֐�.
bool clsSOUND_MANAGER_BASE::StopSE( const int seNo )
{
	SOUND_NUMBER_OVER_SHECK( seNo, m_vupSe );
	m_vupSe[seNo]->SeekToStart();

	m_dqbLoopSe[seNo] = bLOOP_INIT;

	return m_vupSe[seNo]->Stop();
}
//���̒�~���m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsStoppedSE( const int seNo ) const
{
	SOUND_NUMBER_OVER_SHECK( seNo, m_vupSe );
	return m_vupSe[seNo]->IsStopped();
}
//���̍Đ������m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsPlayingSE( const int seNo ) const
{
	SOUND_NUMBER_OVER_SHECK( seNo, m_vupSe );
	return m_vupSe[seNo]->IsPlaying();
}
//�����߂��֐�(�Đ��ʒu������).
bool clsSOUND_MANAGER_BASE::SeekToStartSE( const int seNo ) const
{
	SOUND_NUMBER_OVER_SHECK( seNo, m_vupSe );
	return m_vupSe[seNo]->SeekToStart();
}




