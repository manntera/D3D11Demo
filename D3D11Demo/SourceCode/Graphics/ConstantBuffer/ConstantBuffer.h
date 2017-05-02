//==========================
//===�yConstantBuffer.h�z
//==========================
//    DirectX11�ɂ�����
//    �R���X�^���g�o�b�t�@(�萔�o�b�t�@)���Ǘ����܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../D3D11Device/D3D11Device.h"
#include"../D3D11RenderManager/D3D11RenderManager.h"
#include<vector>

namespace	OGL
{
	class D3D11RenderManager;

	class	ConstantBuffer
	{
	public:
		bool	Create(UINT byteSize);
		bool	SetResource(void* resource);

	private:
		WRL::ComPtr<ID3D11Buffer> mp_buffer;
		UINT				m_bufferSize;

	public:
		ConstantBuffer();
		~ConstantBuffer();

		friend D3D11RenderManager;
	};	//EndOf__class_ConstantBuffer
}	//EndOf__namespace_OGL
