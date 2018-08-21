#pragma once

#include"Shot.h"

//�ˌ����s�����߂̏�����������N���X.

struct WeaponState
{
	BulletState  BState;
	ShootingState SState;

	int iAtk;
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
	void Update();
	bool Shot(clsObject* pTargetObj = nullptr);

	int Hit(
		std::vector<clsObject::SPHERE> const v_TargetSphere);
	
	void Reload();

	bool IsNeedReload();//�c�e�����邩�Ŏˌ��������[�h���𔻒�.

	bool IsRock();
	bool IsRockRange();

private:
	WeaponState m_State;

	clsShot** m_ppBullet;
	int m_iRemainingBullet;

	int m_iReloadCnt;

	clsPOINTER_GROUP* m_pPtrGroup;
};

