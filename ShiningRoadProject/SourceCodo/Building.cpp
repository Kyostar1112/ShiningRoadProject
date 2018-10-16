#include "Building.h"

using namespace std;

const char* sTEX_NAME_SIDE = "Data\\Image\\Building\\BuildingTexSide.png";
const char* sTEX_NAME_TOP  = "Data\\Image\\Building\\BuildingTexTop.png";


const int iRESURVE_NUM = 256;

const D3DXVECTOR3 vTILE_SIZE_MIN = { 25.0f, 25.0f, 1.0f };
const D3DXVECTOR3 vTILE_SIZE_MAX = { 30.0f, 30.0f, 1.0f };

//���ʂ�for���̑�����.
const int iSIDE_TILE_COUNT_NUM = 2;


clsBUILDING::clsBUILDING( 
		ID3D11Device* const pDevice11,
		ID3D11DeviceContext* const pContext11,
		clsDX9Mesh* const pModel )
	:m_wpDevice( pDevice11 )
	,m_wpContext( pContext11 )
	,m_Trans( { 
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 100.0f, 100.0f, 100.0f } } )
{
	m_upBox = make_unique< clsCharaStatic >();
	m_upBox->AttachModel( pModel );



	m_vvTop.resize( 1 );
	m_vvTop.reserve( iRESURVE_NUM );
	for( unsigned int Row=0; Row<m_vvTop.size(); Row++ ){
		m_vvTop[ Row ].resize( 1 );
		m_vvTop[ Row ].reserve( iRESURVE_NUM );
	}
	m_upTop = make_unique< clsSprite >();
	m_upTop->Create( pDevice11, pContext11, sTEX_NAME_TOP );


	for( int SideNum=0; SideNum<enWALL_DIRECTION_size; SideNum++  ){
		m_vvSide[ SideNum ].resize( 12 );
		m_vvSide[ SideNum ].reserve( iRESURVE_NUM );
		for( unsigned int Row=0; Row<m_vvSide[ SideNum ].size(); Row++ ){
			m_vvSide[ SideNum ][ Row ].resize( 12 );
			m_vvSide[ SideNum ][ Row ].reserve( iRESURVE_NUM );
		}
	}
	m_upSide = make_unique< clsSprite >();
	m_upSide->Create( pDevice11, pContext11, sTEX_NAME_SIDE );
}

clsBUILDING::~clsBUILDING()
{
	m_upBox->DetatchModel();
	m_wpDevice = nullptr;
	m_wpContext = nullptr;
}



