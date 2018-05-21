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

		enSkinModel_Max,
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



	//�X�^�e�B�b�N���f��.
	HRESULT		InitStaticModel( const HWND hWnd, ID3D11Device* const pDevice, ID3D11DeviceContext* const pContext );
	HRESULT		CreateStaticModel( LPSTR const fileName, const enSTATIC_MODEL enModel );
	clsDX9Mesh* GetStaticModels( const enSTATIC_MODEL enModel ) const;
	HRESULT		ReleaseStaticModel( const enSTATIC_MODEL enModel );


	//�X�L�����f��.
	HRESULT		InitSkinModel( const HWND hWnd, ID3D11Device* const pDevice, ID3D11DeviceContext* const pContext );
	HRESULT		CreateSkinModel( LPSTR const fileName, const enSKIN_MODEL enModel );
	clsD3DXSKINMESH*	GetSkinModels( const enSKIN_MODEL enModel ) const;
	HRESULT		ReleaseSkinModel( const enSKIN_MODEL enModel );

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