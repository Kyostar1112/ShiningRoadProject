#ifndef SCENE_GAME_OVER_H_
#define SCENE_GAME_OVER_H_


#include "SceneBase.h"
#include "CameraGameOver.h"
#include "MissionModel.h"
#include "Sprite2DCenter.h"
class clsMENU_WINDOW_GAME_OVER_CONTINUE;

//================================//
//========== ゲームオーバークラス ==========//
//================================//
class clsSCENE_GAME_OVER : public clsSCENE_BASE
{
public:
	clsSCENE_GAME_OVER( clsPOINTER_GROUP* const ptrGroup );
	~clsSCENE_GAME_OVER();


private:

	void CreateProduct() final;
	void UpdateProduct( enSCENE &enNextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) final;
	void RenderUi() final;//「 UIの 」Render.

	//メニューの動き.
	void MenuUpdate( enSCENE &enNextScene );



	struct MESSAGE_TEXT_STATE
	{
		D3DXVECTOR3 vPos;
		float fScale;

		MESSAGE_TEXT_STATE()
		:vPos( { 0.0f, 0.0f, 0.0f } )
		,fScale( 0.0f )
		{}
	};

	enum enMESSAGE_INDEX : int
	{
		enMESSAGE_INDEX_MISSION_FAILD = 0,
		enMESSAGE_INDEX_GAME_OVER,
		enMESSAGE_INDEX_NEVER_GIVE_UP,

		enMESSAGE_INDEX_size
	};
	MESSAGE_TEXT_STATE m_TextStateArray[ enMESSAGE_INDEX_size ];
	enMESSAGE_INDEX m_enTextRenderIndex;







	//メッセボックス.
	std::unique_ptr< clsMENU_WINDOW_GAME_OVER_CONTINUE > m_upMenu;
	
	//メニューから帰ってくる情報との照合用.
	std::vector<unsigned int> m_vecuiInformationDataArray;




	//黒背景.
	std::unique_ptr< clsSprite2D > m_upBlackBack;



#if _DEBUG
	//デバック゛テキストの表示.
	void RenderDebugText() final;
#endif//#if _DEBUG


};
#endif//#ifndef SCENE_GAME_OVER_H_