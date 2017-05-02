//==========================
//===【IndexBuffer.cpp】
//==========================
//    DirectX11における
//    インデックスバッファを管理します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"IndexBuffer.h"

OGL::IndexBuffer::IndexBuffer()
{
	mp_buffer = nullptr;
	m_count = 0;
}

OGL::IndexBuffer::~IndexBuffer()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：インデックスバッファを生成します。
//■■■ 引数1：UINT：インデックス数
//■■■ 引数2：int*：インデックス数
//■■■   返値：bool：セット出来たかどうか
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::IndexBuffer::Create(UINT indexCount, int* indexData)
{
	m_count = indexCount;
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.ByteWidth = sizeof(int)* indexCount;
	hBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA hSubResourceData;
	hSubResourceData.pSysMem = indexData;
	hSubResourceData.SysMemPitch = 0;
	hSubResourceData.SysMemSlicePitch = 0;
	HRESULT hr = D3D11Device::GetDevice()->CreateBuffer(&hBufferDesc, &hSubResourceData, &mp_buffer);
	if (FAILED(hr))
	{
		ErrorMessage("IndexBuffer::Create バッファの生成に失敗しました。");
		return false;
	}
	return true;
}