void clsBUILDING::Update()
{
//	if( GetAsyncKeyState( VK_UP ) & 0x8000 )	m_Trans.vPos.z += 1.0f;
//	if( GetAsyncKeyState( VK_DOWN ) & 0x8000 )	m_Trans.vPos.z -= 1.0f;
//	if( GetAsyncKeyState( VK_RIGHT ) & 0x8000 )	m_Trans.vPos.x += 1.0f;
//	if( GetAsyncKeyState( VK_LEFT ) & 0x8000 )	m_Trans.vPos.x -= 1.0f;
//
//	if( GetAsyncKeyState( 'W' ) & 0x1 )		m_Trans.vScale.z += 10.0f;
//	if( GetAsyncKeyState( 'S' ) & 0x1 )		m_Trans.vScale.z -= 10.0f;
//	if( GetAsyncKeyState( 'D' ) & 0x1 )		m_Trans.vScale.x += 10.0f;
//	if( GetAsyncKeyState( 'A' ) & 0x1 )		m_Trans.vScale.x -= 10.0f;
//	if( GetAsyncKeyState( 'E' ) & 0x1 )		m_Trans.vScale.y += 10.0f;
//	if( GetAsyncKeyState( 'Q' ) & 0x1 )		m_Trans.vScale.y -= 10.0f;
//
//	if( GetAsyncKeyState( 'R' ) & 0x1 )	m_Trans.vRot.y += 0.01f;
//	if( GetAsyncKeyState( 'F' ) & 0x1 )	m_Trans.vRot.y -= 0.01f;


	m_upBox->SetPosition( m_Trans.vPos );
	m_upBox->SetRotation( m_Trans.vRot );
	m_upBox->SetScale( m_Trans.vScale );

	//���.
	{
		const int iEND_LOOP = 1;
		unsigned int uiROW = m_vvTop.size();
		unsigned int uiCOL = m_vvTop[0].size();
#if 0
		//�������̂��J��Ԃ��Ȃ����߂̃`�F�b�N�p�z��.
		vector<unsigned int> vuiRow;
		vector<unsigned int> vuiCol;
		vuiRow.reserve( iRESURVE_NUM );
		vuiCol.reserve( iRESURVE_NUM );
		bool isRowEnd = false;
		for( int i=0; i<iEND_LOOP;  ){
			//�^�C���̖ڕW�������.
			SetTileNumTargetTop( uiROW, uiCOL );
			//�ڕW�̐��ɍ��킹�ă^�C���𑝌�����.
			SetTileNumTop( uiROW, uiCOL );
			//�^�C������ׂ�.
			SetTransformTop();
			//���₷.
			vuiRow.push_back( uiROW );
			vuiCol.push_back( uiCOL );
			if( !isRowEnd ){
				//�Ō�̂��̂͌���Ɠ����Ȃ̂Ŕ�r���Ȃ�.
				for( unsigned int j=0; j<vuiRow.size() - 1; j++ )
				{
					if( uiROW == vuiRow[j] ){
						isRowEnd = true;
						break;
					}
				}
				continue;
			}
			else{
				for( unsigned int j=0; j<vuiCol.size() - 1; j++ ){
					if( uiCOL == vuiCol[j] ){
						i = iEND_LOOP;
						break;
					}
				}
			}
		}
#else
		//�^�C���̖ڕW�������.
		SetTileNumTargetTop( uiROW, uiCOL );
		//�ڕW�̐��ɍ��킹�ă^�C���𑝌�����.
		SetTileNumTop( uiROW, uiCOL );
		//�^�C������ׂ�.
		SetTransformTop();
#endif
	}
	//����.
	{
		unsigned int uiROW_Z = m_vvSide[ enWD_SOUTH ].size();
		unsigned int uiCOL_Z = m_vvSide[ enWD_SOUTH ][0].size();
		unsigned int uiROW_X = m_vvSide[ enWD_EAST ].size();
		unsigned int uiCOL_X = m_vvSide[ enWD_EAST ][0].size();
		//�^�C���̖ڕW�������.
		SetTileNumTargetSide( uiROW_Z, uiCOL_Z, uiROW_X, uiCOL_X );
		//�ڕW�̐��ɍ��킹�ă^�C���𑝌�����.
		SetTileNumSide( uiROW_Z, uiCOL_Z, uiROW_X, uiCOL_X );
		//�^�C������ׂ�.
		SetTransformSide();
	}



}




void clsBUILDING::Render(
	const D3DXMATRIX &mView, 
	const D3DXMATRIX &mProj,
	const D3DXVECTOR3 &vLight, 
	const D3DXVECTOR3 &vEye )
{
#ifdef _DEBUG
	m_upBox->Render( mView, mProj, vLight, vEye );
#endif//#ifdef _DEBUG
	for( unsigned int Row=0; Row<m_vvTop.size(); Row++ )
	{
		for( unsigned int Col=0; Col<m_vvTop[ Row ].size(); Col++ ){
			m_upTop->SetPos( m_vvTop[ Row ][ Col ].vPos );
			m_upTop->SetRot( m_vvTop[ Row ][ Col ].vRot );
			m_upTop->SetScale( m_vvTop[ Row ][ Col ].vScale );
			m_upTop->Render( mView, mProj, vEye );
		}
	}

	for( int SideNum=0; SideNum<enWALL_DIRECTION_size; SideNum++  )
	{
		for( unsigned int Row=0; Row<m_vvSide[ SideNum ].size(); Row++ )
		{
			for( unsigned int Col=0; Col<m_vvSide[ SideNum ][ Row ].size(); Col++ ){
				m_upSide->SetPos( m_vvSide[ SideNum ][ Row ][ Col ].vPos );
				m_upSide->SetRot( m_vvSide[ SideNum ][ Row ][ Col ].vRot );
				m_upSide->SetScale( m_vvSide[ SideNum ][ Row ][ Col ].vScale );
				m_upSide->Render( mView, mProj, vEye );
			}
		}
	}

}





