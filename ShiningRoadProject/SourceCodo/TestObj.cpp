#include"TestObject.h"

clsTestObj::clsTestObj()
{
	ZeroMemory(this, sizeof(clsTestObj));
}

clsTestObj::~clsTestObj()
{

}

void clsTestObj::Init(HWND hWnd,
	ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11,
	clsPOINTER_GROUP* const pPtrGroup )
{
	RoboInit(hWnd, pDevice11, pContext11, pPtrGroup);

	m_pInput = new clsInputRobo(pPtrGroup->GetDxInput(), pPtrGroup->GetXInput());

	m_pMesh->SetAnimSpeed(0.01);
}

void clsTestObj::Action(const clsDX9Mesh* pWall)
{
	float fPush = 0.0f;
	float fAngle = 0.0f;
	clsRoboCommand* pRoboCom;

	float fPushMin = 0.5f;

	Updata();

	pRoboCom = m_pInput->MoveSwitch();

	if (pRoboCom)
	{
		pRoboCom->PushBotton(this);
	}

	pRoboCom = m_pInput->BoostRising();

	if (pRoboCom)
	{
		pRoboCom->PushBotton(this);
	}

	pRoboCom = m_pInput->LSInput(fPush, fAngle);
	pRoboCom->Trigger(this, fPush, fAngle);

	if (abs(fPush) >= fPushMin)//LS��������.
	{
		pRoboCom = m_pInput->QuickBoost();//�N�C�b�N�u�[�X�g.
		if (pRoboCom)
		{
			pRoboCom->Trigger(this, fPush, fAngle);
			pRoboCom->PushBotton(this);
		}

		pRoboCom = m_pInput->RSHorInput(fPush, fAngle);//����.
		pRoboCom->Trigger(this, abs(fPush), fAngle);
	}

	else
	{
		pRoboCom = m_pInput->RSHorInput(fPush, fAngle);//����.
		pRoboCom->Trigger(this, abs(fPush), fAngle);

		if (abs(fPush) >= fPushMin)//RS��������.
		{
			pRoboCom = m_pInput->QuickTurn();

			if (pRoboCom)
			{
				pRoboCom->Trigger(this, fPush, fAngle);
				pRoboCom->PushBotton(this);
			}
		}

		else
		{
			pRoboCom = m_pInput->QuickBoost();

			if (pRoboCom)
			{
				pRoboCom->PushBotton(this);
			}
		}
	}

	



	

	if (pWall)
	{
		WallJudge(pWall);
	}
}

void clsTestObj::InhUpdate()
{
	m_pMesh->SetAnimSpeed(0.01);
}