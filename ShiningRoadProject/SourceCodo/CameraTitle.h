#pragma once

#include "Camera.h"


class clsCAMERA_TITLE : public clsCAMERA_BASE
{
public:
	clsCAMERA_TITLE();
	~clsCAMERA_TITLE();

	void Create() final;

	void Update() final;


private:


	enum class enMODE : UCHAR
	{
		START = 0,	//�^�C�g����ʊJ�n��.
		IDLE,		//�ҋ@.

		UP_1,

		SPN_L,
		SPN_R,
	}m_enMode;

	//�e���[�h�̏�����.
	void Init( const enMODE enMode );

	//�Ď��Ώۂ𒆐S�ɐ��񂷂�.
	void Spn( const float fSpn );

	//�J�����ʒu�𒆐S�ɂ��Č���.
	void Turn( const float fTurn );

	//���̃J���������ɑO�i.advancing
	void Advancing( const float fMove );

	float m_fDistance;//�J�����Ǝ��_�̋���( x&z�������̓񎟌���ł� ).

	D3DXVECTOR3 m_vMoveSpd;	//���x.
	D3DXVECTOR3 m_vMoveAcc;	//�����x.

};

