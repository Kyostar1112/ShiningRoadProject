#pragma once

#include "Global.h"

//���{�̍\���ɕK�v�ȃp�[�c��.
enum class enPARTS : UCHAR
{
	LEG,
	CORE,
	HEAD,
	ARM_L,
	ARM_R,
	WEAPON_L,
	WEAPON_R,

	MAX
};


//========== �p�[�c�̊��N���X ==========//.
class clsPARTS_BASE
{
public:
	clsPARTS_BASE();
	virtual ~clsPARTS_BASE();

private:


};

