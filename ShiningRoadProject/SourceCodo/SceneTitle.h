#pragma once

#include "SceneClass.h"
#include "CameraTitle.h"



//================================//
//========== �^�C�g���N���X ==========//
//================================//
class clsTITLE : public clsSCENE_BASE
{
public:
	clsTITLE( clsPOINTER_GROUP* const ptrGroup );
	~clsTITLE();


	void Create() final;
	void Update( enSCENE &nextScene ) final;
	void Render(
		const D3DXMATRIX &mView, 
		const D3DXMATRIX &mProj,
		const D3DXVECTOR3 &vLight ) const final;



private:


	//�e�X�g�p���f��( ����͏����Ă��ǂ��ł��A����Ȃ��ł� ).
	clsCharaStatic* m_pTestChara;


};
