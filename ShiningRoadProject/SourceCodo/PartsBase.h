#pragma once


//
//	�X�e�[�^�X�������ɕK�v�Ȃ̂������ɉ������B.
//
//	�A�Z���u���V�[���Ɋe�p�[�c�̃t�@�C���N���X���������悤.
//
//
//
//
//
//

#include "Global.h"
#include "SkinMesh.h"

#include "Object.h"


#include <vector>
#include <string>

//�X�e�[�^�X�񋓑̂̌^( �p���N���X�Œ�`���Ă��� ).
#define PARTS_STATUS_TYPE UCHAR

//========== �p�[�c�̊��N���X ==========//.
class clsPARTS_BASE : public clsSkinMesh , public clsObject
{
public:
	clsPARTS_BASE();
	virtual ~clsPARTS_BASE();
	
	//�쐬��.
	void Create();
	//���t���[��.
	void Update();
	//�`��.
	void Render(
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye,
		const D3DXVECTOR4 &vColor,
		const bool isAlpha );


	//�p�[�c�̃X�e�[�^�X��f���o��( �Y�����͊e�N���X�̗񋓑̂��Q�Ƃ��ꂽ�� ).
	int GetStatus( PARTS_STATUS_TYPE Num );
	//�X�e�[�^�X�Z�b�g( ������:�X�e�[�^�X�ɓ���鐔  ������:for���̃J�E���g ).
	template<class T>
	void SetStatus( const int iStatus, const T tNum );

protected:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	virtual void CreateProduct() = 0;//�e�V�[����Create.
	virtual void UpdateProduct() = 0;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.



private:

};

