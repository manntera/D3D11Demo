//==========================
//===【ConstantBuffer.cpp】
//==========================
//    DirectX11における
//    コンスタントバッファ(定数バッファ)を管理します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"ConstantBuffer.h"

OGL::ConstantBuffer::ConstantBuffer()
{
}

OGL::ConstantBuffer::~ConstantBuffer()
{
}

//■■■■■■■■■■■//
//■■■【public】■■■//
//■■■■■■■■■■■//

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：定数バッファを生成します。
//■■■ 引数1：UINT：セットするスロットを指定します。
//■■■ 引数2：UINT：セットする定数バッファのサイズを指定します。(16の倍数である事)
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::ConstantBuffer::Create(UINT byteSize)
{
	if ((byteSize % 16) != 0)
	{
		ErrorMessage("ConstantBuffer::Create 定数バッファのサイズは１６の倍数で指定して下さい");
		return false;
	}
	D3D11_BUFFER_DESC desc = { 0 };
	desc.ByteWidth = byteSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	
	m_bufferSize = byteSize;

	if (FAILED(D3D11Device::GetDevice()->CreateBuffer(&desc,nullptr,&mp_buffer)))
	{
		ErrorMessage("ConstantBuffer::Create コンスタントバッファの生成に失敗しました。");
		return false;
	}
	return true;
}

//■■■■■■■■■■■■■■■■■■■■■■
//■■■　機能：定数バッファにデータを設定します。
//■■■ 引数1：void*：セットするリソース配列
//■■■   返値：bool：設定したかしてないかを返します
//■■■■■■■■■■■■■■■■■■■■■■
bool	OGL::ConstantBuffer::SetResource(void* resource)
{
	D3D11Device::GetDeviceConText()->UpdateSubresource
		(mp_buffer.Get(), 0, NULL, resource, 0, 0);
	return true;
}
