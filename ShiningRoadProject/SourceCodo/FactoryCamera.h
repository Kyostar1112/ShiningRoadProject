#ifndef FACTORY_CAMERA_H_
#define FACTORY_CAMERA_H_



#include "Camera.h"
#include "CameraTitle.h"
#include "CameraAssemble.h"
#include "CameraMission.h"
#include "CameraEnding.h"
#include "CameraGameOver.h"

//フラグに応じてシーンごとにカメラを吐き出すクラス.
class clsFACTORY_CAMERA
{
public:
//	clsFACTORY_CAMERA();
//	~clsFACTORY_CAMERA();

	//カメラを吐き出す.
	clsCAMERA_BASE* Create( const enSCENE enScene );


};

#endif//#ifndef FACTORY_CAMERA_H_