#include "SoundManagerBase.h"

using namespace std;

const unsigned int uiRESERVE_SIZE_BGM = 16;
const unsigned int uiRESERVE_SIZE_SE = 256;

//BGM.
const clsSound::SOUND_DATA BGM_DATA[] =
{
	//�^�C�g��.
	{ "Title", "BGM\\100Title\\100Title.mp3", 350 },
	//�A�Z���u��.
	{ "Assemble", "BGM\\200Main\\010Stage.mp3", 250 },
	//�~�b�V����.
	{ "Mission", "BGM\\300Result\\200ResultJingle.mp3", 350 },
	//�N���A.
	{ "Clear", "BGM\\400Clear\\100EndRoll.mp3", 200 },
	//�Q�[���I�[�o�[.
	{ "GameOver", "BGM\\500Over\\100Bye.mp3", 300 },
};

//SE.
const clsSound::SOUND_DATA SE_DATA[] =
{
	//���邢���.
	{ "Enter", "SE\\700Button\\100Enter.wav", 300 },
	//�Â����.
	{ "Exit", "SE\\700Button\\200Exit.wav", 300 },
};

//push_back�p.
const clsSound::SOUND_DATA INIT_SOUND_DATA = { "", "", 1000 };
const char cALIAS_NUM = 0;
const char cPATH_NUM = 1;
const char cVOLUME_NUM = 2;

//�t�@�C���N���X�̃p�X�p.
const string sDATA_PASS = "Data\\Sound\\Data\\";
const string sBGM_PASS = "BGM.csv";
const string sSE_PASS = "SE.csv";


clsSOUND_MANAGER_BASE::clsSOUND_MANAGER_BASE( const HWND hWnd )
	:m_hWnd( hWnd )
	,m_vupBgm()
	,m_vupSe()
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

	m_hWnd = nullptr;
}

//���ׂĒ�~.
void clsSOUND_MANAGER_BASE::StopAllSound()
{
	for( unsigned int i=0; i<m_vupBgm.size(); i++ ){
		if( m_vupBgm[i] ){
			m_vupBgm[i]->Stop();
		}
	}

	for( unsigned int i=0; i<m_vupSe.size(); i++ ){
		if( m_vupSe[i] ){
			m_vupSe[i]->Stop();
		}
	}
}




void clsSOUND_MANAGER_BASE::Create()
{
	//�p���N���X�œ����֐�( m_sSceneName������ ).
	CreateSceneName();

	string tmpPass = sDATA_PASS + m_sSceneName;

	//BGM.
	CreateSound( m_vupBgm, tmpPass + sBGM_PASS );
	//SE.
	CreateSound( m_vupSe, tmpPass + sSE_PASS );
}



//�T�E���h�N���X�쐬.
void clsSOUND_MANAGER_BASE::CreateSound( 
	vector< unique_ptr< clsSound > > &vpSound,
	const std::string sFilePath )
{
	//�T�E���h�f�[�^.
	std::vector< clsSound::SOUND_DATA > vData;
	CreateSoundData( vData, sFilePath );

	//���̐�.
	int iSoundNum = vData.size();

	//�e�ʂ𑽂߂ɂƂ�.
	vpSound.reserve( uiRESERVE_SIZE_BGM );

	for( int i=0; i<iSoundNum; i++ ){
		//�z��𑝂₵��new( make_unique )����.
		vpSound.push_back( nullptr );
		vpSound[i] = make_unique<clsSound>();

		//���O.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), vData[i].sAlias.c_str() );
		//�쐬.
		vpSound[i]->Open( vData[i].sPath.c_str(), cAliasName, m_hWnd );
		//�ő剹�ʐݒ�.
		vpSound[i]->SetMaxVolume( vData[i].iMaxVolume );
		//�����ʏ�����.
		vpSound[i]->SetVolume( vData[i].iMaxVolume );
	}
	//�]���ȕ�������.
	vpSound.shrink_to_fit();
	vData.clear();
	vData.shrink_to_fit();
}

//�T�E���h�f�[�^�쐬.
void clsSOUND_MANAGER_BASE::CreateSoundData(
	std::vector< clsSound::SOUND_DATA > &vData,
	const std::string sFilePath )
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
bool clsSOUND_MANAGER_BASE::PlayBGM( const int bgmNo, const bool bNotify ) const
{
	return m_vupBgm[bgmNo]->Play( bNotify );
}
//��~�֐�.
bool clsSOUND_MANAGER_BASE::StopBGM( const int bgmNo ) const
{
	return m_vupBgm[bgmNo]->Stop();
}
//���̒�~���m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsStoppedBGM( const int bgmNo ) const
{
	return m_vupBgm[bgmNo]->IsStopped();
}
//���̍Đ������m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsPlayingBGM( const int bgmNo ) const
{
	return m_vupBgm[bgmNo]->IsPlaying();
}
//�����߂��֐�(�Đ��ʒu������).
bool clsSOUND_MANAGER_BASE::SeekToStartBGM( const int bgmNo ) const
{
	return m_vupBgm[bgmNo]->SeekToStart();
}


//----- SE -----//
//�Đ��֐�.
bool clsSOUND_MANAGER_BASE::PlaySE( const int seNo, const bool bNotify ) const
{
	return m_vupSe[seNo]->Play( bNotify );
}
//��~�֐�.
bool clsSOUND_MANAGER_BASE::StopSE( const int seNo ) const
{
	return m_vupSe[seNo]->Stop();
}
//���̒�~���m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsStoppedSE( const int seNo ) const
{
	return m_vupSe[seNo]->Stop();
}
//���̍Đ������m�F����֐�.
bool clsSOUND_MANAGER_BASE::IsPlayingSE( const int seNo ) const
{
	return m_vupSe[seNo]->Stop();
}
//�����߂��֐�(�Đ��ʒu������).
bool clsSOUND_MANAGER_BASE::SeekToStartSE( const int seNo ) const
{
	return m_vupSe[seNo]->Stop();
}




