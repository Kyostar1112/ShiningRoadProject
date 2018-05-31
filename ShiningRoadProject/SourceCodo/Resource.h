#ifndef RESOURCE_H_
#define RESOURCE_H_

#define _CRT_SECURE_NO_WARNINGS

const int iTEST_ROBO_PARTS_MODEL_MAX = 1;//�e�X�g���̃p�[�c�ő吔.

/*
//�e�X�g���f���ɑ���3�Ԃ̃��f�������蓖�Ă��.
	m_pMesh->AttachModel(
		m_wpResource->GetPartsModels( enPARTS::LEG, 3 ) );


//���܂�.
	m_pMesh->AttachModel(
		m_wpResource->GetSkinModels( clsResource::enSkinModel_Leg ) );
*/

#include "Global.h"
#include "DX9Mesh.h"
#include "CD3DXSKINMESH.h"


//�X�L�����b�V���񋓑̂̌^.
#define SKIN_ENUM_TYPE UCHAR

//�V���O���g���̎��͂���.
//#define RESOURCE_CLASS_SINGLETON


//3D���f���̂��ƃf�[�^���i�[����N���X.
//�V���O���g���ɂ��Ăǂ�����ł��Q�Ƃł���.
class clsResource
{
public:
	//�X�^�e�B�b�N���f�����.
	enum enSTATIC_MODEL : UCHAR
	{
		enStaticModel_Ground = 0,
		enStaticModel_Shpere,
		enStaticModel_Enemy,

		enStaticModel_Max
	};

	//�X�L�����f�����.
	enum enSKIN_MODEL : SKIN_ENUM_TYPE
	{
		enSkinModel_Player = 0,
		enSkinModel_Leg,

		enSkinModel_Max//���Œ胂�f����max.
	};

	//�g���Ƃ��͂��̏���.
	SKIN_ENUM_TYPE m_ucLegNum;	//�r�̐�.
	SKIN_ENUM_TYPE m_ucCoreNum;	//�R�A�̐�.
	SKIN_ENUM_TYPE m_ucHeadNum;	//���̐�.
	SKIN_ENUM_TYPE m_ucArmsNum;	//�r�̐�( ���E���ʂȂ̂ň�ł悢 ).
	SKIN_ENUM_TYPE m_ucWeaponNum;//����̐�.

	SKIN_ENUM_TYPE m_ucSkinModelMax;


#ifdef RESOURCE_CLASS_SINGLETON
	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
	static clsResource* GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//(static�ō쐬���ꂽ�̂�2��ڂ͖��������).
		static clsResource s_Instance;
		return &s_Instance;
	}
#else//#ifdef RESOURCE_CLASS_SINGLETON
	clsResource();
#endif//#ifdef RESOURCE_CLASS_SINGLETON
	~clsResource();

	//new����Ɏg��.
	void Create( const HWND hWnd, ID3D11Device* const pDevice, ID3D11DeviceContext* const pContext );


	//�X�^�e�B�b�N���f��( Attach�̈��� ).
	clsDX9Mesh* GetStaticModels( const enSTATIC_MODEL enModel ) const;


	//�X�L�����f��( Attach�̈��� )( �p�[�c�͂���ł�Attach�o���Ȃ� ).
	clsD3DXSKINMESH*	GetSkinModels( const enSKIN_MODEL enModel ) const;

	//���{�̃p�[�c��Attach����֐�.
	//������ : ���̃p�[�c?.
	//������ : ���̃p�[�c�̉��Ԗ�?.
	clsD3DXSKINMESH* GetPartsModels(
		const enPARTS enParts, const SKIN_ENUM_TYPE PartsNum );


#ifdef Inoue
	enSTATIC_MODEL ItoE( const int iNum ) const {
		return static_cast<enSTATIC_MODEL>( iNum );
	}

	int EtoI( const enSTATIC_MODEL iNum ) const {
		return static_cast<int>( iNum );
	}
#endif//#ifdef Inoue.

private:

#ifdef RESOURCE_CLASS_SINGLETON
	//������R�s�[���֎~����.
	clsResource();
	clsResource( const clsResource& rhs );
	clsResource& operator = ( const clsResource& rhs );
#endif//#ifdef RESOURCE_CLASS_SINGLETON

	//�X�^�e�B�b�N���f��.
	HRESULT		InitStaticModel( const HWND hWnd, ID3D11Device* const pDevice, ID3D11DeviceContext* const pContext );
	HRESULT		CreateStaticModel( LPSTR const fileName, const enSTATIC_MODEL enModel );
	HRESULT		ReleaseStaticModel( const enSTATIC_MODEL enModel );


	//�X�L�����f��.
	HRESULT		InitSkinModel( const HWND hWnd, ID3D11Device* const pDevice, ID3D11DeviceContext* const pContext );
	HRESULT		CreateSkinModel( LPSTR const fileName, const enSKIN_MODEL enModel );
	HRESULT		ReleaseSkinModel( const enSKIN_MODEL enModel );


	//�p�[�c�쐬.
	void CreatePartsGroup();//CreateParts�̏W����.
	void CreateParts( const enPARTS enParts );
	//CreateParts�ŕK�v�ȕϐ�����������.
	std::string SetVarToCreateParts(
		SKIN_ENUM_TYPE &ucStart,	//(out)���̃p�[�c�̎n�܂�ԍ�.
		SKIN_ENUM_TYPE &ucMax,	//(out)���̃p�[�c�̍ő�ԍ�.
		const enPARTS enParts );
		

	//GetSkinModels()�̈������ǂ̃p�[�c���Ƃ��̃p�[�c�̔ԍ���������o���֐�.
	//������ : ���̃p�[�c?.
	//������ : ���̃p�[�c�̉��Ԗ�?.
	enSKIN_MODEL GetPartsResourceNum( 
		const enPARTS enParts, const SKIN_ENUM_TYPE PartsNum ) const;

	//SetVarToCreateParts()��GetPartsResourceNum()�̕⏕.
	//���̃p�[�c�̍ŏ��̃i���o�[�����\�[�X�ԍ��ɂ��ċ����Ă����.
	SKIN_ENUM_TYPE GetPartsResourceStart( const enPARTS enParts ) const;


	HWND					m_hWnd;
	ID3D11Device*			m_pDevice11;
	ID3D11DeviceContext*	m_pCotext11;
	CD3DXSKINMESH_INIT		m_Si;

	clsDX9Mesh**			m_ppStaticModels;
	clsD3DXSKINMESH**		m_ppSkinModels;

	//�͈͓����`�F�b�N����֐�.
	bool IsRangeStaticModel( const enSTATIC_MODEL enModel ) const;
	bool IsRangeSkinModel( const enSKIN_MODEL enModel ) const;


	char m_FilePath[255];


};

#endif//#ifndef RESOURCE_H_