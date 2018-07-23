#pragma once 


#include "AssembleModel.h"


#define sBONE_NAME_COL_JOINT	"Joint"//00�`xx.





class clsMISSION_MODEL : public clsASSEMBLE_MODEL
{
public:
	clsMISSION_MODEL();
	~clsMISSION_MODEL();

	enum enCOL_PARTS : UCHAR
	{
		enCOL_PARTS_LEG = 0,
		enCOL_PARTS_CORE,
		enCOL_PARTS_HEAD,
		enCOL_PARTS_ARMS,

		enCOL_PARTS_size
	};

	//���̃p�[�c�̓����蔻��̐���Ԃ�.
	int GetColNum( const enCOL_PARTS enColParts );

	//�����蔻��̍��W�̔z������ׂĕԂ�.
	std::vector< D3DXVECTOR3 > GetColPosArr();

private:

	int m_iColNum[enCOL_PARTS_size];

};