//�^�C���̖ڕW�������.
void clsBUILDING::SetTileNumTargetTop( unsigned int& puiRow, unsigned int& puiCol )
{
	//----- �������킹�� -----//.

	if( !m_vvTop.size() ){
		return;
	}
	for( unsigned int i=0; i<m_vvTop.size(); i++ ){
		if( !m_vvTop[i].size() ){
			return;
		}
	}

	m_vvTop[ 0 ][ 0 ].vScale.x = m_Trans.vScale.x / m_vvTop[ 0 ].size();
	m_vvTop[ 0 ][ 0 ].vScale.y = m_Trans.vScale.z / m_vvTop.size();
	D3DXVECTOR3 vScale = m_vvTop[0][0].vScale;

	if( vScale.y > vTILE_SIZE_MAX.y ){
		puiRow ++;	
	}
	else if( vScale.y < vTILE_SIZE_MIN.y ){
		if( puiRow > 1 ){
			puiRow --;
		}
	}

	if( vScale.x > vTILE_SIZE_MAX.x ){
		puiCol ++;	
	}
	else if( vScale.x < vTILE_SIZE_MIN.x ){
		if( puiCol > 1 ){
			puiCol --;
		}
	}

}

//�ڕW�̐��ɍ��킹�ă^�C���𑝌�����.
void clsBUILDING::SetTileNumTop( const unsigned int uiROW, const unsigned int uiCOL )
{
	//----- �� -----//.
	//�c.
	//����Ȃ����瑝�₷.
	if( m_vvTop.size() < uiROW ){
		vector< TRANSFORM > tmpInit;
		m_vvTop.push_back( tmpInit );//�s�𑝂₷.
		const unsigned int uiNEW_ROW_NUM = m_vvTop.size() - 1;
		m_vvTop[ uiNEW_ROW_NUM ].resize( m_vvTop[0].size() );//���₵���s�̗�̐������낦��.
		m_vvTop[ uiNEW_ROW_NUM ].reserve( iRESURVE_NUM );
	}
	//�������猸�炷.
	else if( m_vvTop.size() > uiROW ){
		const unsigned int uiDELETE_RAW_NUM = m_vvTop.size() - 1;
		m_vvTop.pop_back();//�s�����炷.
	}
	//��.
	//����Ȃ����瑝�₷.
	if( m_vvTop[0].size() < uiCOL ){
		TRANSFORM tmpInit;
		for( unsigned int Row=0; Row<m_vvTop.size(); Row++ ){
			m_vvTop[ Row ].push_back( tmpInit );
		}
	}
	//�������猸�炷.
	else if( m_vvTop[0].size() > uiCOL ){
		for( unsigned int Row=0; Row<m_vvTop.size(); Row++ ){
			m_vvTop[ Row ].pop_back();
		}
	}
}

//�^�C������ׂ�.
void clsBUILDING::SetTransformTop()
{
	const float fHALF = 0.5f;

	//----- �g�����X�t�H�[���𐮂��� -----//.
	//���.
	for( unsigned int Row=0; Row<m_vvTop.size(); Row++ )
	{
		for( unsigned int Col=0; Col<m_vvTop[ Row ].size(); Col++ ){
			//�傫�������낦��.
			m_vvTop[ Row ][ Col ].vScale.x = m_Trans.vScale.x / m_vvTop[ Row ].size();
			m_vvTop[ Row ][ Col ].vScale.y = m_Trans.vScale.z / m_vvTop.size();
			//���S��.
			m_vvTop[ Row ][ Col ].vPos = m_Trans.vPos;
			//����.	
			m_vvTop[ Row ][ Col ].vPos.x -= m_Trans.vScale.x * fHALF;				//�̐^�񒆂��[�ɗ���.
			m_vvTop[ Row ][ Col ].vPos.x += m_vvTop[ Row ][ Col ].vScale.x * fHALF;	//�̔����������炷.
			//���Ԃɓ\��.		
			m_vvTop[ Row ][ Col ].vPos.x += ( m_Trans.vScale.x / ( m_vvTop[ Row ].size() ) ) * Col;
			//����.	
			m_vvTop[ Row ][ Col ].vPos.z -= m_Trans.vScale.z * fHALF;
			m_vvTop[ Row ][ Col ].vPos.z += m_vvTop[ Row ][ Col ].vScale.y * fHALF;
			//���Ԃɓ\��.		
			m_vvTop[ Row ][ Col ].vPos.z += ( m_Trans.vScale.z / ( m_vvTop.size() ) ) * Row;
			//����.			   
			m_vvTop[ Row ][ Col ].vPos.y += m_Trans.vScale.y;
			m_vvTop[ Row ][ Col ].vRot = { 0.0f, 0.0f, 0.0f };
			m_vvTop[ Row ][ Col ].vRot.x = m_Trans.vRot.y;
			m_vvTop[ Row ][ Col ].vRot.x += static_cast<float>( M_PI_2 );
			m_vvTop[ Row ][ Col ].vRot.y -= static_cast<float>( M_PI_2 );
			m_vvTop[ Row ][ Col ].vRot.z -= static_cast<float>( M_PI_2 + M_PI );

			//�{�̂̉�]�ɉ����Ĉړ�.
			float fTheta, fDistance;
			GetTileTheta( m_vvTop[ Row ][ Col ], m_Trans, &fTheta, &fDistance );
			GetTilePosForRotation( &m_vvTop[ Row ][ Col ].vPos, m_Trans.vPos, fTheta, fDistance );
		}
	}
}


