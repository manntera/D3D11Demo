//����������������������������
//�������y�萔�o�b�t�@�z������
//����������������������������
/*�������e��s�񁥁���*/
cbuffer cbTransform:register(b0)
{
	column_major float4x4	transformMat;
	column_major float4x4	worldMat;
	column_major float4x4	viewMat;
	column_major float4x4	projMat;
	float4	viewVector;
};
//��������������������������
//�������y�\���̐錾�z������
//��������������������������
/*���������_IN������*/
struct vertexIn
{
	float4	pos			:	POSITION;
};
/*���������_OUT������*/
struct vertexOut
{
	float4	pos			:	SV_POSITION;
};
//��������������������������������
//�������y�V�F�[�_�[�R�[�h�z������
//��������������������������������
/*���������_�V�F�[�_������*/
vertexOut VS(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.pos = mul(In.pos, transformMat);

	return Out;
}