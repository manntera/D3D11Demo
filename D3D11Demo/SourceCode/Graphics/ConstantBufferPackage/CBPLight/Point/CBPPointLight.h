//==========================
//===�yCBPPointLight.h�z
//==========================
//    ���C�g�̏����܂Ƃ߂�
//    �R���X�^���g�o�b�t�@�p�b�P�[�W���Ǘ��E�ێ����܂��B
//==========================
#pragma	once
//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include"../../../D3D11Device/D3D11Device.h"
#include"../../../ConstantBuffer/ConstantBuffer.h"
#include"../../../PipelineMatrix/ViewMatrix/ViewMatrix.h"

#define MAX_POINT_LIGHT_COUNT (10)

namespace	OGL
{
	class	CBPPointLight
	{
	private:
		struct T_light
		{
			D3DXVECTOR4 lightPos;
			D3DXVECTOR4	diffuseCollar;
			D3DXVECTOR4	decrement;		//x=�����J�n���� y=�����I������
		};
		struct T_BufferData
		{
			float count[4];
			T_light light[MAX_POINT_LIGHT_COUNT];
		};

	public:
		void					SetSlotCount(UINT count);
		void					SetPos(UINT slot,D3DXVECTOR3 pos);
		void					AddPos(UINT slot, D3DXVECTOR3 pos);
		void					SetDiffuseCollar(UINT slot, D3DXVECTOR4 col);
		void					SetDecrement(UINT slot, float prm1, float prm2);
		void					AddDecrement(UINT slot, float prm1, float prm2);
		void					Update(void);
		ConstantBuffer*	GetConstantBuffer(void);

	private:
		T_BufferData		m_lightData;
		ConstantBuffer		m_constantBuffer;
	public:
		CBPPointLight();
		~CBPPointLight();
	private:
	};	//EndOf__class_CBPLight
}	//EndOf__namespace_OGL
