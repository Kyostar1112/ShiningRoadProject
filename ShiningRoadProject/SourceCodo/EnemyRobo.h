#pragma once

#include"Enemy.h"
#include"Robo.h"

#define sShot

class clsEnemyRobo : public clsRobo
{
public:
	clsEnemyRobo();
	virtual ~clsEnemyRobo();

	void Action();
	
	bool IsQuickTurn();//�^�[�Q�b�g�ʒu�̕��������ʂ�����ȏ㗣��Ă��ꍇ�A�N�C�b�N�^�[�����g�p.
	bool IsQuickBoostApproach();//�N�C�b�N�u�[�X�g���g�p���A�^�[�Q�b�g�Ƃ̋������l�߂�.
	
	bool IsQuickBoostAvoid();//�N�C�b�N�u�[�X�g�ɂ����.

	bool IsQuickBoostAvoidtoRockTime();
	bool IsQuickBoostAvoidtoDamage();

	bool IsShotR();
	bool IsShotL();



private:

};

clsEnemyRobo::clsEnemyRobo()
{
}

clsEnemyRobo::~clsEnemyRobo()
{
}