#include"Robo.h"
#include "OperationString.h"

//�W���C���g�{�[���̐����̌���.
const char g_cBONE_NAME_NUM_DIGIT_JOINT = 2;

const int g_iQuickInterbal = (int)g_fFPS;
const int g_iQuickTurnFrame = (int)g_fFPS;

const int g_iWalkTopSpeedFrame = (int)g_fFPS / 10;
const int g_iRotTopSpeedFrame = (int)g_fFPS / 2;
const int g_iBoostTopSpeedFrame = (int)g_fFPS;
const int g_iBoostRisingyTopSpeedFrame = (int)g_fFPS / 4;//�u�[�X�g�㏸��������.

const int g_iStabilityVariationRange = 3;//���萫�\�ȂǂŌ�������X�e�[�^�X���Œ�l���牽�{���̕ϓ������邩.

const int g_iBoostResDec = 10;//�u�[�X�g�W�J��.�̗������x�����̓x��.
const int g_iHeadLockSpeedReference = 500;//���p�[�c�̃��b�N���x�̊�l�A������Ⴂ�ƃ��b�N���Ԃ������Ȃ�.

enum enAnimNoLeg
{
	enAnimNoLegWait = 0,
	enAnimNoLegWalkStart,
	enAnimNoLegWalkRight,
	enAnimNoLegWalkLeft,
	enAnimNoLegWalkEndRight,
	enAnimNoLegWalkEndLeft,
	enAnimNoLegBoostStart,
	enAnimNoLegBoost,
	enAnimNoLegBoostEnd,
	enAnimNoLegJumpStart,
	enAnimNoLegJumpUp,
	enAnimNoLegJump,
	enAnimNoLegJumpDown,
	enAnimNoLegJumpEnd,
	enAnimNoLegDown
};

