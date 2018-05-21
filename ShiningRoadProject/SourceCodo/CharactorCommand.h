#pragma once

#include"Charactor.h"

class clsCharactorCommand
{
public:
	clsCharactorCommand(){};
	~clsCharactorCommand(){};

	//�{�^������.
	virtual void PushBotton(clsCharactor* pChara)
	{

	};

	//�{�^������.
	virtual void Trigger(clsCharactor* pChara, const float fS, const float fAngle)
	{

	};
};

class clsCommandRS : public clsCharactorCommand
{
public:
	virtual void Trigger(clsCharactor* pChara, const float fS, const float fAngle)
	{
		pChara->Rotate(fAngle, fS);
	}

};

class clsCommandLS : public clsCharactorCommand
{
public:
	virtual void Trigger(clsCharactor* pChara,const float fS,const float fAngle)
	{ 
		pChara->Move(fAngle,fS);
	}
};

class clsCommandJump : public clsCharactorCommand
{
public:
	virtual void PushBotton(clsCharactor* pChara)
	{
		pChara->Jump();
	}
};


