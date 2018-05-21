#pragma once

#include "Global.h"



//�J�����̊��N���X.
class clsCAMERA_BASE
{
public:
	clsCAMERA_BASE();
	virtual ~clsCAMERA_BASE();

	//�ŏ�( �V�[���̂͂��� )�̏�����.
	virtual void Create() = 0;

	//��������true->m_vLook�����Ă���.
	//��������false->m_vLook�͂��̂܂܂̈ʒu.
	virtual void SetPos( const D3DXVECTOR3& vPos, bool isWithLook = true );
	virtual void AddPos( const D3DXVECTOR3& vPos, bool isWithLook = true );

	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetLookPos();

protected:

	D3DXVECTOR3 m_vPos;	//�J�����ʒu.
	D3DXVECTOR3 m_vLook;//�����ʒu.
	D3DXVECTOR3 m_vRot;	//��]�l.

	D3DXMATRIX	m_mRot;	//��]�s��.

};

