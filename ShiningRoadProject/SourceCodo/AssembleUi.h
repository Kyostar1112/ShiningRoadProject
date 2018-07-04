#pragma once

//#include "Global.h"

#include "Sprite2DCenter.h"
#include <vector>

class clsASSEMBLE_UI
{
public:
	clsASSEMBLE_UI();
	~clsASSEMBLE_UI();

	void Create( 
		ID3D11Device* const pDevice, 
		ID3D11DeviceContext* const pContext );
	void Input();
	void Update();
	void Render();

#if _DEBUG
	//デバッグテキスト用.
	D3DXVECTOR3 GetUiPos();
#endif//#if _DEBUG

private:

	enum enPARTS_TYPE
	{
		LEG = 0,
		CORE,
		HEAD,
		ARMS,
		WEAPON,
	
		enPARTS_TYPE_SIZE
	};

	std::vector< std::unique_ptr< clsSprite2D > >	m_vupPartsType;		//パーツカテゴリ.
	std::unique_ptr< clsSprite2D >					m_upPartsTypeSelect;	//選択中( 半透明 ).
	std::vector<clsSprite2D*>	m_vpPartsNum;		//.
	std::unique_ptr< clsSprite2D >					m_upPartsNumSelect;	//.
	std::unique_ptr< clsSprite2D >					m_upStatusWindow;	//ステータスが表示される.
	std::unique_ptr< clsSprite2D >					m_upPartsWindow;	//パーツの単体モデル表示される.

	std::vector< std::unique_ptr< clsSPRITE2D_CENTER > > m_pArrow;//矢印.

#if _DEBUG
	std::unique_ptr< clsSprite2D > m_upDegine;
#endif//#if _DEBUG
};
