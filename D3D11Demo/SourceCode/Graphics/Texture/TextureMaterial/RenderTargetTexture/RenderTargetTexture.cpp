//==========================
//===�yRenderTargetTexture.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �����_�[�^�[�Q�b�g�e�N�X�`���̊Ǘ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"RenderTargetTexture.h"

OGL::RenderTargetTexture::RenderTargetTexture():
mp_tex(nullptr),
mp_srv(nullptr),
mp_rtv(nullptr)
{
}

OGL::RenderTargetTexture::~RenderTargetTexture()
{
	Release();
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�����_�[�^�[�Q�b�g�e�N�X�`���𐶐����܂��B
//������ ����1�FUINT�F�e�N�X�`���̕�
//������ �����Q�FUINT�F�e�N�X�`���̍���
//������ �����R�FDXGI_FORMAT�F�e�N�X�`���̃t�H�[�}�b�g
//������ �����S�FDXGI_FORMAT�F�V�F�[�_�[���\�[�X�r���[�̃t�H�[�}�b�g
//������ �����T�FDXGI_FORMAT�F�����_�[�^�[�Q�b�g�r���[�̃t�H�[�}�b�g
//������   �Ԓl�Fbool�F������true
//��������������������������������������������
bool	OGL::RenderTargetTexture::Create(UINT width, UINT height, 
	DXGI_FORMAT texFormat, DXGI_FORMAT srvFormat, DXGI_FORMAT rtvFormat)
{
	HRESULT	hr;

	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(texDesc));
	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = texFormat;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	hr = D3D11Device::GetDevice()->CreateTexture2D(&texDesc, nullptr, &mp_tex);
	if (FAILED(hr))
	{
		ErrorMessage("RenderTargetTexture::Create �����_�[�^�[�Q�b�g�e�N�X�`���쐬���s");
		return false;
	}


	D3D11_RENDER_TARGET_VIEW_DESC	rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = rtvFormat;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	hr = D3D11Device::GetDevice()->CreateRenderTargetView(mp_tex, &rtvDesc, &mp_rtv);
	if (FAILED(hr))
	{
		ErrorMessage("RenderTargetTexture::Create �����_�[�^�[�Q�b�g�r���[�쐬���s");
		return false;
	}

	//D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	//memset(&srvDesc, 0, sizeof(srvDesc));
	//srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//srvDesc.Format = srvFormat;
	//srvDesc.Texture2D.MipLevels = 1;
	hr = D3D11Device::GetDevice()->CreateShaderResourceView(mp_tex, NULL, &mp_srv);
	if (FAILED(hr))
	{
		ErrorMessage("RenderTargetTexture::Create �����_�[�^�[�Q�b�g�V�F�[�_�[���\�[�X�쐬���s");
		return false;
	}
	return true;
}

//��������������������������������������������
//�������@�@�\�F�����_�[�^�[�Q�b�g�e�N�X�`�����N���A����F�œh��Ԃ��܂��B
//������ ����1�Ffloat�F��
//������ ����2�Ffloat�F��
//������ ����3�Ffloat�F��
//������ ����4�Ffloat�F�A���t�@
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::RenderTargetTexture::Clear(float r, float g, float b, float a)
{
	float col[4] = { r, g, b, a };
	D3D11Device::GetDeviceConText()->ClearRenderTargetView(mp_rtv, col);
}

//��������������������������������������������
//�������@�@�\�F�e�N�X�`�����擾���܂��B
//������ ����1�Fvoid
//������   �Ԓl�FID3D11Texture2D*
//��������������������������������������������
ID3D11Texture2D*				OGL::RenderTargetTexture::GetTEX(void)
{
	return	mp_tex;
}

//��������������������������������������������
//�������@�@�\�F�V�F�[�_�[���\�[�X�r���[���擾���܂��B
//������ ����1�Fvoid
//������   �Ԓl�FID3D11ShaderResourceView*
//��������������������������������������������
ID3D11ShaderResourceView*	OGL::RenderTargetTexture::GetSRV(void)
{
	return	mp_srv;
}

//��������������������������������������������
//�������@�@�\�F�����_�[�^�[�Q�b�g�r���[���擾���܂��B
//������ ����1�Fvoid
//������   �Ԓl�FID3D11RenderTargetView*
//��������������������������������������������
ID3D11RenderTargetView*		OGL::RenderTargetTexture::GetRTV(void)
{
	return	mp_rtv;
}

//��������������������������������������������
//�������@�@�\�F�����_�[�^�[�Q�b�g�e�N�X�`����j�����܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::RenderTargetTexture::Release(void)
{
	SAFE_RELEASE(mp_tex);
	SAFE_RELEASE(mp_srv);
	SAFE_RELEASE(mp_rtv);
}