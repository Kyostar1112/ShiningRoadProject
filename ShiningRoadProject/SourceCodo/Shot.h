#ifndef _SHOT_H_
#define _SHOT_H_

#include"CEffects.h"
#include"CSound.h"
#include"Resource.h"
#include"CSkinChara.h"

#define SHOT_SPEED 1.0f

struct SHOT_EFC
{
	clsEffects::enEfcType ShotEfcType;
	clsEffects::enEfcType LineEfcType;
	clsEffects::enEfcType HitEfcType;
};

class clsShot
{
public:
	clsShot();
	~clsShot();

	DXSTATIC_TRANSFORM m_Trans;

	D3DXVECTOR3 m_vStartPos;
	D3DXVECTOR3 vMoveAxis;

	int m_iThisShotIndex;
	clsSound** m_ppSE;
	int m_iSoundMaxNo;

	D3DXVECTOR3 m_vMoveAxis;

	bool m_bShotExistFlg;//�e�̑��݊m�F(false�Ȃ�e�����݂��Ȃ����).
	bool m_bExistFlg;//�e,����,�O�Ղ̑��݊m�F(false�Ȃ炻���S�Ă����݂��Ȃ����)

	HRESULT Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11, SHOT_EFC ShotEffects, clsEffects::UseChar UseChar);

	clsEffects::UseChar m_UseChar;

	clsEffects* m_pEffect;
	::Effekseer::Handle m_ShotEfcH;
	::Effekseer::Handle m_LineEfcH;
	::Effekseer::Handle m_HitEfcH;

	SHOT_EFC ShotEfcTypes;

	SPHERE m_Sphere;

	void SEInit(HWND hWnd);

	void Move();
	bool Hit(SPHERE* ppTargetSphere,int iSphereMax);
	bool Form(D3DXVECTOR3 vShotPos,D3DXVECTOR3 vTarget);
	void ReStart();

private:

};

#endif //#ifndef _SHOT_H_