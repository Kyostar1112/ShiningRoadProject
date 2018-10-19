#pragma once

#include "Sprite2DCenter.h"

//���̎l�p.
class clsLINE_BOX
{
public:

	//��ɕω�����.
	enum class encBEFOR_CHANGE : UCHAR
	{
		NOTHING = 0,//�I�������玩���ł���ɂȂ�B���炪�I��ł͂����Ȃ�.

		WIDTH,
		HEIGHT,
		BOTH,	//���������ɕς��.
	};

	clsLINE_BOX(		
		ID3D11Device* const pDevice11,
		ID3D11DeviceContext* const pContext11 );

	virtual ~clsLINE_BOX();


	virtual void Update();

	virtual void Render();

	void SetPos( const D3DXVECTOR3 &vPos );
	void AddPos( const D3DXVECTOR3 &vPos );
	void SetSize( const D3DXVECTOR3 &vSize );
	void SetSize( const float &fSize );
	void AddSize( const D3DXVECTOR3 &vSize );
	void AddScale( const D3DXVECTOR3 &vScale );
	void AddScale( const float &fScale );

	//���킶��傫����ς����������Ƃ��Ɏg��.
	void SetSizeTarget( const D3DXVECTOR3 &vSize );
	void AddChangeData( 
		const float fWidthSpd,
		const float fHeightSpd,
		const encBEFOR_CHANGE encBefor );
	//�ω�����false.
	bool isStopChange();

	D3DXVECTOR3 GetPos() const;
	D3DXVECTOR3 GetSize() const;

	void SetAlpha( const float fAlpha );
	//�͈͂�over�����false���Ԃ��Ă���.
	bool AddAlpha( const float fAlpha );

protected:

	virtual void SetColor( const D3DXVECTOR3& vColor ){
		for( char i=0; i<2; i++ ){
			m_upLineH[i]->SetColor( vColor );
			m_upLineV[i]->SetColor( vColor );
			m_upLineJoint[i]->SetColor( vColor );
			m_upLineJoint[ i + 2 ]->SetColor( vColor );
		}
	}

	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vSize;//���a.

	float		m_fAlpha;	//�A���t�@�l.

private:
	//�����`���.
	void SetUpBox();

	//�p��scale.
	void SetUpJointSize();

	//Target�Ɍ����ăT�C�Y��ς���.
	void AddSizeForTarget();

	std::unique_ptr< clsSPRITE2D_CENTER > m_upLineH[2];//����( ���� )( 0���� ).
	std::unique_ptr< clsSPRITE2D_CENTER > m_upLineV[2];//����( �c�� )( 0���� ).
	std::unique_ptr< clsSPRITE2D_CENTER > m_upLineJoint[4];//�p( ���ォ�玞�v��� ).


	D3DXVECTOR3 m_vSizeTarget;
	D3DXVECTOR3 m_vChangeSpd;
	bool m_isChangeBigW;//true�Ȃ�傫���ς��.
	bool m_isChangeBigH;
	encBEFOR_CHANGE m_encBeforChange;

private:


	//�ω����~�܂��Ă��邩.
	bool m_isStopChange;

};
