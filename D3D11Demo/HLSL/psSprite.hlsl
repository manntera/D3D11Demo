//����������������������������
//�������y�萔�o�b�t�@�z������
//����������������������������

//��������������������������
//�������y�\���̐錾�z������
//��������������������������
struct pixelIn
{
	float4	pos			:	SV_POSITION;
	float2	uv				:	UV;
};
struct pixelOut
{
	float4 col		:	SV_TARGET0;
};

//��������������������������������
//�������y�e�N�X�`���̐ݒ�z������
//��������������������������������
/*�������T���v���̐ݒ聥����*/
SamplerState _sampler	:	register(s0);
/*�������񎟌��e�N�X�`���̐ݒ聥����*/
Texture2D tex		:	register(t0);

//��������������������������������
//�������y�V�F�[�_�[�R�[�h�z������
//��������������������������������
/*�������s�N�Z���V�F�[�_������*/
pixelOut PS(pixelIn In)
{
	pixelOut Out;

	Out.col = tex.Sample(_sampler, In.uv);

	return Out;
}
