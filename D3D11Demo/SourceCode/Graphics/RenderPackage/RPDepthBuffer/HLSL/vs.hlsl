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
};
/*₯₯₯Έ_OUT₯₯₯*/
struct vertexOut
{
	float4	pos			:	SV_POSITION;
};
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
//‘‘‘yVF[_[R[hz‘‘‘
//‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘‘
/*₯₯₯Έ_VF[_₯₯₯*/
vertexOut VS(vertexIn In)
{
	vertexOut Out = (vertexOut)0;
	Out.pos = mul(In.pos, transformMat);

	return Out;
}