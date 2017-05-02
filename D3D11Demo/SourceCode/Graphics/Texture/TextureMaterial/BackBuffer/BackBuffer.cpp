//==========================
//===【BackBuffer.cpp】
//==========================
//    DirectX11における
//    バックバッファを管理します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"BackBuffer.h"

OGL::BackBuffer::BackBuffer()
:mp_backBufferView(nullptr)
{

}

OGL::BackBuffer::~BackBuffer()
{
	this->Release();
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：バックバッファを生成します。
//■■■ 引数1：void
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::BackBuffer::Create(void)
{
	HRESULT	hr;
	ID3D11Texture2D *BackBuffer = nullptr;
	D3D11Device::GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
	hr=D3D11Device::GetDevice()->CreateRenderTargetView(BackBuffer, NULL, &mp_backBufferView);
	SAFE_RELEASE(BackBuffer);
	if (FAILED(hr))
	{
		ErrorMessage("BackBuffer::Create バックバッファの生成に失敗しました。");
		return false;
	}
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：バックバッファのテクスチャをクリアし一色で塗りつぶします。
//■■■ 引数1：float：赤
//■■■ 引数2：float：緑
//■■■ 引数3：float：青
//■■■ 引数4：float：アルファ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::BackBuffer::Clear(float r, float g, float b, float a)
{
	float col[4] = { r, g, b, a };
	D3D11Device::GetDeviceConText()->ClearRenderTargetView(mp_backBufferView, col);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：バックバッファを破棄します。
//■■■ 引数1：void
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::BackBuffer::Release(void)
{
	SAFE_RELEASE(mp_backBufferView);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：バックバッファビューを取得します。
//■■■ 引数1：ID3D11RenderTargetView*：バックバッファのビュー
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
ID3D11RenderTargetView*	OGL::BackBuffer::GetRTV(void)
{
	return mp_backBufferView;
}