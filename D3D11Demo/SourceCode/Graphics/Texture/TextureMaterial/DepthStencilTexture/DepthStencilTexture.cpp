//==========================
//===�yDepthStencilTexture.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �f�v�X�X�e���V���e�N�X�`���̊Ǘ����s���܂�
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"DepthStencilTexture.h"
#include<assert.h>

OGL::DepthStencilTexture::DepthStencilTexture():
m_depthStencilTexture(nullptr),
mp_depthStencilView(nullptr),
mp_srv(nullptr)
{
}

OGL::DepthStencilTexture::~DepthStencilTexture()
{
	Release();
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�f�v�X�X�e���V���e�N�X�`���𐶐����܂��B
//������ ����1�FUINT�F�e�N�X�`���̕�
//������ �����Q�FUINT�F�e�N�X�`���̍���
//������ �����R�FDSTEX_FORMAT�F�e�N�X�`���̃t�H�[�}�b�g
//������ �����S�Fbool�F�V�F�[�_�[���\�[�X�r���[����������ꍇ��true
//������   �Ԓl�Fbool�F������true
//��������������������������������������������
bool	OGL::DepthStencilTexture::Create(UINT width, UINT height, DSTEX_FORMAT format, bool	srvFlg)
{
	m_width = width;
	m_height = height;

	switch (format)
	{
	case OGL::DSF_D16:
		m_format = DXGI_FORMAT_R16_TYPELESS;
		break;
	case OGL::DSF_D32:
		m_format = DXGI_FORMAT_R32_TYPELESS;
		break;
	case OGL::DSF_D24S8:
		m_format = DXGI_FORMAT_R24G8_TYPELESS;
		break;
	default:
		break;
	}

	HRESULT hr;
	D3D11_TEXTURE2D_DESC	textureDesc;

	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Format = m_format;
	textureDesc.Width = m_width;
	textureDesc.Height = m_height;
	textureDesc.ArraySize = 1;
	textureDesc.MipLevels = 1;
	if (srvFlg)
	{
		textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	}
	else
	{
		textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	}
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.MiscFlags = 0;
	hr = D3D11Device::GetDevice()->CreateTexture2D(&textureDesc, 0, &m_depthStencilTexture);
	if (FAILED(hr))
	{
		ErrorMessage("DepthStencilTexture::Create �f�v�X�X�e���V���e�N�X�`���쐬���s");
		return false;
	}

	// �y�o�b�t�@�r���[�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
	ZeroMemory(&DepthStencilViewDesc, sizeof(DepthStencilViewDesc));
	DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	switch (textureDesc.Format)
	{
	case DXGI_FORMAT_R16_TYPELESS:
		DepthStencilViewDesc.Format = DXGI_FORMAT_D16_UNORM;
		break;
	case DXGI_FORMAT_R32_TYPELESS:
		DepthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		break;
	case DXGI_FORMAT_R24G8_TYPELESS:
		DepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;
	}
	DepthStencilViewDesc.Texture2D.MipSlice = 0;
	DepthStencilViewDesc.Texture2DArray.FirstArraySlice = 0;
	DepthStencilViewDesc.Texture2DArray.ArraySize = 1;
	DepthStencilViewDesc.Flags = 0;
	hr = D3D11Device::GetDevice()->CreateDepthStencilView(m_depthStencilTexture, &DepthStencilViewDesc, &mp_depthStencilView);
	if (FAILED(hr))
	{
		ErrorMessage("DepthStencilTexture::Create �f�v�X�X�e���V���r���[�쐬���s");
		return false;
	}

	if (srvFlg)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		switch (DepthStencilViewDesc.Format)
		{
		case DXGI_FORMAT_D16_UNORM:
			srvd.Format = DXGI_FORMAT_R16_FLOAT;
			break;
		case DXGI_FORMAT_D32_FLOAT:
			srvd.Format = DXGI_FORMAT_R32_FLOAT;
			break;
		case DXGI_FORMAT_D24_UNORM_S8_UINT:
			srvd.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			break;
		}
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = 1;
		srvd.Texture2DArray.FirstArraySlice = 0;
		srvd.Texture2DArray.ArraySize = 1;
		// �V�F�[�_���\�[�X�r���[�𐶐�.
		hr = D3D11Device::GetDevice()->CreateShaderResourceView(m_depthStencilTexture, &srvd, &mp_srv);
		if (FAILED(hr))
		{
			ErrorMessage("DepthStencilTexture::Create �f�v�X�X�e���V���e�N�X�`���̃V�F�[�_�[���\�[�X�r���[�쐬���s");
			return false;
		}
	}
	return true;
}

//��������������������������������������������
//�������@�@�\�F�f�v�X�X�e���V���e�N�X�`�����N���A����F�œh��Ԃ��܂��B
//������ ����1�Ffloat�G�h��ׂ��[�x�l
//������ �����Q�FUINT8�F�h��ׂ��X�e���V���l(�w��Ȃ��̏ꍇ��0)
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::DepthStencilTexture::Clear(float depth, UINT8 stencil)
{
	if (m_format == DSF_D24S8)
	{
		D3D11Device::GetDeviceConText()->ClearDepthStencilView(mp_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
	}
	else
	{
		D3D11Device::GetDeviceConText()->ClearDepthStencilView(mp_depthStencilView, D3D11_CLEAR_DEPTH, depth, 0);
	}
}

//��������������������������������������������
//�������@�@�\�F�f�v�X�X�e���V���r���[���擾���܂��B
//������ ����1�Fvoid
//������   �Ԓl�FID3D11DepthStencilView*
//��������������������������������������������
ID3D11DepthStencilView*		OGL::DepthStencilTexture::GetDSV(void)
{
	return	mp_depthStencilView;
}

//��������������������������������������������
//�������@�@�\�F�f�v�X�X�e���V���e�N�X�`���̃V�F�[�_�[���\�[�X�r���[���擾���܂��B
//������ ����1�Fvoid
//������   �Ԓl�FID3D11ShaderResourceView*
//��������������������������������������������
ID3D11ShaderResourceView*	OGL::DepthStencilTexture::GetSRV(void)
{
	return	mp_srv;
}

//��������������������������������������������
//�������@�@�\�F�f�v�X�X�e���V���e�N�X�`����j�����܂��B
//������ ����1�Fvoid
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::DepthStencilTexture::Release(void)
{
	SAFE_RELEASE(m_depthStencilTexture);
	SAFE_RELEASE(mp_depthStencilView);
	SAFE_RELEASE(mp_srv);
}