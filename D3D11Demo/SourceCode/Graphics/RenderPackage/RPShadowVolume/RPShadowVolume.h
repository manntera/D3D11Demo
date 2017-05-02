//==========================
//===�yRPShadowVolume.h�z
//==========================
//    �V���h�E�{�����[���ɗp����GBuffer�̕`��ɕK�v�ȃf�[�^�Ƌ@�\���Ǘ����܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../../D3D11RenderManager/D3D11RenderManager.h"
#include"../../ConstantBufferPackage/CBPPipelineMatrix/CBPPipelineMatrix.h"
#include"../../ModelData/ModelData.h"

namespace	OGL
{
	class	RPShadowVolume
	{
	public:
		bool	SetProjectionMatrix(ProjectionMatrix*	matObj);
		bool	SetViewMatrix(ViewMatrix*	matObj);
		bool	SetWorldMatrix(WorldMatrix*	matObj);
		bool	SetModelData(ModelData*		modelData);
		bool	Draw(OutputTexture* tex);

	private:
		D3D11RenderData		m_renderData;
		CBPPipelineMatrix	m_transfoam;
		ConstantBuffer		m_lightVector;
		ModelData*			mp_modelData;

	public:
		RPShadowVolume();
		~RPShadowVolume();

	};	//EndOf__class_RPGBuffer
}	//EndOf__namespace_OGL
