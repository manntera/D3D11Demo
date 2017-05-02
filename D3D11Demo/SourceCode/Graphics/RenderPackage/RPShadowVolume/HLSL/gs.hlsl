//����������������������������
//�������y�萔�o�b�t�@�z������
//����������������������������
/*�������e��s�񁥁���*/
cbuffer cbLight:register(b1)
{
	float4 lightVector;
};

//��������������������������
//�������y�\���̐錾�z������
//��������������������������
/*���������_IN������*/
struct geometryIn
{
	float4	pos			:	POSITION;
};
/*���������_OUT������*/
struct geometryOut
{
	float4	pos		:	SV_POSITION;
};
//��������������������������������
//�������y�V�F�[�_�[�R�[�h�z������
//��������������������������������
/*���������_�V�F�[�_������*/
[maxvertexcount(24)]
void	GS(triangle geometryIn In[3], inout TriangleStream<geometryOut> TriStream)
{
	geometryOut Out;
	float4 pold[6];

	for (int i = 0; i < 3; i++)
	{
		Out.pos = In[i].pos;
		pold[i] = Out.pos;
		TriStream.Append(Out);		//1���_
	}
	TriStream.RestartStrip();		//1�|��
	for (int i = 0; i < 3; i++)
	{
		Out.pos.x = In[i].pos.x + (lightVector.x * 1000);
		Out.pos.y = In[i].pos.y + (lightVector.y * 1000);
		Out.pos.z = In[i].pos.z + (lightVector.z * 1000);
		Out.pos.w = In[i].pos.w;
		pold[i+3] = Out.pos;
		TriStream.Append(Out);		//1���_
	}
	Out.pos = pold[0];
	TriStream.Append(Out);
	Out.pos = pold[3];
	TriStream.Append(Out);
	Out.pos = pold[4];
	TriStream.Append(Out);
	TriStream.RestartStrip();		//1�|��

	Out.pos = pold[0];
	TriStream.Append(Out);
	Out.pos = pold[4];
	TriStream.Append(Out);
	Out.pos = pold[1];
	TriStream.Append(Out);
	TriStream.RestartStrip();		//1�|��

	Out.pos = pold[1];
	TriStream.Append(Out);
	Out.pos = pold[4];
	TriStream.Append(Out);
	Out.pos = pold[5];
	TriStream.Append(Out);
	TriStream.RestartStrip();		//1�|��

	Out.pos = pold[4];
	TriStream.Append(Out);
	Out.pos = pold[5];
	TriStream.Append(Out);
	Out.pos = pold[2];
	TriStream.Append(Out);
	TriStream.RestartStrip();		//1�|��

	Out.pos = pold[2];
	TriStream.Append(Out);
	Out.pos = pold[5];
	TriStream.Append(Out);
	Out.pos = pold[3];
	TriStream.Append(Out);
	TriStream.RestartStrip();		//1�|��

	Out.pos = pold[5];
	TriStream.Append(Out);
	Out.pos = pold[3];
	TriStream.Append(Out);
	Out.pos = pold[0];
	TriStream.Append(Out);
	TriStream.RestartStrip();		//1�|��
}/*
03
14
25
03
*/