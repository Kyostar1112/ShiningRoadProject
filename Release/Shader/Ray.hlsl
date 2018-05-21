//�O���[�o��.

cbuffer global
{
	matrix	g_mWVP;	//WorldViewProj�̕ϊ��s��.
	float4	g_vColor;//�F.
};

//�o�[�e�b�N�X�V�F�[�_.
float4 VS( float4 Pos : POSITION ) : SV_Position
{
	Pos = mul( Pos, g_mWVP );
	return Pos;
}

//�s�N�Z���V�F�[�_.
float4 PS( float4 Pos : SV_Position ) : SV_Target
{
	return g_vColor;
}
