//==========================
//===【CBPSpotLight.cpp】
//==========================
//    ライトの情報をまとめた
//    コンスタントバッファパッケージを管理・保持すます。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"CBPSpotLight.h"

OGL::CBPSpotLight::CBPSpotLight()
{
	m_constantBuffer.Create(sizeof(T_BufferData));
	m_lightData.count[0] = 0;

	for (int i = 0; i < MAX_SPOT_LIGHT_COUNT; i++)
	{
		m_lightData.light[i].pos = D3DXVECTOR4(0, 0, 0, 1);
		m_lightData.light[i].rot = D3DXVECTOR4(0, 0, 1, 1);
		m_lightData.light[i].diffuseCollar = D3DXVECTOR4(1, 1, 1, 1);
		m_lightData.light[i].decrement = D3DXVECTOR4(0, 0, 0, 1);
	}
}

OGL::CBPSpotLight::~CBPSpotLight()
{
}
void	OGL::CBPSpotLight::SetSlotCount(UINT count)
{
	m_lightData.count[0] = count;
}
void	OGL::CBPSpotLight::SetDiffuseCollar(UINT slot, D3DXVECTOR4 col)
{
	m_lightData.light[slot].diffuseCollar = col;
}
void	OGL::CBPSpotLight::SetDecrement(UINT slot, float prm1, float prm2)
{
	m_lightData.light[slot].decrement.x = prm1;
	m_lightData.light[slot].decrement.y = prm2;
}
void	OGL::CBPSpotLight::AddDecrement(UINT slot, float prm1, float prm2)
{
	m_lightData.light[slot].decrement.x += prm1;
	m_lightData.light[slot].decrement.y += prm2;
}
void	OGL::CBPSpotLight::SetRange(UINT slot, float range)
{
	m_lightData.light[slot].decrement.z = range;
}
void	OGL::CBPSpotLight::AddRange(UINT slot, float range)
{
	m_lightData.light[slot].decrement.z += range;
}
OGL::WorldMatrix*	OGL::CBPSpotLight::GetTransform(UINT slot)
{
	return &m_lightMat[slot];
}
void	OGL::CBPSpotLight::Update(void)
{
	for (int i = 0; i < MAX_SPOT_LIGHT_COUNT; i++)
	{
		D3DXMATRIX* mat = m_lightMat[i].Getmatrix();
		m_lightData.light[i].pos.x = mat->_41;
		m_lightData.light[i].pos.y = mat->_42;
		m_lightData.light[i].pos.z = mat->_43;
		m_lightData.light[i].rot.x = mat->_31;
		m_lightData.light[i].rot.y = mat->_32;
		m_lightData.light[i].rot.z = mat->_33;

	}
	m_constantBuffer.SetResource(&m_lightData);
}
OGL::ConstantBuffer*	OGL::CBPSpotLight::GetConstantBuffer(void)
{
	return &m_constantBuffer;
}