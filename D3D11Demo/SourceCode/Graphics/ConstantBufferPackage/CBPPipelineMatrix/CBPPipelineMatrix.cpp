//==========================
//===【CBPPipelineMatrix.cpp】
//==========================
//    ビューイングパイプラインの行列変換をまとめた
//    コンスタントバッファパッケージを管理、保持します。
//==========================

//=====================//
//===【インクルード記述】 ===//
//=====================//
#include	"CBPPipelineMatrix.h"

OGL::CBPPipelineMatrix::CBPPipelineMatrix()
{
	m_constantBuffer.Create(sizeof(T_pipelineMatrix));
	m_invFlg = false;
}

OGL::CBPPipelineMatrix::~CBPPipelineMatrix()
{
}

bool	OGL::CBPPipelineMatrix::SetProjectionMatrix(ProjectionMatrix* matObj)
{
	m_matData.proj = *matObj->Getmatrix();
	D3DXMatrixTranspose(&m_matData.proj, &m_matData.proj);
	return true;
}
bool	OGL::CBPPipelineMatrix::SetProjectionMatrix(D3DXMATRIX* mat)
{
	D3DXMatrixTranspose(&m_matData.proj, mat);
	return true;
}
bool	OGL::CBPPipelineMatrix::SetViewMatrix(ViewMatrix* matObj)
{
	m_matData.view = *matObj->Getmatrix();
	m_matData.viewVector = D3DXVECTOR4(m_matData.view._13, m_matData.view._23, m_matData.view._33, 1);
	D3DXMatrixTranspose(&m_matData.view, &m_matData.view);
	return true;
}
bool	OGL::CBPPipelineMatrix::SetViewMatrix(D3DXMATRIX* mat)
{
	D3DXMatrixTranspose(&m_matData.proj, mat);
	return true;
}
bool	OGL::CBPPipelineMatrix::SetWorldMatrix(WorldMatrix* matObj)
{
	m_matData.world = *matObj->Getmatrix();
	D3DXMatrixTranspose(&m_matData.world, &m_matData.world);
	return true;
}
bool	OGL::CBPPipelineMatrix::SetWorldMatrix(D3DXMATRIX* mat)
{
	D3DXMatrixTranspose(&m_matData.proj, mat);
	return true;
}
bool	OGL::CBPPipelineMatrix::SetInverseFlg(bool flg)
{
	m_invFlg = flg;
	return true;
}
void	OGL::CBPPipelineMatrix::Update(void)
{
	m_matData.transform = m_matData.proj*m_matData.view*m_matData.world;
	if (m_invFlg)
	{
		T_pipelineMatrix temp;
		D3DXMatrixInverse(&temp.transform, nullptr, &m_matData.transform);
		D3DXMatrixTranspose(&temp.proj, D3DXMatrixInverse(&temp.proj, nullptr, D3DXMatrixTranspose(&temp.proj, &m_matData.proj)));
		D3DXMatrixTranspose(&temp.view, D3DXMatrixInverse(&temp.view, nullptr, D3DXMatrixTranspose(&temp.view, &m_matData.view)));
		D3DXMatrixTranspose(&temp.world, D3DXMatrixInverse(&temp.world, nullptr, D3DXMatrixTranspose(&temp.world, &m_matData.world)));
		m_constantBuffer.SetResource(&temp);
	}
	else
	{
		m_constantBuffer.SetResource(&m_matData);
	}
}
OGL::ConstantBuffer*	OGL::CBPPipelineMatrix::GetConstantBuffer(void)
{
	return &m_constantBuffer;
}