#include "SoundManagerBase.h"
#include "File.h"

#include "OperationString.h"

#include <assert.h>

using namespace std;

const unsigned int uiRESERVE_SIZE_BGM = 16;
const unsigned int uiRESERVE_SIZE_SE = 256;
const unsigned int uiRESURVE_SIZE_MAX = 8;	//�����Đ���.


//�Y����.
const char cALIAS_NUM = 0;	//�G�C���A�X��.
const char cPATH_NUM = 1;	//�����f�[�^�̃t�@�C���p�X.
const char cVOLUME_NUM = 2;	//�ő剹��.
const char cMAX_NUM = 3;	//�����Đ��\��.

//�t�@�C���N���X�̃p�X�p.
const string sDATA_PASS = "Data\\Sound\\Data\\";
const string sBGM_PASS = "BGM.csv";
const string sSE_PASS = "SE.csv";
const string sSUB_PASS_BGM = "BGM\\";
const string sSUB_PASS_SE = "SE\\";

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
	,m_vvupBgm()
	,m_vvupSe()
	,m_dqbLoopBgm()
	,m_dqbLoopSe()
	,m_viBgmNum()
	,m_viSeNum()
	,m_uiRESERVE_SIZE_BGM( uiRESERVE_SIZE_BGM )
	,m_uiRESERVE_SIZE_SE( uiRESERVE_SIZE_SE )	
{
}

clsSOUND_MANAGER_BASE::~clsSOUND_MANAGER_BASE()
{
	StopAllSound();

	//�T�E���h�N���X.
	for( unsigned int i=0; i<m_vvupSe.size(); i++ ){
		for( unsigned int j=0; j<m_vvupSe[i].size(); j++ ){
			if( m_vvupSe[i][j] ){
				m_vvupSe[i][j]->Close();
				m_vvupSe[i][j].reset();
				m_vvupSe[i][j] = nullptr;
			}
		}
		m_vvupSe[i].clear();
		m_vvupSe[i].shrink_to_fit();
	}
	m_vvupSe.clear();
	m_vvupSe.shrink_to_fit();

	for( unsigned int i=0; i<m_vvupBgm.size(); i++ ){
		for( unsigned int j=0; j<m_vvupBgm[i].size(); j++ ){
			if( m_vvupBgm[i][j] ){
				m_vvupBgm[i][j]->Close();
				m_vvupBgm[i][j].reset();
				m_vvupBgm[i][j] = nullptr;
			}
		}
		m_vvupBgm[i].clear();
		m_vvupBgm[i].shrink_to_fit();
	}
	m_vvupBgm.clear();
	m_vvupBgm.shrink_to_fit();

	m_dqbLoopBgm.clear();
	m_dqbLoopBgm.shrink_to_fit();
	m_dqbLoopSe.clear();
	m_dqbLoopSe.shrink_to_fit();

	m_viBgmNum.clear();
	m_viBgmNum.shrink_to_fit();
	m_viSeNum.clear();
	m_viSeNum.shrink_to_fit();



	m_hWnd = nullptr;

}





void clsSOUND_MANAGER_BASE::Create()
{
	//�p���N���X�œ����֐�( m_sSceneName������ ).
	CreateSceneName();

	//CSV�f�[�^�̃p�X.
	string tmpDataPass = sDATA_PASS + m_sSceneName;
	string BgmDataPath = tmpDataPass + sBGM_PASS;
	string SeDataPath  = tmpDataPass + sSE_PASS;

	//BGM.
	CreateSound( m_vvupBgm, m_dqbLoopBgm, uiRESERVE_SIZE_BGM, BgmDataPath, sSUB_PASS_BGM, m_viBgmNum );
	//SE.
	CreateSound( m_vvupSe,  m_dqbLoopSe,  uiRESERVE_SIZE_SE,  SeDataPath,  sSUB_PASS_SE,  m_viSeNum );
}

