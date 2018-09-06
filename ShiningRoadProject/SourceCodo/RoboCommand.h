//#pragma once
#ifndef ROBOCOMMAND
#define ROBOCOMMAND

#include"Robo.h"

class clsRoboCommand
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
	virtual void Trigger(clsRobo* pRobo, const float fS, const float fAngle)
	{
		pRobo->SetDirQuickBoost(fAngle);
	}

	virtual void PushBotton(clsRobo* pRobo)
	{
		pRobo->QuickBoost();
	}
};

class clsCommandQuickTurn : public clsRoboCommand
{
public:
	virtual void Trigger(clsRobo* pRobo, const float fS, const float fAngle)
	{
		pRobo->SetDirQuickTurn(fAngle);
	}

	virtual void PushBotton(clsRobo* pRobo)
	{
		pRobo->QuickTurn();
	}
};

class clsCommandRotate : public clsRoboCommand
{
public:
	virtual void Trigger(clsRobo* pRobo, const float fS, const float fAngle)
	{
		pRobo->AddRotAccele(fAngle, fS);
	}

};

class clsCommandMove : public clsRoboCommand
{
public:
	virtual void Trigger(clsRobo* pRobo, const float fS, const float fAngle)
	{
		pRobo->AddMoveAccele(fAngle, fS);
	}
};

class clsCommandLookVerMove : public clsRoboCommand
{
public:
	virtual void Trigger(clsRobo* pRobo, const float fS, const float fAngle)
	{
		pRobo->LookUp(fAngle, fS);
	}
};

class clsCommandLShot : public clsRoboCommand
{
public:
	virtual void PushBotton(clsRobo* pRobo)
	{
		pRobo->ShotLWeapon();
	}
};

class clsCommandRShot : public clsRoboCommand
{
public:
	virtual void PushBotton(clsRobo* pRobo)
	{
		pRobo->ShotRWeapon();
	}
};

#endif//#ifndef ROBOCOMMAND