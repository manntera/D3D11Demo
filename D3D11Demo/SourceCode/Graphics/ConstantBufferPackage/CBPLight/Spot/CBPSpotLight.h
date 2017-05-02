//==========================
//===�yCBPSpotLight.h�z
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
#include"../../../PipelineMatrix/WorldMatrix/WorldMatrix.h"

#define MAX_SPOT_LIGHT_COUNT (50)

namespace	OGL
{
	class	CBPSpotLight
	{
	private:
		struct T_light
		{
			D3DXVECTOR4	pos;
			D3DXVECTOR4	rot;
			D3DXVECTOR4	diffuseCollar;
			D3DXVECTOR4	decrement;		//x=�����J�n���� y=�����I������ z=�X�|�b�g���C�g�͈̔�
		};
		struct T_BufferData
		{
			float count[4];
			T_light light[MAX_SPOT_LIGHT_COUNT];
		};

	public:
		void					SetSlotCount(UINT count);
		void					SetDiffuseCollar(UINT slot, D3DXVECTOR4 col);
		void					SetDecrement(UINT slot, float prm1, float prm2);
		void					AddDecrement(UINT slot, float prm1, float prm2);
		void					SetRange(UINT slot, float range);	//1~-1 ���ϒl��ݒ�
		void					AddRange(UINT slot, float range);	//1~-1 ���ϒl��ݒ�
		WorldMatrix*		GetTransform(UINT slot);
		void					Update(void);
		ConstantBuffer*	GetConstantBuffer(void);

	private:
		T_BufferData		m_lightData;
		ConstantBuffer		m_constantBuffer;
		WorldMatrix			m_lightMat[MAX_SPOT_LIGHT_COUNT];
	public:
		CBPSpotLight();
		~CBPSpotLight();
	private:
	};	//EndOf__class_CBPLight
}	//EndOf__namespace_OGL
