#pragma once

//#include "Global.h"

#include "Sprite2DCenter.h"
#include "UiText.h"
#include "File.h"
#include <vector>

class clsASSEMBLE_UI
{
public:
	clsASSEMBLE_UI();
	~clsASSEMBLE_UI();

	//�e�p�[�cUI���󂯎��p.
	using PARTS_NUM_DATA = std::vector< int >; 

	void Create( 
		ID3D11Device* const pDevice, 
		ID3D11DeviceContext* const pContext,
		PARTS_NUM_DATA data );//�e�p�[�cUI�̐��m��p.

	void Input();

	//�������̓f�[�^����A�X�e�[�^�X�ȊO�̃f�[�^�̐��B��O�����̓p�[�c���̔ԍ�.
	void Update( 
		std::shared_ptr< clsFILE > const spFile,
		const int iPartsType,	//�p�[�c���.
		const int iPartsNum,	//�p�[�c�ԍ�.
		const int iStatusCutNum );//�X�e�[�^�X����Ȃ��f�[�^�̐�.	

	void Render( const int iPartsType, const int iPartsNum );//�I�𒆃p�[�c�ԍ�.

#if _DEBUG
	//�f�o�b�O�e�L�X�g�p.
	D3DXVECTOR3 GetUiPos();
#endif//#if _DEBUG

private:

	enum enPARTS_TYPE : int
	{
		LEG = 0,
		CORE,
		HEAD,
		ARMS,
		WEAPON,
	
		enPARTS_TYPE_SIZE
	};

	std::vector< std::unique_ptr< clsSprite2D > >	m_vupPartsType;		//�p�[�c�J�e�S��.
	std::unique_ptr< clsSprite2D >					m_upPartsTypeSelect;//�I��( ������ ).
	std::vector< std::unique_ptr< clsSprite2D > >	m_vupPartsIcon[ enPARTS_TYPE_SIZE ];	//�e�p�[�c��UI.
	std::unique_ptr< clsSprite2D >					m_upPartsNumSelect;	//�I��( ������ ).
	std::unique_ptr< clsSprite2D >					m_upStatusWindow;	//�X�e�[�^�X���\�������.
	std::unique_ptr< clsSprite2D >					m_upPartsWindow;	//�p�[�c�̒P�̃��f���\�������.

	std::unique_ptr< clsSprite2D > m_upHeader;//��ʏ㕔�̑�.
	std::unique_ptr< clsSprite2D > m_upFooter;//��ʉ����̑�.

	std::vector< std::unique_ptr< clsSPRITE2D_CENTER > > m_pArrow;//���.

	std::unique_ptr< clsUiText > m_upHeaderText;//�w�b�_�[����.
	std::unique_ptr< clsUiText > m_upFooterText;//�t�b�^�[����.

	std::unique_ptr< clsUiText >				m_upStatusTitleText;//�X�e�[�^�X�̃^�C�g��.
	std::vector< std::unique_ptr< clsUiText > > m_vupStatusText;	//�X�e�[�^�X����( ���ږ� ).
	std::vector< std::unique_ptr< clsUiText > > m_vupStatusNumText;	//�X�e�[�^�X�l.


	std::unique_ptr< clsUiText > m_upPartsNameText;//�p�[�c��.


	//�X�e�[�^�X�̐�( �s�� ).
	int m_iStatusNum;
	//�X�e�[�^�X�̖��O���i�[���Ă���.
	std::vector< std::string > m_vsStatusNameBox[enPARTS_TYPE_SIZE];

#if _DEBUG
	std::unique_ptr< clsSprite2D > m_upDegine;
#endif//#if _DEBUG
};
