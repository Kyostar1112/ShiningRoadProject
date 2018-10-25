#ifndef SPRITE_2D_CENTER_H_
#define SPRITE_2D_CENTER_H_

#include "Sprite2D.h"

//��_�����S�ɂ���̂ŉ�]���ł���.
class clsSPRITE2D_CENTER : public clsSprite2D
{
public:
	clsSPRITE2D_CENTER();
	~clsSPRITE2D_CENTER();

		//�`��(�����_�����O)
	void Render() override;

	void SetRot( const D3DXVECTOR3 &vRot );
	D3DXVECTOR3 GetRot();
	void AddRot( const D3DXVECTOR3 &vRot );


protected:

	//���f���쐬.
	HRESULT InitModel( SPRITE_STATE ss ) override;


	//��]�̐��l�̌��E�����яo�Ȃ�.
	D3DXVECTOR3 GuardRotOver( D3DXVECTOR3 &vRot );
	float GuardRotOver( float &fRot );

	D3DXVECTOR3 m_vRot;//��].
};

#endif//#ifndef SPRITE_2D_CENTER_H_