#include"SkinMesh.h"

clsSkinMesh::clsSkinMesh() :
	m_pMesh( NULL ),
	m_AnimTime( 0.0 ),
	m_AnimNo( 0 ),
	m_pAnimCtrl( NULL ),
	m_dAnimSpeed( 0.1 ),
	m_bAnimReverce( false )
{
//	ZeroMemory(this, sizeof(clsSkinMesh));
}
clsSkinMesh::~clsSkinMesh()
{
	DetatchModel();
}

void clsSkinMesh::ModelRender(
	const D3DXMATRIX& const mView, 
	const D3DXMATRIX& const mProj, 
	const D3DXVECTOR3& const vLight, 
	const D3DXVECTOR3& const vEye,
	const D3DXVECTOR4 &vColor,
	const bool alphaFlg )
{
	if (m_pMesh == NULL || m_pAnimCtrl == NULL)return;

	if (!m_bAnimReverce)
	{
		m_AnimTime += abs(m_dAnimSpeed);

		if (m_pAnimCtrl != NULL){
			m_pAnimCtrl->AdvanceTime(m_dAnimSpeed, NULL);
		}
	}

	else
	{
		if (m_AnimTime - m_dAnimSpeed > 0)
		{
			m_AnimTime -= abs(m_dAnimSpeed);
		}
		
		ChangeAnimSet(m_AnimNo, m_AnimTime);

		// ��Ґi�s.
		if (m_pAnimCtrl != NULL){
			m_pAnimCtrl->AdvanceTime(0, NULL);
		}
	}

	m_pMesh->Render(mView, mProj, vLight, vEye, vColor, alphaFlg, m_pAnimCtrl);
}

void clsSkinMesh::DetatchModel()
{
	if (m_pMesh != NULL)
	{
		m_pMesh = NULL;

		if (m_pAnimCtrl != NULL)
		{
			m_pAnimCtrl->Release();
			m_pAnimCtrl = NULL;
		}
	}
}

//�����ް��̊֘A�t��.
void clsSkinMesh::AttachModel(clsD3DXSKINMESH* const pModel)
{
	if (pModel == NULL)
	{
		return;
	}

	//���ِݒ�.
	m_pMesh = pModel;
	//��Ұ��ݑ��x.
	m_dAnimSpeed = m_pMesh->GetAnimSpeed();

	//��Ұ��ݺ��۰̸ׂ۰݂��쐬.
	LPD3DXANIMATIONCONTROLLER pAC = m_pMesh->GetAnimController();

	pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
		&m_pAnimCtrl);//(out)��Ұ��ݺ��۰�.
}

//��Ұ��ݍő吔���擾.
int clsSkinMesh::GetAnimSetMax()
{
	if (m_pAnimCtrl != NULL)
	{
		return (int)m_pAnimCtrl->GetMaxNumAnimationSets();
	}
	return -1;
}

//��Ұ��ݐ؂�ւ��֐�.
void clsSkinMesh::ChangeAnimSet(int index, double dStartPos)
{
	//��Ұ��݂͈͓̔�������.
	if (index < 0 || index >= GetAnimSetMax())return;
	m_pMesh->ChangeAnimSet_StartPos(index, dStartPos, m_pAnimCtrl);
}
