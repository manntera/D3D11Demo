//==========================
//===【BlendState.cpp】
//==========================
//    DirectX11における
//    ブレンドステートの管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"BlendState.h"

OGL::BlendState::BlendState()
{
	mp_state = nullptr;
	CD3D11_BLEND_DESC desc(D3D11_DEFAULT);
	m_desc = desc;
	m_desc.IndependentBlendEnable = false;
}

OGL::BlendState::~BlendState()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：AlphaToCoverage機能のセットをします。
//■■■ 引数1：bool
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::BlendState::SetAlphaToCoverageEnable(bool enable)
{
	m_desc.AlphaToCoverageEnable = enable;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：レンダーターゲット別のブレンド処理を設定します。
//■■■ 引数1：UINT：設定するレンダーターゲット(0~7)
//■■■ 引数2：bool：BlendEnable
//■■■ 引数3：D3D11_BLEND：SrcBlend
//■■■ 引数4：D3D11_BLEND：DestBlend
//■■■ 引数5：D3D11_BLEND_OP：BlendOp
//■■■ 引数6：D3D11_BLEND：SrcBlendAlpha
//■■■ 引数7：D3D11_BLEND：DestBlendAlpha
//■■■ 引数8：D3D11_BLEND_OP：BlendOpAlpha
//■■■ 引数9：UINT8：RenderTargetWriteMask
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::BlendState::SetRenderTargetBlendDesc(UINT targetNum, bool BlendEnable, D3D11_BLEND SrcBlend,
	D3D11_BLEND DestBlend, D3D11_BLEND_OP BlendOp, D3D11_BLEND SrcBlendAlpha,
	D3D11_BLEND DestBlendAlpha, D3D11_BLEND_OP BlendOpAlpha, UINT8 RenderTargetWriteMask)
{
	if (targetNum != 0)
	{
		m_desc.IndependentBlendEnable = true;
	}
	if (targetNum > 8)
	{
		ErrorMessage("BlendState::SetRenderTargetBlendDesc 指定されたレンダーターゲットは最大数を超過しています。");
		return false;
	}
	m_desc.RenderTarget[targetNum].BlendEnable = BlendEnable;
	m_desc.RenderTarget[targetNum].SrcBlend = SrcBlend;
	m_desc.RenderTarget[targetNum].DestBlend = DestBlend;
	m_desc.RenderTarget[targetNum].BlendOp = BlendOp;
	m_desc.RenderTarget[targetNum].SrcBlendAlpha = SrcBlendAlpha;
	m_desc.RenderTarget[targetNum].DestBlendAlpha = DestBlendAlpha;
	m_desc.RenderTarget[targetNum].BlendOpAlpha = BlendOpAlpha;
	m_desc.RenderTarget[targetNum].RenderTargetWriteMask = RenderTargetWriteMask;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ブレンドステートオブジェクトを生成します。
//■■■ 引数1：void
//■■■   返値：bool：生成に成功したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::BlendState::Create(void)
{
	
	if (FAILED(D3D11Device::GetDevice()->CreateBlendState(&m_desc, mp_state.GetAddressOf())))
	{
		ErrorMessage("BlendState::Create ブレンドステートの生成に失敗しました。");
		return false;
	}
	return true;
}