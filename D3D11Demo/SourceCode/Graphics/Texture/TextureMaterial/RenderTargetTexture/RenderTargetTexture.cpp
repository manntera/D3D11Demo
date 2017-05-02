//==========================
//===【RenderTargetTexture.cpp】
//==========================
//    DirectX11における
//    レンダーターゲットテクスチャの管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
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

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：レンダーターゲットテクスチャを生成します。
//■■■ 引数1：UINT：テクスチャの幅
//■■■ 引数２：UINT：テクスチャの高さ
//■■■ 引数３：DXGI_FORMAT：テクスチャのフォーマット
//■■■ 引数４：DXGI_FORMAT：シェーダーリソースビューのフォーマット
//■■■ 引数５：DXGI_FORMAT：レンダーターゲットビューのフォーマット
//■■■   返値：bool：成功時true
//■■■■■■■■■■■■■■■■■■■■■■
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
		ErrorMessage("RenderTargetTexture::Create レンダーターゲットテクスチャ作成失敗");
		return false;
	}


	D3D11_RENDER_TARGET_VIEW_DESC	rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = rtvFormat;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	hr = D3D11Device::GetDevice()->CreateRenderTargetView(mp_tex, &rtvDesc, &mp_rtv);
	if (FAILED(hr))
	{
		ErrorMessage("RenderTargetTexture::Create レンダーターゲットビュー作成失敗");
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
		ErrorMessage("RenderTargetTexture::Create レンダーターゲットシェーダーリソース作成失敗");
		return false;
	}
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：レンダーターゲットテクスチャをクリアし一色で塗りつぶします。
//■■■ 引数1：float：赤
//■■■ 引数2：float：緑
//■■■ 引数3：float：青
//■■■ 引数4：float：アルファ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::RenderTargetTexture::Clear(float r, float g, float b, float a)
{
	float col[4] = { r, g, b, a };
	D3D11Device::GetDeviceConText()->ClearRenderTargetView(mp_rtv, col);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャを取得します。
//■■■ 引数1：void
//■■■   返値：ID3D11Texture2D*
//■■■■■■■■■■■■■■■■■■■■■■
ID3D11Texture2D*				OGL::RenderTargetTexture::GetTEX(void)
{
	return	mp_tex;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：シェーダーリソースビューを取得します。
//■■■ 引数1：void
//■■■   返値：ID3D11ShaderResourceView*
//■■■■■■■■■■■■■■■■■■■■■■
ID3D11ShaderResourceView*	OGL::RenderTargetTexture::GetSRV(void)
{
	return	mp_srv;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：レンダーターゲットビューを取得します。
//■■■ 引数1：void
//■■■   返値：ID3D11RenderTargetView*
//■■■■■■■■■■■■■■■■■■■■■■
ID3D11RenderTargetView*		OGL::RenderTargetTexture::GetRTV(void)
{
	return	mp_rtv;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：レンダーターゲットテクスチャを破棄します。
//■■■ 引数1：void
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::RenderTargetTexture::Release(void)
{
	SAFE_RELEASE(mp_tex);
	SAFE_RELEASE(mp_srv);
	SAFE_RELEASE(mp_rtv);
}