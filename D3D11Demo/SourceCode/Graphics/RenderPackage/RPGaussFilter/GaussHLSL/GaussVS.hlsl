//����������������������������
//�������y�萔�o�b�t�@�z������
//����������������������������
/*�������e�N�X�`���̃T�C�Y������*/
cbuffer cbWindow:register(b0)
{
	float4 texSize : packoffset(c0);	// x�cWidth y�cHeight z�coffsetX w�coffsetY
};

//��������������������������
//�������y�\���̐錾�z������
//��������������������������
/*���������_IN������*/
struct vertexIn
{
	float4	pos		:	POSITION;
	float4	uv			:	TEX_UV;
};
/*���������_OUT������*/
struct vertexOut
{
	float4 pos    : SV_POSITION;
	float4 uv0 : TEX_UV0;   // �e�N�Z��
	float4 uv1 : TEX_UV1;   // �e�N�Z��
	float4 uv2 : TEX_UV2;   // �e�N�Z��
	float4 uv3 : TEX_UV3;   // �e�N�Z��
	float4 uv4 : TEX_UV4;   // �e�N�Z��
	float4 uv5 : TEX_UV5;   // �e�N�Z��
	float4 uv6 : TEX_UV6;   // �e�N�Z��
	float4 uv7 : TEX_UV7;   // �e�N�Z��
};
//��������������������������������
//�������y�V�F�[�_�[�R�[�h�z������
//��������������������������������
/*���������_�V�F�[�_������*/
vertexOut VS_x(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.pos = In.pos;
	Out.uv0 = In.uv + float4(-1.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv1 = In.uv + float4(-3.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv2 = In.uv + float4(-5.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv3 = In.uv + float4(-7.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv4 = In.uv + float4(-9.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv5 = In.uv + float4(-11.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv6 = In.uv + float4(-13.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	Out.uv7 = In.uv + float4(-15.0f / texSize.x, 0.0f, 0.0f, 0.0f);
	return Out;
}
/*���������_�V�F�[�_������*/
vertexOut VS_y(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.pos = In.pos;
	Out.uv0 = In.uv + float4(0.0f, -1.0f / texSize.y, 0.0f, 0.0f);
	Out.uv1 = In.uv + float4(0.0f, -3.0f / texSize.y, 0.0f, 0.0f);
	Out.uv2 = In.uv + float4(0.0f, -5.0f / texSize.y, 0.0f, 0.0f);
	Out.uv3 = In.uv + float4(0.0f, -7.0f / texSize.y, 0.0f, 0.0f);
	Out.uv4 = In.uv + float4(0.0f, -9.0f / texSize.y, 0.0f, 0.0f);
	Out.uv5 = In.uv + float4(0.0f, -11.0f / texSize.y, 0.0f, 0.0f);
	Out.uv6 = In.uv + float4(0.0f, -13.0f / texSize.y, 0.0f, 0.0f);
	Out.uv7 = In.uv + float4(0.0f, -15.0f / texSize.y, 0.0f, 0.0f);
	return Out;
}