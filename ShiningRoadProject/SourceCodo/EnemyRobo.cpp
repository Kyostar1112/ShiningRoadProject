#include"EnemyRobo.h"
#include"File.h"

void clsEnemyRobo::Init(
	LPSTR strEnemyFolderName,
	clsRobo* pRobo)
{
	m_pBody = pRobo;
	m_pChara = m_pBody;

	m_UpdateState.iHorDirResult = 0;
	m_UpdateState.vHorMovePos = { 0.0f, 0.0f, 0.0f };

	ShotState SSTmp;
	SSTmp.iShotDisMax = 50.0f;
	SSTmp.iShotDisMin = 1.0f;

	MoveState MSTmp;
	MSTmp.iHorDisRandMax = 500;
	MSTmp.iHorDistance = 100;
	MSTmp.iMoveDir = 0;
	MSTmp.iMoveDirRandMax = 0;
	MSTmp.iVerDistance = 100;
	MSTmp.iVerDistRandMax = 20;

	m_BoostState.iENLimitParcent = 30;
	m_BoostState.iRisingENParcent = 70;
	m_bENSaving = false;

	m_v_LShotState.push_back(SSTmp);

	m_v_RShotState.push_back(SSTmp);

	m_v_MoveState.push_back(MSTmp);

	m_v_QuickBoostAvoidState.resize(2);


	for (unsigned int i = 0; i < m_v_QuickBoostAvoidState.size(); i++)
	{
		m_v_QuickBoostAvoidState[i].iAvoidNum = i;
		m_v_QuickBoostAvoidState[i].iUpdateTime = 300 * (int)g_fFPS;
		m_v_QuickBoostAvoidState[i].iLockTimeorDamage = 5;
		m_v_QuickBoostAvoidState[i].iAvoidDir = 45;

		m_v_QuickBoostAvoidState[i].iAvoidDamageUpdateTime = m_v_QuickBoostAvoidState[i].iUpdateTime;
		m_v_QuickBoostAvoidState[i].iDamage = 0;
		m_v_QuickBoostAvoidState[i].iLockTime = m_v_QuickBoostAvoidState[i].iLockTimeorDamage* (int)g_fFPS;
	}
}