//���t���[�����g��.
void clsSOUND_MANAGER_BASE::UpdateLoop()
{
	//���[�v�Đ�.
	for( unsigned int i=0; i<m_vvupBgm.size(); i++ ){
		//���[�v����K�v����?.
		if( !m_dqbLoopBgm[i] ){
			continue;
		}
		//���݂���?.
		if( !m_vvupBgm[i][0] ){
			continue;
		}
		//�~�܂��Ă���Ȃ�.
		if( IsStoppedBGM( i ) ){
			//������x.
			PlayBGM( i, true );//���[�v���鉹�͎������[�v�ł���悤�ɂ���.
		}		
	}

	for( unsigned int i=0; i<m_vvupSe.size(); i++ ){
		if( !m_dqbLoopSe[i] ){
			continue;
		}
		if( !m_vvupSe[i][0] ){
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
	for( unsigned int i=0; i<m_vvupBgm.size(); i++ ){
		StopBGM( i );
	}

	for( unsigned int i=0; i<m_vvupSe.size(); i++ ){
		StopSE( i );
	}
}


//�T�E���h�N���X�쐬.
void clsSOUND_MANAGER_BASE::CreateSound( 
	SOUND_SET &vpSound,
	std::deque<bool> &dqbLoop,
	const unsigned int uiRESERVE_SIZE,
	const string &sFilePath,
	const string &sSubPath,
	vector<int> &viMaxNum )
{
	//�T�E���h�f�[�^.
	vector< clsSound::SOUND_DATA > vData;
	CreateSoundData( vData, sFilePath, sSubPath, viMaxNum );

	//���̐�.
	int iSoundNum = vData.size();

	//�G�C���A�X���p.
	clsOPERATION_STRING OprtStr;

	//���s�ڂɏ�������?.
	vpSound.resize( iSoundNum );
	for( unsigned int i=0; i<vpSound.size(); i++ )
	{
		vpSound[i].resize( viMaxNum[i] );
		//���܂œ����Đ�������?.
		for( unsigned int j=0; j<vpSound[i].size(); j++ ){
			vpSound[i][j]= make_unique<clsSound>();

			//�G�C���A�X���ɐ������Ȃ���.
			string tmpAlias = OprtStr.ConsolidatedNumber( vData[i].sAlias.c_str(), j );

			//�쐬.
			vpSound[i][j]->Open( vData[i].sPath.c_str(), tmpAlias.c_str(), m_hWnd );
			//�ő剹�ʐݒ�.
			vpSound[i][j]->SetMaxVolume( vData[i].iMaxVolume );
			//�����ʏ�����.
			vpSound[i][j]->SetVolume( vData[i].iMaxVolume );
		}
		vpSound[i].shrink_to_fit();
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
	const string &sFilePath,
	const string &sSubPath,
	std::vector<int> &viMaxNum )
{
	unique_ptr< clsFILE > upFile = make_unique< clsFILE >();
	//�J���Ȃ�������X���[.
	if( upFile->Open( sFilePath ) ){
		//�Ƃ肠��������.
		vData.clear();
		viMaxNum.clear();
		//�t�@�C�����Ƃ����s�������₷.
		vData.resize( upFile->GetSizeRow() );
		viMaxNum.resize( vData.size() );
		//�f�[�^�̒��g������.
		for( unsigned int i=0; i<upFile->GetSizeRow(); i++ ){
			vData[i].sAlias = upFile->GetDataString( i, cALIAS_NUM );
			vData[i].sPath = sSubPath + upFile->GetDataString( i, cPATH_NUM );
			vData[i].iMaxVolume = upFile->GetDataInt( i, cVOLUME_NUM );
			
			viMaxNum[i] = upFile->GetDataInt( i, cMAX_NUM );
		}
	}
	upFile->Close();
	upFile.reset( nullptr );
}




//----- BGM -----//
//�Đ��֐�.
bool clsSOUND_MANAGER_BASE::PlayBGM( const int bgmNo, const bool bNotify )
{
	return Play( m_vvupBgm, m_dqbLoopBgm, m_viBgmNum, bgmNo, bNotify );
}
//��~�֐�.
bool clsSOUND_MANAGER_BASE::StopBGM( const int bgmNo )
{
	return Stop( m_vvupBgm, m_dqbLoopBgm, bgmNo );
}
//���̒�~���m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsStoppedBGM( const int bgmNo ) const
{
	return IsStopped( m_vvupBgm, bgmNo );
}
//���̍Đ������m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsPlayingBGM( const int bgmNo ) const
{
	return IsPlaying( m_vvupBgm, bgmNo );
}
//�����߂��֐�(�Đ��ʒu������).
bool clsSOUND_MANAGER_BASE::SeekToStartBGM( const int bgmNo ) const
{
	return SeekToStart( m_vvupBgm, bgmNo );
}


//----- SE -----//
//�Đ��֐�.
bool clsSOUND_MANAGER_BASE::PlaySE( const int seNo, const bool bNotify )
{
	return Play( m_vvupSe, m_dqbLoopSe, m_viSeNum, seNo, bNotify );
}
//��~�֐�.
bool clsSOUND_MANAGER_BASE::StopSE( const int seNo )
{
	return Stop( m_vvupSe, m_dqbLoopSe, seNo );
}
//���̒�~���m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsStoppedSE( const int seNo ) const
{
	return IsStopped( m_vvupSe, seNo );
}
//���̍Đ������m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsPlayingSE( const int seNo ) const
{
	return IsPlaying( m_vvupSe, seNo );
}
//�����߂��֐�(�Đ��ʒu������).
bool clsSOUND_MANAGER_BASE::SeekToStartSE( const int seNo ) const
{
	return SeekToStart( m_vvupSe, seNo );
}


//----- �e�֐��̒��g -----//.
//�Đ��֐�.
bool clsSOUND_MANAGER_BASE::Play( 
	const SOUND_SET &vpSound, 
	std::deque<bool> &dqbLoop,
	std::vector<int> &viNum,
	const int No, const bool bNotify )
{
	SOUND_NUMBER_OVER_SHECK( No, vpSound );
	dqbLoop[No] = bNotify;
#if 0
	vpSound[No]->SeekToStart();
	return vpSound[No]->Play( bNotify );
#else//#if 0

	//����No�̉��̉��Ԗڂ�炷��?( ������m_viBgmNum�Am_viSeNum�̎g�������ς�� ).
	viNum[No] ++;
	if( static_cast<unsigned int>( viNum[No] ) >= vpSound[No].size() ){
		viNum[No] = 0;
	}

	vpSound[No][ viNum[No] ]->SeekToStart();

	return vpSound[No][ viNum[No] ]->Play( bNotify );
#endif//#if 0
}

//��~�֐�.
bool clsSOUND_MANAGER_BASE::Stop( 
	const SOUND_SET &vpSound, std::deque<bool> &dqbLoop, const int No )
{
	SOUND_NUMBER_OVER_SHECK( No, vpSound );
	dqbLoop[No] = bLOOP_INIT;

#if 0
	vpSound[No]->SeekToStart();

	return vpSound[No]->Stop();
#else//#if 0

	for( unsigned int i=0; i<vpSound[No].size(); i++ ){
		//���Ɏ~�܂��Ă���Ȃ牽�����Ȃ�.
		if( vpSound[No][i]->IsStopped() ){
			continue;
		}
		if( !vpSound[No][i]->Stop() ){
			assert( !"�~�߂�܂���ł���" );
			return false;
		}
	}
	return true;

#endif//#if 0
}

//���̒�~���m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsStopped( const SOUND_SET &vpSound, const int No ) const
{
	SOUND_NUMBER_OVER_SHECK( No, vpSound );
	for( unsigned int i=0; i<vpSound[No].size(); i++ ){
		if( !vpSound[No][i]->IsStopped() ){
			return false;
		}
	}
	return true;
}

//���̍Đ������m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsPlaying( const SOUND_SET &vpSound, const int No ) const
{
	SOUND_NUMBER_OVER_SHECK( No, vpSound );
	for( unsigned int i=0; i<vpSound[No].size(); i++ ){
		if( !vpSound[No][i]->IsPlaying() ){
			return false;
		}
	}
	return true;
}

//�����߂��֐�(�Đ��ʒu������).
bool clsSOUND_MANAGER_BASE::SeekToStart( const SOUND_SET &vpSound, const int No ) const
{
	SOUND_NUMBER_OVER_SHECK( No, vpSound );
	for( unsigned int i=0; i<vpSound[No].size(); i++ ){
		if( !vpSound[No][i]->SeekToStart() ){
			assert( !"�߂��Ȃ�����" );
			return false;
		}
	}
	return true;
}


