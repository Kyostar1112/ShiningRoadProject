#ifndef EFFECTS_H_
#define EFFECTS_H_

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���B4005:�Ē�`.
#pragma warning( disable : 4005 )

//==================================================
//	��ɂ��Ă����ׂ��w�b�_�A���C�u�����̓Ǎ�.
//==================================================
#include <stdio.h>

#include <D3D11.h>
#include <XAudio2.h>
#pragma comment( lib, "d3d11.lib" )

//==================================================
//	��������Effekseer�֌W �w�b�_�A���C�u�����̓Ǎ�.
//==================================================
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>


#if _DEBUG
#pragma comment( lib, "VS2013\\Debug\\Effekseer.lib" )
#pragma comment( lib, "VS2013\\Debug\\EffekseerRendererDX11.lib" )
#pragma comment( lib, "VS2013\\Debug\\EffekseerSoundXAudio2.lib" )
#else//#if _DEBUG
#pragma comment( lib, "VS2013\\Release\\Effekseer.lib" )
#pragma comment( lib, "VS2013\\Release\\EffekseerRendererDX11.lib" )
#pragma comment( lib, "VS2013\\Release\\EffekseerSoundXAudio2.lib" )
#endif//#if _DEBUG


//�uD3DX�`�v�g�p�ŕK�{.
//����:Effekseer�֌W����ɓǂݍ��ނ���.
#include <D3DX10.h>
#pragma comment( lib, "d3dx10.lib" )


//�V���O���g���̎��͂���.
//#define EFFECTS_CLASS_SINGLETON



//==================================================
//	�t���[�\�t�gEffekseer�̃f�[�^���g�����߂̃N���X.
//==================================================
class clsEffects
{
public:
	//�G�t�F�N�g��ޗ񋓑�.
	enum enEFFECTS : UCHAR
	{
		//Arbia.
		enEFFECTS_STEP = 0,	//asiato.v
		enEFFECTS_ARBIA_ATK,//arbia_kougeki.v
		enEFFECTS_WAVE,		//syougekiha.v
		enEFFECTS_KICK_HIT,	//kougeki.v

		//Enemy.
		enEFFECTS_ENEMY_ATK,//teki_kougeki.
		enEFFECTS_SLASH_HIT,//yarare.v
		enEFFECTS_SLASH_DISC,//bikkuri.v

		//Pendulum.
		enEFFECTS_PEND_FIRE,//hibana.v

		//TreasureBox.
		enEFFECTS_TRB_OPEN,	//takara_hasira.v
		enEFFECTS_TRB_LOOP,	//takara_nakami.v

		//Door.
		enEFFECTS_DOOR_DUST,//takara_nakami.v

		//for loop.
		enEFFECTS_MAX
	};


#ifdef EFFECTS_CLASS_SINGLETON
	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
	static clsEffects* GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//(static�ō쐬���ꂽ�̂�2��ڂ͖��������).
		static clsEffects s_Instance;
		return &s_Instance;
	}
#else//EFFECTS_CLASS_SINGLETON
	clsEffects();
#endif//EFFECTS_CLASS_SINGLETON
	~clsEffects();

	//�\�z�֐�.
	HRESULT Create( ID3D11Device* const pDevice,
					ID3D11DeviceContext* const pContext );
	//�j���֐�.
	HRESULT Destroy();
	//�f�[�^�Ǎ��֐�.
	HRESULT LoadData();
	//�f�[�^����֐�.
	HRESULT ReleaseData();

	//�`��.
	void Render( 
		const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vEye ) const;

	//�r���[�s��ݒ�.
	void SetViewMatrix( const D3DXMATRIX& mView ) const;
	//�v���W�F�N�V�����s��ݒ�.
	void SetProjectionMatrix( const D3DXMATRIX& mProj ) const;


	//�Đ��֐�.
	::Effekseer::Handle Play( const enEFFECTS EfcType, const D3DXVECTOR3 vPos ) const {
		return m_pManager->Play(
			m_pEffect[EfcType], vPos.x, vPos.y, vPos.z );
	};
	//�ꎞ��~.
	void Paused( const ::Effekseer::Handle handle, const bool bFlag ) const {
		m_pManager->SetPaused( handle, bFlag );	//bFlag:true = �ꎞ��~.
	}
	//��~.
	void Stop( const ::Effekseer::Handle handle ) const {
		m_pManager->StopEffect( handle );
	}
	//���ׂĒ�~.
	void StopAll( const ::Effekseer::Handle handle ) const {
		m_pManager->StopAllEffects();
	}

	//�T�C�Y�w��.
	void SetScale( const ::Effekseer::Handle handle, const D3DXVECTOR3 vScale ) const {
		m_pManager->SetScale( handle,
			vScale.x, vScale.y, vScale.z );
	}
	//�X�s�[�h�w��.
	void SetSpd( const ::Effekseer::Handle handle, const float fSpd ) const {
		m_pManager->SetSpeed( handle, fSpd );
	}
	//��]�w��.
	void SetRotation( const ::Effekseer::Handle handle, const D3DXVECTOR3 vRot ) const {
		m_pManager->SetRotation( handle,
			vRot.x, vRot.y, vRot.z );
	}
	void SetRotation( const ::Effekseer::Handle handle,
			const D3DXVECTOR3 vAxis, const float fAngle ) const {
		m_pManager->SetRotation( handle,
			::Effekseer::Vector3D( vAxis.x, vAxis.y, vAxis.z ),
			fAngle );
	}
	//�ʒu�w��.
	void SetLocation( const ::Effekseer::Handle handle, const D3DXVECTOR3 vPos ) const {
		m_pManager->SetLocation( handle,
			::Effekseer::Vector3D( vPos.x, vPos.y, vPos.z ) );
	}

	//�����Ă�?.
	bool PlayCheck( const ::Effekseer::Handle handle ) const
	{
		return m_pManager->Exists( handle );
	}



	//�x�N�^�[�ϊ��֐�.
	::Effekseer::Vector3D Vector3DDxToEfk( 
					const D3DXVECTOR3* pSrcVec3Dx ) const;
	D3DXVECTOR3 Vector3EfkToDx( 
					const ::Effekseer::Vector3D* pSrcVec3Efk ) const;

	//�s��ϊ��֐�.
	::Effekseer::Matrix44 MatrixDxToEfk(
					const D3DXMATRIX* pSrcMatDx ) const;
	D3DXMATRIX MatrixEfkToDx(
					const ::Effekseer::Matrix44* pSrcMatEfk ) const;


private:
#ifdef EFFECTS_CLASS_SINGLETON
	//������R�s�[���֎~����.
	clsEffects();
	clsEffects( const clsEffects& rhs );
	clsEffects& operator = ( const clsEffects& rhs ) const;
#endif//#ifdef EFFECTS_CLASS_SINGLETON

	//�G�t�F�N�g���쓮�����邽�߂ɕK�v.
	::Effekseer::Manager*			m_pManager;
	::EffekseerRenderer::Renderer*	m_pRender;
	::EffekseerSound::Sound*		m_pSound;
	//�G�t�F�N�g�f�[�^�Ɋ܂܂�鉹�Đ��ɕK�v.
	IXAudio2*						m_pXA2;
	IXAudio2MasteringVoice*			m_pXA2Master;


	//�G�t�F�N�g�̎�ނ��ƂɕK�v.
	::Effekseer::Effect*			m_pEffect[ enEFFECTS_MAX ];


};

