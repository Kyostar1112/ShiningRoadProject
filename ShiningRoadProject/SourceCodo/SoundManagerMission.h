#ifndef SOUND_MANAGER_MISSION_H_
#define SOUND_MANAGER_MISSION_H_

#include "SoundManagerBase.h"


class clsSOUND_MANAGER_MISSION : public clsSOUND_MANAGER_BASE
{
public:
	clsSOUND_MANAGER_MISSION( const HWND hWnd );
	~clsSOUND_MANAGER_MISSION();

private:

	//�e�p���N���X�̃N���X����m_sSceneName�ɓ����.
	void CreateSceneName() final;

};

#endif//#ifndef SOUND_MANAGER_MISSION_H_