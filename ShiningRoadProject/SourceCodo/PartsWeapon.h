#ifndef PARTS_WEAPON_H_
#define PARTS_WEAPON_H_


#include "PartsBase.h"


class clsPARTS_WEAPON : public clsPARTS_BASE
{
public:
	clsPARTS_WEAPON();
	~clsPARTS_WEAPON();

	//ステータス変数の添え字.
	enum enSTATUS : PARTS_STATUS_TYPE
	{
		ATK = 0,			//攻撃力.
		BULLET_SPD,			//弾速.
		RANGE,				//射程距離.
		COST,				//消費エネルギー.
		LOAD_TIME,			//装填時間.
		LOCK_ON_TIME,		//ロック時間.
		STABILITY,			//射撃安定.
		MAGAZINE_LOAD_TIME,	//マガジン装填時間.
		BULLETS_NUM,		//装弾数.

		COL_SIZE,	//弾の当たり判定サイズ.
		EFC_BULLET,	//弾本体のエフェクト.
		EFC_LOCUS,	//弾の軌跡のエフェクト.
		EFC_HIT,	//着弾のエフェクト.
		EFC_CARTRIDGE,//薬莢エフェクト.
		SE_FIER,	//発射SE.
		SE_HIT,		//着弾のSE.

		size
	};



private:
	//----- 各パーツごとの関数 -----//.
	void CreateProduct() final;//各シーンのCreate.
	void UpdateProduct() final;//各シーンのUpdate.
	//----- 各パーツごとの関数 -----//.


};

#endif//PARTS_WEAPON_H_