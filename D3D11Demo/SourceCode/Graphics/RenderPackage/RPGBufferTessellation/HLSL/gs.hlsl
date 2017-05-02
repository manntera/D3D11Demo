//■■■■■■■■■■■■■■
//■■■【定数バッファ】■■■
//■■■■■■■■■■■■■■
/*▼▼▼各種行列▼▼▼*/
cbuffer cbTransform:register(b0)
{
	column_major float4x4	transformMat;
	column_major float4x4	worldMat;
	column_major float4x4	viewMat;
	column_major float4x4	projMat;
	float4	viewVector;
};

//■■■■■■■■■■■■■
//■■■【構造体宣言】■■■
//■■■■■■■■■■■■■
/*▼▼▼頂点IN▼▼▼*/
struct geometryIn
{
	float4	pos			:	SV_POSITION;
	float4	texUV			:	TEX_UV;
};
/*▼▼▼頂点OUT▼▼▼*/
struct geometryOut
{
	float4	pos		:	SV_POSITION;
	float4	wPos		:	WORLD_POS;
	float4	normal	:	NORMAL;
	float4	texUV		:	TEX_UV;
};
//■■■■■■■■■■■■■■■■
//■■■【シェーダーコード】■■■
//■■■■■■■■■■■■■■■■
/*▼▼▼頂点シェーダ▼▼▼*/
[maxvertexcount(3)]
void	GS(triangle geometryIn In[3], inout TriangleStream<geometryOut> TriStream)
{
	geometryOut Out;
	float4 p[3];

	p[0] = mul(In[0].pos, worldMat);
	p[1] = mul(In[1].pos, worldMat);
	p[2] = mul(In[2].pos, worldMat);
	
	float4 nor = float4(cross(p[0].xyz - p[1].xyz, p[0].xyz - p[2].xyz),0);

	for (int i = 0; i < 3; i++)
	{
		Out.texUV = In[i].texUV;
		Out.pos = mul(In[i].pos, transformMat);
		Out.wPos = p[i];
		Out.normal = nor;
		TriStream.Append(Out);
	}
	TriStream.RestartStrip();
}

/*
[maxvertexcount(6)]
void	GS(triangle GsIn In[3], inout TriangleStream<GsOut> TriStream)
{
	GsOut Out;
	int i;

	for (i = 0; i < 3; i++)
	{
		Out.pos = In[i].pos;
		Out.normal = In[i].normal;
		Out.posLV = In[i].posLV;
		Out.f = In[i].f;
		Out.texUV = In[i].texUV;
		Out.m = In[i].m;
		Out.col = float4(1, 1, 1, 1);
		//		Out.viewVec = float4(0,0,0,0);
		TriStream.Append(Out);
	}
	TriStream.RestartStrip();
	for (i = 2; i >= 0; i--)
	{
		Out.pos = In[i].pos + float4(In[i].normal.xyz * 0.05, 0);
		Out.pos.z = Out.pos.z + viewVector.z*0.05;
		Out.normal = In[i].normal;
		Out.posLV = In[i].posLV;
		Out.f = In[i].f;
		Out.texUV = In[i].texUV;
		Out.m = In[i].m;
		Out.col = float4(0.6, 0.6, 0.6, 1);
		//	Out.viewVec = float4(0, 0, 0, 0);
		TriStream.Append(Out);
	}
	TriStream.RestartStrip();
}
*/