#ifndef SCENE_TITLE_INFORMATION_H_
#define SCENE_TITLE_INFORMATION_H_


//���̈���.
enum enBGM : int
{
	enBGM_MAOU1 = 0,
	enBGM_MAOU3,
};

enum enSE : int
{
	enSE_CURSOL_MOVE = 0,
	enSE_ENTER,
	enSE_EXIT,

	enSE_BOMBER,

	enSE_WIN_APP,
	enSE_WIN_DISAPP
};

//���j���[����󂯎���������ƍ�����.
enum enINFORMATION_INDEX : char
{
	enINFORMATION_INDEX_GAME_END = 0,
	enINFORMATION_INDEX_NEXT_SCENE,
	enINFORMATION_INDEX_CLOSE_MENU,

	enINFORMATION_INDEX_size
};

#endif//#ifndef SCENE_TITLE_INFORMATION_H_