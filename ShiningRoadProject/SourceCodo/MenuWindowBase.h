#ifndef MENU_WINDOW_BASE_H_
#define MENU_WINDOW_BASE_H_

class clsPOINTER_GROUP;
class clsUiText;
class clsFont;

#include "WindowBox.h"


//�����j���[�̊��N���X.
class clsMENU_WINDOW_BASE : public clsWINDOW_BOX
{
public:

	clsMENU_WINDOW_BASE(		
		clsPOINTER_GROUP* const pPtrGroup,
		clsMENU_WINDOW_BASE* const pParentWindow,
		const D3DXVECTOR2& vSize );

	~clsMENU_WINDOW_BASE();

	void Update() final;

	void Render() final;

	//����.
	virtual bool SelectUp() = 0;
	virtual bool SelectDown() = 0;
	virtual bool SelectRight() = 0;
	virtual bool SelectLeft() = 0;
	virtual bool SelectEnter() = 0;
	virtual bool SelectExit() = 0;



protected:

	//���̑���f���o��( ���������Ȃ�true ).
	bool CreateNextWindow( clsMENU_WINDOW_BASE** ppOutNextWindow );

	//���̃E�B���h�E�𑀍삷��悤�ɂȂ�Ȃ�true,�����Ȃ�false.
	void Operation( const bool isOperation );

	//���̃E�B���h�E����Đe�E�B���h�E�ɑ����Ԃ�.
	void Close();

private:
	virtual void UpdateProduct() = 0;
	virtual void RenderProduct() = 0;
	virtual bool CreateNextWindowProduct( 
		clsMENU_WINDOW_BASE** ppOutNextWindow, 
		clsMENU_WINDOW_BASE* const pParentWindow ) = 0;



	void SetColor( const D3DXVECTOR3& vColor ) final;

	//�I���J�[�\��.
	std::unique_ptr< clsSprite2D > m_upCursor;

	//���̑����J������.
	clsMENU_WINDOW_BASE* m_pParentWindow;
	//���ɊJ����.
	clsMENU_WINDOW_BASE* m_pNextWindow;


	//true�Ȃ炱�̑��𓮂�����.
	bool m_isOperation;

	//�I����.
	int m_iSelectNum;


	//�\��.
	clsFont* m_wpFont;
	std::vector< std::unique_ptr< clsUiText > > m_vecupUiText;

};

#endif//#ifndef MENU_WINDOW_BASE_H_