#include"EnemyRobo.h"

void clsEnemyRobo::Init(
	LPSTR strEnemyFolderName,
	clsCharactor* pChara,
	std::vector<clsCharactor*> v_pEnemys)
{

}

void clsEnemyRobo::Action()
{

}

bool clsEnemyRobo::IsQuickTurn()//�^�[�Q�b�g�ʒu�̕��������ʂ�����ȏ㗣��Ă��ꍇ�A�N�C�b�N�^�[�����g�p.
{


	return false;
}

bool clsEnemyRobo::IsQuickBoostApproach()//�N�C�b�N�u�[�X�g���g�p���A�^�[�Q�b�g�Ƃ̋������l�߂�.
{


	return false;
}

bool clsEnemyRobo::IsQuickBoostAvoid()//�N�C�b�N�u�[�X�g�ɂ����.
{


	return false;
}

bool clsEnemyRobo::IsQuickBoostAvoidtoRockTime()
{


	return false;
}

bool clsEnemyRobo::IsQuickBoostAvoidtoDamage()
{


	return false;
}

bool clsEnemyRobo::IsShotR()
{


	return false;
}

bool clsEnemyRobo::IsShotL()
{


	return false;
}

clsRoboCommand* clsEnemyRobo::MoveOperation(float& fPower, float& fAngle)
{


	return nullptr;
}

clsRoboCommand* clsEnemyRobo::MoveSwitchOperation()
{


	return nullptr;
}

clsRoboCommand* clsEnemyRobo::RotateOperation(float& fPower, float& fAngle)
{


	return nullptr;
}

clsRoboCommand* clsEnemyRobo::LookOperation(float& fPower, float& fAngle)
{


	return nullptr;
}

clsRoboCommand* clsEnemyRobo::QuickTurnOperation()
{


	return nullptr;
}

clsRoboCommand* clsEnemyRobo::QuickBoostOperation()
{


	return nullptr;
}

clsRoboCommand* clsEnemyRobo::BoostOperation()
{


	return nullptr;
}

clsRoboCommand* clsEnemyRobo::LShotOperation()
{


	return nullptr;
}

clsRoboCommand* clsEnemyRobo::RShotOperation()
{


	return nullptr;
}

clsEnemyRobo::clsEnemyRobo()
{
}

clsEnemyRobo::~clsEnemyRobo()
{
}