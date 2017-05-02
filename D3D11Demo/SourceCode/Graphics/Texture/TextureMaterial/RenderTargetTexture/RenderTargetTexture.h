//==========================
//===【RenderTargetTexture.h】
//==========================
//    DirectX11における
//    レンダーターゲットテクスチャの管理を行います。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../../../D3D11Device/D3D11Device.h"

namespace	OGL
{
	class	RenderTargetTexture
	{
	public:
		bool	Create(UINT width, UINT height, DXGI_FORMAT texFormat, DXGI_FORMAT srvFormat, DXGI_FORMAT rtvFormat);
		void	Clear(float r, float g, float b, float a);
		ID3D11Texture2D*				GetTEX(void);
		ID3D11ShaderResourceView*	GetSRV(void);
		ID3D11RenderTargetView*		GetRTV(void);
		void	Release(void);

	private:
		ID3D11Texture2D					*mp_tex;
		ID3D11ShaderResourceView	*mp_srv;
		ID3D11RenderTargetView		*mp_rtv;

	public:
		RenderTargetTexture();
		~RenderTargetTexture();
	};	//EndOf__class_RenderTargetTexture
}	//EndOf__namespace_OGL
