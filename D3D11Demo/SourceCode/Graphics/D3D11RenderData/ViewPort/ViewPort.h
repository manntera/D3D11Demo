//==========================
//===�yViewPort.h�z
//==========================
//    DirectX11�ɂ�����
//    �r���[�|�[�g�ݒ��
//    �Ǘ��E�ێ����s���܂�
//==========================
#pragma	once
#include"../../D3D11Device/D3D11Device.h"
#include"../D3D11RenderData.h"
#include<memory>

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
namespace	OGL
{
	class D3D11RenderData;

	class	ViewPort
	{
	public:
		void	SetRange(float topLeftX, float topLeftY, float Width, float height);
		void	SetDepth(float min, float max);

	private:
		std::shared_ptr<D3D11_VIEWPORT> mp_viewPort;

	public:
		ViewPort();
		~ViewPort();

		friend D3D11RenderData;

	};	//EndOf__class_ViewPort
}	//EndOf__namespace_OGL
