#ifndef _SHOT_H_
#define _SHOT_H_

#include"Effects.h"
#include"Sound.h"
#include"Object.h"
#include "PtrGroup.h"

struct ShotState
{
	float fShotScale;

	int iSEShotNum;
	int iSEHitNum;

	int iShotEfcNum;
	int iLineEfcNum;
	int iHitEfcNum;
};

class clsShot : public clsObject
{
private:
	enum enSEType
	{
		enSEShot = 0,
		enSEHit,

		enSESize
	};

	enum enEfcType
	{
		enEfcShot = 0,
		enEfcLine,
		enEfcHit,

		enEfcSize
	};

public:
	clsShot(clsPOINTER_GROUP* pPtrGroup);
	~clsShot();

	int m_iThisShotIndex;

	bool m_bShotExistFlg;//�e�̑��݊m�F(false�Ȃ�e�����݂��Ȃ����).
	bool m_bExistFlg;//�e,����,�O�Ղ̑��݊m�F(false�Ȃ炻���S�Ă����݂��Ȃ����)

	HRESULT Init(LPSTR strWeaponFolderName);

	void SEInit(HWND hWnd);

	void Move();
	bool Hit(SPHERE* ppTargetSphere,int iSphereMax);
	bool Form(D3DXVECTOR3 vShotPos,D3DXVECTOR3 vTarget);
	void ReStart();

private:

	clsSound* m_ppSE[enSESize];

	clsEffects* m_wpEffect;

	::Effekseer::Handle m_ShotEfcHandles[enEfcSize];

	D3DXVECTOR3 m_vStartPos;

	ShotState m_ShotState;
};

#endif //#ifndef _SHOT_H_