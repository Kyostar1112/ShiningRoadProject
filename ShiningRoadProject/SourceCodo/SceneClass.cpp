#include "SceneClass.h"
#include <Windows.h>


//���C�g����.
const D3DXVECTOR3 vLIGHT_DIR = { 0.0f, 0.01f, 0.02f };
//�J�����̂��.
const float fZOOM = static_cast<float>( D3DX_PI / 4.0 );
//�`����E����.
const float fRENDER_LIMIT = 150.0f;


//================================//
//========== ���N���X ==========//
//================================//
clsSCENE_BASE::clsSCENE_BASE( clsPOINTER_GROUP* const ptrGroup ) :
	m_wpDevice( ptrGroup->GetDevice() ),
	m_wpContext( ptrGroup->GetContext() ),
	m_wpViewPort( ptrGroup->GetViewPort() ),
	m_wpPtrGroup( ptrGroup ),
	m_wpDxInput( ptrGroup->GetDxInput() ),
	m_wpResource( ptrGroup->GetResource() ),
	m_wpEffects( ptrGroup->GetEffects() ),
	m_wpSound( ptrGroup->GetSound() ),
	m_wpCamera( ptrGroup->GetCamera() )
{
	D3DXMatrixIdentity( &m_mView );
	D3DXMatrixIdentity( &m_mProj );	
	m_vLight = vLIGHT_DIR;
}

clsSCENE_BASE::~clsSCENE_BASE()
{
	m_wpCamera = nullptr;
	m_wpSound = nullptr;
	m_wpEffects = nullptr;
	m_wpResource = nullptr;
	m_wpDxInput = nullptr;
	m_wpPtrGroup = nullptr;
	m_wpViewPort = nullptr;
	m_wpContext = nullptr;
	m_wpDevice = nullptr;
}


//�V�[���쐬����ɁuSceneManager.cpp�v�́uSwitchScene�v�֐����Ŏg�p����Ă���.
void clsSCENE_BASE::Create()
{
	CreateProduct();
}

//���[�v���̏���( �������֐����ŕύX����ƍ��̃V�[�����j������A.
//				  �w�肵���V�[������������� ).
void clsSCENE_BASE::Update( enSCENE &nextScene )
{
	UpdateProduct( nextScene );

	DebugChangeScene( nextScene );
}

//�V�[�����̃I�u�W�F�N�g�̕`��֐��̂܂Ƃ�.
void clsSCENE_BASE::Render()
{
	//�J�����֐�.
	Camera();
	//�v���W�F�N�V�����֐�.
	Proj();

	RenderProduct();
}


D3DXVECTOR3 clsSCENE_BASE::GetCameraPos() const
{
	ASSERT_IF_NULL( m_wpCamera );
	return m_wpCamera->GetPos();
}
D3DXVECTOR3 clsSCENE_BASE::GetCameraLookPos() const
{
	ASSERT_IF_NULL( m_wpCamera );
	return m_wpCamera->GetLookPos();
}


//3D���W���X�N���[��( 2D )���W�ւƕϊ�����.dimensions(����) conversion(�ϊ�)
D3DXVECTOR3 clsSCENE_BASE::ConvDimPos( const D3DXVECTOR3 &v3DPos )
{
	D3DXVECTOR3 v2DPos;
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity( &mWorld );
	D3DXVec3Project( &v2DPos, &v3DPos, m_wpViewPort, &m_mProj, &m_mView, &mWorld );
	return v2DPos;
}


//�f�o�b�O�p�V�[���؂�ւ�.
void clsSCENE_BASE::DebugChangeScene( enSCENE &nextScene ) const
{
	if( GetAsyncKeyState( VK_F5 ) & 0x1 ){
		nextScene = enSCENE::TITLE;
	}
	else if( GetAsyncKeyState( VK_F6 ) & 0x1 ){
		nextScene = enSCENE::ASSEMBLE;
	}
	else if( GetAsyncKeyState( VK_F7  ) & 0x1 ){
		nextScene = enSCENE::MISSION;
	}
	else if( GetAsyncKeyState( VK_F8  ) & 0x1 ){
		nextScene = enSCENE::ENDING;
	}
}

//============================================================
//	�J�����֐�.
//============================================================
void clsSCENE_BASE::Camera()
{
	//�r���[(�J����)�ϊ�.
	D3DXVECTOR3 vUpVec	( 0.0f, 1.0f, 0.0f );	//����ʒu.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)�r���[�v�Z����.
		&GetCameraPos(), &GetCameraLookPos(), &vUpVec );

}
//============================================================
//	�v���W�F�N�V�����֐�.
//============================================================
void clsSCENE_BASE::Proj()
{
	//�v���W�F�N�V����(�ˉe�s��)�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,			//(out)�v���W�F�N�V�����v�Z����.
		fZOOM,	//y�����̎���(���W�A���w��)������傫�������王�삪�����Ȃ�.
		static_cast<FLOAT>( WND_W ) / static_cast<FLOAT>( WND_H ),//�A�X�y�N�g��(��/����).
		0.1f,				//�߂��r���[���ʂ�z�l.
		fRENDER_LIMIT );	//�����r���[���ʂ�z�l.
}
