#ifndef SOUND_MANAGER_TITLE_H_
#define SOUND_MANAGER_TITLE_H_

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

#endif//#ifndef SOUND_MANAGER_TITLE_H_