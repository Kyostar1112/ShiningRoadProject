#pragma once

#include "SoundManagerBase.h"


class clsSOUND_MANAGER_TITLE : public clsSOUND_MANAGER_BASE
{
public:
	clsSOUND_MANAGER_TITLE( const HWND hWnd );
	~clsSOUND_MANAGER_TITLE();

private:

	//�e�p���N���X�̃N���X����m_sSceneName�ɓ����.
	void CreateSceneName() final;

};

