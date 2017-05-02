//==========================
//===【HullShader.h】
//==========================
//    DirectX11における
//    ハルシェーダーの管理を行います。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../BaseShader/BaseShader.h"
#include"../../D3D11RenderData.h"

namespace	OGL
{
	class D3D11RenderData;

	class	HullShader :public BaseShader
	{
	public:
		bool	CreateShader(char* shaderFileName, char* functionName, char* profile);

	private:
		WRL::ComPtr<ID3D11HullShader>	mp_hullShader;

	public:
		HullShader();
		~HullShader();

		friend D3D11RenderData;
	};	//EndOf__class_PixelShader
}	//EndOf__namespace_OGL