void clsRobo::RoboInit(
	clsPOINTER_GROUP* const pPtrGroup,
	clsROBO_STATUS* const pRobo)
{
#ifdef Tahara
	m_wpResource = pPtrGroup->GetResource();
	m_wpEffects = pPtrGroup->GetEffects();
	m_wpSound = pPtrGroup->GetSound();
#endif//#ifdef Tahara

	const int iHulf = 2;

	m_iMaxHP = pRobo->GetRoboState(clsROBO_STATUS::HP);//HP�󂯎��.
	m_iMaxHP = 10000;
	m_iHP = m_iMaxHP;//����HP���ő�l�ŏ�����.
	
	//���s�ō����x.
	m_fWalktMoveSpeedMax = pRobo->GetRoboState(clsROBO_STATUS::WALK_SPD) * g_fDistanceReference;
	//���s��������.
	m_iWalkTopSpeedFrame = g_iWalkTopSpeedFrame + (g_iWalkTopSpeedFrame * g_iStabilityVariationRange) * (pRobo->GetRoboState(clsROBO_STATUS::STABILITY) * g_fPercentage);

	//��]�ō����Ɖ������Ԑݒ�.
	SetRotAcceleSpeed(pRobo->GetRoboState(clsROBO_STATUS::TURN)* g_fDirectionReference,
		g_iRotTopSpeedFrame + ((g_iRotTopSpeedFrame * g_iStabilityVariationRange) * (pRobo->GetRoboState(clsROBO_STATUS::STABILITY) * g_fPercentage)));

	//�W�����v��.
	SetJumpPower(pRobo->GetRoboState(clsROBO_STATUS::JUMP_POWER) * g_fDistanceReference);

	//�G�l���M�[�ő�l.
	m_iEnelgy = m_iEnelgyMax = pRobo->GetRoboState(clsROBO_STATUS::EN_CAPA);
	//�G�l���M�[�񕜗�.
	//m_iEnelgyOutput = pRobo->GetRoboState(clsROBO_STATUS::EN_OUTPUT) / static_cast<int>(g_fFPS);

	m_iEnelgyOutput = 50000;

	//���V���G�l���M�[�񕜗�(�ʏ�G�l���M�[�̔���).
	m_iBoostFloatRecovery = m_iEnelgyOutput / iHulf;
	
	//�u�[�X�g�ړ����x.
	m_fBoostMoveSpeedMax = pRobo->GetRoboState(clsROBO_STATUS::BOOST_THRUST_H) * g_fDistanceReference;
	//�u�[�X�g��������.
	m_iBoostTopSpeedFrame = g_iBoostRisingyTopSpeedFrame + (g_iWalkTopSpeedFrame * g_iStabilityVariationRange) * (pRobo->GetRoboState(clsROBO_STATUS::STABILITY) * g_fPercentage);
	//�u�[�X�g�W�J����EN����.
	m_iBoostMoveCost = pRobo->GetRoboState(clsROBO_STATUS::BOOST_COST_H);

	//�u�[�X�g�㏸���x.
	m_fBoostRisingSpeedMax = pRobo->GetRoboState(clsROBO_STATUS::BOOST_THRUST_V) * g_fDistanceReference;
	//�u�[�X�g�㏸EN���.
	m_iBoostRisingyCost = pRobo->GetRoboState(clsROBO_STATUS::BOOST_COST_V);

	//�u�[�X�g�㏸��������.
	m_iBoostRisingTopSpeedFrame = g_iBoostRisingyTopSpeedFrame;
	//�u�[�X�g�㏸������.
	m_fBoostRisingAccele = m_fBoostRisingSpeedMax / g_iBoostRisingyTopSpeedFrame;

	//�u�[�X�g�W�J���ɉ��ɗ����鑬�x.
	m_fBoostFollRes = m_fBoostRisingSpeedMax / g_iBoostResDec;

	m_fQuickBoostSpeedMax = pRobo->GetRoboState(clsROBO_STATUS::QUICK_THRUST) * g_fDistanceReference;
	m_iQuickBoostEnelgyCost = pRobo->GetRoboState(clsROBO_STATUS::QUICK_COST);
	m_iQuickBoostTopSpeedTime = pRobo->GetRoboState(clsROBO_STATUS::QUICK_TIME);

	m_fQuickTrunSpeedMax = (float)D3DX_PI / g_iQuickTurnFrame;
	m_iQuickTrunTopSpeedTime = m_iQuickBoostTopSpeedTime;

	m_iActivityLimitTime = 300 * static_cast<int>(g_fFPS);
	//m_iActivityLimitTime = pRobo->GetRoboState(clsROBO_STATUS::ACT_TIME) * static_cast<int>(g_fFPS);

	m_fRaderRange = pRobo->GetRoboState(clsROBO_STATUS::SEARCH);

	m_fLockRange = pRobo->GetRoboState(clsROBO_STATUS::LOCK_ON_RANGE);

	m_pMesh = new clsMISSION_MODEL;

	m_pMesh->Create(m_wpResource, pRobo);

	m_Trans.vPos.y = 10.0f;

	SetMoveAcceleSpeed(m_fWalktMoveSpeedMax, m_iWalkTopSpeedFrame);
	SetMoveDeceleSpeed(m_iTopMoveSpeedFrame);

	m_iEnelgyMax = 10000;

	m_iEnelgy = m_iEnelgyMax;

	/*m_fWalktMoveSpeedMax = 0.25f;
	m_iWalkTopSpeedFrame = 5;

	m_fBoostMoveSpeedMax = 0.5f;
	m_iBoostTopSpeedFrame = 60;

	m_fQuickBoostSpeedMax = m_fBoostMoveSpeedMax * 3.0f;
	m_iQuickBoostTopSpeedTime = 1 * static_cast<int>(g_fFPS);

	m_fQuickTrunSpeedMax = (float)D3DX_PI / g_iQuickTurnFrame;
	m_iQuickTrunTopSpeedTime = 15;

	m_fBoostRisingAccele = m_fBoostRisingSpeedMax / m_iBoostRisingTopSpeedFrame;// = m_fMoveSpeedMax / m_fTopSpeedFrame;
	

	SetMoveAcceleSpeed(m_fWalktMoveSpeedMax, m_iWalkTopSpeedFrame);
	SetMoveDeceleSpeed(m_iTopMoveSpeedFrame);

	m_iQuickBoostEnelgyCost = 1000;
	m_iQuickTrunEnelgyCost = 1000;
	m_iBoostRisingyCost = 100;

	m_iEnelgyMax = 10000;
	m_iEnelgy = m_iEnelgyMax;
	m_iEnelgyOutput = 1500 / static_cast<int>(g_fFPS);
	m_iBoostFloatRecovery = m_iEnelgyOutput / 2;

	SetRotAcceleSpeed(0.01f, 30);
	SetJumpPower(0.5f);

	m_iActivityLimitTime = 300 * static_cast<int>(g_fFPS);*/

	//m_MaxHP = 5000;
	//m_HP = m_MaxHP;

	WeaponState WS[enWeaponTypeSize];

	for (int i = 0; i < enWeaponTypeSize; i++)
	{
		//float�^��int�œ����Ă����X�e�[�^�X�ɂ��ꂱ�ꂵ�Čv�Z����.

		clsROBO_STATUS::enWEAPON_NUM ucEquipWeaponNum = static_cast<clsROBO_STATUS::enWEAPON_NUM>(i);

		WS[i].iAtk = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::ATK);
		WS[i].iBulletNumMax = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::BULLETS_NUM);
		WS[i].BState.fSpeed = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::BULLET_SPD) * g_fDistanceReference;
		WS[i].BState.fScale = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::COL_SIZE)* g_fDistanceReference;
		WS[i].iShotEN = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::COST);
		WS[i].BState.iShotEfcNum = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::EFC_BULLET);
		pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::EFC_CARTRIDGE);
		WS[i].BState.iHitEfcNum = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::EFC_HIT);
		WS[i].BState.iLineEfcNum = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::EFC_LOCUS);
		WS[i].iReloadTime = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::LOAD_TIME);
		
		WS[i].MagazineReloadTime = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::MAGAZINE_LOAD_TIME);
		WS[i].BState.fRangeMax = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::RANGE)* g_fDistanceReference;
		WS[i].BState.iSEHitNum = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::SE_FIER);
		WS[i].BState.iSEShotNum = pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::SE_HIT);

		WS[i].iLockSpeed = (
			pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::LOCK_ON_TIME) / pRobo->GetRoboState(clsROBO_STATUS::LOCK_ON_SPEED));

		//�r�̏Ə����x�ƕ��펩�̂̎ˌ����x�ŏW�c����ݒ�.
		WS[i].iStablity = (
			(pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::SHOT_STABILITY) + 
			pRobo->GetRoboState(clsROBO_STATUS::AIMING)) 
			/ iHulf);
	}

	WeaponInit(pPtrGroup, WS, enWeaponTypeSize);

	SetBoostEffect();

	//m_fLockRange = 500.0f;//���b�N�I������.
	m_fLockCircleRadius = 500.0f;//���b�N�I������̔��a.

	m_pViewPort = pPtrGroup->GetViewPort10();

	m_pMesh->PartsAnimChange(enPARTS::ARM_R, 3);
	m_pMesh->SetAnimSpd(g_dAnimSpeedReference);
}

void clsRobo::Walk()
{
	SetMoveAcceleSpeed(m_fWalktMoveSpeedMax, m_iWalkTopSpeedFrame);
	m_iMoveStopFrame = m_iWalkTopSpeedFrame;
	
	m_bBoost = false;
}

void clsRobo::Boost()
{
	SetMoveAcceleSpeed(m_fBoostMoveSpeedMax, m_iBoostTopSpeedFrame);
	m_iMoveStopFrame = m_iBoostTopSpeedFrame;

	m_bBoost = true;
}

void clsRobo::MoveSwitch()
{
	if (IsMoveControl())
	{
		if (m_bBoost)
		{
			Walk();
		}

		else
		{
			Boost();
		}
	}
}

void clsRobo::BoostRising()
{
	if (!m_bGround || IsMoveing())
	{
		if (EnelgyConsumption(m_iBoostRisingyCost))
		{
			if (m_fFollPower < m_fBoostMoveSpeedMax)
			{
				m_fFollPower += m_fBoostRisingAccele;
			}

			else
			{
				m_fFollPower = m_fBoostMoveSpeedMax;
			}

			if (!m_bBoost)
			{
				Boost();
			}
		}

		else
		{
			Walk();
		}
	}

	else
	{
		m_pMesh->SetPartsAnimNo(enPARTS::LEG, enAnimNoLegJumpStart);
	}
}

