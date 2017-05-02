//==========================
//===【D3D11Device.cpp】
//==========================
//    DirectX11における、
//    デバイス/デバイスコンテキストの
//    管理・保持を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"D3D11Device.h"

OGL::D3D11Device::D3D11Device()
{
}

OGL::D3D11Device::~D3D11Device()
{
}
//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：デバイスを生成します。
//■■■ 引数1：HWND*：ウィンドウハンドル
//■■■ 引数2：int　　 ：ウィンドウの幅
//■■■ 引数3：int      ：ウィンドウの高さ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11Device::Create(HWND*	hWnd, int width, int height)
{
	this->CreateDevice(hWnd, width, height);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：DirectX11のデバッグログを出力します。
//■■■			ただし、このメソッドはWindows8以下で実行する事は出来ません。
//■■■ 引数1：void
//■■■   返値：bool：出力に成功したかどうか
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::D3D11Device::OutputDebugLog(void)
{
#ifdef _DEBUG
	HRESULT hr;
	hr = mp_device.Get()->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(m_pD3dDebug.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrorMessage("D3D11Device::OutputDebugLog QueryInterfaceに失敗しました。");
		return false;
	}

	m_pD3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	return true;
#endif
}

//■■■■■■■■■■■■//
//■■■【private】 ■■■//
//■■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：デバイスの生成を実行します。
//■■■ 引数1：HWND*：ウィンドウハンドル
//■■■ 引数2：int　　 ：ウィンドウの幅
//■■■ 引数3：int      ：ウィンドウの高さ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11Device::CreateDevice(HWND*	hWnd, int width, int height)
{
	DXGI_SWAP_CHAIN_DESC	swapDesc;
	ZeroMemory(&swapDesc, sizeof(swapDesc));
	swapDesc.BufferCount = 1;         //バックバッファの数
	swapDesc.BufferDesc.Width = width;     //バッファの幅
	swapDesc.BufferDesc.Height = height;    //バッファの高さ
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //バッファのフォーマット
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;   //リフレッシュレート
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = *hWnd;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Windowed = TRUE;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr;
	UINT flags = 0;
#ifdef _DEBUG
		flags = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL  FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	hr = D3D11CreateDeviceAndSwapChain(
		NULL, D3D_DRIVER_TYPE_HARDWARE,
		NULL, flags,
		&FeatureLevel, 1,
		D3D11_SDK_VERSION, &swapDesc,
		&mp_swapChain, &mp_device,
		NULL, &mp_deviceContext);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("デバイスとスワップチェインの生成に失敗しました。"), TEXT("Err"), MB_OK);
	}
}







void ErrorMessage(char* str)
{
	MessageBox(NULL, TEXT(str), TEXT("Err"), MB_OK);
}