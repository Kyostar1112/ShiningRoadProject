#pragma once

#include	"MyMacro.h"

#include	<Windows.h>

#include	<D3DX11.h>
#include	<D3D11.h>

#include	<D3DX10.h>//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include	<D3D10.h>



//============================================================
//	���C�u����.
//============================================================
#pragma comment( lib, "winmm.lib" )

#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )

#pragma comment( lib, "d3dx10.lib" )//�uD3DX�`�v�̒�`�g�p���ɕK�v.

//�\����.
struct  TEXT_CONSTANT_BUFFER
{
	D3DXMATRIX	mWVP;
	D3DXVECTOR4	vColor;
	D3DXVECTOR4	fAlpha;
};

//�e�L�X�g�̈ʒu���.
struct TextVertex
{
	D3DXVECTOR3	Pos;	//�ʒu.
	D3DXVECTOR2	Tex;	//�e�N�X�`�����W.
};

