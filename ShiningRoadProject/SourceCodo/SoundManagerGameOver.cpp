#include "SoundManagerGameOver.h"

using namespace std;

namespace{

	//���̃V�[���̃t�@�C���ɂȂ���t�@�C����.
	const string sDATA_PASS = "GameOver";

}

clsSOUND_MANAGER_GAME_OVER::clsSOUND_MANAGER_GAME_OVER( const HWND hWnd )	: clsSOUND_MANAGER_BASE( hWnd )
{
}

clsSOUND_MANAGER_GAME_OVER::~clsSOUND_MANAGER_GAME_OVER()
{
}


void clsSOUND_MANAGER_GAME_OVER::CreateSceneName()
{
	m_sSceneName = sDATA_PASS;
}