//==========================
//===【RasterizerState.cpp】
//==========================
//    DirectX11における
//    ラスタライザステートの管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"RasterizerState.h"

OGL::RasterizerState::RasterizerState()
{
	mp_state = nullptr;
	CD3D11_RASTERIZER_DESC desc(D3D11_DEFAULT);
	m_desc = desc;
}

OGL::RasterizerState::~RasterizerState()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ワイヤーフレームを使うかを設定します。
//■■■ 引数1：bool：tureの場合はワイヤーフレームを適用します。
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::RasterizerState::SetWireFrameEnable(bool enable)
{
	if (enable)
	{
		m_desc.FillMode = D3D11_FILL_WIREFRAME;
	}
	else
	{
		m_desc.FillMode = D3D11_FILL_SOLID;
	}
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ポリゴンのカリングを設定します。
//■■■ 引数1：D3D11_CULL_MODE：カリング設定
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::RasterizerState::SetCullMode(D3D11_CULL_MODE mode)
{
	m_desc.CullMode = mode;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ポリゴンの回転方向による裏表を設定します。
//■■■ 引数1：ROTATORY_FRONT_MODE：設定項目
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::RasterizerState::SetRotatoryFrontMode(ROTATORY_FRONT_MODE mode)
{
	m_desc.FrontCounterClockwise = mode;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：深度バイアスに関する設定を行います。
//■■■ 引数1：int：ピクセルに加算する深度値を設定します。
//■■■ 引数2：float：ピクセルの最大深度バイアスを設定します。
//■■■ 引数3：float：指定ピクセルのスロープに対するスカラ値を設定します。
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::RasterizerState::SetDepthBias(int depthBias, float depthBiasClamp, float slopeScaledDepthBias)
{
	m_desc.DepthBias = depthBias;
	m_desc.DepthBiasClamp = depthBiasClamp;
	m_desc.SlopeScaledDepthBias = slopeScaledDepthBias;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：距離クリッピングを設定します。
//■■■ 引数1：bool：有効にするかしないか
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::RasterizerState::SetDepthClippingEnable(bool enable)
{
	m_desc.DepthClipEnable = enable;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：マルチサンプリングのエアンチエイリアシングを設定します。
//■■■ 引数1：bool：有効にするかしないか
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::RasterizerState::SetMultisampleEnable(bool enable)
{
	m_desc.MultisampleEnable = enable;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：マルチサンプリングのエアンチエイリアシングを設定します。
//■■■　         SetMultisampleEnableでfalseを指定している必要があります。
//■■■ 引数1：bool：有効にするかしないか
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::RasterizerState::SetAntialiasedLineEnable(bool enable)
{
	m_desc.AntialiasedLineEnable = enable;
	return true;
}
//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ラスタライザステートオブジェクトを生成します。
//■■■ 引数1：void
//■■■   返値：bool：生成に成功したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::RasterizerState::Create(void)
{
	if (FAILED(D3D11Device::GetDevice()->CreateRasterizerState(&m_desc, mp_state.GetAddressOf())))
	{
		ErrorMessage("RasterizerState::Create ラスタライザステート生成に失敗しました。");
		return false;
	}
	return true;

}