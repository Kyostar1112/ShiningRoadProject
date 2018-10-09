#pragma once

#include "FactoryParts.h"

#include "Resource.h"

#include "RoboStatus.h"


//�A�������̃{�[����.
#define sBONE_NAME_LEG_TO_CORE		"JunctionCore"
#define sBONE_NAME_CORE_TO_HEAD		"JunctionHead"
#define sBONE_NAME_CORE_TO_ARM_L	"JunctionArmL"
#define sBONE_NAME_CORE_TO_ARM_R	"JunctionArmR"
#define sBONE_NAME_ARM_TO_WEAPON	"JunctionWeapon"

//����̉�]���m��Ɏg��.
#define  sBONE_NAME_WEAPON_VEC_ROOT	 "JunctionWeapon"	//"WeaponVecRoot"
#define  sBONE_NAME_WEAPON_VEC_END	 "WeaponVec"		//"WeaponVecEnd"



//�A�Z���u���V�[���̃��f������.
class clsASSEMBLE_MODEL
{
public:
	clsASSEMBLE_MODEL();
	virtual ~clsASSEMBLE_MODEL();

	//�I�����̂���p�[�c�̎��( �z��̓Y�����ɂȂ� ).
	enum enPARTS_TYPES : UCHAR
	{
		LEG = 0,
		CORE,
		HEAD,
		ARMS,
		WEAPON_L,
		WEAPON_R,

		ENUM_SIZE
	};

	//�A�Z���u���V�[���̊e�֐����Ŏg���܂�.
	void Create( clsResource* const pResource, clsROBO_STATUS* const pStatus, const bool isTitleScene = false );
	void UpDate();
	virtual void Render(
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj, 
		const D3DXVECTOR3& vLight, 
		const D3DXVECTOR3& vEye,
		const enPARTS_TYPES AlphaParts = enPARTS_TYPES::ENUM_SIZE );

	//���f���̏����Z�b�g.
	void Init( clsROBO_STATUS* const pStatus );

	//���f�����ς�.
	void AttachModel( const enPARTS enParts, const SKIN_ENUM_TYPE PartsNum );

	//�g�����X�t�H�[��.
	void SetPos( const D3DXVECTOR3 &vPos );
	void AddPos( const D3DXVECTOR3 &vVec );
	D3DXVECTOR3 GetPos() const;

	void SetRot( const D3DXVECTOR3 &vRot );
	void AddRot( const D3DXVECTOR3 &vRot );
	D3DXVECTOR3 GetRot() const;

	void SetScale( const float fScale );

	void SetAnimSpd( const double &dSpd );

	int GetPartsNum( const enPARTS_TYPES enParts );

	//�p�[�c�̃A�j���[�V�����ύX.
	bool PartsAnimChange( const enPARTS enParts, const int iIndex );

	//�p�[�c�̃{�[���̍��W���擾.
	D3DXVECTOR3 GetBonePos( const enPARTS enParts, const char* sBoneName );

	//�{�[�������݂��邩.
	bool ExistsBone( const enPARTS enParts, const char* sBoneName );


	//�p�[�c�̐F�w��.
	void SetPartsColor( const D3DXVECTOR4 &vColor, const unsigned int uiMaskNum );
	D3DXVECTOR4 GetPartsColor( const unsigned int uiMaskNum );
	void IncrementColor( const clsROBO_STATUS::enCOLOR_GAGE enColorGage );
	void DecrementColor( const clsROBO_STATUS::enCOLOR_GAGE enColorGage );
	//0.0f�`1.0f�ŕԂ�.
	float GetColorGradation( const clsROBO_STATUS::enCOLOR_GAGE enColorGage );
	std::vector< D3DXVECTOR4 > GetColor();

	//0~16�ŕԂ�.
	int GetColorRank( const clsROBO_STATUS::enCOLOR_GAGE enColorGage );

#if _DEBUG
	//�e�p�[�c��pos.
	D3DXVECTOR3 GetPartsPos( const UCHAR ucParts ) const;
#endif//#if _DEBUG

protected:

	//�p����Ŏg���Ă�.
	virtual void CreateProduct();
	virtual void UpdateProduct();

	//�r�̊p�x�𕐊���͎ʂ���.
	void FitJointModel( 
		clsPARTS_BASE *pMover, clsPARTS_BASE *pBace,
		const char *RootBone, const char *EndBone );

	//�F��f���o��.
	D3DXVECTOR4 CreateColor( 
		const enPARTS_TYPES AlphaParts, 
		const UINT uiIndex,
		const unsigned int uiMaskNum );

	//�A�j���[�V�������Z�b�g.
	void AnimReSet();

	//��]�l�}��.
	float GuardDirOver( float &outTheta ) const;

	void ModelUpdate();

	//�F.
	void UpdateColor( const clsROBO_STATUS::enCOLOR_GAGE enColorGage );

	double m_dAnimSpd;

	TRANSFORM m_Trans;

	clsResource* m_wpResource;

	std::unique_ptr< clsFACTORY_PARTS >	m_upPartsFactory;

	//�p�[�c�̐����̃|�C���^.
//	clsPARTS_BASE**	m_wppParts;
	std::vector< clsPARTS_BASE* >	m_vpParts;

private:

	//GetPartsNum�֐��̈�.
	enPARTS_TYPES m_enPartsNum[ enPARTS_TYPES::ENUM_SIZE ];

	//.
	std::vector< D3DXVECTOR4 >	m_vecvColor;

	//�F�̒i�K.
	int m_iColorRank[ clsROBO_STATUS::enCOLOR_GAGE_size ];

};