void clsRobo::SetDirQuickBoost(const float fAngle)
{
	//�N�C�b�N�u�[�X�g���邽�߁A�����I�Ɉړ�����������.
	if (IsMoveControl())
	{
		D3DXVECTOR3 vForward;

		//�������Ă������.
		vForward = GetVec3Dir(m_Trans.fYaw, g_vDirForward);

		//�s����������.
		m_vMoveDir = GetVec3Dir(fAngle, vForward);
	}
}

void clsRobo::QuickBoost()
{
	if (IsMoveControl())
	{
		if (EnelgyConsumption(m_iQuickBoostEnelgyCost))
		{
			if (m_iQuickInterbal < 0)
			{
				m_iQuickInterbal = g_iQuickInterbal;
				m_fMoveSpeed = m_fQuickBoostSpeedMax;
				m_iQuickBoostDecStartTime = m_iQuickBoostTopSpeedTime;
				SetMoveDeceleSpeed(m_iQuickInterbal);
			}
		}
	}
}

void clsRobo::SetDirQuickTurn(const float fAngle)
{
	if (!m_bBoost)
	{
		if (IsRotControl())
		{
			float fTmp = (int)D3DX_PI * (fAngle / abs(fAngle));
			SetRotDir(fTmp);
		}
	}
}

void clsRobo::QuickTurn()
{
	if (!m_bBoost)
	{
		if (EnelgyConsumption(m_iQuickTrunEnelgyCost))
		{
			if (IsRotControl())
			{
				if (m_iQuickInterbal < 0)
				{
					m_iQuickInterbal = g_iQuickInterbal;
					m_fRotSpeed = m_fQuickTrunSpeedMax;
					m_iQuickTrunDecStartTime = m_iQuickTrunTopSpeedTime;
					SetRotDeceleSpeed(m_iQuickInterbal);
				}
			}
		}
	}
}

void clsRobo::Updata()
{
	PlayBoostEfc();
	CharactorUpdate();
	m_vAcceleDir = { 0.0f, 0.0f, 0.0f };//�u�[�X�^�[�G�t�F�N�g�����Ɏg���Ă���̂Ŗ��t���[���̏��������K�v�ɂȂ�.

	if (m_iQuickBoostDecStartTime > 0)//�N�C�b�N�u�[�X�g.
	{
		m_fMoveSpeed = m_fQuickBoostSpeedMax;
		m_iQuickBoostDecStartTime--;
	}

	if (m_iQuickTrunDecStartTime > 0)//�N�C�b�N�^�[��.
	{
		m_fRotSpeed = m_fQuickTrunSpeedMax;
		m_iQuickTrunDecStartTime--;
	}

	if (IsMoveControl())
	{
		if (!m_bBoost)
		{
			Walk();
		}

		else
		{
			Boost();
		}
	}

	if (m_bBoost)
	{
		if (m_fFollPower < -m_fBoostFollRes)
		{
			m_fFollPower += m_fBoostFollRes;

			if (m_fFollPower > -m_fBoostFollRes)
			{
				m_fFollPower = -m_fBoostFollRes;
			}
		}
	}

	if (IsRotControl())
	{
		SetRotDeceleSpeed(m_iRotStopFrame);
	}

	if (m_iQuickInterbal >= 0)
	{
		m_iQuickInterbal--;
	}

	WeaponUpdate();

	EnelgyRecovery();

	UpdataLimitTime();

	AnimUpdate();
}

void clsRobo::UpdataLimitTime()
{
	if (m_iActivityLimitTime < 0)
	{
		m_bTimeUp = true;
		m_pMesh->SetPartsAnimNo(enPARTS::LEG, enAnimNoLegDown);
	}

	else
	{
		m_iActivityLimitTime--;
	}
}

void clsRobo::EnelgyRecovery()
{
	SetEnelgyRecoveryAmount();

	m_iEnelgy += m_iEnelgyRecoveryPoint;

	if (m_iEnelgy > m_iEnelgyMax)
	{
		m_iEnelgy = m_iEnelgyMax;
	}

	if (m_iEnelgy < 0)
	{
		m_iEnelgy = 0;
	}
}

void clsRobo::SetEnelgyRecoveryAmount()
{
	m_iEnelgyRecoveryPoint = m_iEnelgyOutput;

	//�u�[�X�g�W�J��.
	if (m_bBoost)
	{
		//���V��.
		if (!m_bGround)
		{
			//EN�񕜂𗎂Ƃ�.
			m_iEnelgyRecoveryPoint -= m_iBoostFloatRecovery;
		}

		m_iEnelgyRecoveryPoint -= m_iBoostMoveCost;
	}

	if (false)//�ˌ���������.
	{
		m_iEnelgyRecoveryPoint -= (m_iEnelgyOutput);
	}
}

bool clsRobo::EnelgyConsumption(const int iConsumption)
{
	if (IsEnelgyRamaining(iConsumption))
	{
		m_iEnelgy -= iConsumption;
		return true;
	}

	return false;
}

bool clsRobo::IsEnelgyRamaining(const int iConsumption)
{
	if (m_iEnelgy >= iConsumption)
	{
		return true;
	}

	return false;
}

void clsRobo::UpdatePosfromBone()
{
	m_vCenterPos = m_pMesh->GetBonePos(enPARTS::CORE, "Jenerator");

	m_vLockRangePos = m_pMesh->GetBonePos(enPARTS::HEAD, "Center");

	m_v_vMuzzlePos[enWeaponLHand] = m_pMesh->GetBonePos(enPARTS::WEAPON_L, "MuzzleEnd");
	m_v_vShotDir[enWeaponLHand] = m_v_vMuzzlePos[enWeaponLHand] - m_pMesh->GetBonePos(enPARTS::WEAPON_L, "MuzzleRoot");

	m_v_vMuzzlePos[enWeaponRHand] = m_pMesh->GetBonePos(enPARTS::WEAPON_R, "MuzzleEnd");
	m_v_vShotDir[enWeaponRHand] = m_v_vMuzzlePos[enWeaponRHand] - m_pMesh->GetBonePos(enPARTS::WEAPON_R, "MuzzleRoot");

	for (int i = 0; i < enWeaponTypeSize; i++)
	{
		D3DXVec3Normalize(&m_v_vShotDir[i], &m_v_vShotDir[i]);
	}
}

