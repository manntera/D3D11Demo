//==========================
//===【VertexShader.h】
//==========================
//    DirectX11における
//    頂点シェーダーの管理を行います
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

	class	VertexShader:public BaseShader
	{
	public:
		void	SetInputLayoutNum(UINT num);
		bool	SetInputLayoutData(UINT arrayNum, char* semanticName, UINT inputSlot, DXGI_FORMAT format,
											UINT semanticIndex = 0, UINT byteOffset = 0,
											D3D11_INPUT_CLASSIFICATION instanceFlg = D3D11_INPUT_PER_VERTEX_DATA, 
											UINT InstanceDataStepRate=0);
		bool	CreateShader(char* shaderFileName, char* functionName, char* profile);

	private:
		UINT	m_layoutum;
		D3D11_INPUT_ELEMENT_DESC*			mp_layoutData;
		WRL::ComPtr<ID3D11VertexShader>	mp_vertexShader;
		WRL::ComPtr<ID3D11InputLayout>		mp_vertexLayout;

	public:
		VertexShader();
		~VertexShader();

		friend D3D11RenderData;
	};	//EndOf__class_VertexShader
}	//EndOf__namespace_OGL
