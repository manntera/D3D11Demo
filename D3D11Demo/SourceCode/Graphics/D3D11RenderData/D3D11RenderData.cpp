//==========================
//===【D3D11RenderData.cpp】
//==========================
//    DirectX11における
//    レンダリングする際に必要なパイプラインデータを保持します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"D3D11RenderData.h"

OGL::D3D11RenderData::D3D11RenderData()
{
	mp_inputLayout = nullptr;
	mp_vertexShader = nullptr;
	mp_geometryShader = nullptr;
	mp_pixelShader = nullptr;
	
	mp_rasterizerState = nullptr;
	mp_depthStencilState = nullptr;
	mp_blendState = nullptr;
	m_blendFactor[0] = 1;
	m_blendFactor[1] = 1;
	m_blendFactor[2] = 1;
	m_blendFactor[3] = 1;
	m_sampleMask = 0xffffffff;
	m_writeStencilNum = 1;
	mp_devCon=D3D11Device::GetInstance()->GetDeviceConText();
}
OGL::D3D11RenderData::~D3D11RenderData()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：プリミティブトポロジーをセットします。
//■■■ 引数1：VertexShader* ：頂点シェーダーオブジェクト
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■ TODO: インスタンス描画用の仕組み作ろうか
void OGL::D3D11RenderData::SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology)
{
	m_primitiveTopology = topology;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：頂点シェーダーのセットを行います。
//■■■ 引数1：VertexShader* ：頂点シェーダーオブジェクト
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■ TODO: インスタンス描画用の仕組み作ろうか
void OGL::D3D11RenderData::SetVertexShader(VertexShader* vertexShader)
{
	mp_vertexShader = vertexShader->mp_vertexShader.Get();
	mp_inputLayout = vertexShader->mp_vertexLayout.Get();
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ハルシェーダーのセットを行います。
//■■■ 引数1：HullShader* ：ハルシェーダーオブジェクト
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■ TODO: インスタンス描画用の仕組み作ろうか
void OGL::D3D11RenderData::SetHullShader(HullShader* hullShader)
{
	mp_hullShader = hullShader->mp_hullShader;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ドメインシェーダーのセットを行います。
//■■■ 引数1：DomainShader* ：ドメインシェーダーオブジェクト
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■ TODO: インスタンス描画用の仕組み作ろうか
void OGL::D3D11RenderData::SetDomainShader(DomainShader* domainShader)
{
	mp_domainShader = domainShader->mp_domainShader;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ジオメトリシェーダーのセットを行います。
//■■■ 引数1：GeometryShader* ：ジオメトリシェーダーオブジェクト
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■ TODO: インスタンス描画用の仕組み作ろうか
void OGL::D3D11RenderData::SetGeometryShader(GeometryShader* geometryShader)
{
	mp_geometryShader = geometryShader->mp_geometryShader;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ピクセルシェーダーのセットを行います。
//■■■ 引数1：PixelShader* ：ピクセルシェーダーオブジェクト
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void OGL::D3D11RenderData::SetPixelShader(PixelShader* pixelShader)
{
	mp_pixelShader = pixelShader->mp_pixelShader;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：頂点シェーダーにサンプラステートのセットを行います。
//■■■ 引数1：SamplerState* ：サンプラーステートオブジェクト
//■■■ 引数2：int ：セットするスロット
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void OGL::D3D11RenderData::SetVsSamplerState(SamplerState* samplerState, int slot)
{
	for (unsigned int i = 0; i < m_vsSamplerState.size(); i++)
	{
		if (m_vsSamplerState[i].slot == slot)
		{
			m_vsSamplerState[i].state = samplerState->mp_state;
			return;
		}
	}
	T_SamplerData temp;
	m_vsSamplerState.push_back(temp);
	std::vector<T_SamplerData>::iterator end = m_vsSamplerState.end();
	end--;
	end->slot = slot;
	end->state = samplerState->mp_state;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ハルシェーダーにサンプラステートのセットを行います。
//■■■ 引数1：SamplerState* ：サンプラーステートオブジェクト
//■■■ 引数2：int ：セットするスロット
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void OGL::D3D11RenderData::SetHsSamplerState(SamplerState* samplerState, int slot)
{
	for (unsigned int i = 0; i < m_hsSamplerState.size(); i++)
	{
		if (m_hsSamplerState[i].slot == slot)
		{
			m_hsSamplerState[i].state = samplerState->mp_state;
			return;
		}
	}
	T_SamplerData temp;
	m_hsSamplerState.push_back(temp);
	std::vector<T_SamplerData>::iterator end = m_hsSamplerState.end();
	end--;
	end->slot = slot;
	end->state = samplerState->mp_state;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ドメインシェーダーにサンプラステートのセットを行います。
//■■■ 引数1：SamplerState* ：サンプラーステートオブジェクト
//■■■ 引数2：int ：セットするスロット
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void OGL::D3D11RenderData::SetDsSamplerState(SamplerState* samplerState, int slot)
{
	for (unsigned int i = 0; i < m_dsSamplerState.size(); i++)
	{
		if (m_dsSamplerState[i].slot == slot)
		{
			m_dsSamplerState[i].state = samplerState->mp_state;
			return;
		}
	}
	T_SamplerData temp;
	m_dsSamplerState.push_back(temp);
	std::vector<T_SamplerData>::iterator end = m_dsSamplerState.end();
	end--;
	end->slot = slot;
	end->state = samplerState->mp_state;
}
//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ジオメトリシェーダーにサンプラステートのセットを行います。
//■■■ 引数1：SamplerState* ：サンプラーステートオブジェクト
//■■■ 引数2：int ：セットするスロット
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void OGL::D3D11RenderData::SetGsSamplerState(SamplerState* samplerState, int slot)
{
	for (unsigned int i = 0; i < m_gsSamplerState.size(); i++)
	{
		if (m_gsSamplerState[i].slot == slot)
		{
			m_gsSamplerState[i].state = samplerState->mp_state;
			return;
		}
	}
	T_SamplerData temp;
	m_gsSamplerState.push_back(temp);
	std::vector<T_SamplerData>::iterator end = m_gsSamplerState.end();
	end--;
	end->slot = slot;
	end->state = samplerState->mp_state;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ピクセルシェーダーにサンプラステートのセットを行います。
//■■■ 引数1：SamplerState* ：サンプラーステートオブジェクト
//■■■ 引数2：int ：セットするスロット
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void OGL::D3D11RenderData::SetPsSamplerState(SamplerState* samplerState, int slot)
{
	for (unsigned int i = 0; i < m_psSamplerState.size(); i++)
	{
		if (m_psSamplerState[i].slot == slot)
		{
			m_psSamplerState[i].state = samplerState->mp_state;
			return;
		}
	}
	T_SamplerData temp;
	m_psSamplerState.push_back(temp);
	std::vector<T_SamplerData>::iterator end = m_psSamplerState.end();
	end--;
	end->slot = slot;
	end->state = samplerState->mp_state;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ラスタライザのセットを行います。
//■■■ 引数1：RasterizerState* ：ラスタライザステートオブジェクト
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void OGL::D3D11RenderData::SetRasterizerState(RasterizerState* rasterizerState)
{
	mp_rasterizerState = rasterizerState->mp_state;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：デプスステンシルステートのセットを行います。
//■■■ 引数1：DepthStencilState* ：デプスステンシルステートオブジェクト
//■■■ 引数2：UINT                     ：ステンシルに書き込む数値を記述します。
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void OGL::D3D11RenderData::SetDepthStencilState(DepthStencilState* depthStencilState, UINT writeStencilNum)
{
	mp_depthStencilState = depthStencilState->mp_state;
	m_writeStencilNum = writeStencilNum;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ブレンドステートのセットを行います。
//■■■ 引数1：VertexShader*：ブレンドステートオブジェクト
//■■■ 引数2：UINT				：サンプルガバレッジ(規定値は0xffffffff)
//■■■ 引数3：float				：SetRenderTargetBlendDescでD3D11_BLEND_BLEND_FACTORを選択した際に用いられる色を指定します。(r)
//■■■ 引数4：float				：同上(g)
//■■■ 引数5：float				：同上(b)
//■■■ 引数6：float				：同上(a)
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void OGL::D3D11RenderData::SetBlendState(BlendState* blendState, UINT sampleMask, float factor_r, float factor_g, float factor_b, float factor_a)
{
	mp_blendState = blendState->mp_state;
	m_sampleMask = sampleMask;
	m_blendFactor[0] = factor_r;
	m_blendFactor[1] = factor_g;
	m_blendFactor[2] = factor_b;
	m_blendFactor[3] = factor_a;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ビューポートのセットを行います。
//■■■ 引数1：ViewPort* ：ビューポートオブジェクト
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void OGL::D3D11RenderData::SetViewPort(ViewPort* viewPort)
{
	mp_viewPort = viewPort->mp_viewPort;
}

