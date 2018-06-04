#include "PartsBase.h"

const int iERROR_NUM = -1;


clsPARTS_BASE::clsPARTS_BASE() :
	m_StatusMax( 0 )
{
	
}

clsPARTS_BASE::~clsPARTS_BASE()
{
	m_viStatus.clear();
	m_viStatus.shrink_to_fit();

	m_StatusMax = 0;	
}



//�쐬��.
void clsPARTS_BASE::Create()
{
	CreateProduct();
}

//���t���[��.
void clsPARTS_BASE::Update()
{
	UpdateProduct();
	ModelUpdate( m_Trans );
}

//�`��.
void clsPARTS_BASE::Render(
	const D3DXMATRIX& mView, 
	const D3DXMATRIX& mProj, 
	const D3DXVECTOR3& vLight, 
	const D3DXVECTOR3& vEye,
	const D3DXVECTOR4 &vColor,
	const bool isAlpha )
{
	ModelRender( mView, mProj, vLight, vEye, vColor, isAlpha );
}


//�p�[�c�̃X�e�[�^�X��f���o��( �Y�����͊e�N���X�̗񋓑̂��Q�Ƃ��ꂽ�� ).
int clsPARTS_BASE::GetStatus( PARTS_STATUS_TYPE Num )
{
	//�X�e�[�^�X���͈̓I�[�o�[���Ă��Ȃ����̃`�F�b�N.
	isWithInRange( Num );

	return m_viStatus[Num];
}

//�X�e�[�^�X�Z�b�g( ������:�X�e�[�^�X�ɓ���鐔  ������:for���̃J�E���g ).
template<class T>
void clsPARTS_BASE::SetStatus( const int iStatus, const T tNum )
{
	PARTS_STATUS_TYPE Num = static_cast<PARTS_STATUS_TYPE>( tNum );

	//�X�e�[�^�X���͈̓I�[�o�[���Ă��Ȃ����̃`�F�b�N.
	isWithInRange( Num );

	m_viStatus[Num] = iStatus;
}



//�X�e�[�^�X.
void clsPARTS_BASE::SetStatusMax( PARTS_STATUS_TYPE Num )
{
	m_StatusMax = Num;
}
PARTS_STATUS_TYPE clsPARTS_BASE::GetStatusMax()
{
	return m_StatusMax;
}


//�X�e�[�^�X���͈̓I�[�o�[���Ă��Ȃ����̃`�F�b�N.
bool clsPARTS_BASE::isWithInRange( PARTS_STATUS_TYPE Num )
{
	//�͈͂��I�[�o�[������.
	if( Num >= m_StatusMax ){
		//�G���[�𑗂�t����.
		assert( !"�w�肳�ꂽ�p�[�c�X�e�[�^�X�̔ԍ��͔͈͊O�ł�" );
		return false;
	}
	return true;
}
