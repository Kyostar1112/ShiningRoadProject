//�O���[�o���ϐ�.
//�e�N�X�`���̓��W�X�^�[ t(n).
Texture2D		g_Texture	: register( t0 );
//�T���v���[�̓��W�X�^�[ s(n).
SamplerState	g_Sampler	: register( s0 );

//�R���X�^���g�o�b�t�@.
cbuffer	global	: register( b0 )
{
	matrix	g_mW			: packoffset( c0 );
	float4	g_vColor		: packoffset( c4 );
	float	g_fViewPortW	: packoffset( c5 );
	float	g_fViewPortH	: packoffset( c6 );
	float2	g_vUV			: packoffset( c7 );
	float	g_fPulse		: packoffset( c8 );
	float	g_fPulseOffset	: packoffset( c9 );
	int		g_iBlock		: packoffset( c10 );
	int		g_iSeed			: packoffset( c11 );
	float2	g_vNoiseStart	: packoffset( c12 );
	float2	g_vNoiseEnd		: packoffset( c13 );
};


//�o�[�e�b�N�X�V�F�[�_�̏o�̓p�����[�^.
struct VS_OUT
{
	float4	Pos	: SV_Position;
	float2	UV	: TEXCOORD;
};

//========== �֐� ==========//.
float random( float2 TexCoord )
{
	return frac( sin( dot( TexCoord.xy, float2( 12.9898, 78.233 ) ) + g_iSeed ) * 43758.5453 );
}

float noise( float2 st )
{
	float2 p = floor( st );
	return random( p );
}
//========== �֐� ==========//.




//�o�[�e�b�N�X�V�F�[�_.
VS_OUT VS_Main( float4 Pos	: POSITION,
				float2 UV	: TEXCOORD )
{
	//������.
	VS_OUT	output = ( VS_OUT )0;

	output.Pos = mul( Pos, g_mW );

	//�X�N���[�����W�ɍ��킹��v�Z.
	output.Pos.x = ( output.Pos.x / g_fViewPortW ) * 2 - 1;
	output.Pos.y = 1 - ( output.Pos.y / g_fViewPortH ) * 2;

	//UV�ݒ�.
	output.UV = UV;

	//UV���W�����炷.
	output.UV.x += g_vUV.x;
	output.UV.y += g_vUV.y;

	return output;
}

//�s�N�Z���V�F�[�_.

//�ʏ�.
float4 PS_Main( VS_OUT input )	: SV_Target
{
	float4 color =
		g_Texture.Sample( g_Sampler, input.UV );//�F��Ԃ�.

	color *= g_vColor;

	return color;
}

//�m�C�Y.
float4 PS_Noise( VS_OUT input ) : SV_Target
{
	float4 color =
		g_Texture.Sample( g_Sampler, input.UV );//�F��Ԃ�.

	//----- �m�C�Y -----//.
	//�p���X.
	float2 uv = input.UV;
	float x = 2 * uv.y;
	uv.x += g_fPulse * sin( 10 * x + g_fPulseOffset ) * ( - ( x - 1 ) * ( x - 1 ) + 1 );
	float4 col = g_Texture.Sample( g_Sampler, uv );
	color = col;
	//�u���b�N.
	float c = noise( input.UV * g_iBlock );
	color *= g_Texture.Sample( g_Sampler, input.UV * c );
	//----- �m�C�Y �I�� -----//.

	color *= g_vColor;

	return color;
}


