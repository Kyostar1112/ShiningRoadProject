#ifndef MENU_WINDOW_GAME_OVER_CONTINUE_H_
#define MENU_WINDOW_GAME_OVER_CONTINUE_H_

#include "MenuWindowBase.h"

//やられたときにコンティニューするかしないか聞いてくる.
//コンティニューするならロボを組みなおすか聞いてくるメニューを開く.
class clsMENU_WINDOW_GAME_OVER_CONTINUE : public clsMENU_WINDOW_BASE
{
public:
	clsMENU_WINDOW_GAME_OVER_CONTINUE(
		clsPOINTER_GROUP* const pPtrGroup,
		clsMENU_WINDOW_BASE* const pParentWindow,
		unsigned int* const pInformationArray );
	~clsMENU_WINDOW_GAME_OVER_CONTINUE();

private:
	
	void UpdateProduct() override;
	void RenderProduct() override;
	bool CreateNextWindowProduct( 
		clsMENU_WINDOW_BASE** ppOutNextWindow, 
		clsMENU_WINDOW_BASE* const pParentWindow ) override;

	enum enSE : int
	{
		enSE_CURSOL_MOVE = 0,
		enSE_ENTER,
		enSE_EXIT,
		enSE_MISSION_START,
		enSE_WIN_APP,
		enSE_WIN_DISAPP,
	};



};
#endif//#ifndef MENU_WINDOW_GAME_OVER_CONTINUE_H_