//����������������������������
//�������y�萔�o�b�t�@�z������
//����������������������������

//��������������������������
//�������y�\���̐錾�z������
//��������������������������
/*���������_IN������*/
struct vertexIn
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
/*���������_OUT������*/
struct vertexOut
{
	float4	pos			:	POSITION;
	float4	texUV			:	TEX_UV;
};
//��������������������������������
//�������y�V�F�[�_�[�R�[�h�z������
//��������������������������������
/*���������_�V�F�[�_������*/
vertexOut VS(vertexIn In)
{
	vertexOut Out;
	Out.pos = In.pos;
	Out.texUV = In.texUV;

	return Out;
}