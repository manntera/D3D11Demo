//==========================
//===�yRPLambertModel.h�z
//==========================
//    LambertModel�`��ɕK�v�ȃf�[�^�Ƌ@�\���Ǘ����܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../../D3D11RenderManager/D3D11RenderManager.h"
#include"../../ConstantBufferPackage/CBPPipelineMatrix/CBPPipelineMatrix.h"
#include"../../ConstantBufferPackage/CBPLight/Point/CBPPointLight.h"
#include"../../ModelData/ModelData.h"

namespace	OGL
{
	class	RPLambertModel
	{
	public:
		bool	SetProjectionMatrix(ProjectionMatrix*	matObj);
		bool	SetViewMatrix(ViewMatrix*	matObj);
		bool	SetWorldMatrix(WorldMatrix*	matObj);
		bool	SetPointLight(CBPPointLight* data);
		bool	SetModelData(ModelData*		modelData);
		bool	Draw(OutputTexture* tex);

	private:
		D3D11RenderData	m_renderData;
		CBPPipelineMatrix m_transfoam;
		CBPPointLight*		mp_pointLight;
		ModelData*			mp_modelData;

	public:
		RPLambertModel();
		~RPLambertModel();

	private:
	};	//EndOf__class_RPLambertModel
}	//EndOf__namespace_OGL
