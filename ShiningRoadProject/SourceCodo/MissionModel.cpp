#include "MissionModel.h"
#include "OperationString.h"


using namespace std;

//�W���C���g�{�[���̐����̌���.
const char cBONE_NAME_NUM_DIGIT_JOINT = 2;

//�����蔻��.
const int iRESURVE_SIZE_COL = 64;

clsMISSION_MODEL::clsMISSION_MODEL()
	:m_iColNum()
	,m_iColMax( 0 )
	,m_iColStateIndex( 0 )
{
	m_vColStates.reserve( iRESURVE_SIZE_COL );
}

clsMISSION_MODEL::~clsMISSION_MODEL()
{
}

void clsMISSION_MODEL::CreateProduct()
{
	CreateColStateBones();
}


int clsMISSION_MODEL::CreateColStateBones()
{
	int iReturn = 0;
	iReturn += CreateColStateBone( clsMISSION_MODEL::enCOL_PARTS_LEG );
	iReturn += CreateColStateBone( clsMISSION_MODEL::enCOL_PARTS_CORE );
	iReturn += CreateColStateBone( clsMISSION_MODEL::enCOL_PARTS_HEAD );
	iReturn += CreateColStateBone( clsMISSION_MODEL::enCOL_PARTS_ARMS );

	return iReturn;
}



//���̃p�[�c�̓����蔻��̐���Ԃ�.
int clsMISSION_MODEL::CreateColStateBone( const enCOL_PARTS enColParts )
{
	int iReturn = 0;
	clsOPERATION_STRING OprtStr;
	int i = 0;
	int tmpIndex;
	const BONE_SET INIT_BONE_SET;
	 

	switch( enColParts )
	{
	case enCOL_PARTS_LEG:
		tmpIndex = static_cast< int >( enPARTS::LEG );
		//�{�[�������邾���J��Ԃ�.
		while( m_vpParts[ tmpIndex ]->ExistsBone( OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, i, cBONE_NAME_NUM_DIGIT_JOINT ).c_str() ) )
		{
			m_vColStates.push_back( INIT_BONE_SET );
			m_vColStates[ m_iColStateIndex ].iParts = tmpIndex;
			m_vColStates[ m_iColStateIndex ].sName = OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, i, cBONE_NAME_NUM_DIGIT_JOINT );

			m_iColStateIndex ++;	
			i ++;
		}
		m_iColNum[ enColParts ] = iReturn = i;
		break;
	case enCOL_PARTS_CORE:
		tmpIndex = static_cast< int >( enPARTS::CORE );
		if( m_vpParts[ tmpIndex ]->ExistsBone( sBONE_NAME_COL_CORE ) ){
			m_vColStates.push_back( INIT_BONE_SET );
			m_vColStates[ m_iColStateIndex ].iParts = tmpIndex;
			m_vColStates[ m_iColStateIndex ].sName = sBONE_NAME_COL_CORE;

			m_iColStateIndex ++;	
			m_iColNum[ enColParts ] = iReturn = 1;
		}
		break;
	case enCOL_PARTS_HEAD:
		tmpIndex = static_cast< int >( enPARTS::HEAD );
		if( m_vpParts[ tmpIndex ]->ExistsBone( sBONE_NAME_COL_HEAD ) ){
			m_vColStates.push_back( INIT_BONE_SET );
			m_vColStates[ m_iColStateIndex ].iParts = tmpIndex;
			m_vColStates[ m_iColStateIndex ].sName = sBONE_NAME_COL_HEAD;

			m_iColStateIndex ++;	
			m_iColNum[ enColParts ] = iReturn = 1;
		}
		break;
	case enCOL_PARTS_ARMS:
		//���r.
		tmpIndex = static_cast< int >( enPARTS::ARM_L );
		while( m_vpParts[ tmpIndex ]->ExistsBone( OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, i, cBONE_NAME_NUM_DIGIT_JOINT ).c_str() ) )
		{
			m_vColStates.push_back( INIT_BONE_SET );
			m_vColStates[ m_iColStateIndex ].iParts = tmpIndex;
			m_vColStates[ m_iColStateIndex ].sName = OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, i, cBONE_NAME_NUM_DIGIT_JOINT );

			m_iColStateIndex ++;	
			i ++;
		}
		m_iColNum[ enColParts ] = iReturn = i;

		//�E�r.
		tmpIndex = static_cast< int >( enPARTS::ARM_R );
		i = 0;
		while( m_vpParts[ tmpIndex ]->ExistsBone( OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, i, cBONE_NAME_NUM_DIGIT_JOINT ).c_str() ) )
		{
			m_vColStates.push_back( INIT_BONE_SET );
			m_vColStates[ m_iColStateIndex ].iParts = tmpIndex;
			m_vColStates[ m_iColStateIndex ].sName = OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, i, cBONE_NAME_NUM_DIGIT_JOINT );

			m_iColStateIndex ++;	
			i ++;
		}
		m_iColNum[ enColParts ] = iReturn += i;
		break;
	default:
		return -1;
	}

	return iReturn;
}


//�{�[���̐����m�肷��.
void clsMISSION_MODEL::FixBoneStates()
{
	m_vColStates.shrink_to_fit();
	m_iColMax = 0;
	for( UCHAR i=0; i<enCOL_PARTS_size; i++ ){
		m_iColMax += m_iColNum[i];
	}
}

//�e�p�[�c�̓����蔻��̐���Ԃ�.
int clsMISSION_MODEL::GetColNum( const enCOL_PARTS enColParts )
{
	switch( enColParts )
	{
	case enCOL_PARTS_LEG:
	case enCOL_PARTS_CORE:
	case enCOL_PARTS_HEAD:
	case enCOL_PARTS_ARMS:
		return m_iColNum[ enColParts ];
	}

	return -1;
}


//�����蔻��̍��W�̔z������ׂĕԂ�.
vector< D3DXVECTOR3 > clsMISSION_MODEL::GetColPosArr()
{
	vector< D3DXVECTOR3 > vvReturn;

	vvReturn.resize( m_iColMax );

	return vvReturn;
}

