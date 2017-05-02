//=========================================================================//
//======【ViewMatrix.cpp 】
//======		カメラ行列を管理しています。
//=========================================================================//
#include "ViewMatrix.h"
#include"../../../input/input.h"

OGL::ViewMatrix::ViewMatrix()
{
	D3DXMatrixIdentity(&m_matrix);
	m_centerPos = D3DXVECTOR3(0, 0, 0);
	m_rot=D3DXVECTOR3(0,0,0);
	m_length=1;
}

OGL::ViewMatrix::~ViewMatrix()
{
}

//■■■■■■■■■■■■
//■■■【private】 ■■■
//■■■■■■■■■■■■
//▼▼▼ビュー行列の設定▼▼▼
void	OGL::ViewMatrix::CreateMatrix(void)
{
	D3DXMATRIX temp;
	D3DXVECTOR3 upVec;
	D3DXVECTOR3 rotVec;
	D3DXVec3Normalize(&upVec, &upVec);
	D3DXMatrixRotationYawPitchRoll(&temp, D3DXToRadian(m_rot.y), D3DXToRadian(m_rot.x), D3DXToRadian(m_rot.z));
	rotVec.x = temp._31;
	rotVec.y = temp._32;
	rotVec.z = temp._33;
	upVec.x = temp._21;
	upVec.y = temp._22;
	upVec.z = temp._23;
	D3DXVec3Normalize(&rotVec, &rotVec);
	D3DXMatrixIdentity(&m_matrix);
	D3DXMatrixLookAtLH(&m_matrix, &(m_centerPos + (-rotVec*(m_length+1))), &m_centerPos, &upVec);
}

//■■■■■■■■■■■
//■■■【public】■■■
//■■■■■■■■■■■
void	OGL::ViewMatrix::SetCenterPos(float x, float y, float z)
{
	m_centerPos.x = x;
	m_centerPos.y = y;
	m_centerPos.z = z;
}

void	OGL::ViewMatrix::SetRotation(float x, float y, float z)
{
	m_rot.x = x;
	m_rot.y = y;
	m_rot.z = z;
}

void	OGL::ViewMatrix::SetLength(float length)
{

	m_length = length;
}

void	OGL::ViewMatrix::AddCenterPos(float x, float y, float z)
{
	m_centerPos.x += x;
	m_centerPos.y += y;
	m_centerPos.z += z;
}

void	OGL::ViewMatrix::AddRotation(float x, float y, float z)
{
	m_rot.x += x;
	m_rot.y += y;
	m_rot.z += z;
}

void	OGL::ViewMatrix::AddLength(float length)
{
	m_length += length;
}

void	OGL::ViewMatrix::UpdateDebugCamera(void)
{
	if (GetKeyboardPress(DIK_LCONTROL))
	{
		if (GetKeyboardPress(DIK_W))
		{
			this->AddCenterPos(0, 0.3, 0);
		}
		if (GetKeyboardPress(DIK_S))
		{
			this->AddCenterPos(0, -0.3, 0);
		}
		if (GetKeyboardPress(DIK_A))
		{
			this->AddCenterPos(-0.3, 0, 0);
		}
		if (GetKeyboardPress(DIK_D))
		{
			this->AddCenterPos(0.3, 0, 0);
		}
		if (GetKeyboardPress(DIK_Q))
		{
			this->AddLength(-0.3);
		}
		if (GetKeyboardPress(DIK_E))
		{
			this->AddLength(0.3);
		}
	}
	else
	{
		if (GetKeyboardPress(DIK_W))
		{
			this->AddRotation(1, 0, 0);
		}
		if (GetKeyboardPress(DIK_S))
		{
			this->AddRotation(-1, 0, 0);
		}
		if (GetKeyboardPress(DIK_A))
		{
			this->AddRotation(0, 1, 0);
		}
		if (GetKeyboardPress(DIK_D))
		{
			this->AddRotation(0, -1, 0);
		}
		if (GetKeyboardPress(DIK_Q))
		{
			this->AddRotation(0, 0, -1);
		}
		if (GetKeyboardPress(DIK_E))
		{
			this->AddRotation(0, 0, 1);
		}
	}
	if (GetKeyboardPress(DIK_Z))
	{
		this->AddCenterPos(0, 0, -0.3);
	}
	if (GetKeyboardPress(DIK_X))
	{
		this->AddCenterPos(0, 0, 0.3);
	}
}

//▼▼▼ビュー行列の取得▼▼▼
D3DXMATRIX*	OGL::ViewMatrix::Getmatrix(void)
{
	CreateMatrix();
	return &m_matrix;
}