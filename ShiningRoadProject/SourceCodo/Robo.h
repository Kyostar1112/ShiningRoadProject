#pragma once



#include"Charactor.h"
#include"SkinMesh.h"


//太原の書き足した分.
#ifdef Tahara
#include "PtrGroup.h"

//2018/05/16( 水 ).
	//関数「RoboInit」に「clsPOINTER_GROUP」型の引数を追加し、.
	//追加したメンバ変数( m_wpResource、m_wpEffects、m_wpSound ).
	//にアドレスを割り当てる処理を追加しました.
	
	//装飾子の都合上このクラスの「Render」関数と.
	//「clsSkinMesh」クラスの「ModelRender」関数と.
	//「clsD3DXSKINMESH」クラスの「Render」関数の.
	//引数にconstを付けました.
	
	//Zeromemoryはポインタが大暴れするので初期化を一つ一つ行いました.
	//↑「clsCharactor」と「clsObject」「clsSkinMesh」も.

#endif//#ifdef Tahara



class clsRobo : public clsCharactor
{
public:
	/*clsSkinMesh * m_pHead;
	clsSkinMesh * m_pCore;
	clsSkinMesh * m_pLeftArm;
	clsSkinMesh * m_pRightArm;
	clsSkinMesh * m_pLeg;*/
	clsSkinMesh* m_pMesh;

	void RoboInit(HWND hWnd,
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11,
		clsPOINTER_GROUP* const pPtrGroup );

	void Update()
	{
		DXSKIN_TRANSFORM tmpTrans;

		tmpTrans.fPitch = m_Trans.fPitch;
		tmpTrans.fYaw = m_Trans.fYaw;
		tmpTrans.fRoll = m_Trans.fRoll;
		tmpTrans.vPos = m_Trans.vPos;
		tmpTrans.vScale = m_Trans.vScale;

		m_pMesh->ModelUpdate(tmpTrans);
	}

	void Render( 
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye,
		const D3DXVECTOR4 &vColor = { 1.0f, 1.0f, 1.0f ,1.0f },
		const bool alphaFlg = false )
	{
		Update();
		m_pMesh->ModelRender(mView, mProj, vLight, vEye, vColor, alphaFlg );
	}

	bool m_bBoost;

	float m_fWalktMoveSpeedMax;
	int m_fWalkTopSpeedFrame;

	float m_fBoostMoveSpeedMax;
	int m_iBoostTopSpeedFrame;

	float m_fBoostRisingSpeedMax;//スピードの最大値.
	int m_iBoostRisingTopSpeedFrame;//↑に達するまでのフレーム値.
	float m_fBoostRisingAccele;// = m_fMoveSpeedMax / m_fTopSpeedFrame;

	void Walk();
	void Boost();
	void MoveSwitch();
	void BoostRising();
	void QuickBoost();
	void SetDirQuickBoost(const float fAngle);

	clsRobo();
	~clsRobo();

private:


//太原の書き足した分.
#ifdef Tahara
	//消すときdeleteしないでnullしてね.
	clsResource*		m_wpResource;
	clsEffects*			m_wpEffects;
	clsSOUND_MANAGER*	m_wpSound;
#endif//#ifdef Tahara


};


