//=========================================================================//
//======【PrijectionMatrix.cpp】
//======		プロジェクション行列を管理しています。
//=========================================================================//
#include "ProjectionMatrix.h"

OGL::ProjectionMatrix::ProjectionMatrix()
{
	D3DXMatrixIdentity(&m_matrix);
	m_fovAngle = 45.0f;
	m_aspect = 16 / 9;
	m_nearZ = 1;
	m_farZ = 1000;
	m_perspectiveEnable = true;
}

OGL::ProjectionMatrix::~ProjectionMatrix()
{
}

//■■■■■■■■■■■■
//■■■【private】 ■■■
//■■■■■■■■■■■■
//▼▼▼プロジェクション行列の設定▼▼▼
void	OGL::ProjectionMatrix::CreateMatrix(void)
{
	if (m_perspectiveEnable) {
		D3DXMatrixPerspectiveFovLH(&m_matrix, D3DXToRadian(m_fovAngle), m_aspect, m_nearZ, m_farZ);
	}
	else {
		D3DXMatrixOrthoLH(&m_matrix, m_size.x, m_size.y, m_nearZ, m_farZ);
	}
}

//■■■■■■■■■■■
//■■■【public】■■■
//■■■■■■■■■■■
void	OGL::ProjectionMatrix::SetPerspectiveEnable(bool enable)
{
	m_perspectiveEnable = enable;
}
//▼▼▼視野角の設定▼▼▼
void	OGL::ProjectionMatrix::SetFovangle(float angle)
{
	m_fovAngle = angle;
}

//▼▼▼アスペクト比の設定▼▼▼
void	OGL::ProjectionMatrix::SetAspect(float aspect)
{
	m_aspect = aspect;
}

//▼▼▼アスペクトの設定▼▼▼
void	OGL::ProjectionMatrix::SetAspect(float X, float Y)
{
	m_aspect = X / Y;
	m_size.x = X;
	m_size.y = Y;
}

//▼▼▼クリッピングプレーンの設定▼▼▼
void	OGL::ProjectionMatrix::SetClippingPlane(float nearP, float farP)
{
	m_nearZ = nearP;
	m_farZ = farP;
}

//▼▼▼プロジェクション行列の取得▼▼▼
D3DXMATRIX*	OGL::ProjectionMatrix::Getmatrix(void)
{
	CreateMatrix();
	return &m_matrix;
}