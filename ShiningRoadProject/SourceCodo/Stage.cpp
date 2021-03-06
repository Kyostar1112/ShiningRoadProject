#include "Stage.h"
#include "File.h"
#include "Building.h"
#include "PtrGroup.h"
#include "ObjStaticMesh.h"

using namespace std;

const char* sSTAGE_BASE_DATA_PATH = "Data\\Stage\\StageBase.csv";
const char* sBUILDING_DATA_PATH = "Data\\Stage\\Building.csv";

//ファイル読み取り時の添え字.
const char cINDEX_POS_X = 0;
const char cINDEX_POS_Y = 1;
const char cINDEX_POS_Z = 2;

const char cINDEX_ROT_X = 3;
const char cINDEX_ROT_Y = 4;
const char cINDEX_ROT_Z = 5;

const char cINDEX_SCALE_X = 6;
const char cINDEX_SCALE_Y = 7;
const char cINDEX_SCALE_Z = 8;


clsStage::clsStage( clsPOINTER_GROUP* const pPtrGroup )
{
	clsFILE file;
	file.Open( sSTAGE_BASE_DATA_PATH );
	//土台.
	m_pStageGround = make_unique< clsObjStaticMesh >();
	m_pStageGround->AttachModel( 
		pPtrGroup->GetResource()->GetStaticModels( clsResource::enStaticModel_StageBase ) );

	//ステータス受け取り.
	//座標.
	m_pStageGround->SetPosition( {
		file.GetDataFloat( 0, cINDEX_POS_X ),
		file.GetDataFloat( 0, cINDEX_POS_Y ),
		file.GetDataFloat( 0, cINDEX_POS_Z ) } );
	//回転.
	m_pStageGround->SetRotation( {
		file.GetDataFloat( 0, cINDEX_ROT_X ),
		file.GetDataFloat( 0, cINDEX_ROT_Y ),
		file.GetDataFloat( 0, cINDEX_ROT_Z ) } );
	//縮尺.
	m_pStageGround->SetScale( {
		file.GetDataFloat( 0, cINDEX_SCALE_X ),
		file.GetDataFloat( 0, cINDEX_SCALE_Y ),
		file.GetDataFloat( 0, cINDEX_SCALE_Z ) } );
	file.Close();

	//障害物.
	file.Open( sBUILDING_DATA_PATH );
	m_vpBuilding.resize( file.GetSizeRow() );
	for( unsigned int i=0; i<m_vpBuilding.size(); i++ ){
		m_vpBuilding[i] = make_unique< clsBUILDING >( 
			pPtrGroup->GetDevice(), 
			pPtrGroup->GetContext(), 
			pPtrGroup->GetResource()->GetStaticModels( clsResource::enStaticModel_Building ) );
//		m_vpBuilding[i]->AttachModel( 
//			pResource->GetStaticModels( clsResource::enStaticModel_Building ) );

		//座標.
		m_vpBuilding[i]->SetPos( {
			file.GetDataFloat( i, cINDEX_POS_X ),
			file.GetDataFloat( i, cINDEX_POS_Y ),
			file.GetDataFloat( i, cINDEX_POS_Z ) } );
		//回転.
		m_vpBuilding[i]->SetRot( {
			file.GetDataFloat( i, cINDEX_ROT_X ),
			file.GetDataFloat( i, cINDEX_ROT_Y ),
			file.GetDataFloat( i, cINDEX_ROT_Z ) } );
		//縮尺.
		m_vpBuilding[i]->SetScale( {
			file.GetDataFloat( i, cINDEX_SCALE_X ),
			file.GetDataFloat( i, cINDEX_SCALE_Y ),
			file.GetDataFloat( i, cINDEX_SCALE_Z ) } );
	}
	file.Close();

	const int iBUILDING_UPDATE_TILE_NUM = 100;
	for( unsigned int i=0; i<m_vpBuilding.size(); i++ )
	{
		for( int j=0; j<iBUILDING_UPDATE_TILE_NUM; j++ ){
			m_vpBuilding[i]->UpdateTile();
		}
	}
}
//enStaticModel_Building
clsStage::~clsStage()
{
	m_pStageGround->DetatchModel();

//	for( unsigned int i=0; i<m_vpBuilding.size(); i++ ){
//		m_vpBuilding[i]->DetatchModel();
//	}
}

void clsStage::Render(
	const D3DXMATRIX &mView, const D3DXMATRIX &mProj,
	const D3DXVECTOR3 &vLight, const D3DXVECTOR3 &vEye )
{
	m_pStageGround->Render( mView, mProj, vLight, vEye );

	for( unsigned int i=0; i<m_vpBuilding.size(); i++ ){
		m_vpBuilding[i]->Render( mView, mProj, vLight, vEye );
	}
}

vector<clsDX9Mesh*> clsStage::GetStageMeshArray()
{
	vector<clsDX9Mesh*> vvpMeshArrayTmp;

	int iSize = sizeof(clsDX9Mesh*) * (m_vpBuilding.size() + 1);

	vvpMeshArrayTmp.reserve(iSize);

	for (unsigned int i = 0; i < m_vpBuilding.size(); i++)
	{
		vvpMeshArrayTmp.push_back(m_vpBuilding[i]->GetModelPtr());
	}

	vvpMeshArrayTmp.push_back(m_pStageGround->GetStaticMesh());

	vvpMeshArrayTmp.shrink_to_fit();

	return vvpMeshArrayTmp;
}

void clsStage::SetStageObjTransform(const int iObjNo)
{
	if (iObjNo >= m_vpBuilding.size())
	{
		return;
	}

	m_vpBuilding[iObjNo]->UpdateModel();
}