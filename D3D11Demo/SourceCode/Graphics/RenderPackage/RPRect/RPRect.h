//==========================
//===�yRPRect.h�z
//==========================
//    �l�p�`�̕`��ɕK�v�ȃf�[�^�Ƌ@�\���Ǘ����܂��B
//    ���̍ہA�s�N�Z���V�F�[�_�[���O������w�肷�鎖��
//    �|�X�g�v���Z�X�̏����ɗp���܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../../D3D11Device/D3D11Device.h"
#include"../../D3D11RenderManager/D3D11RenderManager.h"
#include<vector>

namespace	OGL
{
	class	RPRect
	{
	public:
		bool	SetRectSize(float xPos, float yPos, float xLen, float yLen);
		bool	SetInputTexture(InputTexture* tex);
		bool	SetSampler(SamplerState* smp, UINT slot);
		bool	SetPixelShader(char* fileName);
		bool	SetConstantBuffer(ConstantBuffer* buff, UINT slot);
		bool	Draw(OutputTexture* tex);

	private:
		struct T_PsConstantBuffer
		{
			ConstantBuffer*	cb;
			UINT					slot;
		};
		D3D11RenderData		m_renderData;
		ConstantBuffer			m_rectData;
		InputTexture*			m_inputTex;
		IndexBuffer				m_index;
		VertexBuffer			m_vertex;
		std::vector<T_PsConstantBuffer>	m_constantBuffer;

	public:
		RPRect();
		~RPRect();
	private:
	};	//EndOf__class_RPRect
}	//EndOf__namespace_OGL
