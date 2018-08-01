#pragma once

//#include "Global.h"

#include "Sprite2DCenter.h"
#include "UiText.h"
#include "WindowBox.h"
#include "File.h"
#include <vector>


class clsASSEMBLE_UI
{
public:
	clsASSEMBLE_UI();
	~clsASSEMBLE_UI();

	//�e�p�[�cUI���󂯎��p.
	using PARTS_NUM_DATA = std::vector< int >; 

	//�p�[�c�I�𒆂�����ȊO��.
	enum class enSELECT_MODE : UCHAR
	{
		PARTS = 0,
		MISSION_START
	}m_enSelectMode;

	void Create( 
		ID3D11Device* const pDevice, 
		ID3D11DeviceContext* const pContext,
		PARTS_NUM_DATA data );//�e�p�[�cUI�̐��m��p.

	void Input();

	//�������̓f�[�^����A�X�e�[�^�X�ȊO�̃f�[�^�̐��B��O�����̓p�[�c���̔ԍ�.
	void Update( 
		enSELECT_MODE enSelect,
		std::shared_ptr< clsFILE > const spFile = nullptr,
		const int iPartsType = 0,	//�p�[�c���.
		const int iPartsNum = 0,	//�p�[�c�ԍ�.
		const int iStatusCutNum = 0 );//�X�e�[�^�X����Ȃ��f�[�^�̐�.	

	void Render( 
		enSELECT_MODE enSelect, 
		const int iPartsType, 
		const int iPartsNum );//�I�𒆃p�[�c�ԍ�.


#if _DEBUG
	//�f�o�b�O�e�L�X�g�p.
	D3DXVECTOR3 GetUiPos();
#endif//#if _DEBUG

private:

	//�p�[�c���ڐ�.
	enum enPARTS_TYPE : int
	{
		LEG = 0,
		CORE,
		HEAD,
		ARMS,
		WEAPON_L,
		WEAPON_R,
	
		enPARTS_TYPE_SIZE
	};

	//�p�[�c�\���p�̃E�B���h�E.
	D3D11_VIEWPORT m_ViewPortPartsWindow;

	std::vector< std::unique_ptr< clsSprite2D > >	m_vupPartsType;		//�p�[�c�J�e�S��.
	std::unique_ptr< clsSprite2D >					m_upPartsTypeSelect;//�I��( ������ ).

	std::vector< std::unique_ptr< clsSprite2D > >	m_vupPartsIcon[ enPARTS_TYPE_SIZE ];	//�e�p�[�c��UI.
	std::unique_ptr< clsSprite2D >					m_upPartsNumSelect;	//�I��( ������ ).

	std::unique_ptr< clsSprite2D >					m_upStatusWindow;	//�X�e�[�^�X���\�������.

	std::unique_ptr< clsSprite2D >					m_upPartsWindow;	//�p�[�c�̒P�̃��f���\�������.

	std::unique_ptr< clsSprite2D >					m_upMissionStart;	//�o���{�^��.

	std::unique_ptr< clsSprite2D > m_upHeader;//��ʏ㕔�̑�.

	std::vector< std::unique_ptr< clsSPRITE2D_CENTER > > m_pArrow;//���.

	std::unique_ptr< clsUiText > m_upHeaderText;//�w�b�_�[����.
	std::unique_ptr< clsUiText > m_upFooterText;//�t�b�^�[����.

	std::vector< std::unique_ptr< clsUiText > > m_vupStatusText;	//�X�e�[�^�X����( ���ږ� ).
	std::vector< std::unique_ptr< clsUiText > > m_vupStatusNumText;	//�X�e�[�^�X�l.


	std::unique_ptr< clsUiText > m_upPartsNameText;//�p�[�c��.

	//�u���̕���͉E�r?����Ƃ����r?�v.
	std::unique_ptr< clsWINDOW_BOX > m_upWndBox;//���E�ǂ����������Ă��锠.


	//�X�e�[�^�X�̐�( �s�� ).
	int m_iStatusNum;
	//�X�e�[�^�X�̖��O���i�[���Ă���.
	std::vector< std::string > m_vsStatusNameBox[enPARTS_TYPE_SIZE];

#if _DEBUG
	std::unique_ptr< clsSprite2D > m_upDegine;
#endif//#if _DEBUG
};
