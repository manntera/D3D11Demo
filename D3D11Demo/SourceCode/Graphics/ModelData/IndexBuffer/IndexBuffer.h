//==========================
//===�yIndexBuffer.h�z
//==========================
//    DirectX11�ɂ�����
//    �C���f�b�N�X�o�b�t�@���Ǘ����܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
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
