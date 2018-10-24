#ifndef CAMERA_BASE_H_
#define CAMERA_BASE_H_

#include "Global.h"



//�J�����̊��N���X.
class clsCAMERA_BASE
{
public:
	clsCAMERA_BASE();
	virtual ~clsCAMERA_BASE();

	//�ŏ�( �V�[���̂͂��� )�̏�����.
	virtual void Create() = 0;
	//���t���[���̏���.
	virtual void Update() = 0;

	//��������true->m_vLook�����Ă���.
	//��������false->m_vLook�͂��̂܂܂̈ʒu.
	void SetPos( const D3DXVECTOR3& vPos, bool isWithLook = true );
	void AddPos( const D3DXVECTOR3& vVec, bool isWithLook = true );
	D3DXVECTOR3 GetPos();

	void SetLookPos( const D3DXVECTOR3& vPos );
	void AddLookPos( const D3DXVECTOR3& vVec );
	D3DXVECTOR3 GetLookPos();

	D3DXVECTOR3 GetRot();
	void SetRot( const D3DXVECTOR3 &vRot );

protected:

	D3DXVECTOR3 m_vPos;	//�J�����ʒu.
	D3DXVECTOR3 m_vLook;//�����ʒu.
	D3DXVECTOR3 m_vRot;	//��]�l.

	D3DXMATRIX	m_mRot;	//��]�s��.

};

#endif//#ifndef CAMERA_BASE_H_