void clsRobo::ShotLWeapon()
{
	ShotSwich(enWeaponLHand);
	if (IsEnelgyRamaining(m_v_pWeapons[enWeaponLHand]->GetShotEN()))
	{
		if (Shot())
		{
			//EN����.
			EnelgyConsumption(m_v_pWeapons[enWeaponLHand]->GetShotEN());

			//�ˌ��A�j������.


		}

		else
		{
			if (Reload())
			{
				//�����[�h�A�j������.
			}
		}
	}
}
	

void clsRobo::ShotRWeapon()
{
	ShotSwich(enWeaponRHand);
	if (IsEnelgyRamaining(m_v_pWeapons[enWeaponRHand]->GetShotEN()))
	{
		if (Shot())
		{
			//EN����.
			EnelgyConsumption(m_v_pWeapons[enWeaponRHand]->GetShotEN());

			//�ˌ��A�j������.
		}

		else
		{
			if (Reload())
			{
				//�����[�h�A�j������.
			}
		}
	}
	
}

void clsRobo::SetBoostEffect()
{
	SetRHandFrontBoostEffect();
	SetRHandSideBoostEffect();
	SetRHandBackBoostEffect();

	SetLHandFrontBoostEffect();
	SetLHandSideBoostEffect();
	SetLHandBackBoostEffect();

	SetCoreBoostEffect();

	SetLegBoostEffect();
}

void clsRobo::SetRHandFrontBoostEffect()
{
	enPARTS PartsNum = enPARTS::ARM_R;

	std::string strBoostRootBoneName = "BoosterFront";

	int iEfcNum = GetBoostEfcNum(PartsNum, strBoostRootBoneName.c_str());

	m_v_RHandFrontBoostEfc.resize(iEfcNum);

	for (unsigned int i = 0; i < m_v_RHandFrontBoostEfc.size(); i++)
	{
		m_v_RHandFrontBoostEfc[i] = 0;
	}
}

void clsRobo::SetRHandSideBoostEffect()
{
	enPARTS PartsNum = enPARTS::ARM_R;

	std::string strBoostRootBoneName = "BoosterSide";

	int iEfcNum = GetBoostEfcNum(PartsNum, strBoostRootBoneName.c_str());

	m_v_RHandSideBoostEfc.resize(iEfcNum);

	for (unsigned int i = 0; i < m_v_RHandSideBoostEfc.size(); i++)
	{
		m_v_RHandSideBoostEfc[i] = 0;
	}
}

void clsRobo::SetRHandBackBoostEffect()
{
	enPARTS PartsNum = enPARTS::ARM_R;

	std::string strBoostRootBoneName = "BoosterBack";

	int iEfcNum = GetBoostEfcNum(PartsNum, strBoostRootBoneName.c_str());

	m_v_RHandBackBoostEfc.resize(iEfcNum);

	for (unsigned int i = 0; i < m_v_RHandBackBoostEfc.size(); i++)
	{
		m_v_RHandBackBoostEfc[i] = 0;
	}
}

void clsRobo::SetLHandFrontBoostEffect()
{
	enPARTS PartsNum = enPARTS::ARM_L;

	std::string strBoostRootBoneName = "BoosterFront";

	int iEfcNum = GetBoostEfcNum(PartsNum, strBoostRootBoneName.c_str());

	m_v_LHandFrontBoostEfc.resize(iEfcNum);

	for (unsigned int i = 0; i < m_v_LHandFrontBoostEfc.size(); i++)
	{
		m_v_LHandFrontBoostEfc[i] = 0;
	}
}

void clsRobo::SetLHandSideBoostEffect()
{
	enPARTS PartsNum = enPARTS::ARM_L;

	std::string strBoostRootBoneName = "BoosterSide";

	int iEfcNum = GetBoostEfcNum(PartsNum, strBoostRootBoneName.c_str());

	m_v_LHandSideBoostEfc.resize(iEfcNum);

	for (unsigned int i = 0; i < m_v_LHandSideBoostEfc.size(); i++)
	{
		m_v_LHandSideBoostEfc[i] = 0;
	}
}

void clsRobo::SetLHandBackBoostEffect()
{
	enPARTS PartsNum = enPARTS::ARM_L;

	std::string strBoostRootBoneName = "BoosterBack";

	int iEfcNum = GetBoostEfcNum(PartsNum, strBoostRootBoneName.c_str());

	m_v_LHandBackBoostEfc.resize(iEfcNum);

	for (unsigned int i = 0; i < m_v_LHandBackBoostEfc.size(); i++)
	{
		m_v_LHandBackBoostEfc[i] = 0;
	}
}

void clsRobo::SetCoreBoostEffect()
{
	enPARTS PartsNum = enPARTS::CORE;

	std::string strBoostRootBoneName = "Booster";

	int iEfcNum = GetBoostEfcNum(PartsNum, strBoostRootBoneName.c_str());

	m_v_CoreBoostEfc.resize(iEfcNum);

	for (unsigned int i = 0; i < m_v_CoreBoostEfc.size(); i++)
	{
		m_v_CoreBoostEfc[i] = 0;
	}
}

void clsRobo::SetLegBoostEffect()
{
	enPARTS PartsNum = enPARTS::LEG;

	std::string strBoostRootBoneName = "Booster";

	int iEfcNum = GetBoostEfcNum(PartsNum, strBoostRootBoneName.c_str());

	m_v_LegBoostEfc.resize(iEfcNum);

	for (unsigned int i = 0; i < m_v_LegBoostEfc.size(); i++)
	{
		m_v_LegBoostEfc[i] = 0;
	}
}

int clsRobo::GetBoostEfcNum(enPARTS PartsNum, const char* strBoostPosition)
{
	std::string strBoostRootBoneName = strBoostPosition;
	strBoostRootBoneName += "Root";

	std::string strBoostEndBoneName = strBoostPosition;
	strBoostEndBoneName += "End";

	int iRootNum = m_pMesh->GetSimilarityNameBoneNum(PartsNum, strBoostRootBoneName.c_str());
	int iEndNum = m_pMesh->GetSimilarityNameBoneNum(PartsNum, strBoostEndBoneName.c_str());

	int iResult = 0;
	if (iRootNum > iEndNum)
	{
		iResult = iEndNum;
	}

	else
	{
		iResult = iRootNum;
	}

	return iResult;
}

