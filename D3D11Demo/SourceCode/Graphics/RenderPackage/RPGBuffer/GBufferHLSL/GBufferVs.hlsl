//‘‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘yθobt@z‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯eνsρ₯₯₯*/
cbuffer cbTransform:register(b0)
{
	column_major float4x4	transformMat;
	column_major float4x4	worldMat;
	column_major float4x4	viewMat;
	column_major float4x4	projMat;
	float4	viewVector;
};

//‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘y\’ΜιΎz‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯Έ_IN₯₯₯*/
struct vertexIn
{
	float4	pos			:	POSITION;
	float4	normal		:	NORMAL;
	float4	texUV			:	TEX_UV;
};
/*₯₯₯Έ_OUT₯₯₯*/
struct vertexOut
{
	float4	pos		:	SV_POSITION;
	float4	wPos		:	WORLD_POS;
	float4	normal	:	NORMAL;
	float4	texUV		:	TEX_UV;
};
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘yVF[_[R[hz‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯Έ_VF[_₯₯₯*/
vertexOut VS(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.wPos = mul(In.pos, worldMat);
	Out.pos = mul(In.pos, transformMat);
	Out.texUV = In.texUV;

	float3 nor = normalize(In.normal.xyz);
	Out.normal.xyz = mul(nor, (float3x3)worldMat);

	return Out;
}