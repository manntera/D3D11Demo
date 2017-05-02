//==========================
//===【ImageTexture.cpp】
//==========================
//    DirectX11における
//    画像ファイルを読み込んだテクスチャの管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
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

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャをロードします
//■■■ 引数1：std::string：テクスチャのファイルパス
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::ImageTexture::LoadFile(std::string fiileName)
{
	Release();
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(D3D11Device::GetDevice(), fiileName.c_str(), NULL, NULL, &mp_srv, NULL);
	if (FAILED(hr)) {
		ErrorMessage("ImageTexture::LoadFile テクスチャのロードに失敗しました。");
		return false;
	}
	return true;
}
//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャ配列をロードします
//■■■ 引数1：std::string*：テクスチャのファイルパスの配列
//■■■ 引数1：UINT：配列数
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
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
	info.FirstMipLevel = D3DX11_DEFAULT;          // テクスチャーの最高解像度のミップマップ レベル。
	info.MipLevels = 1;                           // ミップマップ数。ここでは1つのみとする。
	info.Usage = D3D11_USAGE_STAGING;             // GPU から CPU へのデータ転送 (コピー) をサポート
	info.BindFlags = 0;
	info.CpuAccessFlags = D3D11_CPU_ACCESS_READ;  // リソースをマップ可能にし、CPU がそのリソースの内容を読み取れるようにする
	info.MiscFlags = 0;
	info.Format = DXGI_FORMAT_FROM_FILE;
	info.Filter = D3DX11_FILTER_POINT;            // テクスチャー読み込み時に使用するフィルター
	info.MipFilter = D3DX11_FILTER_POINT;         // ミップマップ作成時に使用するフィルター

	D3D11_TEXTURE2D_DESC desc;
	::ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));

	for (UINT i = 0; i<fileNum; i++)
	{
		ID3D11Resource* pLoadedRes = NULL;
		ID3D11Texture2D* pLoadedTexture2D = NULL;

		// 画像ファイルを読み込んでテクスチャーを作成する
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

		// 空テクスチャー作成
		if (i == 0)
		{
			// 画像ファイルを読み込んで作成したテクスチャーの情報を取得する
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

		// ファイルから画像ファイルを読み込んで作成したテクスチャーを、読み込みモードでマップする
		hr = D3D11Device::GetDeviceConText()->Map(pLoadedTexture2D, NULL, D3D11_MAP_READ, 0, &mappedResource);
		if (FAILED(hr))
		{
			SAFE_RELEASE(pTexture);
			return false;
		}

		// 空テクスチャーのサブリソースをファイルから画像ファイルを読み込んで作成したテクスチャーの内容で更新する
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
	// シェーダーリソースビューを作成する
	hr = D3D11Device::GetDevice()->CreateShaderResourceView(pTexture, &SRVDesc, &mp_srv);
	SAFE_RELEASE(pTexture);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：SRVを取得します。
//■■■ 引数1：void:
//■■■   返値：ID3D11ShaderResourceView*：テクスチャのSRV
//■■■■■■■■■■■■■■■■■■■■■■
ID3D11ShaderResourceView*	OGL::ImageTexture::GetSRV(void)
{
	return mp_srv;
}
//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャを破棄します。
//■■■ 引数1：void:
//■■■   返値：void:
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::ImageTexture::Release(void)
{
	SAFE_RELEASE(mp_srv);
}