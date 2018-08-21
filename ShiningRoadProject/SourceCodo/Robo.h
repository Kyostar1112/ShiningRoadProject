#pragma once

#include"Charactor.h"
#include"SkinMesh.h"

//�����̏�����������.
#ifdef Tahara
#include "PtrGroup.h"
#include "MissionModel.h"

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
	enum enWeaponType
	{
		enWeaponLHand,
		enWeaponRHand,

		enWeaponTypeSize
	};

	clsMISSION_MODEL* m_pMesh;

	void RoboInit(clsPOINTER_GROUP* const pPtrGroup, clsROBO_STATUS* const pRobo);

	void ModelUpdate()
	{
		D3DXVECTOR3 vTmp;

		vTmp = GetPosition();
		m_pMesh->SetPos(vTmp);

		vTmp = GetRotation();
		vTmp.y += D3DX_PI;

		ObjRollOverGuard(&vTmp.y);

		m_pMesh->SetRot(vTmp);

		m_pMesh->SetScale(m_Trans.vScale.x);

		m_pMesh->UpDate();
		//UpdateCollsion();
	}

	void Render( 
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye,
		const D3DXVECTOR4& vColor = { 1.0f, 1.0f, 1.0f ,1.0f },
		const bool isAlpha = false )
	{
		ModelUpdate();
		m_pMesh->Render(mView, mProj, vLight, vEye);
	}

	void UpdateCollsion();

	bool m_bBoost;//true:�u�[�X�^�[�W�J/false:��W�J.

	//Head�p�[�c���琔�l���擾����ϐ��Ɗ֘A����ϐ�//

	//Core�p�[�c���琔�l���擾����ϐ��Ɗ֘A����ϐ�//
	int m_iEnelgyMax;//�G�l���M�[�ő�e��.
	int m_iEnelgy;//���݃G�l���M�[�c��.
	int m_iEnelgyOutput;//�G�l���M�[�o��(�񕜗�)
	int m_iEnelgyRecoveryPoint;//���݂̃G�l���M�[�񕜗�.
	int m_iBoostFloatRecovery;//�󒆂Ńu�[�X�g�W�J���̃G�l���M�[�g�p��.

	void EnelgyRecovery();
	void SetEnelgyRecoveryAmount();
	bool EnelgyConsumption(const int iConsumption);//�G�l���M�[����͂�������.

	float m_fBoostMoveSpeedMax;
	int m_iBoostMoveCost;

	float m_fQuickBoostSpeedMax;
	int m_iQuickBoostEnelgyCost;
	int m_iQuickBoostTopSpeedTime;//�ō�����ۂt���[���l.
	int m_iQuickBoostDecStartTime;//�c�N�C�b�N���ˎ���.

	float m_fQuickTrunSpeedMax;
	int m_iQuickTrunEnelgyCost;
	int m_iQuickTrunTopSpeedTime;//�ō�����ۂt���[���l.
	int m_iQuickTrunDecStartTime;//�c�N�C�b�N���ˎ���.

	int m_iQuickInterbal;//�N�C�b�N�u�[�X�g�̍ĕ��˂܂ł̃t���[��.

	float m_fBoostRisingSpeedMax;//�u�[�X�^�[�����ړ��̍ō���.
	int m_iBoostRisingTopSpeedFrame;//���ɒB����܂ł̃t���[���l.
	float m_fBoostRisingAccele;// = m_fMoveSpeedMax / m_fTopSpeedFrame;
	int m_iBoostRisingyCost;
	float m_fBoostFollRes;//�u�[�X�^�[�W�J���ɗ����鑬�x.

	int m_iActivityLimitTime;//�������E����.
	bool m_bTimeUp;

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

	void ShotLWeapon();
	void ShotRWeapon();

	void Updata();
	void UpdataQuick();
	void UpdataLimitTime();
	void UpdataBoost();

	void UpdatePosfromBone();

	clsRobo();
	~clsRobo();

private:


//�����̏�����������.
#ifdef Tahara
	//�����Ƃ�delete���Ȃ���null���Ă�.
	clsResource*		m_wpResource;
	clsEffects*			m_wpEffects;
	clsSOUND_MANAGER_BASE*	m_wpSound;

	//�����蔻��̃|�C���^.
	std::shared_ptr< std::vector< D3DXVECTOR3 > > m_spColPoss;

	//���{���f��.
	std::unique_ptr< clsMISSION_MODEL > m_upMissModel;

#endif//#ifdef Tahara


};


