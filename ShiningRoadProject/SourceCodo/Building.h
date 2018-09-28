#ifndef BUILDING_H_
#define BUILDING_H_

#include "Global.h"
#include "CharaStatic.h"
#include "Sprite.h"
#include <vector>

//�X�e�[�W�ɐݒu����r���N���X.
//�傫����ς��Ă��e�N�X�`���������L�΂���邱�Ƃ͂Ȃ�.
//����ȃu���b�N��������.
class clsBUILDING
{
public:
	clsBUILDING( 
		ID3D11Device* const pDevice11,
		ID3D11DeviceContext* const pContext11,
		 clsDX9Mesh* const pModel );
	~clsBUILDING();

	//���t���[���g���Ă͂����Ȃ�.
	//.
	void Update();

	void Render(
		const D3DXMATRIX &mView, 
		const D3DXMATRIX &mProj,
		const D3DXVECTOR3 &vLight, 
		const D3DXVECTOR3 &vEye );

	//���C�p.
	clsDX9Mesh* GetModelPtr();

	D3DXVECTOR3 GetPos();
	void SetPos( const D3DXVECTOR3& vPos );
	void AddPos( const D3DXVECTOR3& vPos );

	D3DXVECTOR3 GetRot();
	void SetRot( const D3DXVECTOR3& vRot );
	void AddRot( const D3DXVECTOR3& vRot );

	D3DXVECTOR3 GetScale();
	void SetScale( const D3DXVECTOR3& vScale );
	void AddScale( const D3DXVECTOR3& vScale );


private:

	struct TRANSFORM
	{
		D3DXVECTOR3 vPos;
		D3DXVECTOR3 vRot;
		D3DXVECTOR3 vScale;
	};

	enum enWALL_DIRECTION : int
	{
		enWD_SOUTH = 0,
		enWD_EAST,
		enWD_NORTH,
		enWD_WEST,

		enWALL_DIRECTION_size
	};

	//�^�C���̖ڕW�������.
	void SetTileNumTargetTop( unsigned int& puiRow, unsigned int& puiCol );
	//�ڕW�̐��ɍ��킹�ă^�C���𑝌�����.
	void SetTileNumTop( const unsigned int uiROW, const unsigned int uiCOL );
	//�^�C������ׂ�.
	void SetTransformTop();

	//Z=�k�Ɠ�.//�����͎�����.
	void SetTileNumTargetSide( 
		unsigned int& puiRowZ, unsigned int&  puiColZ,
		unsigned int& puiRowX, unsigned int&  puiColX );
	//�ڕW�̐��ɍ��킹�ă^�C���𑝌�����.
	void SetTileNumSide( 
		const unsigned int uiROW_Z, const unsigned int uiCOL_Z,
		const unsigned int uiROW_X, const unsigned int uiCOL_X );
	//�^�C������ׂ�.
	void SetTransformSide();

	//�����ɓ��ꂽ�^�C�������S���猩�ĉ��x�̈ʒu�ɂ��邩.
	float GetTileTheta( 
		const TRANSFORM& Tile, const TRANSFORM& Center,
		float* const pfTheta, float* const pfDistance ) const;
	//��]�ɉ����č��W���X�V����.
	D3DXVECTOR3 GetTilePosForRotation( 
		D3DXVECTOR3* const vTilePos,
		const D3DXVECTOR3& vCenterPos,
		const float fTileTheta, 
		const float fTileDistance );


	//�{��.
	TRANSFORM m_Trans;
	//���.
	std::vector< std::vector< TRANSFORM > > m_vvTop;
	//����.
	std::vector< std::vector< TRANSFORM > > m_vvSide[ enWALL_DIRECTION_size ];


	std::unique_ptr< clsCharaStatic > m_upBox;


	std::unique_ptr< clsSprite > m_upTop;
	std::unique_ptr< clsSprite > m_upSide;

	ID3D11Device*  m_wpDevice;
	ID3D11DeviceContext* m_wpContext;

};
#endif//#ifndef BUILDING_H_