#pragma once

#include "Global.h"
#include"SkinMesh.h"

//���{�̍\���ɕK�v�ȃp�[�c��.
enum class enPARTS : UCHAR
{
	LEG = 0,
	CORE,
	HEAD,
	ARM_L,
	ARM_R,
	WEAPON_L,
	WEAPON_R,

	MAX
};


//========== �p�[�c�̊��N���X ==========//.
class clsPARTS_BASE : public clsSkinMesh
{
public:
	clsPARTS_BASE();
	virtual ~clsPARTS_BASE();
	
protected:

private:


};

