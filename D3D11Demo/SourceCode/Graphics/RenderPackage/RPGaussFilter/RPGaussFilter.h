//==========================
//===�yRPGaussFilter.h�z
//==========================
//    �K�E�X�t�B���^�[�`��ɕK�v�ȃf�[�^�Ƌ@�\���Ǘ����܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../../D3D11Device/D3D11Device.h"
#include"../../D3D11RenderManager/D3D11RenderManager.h"

namespace	OGL
{
	class	RPGaussFilter
	{
		struct T_GaussConstant
		{
			D3DXVECTOR4 weight1;
			D3DXVECTOR4 weight2;
		};
		struct T_TexSize
		{
			D3DXVECTOR4 texSize;	// x�cWidth y�cHeight z�coffsetX w�coffsetY
		};
	public:
		bool	SetDivision(float dispersion);
		bool	SetTexSize(float width, float height);
		bool	SetInputTexture(InputTexture* tex);
		bool	Draw(OutputTexture* tex);
	private:
		D3D11RenderData	m_renderData;
		IndexBuffer			m_indexBuff;
		VertexBuffer		m_posBuff;
		VertexBuffer		m_uvBuff;
		InputTexture*		m_inputTex;

		ConstantBuffer		m_weight;
		ConstantBuffer		m_texSize;

		VertexShader	vsX;
		PixelShader	psX;
		VertexShader	vsY;
		PixelShader	psY;

	public:
		RPGaussFilter();
		~RPGaussFilter();
	private:
	};	//EndOf__class_RPGaussFilter
}	//EndOf__namespace_OGL