bool clsRobo::IsLWeaponLock()
{
	if (m_v_pWeapons[enWeaponLHand]->IsLock())
	{
		return true;
	}

	return false;
}

bool clsRobo::IsRWeaponLock()
{
	if (m_v_pWeapons[enWeaponRHand]->IsLock())
	{
		return true;
	}

	return false;
}

void clsRobo::PlayBoostEfc()
{
	m_vMoveDirforBoost = GetVec3Dir(-m_Trans.fYaw, m_vAcceleDir);
	m_vMoveDirforBoost.z = +m_vMoveDirforBoost.z;

	PlayFrontBoostEfc();
	PlayRightBoostEfc();
	PlayLeftBoostEfc();
	PlayBackBoostEfc();

	PlayLegBoostEfc();
}

void clsRobo::PlayFrontBoostEfc()
{
	clsOPERATION_STRING OprtStr;//�{�[�����Ɣԍ����q�������.

	if (m_vMoveDirforBoost.z < -0.1f)
	{
		std::string strBoostRootName = "BoosterFrontRoot";
		std::string strBoostEndName = "BoosterFrontEnd";
		std::string strBoostRootNameTmp = "";
		std::string strBoostEndNameTmp = "";

		D3DXVECTOR3 vPosRotTmp = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 vPosEndTmp = { 0.0f, 0.0f, 0.0f };

		for (unsigned int i = 0; i < m_v_LHandFrontBoostEfc.size(); i++)
		{
			//�t�����̖��O�𐶐�.
			strBoostRootNameTmp = strBoostRootName;
			strBoostRootNameTmp = OprtStr.ConsolidatedNumber(strBoostRootNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			strBoostEndNameTmp = strBoostEndName;
			strBoostEndNameTmp = OprtStr.ConsolidatedNumber(strBoostEndNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			vPosRotTmp = m_pMesh->GetDirfromBone(enPARTS::ARM_L, strBoostRootName.c_str(), strBoostEndName.c_str());
			vPosEndTmp = m_pMesh->GetBonePos(enPARTS::ARM_L, strBoostEndNameTmp.c_str());

			if (!m_wpEffects->isPlay(m_v_LHandFrontBoostEfc[i]))
			{
				m_v_LHandFrontBoostEfc[i] = m_wpEffects->Play(3, vPosEndTmp);
			}

			else
			{
				m_wpEffects->SetPosition(m_v_LHandFrontBoostEfc[i], vPosEndTmp);
			}

			m_wpEffects->SetRotation(m_v_LHandFrontBoostEfc[i], vPosRotTmp);
		}

		for (unsigned int i = 0; i < m_v_RHandFrontBoostEfc.size(); i++)
		{
			//�t�����̖��O�𐶐�.
			strBoostRootNameTmp = strBoostRootName;
			strBoostRootNameTmp = OprtStr.ConsolidatedNumber(strBoostRootNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			strBoostEndNameTmp = strBoostEndName;
			strBoostEndNameTmp = OprtStr.ConsolidatedNumber(strBoostEndNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			vPosRotTmp = m_pMesh->GetDirfromBone(enPARTS::ARM_R, strBoostRootName.c_str(), strBoostEndName.c_str());

			vPosEndTmp = m_pMesh->GetBonePos(enPARTS::ARM_R, strBoostEndNameTmp.c_str());
			if (!m_wpEffects->isPlay(m_v_RHandFrontBoostEfc[i]))
			{
				m_v_RHandFrontBoostEfc[i] = m_wpEffects->Play(3, vPosEndTmp);
			}

			else
			{
				m_wpEffects->SetPosition(m_v_RHandFrontBoostEfc[i], vPosEndTmp);
			}
			m_wpEffects->SetRotation(m_v_RHandFrontBoostEfc[i], vPosRotTmp);
			
		}
	}

	else
	{
		for (unsigned int i = 0; i < m_v_LHandFrontBoostEfc.size(); i++)
		{
			if (m_wpEffects->isPlay(m_v_LHandFrontBoostEfc[i]))
			{
				m_wpEffects->Stop(m_v_LHandFrontBoostEfc[i]);
			}
		}

		for (unsigned int i = 0; i < m_v_RHandFrontBoostEfc.size(); i++)
		{
			if (m_wpEffects->isPlay(m_v_RHandFrontBoostEfc[i]))
			{
				m_wpEffects->Stop(m_v_RHandFrontBoostEfc[i]);
			}
		}
	}
}

void clsRobo::PlayRightBoostEfc()
{
	clsOPERATION_STRING OprtStr;//�{�[�����Ɣԍ����q�������.

	if (m_vMoveDirforBoost.x < -0.1f)
	{
		std::string strBoostRootName = "BoosterSideRoot";
		std::string strBoostEndName = "BoosterSideEnd";
		std::string strBoostRootNameTmp = "";
		std::string strBoostEndNameTmp = "";

		D3DXVECTOR3 vPosRotTmp = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 vPosEndTmp = { 0.0f, 0.0f, 0.0f };

		for (unsigned int i = 0; i < m_v_RHandSideBoostEfc.size(); i++)
		{
			//�t�����̖��O�𐶐�.
			strBoostRootNameTmp = strBoostRootName;
			strBoostRootNameTmp = OprtStr.ConsolidatedNumber(strBoostRootNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			strBoostEndNameTmp = strBoostEndName;
			strBoostEndNameTmp = OprtStr.ConsolidatedNumber(strBoostEndNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			vPosRotTmp = m_pMesh->GetDirfromBone(enPARTS::ARM_R, strBoostRootName.c_str(), strBoostEndName.c_str());

			vPosEndTmp = m_pMesh->GetBonePos(enPARTS::ARM_R, strBoostEndNameTmp.c_str());
			if (!m_wpEffects->isPlay(m_v_RHandSideBoostEfc[i]))
			{
				m_v_RHandSideBoostEfc[i] = m_wpEffects->Play(3, vPosEndTmp);
			}

			else
			{
				m_wpEffects->SetPosition(m_v_RHandSideBoostEfc[i], vPosEndTmp);
			}

			m_wpEffects->SetRotation(m_v_RHandSideBoostEfc[i], vPosRotTmp);
			
		}
	}

	else
	{
		for (unsigned int i = 0; i < m_v_RHandSideBoostEfc.size(); i++)
		{
			if (m_wpEffects->isPlay(m_v_RHandSideBoostEfc[i]))
			{
				m_wpEffects->Stop(m_v_RHandSideBoostEfc[i]);
			}
		}
	}
}

void clsRobo::PlayLeftBoostEfc()
{
	clsOPERATION_STRING OprtStr;//�{�[�����Ɣԍ����q�������.

	if (m_vMoveDirforBoost.x > 0.1f)
	{
		std::string strBoostRootName = "BoosterSideRoot";
		std::string strBoostEndName = "BoosterSideEnd";
		std::string strBoostRootNameTmp = "";
		std::string strBoostEndNameTmp = "";

		D3DXVECTOR3 vPosRotTmp = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 vPosEndTmp = { 0.0f, 0.0f, 0.0f };

		for (unsigned int i = 0; i < m_v_LHandSideBoostEfc.size(); i++)
		{
			//�t�����̖��O�𐶐�.
			strBoostRootNameTmp = strBoostRootName;
			strBoostRootNameTmp = OprtStr.ConsolidatedNumber(strBoostRootNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			strBoostEndNameTmp = strBoostEndName;
			strBoostEndNameTmp = OprtStr.ConsolidatedNumber(strBoostEndNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			vPosRotTmp = m_pMesh->GetDirfromBone(enPARTS::ARM_L, strBoostRootName.c_str(), strBoostEndName.c_str());

			vPosEndTmp = m_pMesh->GetBonePos(enPARTS::ARM_L, strBoostEndNameTmp.c_str());

			if (!m_wpEffects->isPlay(m_v_LHandSideBoostEfc[i]))
			{
				m_v_LHandSideBoostEfc[i] = m_wpEffects->Play(3, vPosEndTmp);
			}

			else
			{
				m_wpEffects->SetPosition(m_v_LHandSideBoostEfc[i], vPosEndTmp);
			}

			m_wpEffects->SetRotation(m_v_LHandSideBoostEfc[i], vPosRotTmp);
		}
	}

	else
	{
		for (unsigned int i = 0; i < m_v_LHandSideBoostEfc.size(); i++)
		{
			if (m_wpEffects->isPlay(m_v_LHandSideBoostEfc[i]))
			{
				m_wpEffects->Stop(m_v_LHandSideBoostEfc[i]);
			}
		}
	}
}

void clsRobo::PlayBackBoostEfc()
{
	clsOPERATION_STRING OprtStr;//�{�[�����Ɣԍ����q�������.

	if (m_vMoveDirforBoost.z > 0.1f)
	{
		std::string strBoostRootName = "BoosterBackRoot";
		std::string strBoostEndName = "BoosterBackEnd";
		std::string strBoostRootNameTmp = "";
		std::string strBoostEndNameTmp = "";

		D3DXVECTOR3 vPosRotTmp = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 vPosEndTmp = { 0.0f, 0.0f, 0.0f };

		for (unsigned int i = 0; i < m_v_LHandBackBoostEfc.size(); i++)
		{
			//�t�����̖��O�𐶐�.
			strBoostRootNameTmp = strBoostRootName;
			strBoostRootNameTmp = OprtStr.ConsolidatedNumber(strBoostRootNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			strBoostEndNameTmp = strBoostEndName;
			strBoostEndNameTmp = OprtStr.ConsolidatedNumber(strBoostEndNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			vPosRotTmp = m_pMesh->GetDirfromBone(enPARTS::ARM_L, strBoostRootName.c_str(), strBoostEndName.c_str());

			vPosEndTmp = m_pMesh->GetBonePos(enPARTS::ARM_L, strBoostEndNameTmp.c_str());

			if (!m_wpEffects->isPlay(m_v_LHandBackBoostEfc[i]))
			{
				m_v_LHandBackBoostEfc[i] = m_wpEffects->Play(3, vPosEndTmp);
			}

			else
			{
				m_wpEffects->SetPosition(m_v_LHandBackBoostEfc[i], vPosEndTmp);
			}

			m_wpEffects->SetRotation(m_v_LHandBackBoostEfc[i], vPosRotTmp);
		}

		for (unsigned int i = 0; i < m_v_RHandBackBoostEfc.size(); i++)
		{
			//�t�����̖��O�𐶐�.
			strBoostRootNameTmp = strBoostRootName;
			strBoostRootNameTmp = OprtStr.ConsolidatedNumber(strBoostRootNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			strBoostEndNameTmp = strBoostEndName;
			strBoostEndNameTmp = OprtStr.ConsolidatedNumber(strBoostEndNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			vPosRotTmp = m_pMesh->GetDirfromBone(enPARTS::ARM_R, strBoostRootName.c_str(), strBoostEndName.c_str());

			vPosEndTmp = m_pMesh->GetBonePos(enPARTS::ARM_R, strBoostEndNameTmp.c_str());

			if (!m_wpEffects->isPlay(m_v_RHandBackBoostEfc[i]))
			{
				m_v_RHandBackBoostEfc[i] = m_wpEffects->Play(3, vPosEndTmp);
			}

			else
			{
				m_wpEffects->SetPosition(m_v_RHandBackBoostEfc[i], vPosEndTmp);
			}
			m_wpEffects->SetRotation(m_v_RHandBackBoostEfc[i], vPosRotTmp);
		}

		strBoostRootName = "BoosterRoot";
		strBoostEndName = "BoosterEnd";

		for (unsigned int i = 0; i < m_v_CoreBoostEfc.size(); i++)
		{
			//�t�����̖��O�𐶐�.
			strBoostRootNameTmp = strBoostRootName;
			strBoostRootNameTmp = OprtStr.ConsolidatedNumber(strBoostRootNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			strBoostEndNameTmp = strBoostEndName;
			strBoostEndNameTmp = OprtStr.ConsolidatedNumber(strBoostEndNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			vPosRotTmp = m_pMesh->GetDirfromBone(enPARTS::CORE, strBoostRootName.c_str(), strBoostEndName.c_str());

			vPosEndTmp = m_pMesh->GetBonePos(enPARTS::CORE, strBoostEndNameTmp.c_str());
			if (!m_wpEffects->isPlay(m_v_CoreBoostEfc[i]))
			{
				m_v_CoreBoostEfc[i] = m_wpEffects->Play(3, vPosEndTmp);
			}

			else
			{
				m_wpEffects->SetPosition(m_v_CoreBoostEfc[i], vPosEndTmp);
			}
			m_wpEffects->SetRotation(m_v_CoreBoostEfc[i], vPosRotTmp);
			m_wpEffects->SetScale(m_v_CoreBoostEfc[i], 2.0f);

		}
	}

	else
	{
		for (unsigned int i = 0; i < m_v_LHandBackBoostEfc.size(); i++)
		{
			if (m_wpEffects->isPlay(m_v_LHandBackBoostEfc[i]))
			{
				m_wpEffects->Stop(m_v_LHandBackBoostEfc[i]);
			}
		}

		for (unsigned int i = 0; i < m_v_RHandBackBoostEfc.size(); i++)
		{
			if (m_wpEffects->isPlay(m_v_RHandBackBoostEfc[i]))
			{
				m_wpEffects->Stop(m_v_RHandBackBoostEfc[i]);
			}
		}

		for (unsigned int i = 0; i < m_v_CoreBoostEfc.size(); i++)
		{
			if (m_wpEffects->isPlay(m_v_CoreBoostEfc[i]))
			{
				m_wpEffects->Stop(m_v_CoreBoostEfc[i]);
			}
		}
	}
}

void clsRobo::PlayLegBoostEfc()
{
	clsOPERATION_STRING OprtStr;//�{�[�����Ɣԍ����q�������.

	if (m_bBoost)
	{
		std::string strBoostRootName = "BoosterRoot";
		std::string strBoostEndName = "BoosterEnd";
		std::string strBoostRootNameTmp = "";
		std::string strBoostEndNameTmp = "";

		D3DXVECTOR3 vPosRotTmp = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 vPosEndTmp = { 0.0f, 0.0f, 0.0f };

		for (unsigned int i = 0; i < m_v_LegBoostEfc.size(); i++)
		{
			//�t�����̖��O�𐶐�.
			strBoostRootNameTmp = strBoostRootName;
			strBoostRootNameTmp = OprtStr.ConsolidatedNumber(strBoostRootNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			strBoostEndNameTmp = strBoostEndName;
			strBoostEndNameTmp = OprtStr.ConsolidatedNumber(strBoostEndNameTmp, i, g_cBONE_NAME_NUM_DIGIT_JOINT);

			vPosRotTmp = m_pMesh->GetDirfromBone(enPARTS::LEG, strBoostRootName.c_str(), strBoostEndName.c_str());

			vPosEndTmp = m_pMesh->GetBonePos(enPARTS::LEG, strBoostEndNameTmp.c_str());

			if (!m_wpEffects->isPlay(m_v_LegBoostEfc[i]))
			{
				m_v_LegBoostEfc[i] = m_wpEffects->Play(3, vPosEndTmp);
			}

			else
			{
				m_wpEffects->SetPosition(m_v_LegBoostEfc[i], vPosEndTmp);
			}
				
			m_wpEffects->SetRotation(m_v_LegBoostEfc[i], vPosRotTmp);
		}
	}

	else
	{
		for (unsigned int i = 0; i < m_v_LegBoostEfc.size(); i++)
		{
			if (m_wpEffects->isPlay(m_v_LegBoostEfc[i]))
			{
				m_wpEffects->Stop(m_v_LegBoostEfc[i]);
			}
		}
	}
}

void clsRobo::SetRotateHeadParts()
{
	D3DXVECTOR3 vTmp = GetRotation();
	vTmp.y += static_cast<float>(D3DX_PI);

	if (m_pTargetChara)
	{
		const float fVecX = m_pTargetChara->GetPosition().x - GetPosition().x;
		const float fVecZ = m_pTargetChara->GetPosition().z - GetPosition().z;

		float fRot = atan2f(fVecX, fVecZ);
		
		fRot += static_cast<float>(D3DX_PI);
		ObjRollOverGuard(&fRot);

		D3DXVECTOR3 vHeadRot = { vTmp.x, fRot, vTmp.z };

		m_pMesh->SetPartsRotate(enPARTS::HEAD, vHeadRot);
	}

	else
	{
		m_pMesh->SetPartsRotate(enPARTS::HEAD, vTmp);
	}
}

void clsRobo::SetRotateArmParts()
{
	D3DXVECTOR3 vTmp = GetRotation();

	//const float fVecX = m_pTargetChara->GetPosition().x - GetPosition().x;
	//const float fVecZ = m_pTargetChara->GetPosition().z - GetPosition().z;

	//float fRot = atan2f(fVecX, fVecZ);

	float fRot = m_fVerLookDir;

	vTmp.y += static_cast<float>(D3DX_PI);
	ObjRollOverGuard(&vTmp.y);

	D3DXVECTOR3 vArmRot = { fRot, vTmp.y, vTmp.z };

	m_pMesh->SetPartsRotate(enPARTS::ARM_L, vArmRot);
	m_pMesh->SetPartsRotate(enPARTS::ARM_R, vArmRot);
}

void clsRobo::SetRotateCoreParts()
{
	D3DXVECTOR3 vTmp = GetRotation();
	vTmp.y += static_cast<float>(D3DX_PI);
	ObjRollOverGuard(&vTmp.y);

	m_pMesh->SetPartsRotate(enPARTS::CORE, vTmp);
}

void clsRobo::SetRotateLegParts()
{
	D3DXVECTOR3 vTmp = GetRotation();
	
	const float fHulfDir = D3DX_PI / 2;

	const float fVecX = m_vMoveDirforBoost.x;
	const float fVecZ = m_vMoveDirforBoost.z;

	float fRot = atan2f(fVecX, fVecZ);

	if (!m_bBoost)
	{
		if (abs(fRot) > fHulfDir)
		{
			fRot -= D3DX_PI * (abs(fRot) / fRot);

			const enAnimNoLeg iAnimNo = static_cast<enAnimNoLeg>(m_pMesh->GetPartsAnimNo(enPARTS::LEG));

			if (iAnimNo > enAnimNoLegWait &&
				iAnimNo < enAnimNoLegBoostStart)//�r�p�[�c�̃A�j���[�V���������s�n����?.
			{
				//���s�A�j���[�V����������.
				if (!m_pMesh->IsPartsAnimReverce(enPARTS::LEG))
				{
					m_pMesh->SetPartsAnimReverce(enPARTS::LEG,true);
				}
			}
		}

		else
		{
			const enAnimNoLeg iAnimNo = static_cast<enAnimNoLeg>(m_pMesh->GetPartsAnimNo(enPARTS::LEG));

			if (iAnimNo > enAnimNoLegWait &&
				iAnimNo < enAnimNoLegBoostStart)//�r�p�[�c�̃A�j���[�V���������s�n����?.
			{
				//���s�A�j���[�V����������.
				if (m_pMesh->IsPartsAnimReverce(enPARTS::LEG))
				{
					m_pMesh->SetPartsAnimNormal(enPARTS::LEG, true);
				}
			}
		}
	}

	vTmp.y += fRot;

	vTmp.y += static_cast<float>(D3DX_PI);
	ObjRollOverGuard(&vTmp.y);

	D3DXVECTOR3 vLegRot = vTmp;

	m_pMesh->SetPartsRotate(enPARTS::LEG, vLegRot);
}

void clsRobo::AnimUpdate()
{
	AnimUpdateLeg();
}

void clsRobo::AnimUpdateLeg()
{
	const enAnimNoLeg iAnimNo = static_cast<enAnimNoLeg>(m_pMesh->GetPartsAnimNo(enPARTS::LEG));

	enAnimNoLeg iChangeAnimNo = iAnimNo;

	double dAnimStartTime = 0.0f;

	switch (iAnimNo)
	{
	case enAnimNoLegWait://�ҋ@��.

		if (IsMoveing())
		{
			iChangeAnimNo = enAnimNoLegWalkStart;
		}

		if (m_bBoost)
		{
			iChangeAnimNo = enAnimNoLegBoostStart;
		}

		break;
	case enAnimNoLegWalkStart:
		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG) || m_pMesh->IsPartsAnimReverce(enPARTS::LEG))//�t�Đ��ɂȂ��Ă�����.
		{
			iChangeAnimNo = enAnimNoLegWalkRight;
			//dAnimStartTime = m_pMesh->GetPartsAnimNowTime(enPARTS::LEG);
		}

		if (!IsMoveing())
		{
			iChangeAnimNo = enAnimNoLegWalkEndRight;
		}

		break;
	case enAnimNoLegWalkRight:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			iChangeAnimNo = enAnimNoLegWalkLeft;
		}

		if (!IsMoveing())
		{
			iChangeAnimNo = enAnimNoLegWalkEndRight;
			//dAnimStartTime = m_pMesh->GetPartsAnimNowTime(enPARTS::LEG);
		}

		break;
	case enAnimNoLegWalkLeft:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			iChangeAnimNo = enAnimNoLegWalkRight;
		}

		if (!IsMoveing())
		{
			iChangeAnimNo = enAnimNoLegWalkEndLeft;
			dAnimStartTime = m_pMesh->GetPartsAnimNowTime(enPARTS::LEG);
		}

		break;
	case enAnimNoLegWalkEndRight:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			iChangeAnimNo = enAnimNoLegWait;
		}

		break;
	case enAnimNoLegWalkEndLeft:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			iChangeAnimNo = enAnimNoLegWait;
		}

		break;
	case enAnimNoLegBoostStart:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			iChangeAnimNo = enAnimNoLegBoost;
		}

		break;
	case enAnimNoLegBoost:

		if (!m_bBoost)//|| !IsMoveing())
		{
			iChangeAnimNo = enAnimNoLegBoostEnd;
		}

		break;
	case enAnimNoLegBoostEnd:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			iChangeAnimNo = enAnimNoLegWait;
		}

		break;
	case enAnimNoLegJumpStart:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			iChangeAnimNo = enAnimNoLegJumpUp;
			Jump();
		}

		break;
	case enAnimNoLegJumpUp:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			iChangeAnimNo = enAnimNoLegJump;
		}

		break;
	case enAnimNoLegJump:

		if (m_fFollPower < 0)
		{
			iChangeAnimNo = enAnimNoLegJumpDown;
		}

		break;
	case enAnimNoLegJumpDown:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			m_pMesh->SetPartsAnimSpeed(enPARTS::LEG, 0.0);
		}

		if (m_bGround)
		{
			iChangeAnimNo = enAnimNoLegJumpEnd;
			m_pMesh->SetPartsAnimSpeed(enPARTS::LEG, g_dAnimSpeedReference);
		}

		break;
	case enAnimNoLegJumpEnd:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			iChangeAnimNo = enAnimNoLegWait;
		}

		break;
	case enAnimNoLegDown:

		if (m_pMesh->IsPartsAnimEnd(enPARTS::LEG))
		{
			m_pMesh->SetPartsAnimSpeed(enPARTS::LEG, 0.0);
		}

		break;
	}

	//�A�j���[�V�����̕ύX������.
	if (iChangeAnimNo != iAnimNo)
	{
		if (m_pMesh->IsPartsAnimReverce(enPARTS::LEG))//�t�Đ��ɂȂ��Ă�����.
		{
			m_pMesh->SetPartsAnimNormal(enPARTS::LEG);//�ʏ�Đ��ɖ߂�.
		}

		m_pMesh->SetPartsAnimNo(enPARTS::LEG, iChangeAnimNo, dAnimStartTime);
	}
}

void clsRobo::AnimUpdateCore()
{

}

void clsRobo::AnimUpdateArmL()
{

}

void clsRobo::AnimUpdateArmR()
{

}

clsRobo::clsRobo() :
m_pMesh(NULL),
m_bBoost(false),
m_fWalktMoveSpeedMax(0.0f),
m_iWalkTopSpeedFrame(0),
m_fBoostMoveSpeedMax(0.0f),
m_iBoostTopSpeedFrame(0),
m_fBoostRisingSpeedMax(0.0f),
m_iBoostRisingTopSpeedFrame(0),
m_fBoostRisingAccele(0.0f),
m_iQuickInterbal(0),
m_wpResource(nullptr),
m_wpEffects(nullptr),
m_wpSound(nullptr)
{
	
}

clsRobo::~clsRobo()
{
	if (m_pMesh != NULL)
	{
		delete m_pMesh;
		m_pMesh = NULL;
	}

#ifdef Tahara
	//�����Ƃ�delete���Ȃ���null���Ă�.
	m_wpSound = nullptr;
	m_wpEffects = nullptr;
	m_wpResource = nullptr;
#endif//#ifdef Tahara
}