#ifndef GLOBAL_H_	//�C���N���[�h�K�[�h.
#define GLOBAL_H_


//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )

//���KyoStar.
#define Inoue

//����.
#define Tahara


//============================================================
//	�C���N���[�h.
//============================================================
#include "MyMacro.h"
	    
#include <Windows.h>
	    
#include <D3DX11.h>
#include <D3D11.h>
	    
#include <D3DX10.h>//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>

#include <memory>

//============================================================
//	���C�u����.
//============================================================
#pragma comment( lib, "winmm.lib" )

#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )

#pragma comment( lib, "d3dx10.lib" )//�uD3DX�`�v�̒�`�g�p���ɕK�v.



//============================================================
//	�萔.
//============================================================
#define WND_W 1280	//�E�B���h�E��.
#define WND_H 720	//�E�B���h�E����.



//�i�s�����񋓑�.
enum class enDIRECTION : UCHAR
{
	STOP	= 0,//��~.
	FOWARD,		//�O�i.
	BACK,	//���.
//	enDirection_LeftTurn,	//����].
//	enDirection_RightTurn	//�E��].
};


//���̃Q�[���̊e�V�[���̗񋓑�( �t���O�p ).
enum class enSCENE : UCHAR
{
	TITLE,		//�^�C�g�����.
	ASSEMBLE,	//�p�[�c�g�݊������.
	MISSION,	//�A�N�V�����V�[��( �Q�[���̃��C�� ).
	ENDING,		//�N���A��.
	GAMEOVER,		//�Q�[���I�[�o�[.			

	NOTHING		//�uSwitchScene�v�֐��̃t���O�p.
				//�Ȃ�̃V�[�����w�肵�Ă��Ȃ�.
};



#endif//#ifndef GLOBAL_H_