//����������������������������
//�������y�萔�o�b�t�@�z������
//����������������������������
/*������WINDOW�̍L��������*/
cbuffer cbWindow:register(b0)
{
	float4 windowScale : packoffset(c0);
};

//��������������������������
//�������y�\���̐錾�z������
//��������������������������
/*���������_IN������*/
struct vertexIn
{
	float4	rect			:	RECT;
};
/*���������_OUT������*/
struct vertexOut
{
	float4	rect			:	RECT;
};
//��������������������������������
//�������y�V�F�[�_�[�R�[�h�z������
//��������������������������������
/*���������_�V�F�[�_������*/
vertexOut VS(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.rect.x = ((In.rect.x / windowScale.x) - 0.5) * 2;
	Out.rect.y = ((In.rect.y / windowScale.y) - 0.5) * 2;
	Out.rect.z = (In.rect.z / windowScale.x);
	Out.rect.w = (In.rect.w / windowScale.y);
	return Out;
}