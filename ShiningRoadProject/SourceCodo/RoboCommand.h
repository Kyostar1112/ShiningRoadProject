#pragma once

#include"Robo.h"
#include"CharactorCommand.h"

class clsRoboCommand : public clsCharactorCommand
{
public:
	clsRoboCommand() {};
	~clsRoboCommand() {};

	//�{�^������.
	virtual void PushBotton(clsRobo* pRobo)
	{

	};

	//�{�^������.
	virtual void Trigger(clsRobo* pRobo, const float fS, const float fAngle)
	{

	};
};

class clsCommandBoostRising : public clsRoboCommand
{
public:
	virtual void PushBotton(clsRobo* pRobo)
	{
		pRobo->BoostRising();
	}
};

class clsCommandMoveSwitch : public clsRoboCommand
{
public:
	virtual void PushBotton(clsRobo* pRobo)
	{
		pRobo->MoveSwitch();
	}
};

class clsCommandQuickBoost : public clsRoboCommand
{
public:
	virtual void PushBotton(clsRobo* pRobo)
	{
		pRobo->QuickBoost();
	}
};