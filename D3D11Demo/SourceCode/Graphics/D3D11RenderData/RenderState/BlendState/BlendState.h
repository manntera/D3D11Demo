//==========================
//===【BlendState.h】
//==========================
//    DirectX11における
//    ブレンドステートの管理を行います。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../../D3D11RenderData.h"

namespace	OGL
{
	class D3D11RenderData;

	class	BlendState
	{
	public:
		bool	SetAlphaToCoverageEnable(bool enable);
		bool	SetRenderTargetBlendDesc(UINT targetNum, bool BlendEnable, D3D11_BLEND SrcBlend,
			D3D11_BLEND DestBlend, D3D11_BLEND_OP BlendOp, D3D11_BLEND SrcBlendAlpha,
			D3D11_BLEND DestBlendAlpha, D3D11_BLEND_OP BlendOpAlpha, UINT8 RenderTargetWriteMask);
		bool	Create(void);

	private:
		WRL::ComPtr<ID3D11BlendState>	mp_state;
		D3D11_BLEND_DESC	m_desc;

	public:
		BlendState();
		~BlendState();

		friend D3D11RenderData;
	};	//EndOf__class_BlendState
}	//EndOf__namespace_OGL
