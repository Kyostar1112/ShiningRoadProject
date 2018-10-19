#ifndef MENU_WINDOW_BASE_H_
#define MENU_WINDOW_BASE_H_

class clsPOINTER_GROUP;
class clsUiText;
class clsFont;
class clsXInput;
class clsDxInput;
class clsSOUND_MANAGER_BASE;

#include "WindowBox.h"


//�����j���[�̊��N���X.
class clsMENU_WINDOW_BASE : public clsWINDOW_BOX
{
public:

	clsMENU_WINDOW_BASE(		
		clsPOINTER_GROUP* const pPtrGroup,
		clsMENU_WINDOW_BASE* const pParentWindow,
		unsigned int* const pInformationArray );
	virtual ~clsMENU_WINDOW_BASE();

	//���̃��j���[�E�B���h�E��delete�͂���if���̒��Ŏg���܂��傤.
	bool isDeletePermission();

protected:
	//�p����̃R���X�g���N�^�Ŏg��.
	void Open( const D3DXVECTOR2& vSize );
public:


	void Update() final;

	void Render() final;

	//���̃E�B���h�E����Đe�E�B���h�E�ɑ����Ԃ�.
	void Close();

	//�I��悵�����ʂ�Ԃ�.
	unsigned int GetInformation(){
		if( m_pNextWindow ){
			m_pNextWindow->GetInformation();
		}
		return m_uiInformation;
	}


protected:

	//���̑���f���o��( ���������Ȃ�true ).
	bool CreateNextWindow( clsMENU_WINDOW_BASE** ppOutNextWindow );

	//���̃E�B���h�E�𑀍삷��悤�ɂȂ�Ȃ�true,�����Ȃ�false.
	void Operation( const bool isOperation );


	//����.
	bool SelectUp();
	bool SelectDown();
	bool SelectRight();
	bool SelectLeft();
	bool SelectEnter();
	bool SelectExit();

	//�I����.
	int m_iSelectNum;
	//���j���[���J�������̂ɕԂ��l.
	unsigned int m_uiInformation;
	//�V�[�����������Ă���, ���̉�������\�����̐��l�̔z��.
	unsigned int* m_puiInformationDataArray;

private:
	virtual void UpdateProduct() = 0;
	virtual void RenderProduct() = 0;
	virtual bool CreateNextWindowProduct( 
		clsMENU_WINDOW_BASE** ppOutNextWindow, 
		clsMENU_WINDOW_BASE* const pParentWindow ) = 0;

	void SetColor( const D3DXVECTOR3& vColor ) final;

	//�J�[�\���ړ��ɕK�v.
	struct HOLD_STATE
	{
		int iHoldFream;
		int iFirstPush;//�ŏ��̈��.
		HOLD_STATE()
		:iHoldFream( 0 )
		,iFirstPush( 0 )
		{}
	};
	HOLD_STATE m_HoldRight;
	HOLD_STATE m_HoldLeft;
	HOLD_STATE m_HoldUp;
	HOLD_STATE m_HoldDown;




	//�I���J�[�\��.
	std::unique_ptr< clsSprite2D > m_upCursor;

	//���̑����J������.
	clsMENU_WINDOW_BASE* m_pParentWindow;
	//���ɊJ����.
	clsMENU_WINDOW_BASE* m_pNextWindow;


	//true�Ȃ炱�̑��𓮂�����.
	bool m_isOperation;




	//�\��.
	clsFont* m_wpFont;
	std::vector< std::unique_ptr< clsUiText > > m_vecupUiText;

	//����.
	clsXInput*	m_wpXInput;
	clsDxInput* m_wpDInput;

	clsSOUND_MANAGER_BASE* m_wpSound;
};

#endif//#ifndef MENU_WINDOW_BASE_H_