#pragma once

#include "SoundManagerBase.h"


class clsSOUND_MANAGER_GAME_OVER : public clsSOUND_MANAGER_BASE
{
public:
	clsSOUND_MANAGER_GAME_OVER( const HWND hWnd );
	~clsSOUND_MANAGER_GAME_OVER();

private:

	//�e�p���N���X�̃N���X����m_sSceneName�ɓ����.
	void CreateSceneName() final;

};

