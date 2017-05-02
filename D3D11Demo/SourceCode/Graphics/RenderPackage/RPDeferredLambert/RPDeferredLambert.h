//==========================
//===【RPDeferredLambert.h】
//==========================
//    ディファードレンダリングによるGBufferの描画に必要なデータと機能を管理します。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../../D3D11Device/D3D11Device.h"
#include"../../D3D11RenderManager/D3D11RenderManager.h"
#include"../../ConstantBufferPackage/CBPPipelineMatrix/CBPPipelineMatrix.h"
#include"../../ConstantBufferPackage/CBPLight/Point/CBPPointLight.h"
#include"../../ConstantBufferPackage/CBPLight/Spot/CBPSpotLight.h"

namespace	OGL
{
	class	RPDeferredLambert
	{
	public:
		void	SetPointLight(CBPPointLight* light);
		void	SetSpotLight(CBPSpotLight* light);
		void	SetProjectionMatrix(ProjectionMatrix* mat);
		void	SetViewMatrix(ViewMatrix* mat);
		void	SetInputTexture(InputTexture* tex);
		void	Draw(OutputTexture* tex);

	private:
		D3D11RenderData	m_renderData;
		
		CBPPipelineMatrix	m_matrix;
		CBPPointLight*		m_pointLight;
		CBPSpotLight*		m_spotLight;
		IndexBuffer			m_indexBuff;
		VertexBuffer		m_posBuff;
		VertexBuffer		m_uvBuff;
		InputTexture*		m_inputTex;

	public:
		RPDeferredLambert();
		~RPDeferredLambert();
	private:
	};	//EndOf__class_RPDeferredLambert
}	//EndOf__namespace_OGL
