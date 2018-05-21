#pragma once

#include "SceneClass.h"
#include "CameraAssemble.h"




//================================//
//========== �g�݊����N���X ==========//
//================================//
//�X�e�[�W�I�������˂�?���˂Ȃ�?.
class clsASSEMBLE : public clsSCENE_BASE
{
public:
	clsASSEMBLE( clsPOINTER_GROUP* const ptrGroup );
	~clsASSEMBLE();

	void Create() final;
	void Update( enSCENE &nextScene ) final;
	void Render(
		const D3DXMATRIX &mView, const D3DXMATRIX &mProj,
		const D3DXVECTOR3 &vLight ) const final;

private:

	clsSPRITE2D_CENTER* m_pSprite;

	clsCharaStatic* m_pTestChara;
	clsCharaStatic* m_pParts;


};



