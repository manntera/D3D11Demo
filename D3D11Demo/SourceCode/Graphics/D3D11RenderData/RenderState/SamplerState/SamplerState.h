//==========================
//===【SamplerState.h】
//==========================
//    DirectX11における
//    サンプラーステートの管理を行いまｓ。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../../D3D11RenderData.h"

namespace	OGL
{
	class	SamplerState
	{
	public:
		bool	SetFilter(D3D11_FILTER Filter);
		bool	SetAddresMode(D3D11_TEXTURE_ADDRESS_MODE u, D3D11_TEXTURE_ADDRESS_MODE v, D3D11_TEXTURE_ADDRESS_MODE w);
		bool	SetMipLODBias(float bias);
		bool	SetMaxAnisotropy(unsigned int anisotropy);
		bool	SetComparisonFunc(D3D11_COMPARISON_FUNC func);
		bool	SetBorderColor(float r, float g, float b, float a);
		bool	SetLOD(float min, float max);
		bool	Create(void);

	private:
		D3D11_SAMPLER_DESC	m_desc;
		WRL::ComPtr<ID3D11SamplerState>	mp_state;
	public:
		SamplerState();
		~SamplerState();

		friend D3D11RenderData;
	};	//EndOf__class_SamplerState
}	//EndOf__namespace_OGL
