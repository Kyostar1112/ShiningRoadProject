#include"Robo.h"
#include "OperationString.h"

//ジョイントボーンの数字の桁数.
const char g_cBONE_NAME_NUM_DIGIT_JOINT = 2;

const int g_iQuickInterbal = (int)g_fFPS;
const int g_iQuickTurnFrame = (int)g_fFPS;

const int g_iWalkTopSpeedFrame = (int)g_fFPS / 10;
const int g_iRotTopSpeedFrame = (int)g_fFPS / 2;
const int g_iBoostTopSpeedFrame = (int)g_fFPS;
const int g_iBoostRisingyTopSpeedFrame = (int)g_fFPS / 4;//ブースト上昇加速時間.

const int g_iStabilityVariationRange = 3;//安定性能などで減衰するステータスが最低値から何倍分の変動をするか.

const int g_iBoostResDec = 10;//ブースト展開中.の落下速度減衰の度合.
const int g_iHeadLockSpeedReference = 500;//頭パーツのロック速度の基準値、これより低いとロック時間が長くなる.

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
	enAnimNoLegJumpDown,
	enAnimNoLegJumpEnd,
	//enAnimNoLegDown
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

	m_iMaxHP = pRobo->GetRoboState(clsROBO_STATUS::HP);//HP受け取り.
	m_iMaxHP = 10000;
	m_iHP = m_iMaxHP;//現在HPを最大値で初期化.
	
	//歩行最高速度.
	m_fWalktMoveSpeedMax = pRobo->GetRoboState(clsROBO_STATUS::WALK_SPD) * g_fDistanceReference;
	//歩行加速時間.
	m_iWalkTopSpeedFrame = g_iWalkTopSpeedFrame + (g_iWalkTopSpeedFrame * g_iStabilityVariationRange) * (pRobo->GetRoboState(clsROBO_STATUS::STABILITY) * g_fPercentage);

	//回転最高速と加速時間設定.
	SetRotAcceleSpeed(pRobo->GetRoboState(clsROBO_STATUS::TURN)* g_fDirectionReference,
		g_iRotTopSpeedFrame + ((g_iRotTopSpeedFrame * g_iStabilityVariationRange) * (pRobo->GetRoboState(clsROBO_STATUS::STABILITY) * g_fPercentage)));

	//ジャンプ力.
	SetJumpPower(pRobo->GetRoboState(clsROBO_STATUS::JUMP_POWER) * g_fDistanceReference);

	//エネルギー最大値.
	m_iEnelgy = m_iEnelgyMax = pRobo->GetRoboState(clsROBO_STATUS::EN_CAPA);
	//エネルギー回復量.
	m_iEnelgyOutput = pRobo->GetRoboState(clsROBO_STATUS::EN_OUTPUT) / static_cast<int>(g_fFPS);
	//浮遊時エネルギー回復量(通常エネルギーの半分).
	m_iBoostFloatRecovery = m_iEnelgyOutput / iHulf;
	
	//ブースト移動速度.
	m_fBoostMoveSpeedMax = pRobo->GetRoboState(clsROBO_STATUS::BOOST_THRUST_H) * g_fDistanceReference;
	//ブースト加速時間.
	m_iBoostTopSpeedFrame = g_iBoostRisingyTopSpeedFrame + (g_iWalkTopSpeedFrame * g_iStabilityVariationRange) * (pRobo->GetRoboState(clsROBO_STATUS::STABILITY) * g_fPercentage);
	//ブースト展開中のEN消費.
	m_iBoostMoveCost = pRobo->GetRoboState(clsROBO_STATUS::BOOST_COST_H);

	//ブースト上昇速度.
	m_fBoostRisingSpeedMax = pRobo->GetRoboState(clsROBO_STATUS::BOOST_THRUST_V) * g_fDistanceReference;
	//ブースト上昇EN消費率.
	m_iBoostRisingyCost = pRobo->GetRoboState(clsROBO_STATUS::BOOST_COST_V);

	//ブースト上昇加速時間.
	m_iBoostRisingTopSpeedFrame = g_iBoostRisingyTopSpeedFrame;
	//ブースト上昇加速量.
	m_fBoostRisingAccele = m_fBoostRisingSpeedMax / g_iBoostRisingyTopSpeedFrame;

	//ブースト展開中に下に落ちる速度.
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
		//float型はintで入ってきたステータスにあれこれして計算する.

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

		//腕の照準精度と武器自体の射撃精度で集団率を設定.
		WS[i].iStablity = (
			(pRobo->GetWeaponState(ucEquipWeaponNum, clsROBO_STATUS::enWEAPON_STATE::SHOT_STABILITY) + 
			pRobo->GetRoboState(clsROBO_STATUS::AIMING)) 
			/ iHulf);
	}

	WeaponInit(pPtrGroup, WS, enWeaponTypeSize);

	SetBoostEffect();

	//m_fLockRange = 500.0f;//ロックオン距離.
	m_fLockCircleRadius = 500.0f;//ロックオン判定の半径.

	m_pViewPort = pPtrGroup->GetViewPort10();

	m_pMesh->PartsAnimChange(enPARTS::ARM_R, 3);
	m_pMesh->SetAnimSpd(0.0f);
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
		Jump();
	}
}

