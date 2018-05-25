#ifndef RESOURCE_H_
#define RESOURCE_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Global.h"
#include "DX9Mesh.h"
#include "CD3DXSKINMESH.h"



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

		enStaticModel_Max,
	};

	//�X�L�����f�����.
	enum enSKIN_MODEL : UCHAR
	{
		enSkinModel_Player = 0,

		enSkinModel_Max,//���Œ胂�f����max.
	};

	//�r.
	enum enLEG_MODEL : UCHAR
	{
		enLegModel0 = enSkinModel_Max,
		enLegModel1,
		enLegModel2,
		enLegModel3,

		enLegModelMax,
	};
	//�R�A.
	enum enCORE_MODEL : UCHAR
	{
		enCoreModel0 = enLegModelMax,
		enCoreModel1,
		enCoreModel2,
		enCoreModel3,

		enCoreModelMax,
	};
	//��.
	enum enHEAD_MODEL : UCHAR
	{
		enHeadModel0 = enCoreModelMax,
		enHeadModel1,
		enHeadModel2,
		enHeadModel3,
		  
		enHeadModelMax,
	};
	//���r.
	enum enARML_MODEL : UCHAR
	{
		enArmLModel0 = enHeadModelMax,
		enArmLModel1,
		enArmLModel2,
		enArmLModel3,
		  
		enArmLModelMax,
	};
	//�E�r.
	enum enARMR_MODEL : UCHAR
	{
		enArmRModel0 = enArmLModelMax,
		enArmRModel1,
		enArmRModel2,
		enArmRModel3,
		  
		enArmRModelMax,
	};
	//����.
	enum enWEAPON_MODEL : UCHAR
	{
		enWeaponModel0 = enArmRModelMax,
		enWeaponModel1,
		enWeaponModel2,
		enWeaponModel3,

		enWeaponModelMax,//�S�X�L�����f����max.
	};
	//���ׂẴX�L�����f���̐�.
	enum enALL_SKIN_MODEL : UCHAR
	{
		enAllPartsMax = enWeaponModelMax
	};

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


	//�X�^�e�B�b�N���f��.
	clsDX9Mesh* GetStaticModels( const enSTATIC_MODEL enModel ) const;


	//�X�L�����f��.
	clsD3DXSKINMESH*	GetSkinModels( const enSKIN_MODEL enModel ) const;

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
		UCHAR &ucStart,	//(out)���̃p�[�c�̎n�܂�ԍ�.
		UCHAR &ucMax,	//(out)���̃p�[�c�̍ő�ԍ�.
		const enPARTS enParts );
		

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