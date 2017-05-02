//==========================
//===【D3D11RenderData.h】
//==========================
//    DirectX11における
//    レンダリングする際に必要なパイプラインデータを保持します。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include<vector>
#include"../D3D11Device/D3D11Device.h"

#include"Shader/VertexShader/VertexShader.h"
#include"Shader/HullShader/HullShader.h"
#include"Shader/DomainShader/DomainShader.h"
#include"Shader/GeometryShader/GeometryShader.h"
#include"Shader/PixelShader/PixelShader.h"

#include"RenderState/BlendState/BlendState.h"
#include"RenderState/RasterizerState/RasterizerState.h"
#include"RenderState/DepthStencilState/DepthStencilState.h"
#include"RenderState/SamplerState/SamplerState.h"

#include"ViewPort/ViewPort.h"

#include"../D3D11RenderManager/D3D11RenderManager.h"

namespace	OGL
{
	class D3D11RenderManager;
	class VertexShader;
	class HullShader;
	class DomainShader;
	class GeometryShader;
	class PixelShader;
	class BlendState;
	class RasterizerState;
	class DepthStencilState;
	class SamplerState;
	class ViewPort;

	class	D3D11RenderData
	{
	private:
		struct T_SamplerData
		{
			int slot;
			WRL::ComPtr<ID3D11SamplerState> state;
		};

	public:
		void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology);
		void SetVertexShader(VertexShader* vertexShader);
		void SetHullShader(HullShader* hullShader);
		void SetDomainShader(DomainShader* domainShader);
		void SetGeometryShader(GeometryShader* geometryShader);
		void SetPixelShader(PixelShader* pixelShader);

		void SetVsSamplerState(SamplerState* samplerState,int slot);
		void SetHsSamplerState(SamplerState* samplerState, int slot);
		void SetDsSamplerState(SamplerState* samplerState, int slot);
		void SetGsSamplerState(SamplerState* samplerState, int slot);
		void SetPsSamplerState(SamplerState* samplerState, int slot);

		void SetRasterizerState(RasterizerState* rasterizerState);
		void SetDepthStencilState(DepthStencilState* depthStencilState, UINT writeStencilNum = 1);
		void SetBlendState(BlendState* blendState, UINT sampleMask = 0xffffffff, float factor_r = 1, float factor_g = 1, float factor_b = 1, float factor_a = 1);

		void SetViewPort(ViewPort* viewPort);
		friend D3D11RenderManager;
	private:
		D3D_PRIMITIVE_TOPOLOGY						m_primitiveTopology;
		WRL::ComPtr<ID3D11InputLayout>				mp_inputLayout;
		WRL::ComPtr<ID3D11VertexShader>			mp_vertexShader;
		WRL::ComPtr<ID3D11HullShader>				mp_hullShader;
		WRL::ComPtr<ID3D11DomainShader>			mp_domainShader;
		WRL::ComPtr<ID3D11GeometryShader>		mp_geometryShader;
		WRL::ComPtr<ID3D11PixelShader>				mp_pixelShader;
		
		std::shared_ptr<D3D11_VIEWPORT>			mp_viewPort;
		std::vector<T_SamplerData>						m_vsSamplerState;
		std::vector<T_SamplerData>						m_hsSamplerState;
		std::vector<T_SamplerData>						m_dsSamplerState;
		std::vector<T_SamplerData>						m_gsSamplerState;
		std::vector<T_SamplerData>						m_psSamplerState;
		WRL::ComPtr<ID3D11RasterizerState>			mp_rasterizerState;
		WRL::ComPtr<ID3D11DepthStencilState>		mp_depthStencilState;
		UINT														m_writeStencilNum;
		WRL::ComPtr<ID3D11BlendState>				mp_blendState;
		float														m_blendFactor[4];
		UINT														m_sampleMask;

		ID3D11DeviceContext* mp_devCon;

	public:
		D3D11RenderData();
		~D3D11RenderData();

	};	//EndOf__class_D3D11RenderData
}	//EndOf__namespace_OGL
