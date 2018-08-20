#include "Object.h"

D3DXVECTOR3 GetVec3Dir(const float Angle, const D3DXVECTOR3 vAxis)
{
	D3DXMATRIX mYaw;

	//��].
	D3DXMatrixRotationY(&mYaw, Angle);//Y����].

	D3DXVECTOR3 vDir;

	//Z���޸�ق��̂��̂���]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord(&vDir, &vAxis, &mYaw);

	D3DXVec3Normalize(&vDir, &vDir);//���݌����Ă�������x�N�g��.

	return vDir;
}

//ڲ��ү���̓����蔻��.
bool clsObject::Intersect(
	const RAYSTATE RayState,
	const clsDX9Mesh* pTarget,//�Ώۂ̕���.
	float* pfDistance, //(out)����.
	D3DXVECTOR3* pvIntersect)//(out)�������W.
{
	D3DXMATRIXA16 matRot;//��]�s��.

	//��]�s����v�Z.
	D3DXMatrixRotationY(&matRot, m_Trans.fYaw);

	//���޸�ق�p��.
	D3DXVECTOR3 vecAxis = RayState.vAxis;
	//Z���޸�ق��̂��̂����݂̉�]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord(&vecAxis, &vecAxis, &matRot);

	D3DXVECTOR3 vecStart, vecEnd, vecDistance;
	//ڲ�̊J�n�I���ʒu��Attacker�ƍ��킹��.
	vecStart = vecEnd = RayState.vRayStart;
	//Attacker�̍��W�ɉ�]�s�����������.
	vecEnd += vecAxis * 1.0f;

	//�Ώۂ������Ă镨�̂ł��A�Ώۂ�world�s��́A�t�����p����ΐ�����ڲ��������.
	D3DXMATRIX matWorld,mTrans,mRotate,mScale;
	D3DXMatrixTranslation(&mTrans,
		pTarget->m_Trans.vPos.x,
		pTarget->m_Trans.vPos.y,
		pTarget->m_Trans.vPos.z);

	D3DXMatrixRotationYawPitchRoll(&mRotate,
		pTarget->m_Trans.fYaw,
		pTarget->m_Trans.fPitch,
		pTarget->m_Trans.fRoll);

	D3DXMatrixScaling(&mScale,
		pTarget->m_Trans.vScale.x,
		pTarget->m_Trans.vScale.y,
		pTarget->m_Trans.vScale.z);

	matWorld = mTrans * mRotate * mScale;

	//�t��������߂�.
	D3DXMatrixInverse(&matWorld, NULL, &matWorld);
	D3DXVec3TransformCoord(&vecStart, &vecStart, &matWorld);
	D3DXVec3TransformCoord(&vecEnd, &vecEnd, &matWorld);

	//���������߂�.
	vecDistance = vecEnd - vecStart;

	BOOL bHit = false;

	DWORD dwIndex = 0;//���ޯ���ԍ�.
	D3DXVECTOR3 vVertex[3];//���_���W.
	FLOAT U = 0, V = 0;//(out)�d�S˯č��W.

	//ү����ڲ�̌����𒲂ׂ�.
	D3DXIntersect(
		pTarget->m_pMesh,//�Ώ�ү��.
		&vecStart,//�J�n�ʒu.
		&vecDistance,//ڲ�̋���.
		&bHit,//(out)���茋��.
		&dwIndex,//(out)bHit��True�̎��Aڲ�̎n�_�ɁB�ł��߂��̖ʂ̲��ޯ���l�ւ��߲��.
		&U, &V,//(out)�d�S˯č��W.
		pfDistance,//���ޯĂƂ̋���.
		NULL, NULL);
	if (bHit)
	{
		//���������Ƃ�.
		FindVecticesOnPoly(pTarget->m_pMeshForRay, dwIndex, vVertex);

		//���S���W��������_���Z�o.
		//۰�ٌ�_p�́Av0 + U*(v1-v0) + V*(v2-v0)�ŋ��܂�.
		*pvIntersect =
			vVertex[0]
			+ U * (vVertex[1] - vVertex[0])
			+ V * (vVertex[2] - vVertex[0]);

		pvIntersect->x *= pTarget->m_Trans.vScale.x;
		pvIntersect->y *= pTarget->m_Trans.vScale.y;
		pvIntersect->z *= pTarget->m_Trans.vScale.z;

		return true;//�������Ă���.
	}

	return false;//�������Ă��Ȃ�.
}

