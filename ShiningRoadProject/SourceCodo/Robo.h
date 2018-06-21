#pragma once

#include"Charactor.h"
#include"SkinMesh.h"

//�����̏�����������.
#ifdef Tahara
#include "PtrGroup.h"

//2018/05/16( �� ).
	//�֐��uRoboInit�v�ɁuclsPOINTER_GROUP�v�^�̈�����ǉ����A.
	//�ǉ����������o�ϐ�( m_wpResource�Am_wpEffects�Am_wpSound ).
	//�ɃA�h���X�����蓖�Ă鏈����ǉ����܂���.
	
	//�����q�̓s���ケ�̃N���X�́uRender�v�֐���.
	//�uclsSkinMesh�v�N���X�́uModelRender�v�֐���.
	//�uclsD3DXSKINMESH�v�N���X�́uRender�v�֐���.
	//������const��t���܂���.
	
	//Zeromemory�̓|�C���^����\�ꂷ��̂ŏ����������s���܂���.
	//���uclsCharactor�v�ƁuclsObject�v�uclsSkinMesh�v��.

#endif//#ifdef Tahara

const int g_iQuickInterbal = 1 * (int)g_fFPS;
const int g_iQuickTurnFrame = 1 * (int)g_fFPS;

class clsRobo : public clsCharactor
{
public:
	/*clsSkinMesh * m_pHead;
	clsSkinMesh * m_pCore;
	clsSkinMesh * m_pLeftArm;
	clsSkinMesh * m_pRightArm;
	clsSkinMesh * m_pLeg;*/
	clsSkinMesh* m_pMesh;

	void RoboInit(HWND hWnd,
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11,
		clsPOINTER_GROUP* const pPtrGroup );

	void ModelUpdate()
	{
		m_pMesh->ModelUpdate(m_Trans);
	}

	void Render( 
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye,
		const D3DXVECTOR4 &vColor = { 1.0f, 1.0f, 1.0f ,1.0f },
		const bool alphaFlg = false )
	{
		ModelUpdate();
		m_pMesh->ModelRender(mView, mProj, vLight, vEye, vColor, alphaFlg );
	}

	virtual void tenshi()override{};

	bool m_bBoost;//true:�u�[�X�^�[�W�J/false:��W�J.

	//Head�p�[�c���琔�l���擾����ϐ��Ɗ֘A����ϐ�//

	//Core�p�[�c���琔�l���擾����ϐ��Ɗ֘A����ϐ�//
	int m_iEnelgyMax;//�G�l���M�[�ő�e��.
	int m_iEnelgy;//���݃G�l���M�[�c��.
	int m_iEnelgyOutput;//�G�l���M�[�o��(�񕜗�)

	float m_fBoostMoveSpeedMax;

	float m_fQuickMoveSpeedMax;//
	int m_iQuickEnelgyCost;
	int m_iQuickTopSpeedTime;//�ō�����ۂt���[���l.

	int m_iQuickDecStartTime;//�c�N�C�b�N���ˎ���.

	int m_iQuickInterbal;//�N�C�b�N�u�[�X�g�̍ĕ��˂܂ł̃t���[��.

	float m_fBoostRisingSpeedMax;//�u�[�X�^�[�����ړ��̍ō���.
	int m_iBoostRisingTopSpeedFrame;//���ɒB����܂ł̃t���[���l.
	float m_fBoostRisingAccele;// = m_fMoveSpeedMax / m_fTopSpeedFrame;
	float m_fBoostFollRes;//�u�[�X�^�[�W�J���ɗ����鑬�x.

	//Arm�p�[�c���琔�l���擾����ϐ��Ɗ֘A����ϐ�//

	//Leg�p�[�c���琔�l���擾����ϐ��Ɗ֘A����ϐ�//
	float m_fWalktMoveSpeedMax;//Leg�p�[�c����擾������s���x.
	int m_iWalkTopSpeedFrame;//���萫�\����v�Z.
	
	int m_iBoostTopSpeedFrame;//���萫�\����v�Z.

	void Walk();
	void Boost();
	void MoveSwitch();
	void BoostRising();
	void QuickBoost();
	void SetDirQuickBoost(const float fAngle);
	void QuickTurn();
	void SetDirQuickTurn(const float fAngle);

	void Updata();

	clsRobo();
	~clsRobo();

private:


//�����̏�����������.
#ifdef Tahara
	//�����Ƃ�delete���Ȃ���null���Ă�.
	clsResource*		m_wpResource;
	clsEffects*			m_wpEffects;
	clsSOUND_MANAGER*	m_wpSound;
#endif//#ifdef Tahara


};


