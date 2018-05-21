#ifndef _ENEMY_H_
#define _ENEMY_H_
#pragma warning(disable:4005)//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.

#define _CRT_SECURE_NO_WARNINGS

#include"CD3DXSKINMESH.h"
#include"DX9Mesh.h"
#include"CSkinChara.h"
#include<math.h>
#include"UISprite.h"
#include "Resource.h"
#include "Shot.h"

//========================================================
//	�萔.
//========================================================
#define E_MOVE_SPEED 0.075f//�ړ����x.
#define E_HP 10

#define E_DOWNBOM 2

#define E_SHOTCNT 60

#define HP_DISP 5

//========================================================
//	�\����.
//========================================================

/*struct sound_data//����ލ\����.
{
char sPath[256];//̧�ٖ�.
char sAlias[256];//��ر�.
};*/



//========================================================
//	��ڲ԰�׽.
//========================================================

enum E_MOVEPATTERN
{
	enMPattaern_None = 0,
	enMPattaern_Normal,
};

struct FILELOAD
{
	D3DXVECTOR3 vOrizinPos;
	int MovePattern;
};

class clsEnemy : public clsSkinChara
{
public:
	//========================================================
	//	�񋓑�.
	//========================================================

	//���޸��.
	D3DXVECTOR3 vecAxisZ;
	D3DXVECTOR3 vecAxisX;

	D3DXVECTOR3 m_vCamPos;

	int HP;//�̗�.
	int m_MaxHP;//�ő�̗�.

	//�ʒu�\����.
	//DXSTATIC_TRANSFORM m_StaticTrans;

	clsDX9Mesh* m_pDX9Mesh;

	bool m_bDeadFlg;//���S�׸�.

	//����(�����Ŏg�����͂킩��Ȃ�)
	clsSound** m_pSE;
	int m_iSoundMaxNo;

	int m_iShotMax;
	int m_iShotCnt;
	D3DXVECTOR3 m_vShotStartPos;
	clsShot** m_ppShot;

	//�����蔻��֌W.
	SPHERE m_BodySphere;

	bool ShotCollision(SPHERE* pTargrt, int iSphereMax = 1);
	bool BodyCollision(SPHERE* pTargrt, int iSphereMax = 1);
	
#if _DEBUG
	//�޳��ިݸ޽̨��p.
	clsDX9Mesh* m_pBodySphere;
#endif

	D3DXVECTOR3 m_vOriginPos;//��ʒu.
	D3DXVECTOR3 m_vOldPos;

	int m_iThisEnemyIndex;
	int m_iMovePattern;

	/*====/ �̪�� /====*/

	clsEffects* m_pEffect;
	/*/ ����� /*/
	::Effekseer::Handle m_DownEfc;
	::Effekseer::Handle m_DeadEfc;

	int m_iDownEfcCnt;

	clsEnemy();
	~clsEnemy();

	HRESULT Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

	void HPUIRender(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vEye);

	bool LockOnFlg;
	void LockOnRender(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vEye);

	void GameMove(D3DXVECTOR3 PlayerPos, clsDX9Mesh* Ground);//�ްђ��ł̓���.

	void SEInit(HWND hWnd);
	void SEUpdate();

	void UpdateCollisionPos();

	void TrackingMove(D3DXVECTOR3 PlayerPos, clsDX9Mesh* Ground);

	void Update();
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vEye, LPD3DXANIMATIONCONTROLLER pAC = NULL);

	void Hit(int Damage);

	void VectorInput(FILE *fp, int No);//csv̧�ق���float�̐��l������(���ǂ̗]�n����)

	void ReStart();

private:
	clsUISprite* m_pHp;//HP�ް�ޕ\��.
	clsUISprite* m_pHpFrame;//HP�ް�ނ̘g.
	clsUISprite* m_pLockOn;//ۯ��ݶ���.

	void HPUIInit(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	void HPUIControl();

	void LockOnInit(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	void LockOnControl();
};

#endif//#ifndef _ENEMY_H_