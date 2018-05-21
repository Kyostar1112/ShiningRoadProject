#pragma once

#include "SceneClass.h"
#include "SceneTitle.h"
#include "SceneAssemble.h"
#include "SceneMission.h"
#include "SceneEnding.h"


class clsCAMERA_BASE;

//���N���X.
class clsFACTORY
{
public:
	//�����̓V�[���̏������ɕK�v�Ȃ���.
	clsFACTORY( clsPOINTER_GROUP* const ptrGroup );
	virtual ~clsFACTORY();
	//�O����g���K��.
	//�V�[���̃|�C���^�Ɂunew�v�̑���Ɏg��.
	clsSCENE_BASE* Create( 
		const enSCENE enScene );


private:
	//���g.
	virtual clsSCENE_BASE* CreateProduct( 
		const enSCENE enScene ) = 0;



};



//�ugameMgr�v�ŃV�[�������N���X.
class clsSCENE_FACTORY : public clsFACTORY
{
public:
	clsSCENE_FACTORY( 
		clsPOINTER_GROUP* const ptrGroup );
	~clsSCENE_FACTORY() override;
private:
	//���g.
	clsSCENE_BASE* CreateProduct( 
		const enSCENE flg ) final;
	//�����Ƃ�delete���Ȃ���null���Ă�.
	clsPOINTER_GROUP* m_wpPtrGroup;

};

