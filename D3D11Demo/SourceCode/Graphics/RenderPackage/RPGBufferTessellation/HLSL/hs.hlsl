//����������������������������
//�������y�萔�o�b�t�@�z������
//����������������������������
/*�������e��s�񁥁���*/
cbuffer cbTessPram:register(b1)
{
	float4	tessPram;
};

//��������������������������
//�������y�\���̐錾�z������
//��������������������������
/*�������n��IN������*/
struct hullIn
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
/*�������n���p�b�`�萔OUT������*/
struct constHullOut
{
	float edges[4]:SV_TessFactor;
	float inside[2]:SV_InsideTessFactor;
};
/*�������n��OUT������*/
struct hullOut
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
//��������������������������������
//�������y�V�F�[�_�[�R�[�h�z������
//��������������������������������
/*�������n���p�b�`�萔�V�F�[�_������*/
constHullOut ConstHS(InputPatch<hullIn, 4> ip, uint PatchID :SV_PrimitiveID)
{
	constHullOut Out;

	Out.edges[0] = Out.edges[1] = Out.edges[2] = Out.edges[3] = tessPram.x;
	Out.inside[0] = Out.inside[1] = tessPram.y;

	return Out;
}
/*�������n���V�F�[�_������*/
[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(4)]
[patchconstantfunc("ConstHS")]
hullOut HS(InputPatch<hullIn, 4> In, uint i:SV_OutputControlPointID, uint PatchID : SV_PrimitiveID)
{
	hullOut Out;

	Out.pos = In[i].pos;
	Out.texUV = In[i].texUV;

	return Out;
}