//�����ʒu����غ�݂̒��_��������.
//�����_���W��۰�ٍ��W.
HRESULT clsObject::FindVecticesOnPoly(
	const LPD3DXMESH pTarget,
	const DWORD dwPolyIndex,
	D3DXVECTOR3* pVecVertices)
{
	//���_���Ƃ��޲Đ����擾.
	DWORD dwStride = pTarget->GetNumBytesPerVertex();
	//���_�����擾.
	DWORD dwVertexAm = pTarget->GetNumVertices();
	//�ʐ����擾.
	DWORD dwPolyAmt = pTarget->GetNumFaces();

	WORD* pwPoly = NULL;

	//���ޯ���ޯ̧��ۯ�(�ǂݍ���Ӱ��)
	pTarget->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);
	BYTE* pbVertices = NULL;//���_(�޲Đ�)
	FLOAT* pfVertices = NULL;//���_(float�^)
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;//���_�ޯ̧.
	pTarget->GetVertexBuffer(&VB);//���_���̎擾.

	//���_�ޯ̧��ۯ�.
	if (SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		/*for (int i = 0; i < 3; i++)
		{
		//��غ�݂̒��_��i�ڂ��擾.
		pfVertices
		= (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + i]];
		pVecVertices[i].x = pfVertices[0];
		pVecVertices[i].y = pfVertices[1];
		pVecVertices[i].z = pfVertices[2];
		}*/

		//��غ�݂̒��_��1�ڂ��擾.
		pfVertices
			= (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pVecVertices[0].x = pfVertices[0];
		pVecVertices[0].y = pfVertices[1];
		pVecVertices[0].z = pfVertices[2];

		//��غ�݂̒��_��2�ڂ��擾.
		pfVertices
			= (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pVecVertices[1].x = pfVertices[0];
		pVecVertices[1].y = pfVertices[1];
		pVecVertices[1].z = pfVertices[2];

		//��غ�݂̒��_��3�ڂ��擾.
		pfVertices
			= (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pVecVertices[2].x = pfVertices[0];
		pVecVertices[2].y = pfVertices[1];
		pVecVertices[2].z = pfVertices[2];

		pTarget->UnlockIndexBuffer();//ۯ�����.
		VB->Unlock();//ۯ�����.
	}
	VB->Release();

	return S_OK;
}

//��]�l����.
void ObjRollOverGuard(float* fRot)
{
	if (*fRot > D3DX_PI * 2.0f)
	{
		//1���ȏサ�Ă���.
		*fRot -= D3DX_PI * 2.0f;//2��(360��)��������.

		//�ċA�֐�.
		if (*fRot > D3DX_PI*2.0f)
		{
			ObjRollOverGuard(fRot);
		}
	}
}

bool clsObject::WallSetAxis(const clsDX9Mesh* pWall, float* fResultDis, const D3DXVECTOR3 vRayDir)
{
	FLOAT fDistance;//����.
	D3DXVECTOR3 vIntersect;//��_���W.
	float fDis;//�����Ɖ�].
	float fRaySpece = g_fRaySpace + m_fMoveSpeed;
	RAYSTATE rs;
	rs.vAxis = vRayDir;
	rs.vRayStart = m_Trans.vPos;

	Intersect(rs, pWall, &fDis, &vIntersect);

	bool bResult = false;

	//�O���ǂɐڋ�.
	if (fDis < fRaySpece && fDis > g_fGroundSpece)
	{
		bResult = true;
	}

	return bResult;
}
bool clsObject::WallForward(const clsDX9Mesh* pWall, const bool bSlip)
{
	FLOAT fDistance;//����.
	D3DXVECTOR3 vIntersect;//��_���W.
	float fDis, fYaw;//�����Ɖ�].
	float fRaySpece = g_fRaySpace + m_fMoveSpeed;
	RAYSTATE rs;
	rs.vAxis = g_vDirForward;
	rs.vRayStart = m_Trans.vPos;
	//ڲ�̌����ɂ�铖����ǂ܂ł̋��������߂�.

	fYaw = fabs(m_Trans.fYaw);//fabs:��Βl(float��)
	ObjRollOverGuard(&fYaw);//0�`2�΂̊ԂɎ��߂�.

	Intersect(rs, pWall, &fDis, &vIntersect);

	bool bResult = false;
	
	//�O���ǂɐڋ�.
	if (fDis < fRaySpece && fDis > g_fGroundSpece)
	{
		bResult = true;

		if (bSlip)
		{
			if (m_Trans.fYaw < 0.0f)
			{
				//���v���
				if (fYaw >= 0.785f && fYaw < 2.355f)//�E����.
				{
					m_Trans.vPos.x += fRaySpece - fDis;
				}

				else if (fYaw >= 2.355f && fYaw < 3.925f)//�O����.
				{
					m_Trans.vPos.z += fRaySpece - fDis;
				}

				else if (fYaw >= 3.925f && fYaw < 5.495f)//������
				{
					m_Trans.vPos.x -= fRaySpece - fDis;
				}

				else//������.
				{
					m_Trans.vPos.z -= fRaySpece - fDis;
				}
			}

			else
			{
				//�����v���
				if (fYaw >= 0.785f && fYaw < 2.355f)//�E����.
				{
					m_Trans.vPos.x -= fRaySpece - fDis;
				}

				else if (fYaw >= 2.355f && fYaw < 3.925f)//�O����.
				{
					m_Trans.vPos.z += fRaySpece - fDis;
				}

				else if (fYaw >= 3.925f && fYaw < 5.495f)//������
				{
					m_Trans.vPos.x += fRaySpece - fDis;
				}

				else//������.
				{
					m_Trans.vPos.z -= fRaySpece - fDis;
				}
			}
		}
	}

	return bResult;
}

bool clsObject::WallBack(const clsDX9Mesh* pWall, const bool bSlip)
{
	FLOAT fDistance;//����.
	D3DXVECTOR3 vIntersect;//��_���W.
	float fDis, fYaw;//�����Ɖ�].
	float fRaySpece = g_fRaySpace + m_fMoveSpeed;
	RAYSTATE rs;
	rs.vAxis = g_vDirBack;
	rs.vRayStart = m_Trans.vPos;
	//ڲ�̌����ɂ�铖����ǂ܂ł̋��������߂�.

	fYaw = fabs(m_Trans.fYaw);//fabs:��Βl(float��)
	ObjRollOverGuard(&fYaw);//0�`2�΂̊ԂɎ��߂�.

	Intersect(rs, pWall, &fDis, &vIntersect);

	bool bResult = false;

	if (fDis < fRaySpece && fDis > g_fGroundSpece)
	{
		bResult = true;

		if (bSlip)
		{
			if (m_Trans.fYaw < 0.0f)
			{
				//���v���
				if (fYaw >= 0.785f && fYaw < 2.355f)//�E����.
				{
					m_Trans.vPos.x -= fRaySpece - fDis;
				}

				else if (fYaw >= 2.355f && fYaw < 3.925f)//�O����.
				{
					m_Trans.vPos.z -= fRaySpece - fDis;
				}

				else if (fYaw >= 3.925f && fYaw < 5.495f)//������
				{
					m_Trans.vPos.x += fRaySpece - fDis;
				}

				else//������.
				{
					m_Trans.vPos.z += fRaySpece - fDis;
				}
			}

			else
			{
				//�����v���
				if (fYaw >= 0.785f && fYaw < 2.355f)//�E����.
				{
					m_Trans.vPos.x += fRaySpece - fDis;
				}

				else if (fYaw >= 2.355f && fYaw < 3.925f)//�O����.
				{
					m_Trans.vPos.z -= fRaySpece - fDis;
				}

				else if (fYaw >= 3.925f && fYaw < 5.495f)//������
				{
					m_Trans.vPos.x -= fRaySpece - fDis;
				}

				else//������.
				{
					m_Trans.vPos.z += fRaySpece - fDis;
				}
			}
		}
	}

	return bResult;
}

bool clsObject::WallLeft(const clsDX9Mesh* pWall, const bool bSlip)
{
	FLOAT fDistance;//����.
	D3DXVECTOR3 vIntersect;//��_���W.
	float fDis, fYaw;//�����Ɖ�].
	float fRaySpece = g_fRaySpace + m_fMoveSpeed;
	RAYSTATE rs;
	rs.vAxis = g_vDirLeft;
	rs.vRayStart = m_Trans.vPos;
	//ڲ�̌����ɂ�铖����ǂ܂ł̋��������߂�.

	fYaw = fabs(m_Trans.fYaw);//fabs:��Βl(float��)
	ObjRollOverGuard(&fYaw);//0�`2�΂̊ԂɎ��߂�.

	Intersect(rs, pWall, &fDis, &vIntersect);

	bool bResult = false;

	if (fDis < fRaySpece && fDis > g_fGroundSpece)
	{
		bResult = true;

		if (bSlip)
		{
			if (m_Trans.fYaw < 0.0f)
			{
				//���v���
				if (fYaw >= 0.785f && fYaw < 2.355f)//�E����.
				{
					m_Trans.vPos.z += fRaySpece - fDis;
				}

				else if (fYaw >= 2.355f && fYaw < 3.925f)//�O����.
				{
					m_Trans.vPos.x -= fRaySpece - fDis;
				}

				else if (fYaw >= 3.925f && fYaw < 5.495f)//������
				{
					m_Trans.vPos.z -= fRaySpece - fDis;
				}

				else//������.
				{
					m_Trans.vPos.x += fRaySpece - fDis;
				}
			}

			else
			{
				//�����v���
				if (fYaw >= 0.785f && fYaw < 2.355f)//�E����.
				{
					m_Trans.vPos.z -= fRaySpece - fDis;
				}

				else if (fYaw >= 2.355f && fYaw < 3.925f)//�O����.
				{
					m_Trans.vPos.x -= fRaySpece - fDis;
				}

				else if (fYaw >= 3.925f && fYaw < 5.495f)//������
				{
					m_Trans.vPos.z += fRaySpece - fDis;
				}

				else//������.
				{
					m_Trans.vPos.x += fRaySpece - fDis;
				}

			}
		}
	}

	return bResult;
}

bool clsObject::WallRight(const clsDX9Mesh* pWall, const bool bSlip)
{
	FLOAT fDistance;//����.
	D3DXVECTOR3 vIntersect;//��_���W.
	float fDis, fYaw;//�����Ɖ�].
	float fRaySpece = g_fRaySpace + m_fMoveSpeed;
	RAYSTATE rs;
	rs.vAxis = g_vDirRight;
	rs.vRayStart = m_Trans.vPos;
	//ڲ�̌����ɂ�铖����ǂ܂ł̋��������߂�.

	fYaw = fabs(m_Trans.fYaw);//fabs:��Βl(float��)
	ObjRollOverGuard(&fYaw);//0�`2�΂̊ԂɎ��߂�.

	Intersect(rs, pWall, &fDis, &vIntersect);

	bool bResult = false;

	if (fDis < fRaySpece && fDis > g_fGroundSpece)
	{
		bResult = true;

		if (bSlip)
		{
			if (m_Trans.fYaw < 0.0f)
			{
				//���v���
				if (fYaw >= 0.785f && fYaw < 2.355f)//�E����.
				{
					m_Trans.vPos.z -= fRaySpece - fDis;
				}

				else if (fYaw >= 2.355f && fYaw < 3.925f)//�O����.
				{
					m_Trans.vPos.x += fRaySpece - fDis;
				}

				else if (fYaw >= 3.925f && fYaw < 5.495f)//������
				{
					m_Trans.vPos.z += fRaySpece - fDis;
				}

				else//������.
				{
					m_Trans.vPos.x -= fRaySpece - fDis;
				}
			}

			else
			{
				//�����v���
				if (fYaw >= 0.785f && fYaw < 2.355f)//�E����.
				{
					m_Trans.vPos.z += fRaySpece - fDis;
				}

				else if (fYaw >= 2.355f && fYaw < 3.925f)//�O����.
				{
					m_Trans.vPos.x += fRaySpece - fDis;
				}

				else if (fYaw >= 3.925f && fYaw < 5.495f)//������
				{
					m_Trans.vPos.z -= fRaySpece - fDis;
				}

				else//������.
				{
					m_Trans.vPos.x -= fRaySpece - fDis;
				}
			}
		}
	}

	return bResult;
}

bool clsObject::WallUp(const clsDX9Mesh* pWall)
{
	FLOAT fDistance;//����.
	D3DXVECTOR3 vIntersect;//��_���W.
	float fDis;//�����Ɖ�].
	float fRaySpece = g_fRaySpace + m_fFollPower;
	RAYSTATE rs;
	rs.vAxis = g_vDirUp;
	rs.vRayStart = m_Trans.vPos;

	Intersect(rs, pWall, &fDis, &vIntersect);

	bool bResult = false;

	if (fDis < fRaySpece + m_fFollPower && fDis > g_fGroundSpece)
	{
		bResult = true;

		if (m_fFollPower > 0.0f)
		{
			m_fFollPower = 0.0f;
			m_Trans.vPos.y = vIntersect.y - fRaySpece;
		}
	}

	return bResult;
}

bool clsObject::WallUnder(const clsDX9Mesh* pWall)
{
	FLOAT fDistance;//����.
	D3DXVECTOR3 vIntersect;//��_���W.
	float fDis;//�����Ɖ�].
	float fRaySpece = g_fRaySpace - m_fFollPower;
	RAYSTATE rs;
	rs.vAxis = g_vDirDown;
	rs.vRayStart = m_Trans.vPos;

	Intersect(rs, pWall, &fDis, &vIntersect);

	bool bResult = false;

	if (fDis < fRaySpece - m_fFollPower && fDis > g_fGroundSpece)
	{
		bResult = true;

		m_Trans.vPos.y = vIntersect.y + (fRaySpece - g_fGroundSpece);

		m_fFollPower = 0.0f;
	}

	return bResult;
}

bool clsObject::Collision(SPHERE pAttacker, SPHERE pTarget)
{
	//2�̕��̂̒��S�Ԃ̋��������߂�.
	D3DXVECTOR3 vLength = *pTarget.vCenter - *pAttacker.vCenter;
	//�����ɕϊ�����.
	float Length = D3DXVec3Length(&vLength);

	//2���̊Ԃ̋������A2���̂̔��a�𑫂�������.
	//�������Ƃ������Ƃ́A�̨����m���d�Ȃ��Ă���.
	//(�Փ˂��Ă���)�Ƃ�������.
	if (Length <=
		pAttacker.fRadius + pTarget.fRadius)
	{
		return true;//�Փ�.
	}
	return false;//�Փ˂��Ă��Ȃ�.
}

bool clsObject::ObjectCollision(std::vector<SPHERE> pTarget, const int iNumMax)
{
	for (int i = 0; i < m_iColSpheresMax; i++)
	{
		for (int j = 0; j < iNumMax; j++)
		{
			if (Collision(m_v_pSpheres[i], pTarget[j]))
			{
				return true;
			}
		}
	}

	return false;
}

void clsObject::FreeFoll()
{
	if (!m_bGround)
	{
		m_fFollPower -= g_fGravity;
		m_Trans.vPos.y += m_fFollPower;
	}
}

bool clsObject::WallJudge(clsStage* const pStage)
{
	if (!pStage)return false;

	std::vector<clsDX9Mesh*> vvpMeshTmp;
	vvpMeshTmp = pStage->GetStageMeshArray();

	m_bGround = false;

	bool bResult = false;

	for (int i = 0; i < vvpMeshTmp.size(); i++)
	{
		clsDX9Mesh* pObjMesh = vvpMeshTmp[i];

		if (!pObjMesh)continue;

		bool bHit = false;

		//StageObject�Ƃ̓����蔻��.
		if (WallForward(pObjMesh))if (!bHit)bHit = true;
		if (WallBack(pObjMesh))if (!bHit)bHit = true;
		if (WallLeft(pObjMesh))if (!bHit)bHit = true;
		if (WallRight(pObjMesh))if (!bHit)bHit = true;
		if (WallUp(pObjMesh))if (!bHit)bHit = true;

		if (WallUnder(pObjMesh))
		{
			m_bGround = true;
			if (!bHit)bHit = true;

			D3DXVECTOR3 vMovePos = GetPosition();
			D3DXVECTOR3 vMoveDir = { 0.0f, 0.0f, 0.0f };

			vMovePos += vMoveDir;
			SetPosition(vMovePos);
		}

		if (!bResult)
		{
			bResult = bHit;
		}
	}

	FreeFoll();

	return bResult;
}