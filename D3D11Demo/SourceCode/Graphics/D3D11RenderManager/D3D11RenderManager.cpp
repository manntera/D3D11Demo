//==========================
//===【D3D11RenderManager.cpp】
//==========================
//    DirectX11における
//    描画設定の管理を行います。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"D3D11RenderManager.h"
OGL::D3D11RenderManager::D3D11RenderManager()
{
}

OGL::D3D11RenderManager::~D3D11RenderManager()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：RenderDataをセットします。
//■■■ 引数1：D3D11RenderData*：レンダリングデータ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetRenderData(D3D11RenderData* data)
{
	ID3D11DeviceContext* dev=D3D11Device::GetDeviceConText();
	dev->IASetPrimitiveTopology(data->m_primitiveTopology);
	dev->IASetInputLayout(data->mp_inputLayout.Get());
	// TODO インスタンス描画時の拡張考えようねー
	dev->VSSetShader(data->mp_vertexShader.Get(), NULL, 0);
	dev->HSSetShader(data->mp_hullShader.Get(),NULL,0);
	dev->DSSetShader(data->mp_domainShader.Get(), NULL, 0);
	dev->GSSetShader(data->mp_geometryShader.Get(), NULL, 0);
	dev->PSSetShader(data->mp_pixelShader.Get(), NULL, 0);
	dev->RSSetViewports(1, data->mp_viewPort.get());
	for (unsigned int i = 0; i < data->m_vsSamplerState.size(); i++)
	{
		ID3D11SamplerState* smp = data->m_vsSamplerState[i].state.Get();
		dev->VSSetSamplers(data->m_vsSamplerState[i].slot, 1, &smp);
	}
	for (unsigned int i = 0; i < data->m_hsSamplerState.size(); i++)
	{
		ID3D11SamplerState* smp = data->m_hsSamplerState[i].state.Get();
		dev->HSSetSamplers(data->m_hsSamplerState[i].slot, 1, &smp);
	}
	for (unsigned int i = 0; i < data->m_dsSamplerState.size(); i++)
	{
		ID3D11SamplerState* smp = data->m_dsSamplerState[i].state.Get();
		dev->DSSetSamplers(data->m_dsSamplerState[i].slot, 1, &smp);
	}
	for (unsigned int i = 0; i < data->m_gsSamplerState.size(); i++)
	{
		ID3D11SamplerState* smp = data->m_gsSamplerState[i].state.Get();
		dev->GSSetSamplers(data->m_gsSamplerState[i].slot, 1, &smp);
	}
	for (unsigned int i = 0; i < data->m_psSamplerState.size(); i++)
	{
		ID3D11SamplerState* smp = data->m_psSamplerState[i].state.Get();
		dev->PSSetSamplers(data->m_psSamplerState[i].slot, 1, &smp);
	}
	dev->RSSetState(data->mp_rasterizerState.Get());
	dev->OMSetDepthStencilState(data->mp_depthStencilState.Get(), data->m_writeStencilNum);
	dev->OMSetBlendState(data->mp_blendState.Get(), data->m_blendFactor, data->m_sampleMask);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：インデックスバッファをセットします。
//■■■ 引数1：IndexBuffer*：インデックスバッファ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetIndexBuffer(IndexBuffer* buff)
{
	D3D11Device::GetDeviceConText()
		->IASetIndexBuffer(buff->mp_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：頂点バッファをセットします。
//■■■ 引数1：VertexBuffer*：頂点バッファ
//■■■ 引数2：UINT：スロット
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetVertexBuffer(VertexBuffer* buff, UINT slot)
{
	UINT	stride = sizeof(D3DXVECTOR4);
	UINT	offset = 0;
	D3D11Device::GetDeviceConText()->IASetVertexBuffers(slot, 1, buff->mp_buffer.GetAddressOf(), &stride, &offset);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：頂点シェーダに定数バッファを設定します。
//■■■ 引数1：ConstantBuffer*：定数バッファ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetVsConstantBuffer(ConstantBuffer* buffer, UINT slot)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();

	dev->VSSetConstantBuffers(slot, 1, buffer->mp_buffer.GetAddressOf());
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ハルシェーダに定数バッファを設定します。
//■■■ 引数1：ConstantBuffer*：定数バッファ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetHsConstantBuffer(ConstantBuffer* buffer, UINT slot)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();

	dev->HSSetConstantBuffers(slot, 1, buffer->mp_buffer.GetAddressOf());
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ドメインシェーダに定数バッファを設定します。
//■■■ 引数1：ConstantBuffer*：定数バッファ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetDsConstantBuffer(ConstantBuffer* buffer, UINT slot)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();

	dev->DSSetConstantBuffers(slot, 1, buffer->mp_buffer.GetAddressOf());
}
//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ジオメトリシェーダに定数バッファを設定します。
//■■■ 引数1：ConstantBuffer*：定数バッファ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetGsConstantBuffer(ConstantBuffer* buffer, UINT slot)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();

	dev->GSSetConstantBuffers(slot, 1, buffer->mp_buffer.GetAddressOf());
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ピクセルシェーダに定数バッファを設定します。
//■■■ 引数1：ConstantBuffer*：定数バッファ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetPsConstantBuffer(ConstantBuffer* buffer, UINT slot)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();

	dev->PSSetConstantBuffers(slot, 1, buffer->mp_buffer.GetAddressOf());
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：頂点シェーダにテクスチャリソースを設定します。
//■■■ 引数1：InputTexture*：入力するテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetVsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		ID3D11ShaderResourceView* srv = inputTex->inputData[i].p_srv;
		dev->VSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ハルシェーダにテクスチャリソースを設定します。
//■■■ 引数1：InputTexture*：入力するテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetHsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		ID3D11ShaderResourceView* srv = inputTex->inputData[i].p_srv;
		dev->HSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ドメインシェーダにテクスチャリソースを設定します。
//■■■ 引数1：InputTexture*：入力するテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetDsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		ID3D11ShaderResourceView* srv = inputTex->inputData[i].p_srv;
		dev->DSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ジオメトリシェーダにテクスチャリソースを設定します。
//■■■ 引数1：InputTexture*：入力するテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetGsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		ID3D11ShaderResourceView* srv = inputTex->inputData[i].p_srv;
		dev->GSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ピクセルシェーダにテクスチャリソースを設定します。
//■■■ 引数1：InputTexture*：入力するテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetPsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		ID3D11ShaderResourceView* srv = inputTex->inputData[i].p_srv;
		dev->PSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：出力されるテクスチャを設定します。
//■■■ 引数1：OutputTexture*：出力するテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::SetOutputTexture(OutputTexture* outputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11RenderTargetView** rtv = outputTex->mp_rtv;
	dev->OMSetRenderTargets(8, rtv, outputTex->mp_dsv);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：頂点シェーダに設定していたテクスチャリソースを解除します。
//■■■ 引数1：InputTexture*：入力していたテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::ClearVsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11ShaderResourceView* srv = nullptr;
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		dev->VSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ハルシェーダに設定していたテクスチャリソースを解除します。
//■■■ 引数1：InputTexture*：入力していたテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::ClearHsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11ShaderResourceView* srv = nullptr;
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		dev->HSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ドメインシェーダに設定していたテクスチャリソースを解除します。
//■■■ 引数1：InputTexture*：入力していたテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::ClearDsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11ShaderResourceView* srv = nullptr;
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		dev->DSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ジオメトリシェーダに設定していたテクスチャリソースを解除します。
//■■■ 引数1：InputTexture*：入力していたテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::ClearGsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11ShaderResourceView* srv = nullptr;
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		dev->GSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：ピクセルシェーダに設定していたテクスチャリソースを解除します。
//■■■ 引数1：InputTexture*：入力していたテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::ClearPsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11ShaderResourceView* srv = nullptr;
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		dev->PSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：出力されるテクスチャに設定していたテクスチャリソースを解除します。
//■■■ 引数1：InputTexture*：入力していたテクスチャ
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::ClearOutputTexture(OutputTexture* outputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11RenderTargetView* rtv[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	ID3D11DepthStencilView* dsv = nullptr;
	dev->OMSetRenderTargets(8, rtv, dsv);
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：描画を実行します。
//■■■ 引数1：UINT：描画するインデックス数
//■■■ 引数1：UINT：描画を開始するインデックス値
//■■■ 引数1：UINT：各インデックスに加算する値
//■■■   返値：void
//■■■■■■■■■■■■■■■■■■■■■■
void	OGL::D3D11RenderManager::Draw(UINT drawIndexCount, UINT startIndexOffset, int addIndex)
{
	D3D11Device::GetDeviceConText()->DrawIndexed(drawIndexCount, startIndexOffset, addIndex);
}