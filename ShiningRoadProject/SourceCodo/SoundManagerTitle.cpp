#include "SoundManagerTitle.h"

using namespace std;

namespace{

	//���̃V�[���̃t�@�C���ɂȂ���t�@�C����.
	const string sDATA_PASS = "Title";

}

clsSOUND_MANAGER_TITLE::clsSOUND_MANAGER_TITLE( const HWND hWnd )	: clsSOUND_MANAGER_BASE( hWnd )
{
}

clsSOUND_MANAGER_TITLE::~clsSOUND_MANAGER_TITLE()
{
}


void clsSOUND_MANAGER_TITLE::CreateSceneName()
{
	m_sSceneName = sDATA_PASS;
}