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
	FixBoneStates();
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
	int iReturn = 0;			//�߂�l.
	clsOPERATION_STRING OprtStr;//�{�[�����Ɣԍ����q�������.
	int iColNum = 0;			//m_iColNum�Ɋi�[���铖���蔻��̐�.
	int tmpIndex;				//m_vecpParts�̓Y����.
	const BONE_SET INIT_BONE_SET;//�������p.
	 
	switch( enColParts )
	{
	case enCOL_PARTS_LEG:
		tmpIndex = static_cast< int >( enPARTS::LEG );
		//�{�[�������邾���J��Ԃ�.
		while( m_vecpParts[ tmpIndex ]->ExistsBone( OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, iColNum, cBONE_NAME_NUM_DIGIT_JOINT ).c_str() ) )
		{
			m_vColStates.push_back( INIT_BONE_SET );
			m_vColStates[ m_iColStateIndex ].iParts = tmpIndex;
			m_vColStates[ m_iColStateIndex ].sName = OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, iColNum, cBONE_NAME_NUM_DIGIT_JOINT );

			m_iColStateIndex ++;	
			iColNum ++;
		}
		m_iColNum[ enColParts ] = iReturn = iColNum;
		break;
	case enCOL_PARTS_CORE:
		tmpIndex = static_cast< int >( enPARTS::CORE );
		if( m_vecpParts[ tmpIndex ]->ExistsBone( sBONE_NAME_COL_CORE ) ){
			m_vColStates.push_back( INIT_BONE_SET );
			m_vColStates[ m_iColStateIndex ].iParts = tmpIndex;
			m_vColStates[ m_iColStateIndex ].sName = sBONE_NAME_COL_CORE;

			m_iColStateIndex ++;	
			m_iColNum[ enColParts ] = iReturn = 1;
		}
		break;
	case enCOL_PARTS_HEAD:
		tmpIndex = static_cast< int >( enPARTS::HEAD );
		if( m_vecpParts[ tmpIndex ]->ExistsBone( sBONE_NAME_COL_HEAD ) ){
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
		while( m_vecpParts[ tmpIndex ]->ExistsBone( OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, iColNum, cBONE_NAME_NUM_DIGIT_JOINT ).c_str() ) )
		{
			m_vColStates.push_back( INIT_BONE_SET );
			m_vColStates[ m_iColStateIndex ].iParts = tmpIndex;
			m_vColStates[ m_iColStateIndex ].sName = OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, iColNum, cBONE_NAME_NUM_DIGIT_JOINT );

			m_iColStateIndex ++;	
			iColNum ++;
		}
		m_iColNum[ enColParts ] = iReturn = iColNum;

		//�E�r.
		tmpIndex = static_cast< int >( enPARTS::ARM_R );
		iColNum = 0;
		while( m_vecpParts[ tmpIndex ]->ExistsBone( OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, iColNum, cBONE_NAME_NUM_DIGIT_JOINT ).c_str() ) )
		{
			m_vColStates.push_back( INIT_BONE_SET );
			m_vColStates[ m_iColStateIndex ].iParts = tmpIndex;
			m_vColStates[ m_iColStateIndex ].sName = OprtStr.ConsolidatedNumber( sBONE_NAME_COL_JOINT, iColNum, cBONE_NAME_NUM_DIGIT_JOINT );

			m_iColStateIndex ++;	
			iColNum ++;
		}
		m_iColNum[ enColParts ] = iReturn += iColNum;
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

	m_vvColPos.resize( m_iColMax );
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
shared_ptr< vector< D3DXVECTOR3 > > clsMISSION_MODEL::GetColPosPtr()
{
	for( int i=0; i<m_iColMax; i++ ){
		//�{�[���̍��W���擾.
		m_vvColPos[i] = GetBonePos( 
			static_cast< enPARTS >( m_vColStates[i].iParts ), 
			m_vColStates[i].sName.c_str() );
	}

	shared_ptr< vector< D3DXVECTOR3 > > spvvReturn( &m_vvColPos );

	return spvvReturn;
}

int clsMISSION_MODEL::GetSimilarityNameBoneNum(const enPARTS PartsNum, const char* strBoneName)
{
	int iResult = 0;
	int iSearchNum = 0;

	std::string strBoneNameTmp;

	clsOPERATION_STRING OprtStr;//�{�[�����Ɣԍ����q�������.

	while (1)
	{
		strBoneNameTmp = strBoneName;
		strBoneNameTmp = OprtStr.ConsolidatedNumber(strBoneNameTmp, iSearchNum, cBONE_NAME_NUM_DIGIT_JOINT);
		if (!ExistsBone(PartsNum, strBoneNameTmp.c_str()))
		{
			break;
		}

		iResult++;
		iSearchNum++;
	}

	return iResult;
}

