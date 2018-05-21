#include "Common.h"

clsCommon::clsCommon()
{
	m_pDevice11 = nullptr;
	m_pDeviceContext11 = nullptr;
	m_pBlendState = nullptr;
};
clsCommon::~clsCommon()
{
	if( m_pBlendState != nullptr ){
		m_pBlendState->Release();
		m_pBlendState = nullptr;
	}

	//�����ł͊J�����Ȃ�.
	m_pDeviceContext11 = nullptr;
	m_pDevice11 = nullptr;
};


//============================================================
//����(�A���t�@�u�����h)�ݒ�̐؂�ւ�.
//============================================================
void clsCommon::SetBlend( const bool flg )
{
	//�A���t�@�u�����h�p�u�����h�X�e�[�g�\����.
	//png�t�@�C�����ɃA���t�@��񂪂���̂ŁA
	//���߂���悤�Ƀu�����h�X�e�[�g��ݒ肷��.
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof( D3D11_BLEND_DESC ) );//������.

	blendDesc.IndependentBlendEnable
		= false;//false:RenderTarget[0]�̃����o�[�݂̂��g�p����.
				//true :RenderTarget[0�`7]���g�p�ł���.
				//      (�����_�[�^�[�Q�b�g���ɓƗ������u�����h����)
	blendDesc.AlphaToCoverageEnable
		= false;//true :�A���t�@�g�D�J�o���b�W���g�p����.
	blendDesc.RenderTarget[0].BlendEnable
		= flg;	//true :�A���t�@�u�����h���g�p����.
	blendDesc.RenderTarget[0].SrcBlend	//���f�ނɑ΂���ݒ�.
		= D3D11_BLEND_SRC_ALPHA;		//	�A���t�@�u�����h���w��.
	blendDesc.RenderTarget[0].DestBlend	//�d�˂�f�ނɑ΂���ݒ�.
		= D3D11_BLEND_INV_SRC_ALPHA;	//	�A���t�@�u�����h�̔��]���w��.

	blendDesc.RenderTarget[0].BlendOp	//�u�����h�I�v�V����.
		= D3D11_BLEND_OP_ADD;			//	ADD:���Z����.

	blendDesc.RenderTarget[0].SrcBlendAlpha	//���f�ނ̃A���t�@�ɑ΂���ݒ�.
		= D3D11_BLEND_ONE;					//	���̂܂܎g�p.
	blendDesc.RenderTarget[0].DestBlendAlpha//�d�˂�f�ނ̃A���t�@�ɑ΂���ݒ�.
		= D3D11_BLEND_ZERO;					//	�������Ȃ�.

	blendDesc.RenderTarget[0].BlendOpAlpha	//�A���t�@�̃u�����h�I�v�V����.
		= D3D11_BLEND_OP_ADD;				//	ADD:���Z����.

	blendDesc.RenderTarget[0].RenderTargetWriteMask	//�s�N�Z�����̏������݃}�X�N.
		= D3D11_COLOR_WRITE_ENABLE_ALL;				//	�S�Ă̐���(RGBA)�ւ̃f�[�^�̊i�[��������.

	//�u�����h�X�e�[�g�쐬.
	if( FAILED(
		m_pDevice11->CreateBlendState(
			&blendDesc, &m_pBlendState ) ) )
	{
		MessageBox( NULL, "�u�����h�X�e�[�g�쐬���s", "clsCommon::SetBlend", MB_OK );
	}

	//�u�����h�X�e�[�g�̐ݒ�.
	UINT mask = 0xffffffff;	//�}�X�N�l.
	m_pDeviceContext11->OMSetBlendState(
		m_pBlendState, NULL, mask );

}






