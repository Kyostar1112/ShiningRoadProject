#pragma once

#include "SoundManagerBase.h"


class clsSOUND_MANAGER_ASSEMBLE : public clsSOUND_MANAGER_BASE
{
public:
	clsSOUND_MANAGER_ASSEMBLE( const HWND hWnd );
	~clsSOUND_MANAGER_ASSEMBLE();

private:

	//�e�p���N���X�̃N���X����m_sSceneName�ɓ����.
	void CreateSceneName() final;

};

