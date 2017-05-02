//==========================
//===【DepthStencilTexture.h】
//==========================
//    DirectX11における
//    デプスステンシルテクスチャの管理を行います
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../../../D3D11Device/D3D11Device.h"

namespace	OGL
{
	enum DSTEX_FORMAT
	{
		DSF_D16,
		DSF_D32,
		DSF_D24S8,
	};
	class	DepthStencilTexture
	{
	public:
		bool	Create(UINT width, UINT height, DSTEX_FORMAT format, bool	srvFlg);
		void	Clear(float depth, UINT8 stencil = 0);
		ID3D11DepthStencilView*		GetDSV(void);
		ID3D11ShaderResourceView*	GetSRV(void);
		void	Release(void);

	private:
		ID3D11Texture2D*			m_depthStencilTexture;
		ID3D11DepthStencilView*	mp_depthStencilView;
		ID3D11ShaderResourceView*	mp_srv;

		UINT	m_width;
		UINT	m_height;
		DXGI_FORMAT	m_format;

	public:
		DepthStencilTexture();
		~DepthStencilTexture();
	};	//EndOf__class_DepthStencilTexture
}	//EndOf__namespace_OGL
