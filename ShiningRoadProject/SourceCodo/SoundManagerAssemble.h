#ifndef SOUND_MANAGER_ASSEMBLE_H_
#define SOUND_MANAGER_ASSEMBLE_H_

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

#endif//#ifndef SOUND_MANAGER_ASSEMBLE_H_