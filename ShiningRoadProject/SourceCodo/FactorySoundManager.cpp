#include "FactorySoundManager.h"


clsSOUND_MANAGER_BASE* clsFACTORY_SOUND_MANAGER::Create( const enSCENE enNextScene, HWND const hWnd )
{
	switch( enNextScene )
	{
	case enSCENE::TITLE:
		return new clsSOUND_MANAGER_TITLE( hWnd );
	case enSCENE::ASSEMBLE:
		return new clsSOUND_MANAGER_ASSEMBLE( hWnd );
	case enSCENE::MISSION:
		return new clsSOUND_MANAGER_MISSION( hWnd );
	case enSCENE::ENDING:
		return new clsSOUND_MANAGER_ENDING( hWnd );
	case enSCENE::GAMEOVER:
		return new clsSOUND_MANAGER_GAME_OVER( hWnd );
	default:
		assert( !"�s���ȃV�[�����w�肳��܂���" );
		break;
	}

	return nullptr;
}