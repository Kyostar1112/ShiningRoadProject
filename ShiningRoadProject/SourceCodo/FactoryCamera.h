#pragma once


#include "Camera.h"
#include "CameraTitle.h"
#include "CameraAssemble.h"
#include "CameraMission.h"
#include "CameraEnding.h"

//�t���O�ɉ����ăV�[�����ƂɃJ������f���o���N���X.
class clsFACTORY_CAMERA
{
public:
//	clsFACTORY_CAMERA();
//	~clsFACTORY_CAMERA();

	//�J������f���o��.
	clsCAMERA_BASE* Create( const enSCENE enScene );


};