//�^�C���̖ڕW�������.//�����͎�����.
void clsBUILDING::SetTileNumTargetSide( 
	unsigned int& puiRowZ, unsigned int&  puiColZ,
	unsigned int& puiRowX, unsigned int&  puiColX )
{
	//----- �������킹�� -----//.

	for( int SideNum=0; SideNum<enWALL_DIRECTION_size; SideNum++  ){
		if( !m_vvSide[ SideNum ].size() ){
			return;
		}
		for( unsigned int i=0; i<m_vvSide[ SideNum ].size(); i++ ){
			if( !m_vvSide[ SideNum ][i].size() ){
				return;
			}
		}
	}

	//========== ��k ==========//.
	for( int SideNum=0; SideNum<enWALL_DIRECTION_size; SideNum+=iSIDE_TILE_COUNT_NUM  ){
		m_vvSide[ SideNum ][ 0 ][ 0 ].vScale.x = m_Trans.vScale.x / m_vvSide[ SideNum ][ 0 ].size();
		m_vvSide[ SideNum ][ 0 ][ 0 ].vScale.y = m_Trans.vScale.y / m_vvSide[ SideNum ].size();
		D3DXVECTOR3 vScale = m_vvSide[ SideNum ][0][0].vScale;

		if( vScale.y > vTILE_SIZE_MAX.y ){
			puiRowZ ++;
		}
		else if( vScale.y < vTILE_SIZE_MIN.y ){
			if( puiRowZ > 1 ){
				puiRowZ --;
			}
		}

		if( vScale.x > vTILE_SIZE_MAX.x ){
			puiColZ ++;
		}
		else if( vScale.x < vTILE_SIZE_MIN.x ){
			if( puiColZ > 1 ){
				puiColZ --;
			}
		}
	}
	//========== ���� ==========//.
	for( int SideNum=1; SideNum<enWALL_DIRECTION_size; SideNum+=iSIDE_TILE_COUNT_NUM  ){
		m_vvSide[ SideNum ][ 0 ][ 0 ].vScale.x = m_Trans.vScale.z / m_vvSide[ SideNum ][ 0 ].size();
		m_vvSide[ SideNum ][ 0 ][ 0 ].vScale.y = m_Trans.vScale.y / m_vvSide[ SideNum ].size();
		D3DXVECTOR3 vScale = m_vvSide[ SideNum ][0][0].vScale;

		if( vScale.y > vTILE_SIZE_MAX.y ){
			puiRowX ++;
		}
		else if( vScale.y < vTILE_SIZE_MIN.y ){
			if( puiRowX > 1 ){
				puiRowX --;
			}
		}

		if( vScale.x > vTILE_SIZE_MAX.x ){
			puiColX ++;
		}
		else if( vScale.x < vTILE_SIZE_MIN.x ){
			if( puiColX > 1 ){
				puiColX --;
			}
		}
	}
}

