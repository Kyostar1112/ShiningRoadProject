#pragma once

#include "Camera.h"


class clsCAMERA_MISSION : public clsCAMERA_BASE
{
public:
	clsCAMERA_MISSION();
	~clsCAMERA_MISSION();

	//�ŏ�( �V�[���̂͂��� )�̏�����.
	void Create() final;

	void Update(const D3DXVECTOR3 vCamPos, const D3DXVECTOR3 vLookPos);

private:

};

