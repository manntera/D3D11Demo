//==========================
//===【OutputTexture.cpp】
//==========================
//    Shaderから描画されるTextureを保持します。
//==========================

//=====================//
//===【インクルード記述】 ===//
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

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャを設定します。
//■■■ 引数1：BackBuffer*：テクスチャオブジェクト
//■■■ 引数2：int：設定するスロット
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool OGL::OutputTexture::SetTexture(BackBuffer* tex, unsigned int slot)
{
	if (tex->GetRTV() == nullptr)
	{
		ErrorMessage("OutputTexture::SetTexture バックバッファにRTVがありません");
		return false;
	}
	if (slot > MAX_SET_RTV)
	{
		ErrorMessage("OutputTexture::SetTexture 指定されたスロットは範囲外です。");
		return false;
	}
	for (int i = 0; i < MAX_SET_RTV; i++)
	{
		if (mp_rtv[i] == tex->GetRTV())
		{
			ErrorMessage("OutputTexture::SetTexture 指定されたテクスチャは他のスロットに指定されています。");
			return false;
		}
	}
	mp_rtv[slot] = tex->GetRTV();
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャを設定します。
//■■■ 引数1：RenderTargetTexture*：テクスチャオブジェクト
//■■■ 引数2：int：設定するスロット
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool OGL::OutputTexture::SetTexture(RenderTargetTexture* tex, unsigned int slot)
{
	if (tex->GetRTV() == nullptr)
	{
		ErrorMessage("OutputTexture::SetTexture バックバッファにRTVがありません");
		return false;
	}
	if (slot > MAX_SET_RTV)
	{
		ErrorMessage("OutputTexture::SetTexture 指定されたスロットは範囲外です。");
		return false;
	}
	for (int i = 0; i < MAX_SET_RTV; i++)
	{
		if (mp_rtv[i] == tex->GetRTV())
		{
			ErrorMessage("OutputTexture::SetTexture 指定されたテクスチャは他のスロットに指定されています。");
			return false;
		}
	}
	mp_rtv[slot] = tex->GetRTV();
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャを設定します。
//■■■ 引数1：DepthStencilTexture*：テクスチャオブジェクト
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool OGL::OutputTexture::SetTexture(DepthStencilTexture* tex)
{
	if (tex->GetDSV() == nullptr)
	{
		ErrorMessage("OutputTexture::SetTexture バックバッファにDSVがありません");
		return false;
	}
	mp_dsv = tex->GetDSV();
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：設定されているレンダーターゲットの情報をクリアします。
//■■■ 引数1：float：r
//■■■ 引数2：float：g
//■■■ 引数3：float：b
//■■■ 引数4：float：a
//■■■ 引数5：int：スロット
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool OGL::OutputTexture::ClearRtv(float r, float g, float b, float a, int slot)
{
	if (slot > MAX_SET_RTV)
	{
		ErrorMessage("OutputTexture::SetTexture 指定されたスロットは範囲外です。");
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

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：設定されているデプスステンシルバッファをクリアします。
//■■■ 引数1：bool：デプステクスチャをクリアするかどうか
//■■■ 引数2：bool：ステンシルテクスチャをクリアするかどうか
//■■■ 引数3：float：デプステクスチャをクリアする際に使う数値
//■■■ 引数4：UINT8：ステンシルテクスチャをクリアする際に使う数値
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
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