//=======================================================
//	�g����.
//=======================================================

//.	//Main��Create�ɂ���
//	clsEffects::GetInstance()->Create( m_pDevice, m_pDeviceContext );
//	clsEffects::GetInstance()->LoadData();




//	//�G�t�F�N�g���o�������N���X�̃w�b�_�[��.
//	//����Ɠ����^�̕ϐ���錾����.
//	::Effekseer::Handle		m_Handle;


//	//----- h�ł̎g�p�� -----//.
//	//���O�ȗ��p.
//	clsEffects*				m_pEffect;
//	//�n���h�� eh = EffekseerHandle.
//	::Effekseer::Handle		m_ehBomb;


//	//----- cpp�ł̎g�p�� -----//.
//	//�R���X�g���N�^��Create�ɂ�.
//	m_pEffect = nullptr;.
//	if( m_pEffect == nullptr ){
//		m_pEffect = clsEffects::GetInstance();
//	}

//	//�o�������^�C�~���O.
//	if( !m_pEffect->PlayCheck( m_ehBomb ) ){
//		m_ehBomb = m_pEffect->Play( clsEffects::enEFFECTS_MgcDrk, m_vPos );
//	}
//	m_pEffect->SetLocation( m_ehBomb, m_vPos );

//	main�֐���Render��
//	clsEffects::GetInstance()->Render( m_mView, m_mProj, m_Camera.vEye );



//	//Release()�֐��ɂ�.
//	 m_pEffect = nullptr;.
//	���e�N���X�ł����delete�͂��Ă͂Ȃ�Ȃ�.


//�����.
	//�G�t�F�N�g���ɕK�v(�����G�t�F�N�g��3�o���Ȃ�3�K�v).


#endif//#ifndef EFFECTS_H_