#ifndef _SHOT_H_
#define _SHOT_H_

#include"Effects.h"
#include"Sound.h"
#include"Object.h"
#include "PtrGroup.h"

class clsShot : public clsObject
{
public:
	clsShot();
	~clsShot();

	D3DXVECTOR3 m_vStartPos;
	D3DXVECTOR3 vMoveAxis;

	int m_iThisShotIndex;
	clsSound** m_ppSE;
	int m_iSoundMaxNo;

	D3DXVECTOR3 m_vMoveAxis;

	bool m_bShotExistFlg;//�e�̑��݊m�F(false�Ȃ�e�����݂��Ȃ����).
	bool m_bExistFlg;//�e,����,�O�Ղ̑��݊m�F(false�Ȃ炻���S�Ă����݂��Ȃ����)

	HRESULT Init(const float );

	clsEffects* m_pEffect;

	::Effekseer::Handle m_ShotEfcH;
	::Effekseer::Handle m_LineEfcH;
	::Effekseer::Handle m_HitEfcH;

	SPHERE m_Sphere;

	void SEInit(HWND hWnd);

	void Move();
	bool Hit(SPHERE* ppTargetSphere,int iSphereMax);
	bool Form(D3DXVECTOR3 vShotPos,D3DXVECTOR3 vTarget);
	void ReStart();

private:

};

#endif //#ifndef _SHOT_H_