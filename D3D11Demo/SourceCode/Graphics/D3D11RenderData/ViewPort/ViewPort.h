//==========================
//===【ViewPort.h】
//==========================
//    DirectX11における
//    ビューポート設定の
//    管理・保持を行います
//==========================
#pragma	once
#include"../../D3D11Device/D3D11Device.h"
#include"../D3D11RenderData.h"
#include<memory>

//=====================//
//===【インクルード記述】 ===//
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
