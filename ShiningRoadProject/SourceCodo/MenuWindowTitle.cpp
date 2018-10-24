#include "MenuWindowTitle.h"
#include "PtrGroup.h"
//#include "UiText.h"



namespace{
	//渡す情報の添え字.
	const char INFORMATION__INDEX_GAME_END		= 0;
	const char INFORMATION__INDEX_NEXT_SCENE	= 1;
	const char INFORMATION__INDEX_CLOSE_MENU	= 2;
}

clsMENU_WINDOW_TITLE::clsMENU_WINDOW_TITLE(		
	clsPOINTER_GROUP* const pPtrGroup,
	clsMENU_WINDOW_BASE* pParentWindow,
		unsigned int* const pInformationArray )
		:clsMENU_WINDOW_BASE( pPtrGroup, pParentWindow, pInformationArray )
{
	assert( m_wpSound );
	m_wpSound->PlaySE( enSE_WIN_APP );

		//この窓のサイズ.
	const D3DXVECTOR2 vTHIS_WINDOW_SIZE = { 200.0f, 150.0f };
	Open( vTHIS_WINDOW_SIZE );
}

clsMENU_WINDOW_TITLE::~clsMENU_WINDOW_TITLE()
{
}





void clsMENU_WINDOW_TITLE::UpdateProduct()
{
	const int iSELECT_NUM_MAX = 1;//選択肢の最大は何?.

	if( SelectUp() ){
		m_iSelectNum --;
		if( m_iSelectNum < 0 ){
			m_iSelectNum = 0;
		}
		else{
			m_wpSound->PlaySE( enSE_CURSOL_MOVE );
		}
	}

	if( SelectDown() ){
		m_iSelectNum ++;
		if( m_iSelectNum > iSELECT_NUM_MAX ){
			m_iSelectNum = iSELECT_NUM_MAX;
		}
		else{
			m_wpSound->PlaySE( enSE_CURSOL_MOVE );
		}
	}

	if( SelectEnter() ){
		if( m_iSelectNum ){
			m_wpSound->PlaySE( enSE_EXIT );
			m_uiInformation = m_puiInformationDataArray[ INFORMATION__INDEX_GAME_END ];
		}
		else{
			m_wpSound->PlaySE( enSE_ENTER );
			m_uiInformation = m_puiInformationDataArray[ INFORMATION__INDEX_NEXT_SCENE ];
		}
	}

	if( SelectExit() ){
		m_wpSound->PlaySE( enSE_WIN_DIS_APP );
		m_uiInformation = m_puiInformationDataArray[ INFORMATION__INDEX_CLOSE_MENU ];
	}


}

void clsMENU_WINDOW_TITLE::RenderProduct()
{
	//始める.
	const D3DXVECTOR2 vPOS_START_LOCAL = { 45.0f, 30.0f };
	const D3DXVECTOR3 vPOS_START = SetPosFromWindow( vPOS_START_LOCAL );
	const float fSCALE = 24;
	int iTextRow = 1;
	m_wpFont->SetPos( vPOS_START );
	m_wpFont->SetScale( fSCALE );
	m_wpFont->Render( iTextRow ++ );

	//終わる.
	const D3DXVECTOR2 vPOS_EXIT_LOCAL = { 45.0f, 80.0f };
	const D3DXVECTOR3 vPOS_EXIT = SetPosFromWindow( vPOS_EXIT_LOCAL );
	m_wpFont->SetPos( vPOS_EXIT );
	m_wpFont->Render( iTextRow ++ );

	///カーソル移動.
	if( m_iSelectNum == 0 ){
		const D3DXVECTOR3 vCURSOR_SCALE = { 24.0f*5.0f, 32.0f, 0.0f };
		m_upCursor->SetScale( vCURSOR_SCALE );
		m_upCursor->SetPos( vPOS_START );
	}
	else if( m_iSelectNum == 1 ){
		const D3DXVECTOR3 vCURSOR_SCALE = { 24.0f*4.0f, 32.0f, 0.0f };
		m_upCursor->SetScale( vCURSOR_SCALE );
		m_upCursor->SetPos( vPOS_EXIT );
	}


}

bool clsMENU_WINDOW_TITLE::CreateNextWindowProduct( 
	clsMENU_WINDOW_BASE** ppOutNextWindow, 
	clsMENU_WINDOW_BASE* const pParentWindow )
{

	return false;
}




