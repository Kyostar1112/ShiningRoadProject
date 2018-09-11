#pragma once

#include "LineBox.h"
#include "UiText.h"


class clsWINDOW_BOX : public clsLINE_BOX
{
public:
	clsWINDOW_BOX(		
		ID3D11Device* const pDevice11,
		ID3D11DeviceContext* const pContext11 );

	~clsWINDOW_BOX();

	//----- �����p -----//.
	//( �E�B���h�E�̍��ォ��� )���W.
	void SetTextPos( const D3DXVECTOR2 &vPos );
	void SetTextScale( const float fScale );
	void SetText( const char* sText );
	void SetTextColor( const D3DXVECTOR4 &vColor = { 1.0f, 1.0f, 1.0f, 1.0f } );

private:

	void UpdateProduct() override;

	void RenderProduct() override;

	std::unique_ptr< clsSPRITE2D_CENTER >	m_upBack;//�w�i�摜.

	std::unique_ptr< clsUiText >			m_upText;//�����\���p.
	D3DXVECTOR2								m_vTextOffset;//�e�L�X�g�̑�����̂���.

};

