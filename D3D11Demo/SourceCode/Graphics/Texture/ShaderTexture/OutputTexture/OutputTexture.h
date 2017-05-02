//==========================
//===yOutputTexture.hz
//==========================
//    Shader‚©‚ç•`‰æ‚³‚ê‚éTexture‚ğ•Û‚µ‚Ü‚·B
//==========================
#pragma	once
//=====================//
//===yƒCƒ“ƒNƒ‹[ƒh‹Lqz ===//
//=====================//
#include"../../TextureMaterial/BackBuffer/BackBuffer.h"
#include"../../TextureMaterial/DepthStencilTexture/DepthStencilTexture.h"
#include"../../TextureMaterial/RenderTargetTexture/RenderTargetTexture.h"
#include"../../../D3D11RenderManager/D3D11RenderManager.h"

#define MAX_SET_RTV (8)
namespace	OGL
{
	class D3D11RenderManager;
	class RenderTargetTexture;
	class DepthStencilTexture;

	class	OutputTexture
	{
	public:
		bool SetTexture(BackBuffer* tex, unsigned int slot);
		bool SetTexture(RenderTargetTexture* tex, unsigned int slot);
		bool SetTexture(DepthStencilTexture* tex);

		bool ClearRtv(float r = 0, float g = 0, float b = 0, float a = 0, int slot = -1);
		bool ClearDsv(bool depthEnable, bool stencilEnable, float clearDepth = 1, UINT8 clearStencil = 0);
	private:
		ID3D11RenderTargetView* mp_rtv[8];
		ID3D11DepthStencilView* mp_dsv;
	public:
		OutputTexture();
		~OutputTexture();

		friend D3D11RenderManager;
	};	//EndOf__class_OutputTexture
}	//EndOf__namespace_OGL
