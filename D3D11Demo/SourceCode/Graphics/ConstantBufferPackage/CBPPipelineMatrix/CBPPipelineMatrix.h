//==========================
//===�yCBPPipelineMatrix.h�z
//==========================
//    �r���[�C���O�p�C�v���C���̍s��ϊ����܂Ƃ߂�
//    �R���X�^���g�o�b�t�@�p�b�P�[�W���Ǘ��A�ێ����܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../../D3D11Device/D3D11Device.h"
#include"../../ConstantBuffer/ConstantBuffer.h"
#include"../../PipelineMatrix/ProjectionMatrix/ProjectionMatrix.h"
#include"../../PipelineMatrix/ViewMatrix/ViewMatrix.h"
#include"../../PipelineMatrix/WorldMatrix/WorldMatrix.h"

namespace	OGL
{
	class	CBPPipelineMatrix
	{
	private:
		struct T_pipelineMatrix
		{
			D3DXMATRIX	transform;
			D3DXMATRIX	world;
			D3DXMATRIX	view;
			D3DXMATRIX	proj;
			D3DXVECTOR4	viewVector;
		};
	public:
		bool	SetProjectionMatrix(ProjectionMatrix* matObj);
		bool	SetProjectionMatrix(D3DXMATRIX* mat);
		bool	SetViewMatrix(ViewMatrix* matObj);
		bool	SetViewMatrix(D3DXMATRIX* mat);
		bool	SetWorldMatrix(WorldMatrix* matObj);
		bool	SetWorldMatrix(D3DXMATRIX* mat);
		bool	SetInverseFlg(bool flg);

		void	Update(void);

		ConstantBuffer*	GetConstantBuffer(void);

	private:
		T_pipelineMatrix	m_matData;
		ConstantBuffer		m_constantBuffer;

		bool	m_invFlg;
	public:
		CBPPipelineMatrix();
		~CBPPipelineMatrix();

	};	//EndOf__class_CBPPipelineMatrix
}	//EndOf__namespace_OGL
