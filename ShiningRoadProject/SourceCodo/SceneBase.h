#pragma once

#include "Global.h"

#if _DEBUG
#include "DebugText.h"
#endif//#if _DEBUG

#include "CharaStatic.h"

#include "PtrGroup.h"

#include "Sprite2DCenter.h"


//================================//
//========== 基底クラス ==========//
//================================//
class clsSCENE_BASE
{
public:
	//引数はリソースなどのポインタのまとめ.
	clsSCENE_BASE( clsPOINTER_GROUP* const ptrGroup );
	virtual ~clsSCENE_BASE();

	//----- 各シーン共通 -----//.
	//シーン作成直後に「SceneManager.cpp」の「SwitchScene」関数内で使用されている.
	void Create();
	//ループ内の処理( 引数を関数内で変更すると今のシーンが破棄され、.
	//				  指定したシーンが生成される ).
	void Update( enSCENE &enNextScene );
	//シーン内のオブジェクトの描画関数のまとめ.
	void Render();
	//----- 各シーン共通 -----//.


	//メインまで送り上げる.
	D3DXVECTOR3 GetCameraPos() const;
	D3DXVECTOR3 GetCameraLookPos() const;

protected:

	//----- 各シーンごとの関数 -----//.
	virtual void CreateProduct() = 0;//各シーンのCreate.
	virtual void UpdateProduct( enSCENE &enNextScene ) = 0;//各シーンのUpdate.
	virtual void RenderProduct( const D3DXVECTOR3 &vCamPos ) const = 0;//各シーンのRender.
	//----- 各シーンごとの関数 -----//.

	//3D座標をスクリーン( 2D )座標へと変換する.
	//dimensions(次元) conversion(変換).
	//戻り値は2D座標.
	D3DXVECTOR3 ConvDimPos( const D3DXVECTOR3 &v3DPos );


	//----- Render用 -----//.
	//深度テスト(Zテスト)　ON/OFF切替.
	void SetDepth( const bool isOn );
	D3DXMATRIX		m_mView;	//ビュー(カメラ)行列.
	D3DXMATRIX		m_mProj;	//プロジェクション行列.
	D3DXVECTOR3		m_vLight;	//ライトの方向.
	//----- Render用 -----//.


	//デバッグテキストクラス.
#if _DEBUG
	clsDebugText*	m_upText;
	//デバック゛テキストの表示.
	virtual void RenderDebugText();
#endif//#if _DEBUG


	//基底クラスのポインタは基底クラスで破棄します.
	//派生クラスでは破棄しないでください.

	//以下、消すときdeleteしないでnullしてね( この基底クラスのデストラクタでやっています ).
	//カメラ( 必要ならばこれを消して、シーンごとに異なった機能のカメラを作りましょう ).
	clsPOINTER_GROUP*	m_wpPtrGroup;//エフェクトや効果音を必要とするロボちゃんの為にもprivateにするわけにはいかない.
	clsDxInput*			m_wpDxInput;
	clsResource*		m_wpResource;
	clsEffects*			m_wpEffects;
	clsSOUND_MANAGER*	m_wpSound;
	clsCAMERA_BASE*		m_wpCamera;	
	clsROBO_STATUS*		m_wpRoboStatus;
	clsBLACK_SCREEN*	m_wpBlackScreen;


private:

	//----- Render用 -----//.
	//カメラ関数.
	void Camera();
	//プロジェクション関数.
	void Proj();
	//----- Render用 -----//.

	//デバッグ用シーン切り替え.
	void DebugChangeScene( enSCENE &enNextScene ) const;

	//暗転中に待ってくれるために必要.
	enSCENE m_enNextScene;

	ID3D11Device*				m_wpDevice;	//デバイスオブジェクト.
	ID3D11DeviceContext*		m_wpContext;//デバイスコンテキスト.
	D3D10_VIEWPORT*				m_wpViewPort;//2DSp用.
	ID3D11DepthStencilState*	m_wpDepthStencilState;//深度(Z)テスト設定.


};