//�ڕW�̐��ɍ��킹�ă^�C���𑝌�����.//�����͎�����.
void clsBUILDING::SetTileNumSide( 
	const unsigned int uiROW_Z, const unsigned int uiCOL_Z,
	const unsigned int uiROW_X, const unsigned int uiCOL_X )
{
	//========== ��k ==========//.
	for( int SideNum=0; SideNum<enWALL_DIRECTION_size; SideNum+=iSIDE_TILE_COUNT_NUM  ){
		//----- �c -----//.
		//����Ȃ����瑝�₷.
		if( m_vvSide[ SideNum ].size() < uiROW_Z ){
			vector< TRANSFORM > tmpInit;
			m_vvSide[ SideNum ].push_back( tmpInit );
			const unsigned int uiNEW_ROW_NUM = m_vvSide[ SideNum ].size() - 1;
			m_vvSide[ SideNum ][ uiNEW_ROW_NUM ].resize( m_vvSide[ SideNum ][0].size() );
			m_vvSide[ SideNum ][ uiNEW_ROW_NUM ].reserve( iRESURVE_NUM );
		}
		//�������猸�炷.
		else if( m_vvSide[ SideNum ].size() > uiROW_Z ){
			const unsigned int uiDELETE_RAW_NUM = m_vvSide[ SideNum ].size() - 1;
			m_vvSide[ SideNum ].pop_back();
		}
		//----- �� -----//.
		//����Ȃ����瑝�₷.
		if( m_vvSide[ SideNum ][0].size() < uiCOL_Z ){
			TRANSFORM tmpInit;
			for( unsigned int Row=0; Row<m_vvSide[ SideNum ].size(); Row++ ){
				m_vvSide[ SideNum ][ Row ].push_back( tmpInit );
			}			
		}
		//�������猸�炷.
		else if( m_vvSide[ SideNum ][0].size() > uiCOL_Z ){
			for( unsigned int Row=0; Row<m_vvSide[ SideNum ].size(); Row++ ){
				m_vvSide[ SideNum ][ Row ].pop_back();
			}
		}
	}
	//========== ���� ==========//.
	for( int SideNum=1; SideNum<enWALL_DIRECTION_size; SideNum+=iSIDE_TILE_COUNT_NUM  ){
		//----- �c -----//.
		//����Ȃ����瑝�₷.
		if( m_vvSide[ SideNum ].size() < uiROW_X ){
			vector< TRANSFORM > tmpInit;
			m_vvSide[ SideNum ].push_back( tmpInit );
			const unsigned int uiNEW_ROW_NUM = m_vvSide[ SideNum ].size() - 1;
			m_vvSide[ SideNum ][ uiNEW_ROW_NUM ].resize( m_vvSide[ SideNum ][0].size() );
			m_vvSide[ SideNum ][ uiNEW_ROW_NUM ].reserve( iRESURVE_NUM );
		}
		//�������猸�炷.
		else if( m_vvSide[ SideNum ].size() > uiROW_X ){
			const unsigned int uiDELETE_RAW_NUM = m_vvSide[ SideNum ].size() - 1;
			m_vvSide[ SideNum ].pop_back();
		}
		//----- �� -----//.
		//����Ȃ����瑝�₷.
		if( m_vvSide[ SideNum ][0].size() < uiCOL_X ){
			TRANSFORM tmpInit;
			for( unsigned int Row=0; Row<m_vvSide[ SideNum ].size(); Row++ ){
				m_vvSide[ SideNum ][ Row ].push_back( tmpInit );
			}			
		}
		//�������猸�炷.
		else if( m_vvSide[ SideNum ][0].size() > uiCOL_X ){
			for( unsigned int Row=0; Row<m_vvSide[ SideNum ].size(); Row++ ){
				m_vvSide[ SideNum ][ Row ].pop_back();
			}
		}
	}

}

