#pragma once

#include"Shot.h"

//�ˌ����s�����߂̏�����������N���X.

struct WeaponState
{
	BulletState  BState;
	ShootingState SState;

	int iReloadTime;
	int iLockSpeed;
	float iLockRange;

	int iStablity;//Robo��Arm�̏Ə����x�Ƃ̌v�Z���ʂ����Ă�������.

	int MagazineReloadTime;
	int iBulletNumMax;
};

class clsWeapon
{
public:
	clsWeapon(clsPOINTER_GROUP* pPtrGroup);
	~clsWeapon();

	void Create(WeaponState State);
	void Updata();
	bool Shot(clsObject* pTargetObj = nullptr);//true : �ˌ�����,false : �e���Ȃ��̂Ń����[�h.
	void Reload();

	clsObject** GetBulletObjs(int& iBulletNumMax) const;

private:
	WeaponState m_State;

	clsShot** m_ppBullet;
	int m_iRemainingBullet;

	clsPOINTER_GROUP* m_pPtrGroup;
};

