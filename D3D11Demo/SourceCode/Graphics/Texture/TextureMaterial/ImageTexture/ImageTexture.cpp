//==========================
//===�yImageTexture.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �摜�t�@�C����ǂݍ��񂾃e�N�X�`���̊Ǘ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"ImageTexture.h"

OGL::ImageTexture::ImageTexture():
mp_srv(nullptr)
{
}

OGL::ImageTexture::~ImageTexture()
{
	Release();
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�F�e�N�X�`�������[�h���܂�
//������ ����1�Fstd::string�F�e�N�X�`���̃t�@�C���p�X
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::ImageTexture::LoadFile(std::string fiileName)
{
	Release();
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(D3D11Device::GetDevice(), fiileName.c_str(), NULL, NULL, &mp_srv, NULL);
	if (FAILED(hr)) {
		ErrorMessage("ImageTexture::LoadFile �e�N�X�`���̃��[�h�Ɏ��s���܂����B");
		return false;
	}
	return true;
}
//��������������������������������������������
//�������@�@�\�F�e�N�X�`���z������[�h���܂�
//������ ����1�Fstd::string*�F�e�N�X�`���̃t�@�C���p�X�̔z��
//������ ����1�FUINT�F�z��
//������   �Ԓl�Fbool�F�ݒ肵�������ĂȂ�����Ԃ��܂�
//��������������������������������������������
bool	OGL::ImageTexture::LoadFileArray(std::string* fileName, UINT fileNum)
{
	Release();
	HRESULT hr = E_FAIL;

	ID3D11Texture2D* pTexture = nullptr;

	D3DX11_IMAGE_LOAD_INFO info;
	::ZeroMemory(&info, sizeof(D3DX11_IMAGE_LOAD_INFO));
	info.Width = D3DX11_DEFAULT;
	info.Height = D3DX11_DEFAULT;
	info.Depth = D3DX11_DEFAULT;
	info.FirstMipLevel = D3DX11_DEFAULT;          // �e�N�X�`���[�̍ō��𑜓x�̃~�b�v�}�b�v ���x���B
	info.MipLevels = 1;                           // �~�b�v�}�b�v���B�����ł�1�݂̂Ƃ���B
	info.Usage = D3D11_USAGE_STAGING;             // GPU ���� CPU �ւ̃f�[�^�]�� (�R�s�[) ���T�|�[�g
	info.BindFlags = 0;
	info.CpuAccessFlags = D3D11_CPU_ACCESS_READ;  // ���\�[�X���}�b�v�\�ɂ��ACPU �����̃��\�[�X�̓��e��ǂݎ���悤�ɂ���
	info.MiscFlags = 0;
	info.Format = DXGI_FORMAT_FROM_FILE;
	info.Filter = D3DX11_FILTER_POINT;            // �e�N�X�`���[�ǂݍ��ݎ��Ɏg�p����t�B���^�[
	info.MipFilter = D3DX11_FILTER_POINT;         // �~�b�v�}�b�v�쐬���Ɏg�p����t�B���^�[

	D3D11_TEXTURE2D_DESC desc;
	::ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));

	for (UINT i = 0; i<fileNum; i++)
	{
		ID3D11Resource* pLoadedRes = NULL;
		ID3D11Texture2D* pLoadedTexture2D = NULL;

		// �摜�t�@�C����ǂݍ���Ńe�N�X�`���[���쐬����
		hr = D3DX11CreateTextureFromFile(D3D11Device::GetDevice(), fileName[i].c_str(), &info, NULL, &pLoadedRes, NULL);
		if (FAILED(hr))
		{
			SAFE_RELEASE(pTexture);
			return false;
		}

		hr = pLoadedRes->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast <void**>(&pLoadedTexture2D));
		if (FAILED(hr))
		{
			SAFE_RELEASE(pTexture);
			return false;
		}

		// ��e�N�X�`���[�쐬
		if (i == 0)
		{
			// �摜�t�@�C����ǂݍ���ō쐬�����e�N�X�`���[�̏����擾����
			pLoadedTexture2D->GetDesc(&desc);

			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = 0;
			desc.ArraySize = fileNum;
			hr = D3D11Device::GetDevice()->CreateTexture2D(&desc, NULL, &pTexture);
			if (FAILED(hr))
			{
				SAFE_RELEASE(pTexture);
				return false;
			}
		}

		D3D11_MAPPED_SUBRESOURCE mappedResource;

		// �t�@�C������摜�t�@�C����ǂݍ���ō쐬�����e�N�X�`���[���A�ǂݍ��݃��[�h�Ń}�b�v����
		hr = D3D11Device::GetDeviceConText()->Map(pLoadedTexture2D, NULL, D3D11_MAP_READ, 0, &mappedResource);
		if (FAILED(hr))
		{
			SAFE_RELEASE(pTexture);
			return false;
		}

		// ��e�N�X�`���[�̃T�u���\�[�X���t�@�C������摜�t�@�C����ǂݍ���ō쐬�����e�N�X�`���[�̓��e�ōX�V����
		for (UINT iMip = 0; iMip < desc.MipLevels; iMip++)
		{
			D3D11Device::GetDeviceConText()->UpdateSubresource(pTexture,
				D3D11CalcSubresource(iMip, i, desc.MipLevels),
				NULL,
				mappedResource.pData,
				mappedResource.RowPitch,
				0
				);
		}
		D3D11Device::GetDeviceConText()->Unmap(pLoadedTexture2D, NULL);

		SAFE_RELEASE(pLoadedTexture2D);
		SAFE_RELEASE(pLoadedRes);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	SRVDesc.Texture2DArray.MipLevels = desc.MipLevels;
	SRVDesc.Texture2DArray.ArraySize = fileNum;
	// �V�F�[�_�[���\�[�X�r���[���쐬����
	hr = D3D11Device::GetDevice()->CreateShaderResourceView(pTexture, &SRVDesc, &mp_srv);
	SAFE_RELEASE(pTexture);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
//��������������������������������������������
//�������@�@�\�FSRV���擾���܂��B
//������ ����1�Fvoid:
//������   �Ԓl�FID3D11ShaderResourceView*�F�e�N�X�`����SRV
//��������������������������������������������
ID3D11ShaderResourceView*	OGL::ImageTexture::GetSRV(void)
{
	return mp_srv;
}
//��������������������������������������������
//�������@�@�\�F�e�N�X�`����j�����܂��B
//������ ����1�Fvoid:
//������   �Ԓl�Fvoid:
//��������������������������������������������
void	OGL::ImageTexture::Release(void)
{
	SAFE_RELEASE(mp_srv);
}