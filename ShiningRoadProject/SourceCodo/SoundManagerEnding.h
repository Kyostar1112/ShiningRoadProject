#ifndef SOUND_MANAGER_ENDING_H_
#define SOUND_MANAGER_ENDING_H_

#include "SoundManagerBase.h"


class clsSOUND_MANAGER_ENDING : public clsSOUND_MANAGER_BASE
{
public:
	clsSOUND_MANAGER_ENDING( const HWND hWnd );
	~clsSOUND_MANAGER_ENDING();

private:

	//�e�p���N���X�̃N���X����m_sSceneName�ɓ����.
	void CreateSceneName() final;

};

#endif//#ifndef SOUND_MANAGER_ENDING_H_