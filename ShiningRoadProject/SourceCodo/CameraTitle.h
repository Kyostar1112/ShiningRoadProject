#pragma once

#include "Camera.h"


class clsCAMERA_TITLE : public clsCAMERA_BASE
{
public:
	clsCAMERA_TITLE();
	~clsCAMERA_TITLE();

	void Create() final;

	void Update() final;

	D3DXVECTOR3 GetSpd(){
		return m_vMoveSpd;
	};

	D3DXVECTOR3 GetAcc(){
		return m_vMoveAcc;
	};


private:


	enum class enMODE : UCHAR
	{
		START = 0,	//�^�C�g����ʊJ�n��.
		IDLE,		//�ҋ@.

		SPN_L,		//�����ŉ�].
		SPN_L_2,	//�Y�[�����ǂ���������.
		SPN_L_3,	//�����������炷.
	}m_enMode;

	//�e���[�h�̏�����.
	void Init( const enMODE enMode );

	//�Ď��Ώۂ𒆐S�ɐ��񂷂�.
	void Spn( const float fSpn );

	//�J�����ʒu�𒆐S�ɂ��Č���.
	void Turn( const float fTurn );

	//���̃J���������ɑO�i.advancing
	void Advancing( const float fMove );

	//���_�Ƃ̋�����ύX.
	void AddDistance( const float fAdd, const bool isCamMove );

	//���邭��.
	void CameraSpnFunction();
	//�Y�[��.
	void CameraFakeZoomFunction();

	float m_fDistance;//�J�����Ǝ��_�̋���( x&z�������̓񎟌���ł� ).

	D3DXVECTOR3 m_vMoveSpd;	//���x.
	D3DXVECTOR3 m_vMoveAcc;	//�����x.

	//�ǂ���֓������̃t���O.
	struct BOOL3
	{
		bool x;
		bool y;
		bool z;
		BOOL3(){
			x = y = z = false;
		}
	}m_MoveFlg;

};

