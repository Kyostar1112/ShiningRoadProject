#pragma once



#include "Global.h"
#include "SkinMesh.h"

#include "Object.h"



//�R���X�g���N�^�ł̔z�񏉊����̈�.
#pragma warning( disable : 4351 )


//�X�e�[�^�X�񋓑̂̌^( �p���N���X�Œ�`���Ă���񋓑̂̌^ ).
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

	//�A�j���[�V�����ύX.//�ύX�ł���Ȃ�true, �ύX�ł��Ȃ��Ȃ�false���Ԃ�.
	bool PartsAnimChange( const int iIndex );

protected:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	virtual void CreateProduct() = 0;//�e�V�[����Create.
	virtual void UpdateProduct() = 0;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.



private:

};

