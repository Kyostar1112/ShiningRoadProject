#ifndef MENU_WINDOW_GAME_OVER_CONTINUE_H_
#define MENU_WINDOW_GAME_OVER_CONTINUE_H_

#include "MenuWindowBase.h"

//���ꂽ�Ƃ��ɃR���e�B�j���[���邩���Ȃ��������Ă���.
//�R���e�B�j���[����Ȃ烍�{��g�݂Ȃ����������Ă��郁�j���[���J��.
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




};
#endif//#ifndef MENU_WINDOW_GAME_OVER_CONTINUE_H_