//==========================
//===�yOutputTexture.cpp�z
//==========================
//    Shader����`�悳���Texture��ێ����܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"OutputTexture.h"

OGL::OutputTexture::OutputTexture()
{
	for (int i = 0; i < MAX_SET_RTV; i++)
	{
		mp_rtv[i] = nullptr;
	}
	mp_dsv = nullptr;
}

OGL::OutputTexture::~OutputTexture()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�e�N�X�`����ݒ肵�܂��B
//������ ����1�FBackBuffer*�F�e�N�X�`���I�u�W�F�N�g
//������ ����2�Fint�F�ݒ肷��X���b�g
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool OGL::OutputTexture::SetTexture(BackBuffer* tex, unsigned int slot)
{
	if (tex->GetRTV() == nullptr)
	{
		ErrorMessage("OutputTexture::SetTexture �o�b�N�o�b�t�@��RTV������܂���");
		return false;
	}
	if (slot > MAX_SET_RTV)
	{
		ErrorMessage("OutputTexture::SetTexture �w�肳�ꂽ�X���b�g�͔͈͊O�ł��B");
		return false;
	}
	for (int i = 0; i < MAX_SET_RTV; i++)
	{
		if (mp_rtv[i] == tex->GetRTV())
		{
			ErrorMessage("OutputTexture::SetTexture �w�肳�ꂽ�e�N�X�`���͑��̃X���b�g�Ɏw�肳��Ă��܂��B");
			return false;
		}
	}
	mp_rtv[slot] = tex->GetRTV();
	return true;
}

//��������������������������������������������
//�������@�@�\�F�e�N�X�`����ݒ肵�܂��B
//������ ����1�FRenderTargetTexture*�F�e�N�X�`���I�u�W�F�N�g
//������ ����2�Fint�F�ݒ肷��X���b�g
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool OGL::OutputTexture::SetTexture(RenderTargetTexture* tex, unsigned int slot)
{
	if (tex->GetRTV() == nullptr)
	{
		ErrorMessage("OutputTexture::SetTexture �o�b�N�o�b�t�@��RTV������܂���");
		return false;
	}
	if (slot > MAX_SET_RTV)
	{
		ErrorMessage("OutputTexture::SetTexture �w�肳�ꂽ�X���b�g�͔͈͊O�ł��B");
		return false;
	}
	for (int i = 0; i < MAX_SET_RTV; i++)
	{
		if (mp_rtv[i] == tex->GetRTV())
		{
			ErrorMessage("OutputTexture::SetTexture �w�肳�ꂽ�e�N�X�`���͑��̃X���b�g�Ɏw�肳��Ă��܂��B");
			return false;
		}
	}
	mp_rtv[slot] = tex->GetRTV();
	return true;
}

//��������������������������������������������
//�������@�@�\�F�e�N�X�`����ݒ肵�܂��B
//������ ����1�FDepthStencilTexture*�F�e�N�X�`���I�u�W�F�N�g
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool OGL::OutputTexture::SetTexture(DepthStencilTexture* tex)
{
	if (tex->GetDSV() == nullptr)
	{
		ErrorMessage("OutputTexture::SetTexture �o�b�N�o�b�t�@��DSV������܂���");
		return false;
	}
	mp_dsv = tex->GetDSV();
	return true;
}

//��������������������������������������������
//�������@�@�\�F�ݒ肳��Ă��郌���_�[�^�[�Q�b�g�̏����N���A���܂��B
//������ ����1�Ffloat�Fr
//������ ����2�Ffloat�Fg
//������ ����3�Ffloat�Fb
//������ ����4�Ffloat�Fa
//������ ����5�Fint�F�X���b�g
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool OGL::OutputTexture::ClearRtv(float r, float g, float b, float a, int slot)
{
	if (slot > MAX_SET_RTV)
	{
		ErrorMessage("OutputTexture::SetTexture �w�肳�ꂽ�X���b�g�͔͈͊O�ł��B");
		return false;
	}
	float col[4] = { r, g, b, a };
	if (slot == -1)
	{
		for (int i = 0; i < MAX_SET_RTV; i++)
		{
			D3D11Device::GetDeviceConText()->ClearRenderTargetView(mp_rtv[i], col);
		}
	}
	else
	{
		D3D11Device::GetDeviceConText()->ClearRenderTargetView(mp_rtv[slot], col);
	}
	return true;
}

//��������������������������������������������
//�������@�@�\�F�ݒ肳��Ă���f�v�X�X�e���V���o�b�t�@���N���A���܂��B
//������ ����1�Fbool�F�f�v�X�e�N�X�`�����N���A���邩�ǂ���
//������ ����2�Fbool�F�X�e���V���e�N�X�`�����N���A���邩�ǂ���
//������ ����3�Ffloat�F�f�v�X�e�N�X�`�����N���A����ۂɎg�����l
//������ ����4�FUINT8�F�X�e���V���e�N�X�`�����N���A����ۂɎg�����l
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool OGL::OutputTexture::ClearDsv(bool depthEnable, bool stencilEnable, float clearDepth, UINT8 clearStencil)
{
	if (depthEnable == true)
	{
		D3D11Device::GetDeviceConText()->ClearDepthStencilView
			(mp_dsv, D3D11_CLEAR_DEPTH, clearDepth, clearStencil);
	}
	if (stencilEnable == true)
	{
		D3D11Device::GetDeviceConText()->ClearDepthStencilView
			(mp_dsv, D3D11_CLEAR_STENCIL, clearDepth, clearStencil);
	}
	return true;
}