//==========================
//===【GeometryShader.h】
//==========================
//    DirectX11における
//    ジオメトリシェーダーの管理を行います
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

	class	GeometryShader:public BaseShader
	{
	public:
		bool	CreateShader(char* shaderFileName, char* functionName, char* profile);

	private:
		WRL::ComPtr<ID3D11GeometryShader>	mp_geometryShader;

	public:
		GeometryShader();
		~GeometryShader();

		friend D3D11RenderData;
	};	//EndOf__class_GeometryShader
}	//EndOf__namespace_OGL
