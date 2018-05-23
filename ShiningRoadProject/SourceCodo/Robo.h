#pragma once



#include"Charactor.h"
#include"SkinMesh.h"


//�����̏�����������.
#ifdef Tahara
#include "PtrGroup.h"

//2018/05/16( �� ).
	//�֐��uRoboInit�v�ɁuclsPOINTER_GROUP�v�^�̈�����ǉ����A.
	//�ǉ����������o�ϐ�( m_wpResource�Am_wpEffects�Am_wpSound ).
	//�ɃA�h���X�����蓖�Ă鏈����ǉ����܂���.
	
	//�����q�̓s���ケ�̃N���X�́uRender�v�֐���.
	//�uclsSkinMesh�v�N���X�́uModelRender�v�֐���.
	//�uclsD3DXSKINMESH�v�N���X�́uRender�v�֐���.
	//������const��t���܂���.
	
	//Zeromemory�̓|�C���^����\�ꂷ��̂ŏ����������s���܂���.
	//���uclsCharactor�v�ƁuclsObject�v�uclsSkinMesh�v��.

#endif//#ifdef Tahara



class clsRobo : public clsCharactor
{
public:
	/*clsSkinMesh * m_pHead;
	clsSkinMesh * m_pCore;
	clsSkinMesh * m_pLeftArm;
	clsSkinMesh * m_pRightArm;
	clsSkinMesh * m_pLeg;*/
	clsSkinMesh* m_pMesh;

	void RoboInit(HWND hWnd,
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11,
		clsPOINTER_GROUP* const pPtrGroup );

	void Update()
	{
		DXSKIN_TRANSFORM tmpTrans;

		tmpTrans.fPitch = m_Trans.fPitch;
		tmpTrans.fYaw = m_Trans.fYaw;
		tmpTrans.fRoll = m_Trans.fRoll;
		tmpTrans.vPos = m_Trans.vPos;
		tmpTrans.vScale = m_Trans.vScale;

		m_pMesh->ModelUpdate(tmpTrans);
	}

	void Render( 
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye,
		const D3DXVECTOR4 &vColor = { 1.0f, 1.0f, 1.0f ,1.0f },
		const bool alphaFlg = false )
	{
		Update();
		m_pMesh->ModelRender(mView, mProj, vLight, vEye, vColor, alphaFlg );
	}

	bool m_bBoost;

	float m_fWalktMoveSpeedMax;
	int m_fWalkTopSpeedFrame;

	float m_fBoostMoveSpeedMax;
	int m_iBoostTopSpeedFrame;

	float m_fBoostRisingSpeedMax;//�X�s�[�h�̍ő�l.
	int m_iBoostRisingTopSpeedFrame;//���ɒB����܂ł̃t���[���l.
	float m_fBoostRisingAccele;// = m_fMoveSpeedMax / m_fTopSpeedFrame;

	void Walk();
	void Boost();
	void MoveSwitch();
	void BoostRising();
	void QuickBoost();
	void SetDirQuickBoost(const float fAngle);

	clsRobo();
	~clsRobo();

private:


//�����̏�����������.
#ifdef Tahara
	//�����Ƃ�delete���Ȃ���null���Ă�.
	clsResource*		m_wpResource;
	clsEffects*			m_wpEffects;
	clsSOUND_MANAGER*	m_wpSound;
#endif//#ifdef Tahara


};