bool clsEnemyRobo::IsBoostRising()
{
	IsENSaving();

	if (!m_bENSaving)
	{
		if (m_pTarget)
		{
			MoveState MoveStatus = m_v_MoveState[m_UpdateState.iMoveCategoryNo];

			int iVerDestDis = MoveStatus.iVerDistance;

			int iRandMax = 0;
			iRandMax = MoveStatus.iVerDistRandMax;

			const int iHulf = 2;

			if (iRandMax != 0)//0���Ǝ~�܂�̂Ŗh�~.
			{
				iVerDestDis += (rand() % (iRandMax * iHulf)) - iRandMax;
			}

			m_UpdateState.fVerDis = iVerDestDis * g_fDistanceReference;

			float fDist = m_pTarget->GetPosition().y - m_pChara->GetPosition().y;

			if (fDist > -m_UpdateState.fVerDis * iHulf &&
				fDist < m_UpdateState.fVerDis * iHulf)
			{
				return true;
			}

			else
			{
				if (fDist > 0.0f)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void clsEnemyRobo::IsENSaving()
{
	int iENLimit;

	if (m_bENSaving)
	{
		iENLimit = static_cast<int>(m_pBody->m_iEnelgyMax * (m_BoostState.iRisingENParcent * g_fPercentage));

		if (m_pBody->m_iEnelgy > iENLimit)
		{
			m_bENSaving = false;
		}
	}

	else
	{
		iENLimit = static_cast<int>(m_pBody->m_iEnelgyMax * (m_BoostState.iENLimitParcent * g_fPercentage));

		if (m_pBody->m_iEnelgy < iENLimit)
		{
			m_bENSaving = true;
		}
	}
}

bool clsEnemyRobo::IsBoostOn()
{
	if (m_pTarget)
	{
		float fVerDis = m_pTarget->GetPosition().y - m_pBody->GetPosition().y;

		const int iHulf = 2;

		float fVerDestDis = m_UpdateState.fVerDis + (m_UpdateState.fVerDis / iHulf);

		if (fVerDis > 0.0f)//�G����ɂ���.
		{
			int iENLimit = iHulf;//static_cast<int>(m_pBody->m_iEnelgyMax * (m_MoveData.v_MoveState[m_iMoveCategoryNo].iVerMoveENLimitParcent * g_fPercentage));

			if (m_pBody->m_iEnelgy > iENLimit)//EN�c�ʂ��\���ɂ���.
			{
				return true;
			}
		}
	}

	return false;
}

bool clsEnemyRobo::IsBoostOff()
{
	if (m_pTarget)
	{
		float fVerDis = m_pTarget->GetPosition().y - m_pBody->GetPosition().y;

		const int iHulf = 2;

		float fVerDestDis = m_UpdateState.fVerDis + (m_UpdateState.fVerDis / iHulf);

		if (fVerDis < 0.0f)//�G�����ɂ���.
		{
			if (abs(fVerDis) > abs(fVerDestDis))//�G�Ƃ̍����̍����傫������.
			{
				return true;
			}
		}

		int iENLimit = static_cast<int>(m_pBody->m_iEnelgyMax * 0.3f);//(m_MoveData.v_MoveState[m_iMoveCategoryNo].iVerMoveENLimitParcent * g_fPercentage));

		if (m_pBody->m_iEnelgy < (m_pBody->m_iEnelgyMax / iHulf))//EN�c�ʂ����Ȃ�.
		{
			return true;
		}
	}

	return false;
}

bool clsEnemyRobo::IsQuickTurn(float& fPush, float& fAngle)//�^�[�Q�b�g�ʒu�̕��������ʂ�����ȏ㗣��Ă��ꍇ�A�N�C�b�N�^�[�����g�p.
{
	fPush = 0.0f;
	fAngle = 0.0f;

	if (m_pTarget)
	{
		const float fVecX = m_pTarget->GetPosition().x - m_pBody->GetPosition().x;
		const float fVecZ = m_pTarget->GetPosition().z - m_pBody->GetPosition().z;

		float fRot = atan2f(fVecX, fVecZ) - m_pBody->GetRotation().y;

		int iDirHulf = 180;
		int iDirFull = 360;

		if (fRot > static_cast<float>D3DXToRadian(iDirHulf))
		{
			fRot -= static_cast<float>D3DXToRadian(iDirFull);
		}
		else if (fRot < -static_cast<float>D3DXToRadian(iDirHulf))
		{
			fRot += static_cast<float>D3DXToRadian(iDirFull);
		}

		ObjRollOverGuard(&fRot);

		if (abs(fRot) > D3DXToRadian(150))
		{
			const float fPushFull = 1.0f;

			if (fRot > 0.0f)
			{
				fPush = fPushFull;
			}

			else
			{
				fPush = -fPushFull;
			}

			fAngle = fRot;

			return true;
		}
	}

	return false;
}

bool clsEnemyRobo::IsQuickBoostApproach(float& fPush, float& fAngle)//�N�C�b�N�u�[�X�g���g�p���A�^�[�Q�b�g�Ƃ̋������l�߂�.
{
	fPush = 0.0f;
	fAngle = 0.0f;

	if (m_pTarget)
	{
		float fDis = D3DXVec3Length(&(m_pTarget->GetPosition() - m_pBody->GetPosition()));

		if (fDis > 300.0f)
		{
			fPush = 1.0f;

			const float fVecX = m_UpdateState.vHorMovePos.x - m_pChara->GetPosition().x;
			const float fVecZ = m_UpdateState.vHorMovePos.z - m_pChara->GetPosition().z;

			float fRot = atan2f(fVecX, fVecZ) - m_pChara->GetRotation().y;

			ObjRollOverGuard(&fRot);

			fAngle = fRot;

			return true;
		}
	}

	return false;
}

bool clsEnemyRobo::IsQuickBoostAvoid(float& fPush, float& fAngle)//�N�C�b�N�u�[�X�g�ɂ����.
{
	fPush = 0.0f;
	fAngle = 0.0f;

	//��������ǂꂩ�𖞂����Ή��.
	//�����͐�ɓo�^���ꂽ���̂���D�悵�Ĕ���.

	for (unsigned int i = 0; i < m_v_QuickBoostAvoidState.size(); i++)
	{
		switch (m_v_QuickBoostAvoidState[i].iAvoidNum)//����p�^�[��.
		{
		case enAvoidLockTime:
			if (IsQuickBoostAvoidtoLockTime(m_v_QuickBoostAvoidState[i], fPush, fAngle))//�탍�b�N����.
			{
				return true;
			}
			break;

		case enAvoidDamage:
			if (IsQuickBoostAvoidtoDamage(m_v_QuickBoostAvoidState[i], fPush,fAngle))//��_���[�W.
			{
				return true;
			}
			break;

		default:
			break;
		}
	}

	return false;
}

bool clsEnemyRobo::IsQuickBoostAvoidtoLockTime(QuickBoostAvoid& AvoidState, float& fPush, float& fAngle)
{
	if (AvoidState.iLockTime > 0)
	{
		AvoidState.iLockTime--;
	}

	else
	{
		AvoidState.iLockTime = AvoidState.iLockTimeorDamage * static_cast<int>(g_fFPS);

		fPush = 1.0f;

		const float fVecX = m_UpdateState.vHorMovePos.x - m_pChara->GetPosition().x;
		const float fVecZ = m_UpdateState.vHorMovePos.z - m_pChara->GetPosition().z;

		float fRot = atan2f(fVecX, fVecZ) - m_pChara->GetRotation().y;

		fRot += static_cast<float>(D3DXToRadian(AvoidState.iAvoidDir));

		ObjRollOverGuard(&fRot);

		fAngle = fRot;

		return true;
	}

	if (!m_pBody->m_bRadarWarning)
	{
		AvoidState.iLockTime = AvoidState.iLockTimeorDamage * static_cast<int>(g_fFPS);
	}

	else
	{
		int y = 0;
	}

	return false;
}

bool clsEnemyRobo::IsQuickBoostAvoidtoDamage(QuickBoostAvoid& AvoidState, float& fPush, float& fAngle)
{
	if (AvoidState.iAvoidDamageUpdateTime > 0)
	{
		AvoidState.iDamage += m_pBody->m_iDamage;
		if (AvoidState.iDamage > AvoidState.iLockTimeorDamage)
		{
			AvoidState.iDamage = 0;//�󂯂��_���[�W�̏�����.

			fPush = 1.0f;

			const float fVecX = m_UpdateState.vHorMovePos.x - m_pChara->GetPosition().x;
			const float fVecZ = m_UpdateState.vHorMovePos.z - m_pChara->GetPosition().z;

			float fRot = atan2f(fVecX, fVecZ) - m_pChara->GetRotation().y;

			fRot += static_cast<float>(D3DXToRadian(AvoidState.iAvoidDir));

			ObjRollOverGuard(&fRot);

			fAngle = fRot;

			return true;
		}

		AvoidState.iAvoidDamageUpdateTime--;
	}

	else
	{

		AvoidState.iAvoidDamageUpdateTime = AvoidState.iUpdateTime;
		AvoidState.iDamage = 0;
	}

	return false;
}

bool clsEnemyRobo::IsShotR()
{
	m_v_ShotState = m_v_RShotState;

	if (IsShot())
	{
		return true;
	}

	return false;
}

bool clsEnemyRobo::IsShotL()
{
	m_v_ShotState = m_v_LShotState;

	if (IsShot())
	{
		return true;
	}

	return false;
}

clsRoboCommand* clsEnemyRobo::MoveOperation(float& fPower, float& fAngle)
{
	if (SetMoveDir(fPower, fAngle))
	{
		return m_pComMove;
	}

	return nullptr;
}

clsRoboCommand* clsEnemyRobo::MoveSwitchOperation()
{
	if (m_pBody->m_bBoost)
	{
		if (IsBoostOff())
		{
			return m_pComMoveSwitch;
		}
	}

	else
	{
		if (IsBoostOn())
		{
			return m_pComMoveSwitch;
		}
	}

	return nullptr;
}

clsRoboCommand* clsEnemyRobo::RotateOperation(float& fPower, float& fAngle)
{
	if (SetRotate(fPower,fAngle))
	{
		return m_pComRotate;
	}

	return nullptr;
}

clsRoboCommand* clsEnemyRobo::LookOperation(float& fPower, float& fAngle)
{
	if (SetLook(fPower, fAngle))
	{
		return m_pComLook;
	}

	return nullptr;
}

clsRoboCommand* clsEnemyRobo::QuickTurnOperation(float& fPower, float& fAngle)
{
	if (IsQuickTurn(fPower, fAngle))
	{
		return m_pComQuickTrun;
	}

	return nullptr;
}

clsRoboCommand* clsEnemyRobo::QuickBoostOperation(float& fPower, float& fAngle)
{
	if (IsQuickBoostAvoid(fPower, fAngle))
	{
		return m_pComQuickBoost;
	}

	if (IsQuickBoostApproach(fPower, fAngle))
	{
		return m_pComQuickBoost;
	}

	return nullptr;
}

clsRoboCommand* clsEnemyRobo::BoostOperation()
{
	if (IsBoostRising())
	{
		return m_pComBoost;
	}

	return nullptr;
}

clsRoboCommand* clsEnemyRobo::LShotOperation()
{
	if (IsShotL())
	{
		return m_pComLShot;
	}

	return nullptr;
}

clsRoboCommand* clsEnemyRobo::RShotOperation()
{
	if (IsShotR())
	{
		return m_pComRShot;
	}

	return nullptr;
}

void clsEnemyRobo::SetShotData()
{
	std::string strShotLDataName = m_BaseState.strEnemyFolderName + "\\ShotL.csv";

	clsFILE File;
	if (File.Open(strShotLDataName))
	{
		m_v_LShotState.resize(File.GetSizeRow());

		for (int i = 0; i < m_v_LShotState.size(); i++)
		{
			m_v_LShotState[i].iShotDisMax = File.GetDataInt(i, enShotStateShotDisMax);
			m_v_LShotState[i].iShotDisMin = File.GetDataInt(i, enShotStateShotDisMin);

			m_v_LShotState[i].iShotENLimitParcent = File.GetDataInt(i, enShotStateShotENLimitParcent);
		}

		File.Close();
	}

	std::string strShotRDataName = m_BaseState.strEnemyFolderName + "\\ShotR.csv";

	if (File.Open(strShotRDataName))
	{
		m_v_RShotState.resize(File.GetSizeRow());

		for (int i = 0; i < m_v_RShotState.size(); i++)
		{
			m_v_RShotState[i].iShotDisMax = File.GetDataInt(i, enShotStateShotDisMax);
			m_v_RShotState[i].iShotDisMin = File.GetDataInt(i, enShotStateShotDisMin);

			m_v_RShotState[i].iShotENLimitParcent = File.GetDataInt(i, enShotStateShotENLimitParcent);
		}

		File.Close();
	}
}

void clsEnemyRobo::SetBoostData()
{
	std::string strBoostDataName = m_BaseState.strEnemyFolderName + "\\Boost.csv";

	clsFILE File;
	if (File.Open(strBoostDataName))
	{
		m_BoostState.iENLimitParcent = File.GetDataInt(0,enBoostENLimitParcent);
		m_BoostState.iRisingENParcent = File.GetDataInt(0, enBoostRisingENParcent);

		File.Close();
	}
}

void clsEnemyRobo::SetQuickBoostAppData()
{
	std::string strQuickBoostAppDataName = m_BaseState.strEnemyFolderName + "\\QuickBoostApp.csv";

	clsFILE File;
	if (File.Open(strQuickBoostAppDataName))
	{
		m_v_QuickAppState.resize(File.GetSizeRow());

		for (int i = 0; i < m_v_MoveState.size(); i++)
		{
			m_v_QuickAppState[i].iUpdateTime = File.GetDataInt(i, enQuickBoostAppUpdateTime);

			m_v_QuickAppState[i].iDis = File.GetDataInt(i, enQuickBoostAppDis);
			m_v_QuickAppState[i].iENLimit = File.GetDataInt(i, enQuickBoostAppENLimit);
		}

		File.Close();
	}
}

void clsEnemyRobo::SetQuickTrunData()
{
	std::string strQuickTrunDataName = m_BaseState.strEnemyFolderName + "\\QuickTrun.csv";

	clsFILE File;
	if (File.Open(strQuickTrunDataName))
	{
		m_v_QuickTrunState.resize(File.GetSizeRow());

		for (int i = 0; i < m_v_MoveState.size(); i++)
		{
			m_v_QuickTrunState[i].iUpdateTime = File.GetDataInt(i, enQuickTrunUpdateTime);

			m_v_QuickTrunState[i].iDir = File.GetDataInt(i, enQuickTrunDir);
			m_v_QuickTrunState[i].iENLimit = File.GetDataInt(i, enQuickTrunENLimit);
		}

		File.Close();
	}
}

void clsEnemyRobo::SetQuickBoostAvoidData()
{
	std::string strQuickBoostAvoidDataName = m_BaseState.strEnemyFolderName + "\\QuickBoostAvoid.csv";

	clsFILE File;
	if (File.Open(strQuickBoostAvoidDataName))
	{
		m_v_QuickBoostAvoidState.resize(File.GetSizeRow());

		for (int i = 0; i < m_v_QuickBoostAvoidState.size(); i++)
		{
			m_v_QuickBoostAvoidState[i].iUpdateTime;
			m_v_QuickBoostAvoidState[i].iAvoidNum;
			m_v_QuickBoostAvoidState[i].iLockTimeorDamage;
			m_v_QuickBoostAvoidState[i].iAvoidDir;
			m_v_QuickBoostAvoidState[i].iENLimit;
		}

		File.Close();
	}
}

void clsEnemyRobo::SetDataProduct()
{

}

clsEnemyRobo::clsEnemyRobo()
{
	m_pComMove = new clsCommandMove;
	m_pComMoveSwitch = new clsCommandMoveSwitch;
	m_pComRotate = new clsCommandRotate;
	m_pComLook = new clsCommandLookVerMove;

	m_pComQuickBoost = new clsCommandQuickBoost;
	m_pComQuickTrun = new clsCommandQuickTurn;
	m_pComBoost = new clsCommandBoostRising;

	m_pComLShot = new clsCommandLShot;
	m_pComRShot = new clsCommandRShot;
}

clsEnemyRobo::~clsEnemyRobo()
{
	delete m_pComMove;
	delete m_pComMoveSwitch;
	delete m_pComRotate;
	delete m_pComLook;
	
	delete m_pComQuickBoost;
	delete m_pComQuickTrun;
	delete m_pComBoost;
	
	delete m_pComLShot;
	delete m_pComRShot;
}