//==========================
//===【VertexBuffer.cpp】
//==========================
//    DirectX11における、
//    頂点バッファを管理します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"VertexBuffer.h"
#include<string.h>

OGL::VertexBuffer::VertexBuffer()
{
	mp_buffer = nullptr;
	mp_data = nullptr;
	m_count = 0;
	m_updateEnable = false;
}

OGL::VertexBuffer::~VertexBuffer()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：頂点バッファを生成します。
//■■■ 引数1：UINT：頂点数
//■■■ 引数2：D3DXVECTOR4*：頂点データ
//■■■ 引数3：bool：今後頂点データを更新する予定があるのであればtrue,無いのであればfalse
//■■■   返値：bool：セット出来たかどうか
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::VertexBuffer::Create(UINT vertexCount, D3DXVECTOR4* vertexData, bool	updateEnable)
{
	m_count = vertexCount;
	m_updateEnable = updateEnable;

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = sizeof(D3DXVECTOR4) * m_count;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertexData;
	if (FAILED(D3D11Device::GetDevice()->CreateBuffer(&bd, &InitData, &mp_buffer)))
	{
		ErrorMessage("VertexBuffer::Create 頂点バッファの生成に失敗しました。");
		return false;
	}

	if (updateEnable)
	{
		std::unique_ptr<D3DXVECTOR4[]> temp(new D3DXVECTOR4[m_count]);
		mp_data = std::move(temp);
		memcpy(mp_data.get() , vertexData, sizeof(D3DXVECTOR4) * m_count);
	}
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：保持している頂点データを返します。ただし、更新可能な頂点バッファに限ります。
//■■■ 引数1：UINT：返すしたい頂点の場所
//■■■   返値：D3DXVECTOR4：頂点情報
//■■■■■■■■■■■■■■■■■■■■■■
D3DXVECTOR4	OGL::VertexBuffer::GetUpdateVertexData(UINT vertexNum)
{
	if (vertexNum > m_count)
	{
		ErrorMessage("VertexBuffer::GetUpdateVertexData 指定した頂点数が超過しています。");
		return D3DXVECTOR4(0, 0, 0, 0);
	}
	if (m_updateEnable)
	{
		return mp_data[vertexNum];
	}
	else
	{
		ErrorMessage("VertexBuffer::GetUpdateVertexData この頂点バッファには更新用データが存在しません。");
		return D3DXVECTOR4(0, 0, 0, 0);
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：更新する頂点データをセットします。ただし、更新可能な頂点バッファに限ります。
//■■■ 引数1：UINT：セットする頂点の場所
//■■■ 引数2：D3DXVECTOR4：頂点情報
//■■■   返値：bool：設定出来たかどうか
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::VertexBuffer::SetUpdateVertexData(UINT vertexNum, D3DXVECTOR4 vertexData)
{
	if (vertexNum > m_count)
	{
		ErrorMessage("VertexBuffer::SetUpdateVertexData 指定した頂点数が超過しています。");
		return false;
	}
	if (m_updateEnable)
	{
		mp_data[vertexNum] = vertexData;
		return true;
	}
	else
	{
		ErrorMessage("VertexBuffer::SetUpdateVertexData この頂点バッファには更新用データが存在しません。");
		return false;
	}
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：この頂点バッファは更新可能であるかを確認します。
//■■■ 引数1：void
//■■■   返値：bool：更新可能であればtrue,更新できないのであればfalse
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::VertexBuffer::IsUpdate(void)
{
	return m_updateEnable;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：頂点バッファを更新します。
//■■■ 引数1：void
//■■■   返値：bool：更新出来たかどうか
//■■■■■■■■■■■■■■■■■■■■■■
bool OGL::VertexBuffer::UpdateBuffer(void)
{
	if (m_updateEnable)
	{
		D3D11Device::GetDeviceConText()->UpdateSubresource
			(mp_buffer.Get(), 0, NULL, mp_data.get(), 0, 0);
		return true;
	}
	else
	{
		ErrorMessage("VertexBuffer::UpdateBuffer この頂点バッファには更新用データが存在しません。");
		return false;
	}
}