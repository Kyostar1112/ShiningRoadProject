#pragma once

#include "Camera.h"


class clsCAMERA_MISSION : public clsCAMERA_BASE
{
public:
	clsCAMERA_MISSION();
	~clsCAMERA_MISSION();

	//�ŏ�( �V�[���̂͂��� )�̏�����.
	void Create() final;
	

#ifdef Tahara
	void Update() final;
#endif//#ifdef Tahara

private:
};

