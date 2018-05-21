//�O���[�o���ϐ�.

//�e�N�X�`���̓��W�X�^�[t(n).
Texture2D		g_texColor	: register(t0);
//�T���v���[�̓��W�X�^�[s(n).
SamplerState	g_samLinear	: register(s0);

//�R���X�^���g�o�b�t�@.
cbuffer global
{
	matrix	g_mWVP;		//���[���h,�r���[,�v���W�F�N�V���������s��.
	float4	g_vColor;	//�F.
	float4	g_fAlpha;	//���ߒl.
};

//���_�V�F�[�_�̏o�̓p�����[�^.
struct VS_OUT
{
	float4	Pos	: SV_Position;	//�ʒu.
	float2	Tex : TEXCOORD;		//�e�N�X�`��.
};

//���_�V�F�[�_.
VS_OUT	VS( float4 Pos	: POSITION,
			float2 Tex	: TEXCOORD )
{
	VS_OUT Out = (VS_OUT)0;
	Out.Pos = mul( Pos, g_mWVP );
	//�e�N�X�`�����W.
	Out.Tex = Tex;

	return Out;
}

//�s�N�Z���V�F�[�_.
float4 PS( VS_OUT In )	: SV_Target
{
	float4 color
		= g_vColor * g_texColor.Sample( g_samLinear, In.Tex );

	return color * g_fAlpha.x;
}


