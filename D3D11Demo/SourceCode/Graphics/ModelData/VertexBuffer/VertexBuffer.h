//==========================
//===�yVertexBuffer.h�z
//==========================
//    DirectX11�ɂ�����A
//    ���_�o�b�t�@���Ǘ����܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../../D3D11RenderManager/D3D11RenderManager.h"
#include<memory>

namespace	OGL
{
	class D3D11RenderManager;

	class	VertexBuffer
	{
	public:
		bool	Create(UINT vertexCount, D3DXVECTOR4* vertexData, bool	updateEnable=false);
		D3DXVECTOR4	GetUpdateVertexData(UINT vertexNum);
		bool	SetUpdateVertexData(UINT vertexNum, D3DXVECTOR4 vertexData);
		bool	IsUpdate(void);
		bool	UpdateBuffer(void);
	private:
		WRL::ComPtr<ID3D11Buffer>		mp_buffer;
		std::unique_ptr<D3DXVECTOR4[]>	mp_data;
		unsigned int		m_count;
		bool					m_updateEnable;
	public:
		VertexBuffer();
		~VertexBuffer();

		friend D3D11RenderManager;
	};	//EndOf__class_VertexBuffer
}	//EndOf__namespace_OGL
