#pragma once 


#include "AssembleModel.h"


#define sBONE_NAME_COL_JOINT	"Joint"//00�`xx.

#define sBONE_NAME_COL_CORE "Jenerator"//�R�A�̒��S.
#define sBONE_NAME_COL_HEAD "Center"//���̒��S.




class clsMISSION_MODEL : public clsASSEMBLE_MODEL
{
public:
	clsMISSION_MODEL();
	~clsMISSION_MODEL();

	//�{�[���ɕK�v�ȏ��.
	struct BONE_SET
	{
		std::string sName;
		D3DXVECTOR3 vPos;
		int			iParts;//���̃p�[�c��(enPARTS���L���X�g���Ă��̕ϐ��ɓ����).
	};

	enum enCOL_PARTS : UCHAR
	{
		enCOL_PARTS_LEG = 0,
		enCOL_PARTS_CORE,
		enCOL_PARTS_HEAD,
		enCOL_PARTS_ARMS,

		enCOL_PARTS_size
	};


	//�����̃p�[�c�̓����蔻��̏��쐬.
	//�߂�l�S�p�[�c�̓����蔻��̐�.
	int CreateColStateBones();

	//�{�[���̐����m�肷��( CreateColStateBones�֐��̌�Ɏg�� ).
	void FixBoneStates();

	//�e�p�[�c�̓����蔻��̐���Ԃ�.
	int GetColNum( const enCOL_PARTS enColParts );

	//�����蔻��̍��W�̔z������ׂĕԂ�.
	std::vector< D3DXVECTOR3 > GetColPosArr();

private:

	//.
	//�߂�l���̃p�[�c�̓����蔻��̐�.
	int CreateColStateBone( const enCOL_PARTS enColParts );

	void CreateProduct() final;

	//�{�[�����.
	std::vector< BONE_SET > m_vColStates;
	int						m_iColStateIndex;

	int m_iColNum[enCOL_PARTS_size];//�e�p�[�c�̓����蔻��̐�.

	int m_iColMax;//�����蔻��̍��v��.

};

