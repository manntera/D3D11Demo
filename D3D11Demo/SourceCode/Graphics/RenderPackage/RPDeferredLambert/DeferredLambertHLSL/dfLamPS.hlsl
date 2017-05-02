//����������������������������
//�������y�萔�o�b�t�@�z������
//����������������������������
struct T_pointLight
{
	float4	pos;
	float4	diffuseCollar;
	float4	decrement;	//x=�����J�n���� y=�����I������
};

struct T_spotLight
{
	float4	pos;
	float4	rot;
	float4	diffuseCollar;
	float4	decrement;	// x = �����J�n���� y = �����I������  z = �X�|�b�g���C�g�͈̔�
};
cbuffer cbTransform:register(b1)
{
	column_major float4x4	transformMat;
	column_major float4x4	worldMat;
	column_major float4x4	viewMat;
	column_major float4x4	projMat;
	float4	viewVector;
};
cbuffer cbPointLight:register(b2)
{
	float4	pointLightCount;
	T_pointLight pointLight[50];
};
cbuffer cbSpotLight:register(b3)
{
	float4	spotLightCount;
	T_spotLight spotLight[50];
};

//��������������������������
//�������y�\���̐錾�z������
//��������������������������
/*���������_IN������*/
struct PixelIn
{
	float4 pos    : SV_POSITION;
	float4 uv		 : TEX_UV;
	float4 sPos		:sPos;
};
/*���������_OUT������*/
struct PixelOut
{
	float4	col		:		SV_TARGET0;
};

//��������������������������������
//�������y�e�N�X�`���̐ݒ�z������
//��������������������������������
/*�������T���v���̐ݒ聥����*/
SamplerState mySampler	:	register(s0);

/*�������񎟌��e�N�X�`���̐ݒ聥����*/
Texture2D albedo			:	register(t0);
Texture2D normalDepth	:	register(t1);
Texture2D worldPos		:	register(t2);
//��������������������������������
//�������y�V�F�[�_�[�R�[�h�z������
//��������������������������������
/*���������_�V�F�[�_������*/
PixelOut PS(PixelIn In)
{
	PixelOut Out = (PixelOut)0;

	float4 wPos;
	float3 normal;

	wPos = worldPos.Sample(mySampler, In.uv.xy);

	normal = normalDepth.Sample(mySampler, In.uv.xy).xyz;
	normal = (normal * 2) - 1;

	float4 totalCol = (float4)0;
	Out.col = float4(albedo.Sample(mySampler, In.uv.xy).xyz, 1);
	
	for (int i = 0; i <pointLightCount.x; i++)
	{
		float lightForce = length(pointLight[i].pos.xyz - wPos);
		float min_ = min(pointLight[i].decrement.x, lightForce);
		float max_ = max(pointLight[i].decrement.y, lightForce);
		lightForce = lightForce / (min_ - max_) - max_ / (min_ - max_);
		lightForce = saturate(lightForce);

		float3 lVec = normalize(pointLight[i].pos.xyz - wPos);
		float d = dot(lVec, normal);
		d = d*0.5 + 0.5;
		d = d*d;
		totalCol += float4(pointLight[i].diffuseCollar.xyz*lightForce*d, 1);
	}


	for (int i = 0; i <spotLightCount.x; i++)
	{
		float dot_ = dot(normalize(spotLight[i].pos.xyz - wPos), normalize(spotLight[i].rot.xyz));
		float d = 0;
		float lightForce = 0;
		if (dot_ > spotLight[i].decrement.z)
		{
			lightForce = length(spotLight[i].pos.xyz - wPos);
			float min_ = min(spotLight[i].decrement.x, lightForce);
			float max_ = max(spotLight[i].decrement.y, lightForce);
			lightForce = lightForce / (min_ - max_) - max_ / (min_ - max_);
			lightForce = saturate(lightForce);

			float3 lVec = normalize(spotLight[i].pos.xyz - wPos);
			d = dot(lVec, normal);
			d = d*0.5 + 0.5;
			d = d*d;
		}
		totalCol += float4(spotLight[i].diffuseCollar.xyz*lightForce*d, 1);
	}
	Out.col = Out.col*totalCol;
	return Out;
}
