//#pragma once

#ifndef SKINMESH
#define SKINMESH

#include "CD3DXSKINMESH.h"

class clsSkinMesh
{
public:
	double m_AnimTime;
	//Ӱ��݊֌W.
	int m_AnimNo;//Ӱ��ݔԍ�.
	double m_dAnimSpeed;
	bool m_bAnimReverce;

	clsD3DXSKINMESH* m_pMesh;
	LPD3DXANIMATIONCONTROLLER m_pAnimCtrl;
	
	//�����ް��̊֘A�t��.
	void AttachModel(clsD3DXSKINMESH* pModel);
	//�����ް��֘A�t������.
	void DetatchModel();

	//�����ݸފ֐�.
	void ModelRender( 
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye,
		const D3DXVECTOR4 &vColor,
		const bool alphaFlg );

	void AnimUpdate();
	//��Ұ��ݍő吔���擾.
	int GetAnimSetMax();
	//��Ұ��ݐ؂�ւ��֐�.
	void SetAnimChange(int index, double dStartPos = 0.0f);

	//���W���]�̍X�V.
	void ModelUpdate(TRANSFORM Transform);

	D3DXVECTOR3 GetBonePos(char* sBoneName);

	//�w�肵���{�[���ʒu����vDiviation���ړ������ʒu���擾����.
	D3DXVECTOR3 GetBoneDiviaPos(char* sBoneName, D3DXVECTOR3 vDiviation);

	void SetAnimSpeed(double dSpeed);
	double GetAnimSpeed();

	double GetAnimTime();
	void SetAnimTime(double dTime);
	double GetAnimEndTime(int AnimIndex);
	
	bool IsAnimTimeEnd(int AnimIndex);
	bool IsAnimTimeAfter(int AnimIndex, double DesignationTime);
	bool IsAnimTimePoint(int AnimIndex, double DesignationTime);

	clsSkinMesh();
	virtual ~clsSkinMesh();

private:

};


#endif