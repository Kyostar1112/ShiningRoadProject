#ifndef FACTORY_SOUND_MANAGER_H_
#define FACTORY_SOUND_MANAGER_H_


#include "Global.h"

#include "SoundManagerBase.h"

#include "SoundManagerTitle.h"
#include "SoundManagerAssemble.h"
#include "SoundManagerMission.h"
#include "SoundManagerEnding.h"
#include "SoundManagerGameOver.h"

class clsFACTORY_SOUND_MANAGER
{
public:

	clsSOUND_MANAGER_BASE* Create( 
		const enSCENE enNextScene,
		HWND const hWnd );

};

#endif//#ifndef FACTORY_SOUND_MANAGER_H_