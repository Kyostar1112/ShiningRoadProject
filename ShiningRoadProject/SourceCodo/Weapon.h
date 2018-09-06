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
	int iShotEN;
	
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
	bool Shot();

	int Hit(std::vector<clsObject::SPHERE> v_TargetSphere);
	
	void Reload();

	bool IsNeedReload();//�c�e�����邩�Ŏˌ��������[�h���𔻒�.

	bool IsLock();

	void Lock(clsObject* pTargetObj = nullptr);//���b�N�͈͂ɓ����Ă��邩�m�F.
	void LockOut();//���b�N�������.

	int GetNowBulletNum();
	int GetMaxBulletNum();

	int GetShotEN() const;

private:
	WeaponState m_State;

	clsObject* m_pTargetObj;

	clsShot** m_ppBullet;
	int m_iRemainingBullet;

	int m_iReloadCnt;
	int m_iLockTime;

	clsPOINTER_GROUP* m_pPtrGroup;
};

