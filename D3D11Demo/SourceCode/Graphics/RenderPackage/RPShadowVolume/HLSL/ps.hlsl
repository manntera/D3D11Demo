//����������������������������
//�������y�萔�o�b�t�@�z������
//����������������������������


//��������������������������
//�������y�\���̐錾�z������
//��������������������������
/*�������s�N�Z��OUT������*/
struct pixelIn
{
	float4	pos		:	SV_POSITION;
	float4	wPos		:	WORLD_POS;
	float4	normal	:	NORMAL;
	float4	texUV		:	TEX_UV;
};
struct pixelOut
{
	float4	albedo				:	SV_TARGET0;	//�A���x�h�F
	float4	normalDepth		:	SV_TARGET1;	//.xyz=�@�� .w=�[�x
	float4	worldPos				:	SV_TARGET2;	//���[���h���W
};

//��������������������������������
//�������y�e�N�X�`���̐ݒ�z������
//��������������������������������

//��������������������������������
//�������y�V�F�[�_�[�R�[�h�z������
//��������������������������������
/*�������s�N�Z���V�F�[�_������*/
pixelOut PS(pixelIn In)
{
	pixelOut Out = (pixelOut)0;

	Out.albedo = float4(1, 1, 1, 1);

	Out.normalDepth.xyz = (In.normal.xyz) / 2;
	Out.normalDepth.w = In.pos.z / In.pos.w;

	Out.worldPos = In.wPos;
	return Out;
}
