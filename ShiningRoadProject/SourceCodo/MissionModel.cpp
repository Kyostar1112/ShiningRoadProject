#include "MissionModel.h"

using namespace std;

clsMISSION_MODEL::clsMISSION_MODEL()
	:m_iColNum()
{
}

clsMISSION_MODEL::~clsMISSION_MODEL()
{
}




//���̃p�[�c�̓����蔻��̐���Ԃ�.
int clsMISSION_MODEL::GetColNum( const enCOL_PARTS enColParts )
{
	int iReturn = 0;

	switch( enColParts )
	{
	case enCOL_PARTS_LEG:
		break;
	case enCOL_PARTS_CORE:
		break;
	case enCOL_PARTS_HEAD:
		break;
	case enCOL_PARTS_ARMS:
		break;
	default:
		break;
	}

	return iReturn;
}

//�����蔻��̍��W�̔z������ׂĕԂ�.
vector< D3DXVECTOR3 > clsMISSION_MODEL::GetColPosArr()
{
	vector< D3DXVECTOR3 > vvReturn;

	return vvReturn;
}

