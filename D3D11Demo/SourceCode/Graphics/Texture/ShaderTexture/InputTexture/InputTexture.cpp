//==========================
//===�yInputTexture.cpp�z
//==========================
//    Shader�ɓǂݍ��܂���Texture��ێ����܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"InputTexture.h"

OGL::InputTexture::InputTexture()
{
}

OGL::InputTexture::~InputTexture()
{
}
//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�e�N�X�`����ݒ肵�܂��B
//������ ����1�FImageTexture*�F�e�N�X�`���I�u�W�F�N�g
//������ ����2�Fint�F�ݒ肷��X���b�g
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool OGL::InputTexture::SetTexture(ImageTexture* tex, unsigned int slot)
{
	return SetSrv(tex->GetSRV(), slot);
}

//��������������������������������������������
//�������@�@�\�F�e�N�X�`����ݒ肵�܂��B
//������ ����1�FImageTexture*�F�e�N�X�`���I�u�W�F�N�g
//������ ����2�Fint�F�ݒ肷��X���b�g
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool OGL::InputTexture::SetTexture(RenderTargetTexture* tex, unsigned int slot)
{
	return SetSrv(tex->GetSRV(), slot);
}

//��������������������������������������������
//�������@�@�\�F�e�N�X�`����ݒ肵�܂��B
//������ ����1�FImageTexture*�F�e�N�X�`���I�u�W�F�N�g
//������ ����2�Fint�F�ݒ肷��X���b�g
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool OGL::InputTexture::SetTexture(DepthStencilTexture* tex, unsigned int slot)
{
	return SetSrv(tex->GetSRV(), slot);
}

//������������������������//
//�������yprivate�z ������//
//������������������������//

//��������������������������������������������
//�������@�@�\�FinputData��ShaderResource���Z�b�g���܂��B
//������ ����1�FID3D11ShaderResourceView*�F�e�N�X�`���I�u�W�F�N�g
//������ ����2�Fint�F�ݒ肷��X���b�g
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool OGL::InputTexture::SetSrv(ID3D11ShaderResourceView* srv, int slot)
{
	if (slot<0||slot >= D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)
	{
		ErrorMessage("InputTexture::SetSrv �ݒ肳�ꂽ�X���b�g�͔͈͊O�ł��B");
		return false;
	}
	if (srv == nullptr)
	{
		ErrorMessage("InputTexture::SetSrv �V�F�[�_�[���\�[�X�r���[���w�肳��Ă��܂���B");
		return false;
	}

	for (unsigned int i = 0; i < inputData.size(); i++)
	{
		if (inputData[i].slot == slot)
		{
			inputData[i].p_srv = srv;
			return true;
		}
	}
	T_srvData temp;
	temp.p_srv = srv;
	temp.slot = slot;
	inputData.push_back(temp);
	return true;
}