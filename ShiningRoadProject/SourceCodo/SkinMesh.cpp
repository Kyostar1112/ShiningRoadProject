#include"SkinMesh.h"

clsSkinMesh::clsSkinMesh() :
	m_pMesh( NULL ),
	m_AnimTime( 0.0 ),
	m_AnimNo( 0 ),
	m_pAnimCtrl( NULL ),
	m_dAnimSpeed( 0.1 ),
	m_bAnimReverce( false )
{

}
clsSkinMesh::~clsSkinMesh()
{
	DetatchModel();
}

void clsSkinMesh::ModelRender(
	const D3DXMATRIX& mView, 
	const D3DXMATRIX& mProj, 
	const D3DXVECTOR3& vLight, 
	const D3DXVECTOR3& vEye,
	const D3DXVECTOR4& vColor,
	const bool alphaFlg )
{
	if (m_pMesh == NULL || m_pAnimCtrl == NULL)return;

	AnimUpdate();
	m_pMesh->Render(mView, mProj, vLight, vEye, vColor, alphaFlg, m_pAnimCtrl);
}

void clsSkinMesh::AnimUpdate()
{
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

		SetAnimChange(m_AnimNo, m_AnimTime);

		// ��Ґi�s.
		if (m_pAnimCtrl != NULL){
			m_pAnimCtrl->AdvanceTime(0, NULL);
		}
	}
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

//��Ұ��ݐ؂�ւ��֐�.//�ύX�ł���Ȃ�true, �ύX�ł��Ȃ��Ȃ�false���Ԃ�.
bool clsSkinMesh::SetAnimChange(int index, double dStartPos)
{
	//��Ұ��݂͈͓̔�������.
	if (index < 0 || index >= GetAnimSetMax()){
		//�͈͊O�Ȃ珉���A�j���[�V�������Đ���,�{��.
		m_pMesh->ChangeAnimSet_StartPos(0, dStartPos, m_pAnimCtrl);
//		assert( !"�͈͊O�̃A�j���[�V�������w�肳��܂���" );
		return false;
	}
	m_pMesh->ChangeAnimSet_StartPos(index, dStartPos, m_pAnimCtrl);
	return true;
}

void clsSkinMesh::ModelUpdate(TRANSFORM Transform)
{
	m_pMesh->m_Trans = Transform;
}

D3DXVECTOR3 clsSkinMesh::GetBonePos( const char* sBoneName, const bool isLocalPos )
{
	D3DXVECTOR3 vBonePos;

	//�{�[���̍��W�����.
	if( !m_pMesh->GetPosFromBone( sBoneName, &vBonePos, isLocalPos ) ){
		//�{�[����������Ȃ����.
//		ERR_MSG( sBoneName, "���̖��O�̃{�[���͑��݂��܂���");
	}

	return vBonePos;
}

//�w�肵���{�[���ʒu����vDiviation���ړ������ʒu���擾����.
D3DXVECTOR3 clsSkinMesh::GetBoneDiviaPos(char* sBoneName, D3DXVECTOR3 vDiviation)
{
	D3DXVECTOR3 vBonePos;

	m_pMesh->GetDeviaPosFromBone(sBoneName, &vBonePos, vDiviation);
	return vBonePos;
}

void clsSkinMesh::SetAnimSpeed(double dSpeed)
{
	m_dAnimSpeed = dSpeed;
	m_pMesh->SetAnimSpeed(m_dAnimSpeed);
}

double clsSkinMesh::GetAnimSpeed()
{
	return m_dAnimSpeed;
}

double clsSkinMesh::GetAnimEndTime(int AnimIndex)
{
	return m_pMesh->GetAnimPeriod(AnimIndex); 
}

void clsSkinMesh::SetAnimTime(double dTime)
{
	m_AnimTime = dTime;
	m_pMesh->SetAnimTime(dTime);
}

double clsSkinMesh::GetAnimTime()
{
	return m_AnimTime; 
}

bool clsSkinMesh::IsAnimTimeEnd(int AnimIndex)
{
	if (!m_bAnimReverce)
	{
		if (GetAnimEndTime(AnimIndex) - m_dAnimSpeed < m_AnimTime)
		{
			m_AnimTime = GetAnimEndTime(AnimIndex);
			return true;
		}
	}

	else
	{
		if (m_AnimTime < m_dAnimSpeed)
		{
			m_AnimTime = 0.0f;
			return true;
		}
	}

	return false;
}

bool clsSkinMesh::IsAnimTimeAfter(int AnimIndex, double DesignationTime)
{
	if (!m_bAnimReverce)
	{
		if (DesignationTime - m_dAnimSpeed < m_AnimTime)
		{
			m_AnimTime = DesignationTime;
			return true;
		}
	}

	else
	{
		if (m_AnimTime < (DesignationTime + m_dAnimSpeed))
		{
			m_AnimTime = DesignationTime;
			return true;
		}
	}


	return false;
}

bool clsSkinMesh::IsAnimTimePoint(int AnimIndex, double DesignationTime)
{
	if (DesignationTime - m_dAnimSpeed < m_AnimTime &&
		DesignationTime + m_dAnimSpeed > m_AnimTime)
	{
		return true;
	}

	return false;
}