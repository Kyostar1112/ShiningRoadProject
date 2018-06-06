#pragma once

#include "File.h"

#include "SceneClass.h"
#include "CameraAssemble.h"
#include "AssembleModel.h"

#include <vector>
#include <string>

//================================//
//========== �g�݊����N���X ==========//
//================================//
class clsSCENE_ASSEMBLE : public clsSCENE_BASE
{
public:
	clsSCENE_ASSEMBLE( clsPOINTER_GROUP* const ptrGroup );
	~clsSCENE_ASSEMBLE();

	//�I�����̂���p�[�c�̎��( �z��̓Y�����ɂȂ� ).
	enum enPARTS_TYPES : UCHAR
	{
		LEG = 0,
		CORE,
		HEAD,
		ARMS,
		WEAPON,

		ENUM_SIZE
	};

	//�ǂ̃p�[�c��I��ł��?.
	struct PARTS_SELECT
	{
		int iType;	//�p�[�c�̎��( �r�A�R�A�� ).
		int iNum;	//�p�[�c�ԍ�.

		PARTS_SELECT(){
			iType = iNum = 0;
		}
	}m_PartsSelect;



private:

	void CreateProduct() final;
	void UpdateProduct( enSCENE &nextScene ) final;
	void RenderProduct( const D3DXVECTOR3 &vCamPos ) final;

#if _DEBUG
	//�f�o�b�N�J�e�L�X�g�̕\��.
	void RenderDebugText() final;
#endif//#if _DEBUG


	clsASSEMBLE_MODEL*	m_pAsmModel;

	clsFILE*	m_pFile[enPARTS_TYPES::ENUM_SIZE];

//	clsSPRITE2D_CENTER* m_pSprite;
//	clsCharaStatic* m_pTestChara;
//	clsCharaStatic* m_pParts;


};



