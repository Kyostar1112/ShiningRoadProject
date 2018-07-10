#pragma once

//#include "Global.h"

#include "Sprite2DCenter.h"
#include "UiText.h"
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
	//�f�o�b�O�e�L�X�g�p.
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

	std::vector< std::unique_ptr< clsSprite2D > >	m_vupPartsType;		//�p�[�c�J�e�S��.
	std::unique_ptr< clsSprite2D >					m_upPartsTypeSelect;	//�I��( ������ ).
	std::vector<clsSprite2D*>	m_vpPartsNum;		//.
	std::unique_ptr< clsSprite2D >					m_upPartsNumSelect;	//.
	std::unique_ptr< clsSprite2D >					m_upStatusWindow;	//�X�e�[�^�X���\�������.
	std::unique_ptr< clsSprite2D >					m_upPartsWindow;	//�p�[�c�̒P�̃��f���\�������.

	std::vector< std::unique_ptr< clsSPRITE2D_CENTER > > m_pArrow;//���.

	std::unique_ptr< clsUiText > m_upText;//����.

#if _DEBUG
	std::unique_ptr< clsSprite2D > m_upDegine;
#endif//#if _DEBUG
};