void clsMISSION_MODEL::SetPartsRotate(const enPARTS PartsNum, const D3DXVECTOR3 vRot)
{
	char cTmpNum = static_cast<char>(PartsNum);

	assert(m_vecpParts[cTmpNum]);
	m_vecpParts[cTmpNum]->SetRotation(vRot);
}

//�r�̊p�x�𕐊���͎ʂ���.
D3DXVECTOR3 clsMISSION_MODEL::GetDirfromBone(const enPARTS PartsNum, const char* strBoneRootName, const char* strBoneEndName)
{
	char cTmpNum = static_cast<char>(PartsNum);
	//return m_vecpParts[cTmpNum]->m_pMesh->ExistsBone(sBoneName);

	std::string strBoneRoot;
	std::string strBoneEnd;

	//�{�[���̃x�N�g�����o��( ���[�J�� ).
	D3DXVECTOR3 vVecLocal =
		m_vecpParts[cTmpNum]->GetBonePos(strBoneEndName, true) -
		m_vecpParts[cTmpNum]->GetBonePos(strBoneRootName, true);
	D3DXVec3Normalize(&vVecLocal, &vVecLocal);

	//�{�[���̃x�N�g�����o��( ���[���h ).
	D3DXVECTOR3 vVecWorld =
		m_vecpParts[cTmpNum]->GetBonePos(strBoneEndName) -
		m_vecpParts[cTmpNum]->GetBonePos(strBoneRootName);
	D3DXVec3Normalize(&vVecWorld, &vVecWorld);

	//�x�N�g�������]�l�����߂�.
	D3DXVECTOR3 vRot = { 0.0f, 0.0f, 0.0f };
	//	vRot.x = atanf( vVec.y );//���̃Q�[���̎d�l�Ȃ琳��( 2018/06/19(��)���� )( �܂�S������ ).
	vRot.x = atan2f(vVecLocal.y, -vVecLocal.z);//.
	vRot.y = atan2f(-vVecWorld.x, -vVecWorld.z);//( ���́A�}�C�i�X���������Ă�����AX,Z������ւ���Ă���̂��Ƃ����΁A0�x�Ń��f�������������������� ).

	vRot.x = GuardDirOver(vRot.x);
	vRot.y = GuardDirOver(vRot.y);
	//	vRot.z = GuardDirOver( vRot.z );

	return vRot;
}

void clsMISSION_MODEL::SetPartsAnimNo(const enPARTS PartsNum, const int iAnimIndex, const double dAnimTime)
{
	char cTmpNum = static_cast<char>(PartsNum);

	assert(m_vecpParts[cTmpNum]);
	m_vecpParts[cTmpNum]->SetAnimChange(iAnimIndex, dAnimTime);
}

void clsMISSION_MODEL::SetPartsAnimSpeed(const enPARTS PartsNum, const double dAnimSpeed)
{
	char cTmpNum = static_cast<char>(PartsNum);

	assert(m_vecpParts[cTmpNum]);
	m_vecpParts[cTmpNum]->SetAnimSpeed(dAnimSpeed);
}

void clsMISSION_MODEL::SetPartsAnimNormal(const enPARTS PartsNum, const bool bAnimTimeInit)
{
	char cTmpNum = static_cast<char>(PartsNum);

	assert(m_vecpParts[cTmpNum]);
	m_vecpParts[cTmpNum]->AnimNormal(bAnimTimeInit);
}

void clsMISSION_MODEL::SetPartsAnimReverce(const enPARTS PartsNum, const bool bAnimTimeInit)
{
	char cTmpNum = static_cast<char>(PartsNum);

	assert(m_vecpParts[cTmpNum]);
	m_vecpParts[cTmpNum]->AnimReverce(bAnimTimeInit);
}

const int clsMISSION_MODEL::GetPartsAnimNo(const enPARTS PartsNum)
{
	char cTmpNum = static_cast<char>(PartsNum);

	assert(m_vecpParts[cTmpNum]);
	return m_vecpParts[cTmpNum]->GetAnimNo();
}

const bool clsMISSION_MODEL::IsPartsAnimEnd(const enPARTS PartsNum)
{
	char cTmpNum = static_cast<char>(PartsNum);

	assert(m_vecpParts[cTmpNum]);
	return m_vecpParts[cTmpNum]->IsAnimTimeEnd();
}

const double clsMISSION_MODEL::GetPartsAnimNowTime(const enPARTS PartsNum)
{
	char cTmpNum = static_cast<char>(PartsNum);

	assert(m_vecpParts[cTmpNum]);
	return m_vecpParts[cTmpNum]->GetAnimTime();
}

const bool clsMISSION_MODEL::IsPartsAnimReverce(const enPARTS PartsNum)
{
	char cTmpNum = static_cast<char>(PartsNum);

	assert(m_vecpParts[cTmpNum]);
	return m_vecpParts[cTmpNum]->IsAnimReverce();
}