//�^�C������ׂ�.
void clsBUILDING::SetTransformSide()
{
	const float fHALF = 0.5f;

	//����.
	const D3DXVECTOR3 vOFFSET_SIDE[ enWALL_DIRECTION_size ] ={
		D3DXVECTOR3( 0.0f,						0.0f, -m_Trans.vScale.z * fHALF ),
		D3DXVECTOR3( -m_Trans.vScale.x * fHALF,	0.0f, 0.0f						),
		D3DXVECTOR3( 0.0f,						0.0f, +m_Trans.vScale.z * fHALF ),
		D3DXVECTOR3( +m_Trans.vScale.x * fHALF,	0.0f, 0.0f						),
	};

	//��k.
	for( int SideNum=0; SideNum<enWALL_DIRECTION_size; SideNum+=iSIDE_TILE_COUNT_NUM  )
	{
		for( unsigned int Row=0; Row<m_vvSide[ SideNum ].size(); Row++ )
		{
			for( unsigned int Col=0; Col<m_vvSide[ SideNum ][ Row ].size(); Col++ ){
				//�傫�������낦��.
				m_vvSide[ SideNum ][ Row ][ Col ].vScale.x	 = m_Trans.vScale.x / m_vvSide[ SideNum ][ Row ].size();
				m_vvSide[ SideNum ][ Row ][ Col ].vScale.y	 = m_Trans.vScale.y / m_vvSide[ SideNum ].size();
				//���S��.
				m_vvSide[ SideNum ][ Row ][ Col ].vPos		 = m_Trans.vPos;
				//�e�ʂɊ񂹂�.
				m_vvSide[ SideNum ][ Row ][ Col ].vPos		+= vOFFSET_SIDE[ SideNum ];
				//����.
				m_vvSide[ SideNum ][ Row ][ Col ].vPos.x	-= m_Trans.vScale.x * fHALF;
				m_vvSide[ SideNum ][ Row ][ Col ].vPos.x	+= m_vvSide[ SideNum ][ Row ][ Col ].vScale.x * fHALF;
				//���Ԃɓ\��.		
				m_vvSide[ SideNum ][ Row ][ Col ].vPos.x	+= ( m_Trans.vScale.x / ( m_vvSide[ SideNum ][ Row ].size() ) ) * Col;
				//����.	
				m_vvSide[ SideNum ][ Row ][ Col ].vPos.y	+= m_vvSide[ SideNum ][ Row ][ Col ].vScale.y * fHALF;
				//���Ԃɓ\��.		
				m_vvSide[ SideNum ][ Row ][ Col ].vPos.y	+= ( m_Trans.vScale.y / ( m_vvSide[ SideNum ].size() ) ) * Row;
				//����.
				m_vvSide[ SideNum ][ Row ][ Col ].vRot		 = m_Trans.vRot;
				m_vvSide[ SideNum ][ Row ][ Col ].vRot.y	+= static_cast<float>( M_PI_2 * SideNum + M_PI );
			
				//�{�̂̉�]�ɉ����Ĉړ�.
				float fTheta, fDistance;
				GetTileTheta( m_vvSide[ SideNum ][ Row ][ Col ], m_Trans, &fTheta, &fDistance );
				GetTilePosForRotation( &m_vvSide[ SideNum ][ Row ][ Col ].vPos, m_Trans.vPos, fTheta, fDistance );
			}
		}
	}
	//����.
	for( int SideNum=1; SideNum<enWALL_DIRECTION_size; SideNum+=iSIDE_TILE_COUNT_NUM  )
	{
		for( unsigned int Row=0; Row<m_vvSide[ SideNum ].size(); Row++ )
		{
			for( unsigned int Col=0; Col<m_vvSide[ SideNum ][ Row ].size(); Col++ )
			{
				//�傫�������낦��.
				m_vvSide[ SideNum ][ Row ][ Col ].vScale.x	 = m_Trans.vScale.z / m_vvSide[ SideNum ][ Row ].size();
				m_vvSide[ SideNum ][ Row ][ Col ].vScale.y	 = m_Trans.vScale.y / m_vvSide[ SideNum ].size();
				//���S��.
				m_vvSide[ SideNum ][ Row ][ Col ].vPos		 = m_Trans.vPos;
				//�e�ʂɊ񂹂�.
				m_vvSide[ SideNum ][ Row ][ Col ].vPos		+= vOFFSET_SIDE[ SideNum ];
				//����.
				m_vvSide[ SideNum ][ Row ][ Col ].vPos.z	-= m_Trans.vScale.z * fHALF;
				m_vvSide[ SideNum ][ Row ][ Col ].vPos.z	+= m_vvSide[ SideNum ][ Row ][ Col ].vScale.x * fHALF;
				//���Ԃɓ\��.		
				m_vvSide[ SideNum ][ Row ][ Col ].vPos.z	+= ( m_Trans.vScale.z / ( m_vvSide[ SideNum ][ Row ].size() ) ) * Col;
				//����.	
				m_vvSide[ SideNum ][ Row ][ Col ].vPos.y	+= m_vvSide[ SideNum ][ Row ][ Col ].vScale.y * fHALF;
				//���Ԃɓ\��.		
				m_vvSide[ SideNum ][ Row ][ Col ].vPos.y	+= ( m_Trans.vScale.y / ( m_vvSide[ SideNum ].size() ) ) * Row;
				//����.
				m_vvSide[ SideNum ][ Row ][ Col ].vRot		 = m_Trans.vRot;
				m_vvSide[ SideNum ][ Row ][ Col ].vRot.y	+= static_cast<float>( M_PI_2 * SideNum + M_PI );
			
				//�{�̂̉�]�ɉ����Ĉړ�.
				float fTheta, fDistance;
				GetTileTheta( m_vvSide[ SideNum ][ Row ][ Col ], m_Trans, &fTheta, &fDistance );
				GetTilePosForRotation( &m_vvSide[ SideNum ][ Row ][ Col ].vPos, m_Trans.vPos, fTheta, fDistance );
			}
		}
	}
}



