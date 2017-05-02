//==========================
//===【RPDepthBuffer.h】
//==========================
//    深度バッファを生成します。
//==========================
#pragma	once
//=====================//
//===【インクルード記述】 ===//
//=====================//
#include"../../D3D11RenderManager/D3D11RenderManager.h"
#include"../../ConstantBufferPackage/CBPPipelineMatrix/CBPPipelineMatrix.h"
#include"../../ModelData/ModelData.h"

namespace	OGL
{
	class	RPDepthBuffer
	{
	public:
		bool	SetMapSize(float size);
//		bool	SetProjectionMatrix(ProjectionMatrix*	matObj);
		bool	SetViewMatrix(ViewMatrix*	matObj);
		bool	SetWorldMatrix(WorldMatrix*	matObj);
		bool	SetModelData(ModelData*		modelData);
		bool	Draw(OutputTexture* tex,float texXsize,float texYsize);

	private:
		float				m_mapSize;

		ProjectionMatrix	m_proj;
		D3D11RenderData		m_renderData;
		CBPPipelineMatrix	m_transfoam;
		ModelData*			mp_modelData;

	public:
		RPDepthBuffer();
		~RPDepthBuffer();

	};	//EndOf__class_RPGBuffer
}	//EndOf__namespace_OGL