void clsRobo::SetDirQuickBoost(const float fAngle)
{
	//クイックブーストするため、強制的に移動方向を決定.
	if (IsMoveControl())
	{
		D3DXVECTOR3 vForward;

		//今向いている方向.
		vForward = GetVec3Dir(m_Trans.fYaw, g_vDirForward);

		//行きたい方向.
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
	m_vAcceleDir = { 0.0f, 0.0f, 0.0f };//ブースターエフェクト発生に使っているので毎フレームの初期化が必要になる.

	if (m_iQuickBoostDecStartTime > 0)//クイックブースト.
	{
		m_fMoveSpeed = m_fQuickBoostSpeedMax;
		m_iQuickBoostDecStartTime--;
	}

	if (m_iQuickTrunDecStartTime > 0)//クイックターン.
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

	
}

void clsRobo::UpdataLimitTime()
{
	if (m_iActivityLimitTime < 0)
	{
		m_bTimeUp = true;
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

	//ブースト展開中.
	if (m_bBoost)
	{
		//浮遊時.
		if (!m_bGround)
		{
			//EN回復を落とす.
			m_iEnelgyRecoveryPoint -= m_iBoostFloatRecovery;
		}

		m_iEnelgyRecoveryPoint -= m_iBoostMoveCost;
	}

	if (false)//射撃準備完了.
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
			//EN消費.
			EnelgyConsumption(m_v_pWeapons[enWeaponLHand]->GetShotEN());

			//射撃アニメ処理.


		}

		else
		{
			if (Reload())
			{
				//リロードアニメ処理.
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
			//EN消費.
			EnelgyConsumption(m_v_pWeapons[enWeaponRHand]->GetShotEN());

			//射撃アニメ処理.
		}

		else
		{
			if (Reload())
			{
				//リロードアニメ処理.
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
	clsOPERATION_STRING OprtStr;//ボーン名と番号を繋げる役割.

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
			//付け根の名前を生成.
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
			//付け根の名前を生成.
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
	clsOPERATION_STRING OprtStr;//ボーン名と番号を繋げる役割.

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
			//付け根の名前を生成.
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
	clsOPERATION_STRING OprtStr;//ボーン名と番号を繋げる役割.

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
			//付け根の名前を生成.
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
	clsOPERATION_STRING OprtStr;//ボーン名と番号を繋げる役割.

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
			//付け根の名前を生成.
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
			//付け根の名前を生成.
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
			//付け根の名前を生成.
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
	clsOPERATION_STRING OprtStr;//ボーン名と番号を繋げる役割.

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
			//付け根の名前を生成.
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

void clsRobo::SetRotateHeadPart()
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

void clsRobo::SetRotateArmPart()
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

void clsRobo::SetRotateCorePart()
{
	D3DXVECTOR3 vTmp = GetRotation();
	vTmp.y += static_cast<float>(D3DX_PI);
	ObjRollOverGuard(&vTmp.y);

	m_pMesh->SetPartsRotate(enPARTS::CORE, vTmp);
}

void clsRobo::SetRotateLegPart()
{
	D3DXVECTOR3 vTmp = GetRotation();

	const float fHulfDir = D3DX_PI / 2;

	const float fVecX = m_vMoveDirforBoost.x;
	const float fVecZ = m_vMoveDirforBoost.z;

	float fRot = atan2f(fVecX, fVecZ);

	if (abs(fRot) > fHulfDir)
	{
		fRot -= D3DX_PI * (abs(fRot) / fRot);
	}

	vTmp.y += fRot;

	vTmp.y += static_cast<float>(D3DX_PI);
	ObjRollOverGuard(&vTmp.y);

	D3DXVECTOR3 vLegRot = vTmp;

	m_pMesh->SetPartsRotate(enPARTS::LEG, vLegRot);
}

void clsRobo::AnimUpdate()
{

}

void clsRobo::AnimUpdateLeg()
{
	const enAnimNoLeg iAnimNo = static_cast<enAnimNoLeg>(m_pMesh->GetPartsAnimNo(enPARTS::LEG));

	switch (iAnimNo)
	{
	default:
		break;
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
	//消すときdeleteしないでnullしてね.
	m_wpSound = nullptr;
	m_wpEffects = nullptr;
	m_wpResource = nullptr;
#endif//#ifdef Tahara
}