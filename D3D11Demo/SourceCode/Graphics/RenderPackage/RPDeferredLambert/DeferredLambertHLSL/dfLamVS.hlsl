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
	float4 uv		 : TEX_UV;
	float4 sPos		:sPos;
};
//��������������������������������
//�������y�V�F�[�_�[�R�[�h�z������
//��������������������������������
/*���������_�V�F�[�_������*/
vertexOut VS(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.pos = In.pos;
	Out.uv = In.uv;
	Out.sPos = In.pos;
	return Out;
}