//�����ɓ��ꂽ�^�C�������S���猩�ĉ��x�̈ʒu�ɂ��邩.
float clsBUILDING::GetTileTheta( 
	const TRANSFORM& Tile, const TRANSFORM& Center,
	float* const pfTheta, float* const pfDistance ) const
{
	float fReturn = 0;
	if( !pfTheta ){
		return fReturn;
	}
	if( !pfDistance ){
		return fReturn;
	}

	float fX = Center.vPos.x - Tile.vPos.x; 
	float fY = Center.vPos.z - Tile.vPos.z;

	fReturn = atan2f( fY, fX );

	*pfDistance = sqrtf( fY * fY + fX * fX );
	*pfTheta = fReturn;

	return fReturn;
}

//��]�ɉ����č��W���X�V����.
D3DXVECTOR3 clsBUILDING::GetTilePosForRotation( 
	D3DXVECTOR3* const vTilePos, const D3DXVECTOR3& vCenterPos,
	const float fTileTheta, const float fTileDistance )
{
	D3DXVECTOR3 vReturn = { 0.0f, 0.0f, 0.0f };
	if( !vTilePos ){
		return vReturn;
	}

	vTilePos->x = vCenterPos.x + cosf( fTileTheta - m_Trans.vRot.y ) * fTileDistance;
	vTilePos->z = vCenterPos.z + sinf( fTileTheta - m_Trans.vRot.y ) * fTileDistance;

	vReturn = *vTilePos;

	return vReturn;
}



clsDX9Mesh* clsBUILDING::GetModelPtr()
{
	clsDX9Mesh* pReturn = m_upBox->GetModelPtr();

	return pReturn;
}



D3DXVECTOR3 clsBUILDING::GetPos()
{
	return m_Trans.vPos;
}

void clsBUILDING::SetPos( const D3DXVECTOR3& vPos )
{
	m_Trans.vPos = vPos;
}

void clsBUILDING::AddPos( const D3DXVECTOR3& vPos )
{
	m_Trans.vPos += vPos;
}


D3DXVECTOR3 clsBUILDING::GetRot()
{
	return m_Trans.vRot;
}

void clsBUILDING::SetRot( const D3DXVECTOR3& vRot )
{
	m_Trans.vRot = vRot;
}

void clsBUILDING::AddRot( const D3DXVECTOR3& vRot )
{
	m_Trans.vRot += vRot;
}


D3DXVECTOR3 clsBUILDING::GetScale()
{
	return m_Trans.vScale;
}

void clsBUILDING::SetScale( const D3DXVECTOR3& vScale )
{
	m_Trans.vScale = vScale;
}

void clsBUILDING::AddScale( const D3DXVECTOR3& vScale )
{
	m_Trans.vScale += vScale;
}

