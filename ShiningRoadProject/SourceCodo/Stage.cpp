#include "Stage.h"
#include "File.h"

using namespace std;

const char* sSTAGE_BASE_DATA_PATH = "Data\\Stage\\StageBase.csv";
const char* sBUILDING_DATA_PATH = "Data\\Stage\\Building.csv";

//�t�@�C���ǂݎ�莞�̓Y����.
const char cINDEX_POS_X = 0;
const char cINDEX_POS_Y = 1;
const char cINDEX_POS_Z = 2;

const char cINDEX_ROT_X = 3;
const char cINDEX_ROT_Y = 4;
const char cINDEX_ROT_Z = 5;

const char cINDEX_SCALE_X = 6;
const char cINDEX_SCALE_Y = 7;
const char cINDEX_SCALE_Z = 8;


clsStage::clsStage( clsResource* const pResource )
{
	clsFILE file;
	file.Open( sSTAGE_BASE_DATA_PATH );
	//�y��.
	m_pStageGround = make_unique< clsCharaStatic >();
	m_pStageGround->AttachModel( 
		pResource->GetStaticModels( clsResource::enStaticModel_StageBase ) );

	//�X�e�[�^�X�󂯎��.
	//���W.
	m_pStageGround->SetPosition( {
		file.GetDataFloat( 0, cINDEX_POS_X ),
		file.GetDataFloat( 0, cINDEX_POS_Y ),
		file.GetDataFloat( 0, cINDEX_POS_Z ) } );
	//��].
	m_pStageGround->SetRotation( {
		file.GetDataFloat( 0, cINDEX_ROT_X ),
		file.GetDataFloat( 0, cINDEX_ROT_Y ),
		file.GetDataFloat( 0, cINDEX_ROT_Z ) } );
	//�k��.
	m_pStageGround->SetScale( {
		file.GetDataFloat( 0, cINDEX_SCALE_X ),
		file.GetDataFloat( 0, cINDEX_SCALE_Y ),
		file.GetDataFloat( 0, cINDEX_SCALE_Z ) } );
	file.Close();

	//��Q��.
	file.Open( sBUILDING_DATA_PATH );
	m_vpStageObject.resize( file.GetSizeRow() );
	for( unsigned int i=0; i<m_vpStageObject.size(); i++ ){
		m_vpStageObject[i] = make_unique< clsCharaStatic >();
		m_vpStageObject[i]->AttachModel( 
			pResource->GetStaticModels( clsResource::enStaticModel_Building ) );

		//���W.
		m_vpStageObject[i]->SetPosition( {
			file.GetDataFloat( i, cINDEX_POS_X ),
			file.GetDataFloat( i, cINDEX_POS_Y ),
			file.GetDataFloat( i, cINDEX_POS_Z ) } );
		//��].
		m_vpStageObject[i]->SetRotation( {
			file.GetDataFloat( i, cINDEX_ROT_X ),
			file.GetDataFloat( i, cINDEX_ROT_Y ),
			file.GetDataFloat( i, cINDEX_ROT_Z ) } );
		//�k��.
		m_vpStageObject[i]->SetScale( {
			file.GetDataFloat( i, cINDEX_SCALE_X ),
			file.GetDataFloat( i, cINDEX_SCALE_Y ),
			file.GetDataFloat( i, cINDEX_SCALE_Z ) } );
	}
	file.Close();
}
//enStaticModel_Building
clsStage::~clsStage()
{
	m_pStageGround->DetatchModel();

	for( unsigned int i=0; i<m_vpStageObject.size(); i++ ){
		m_vpStageObject[i]->DetatchModel();
	}
}

void clsStage::Render(
	const D3DXMATRIX &mView, const D3DXMATRIX &mProj,
	const D3DXVECTOR3 &vLight, const D3DXVECTOR3 &vEye )
{
	m_pStageGround->Render( mView, mProj, vLight, vEye );

	for( unsigned int i=0; i<m_vpStageObject.size(); i++ ){
		m_vpStageObject[i]->Render( mView, mProj, vLight, vEye );
	}
}


bool clsStage::WallJudge( clsObject* const pObj )
{
	bool bHit = false;

	//StageGround�Ƃ̓����蔻��.
	clsDX9Mesh* pGround = m_pStageGround->GetModelPtr();

	if (pObj->WallForward(pGround))if (!bHit)bHit = true;
	if (pObj->WallBack(pGround))if (!bHit)bHit = true;
	if (pObj->WallLeft(pGround))if (!bHit)bHit = true;
	if (pObj->WallRight(pGround))if (!bHit)bHit = true;

	pObj->m_bGround = pObj->WallUnder(pGround);
	if (pObj->m_bGround)if (!bHit)bHit = true;
	if (pObj->WallUp(pGround))if (!bHit)bHit = true;

	for (int i = 0; i < 1; i++)
	{
		clsDX9Mesh* pObjMesh = m_vpStageObject[i]->GetModelPtr();

		//StageObject�Ƃ̓����蔻��.
		if (pObj->WallForward(pObjMesh))if (!bHit)bHit = true;
		if (pObj->WallBack(pObjMesh))if (!bHit)bHit = true;
		if (pObj->WallLeft(pObjMesh))if (!bHit)bHit = true;
		if (pObj->WallRight(pObjMesh))if (!bHit)bHit = true;

		if (pObj->WallUnder(pObjMesh))
		{
			pObj->m_bGround = true;
			if (!bHit)bHit = true;

			D3DXVECTOR3 vMoveDir = pObj->GetPosition();

			vMoveDir += {0.0f, 0.0f, 0.0f};

			pObj->SetPosition(vMoveDir);
		}

		if (pObj->WallUp(pObjMesh))if (!bHit)bHit = true;
	}

		

	return bHit;
}


