//==========================
//===【CBPPointLight.cpp】
//==========================
//    ライトの情報をまとめた
//    コンスタントバッファパッケージを管理・保持すます。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"CBPPointLight.h"

OGL::CBPPointLight::CBPPointLight()
{
	m_constantBuffer.Create(sizeof(T_BufferData));
	m_lightData.count[0] = 0;
	for (int i = 0; i < MAX_POINT_LIGHT_COUNT; i++)
	{
		m_lightData.light[i].lightPos = D3DXVECTOR4(0, 0, 0, 1);
		m_lightData.light[i].diffuseCollar = D3DXVECTOR4(1, 1, 1, 1);
		m_lightData.light[i].decrement = D3DXVECTOR4(0, 0, 0, 1);
	}
}

OGL::CBPPointLight::~CBPPointLight()
{
}
void	OGL::CBPPointLight::SetSlotCount(UINT count)
{
	m_lightData.count[0] = count;
}
void	OGL::CBPPointLight::SetPos(UINT slot,D3DXVECTOR3 pos)
{
	m_lightData.light[slot].lightPos = D3DXVECTOR4(pos.x, pos.y, pos.z, 1);
}
void	OGL::CBPPointLight::AddPos(UINT slot, D3DXVECTOR3 pos)
{
	m_lightData.light[slot].lightPos += D3DXVECTOR4(pos.x, pos.y, pos.z, 0);
}
void	OGL::CBPPointLight::SetDiffuseCollar(UINT slot, D3DXVECTOR4 col)
{
	m_lightData.light[slot].diffuseCollar = col;
}
void	OGL::CBPPointLight::SetDecrement(UINT slot, float prm1, float prm2)
{
	m_lightData.light[slot].decrement = D3DXVECTOR4(prm1, prm2, 1, 1);
}
void	OGL::CBPPointLight::AddDecrement(UINT slot, float prm1, float prm2)
{
	m_lightData.light[slot].decrement += D3DXVECTOR4(prm1, prm2, 1, 0);
}
void	OGL::CBPPointLight::Update(void)
{
	m_constantBuffer.SetResource(&m_lightData);
}
OGL::ConstantBuffer*	OGL::CBPPointLight::GetConstantBuffer(void)
{
	return &m_constantBuffer;
}