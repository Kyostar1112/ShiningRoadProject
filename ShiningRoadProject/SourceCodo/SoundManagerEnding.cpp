#include "SoundManagerEnding.h"

using namespace std;

//���̃V�[���̃t�@�C���ɂȂ���t�@�C����.
const string sDATA_PASS = "Ending";


clsSOUND_MANAGER_ENDING::clsSOUND_MANAGER_ENDING( const HWND hWnd )	: clsSOUND_MANAGER_BASE( hWnd )
{
}

clsSOUND_MANAGER_ENDING::~clsSOUND_MANAGER_ENDING()
{
}


void clsSOUND_MANAGER_ENDING::CreateSceneName()
{
	m_sSceneName = sDATA_PASS;
}