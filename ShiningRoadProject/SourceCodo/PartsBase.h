#ifndef PARTS_BASE_H_
#define PARTS_BASE_H_


#include "Global.h"
#include "SkinMesh.h"

#include "Object.h"





//�X�e�[�^�X�񋓑̂̌^( �p���N���X�Œ�`���Ă���񋓑̂̌^ ).
//#define PARTS_STATUS_TYPE UCHAR
using PARTS_STATUS_TYPE = UCHAR;

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
		const D3DXVECTOR4& vColorBase = { 1.0f, 1.0f, 1.0f, 1.0f },
		const D3DXVECTOR4& vColorArmor = { 1.0f, 1.0f, 1.0f, 1.0f },
		const bool isAlpha = false );

	D3DXVECTOR3 GetBonePos( const char* sBoneName, const bool isLocalPos = false ) override;

	//�A�j���[�V�����ύX.//�ύX�ł���Ȃ�true, �ύX�ł��Ȃ��Ȃ�false���Ԃ�.
	bool PartsAnimChange( const int iIndex );

	//�p�[�c�̖��O���o����.
	void SetPartsName( const std::string &sPartsName );

	//�{�[�������݂��邩.
	bool ExistsBone( const char* sBoneName );

	void AddPosition( const D3DXVECTOR3& vPos ){
		SetPosition( GetPosition() + vPos );
	}

	void AddRotation( const D3DXVECTOR3& vRot ){
		SetRotation( GetRotation() + vRot );
	};

protected:
	//----- �e�p�[�c���Ƃ̊֐� -----//.
	virtual void CreateProduct() = 0;//�e�V�[����Create.
	virtual void UpdateProduct() = 0;//�e�V�[����Update.
	//----- �e�p�[�c���Ƃ̊֐� -----//.

	//�p�[�c�̖��O.
	std::string m_sPartsName;

private:

};

#endif//#ifndef PARTS_BASE_H_