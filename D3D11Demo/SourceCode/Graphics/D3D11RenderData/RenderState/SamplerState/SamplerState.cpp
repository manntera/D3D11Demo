//==========================
//===【SamplerState.cpp】
//==========================
//    DirectX11における
//    サンプラーステートの管理を行いまｓ。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"SamplerState.h"

OGL::SamplerState::SamplerState()
{
	mp_state = nullptr;
	CD3D11_SAMPLER_DESC desc(D3D11_DEFAULT);
	m_desc = desc;
}

OGL::SamplerState::~SamplerState()
{
}
//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：テクスチャのフィルタリングモードを指定します。
//■■■ 引数1：D3D11_FILTER：フィルタリングメソッドの設定
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::SamplerState::SetFilter(D3D11_FILTER filter)
{
	m_desc.Filter = filter;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：指定したUVが0~1以外に指定されている場合の設定をします。
//■■■ 引数1：D3D11_TEXTURE_ADDRESS_MODE：U値に関する設定をします。
//■■■ 引数1：D3D11_TEXTURE_ADDRESS_MODE：V値に関する設定をします。
//■■■ 引数1：D3D11_TEXTURE_ADDRESS_MODE：W値に関する設定をします。
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::SamplerState::SetAddresMode(D3D11_TEXTURE_ADDRESS_MODE u, D3D11_TEXTURE_ADDRESS_MODE v, D3D11_TEXTURE_ADDRESS_MODE w)
{
	m_desc.AddressU = u;
	m_desc.AddressV = v;
	m_desc.AddressW = w;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ミップマップレベルのオフセット値を設定します。
//■■■ 引数1：float：オフセット値
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::SamplerState::SetMipLODBias(float bias)
{
	m_desc.MipLODBias = bias;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：SetFilterでD3D11_FILTER_ANISOTROPICまたは、
//■■■　　　　D3D11_FILTER_COMPARISON_ANISOTROPIC が設定されている際
//■■■　　　　異方性補間のクランプ値を設定します。
//■■■ 引数1：unsigned int：１～１６のクランプ値
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::SamplerState::SetMaxAnisotropy(unsigned int anisotropy)
{
	if (anisotropy > 16 || anisotropy<=0)
	{
		ErrorMessage("SamplerState::SetMaxAnisotropy 指定されたクランプ値は最大幅を超えて指定されています。");
		return false;
	}
	m_desc.MaxAnisotropy = anisotropy;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：既存サンプリングデータに対するデータを比較する関数を設定します。
//■■■ 引数1：D3D11_COMPARISON_FUNC：フィルタリングメソッドの設定
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::SamplerState::SetComparisonFunc(D3D11_COMPARISON_FUNC func)
{
	m_desc.ComparisonFunc = func;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：SetFilterでD3D11_TEXTURE_ADDRESS_BORDER が設定されている際
//■■■　　　　境界の色を設定します。
//■■■ 引数1：float：r：赤色の設定をします。
//■■■ 引数2：float：g：緑色の設定をします。
//■■■ 引数3：float：b：青色の設定をします。
//■■■ 引数4：float：a：αの設定をします。
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::SamplerState::SetBorderColor(float r, float g, float b, float a)
{
	if (r > 1 || r < 0 || g>1 || g < 0 || b>1 || b < 0 || a>1 || a < 0)
	{
		ErrorMessage("SamplerState::SetBorderColor 指定された色の中に0～1の範囲外を指定している物があります。");
		return false;
	}

	m_desc.BorderColor[0] = r;
	m_desc.BorderColor[1] = g;
	m_desc.BorderColor[2] = b;
	m_desc.BorderColor[3] = a;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：アクセスをクランプするミップマップ範囲の下限・上限値を設定します。
//■■■ 引数1：float：下限値
//■■■ 引数2：float：上限値
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::SamplerState::SetLOD(float min, float max)
{
	if (min > max)
	{
		ErrorMessage("SamplerState::SetLOD min値がmax値を超えて指定されています。");
		return false;
	}
	m_desc.MinLOD = min;
	m_desc.MaxLOD = max;
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：サンプラステートオブジェクトを生成します。
//■■■ 引数1：void
//■■■   返値：bool：生成に成功したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::SamplerState::Create(void)
{
	if (FAILED(D3D11Device::GetDevice()->CreateSamplerState(&m_desc, mp_state.GetAddressOf())))
	{
		ErrorMessage("SamplerState::Create サンプラオブジェクトを生成できませんでした");
		return false;
	}
	return true;
}