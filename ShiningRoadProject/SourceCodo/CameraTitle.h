#pragma once

#include "Camera.h"


class clsCAMERA_TITLE : public clsCAMERA_BASE
{
public:
	clsCAMERA_TITLE();
	~clsCAMERA_TITLE();

	void Create() final;

	void Update();


private:

	enum class enMODE : UCHAR
	{
		START = 0,
		UP_1,

		SPN_L,
		SPN_R
	}m_enMode;

	//�e���[�h�̏�����.
	void Init();

	//�Ď��Ώۂ𒆐S�ɐ��񂷂�.
	void Spn( const float fSpn );

	//�J�����ʒu�𒆐S�ɂ��Č���.
	void Turn( const float fTurn );

	//�㉺������.
	void UpDown( const float fRot );

	//���̃J���������ɑO�i.advancing
	void Advancing( const float fMove );

	float m_fDistance;//�J�����Ǝ��_�̋���( x&z�������̓񎟌���ł� ).

};

