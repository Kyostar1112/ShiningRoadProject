#include "SceneMission.h"


//================================//
//========== ミッション中クラス ==========//
//================================//
clsSCENE_MISSION::clsSCENE_MISSION( clsPOINTER_GROUP* const ptrGroup ) : clsSCENE_BASE( ptrGroup ),
	m_pTestRobo( nullptr ),
	m_pTestChara( nullptr )
{
}

clsSCENE_MISSION::~clsSCENE_MISSION()
{
	SAFE_DELETE( m_pTestChara );
	SAFE_DELETE( m_pTestRobo );
}

//生成時に一度だけ通る処理.
void clsSCENE_MISSION::CreateProduct()
{
	m_pTestRobo = new clsTestObj;
	m_pTestRobo->Init(nullptr, nullptr, nullptr, m_wpDxInput, m_wpPtrGroup);//4つ目の引数は効果音やエフェクトを出すために追加しました.

	D3DXVECTOR3 tmpVec3 = { 0.0f, 10.0f, 0.0f };
	m_pTestRobo->SetPosition(tmpVec3);
	m_pTestRobo->SetScale(0.01f);

	//テストモデルの初期化.
	m_pTestChara = new clsCharaStatic;
	m_pTestChara->AttachModel( 
		m_wpResource->GetStaticModels( 
			clsResource::enSTATIC_MODEL::enStaticModel_Enemy ) );
	m_pTestChara->Init();
	m_pTestChara->SetPosition( D3DXVECTOR3( -2.0f, 0.0f, 0.0f ) );
	m_pTestChara->SetRotation( D3DXVECTOR3( 0.0f, 0.0f, D3DX_PI*0.5 ) );

	m_pStage = m_wpResource->GetStaticModels(clsResource::enStaticModel_Ground);
	m_pStage->m_Trans.fScale = 10.0f;
	m_pStage->m_Trans.fYaw = 0.0f;
	m_pStage->m_Trans.fRoll = 0.0f;
	m_pStage->m_Trans.fPitch = 0.0f;
	m_pStage->m_Trans.vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//毎フレーム通る処理.
void clsSCENE_MISSION::UpdateProduct( enSCENE &nextScene )
{
	//nullならassert.
	ASSERT_IF_NULL( m_pTestRobo );
	m_pTestRobo->Action(m_pStage);

	//エンディングに行く場合は以下のようにする.
	if( !"クリア条件を満たすとここを通る" ){
		nextScene = enSCENE::ENDING;
	}
}

//描画.
void clsSCENE_MISSION::RenderProduct( const D3DXVECTOR3 &vCamPos )
{
	//Render関数の引数を書きやすくするための変数.
	D3DXVECTOR3 vTmp = m_pTestRobo->m_Trans.vPos;
	m_wpCamera->SetPos(vTmp);

	vTmp = m_pTestRobo->m_Trans.vPos - (m_pTestRobo->GetVec3Dir(m_pTestRobo->m_Trans.fYaw, vDirForward) * 2);
	vTmp.y += 0.5f;
	m_wpCamera->SetPos(vTmp, false);

	m_wpCamera->GetPos();

	m_pTestChara->Render(m_mView, m_mProj, m_vLight, vCamPos);
	m_pTestRobo->Render(m_mView, m_mProj, m_vLight, vCamPos);
	m_pStage->Render(m_mView, m_mProj, m_vLight, vCamPos);
}

