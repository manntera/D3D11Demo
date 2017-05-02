//==========================
//===【DepthStencilState.cpp】
//==========================
//    DirectX11における
//    デプスステンシルステートの管理を行います
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"DepthStencilState.h"

OGL::DepthStencilState::DepthStencilState()
{
	mp_state = nullptr;
	CD3D11_DEPTH_STENCIL_DESC desc(D3D11_DEFAULT);
	m_desc = desc;
}

OGL::DepthStencilState::~DepthStencilState()
{
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：深度テストを行うかの設定を行います。
//■■■ 引数1：bool：true=行う false=行わない
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::DepthStencilState::SetDepthTestEnable(bool enable)
{
	m_desc.DepthEnable = enable;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：深度バッファに書き込むかの設定を行います。
//■■■ 引数1：bool：true=行う false=行わない
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::DepthStencilState::SetDepthBufferWriteEnable(bool enable)
{
	if (enable)
	{
		m_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	}
	else
	{
		m_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	}
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：深度バッファへの書き込み方法を指定します。
//■■■ 引数1：D3D11_COMPARISON_FUNC
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::DepthStencilState::SetDepthTestComparisonFunc(D3D11_COMPARISON_FUNC func)
{
	m_desc.DepthFunc = func;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ステンシルの書き込みを行うかの設定をします。
//■■■ 引数1：bool：true=行う false=行わない
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::DepthStencilState::SetStencilEnable(bool enable)
{
	m_desc.StencilEnable = enable;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ステンシル読み込み時にマスクするビットを指定します。
//■■■ 引数1：UINT8：マスクするビット
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::DepthStencilState::SetStencilReadMask(UINT8 mask)
{
	m_desc.StencilReadMask = mask;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ステンシル書き込み時にマスクするビットを指定します。
//■■■ 引数1：UINT8：マスクするビット
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::DepthStencilState::SetStencilWriteMask(UINT8 mask)
{
	m_desc.StencilWriteMask = mask;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：法線がカメラの方向を向いているピクセルについての処理を指定します。
//■■■ 引数1：D3D11_STENCIL_OP：ステンシルテストで不合格になった時に実行する処理を指定します。
//■■■ 引数２：D3D11_STENCIL_OP：ステンシルテストに合格し、深度テストで不合格になった時に実行する処理を指定します。
//■■■ 引数３：D3D11_STENCIL_OP：ステンシルテストと深度テストで合格した時に実行する処理を指定します。
//■■■ 引数４：D3D11_COMPARISON_FUNC：ステンシルバッファの比較方法を指定します。
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::DepthStencilState::SetFrontFace(D3D11_STENCIL_OP StencilFailOp, D3D11_STENCIL_OP StencilDepthFailOp, D3D11_STENCIL_OP StencilPassOp, D3D11_COMPARISON_FUNC StencilFunc)
{
	m_desc.FrontFace.StencilFailOp = StencilFailOp;
	m_desc.FrontFace.StencilDepthFailOp = StencilDepthFailOp;
	m_desc.FrontFace.StencilPassOp = StencilPassOp;
	m_desc.FrontFace.StencilFunc = StencilFunc;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：法線がカメラの方向を向いていないピクセルについての処理を指定します。
//■■■ 引数1：D3D11_STENCIL_OP：ステンシルテストで不合格になった時に実行する処理を指定します。
//■■■ 引数２：D3D11_STENCIL_OP：ステンシルテストに合格し、深度テストで不合格になった時に実行する処理を指定します。
//■■■ 引数３：D3D11_STENCIL_OP：ステンシルテストと深度テストで合格した時に実行する処理を指定します。
//■■■ 引数４：D3D11_COMPARISON_FUNC：ステンシルバッファの比較方法を指定します。
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::DepthStencilState::SetBackFace(D3D11_STENCIL_OP StencilFailOp, D3D11_STENCIL_OP StencilDepthFailOp, D3D11_STENCIL_OP StencilPassOp, D3D11_COMPARISON_FUNC StencilFunc)
{
	m_desc.BackFace.StencilFailOp = StencilFailOp;
	m_desc.BackFace.StencilDepthFailOp = StencilDepthFailOp;
	m_desc.BackFace.StencilPassOp = StencilPassOp;
	m_desc.BackFace.StencilFunc = StencilFunc;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：デプスステンシルステートを生成します。
//■■■ 引数1：void
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::DepthStencilState::Create(void)
{
	if (FAILED(D3D11Device::GetDevice()->CreateDepthStencilState(&m_desc, mp_state.GetAddressOf())))
	{
		ErrorMessage("DepthStencilState::Create デプスステンシルステートの生成に失敗しました。");
		return false;
	}
	return true;
}
