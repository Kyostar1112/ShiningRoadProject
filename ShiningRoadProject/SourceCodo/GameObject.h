#ifndef GAME_OBJ_
#define GAME_OBJ_


#define _USE_MATH_DEFINES
#include <math.h>


#include "Global.h"


class clsGameObject
{
public:
	clsGameObject();
	virtual ~clsGameObject();

	virtual void Init() = 0;

	//���f���f�[�^�֘A�t��.
	virtual void AttachModel(){};
	//���f���f�[�^�֘A�t������.
	virtual void DetatchModel(){};

	//�`��.
//	virtual void Render(){};


	//�ʒu�ݒ�.
	virtual void SetPosition( const D3DXVECTOR3 &vPos );
	void SetPositionX( const float fPosX );
	void SetPositionY( const float fPosY );
	void SetPositionZ( const float fPosZ );
	//�擾.
	D3DXVECTOR3 GetPosition() const;
	float GetPositionX() const;
	float GetPositionY() const;
	float GetPositionZ() const;
	//��������.
	void AddPosition( const D3DXVECTOR3 &vMove );
	void AddPositionX( const float fMoveX );
	void AddPositionY( const float fMoveY );
	void AddPositionZ( const float fMoveZ );


	//��]�ݒ�.
	//�ݒ�.
	void SetRotation( const D3DXVECTOR3 &vRot );
	void SetRotationY( const float fRotY );
	void SetRotationZ( const float fRotZ );
	//�擾.
	D3DXVECTOR3 GetRotation() const;
	float GetRotationX() const;
	float GetRotationY() const;
	float GetRotationZ() const;
	//��������.
	void AddRotation( const D3DXVECTOR3 &vMove );
	void AddRotationY( const float fMoveY );
	void AddRotationZ( const float fMoveZ );


	//�g�k�ݒ�.
	void SetScale( const float fScale );
	void SetScale( const D3DXVECTOR3 &vScale );
	D3DXVECTOR3 GetScale() const;


	//�����ŉ��ʂ�ς���.
	int ChangeVolumeDistance( const float fEarPosZ, const float fThisPosZ );


protected:

	//���W���]�l���X�V����.
	virtual void UpDateModel() = 0;
	//360�`0�ɔ[�߂�.
	void ThetaOverGuard( float& theta );
	void ThetaOverGuard( double& theta );

	D3DXVECTOR3		m_vPos;		//�ʒu.
	D3DXVECTOR3		m_vRot;		//��].
	D3DXVECTOR3		m_vScale;	//�g�k.



};



#endif//#ifndef GAME_OBJ_