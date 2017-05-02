//==========================
//===【DepthStencilState.h】
//==========================
//    DirectX11における
//    デプスステンシルステートの管理を行います
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../../../D3D11Device/D3D11Device.h"
#include"../../D3D11RenderData.h"

namespace	OGL
{
	class	DepthStencilState
	{
	public:
		bool	SetDepthTestEnable(bool enable);
		bool	SetDepthBufferWriteEnable(bool enable);
		bool	SetDepthTestComparisonFunc(D3D11_COMPARISON_FUNC func);
		bool	SetStencilEnable(bool enable);
		bool	SetStencilReadMask(UINT8 mask);
		bool	SetStencilWriteMask(UINT8 mask);
		bool	SetFrontFace(D3D11_STENCIL_OP StencilFailOp, D3D11_STENCIL_OP StencilDepthFailOp, D3D11_STENCIL_OP StencilPassOp,D3D11_COMPARISON_FUNC StencilFunc);
		bool	SetBackFace(D3D11_STENCIL_OP StencilFailOp, D3D11_STENCIL_OP StencilDepthFailOp, D3D11_STENCIL_OP StencilPassOp, D3D11_COMPARISON_FUNC StencilFunc);

		bool	Create(void);

	private:
		D3D11_DEPTH_STENCIL_DESC	m_desc;
		WRL::ComPtr<ID3D11DepthStencilState>	mp_state;
		
	public:
		DepthStencilState();
		~DepthStencilState();

		friend D3D11RenderData;
	};	//EndOf__class_DepthStencilState
}	//EndOf__namespace_OGL
