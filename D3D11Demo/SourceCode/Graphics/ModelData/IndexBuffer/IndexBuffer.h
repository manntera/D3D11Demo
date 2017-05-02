//==========================
//===【IndexBuffer.h】
//==========================
//    DirectX11における
//    インデックスバッファを管理します。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../../D3D11RenderManager/D3D11RenderManager.h"

namespace	OGL
{
	class D3D11RenderManager;

	class	IndexBuffer
	{
	public:
		bool	Create(UINT indexCount, int* indexData);

	private:
		WRL::ComPtr<ID3D11Buffer>	mp_buffer;
		unsigned int	m_count;

	public:
		IndexBuffer();
		~IndexBuffer();

		friend D3D11RenderManager;
	};	//EndOf__class_IndexBuffer
}	//EndOf__namespace_OGL
