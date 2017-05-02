//==========================
//===yInputTexture.hz
//==========================
//    Shader‚É“Ç‚İ‚Ü‚¹‚éTexture‚ğ•Û‚µ‚Ü‚·B
//==========================
#pragma	once
//=====================//
//===yƒCƒ“ƒNƒ‹[ƒh‹Lqz ===//
//=====================//
#include<vector>
#include"../../TextureMaterial/ImageTexture/ImageTexture.h"
#include"../../TextureMaterial/RenderTargetTexture/RenderTargetTexture.h"
#include"../../TextureMaterial/DepthStencilTexture/DepthStencilTexture.h"
#include"../../../D3D11RenderManager/D3D11RenderManager.h"

namespace	OGL
{
	class D3D11RenderManager;
	class RenderTargetTexture;
	class DepthStencilTexture;

	class	InputTexture
	{
	private:
		struct T_srvData
		{
			ID3D11ShaderResourceView	*p_srv;
			unsigned int						slot;
		};
	public:
		bool SetTexture(ImageTexture* tex,unsigned int slot);
		bool SetTexture(RenderTargetTexture* tex, unsigned int slot);
		bool SetTexture(DepthStencilTexture* tex, unsigned int slot);

	private:
		std::vector<T_srvData> inputData;
		bool SetSrv(ID3D11ShaderResourceView* srv, int slot);
	public:
		InputTexture();
		~InputTexture();

		friend D3D11RenderManager;
	};	//EndOf__class_InputTexture
}	//EndOf__namespace_OGL
