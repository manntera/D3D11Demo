//����������������������������
//�������y�萔�o�b�t�@�z������
//����������������������������

//��������������������������
//�������y�\���̐錾�z������
//��������������������������
/*���������_IN������*/
struct GsIn
{
	float4	rect			:	RECT;
};
/*���������_OUT������*/
struct GsOut
{
	float4	pos			:	SV_POSITION;
	float2	uv				:	UV;
};

[maxvertexcount(4)]
void	GS(point GsIn In[1], inout TriangleStream<GsOut> TriStream)
{
	GsOut Out;

	Out.pos.z = 0;
	Out.pos.w = 1;

	Out.pos.x = In[0].rect.x - In[0].rect.z;
	Out.pos.y = In[0].rect.y - In[0].rect.w;
	Out.uv.x = 0;
	Out.uv.y = 1;
	TriStream.Append(Out);
	Out.pos.x = In[0].rect.x - In[0].rect.z;
	Out.pos.y = In[0].rect.y + In[0].rect.w;
	Out.uv.x = 0;
	Out.uv.y = 0;
	TriStream.Append(Out);
	Out.pos.x = In[0].rect.x + In[0].rect.z;
	Out.pos.y = In[0].rect.y - In[0].rect.w;
	Out.uv.x = 1;
	Out.uv.y = 1;
	TriStream.Append(Out);
	Out.pos.x = In[0].rect.x + In[0].rect.z;
	Out.pos.y = In[0].rect.y + In[0].rect.w;
	Out.uv.x = 1;
	Out.uv.y = 0;
	TriStream.Append(Out);

	TriStream.RestartStrip();
}