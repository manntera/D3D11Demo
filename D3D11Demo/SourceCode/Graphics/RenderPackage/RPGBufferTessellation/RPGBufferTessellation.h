//==========================
//===�yRPGBufferTessellation.h�z
//==========================
//    �f�B�t�@�[�h�����_�����O�ɗp����GBuffer�̕`��ɕK�v�ȃf�[�^�Ƌ@�\���Ǘ����܂��B
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
	class	RPGBufferTessellation
	{
	public:
		bool	SetProjectionMatrix(ProjectionMatrix*	matObj);
		bool	SetViewMatrix(ViewMatrix*	matObj);
		bool	SetWorldMatrix(WorldMatrix*	matObj);
		bool	Draw(OutputTexture* tex);

	private:
		D3D11RenderData	m_renderData;
		CBPPipelineMatrix m_transfoam;
		ConstantBuffer		m_TessParmBuff;

		ImageTexture		m_mapTex;
		InputTexture		m_inputTex;
		IndexBuffer			m_indexBuffer;
		VertexBuffer		m_posBuffer;
		VertexBuffer		m_uvBuffer;
	public:
		RPGBufferTessellation();
		~RPGBufferTessellation();
	private:
	};	//EndOf__class_RPGBuffer
}	//EndOf__namespace_OGL
